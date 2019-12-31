// DGConstructor.h: interface for the CDGConstructor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DGCONSTRUCTOR_H__D1724475_9137_4FE6_8BA1_4C774E2FC3A7__INCLUDED_)
#define AFX_DGCONSTRUCTOR_H__D1724475_9137_4FE6_8BA1_4C774E2FC3A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class NodeData, class ArcWeight>
class CDGConstructor  
{
public:
	CDGConstructor(){};
	virtual ~CDGConstructor(){};

	CDiGraphic<NodeData, ArcWeight> *createDG()
	{
		return new CDiGraphic();
	}

	void createNode(CDiGraphic<NodeData, ArcWeight> *graghic)
	{
		CNode *node=new CNode();
		graghic->addNode(node);
		return node;
	}

	CNode<NodeData, ArcWeight> *createNode(CDiGraphic<NodeData, ArcWeight> *graghic, NodeData data)
	{
		CNode *node=new CNode(data);
		graghic->addNode(node);
		return node;
	}

	CArc<NodeData, ArcWeight> *createArc(CDiGraphic<NodeData, ArcWeight> *graghic)
	{
		CArc *arc=new CArc();
		graghic->addArc(arc);
		return arc;
	}

	CArc<NodeData, ArcWeight> *createArc(CDiGraphic<NodeData, ArcWeight> *graghic, ArcWeight weight)
	{
		CArc *arc=new CArc(weight);
		graghic->addArc(arc);
		return arc;
	}
	
	void createArc(CDiGraphic<NodeData, ArcWeight> *graghic, CNode<NodeData, ArcWeight> *nodeStart, CNode<NodeData, ArcWeight> *nodeEnd)
	{
		CArc *arc=new CArc(nodeStart, nodeEnd);
		nodeStart->addArcOut(arc);
		nodeEnd->addArcIn(arc);
		graghic->addArc(arc);
	}
	
	void createArc(CDiGraphic<NodeData, ArcWeight> *graghic, ArcWeight weight, CNode<NodeData, ArcWeight> *nodeStart, CNode<NodeData, ArcWeight> *nodeEnd)
	{
		CArc *arc=new CArc(weight, nodeStart, nodeEnd);
		nodeStart->addArcOut(arc);
		nodeEnd->addArcIn(arc);
		graghic->addArc(arc);
	}
};

#endif // !defined(AFX_DGCONSTRUCTOR_H__D1724475_9137_4FE6_8BA1_4C774E2FC3A7__INCLUDED_)
