// XmlOperation.cpp: implementation of the CXmlOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XmlOperation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXmlOperation::CXmlOperation(string path) : m_root(NULL)
{
	if(m_doc.LoadFile(path.c_str()))
	{
		m_isOpen=true;
		m_root=m_doc.RootElement();
	}	
	else
		m_isOpen=false;
}

CXmlOperation::~CXmlOperation()
{

}

// 获取根节点
TiXmlElement *CXmlOperation::getRoot()
{
	if(m_isOpen)
		return m_doc.RootElement();
	else
		return NULL;
}

// 获取指定节点的子节点中指定节点名中的指定属性名=属性值的节点。
// 如果属性名为空，则不考虑属性的因素，返回当前元素
// 如果属性值为空，则查找具有指定属性名的元素
// 如果该属性名的属性值不空，则找到了，否则继续查找其它节点
// 如果属性值不空，则若属性名=属性值，则返回，否则继续查找其它节点
// 返回空，则查找失败
TiXmlElement *CXmlOperation::getElement(TiXmlElement* element,std::string nodeName,std::string attributeName,std::string attributeValue)
{
	if(!m_isOpen)
		return NULL;
	
	if(!element)
		return NULL;

	TiXmlElement* pEle = NULL;
	for (pEle = element->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())
    {
		if (pEle->Value()==nodeName)
		{
			// 如果属性名为空，则不考虑属性的因素，返回当前元素
			if(attributeName=="")
				return pEle;
			else
			{
				string attribute="";
				attribute=pEle->Attribute(attributeName.c_str());
				// 如果属性值为空，则查找具有指定属性名的元素
				if(attributeValue=="")
				{
					// 如果该属性名的属性值不空，则找到了，否则继续查找其它节点
					if(attribute!="")
						return pEle;
				}
				else
				{
					// 如果属性值不空，则若属性名=属性值，则返回，否则继续查找其它节点
					if(attribute==attributeValue)
						return pEle;
				}
			}
		}
	}
	return NULL;
}

// 获取根节点的子节点中指定节点名中的指定属性名=属性值的节点。
// 如果属性名为空，则不考虑属性的因素，返回当前元素
// 如果属性值为空，则查找具有指定属性名的元素
// 如果该属性名的属性值不空，则找到了，否则继续查找其它节点
// 如果属性值不空，则若属性名=属性值，则返回，否则继续查找其它节点
// 返回空，则查找失败
TiXmlElement *CXmlOperation::getElement(std::string nodeName,std::string attributeName,std::string attributeValue)
{
	if(!m_isOpen)
		return NULL;

	return getElement(m_root,nodeName,attributeName,attributeValue);
}

// 先根遍历子树，获取指定节点名中的指定属性名=属性值的节点。
// 如果属性名为空，则不考虑属性的因素，返回当前元素
// 如果属性值为空，则查找具有指定属性名的元素
// 如果该属性名的属性值不空，则找到了，否则继续查找其它节点
// 如果属性值不空，则若属性名=属性值，则返回，否则继续查找其它节点
// 返回空，则查找失败
TiXmlElement *CXmlOperation::getElementInSubtree(TiXmlElement* subRoot,std::string nodeName,std::string attributeName,std::string attributeValue)
{
	if(!m_isOpen)
		return NULL;

	if(!subRoot)
		return NULL;

	// 假如等于根节点名，就退出
	if (subRoot->Value()==nodeName)
	{
		// 如果属性名为空，则不考虑属性的因素，返回当前元素
		if(attributeName=="")
			return subRoot;
		else
		{
			string attribute="";
			attribute=subRoot->Attribute(attributeName.c_str());
			// 如果属性值为空，则查找具有指定属性名的元素
			if(attributeValue=="")
			{
				// 如果该属性名的属性值不空，则找到了，否则继续查找其它节点
				if(attribute!="")
					return subRoot;
			}
			else
			{
				// 如果属性值不空，则若属性名=属性值，则返回，否则继续查找其它节点
				if(attribute==attributeValue)
					return subRoot;
			}
		}
	}
	TiXmlElement* element = NULL;
	for (element = subRoot->FirstChildElement(); element; element = element->NextSiblingElement())
	{
		//递归处理子节点，获取节点指针
		TiXmlElement *retElement=getElementInSubtree(element,nodeName,attributeName,attributeValue);
		if(retElement)
			return retElement;
	}

	return NULL;
}

// 先根遍历整个树，获取指定节点名中的指定属性名=属性值的节点。
// 如果属性名为空，则不考虑属性的因素，返回当前元素
// 如果属性值为空，则查找具有指定属性名的元素
// 如果该属性名的属性值不空，则找到了，否则继续查找其它节点
// 如果属性值不空，则若属性名=属性值，则返回，否则继续查找其它节点
// 返回空，则查找失败
TiXmlElement *CXmlOperation::getElementInSubtree(std::string nodeName,std::string attributeName,std::string attributeValue)
{
	if(!m_isOpen)
		return NULL;

	return getElementInSubtree(m_root,nodeName,attributeName,attributeValue);
}

// 获取指定节点的文本
string CXmlOperation::getElementText(TiXmlElement *element)
{
	if(!m_isOpen)
		return "";

	if(!element)
		return "";

	TiXmlNode *text=element->FirstChild();
	if(!text)
		return "";

	return text->Value();
}

// 获取指定节点的指定属性名称的属性值
string CXmlOperation::getElementAttribute(TiXmlElement *element,string propertyName)
{
	if(!m_isOpen)
		return "";
	
	if(!element)
		return "";
	
	const char *attribute=element->Attribute(propertyName.c_str());
	if(!attribute)
		return "";

	string propertyValue=attribute;
	return propertyValue;
}
