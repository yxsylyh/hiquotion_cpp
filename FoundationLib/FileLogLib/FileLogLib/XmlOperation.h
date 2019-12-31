// XmlOperation.h: interface for the CXmlOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLOPERATION_H__EB0258EF_638E_46E2_8551_6DFF4BB1D6EF__INCLUDED_)
#define AFX_XMLOPERATION_H__EB0258EF_638E_46E2_8551_6DFF4BB1D6EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tinyxml.h"
#include <string>

class CXmlOperation  
{
public:
	CXmlOperation(std::string path);
	virtual ~CXmlOperation();

	// 获取根节点
	TiXmlElement *getRoot();

	bool isOpenSuccess() const { return m_isOpen; }

	// 获取指定节点的子节点中指定节点名中的指定属性名=属性值的节点。
	// 如果属性名为空，则不考虑属性的因素，返回当前元素
	// 如果属性值为空，则查找具有指定属性名的元素
	// 如果该属性名的属性值不空，则找到了，否则继续查找其它节点
	// 如果属性值不空，则若属性名=属性值，则返回，否则继续查找其它节点
	// 返回空，则查找失败
	TiXmlElement *getElement(TiXmlElement* element,std::string nodeName,std::string attributeName="",std::string attributeValue="");

	// 获取根节点的子节点中指定节点名中的指定属性名=属性值的节点。
	// 如果属性名为空，则不考虑属性的因素，返回当前元素
	// 如果属性值为空，则查找具有指定属性名的元素
	// 如果该属性名的属性值不空，则找到了，否则继续查找其它节点
	// 如果属性值不空，则若属性名=属性值，则返回，否则继续查找其它节点
	// 返回空，则查找失败
	TiXmlElement *getElement(std::string nodeName,std::string attributeName="",std::string attributeValue="");

	// 先根遍历子树，获取指定节点名中的指定属性名=属性值的节点。
	// 如果属性名为空，则不考虑属性的因素，返回当前元素
	// 如果属性值为空，则查找具有指定属性名的元素
	// 如果该属性名的属性值不空，则找到了，否则继续查找其它节点
	// 如果属性值不空，则若属性名=属性值，则返回，否则继续查找其它节点
	// 返回空，则查找失败
	TiXmlElement *getElementInSubtree(TiXmlElement* subRoot,std::string nodeName,std::string attributeName="",std::string attributeValue="");

	// 先根遍历整个树，获取指定节点名中的指定属性名=属性值的节点。
	// 如果属性名为空，则不考虑属性的因素，返回当前元素
	// 如果属性值为空，则查找具有指定属性名的元素
	// 如果该属性名的属性值不空，则找到了，否则继续查找其它节点
	// 如果属性值不空，则若属性名=属性值，则返回，否则继续查找其它节点
	// 返回空，则查找失败
	TiXmlElement *getElementInSubtree(std::string nodeName,std::string attributeName="",std::string attributeValue="");

	// 获取指定节点的文本
	std::string getElementText(TiXmlElement *element);
	// 获取指定节点的指定属性名称的属性值
	std::string getElementAttribute(TiXmlElement *element, std::string propertyName);

	// 设置元素的属性可以使用元素本身的SetAttribute方法。

private:
	TiXmlDocument m_doc;
	TiXmlElement *m_root;
	bool m_isOpen;
};

#endif // !defined(AFX_XMLOPERATION_H__EB0258EF_638E_46E2_8551_6DFF4BB1D6EF__INCLUDED_)
