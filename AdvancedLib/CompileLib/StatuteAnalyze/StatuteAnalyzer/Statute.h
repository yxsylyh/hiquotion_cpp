#include "..\..\Lex\Lexer\Lexer.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 这个结构体是规约式在词法分析后得到的
// 包含规约名称和词素列表
typedef struct Statute
{
	std::string statuteName;                  // 规约后的名称
	CPointerList<MachineToken *> tokenList;  // 词素列表
} Statute;  // 规约

// 规约式条目（就是带小点的那种）
typedef struct StatuteItem
{
	StatuteItem()
	{
		statute=NULL;
		indexInStatuteList=-1;
		itemPosition=-1;
	}

	StatuteItem(Statute *s, int indxInStatuteList)
	{
		statute=s;
		indexInStatuteList=indxInStatuteList;
		itemPosition=0;
	}
	
	StatuteItem(Statute *s, int indxInStatuteList, int itemPos)
	{
		statute=s;
		indexInStatuteList=indxInStatuteList;
		itemPosition=itemPos;
	}

	StatuteItem(StatuteItem *item)
	{
		statute=item->statute;
		indexInStatuteList=item->indexInStatuteList;
		itemPosition=item->itemPosition;
	}

	StatuteItem *genNextStatuteItem()
	{
		checkPosition();

		if(itemPosition==statute->tokenList.size())
			return NULL;

		else
			return new StatuteItem(statute, indexInStatuteList, itemPosition+1);
	}
	
	// 打印规约式
	string printStatute()
	{
		return printStatute(itemPosition);
	}

	// 打印规约式
	string printStatute(int itemPosition)
	{
		int i=0;
		string ret;
		ret=statute->statuteName;
		ret+="=>";
		
		if(itemPosition==0)
			ret+=".";
		else
		{
			for(i=0;i<itemPosition;i++)
			{
				MachineToken *token=statute->tokenList.at(i);
				if(!token)
					continue;
				
				ret+=token->token;
			}
			
			ret+=".";
		}
		
		for(i=itemPosition;i<statute->tokenList.size();i++)
		{
			MachineToken *token=statute->tokenList.at(i);
			if(!token)
				continue;
			
			ret+=token->token;
		}
		
		return ret;
	}

	void checkPosition()
	{
		if(itemPosition>statute->tokenList.size())
			itemPosition=statute->tokenList.size();
		
		if(itemPosition<0)
			itemPosition=0;
	}

	BOOL isFinalItemPosition()
	{
		checkPosition();

		if(itemPosition==statute->tokenList.size())
			return TRUE;

		return FALSE;
	}
	
	Statute *statute;
	int indexInStatuteList;
	int itemPosition; // 小点所在位置，0表示最前面
} StatuteItem;  // 规约式条目

