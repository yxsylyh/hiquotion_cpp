// KernelLexer.cpp: implementation of the CKernelLexer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KernelLexer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKernelLexer::CKernelLexer()
{
	m_builder.build();
	m_lexer.setLexStatusGraph(m_builder.getGraph());
}

CKernelLexer::~CKernelLexer()
{

}

// 返回值：
// -1：参数为空
// -2：状态机内部错误（当前结点为空）
// -3：调用 preProcessTokens 失败
int CKernelLexer::analyze(string text, CPointerList<MachineToken *> &tokenList, CValueList<string> &errList)
{
	int ret=m_lexer.analyze(text, tokenList, errList);
	if(ret<0)
		return ret;
	
 	ret=preProcessTokens(tokenList);
	if(ret<0)
		return -3;

	return 0;
}

// 对token列表做预处理
// 1. 把双引号中的内容，变成一个token
// 2. 对于 \" 的处理，如果在一对引号内，则按引号字符处理，如果是在一对引号外，则按引号token处理
// 3. 去掉回车、空格、行注释、块注释等等的token吧
// 4. 提取变量，即在两个%之间的是变量（在提取双引号之间的字符串之后做）
// 参数：
// tokenList：规约式的token列表
// 返回值：
// 0，成功
// -1，tokenList中有错误
// -2，preProcessExtractStringToken调用失败
// -3，第一个token是引号，但不与后面任何token构成引号对
int CKernelLexer::preProcessTokens(CPointerList<MachineToken *> &tokenList)
{
	if(tokenList.size()<=0)
		return -1;

	BOOL isinQuota=FALSE;
	int quotaStartIndex=-1;
	int quotaEndIndex=-1;
//	MachineToken *startToken;
	MachineToken *endToken;

	int i=0;
	// 1. 把双引号中的内容，变成一个token
	// 2. 对于 \" 的处理，如果在一对引号内，则按引号字符处理，如果是在一对引号外，则按引号token处理

	// 从最后一个token开始，这样在操作列表的时候，不会影响列表前面的元素。下同。
	for(i=tokenList.size()-1;i>=0;i--)
	{
		MachineToken *token=tokenList.at(i);
		// 如果发现了引号
		if(token->token=="\"")
		{
			if(i>0 && i-1>=0)
			{
				// 如果引号前面没有\，说明是结束的引号
				if(tokenList.at(i-1)->token!="\\")
				{
					// 如果当前不在引号内
					if(!isinQuota)
					{
						quotaEndIndex=i;
						endToken=token;
						isinQuota=TRUE;
					}
					// 如果已经在引号内了，则取两个引号内的内容，组成一个字符串，将两个引号token和其内的token都删除，并添加该字符串，类型设置为string
					else
					{
						quotaStartIndex=i;
						int ret=preProcessExtractStringToken(tokenList, i, quotaEndIndex);
						if(ret<0)
							return -2;

						// 恢复索引的初值为-1
						quotaStartIndex=-1;
						quotaEndIndex=-1;
						
						// 设置状态为不在引号内
						isinQuota=FALSE;
					}
				}
				else  // 表示实际的引号
				{
					tokenList.destroyByIndex(i-1);

					i--;
				}
			}
			else // i=0 的情况
			{
				// 如果当前不在引号内，说明出错了
				if(!isinQuota)
				{
					std::stringstream ss;
					ss << "第一个token是引号，但不与后面任何token构成引号对";
					m_errMsg=ss.str();
					return -3;
				}
				else
				{
					quotaStartIndex=i;
					int ret=preProcessExtractStringToken(tokenList, i, quotaEndIndex);
					if(ret<0)
						return ret;

					// 恢复索引的初值为-1
					quotaStartIndex=-1;
					quotaEndIndex=-1;
					
					// 设置状态为不在引号内
					isinQuota=FALSE;
				}
			}
		}
	}

	// 3. 去掉回车、空格、行注释、块注释等等的token吧
	for(i=tokenList.size()-1;i>=0;i--)
	{
		MachineToken *token=tokenList.at(i);
		if(!token)
			continue;
		
		std::string name=token->token;
		std::string tp=token->type;
		// 去掉回车、空格、行注释、块注释
		if(name=="\r" || name=="\n" || name=="\r\n" || name==" " || tp=="lineComment" || tp=="blockComment")
			tokenList.destroyByIndex(i);
	}

	// 4. 提取变量，即在两个%之间的是变量（在提取双引号之间的字符串之后做）
	int percentStartIndex=-1;
	int percentEndIndex=-1;
	int percentMetTimes=0;

	for(i=tokenList.size()-1;i>=0;i--)
	{
		MachineToken *token=tokenList.at(i);
		if(!token)
			continue;

		if(token->type!="%")    // 要用type来判断，因为前面引号中的tokenName(name)已经处理成%了，但type是string；
			continue;			// 如果用name判断的话，会混淆，而用type判断就不会混淆了
		
		percentMetTimes=(percentMetTimes+1)%2;

		if(percentMetTimes==1)
		{
			percentEndIndex=i;
			continue;
		}
		else if(percentMetTimes==0)
		{
			percentStartIndex=i;
			if(percentEndIndex==-1)
			{
				percentStartIndex=-1;
				percentEndIndex=-1;
				percentMetTimes=0;
				continue;

			}

			if(percentEndIndex-percentStartIndex!=2)
			{
				percentStartIndex=-1;
				percentEndIndex=-1;
				percentMetTimes=0;
				continue;
			}

			MachineToken *varToken=tokenList.at(i+1);
			if(!varToken)
			{
				percentStartIndex=-1;
				percentEndIndex=-1;
				percentMetTimes=0;
				continue;
			}
// 			if(varToken->type!="id")
// 			{
// 				percentStartIndex=-1;
// 				percentEndIndex=-1;
// 				percentMetTimes=0;
// 				continue;
// 			}
// 
// 			varToken->type="var";

			varToken->check4Statute=CheckType4Statute;

			tokenList.destroyByIndex(percentEndIndex);
			tokenList.destroyByIndex(percentStartIndex);

			percentStartIndex=-1;
			percentEndIndex=-1;
			percentMetTimes=0;
		}
	}

	return 0;
}

// 根据起始和终止索引，来提取该范围的tokens为字符串token
int CKernelLexer::preProcessExtractStringToken(CPointerList<MachineToken *> &tokenList, int startIndex, int endIndex)
{
	int quotaStartIndex=startIndex;
	int quotaEndIndex=endIndex;
	
	// 检查两个引号所在token的位置索引是否合法
	if(quotaStartIndex>=0 && quotaEndIndex>=0 && quotaStartIndex<quotaEndIndex && quotaEndIndex<tokenList.size())
	{
		MachineToken *startToken=tokenList.at(startIndex);
		MachineToken *endToken=tokenList.at(endIndex);
		
		int j=0;
		std::string content="";
		if(quotaEndIndex-quotaStartIndex>1)  // 等于1表示空字符串，就不需要下面语句的处理了；小于1不可能
		{
			for(j=quotaStartIndex+1;j<quotaEndIndex;j++)  // 不保留两个双引号
			{
				MachineToken *tmpToken=tokenList.at(j);
				if(!tmpToken)
					continue;
				
				content+=tmpToken->token;
			}
		}
		
		// 建立一个新的token
		MachineToken *newToken=new MachineToken;
		newToken->startPosition=startToken->startPosition; // 需不需要加1呢，因为该值为引号位置
		newToken->endPosition=endToken->endPosition;  // 需不需要减1呢，因为该值为引号位置
		newToken->token=content;
		newToken->type="string";
		
		// 删除tokenList中的这些解析出来的token
		for(j=quotaEndIndex;j>=quotaStartIndex;j--)
			tokenList.destroyByIndex(j);
		
		// 将新建立的字符串类型的token，添加到quotaStartIndex位置
		if(tokenList.size()<=0)
			tokenList.push_back(newToken);
		else
			tokenList.insert(tokenList.begin()+quotaStartIndex, newToken);
	}
	else
	{
		std::stringstream ss;
		ss<<"token列表中引号的使用有误！（在第" << quotaStartIndex << "和第" << quotaEndIndex << "索引处）";
		m_errMsg=ss.str();
		return -1;
	}
	
	return 0;
}
