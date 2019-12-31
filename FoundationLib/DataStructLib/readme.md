# 数据结构类库

包括如下数据结构：

分类|文件名|说明
----|----|----
.|ValueList.h|值列表模板类，继承自std::vector，模板参数用来表示char,int,float,std::string,CString等直接定义出来、不需要用delete销毁的变量
.|ValueMap.h|值map模板类，继承自std::map，模板参数同上
.|PointerList.h|指针列表模板类，继承自CValueList，模板参数用来表示由new操作符生成的对象指针，该类在析构时可以销毁(delete)列表中的所有对象指针。析构时的销毁操作是可选的，根据实际情况需要（有标志可以设置）可以不销毁
.|PointerMap.h|指针map模板类，继承自CValueMap，模板参数同上
.|PointerStack.h|指针栈模板类，模板参数同上
.|ThreadSafedQue.h|线程安全队列模板类，继承自std::queue，使用生产消费模式
.|StringArrayExt.h|CStringArray类的扩展，以支持CStringArray中元素的排序操作
TreeProj||树
.|TreeNode.h|树节点类
.|DoubleBranchesTreeNode.h|二叉树节点类（不常用）
Graph||图相关类库
.|DiGraphProj/Arc.h|图的边类
.|DiGraphProj/IArcWeight.h|图的边类包含的数据
.|DiGraphProj/Node.h|图的节点类
.|DiGraphProj/INodeData.h|图的节点类包含的数据
.|DiGraphProj/DiGraphic.h|有向图类
.|DiGraphProj/StatusGraphic.h|状态图类，继承自有向图类CDiGraphic
.|DiGraphProj/DGConstructor.h|创建有向图
.|DiGraphProj/RE2SGConverter/RE2SGConverter.h|正则表达式转换成状态图的转换器类
TLVOperation||Tag/Length/Value(TLV)结构数据的操作类，暂时未使用
SelfContainer||自包含数据结构类库。自包含数据结构的概念可以参考<a href='https://blog.csdn.net/yxsylyh/article/details/54613027'>这篇文章</a>。（注：该概念在java 6中无法实现。）
.|SelfTreeNode.h|自包含的树节点类
.|SelfListNode.h|自包含的列表节点类
.|SelfGraphNode.h|自包含的图节点类（准确的说是图节点类包含图边类）
.|SelfGraphArc.h|自包含的图边类（准确的说是图边类包含图节点类）
.|Graph.h|由自包含图节点类或图边类构成的图类
.|MyTreeNode.h|自包含树节点示例
.|MyListNode.h|自包含列表节点示例
