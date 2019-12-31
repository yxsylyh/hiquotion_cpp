// RE2SGConverter.h: interface for the CRE2SGConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RE2SGCONVERTER_H__E8D483D2_5949_487B_A549_573E84F3BA39__INCLUDED_)
#define AFX_RE2SGCONVERTER_H__E8D483D2_5949_487B_A549_573E84F3BA39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\EmptyRegularExpression.h"
#include "..\..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\RangeRegularExpression.h"
#include "..\..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\SymbolRegularExpression.h"
#include "..\..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\ConcatRegularExpression.h"
#include "..\..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\OrRegularExpression.h"
#include "..\..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\KleenStarRegularExpression.h"

template <class NodeData, class ArcWeight>
class CRE2SGConverter  
{
public:
	CRE2SGConverter(){};
	virtual ~CRE2SGConverter(){};

	static CStatusGraphic<NodeData, ArcWeight> *genFromEmptyRE(CEmptyRegularExpression *re);
	static CStatusGraphic<NodeData, ArcWeight> *genFromRangeRE(CRangeRegularExpression *re);
	static CStatusGraphic<NodeData, ArcWeight> *genFromSymbolRE(CSymbolRegularExpression *re);
	static CStatusGraphic<NodeData, ArcWeight> *genFromConcatRE(CConcatRegularExpression *re);
	static CStatusGraphic<NodeData, ArcWeight> *genFromOrRE(COrRegularExpression *re);
	static CStatusGraphic<NodeData, ArcWeight> *genFromKleenStarRE(CKleenStarRegularExpression *re);

	CStatusGraphic *genFromEmptyRE(CEmptyRegularExpression *re)
	{
		if(!re)
			return NULL;

		CStatusGraphic *graphic=new CStatusGraphic();
		CArc *arc=new CArc();  // 权重为空字符的边
		
	// 	graphic->getStartNode()->setArcFirstOut(arc);
	// 	graphic->getEndNode()->setArcFirstIn(arc);

		arc->setNodeStart(graphic->getStartNode());
		arc->setNodeEnd(graphic->getEndNode());
	// 	arc->setNextArcOutFromStart(NULL);
	// 	arc->setNextArcToEnd(NULL);

		return graphic;
	}

	CStatusGraphic *genFromRangeRE(CRangeRegularExpression *re)
	{
		if(!re)
			return NULL;
		
		CStatusGraphic *graphic=new CStatusGraphic();
		CArc *arc=new CArc();  // 权重为字符范围的边，代表多个并联的边
		CArcWeight *weight=new CArcWeight();
		weight->setChecker(re->getChecker());
		arc->setWeight(weight);

		arc->setNodeStart(graphic->getStartNode());
		arc->setNodeEnd(graphic->getEndNode());
	// 	arc->setNextArcOutFromStart(NULL);
	// 	arc->setNextArcToEnd(NULL);
		
		return graphic;
	}

	CStatusGraphic *genFromSymbolRE(CSymbolRegularExpression *re)
	{
		if(!re)
			return NULL;
		
		CStatusGraphic *graphic=new CStatusGraphic();
		CArc *arc=new CArc();  // 权重为单字符的边
		CArcWeight *weight=new CArcWeight();
		weight->setChecker(re->getChecker());
		arc->setWeight(weight);
		
		arc->setNodeStart(graphic->getStartNode());
		arc->setNodeEnd(graphic->getEndNode());
	// 	arc->setNextArcOutFromStart(NULL);
	// 	arc->setNextArcToEnd(NULL);
		
		return graphic;
	}

	CStatusGraphic *genFromConcatRE(CConcatRegularExpression *re)
	{
		if(!re)
			return NULL;

		if(!re->getRegularExpression1() || !re->getRegularExpression2())
			return NULL;
		
		// 新建状态图
		CStatusGraphic *graphic=new CStatusGraphic();

		// 从re中获取两个表达式的状态图
		CStatusGraphic *sg1=re->getRegularExpression1()->genStatusGraphic();
		CStatusGraphic *sg2=re->getRegularExpression2()->genStatusGraphic();

		// 原第一个状态图的开始节点作为新图的开始节点，第二状态图的终点作为新图的终结节点
		graphic->setStartNode(sg1->getStartNode());
		sg1->setStartNodeDestroy(FALSE);
		graphic->setEndNode(sg2->getEndNode());
		sg2->setEndNodeDestroy(FALSE);

		// 将两个状态图中的节点和边，添加到新建的状态图 graphic 中
		graphic->addNodes(sg1->getNodes());
		sg1->setNodesDestroy(FALSE);  // gStart 类销毁时，不销毁其内部的节点列表，因为这些节点已经转移到 graphic 图中了（下同）
		graphic->addNode(sg1->getEndNode());
		sg1->setEndNodeDestroy(FALSE);
		graphic->addArcs(sg1->getArcs());
		sg1->setArcsDestroy(FALSE);

		graphic->addNodes(sg2->getNodes());
		sg2->setNodesDestroy(FALSE);
		graphic->addNode(sg2->getStartNode());
		sg2->setStartNodeDestroy(FALSE);
		graphic->addArcs(sg2->getArcs());
		sg2->setArcsDestroy(FALSE);

		// 连接第一个状态图的终结节点与第二个状态图的开始点的有向边
		CArc *arc=new CArc();  // 权重为空字符的边
		arc->setNodeStart(sg1->getEndNode());
		arc->setNodeEnd(sg2->getStartNode());
	// 	arc->setNextArcOutFromStart(NULL);
	// 	arc->setNextArcToEnd(NULL);
		
		// 给第一个状态图的终结节点添加出边
		CNode *node=sg1->getEndNode();
		if(node)
			node->addArcOut(arc);
		// 给第二个状态图的开始节点添加入边
		node=sg2->getStartNode();
		if(node)
			node->addArcIn(arc);

		// 释放原状态图内存
		delete sg1;
		delete sg2;
		
		return graphic;
	}

	CStatusGraphic *genFromOrRE(COrRegularExpression *re)
	{
		if(!re)
			return NULL;
		
		if(!re->getRegularExpression1() || !re->getRegularExpression2())
			return NULL;
		
		// 新建状态图
		CStatusGraphic *graphic=new CStatusGraphic();
		
		// 从re中获取两个表达式的状态图
		CStatusGraphic *sg1=re->getRegularExpression1()->genStatusGraphic();
		CStatusGraphic *sg2=re->getRegularExpression2()->genStatusGraphic();

		// 将原两个状态图的节点和边添加到新状态图中
		// 并设置原两个状态图的节点和边不被销毁
		graphic->addNode(sg1->getStartNode());
		graphic->addNodes(sg1->getNodes());
		graphic->addNode(sg1->getEndNode());

		sg1->setNodesDestroy(FALSE);
		sg1->setStartNodeDestroy(FALSE);
		sg1->setEndNodeDestroy(FALSE);

		graphic->addNode(sg2->getStartNode());
		graphic->addNodes(sg2->getNodes());
		graphic->addNode(sg2->getEndNode());

		sg2->setNodesDestroy(FALSE);
		sg2->setStartNodeDestroy(FALSE);
		sg2->setEndNodeDestroy(FALSE);
		
		graphic->addArcs(sg1->getArcs());
		graphic->addArcs(sg2->getArcs());

		sg1->setArcsDestroy(FALSE);
		sg2->setArcsDestroy(FALSE);

		// 从新状态图的起始节点划出两个边分别到两个正则表达式生成状态图的开始节点
		CArc *arcToG1=new CArc();
		CArc *arcToG2=new CArc();
		
		arcToG1->setNodeStart(graphic->getStartNode());
		arcToG1->setNodeEnd(sg1->getStartNode());
		CNode *node=graphic->getStartNode();
		if(node)
			node->addArcOut(arcToG1);
		node=sg1->getStartNode();
		if(node)
			node->addArcIn(arcToG1);

		arcToG2->setNodeStart(graphic->getStartNode());
		arcToG2->setNodeEnd(sg2->getStartNode());
		node=graphic->getStartNode();
		if(node)
			node->addArcOut(arcToG2);
		node=sg2->getStartNode();
		if(node)
			node->addArcIn(arcToG2);

		graphic->addArc(arcToG1);
		graphic->addArc(arcToG2);

		// 从原状态图的两个终止节点划出两个边，到新状态图的终止节点
		CArc *arcFromG1=new CArc();
		CArc *arcFromG2=new CArc();

		arcFromG1->setNodeStart(sg1->getEndNode());
		arcFromG1->setNodeEnd(graphic->getEndNode());
		node=sg1->getEndNode();
		if(node)
			node->addArcOut(arcFromG1);
		node=graphic->getEndNode();
		if(node)
			node->addArcIn(arcFromG1);

		arcFromG2->setNodeStart(sg2->getEndNode());
		arcFromG2->setNodeEnd(graphic->getEndNode());
		node=sg2->getEndNode();
		if(node)
			node->addArcOut(arcFromG2);
		node=graphic->getEndNode();
		if(node)
			node->addArcIn(arcFromG2);

		graphic->addArc(arcFromG1);
		graphic->addArc(arcFromG2);

		// 释放原状态图内存
		delete sg1;
		delete sg2;
		
		return graphic;
	}

	CStatusGraphic *genFromKleenStarRE(CKleenStarRegularExpression *re)
	{
		CStatusGraphic *graphic=new CStatusGraphic();

		CStatusGraphic *sg=re->genStatusGraphic();

		// 添加原状态图的节点和边到新状态图中
		// 并设置原状态图的节点和边不被销毁
		graphic->addNode(sg->getStartNode());
		graphic->addNodes(sg->getNodes());
		graphic->addNode(sg->getEndNode());

		sg->setStartNodeDestroy(FALSE);
		sg->setNodesDestroy(FALSE);
		sg->setEndNodeDestroy(FALSE);

		graphic->addArcs(sg->getArcs());
		sg->setArcsDestroy(FALSE);

		// 连接新状态图的开始节点和原状态图的开始节点，有一条epsilon的边
		CArc *arcStart=new CArc();
		arcStart->setNodeStart(graphic->getStartNode());
		arcStart->setNodeEnd(sg->getStartNode());
		CNode *node=graphic->getStartNode();
		if(node)
			node->addArcOut(arcStart);
		node=sg->getStartNode();
		if(node)
			node->addArcIn(arcStart);

		graphic->addArc(arcStart);

		// 连接原状态图的终止节点和新状态图的终止节点，有一条epsilon的边
		CArc *arcEnd=new CArc();
		arcEnd->setNodeStart(sg->getEndNode());
		arcEnd->setNodeEnd(graphic->getEndNode());
		node=sg->getEndNode();
		if(node)
			node->addArcOut(arcEnd);
		node=graphic->getEndNode();
		if(node)
			node->addArcIn(arcEnd);

		graphic->addArc(arcEnd);

		// 连接新状态图的开始和终止节点，有一条epsilon的边
		CArc *arc=new CArc();
		arc->setNodeStart(graphic->getStartNode());
		arc->setNodeEnd(graphic->getEndNode());
		node=graphic->getStartNode();
		if(node)
			node->addArcOut(arc);
		node=graphic->getEndNode();
		if(node)
			node->addArcIn(arc);

		// 连接新状态图的终止节点和原状态图的开始节点，有一条边，需要设置权重
		CArc *arc2=new CArc();
		arc2->setNodeStart(graphic->getEndNode());
		arc2->setNodeEnd(sg->getStartNode());
		node=graphic->getEndNode();
		if(node)
			node->addArcOut(arc2);
		node=sg->getStartNode();
		if(node)
			node->addArcIn(arc2);

		CArcWeight *weight=new CArcWeight();
		weight->setChecker(re->getChecker());

		arc2->setWeight(weight);

		graphic->addArc(arc2);

		// 最后销毁原状态图所占内存
		delete sg;
		
		return graphic;
	}
};

#endif // !defined(AFX_RE2SGCONVERTER_H__E8D483D2_5949_487B_A549_573E84F3BA39__INCLUDED_)
