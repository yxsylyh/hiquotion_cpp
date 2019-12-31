// KernelLexStatusGraphBuilder.cpp: implementation of the CKernelLexStatusGraphBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KernelLexStatusGraphBuilder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKernelLexStatusGraphBuilder::CKernelLexStatusGraphBuilder()
: m_isBuilt(FALSE),

dot('.'), zero('0'), x('x'), X('X'), range19('1', '9'), rangeaf('a', 'f'), rangeAF('A', 'F'),
xX(&x, &X), afAF(&rangeaf, &rangeAF), hex(&afAF, &number),
underline('_'), rangeaz('a', 'z'), rangeAZ('A', 'Z'),
az_AZ(&rangeaz, &rangeAZ), digit_az_AZ(&number, &az_AZ),
underline_az_AZ(&underline, &az_AZ), underline_digit_az_AZ(&underline, &digit_az_AZ),

// `~!@#$%^&*()-=+[]{}\|;:'",.<>/?

s1('`'), s2('~'), s3('!'), s4('@'), s5('#'), s6('$'), s7('%'), s8('^'), s9('&'), s10('*'),
s11('('), s12(')'), s13('-'), s14('='), s15('+'), s16('['), s17(']'), s18('{'), s19('}'), s20('\\'),
s21('|'), s22(';'), s23(':'), s24('\''), s25('"'), s26(','), s27('.'), s28('<'), s29('>'), s30('/'),
s31('?'), s32(' '), s33('\t'), s34('\r'), s35('\n'),

sCR('\r'), sLF('\n'),
notCR(&sCR), notLF(&sLF), CRLF(&sCR, &sLF), notCRLF(&CRLF),
notStar(&s10), notGang(&s30)
{
	m_graph=new CLexStatusGraph();
}

CKernelLexStatusGraphBuilder::~CKernelLexStatusGraphBuilder()
{
	delete m_graph;
}

BOOL CKernelLexStatusGraphBuilder::build()
{
	if(m_isBuilt)
		return TRUE;

	// 开始结点

	CStatusGraphNode *m_startNode=new CStatusGraphNode();
	m_graph->addNode(m_startNode);
	m_graph->setStartNode(m_startNode);

	// 构造数字

	// 6 个结点
	CStatusGraphNode *node1=new CStatusGraphNode(TRUE, "number", "integer");
	CStatusGraphNode *node2=new CStatusGraphNode(TRUE, "number", "integer");
	CStatusGraphNode *node3=new CStatusGraphNode("十六进制数字不合法！\"0x\" 后面缺少数字！");
	CStatusGraphNode *node4=new CStatusGraphNode(TRUE, "number", "hex");
	CStatusGraphNode *node5=new CStatusGraphNode("\".\" 不合法！");
	CStatusGraphNode *node6=new CStatusGraphNode(TRUE, "number", "double");
	
	// 将结点添加到图
	m_graph->addNode(node1);
	m_graph->addNode(node2);
	m_graph->addNode(node3);
	m_graph->addNode(node4);
	m_graph->addNode(node5);
	m_graph->addNode(node6);
	
	// 12 条弧（去掉了第一条弧，该弧表示“.”，与字符串中的“.”有冲突）
// 	CArc *arc1=new CArc(m_graph->getStartNode(), node5, &dot);
	CStatusGraphArc *arc2=new CStatusGraphArc(m_graph->getStartNode(), node1, &range19);
	CStatusGraphArc *arc3=new CStatusGraphArc(m_graph->getStartNode(), node2, &zero);
	CStatusGraphArc *arc4=new CStatusGraphArc(node2, node5, &dot);
	CStatusGraphArc *arc5=new CStatusGraphArc(node2, node1, &number);
	CStatusGraphArc *arc6=new CStatusGraphArc(node1, node1, &number);
	CStatusGraphArc *arc7=new CStatusGraphArc(node1, node5, &dot);
	CStatusGraphArc *arc8=new CStatusGraphArc(node5, node6, &number);
	CStatusGraphArc *arc9=new CStatusGraphArc(node6, node6, &number);
	CStatusGraphArc *arc10=new CStatusGraphArc(node2, node3, &xX);
	CStatusGraphArc *arc11=new CStatusGraphArc(node3, node4, &hex);
	CStatusGraphArc *arc12=new CStatusGraphArc(node4, node4, &hex);
	
	// 将弧添加到图
// 	m_graph->addArc(arc1);
	m_graph->addArc(arc2);
	m_graph->addArc(arc3);
	m_graph->addArc(arc4);
	m_graph->addArc(arc5);
	m_graph->addArc(arc6);
	m_graph->addArc(arc7);
	m_graph->addArc(arc8);
	m_graph->addArc(arc9);
	m_graph->addArc(arc10);
	m_graph->addArc(arc11);
	m_graph->addArc(arc12);


	// 构造标识符

	// 注：这个 “id”是指标识符或关键字，结点内部并未区分，需要外部根据关键字列表来区分是关键字还是标识符
	CStatusGraphNode *symbolNode=new CStatusGraphNode(TRUE, "id");
	symbolNode->setFinal(TRUE);

	m_graph->addNode(symbolNode);

	CStatusGraphArc *symArc1=new CStatusGraphArc(m_graph->getStartNode(), symbolNode, &underline_az_AZ);
	CStatusGraphArc *symArc2=new CStatusGraphArc(symbolNode, symbolNode, &underline_digit_az_AZ);

	m_graph->addArc(symArc1);
	m_graph->addArc(symArc2);


	// 构造其他可打印字符
	// `~!@#$%^&*()-=+[]{}\|;:'",.<>/?
	// （不包括下划线“_”）
	CStatusGraphNode *n1=new CStatusGraphNode(TRUE, "`");
	CStatusGraphNode *n2=new CStatusGraphNode(TRUE, "~");
	CStatusGraphNode *n3=new CStatusGraphNode(TRUE, "!");
	CStatusGraphNode *n4=new CStatusGraphNode(TRUE, "@");
	CStatusGraphNode *n5=new CStatusGraphNode(TRUE, "#");
	CStatusGraphNode *n6=new CStatusGraphNode(TRUE, "$");
	CStatusGraphNode *n7=new CStatusGraphNode(TRUE, "%");
	CStatusGraphNode *n8=new CStatusGraphNode(TRUE, "^");
	CStatusGraphNode *n9=new CStatusGraphNode(TRUE, "&");
	CStatusGraphNode *n10=new CStatusGraphNode(TRUE, "*");
	CStatusGraphNode *n11=new CStatusGraphNode(TRUE, "(");
	CStatusGraphNode *n12=new CStatusGraphNode(TRUE, ")");
	CStatusGraphNode *n13=new CStatusGraphNode(TRUE, "-");
	CStatusGraphNode *n14=new CStatusGraphNode(TRUE, "=");
	CStatusGraphNode *n15=new CStatusGraphNode(TRUE, "+");
	CStatusGraphNode *n16=new CStatusGraphNode(TRUE, "[");
	CStatusGraphNode *n17=new CStatusGraphNode(TRUE, "]");
	CStatusGraphNode *n18=new CStatusGraphNode(TRUE, "{");
	CStatusGraphNode *n19=new CStatusGraphNode(TRUE, "}");
	CStatusGraphNode *n20=new CStatusGraphNode(TRUE, "\\");
	CStatusGraphNode *n21=new CStatusGraphNode(TRUE, "|");
	CStatusGraphNode *n22=new CStatusGraphNode(TRUE, ";");
	CStatusGraphNode *n23=new CStatusGraphNode(TRUE, ":");
	CStatusGraphNode *n24=new CStatusGraphNode(TRUE, "'");
	CStatusGraphNode *n25=new CStatusGraphNode(TRUE, "\"");
	CStatusGraphNode *n26=new CStatusGraphNode(TRUE, ",");
	CStatusGraphNode *n27=new CStatusGraphNode(TRUE, ".");
	CStatusGraphNode *n28=new CStatusGraphNode(TRUE, "<");
	CStatusGraphNode *n29=new CStatusGraphNode(TRUE, ">");
	CStatusGraphNode *n30=new CStatusGraphNode(TRUE, "/");
	CStatusGraphNode *n31=new CStatusGraphNode(TRUE, "?");
	CStatusGraphNode *n32=new CStatusGraphNode(TRUE, "space");
	CStatusGraphNode *n33=new CStatusGraphNode(TRUE, "\\t");
	CStatusGraphNode *n34=new CStatusGraphNode(TRUE, "\\r");
	CStatusGraphNode *n35=new CStatusGraphNode(TRUE, "\\n");

	CStatusGraphNode *n3d1=new CStatusGraphNode(TRUE, "!=");
	CStatusGraphNode *n7d1=new CStatusGraphNode(TRUE, "%=");
	CStatusGraphNode *n9d1=new CStatusGraphNode(TRUE, "&&");
	CStatusGraphNode *n9d2=new CStatusGraphNode(TRUE, "&=");
	CStatusGraphNode *n10d1=new CStatusGraphNode(TRUE, "*=");
// 	CNode *n10d2=new CNode(TRUE, "*/");
	CStatusGraphNode *n13d1=new CStatusGraphNode(TRUE, "--");
	CStatusGraphNode *n13d2=new CStatusGraphNode(TRUE, "-=");
	CStatusGraphNode *n13d3=new CStatusGraphNode(TRUE, "->");
	CStatusGraphNode *n14d1=new CStatusGraphNode(TRUE, "==");
	CStatusGraphNode *n15d1=new CStatusGraphNode(TRUE, "++");
	CStatusGraphNode *n15d2=new CStatusGraphNode(TRUE, "+=");
	CStatusGraphNode *n20d1=new CStatusGraphNode(TRUE, "\\\\");  // \ 的转义字符表示
	CStatusGraphNode *n20d2=new CStatusGraphNode(TRUE, "alt_meaning");  // 转义字符（即 \t,\r,\n 等等）
	CStatusGraphNode *n20d3=new CStatusGraphNode(TRUE, "\\=");
	CStatusGraphNode *n21d1=new CStatusGraphNode(TRUE, "||");
	CStatusGraphNode *n21d2=new CStatusGraphNode(TRUE, "|=");
	CStatusGraphNode *n23d1=new CStatusGraphNode(TRUE, "::");
	CStatusGraphNode *n27d1=new CStatusGraphNode("\"..\" invalid!");
	CStatusGraphNode *n27d1t1=new CStatusGraphNode(TRUE, "...");
	CStatusGraphNode *n28d1=new CStatusGraphNode(TRUE, "<<");
	CStatusGraphNode *n28d2=new CStatusGraphNode(TRUE, "<=");
	CStatusGraphNode *n28d3=new CStatusGraphNode(TRUE, "<-");
	CStatusGraphNode *n29d1=new CStatusGraphNode(TRUE, ">>");
	CStatusGraphNode *n29d2=new CStatusGraphNode(TRUE, ">=");
	CStatusGraphNode *n30d1=new CStatusGraphNode(TRUE, "/=");
	CStatusGraphNode *n30d2=new CStatusGraphNode(TRUE, "//");
	CStatusGraphNode *n30d2t1=new CStatusGraphNode(""); // 行注释内容
	CStatusGraphNode *n30d2t1f1=new CStatusGraphNode(TRUE, "comment", "line");  // 行注释结束符
	CStatusGraphNode *n30d3=new CStatusGraphNode(TRUE, "/*");
	CStatusGraphNode *n30d3t1=new CStatusGraphNode("");  // 块注释内容
	CStatusGraphNode *n30d3t1f1=new CStatusGraphNode(""); // 块注释内容
	CStatusGraphNode *n30d3t1f1f1=new CStatusGraphNode(TRUE, "comment", "block"); // 块注释结束符

	m_graph->addNode(n1);
	m_graph->addNode(n2);
	m_graph->addNode(n3);
	m_graph->addNode(n4);
	m_graph->addNode(n5);
	m_graph->addNode(n6);
	m_graph->addNode(n7);
	m_graph->addNode(n8);
	m_graph->addNode(n9);
	m_graph->addNode(n10);
	m_graph->addNode(n11);
	m_graph->addNode(n12);
	m_graph->addNode(n13);
	m_graph->addNode(n14);
	m_graph->addNode(n15);
	m_graph->addNode(n16);
	m_graph->addNode(n17);
	m_graph->addNode(n18);
	m_graph->addNode(n19);
	m_graph->addNode(n20);
	m_graph->addNode(n21);
	m_graph->addNode(n22);
	m_graph->addNode(n23);
	m_graph->addNode(n24);
	m_graph->addNode(n25);
	m_graph->addNode(n26);
	m_graph->addNode(n27);
	m_graph->addNode(n28);
	m_graph->addNode(n29);
	m_graph->addNode(n30);
	m_graph->addNode(n31);
	m_graph->addNode(n32);
	m_graph->addNode(n33);
	m_graph->addNode(n34);
	m_graph->addNode(n35);

	m_graph->addNode(n3d1);
	m_graph->addNode(n7d1);
	m_graph->addNode(n9d1);
	m_graph->addNode(n9d2);
	m_graph->addNode(n10d1);
// 	m_graph->addNode(n10d2);
	m_graph->addNode(n13d1);
	m_graph->addNode(n13d2);
	m_graph->addNode(n13d3);
	m_graph->addNode(n14d1);
	m_graph->addNode(n15d1);
	m_graph->addNode(n15d2);
	m_graph->addNode(n20d1);
	m_graph->addNode(n20d2);
	m_graph->addNode(n20d3);
	m_graph->addNode(n21d1);
	m_graph->addNode(n21d2);
	m_graph->addNode(n23d1);
	m_graph->addNode(n27d1);
	m_graph->addNode(n27d1t1);
	m_graph->addNode(n28d1);
	m_graph->addNode(n28d2);
	m_graph->addNode(n28d3);
	m_graph->addNode(n29d1);
	m_graph->addNode(n29d2);
	m_graph->addNode(n30d1);
	m_graph->addNode(n30d2);
	m_graph->addNode(n30d2t1);
	m_graph->addNode(n30d2t1f1);
	m_graph->addNode(n30d3);
	m_graph->addNode(n30d3t1);
	m_graph->addNode(n30d3t1f1);
	m_graph->addNode(n30d3t1f1f1);

	CStatusGraphArc *a1=new CStatusGraphArc(m_graph->getStartNode(), n1, &s1);
	CStatusGraphArc *a2=new CStatusGraphArc(m_graph->getStartNode(), n2, &s2);
	CStatusGraphArc *a3=new CStatusGraphArc(m_graph->getStartNode(), n3, &s3);
	CStatusGraphArc *a4=new CStatusGraphArc(m_graph->getStartNode(), n4, &s4);
	CStatusGraphArc *a5=new CStatusGraphArc(m_graph->getStartNode(), n5, &s5);
	CStatusGraphArc *a6=new CStatusGraphArc(m_graph->getStartNode(), n6, &s6);
	CStatusGraphArc *a7=new CStatusGraphArc(m_graph->getStartNode(), n7, &s7);
	CStatusGraphArc *a8=new CStatusGraphArc(m_graph->getStartNode(), n8, &s8);
	CStatusGraphArc *a9=new CStatusGraphArc(m_graph->getStartNode(), n9, &s9);
	CStatusGraphArc *a10=new CStatusGraphArc(m_graph->getStartNode(), n10, &s10);
	CStatusGraphArc *a11=new CStatusGraphArc(m_graph->getStartNode(), n11, &s11);
	CStatusGraphArc *a12=new CStatusGraphArc(m_graph->getStartNode(), n12, &s12);
	CStatusGraphArc *a13=new CStatusGraphArc(m_graph->getStartNode(), n13, &s13);
	CStatusGraphArc *a14=new CStatusGraphArc(m_graph->getStartNode(), n14, &s14);
	CStatusGraphArc *a15=new CStatusGraphArc(m_graph->getStartNode(), n15, &s15);
	CStatusGraphArc *a16=new CStatusGraphArc(m_graph->getStartNode(), n16, &s16);
	CStatusGraphArc *a17=new CStatusGraphArc(m_graph->getStartNode(), n17, &s17);
	CStatusGraphArc *a18=new CStatusGraphArc(m_graph->getStartNode(), n18, &s18);
	CStatusGraphArc *a19=new CStatusGraphArc(m_graph->getStartNode(), n19, &s19);
	CStatusGraphArc *a20=new CStatusGraphArc(m_graph->getStartNode(), n20, &s20);
	CStatusGraphArc *a21=new CStatusGraphArc(m_graph->getStartNode(), n21, &s21);
	CStatusGraphArc *a22=new CStatusGraphArc(m_graph->getStartNode(), n22, &s22);
	CStatusGraphArc *a23=new CStatusGraphArc(m_graph->getStartNode(), n23, &s23);
	CStatusGraphArc *a24=new CStatusGraphArc(m_graph->getStartNode(), n24, &s24);
	CStatusGraphArc *a25=new CStatusGraphArc(m_graph->getStartNode(), n25, &s25);
	CStatusGraphArc *a26=new CStatusGraphArc(m_graph->getStartNode(), n26, &s26);
	CStatusGraphArc *a27=new CStatusGraphArc(m_graph->getStartNode(), n27, &s27);
	CStatusGraphArc *a28=new CStatusGraphArc(m_graph->getStartNode(), n28, &s28);
	CStatusGraphArc *a29=new CStatusGraphArc(m_graph->getStartNode(), n29, &s29);
	CStatusGraphArc *a30=new CStatusGraphArc(m_graph->getStartNode(), n30, &s30);
	CStatusGraphArc *a31=new CStatusGraphArc(m_graph->getStartNode(), n31, &s31);
	CStatusGraphArc *a32=new CStatusGraphArc(m_graph->getStartNode(), n32, &s32);
	CStatusGraphArc *a33=new CStatusGraphArc(m_graph->getStartNode(), n33, &s33);
	CStatusGraphArc *a34=new CStatusGraphArc(m_graph->getStartNode(), n34, &s34);
	CStatusGraphArc *a35=new CStatusGraphArc(m_graph->getStartNode(), n35, &s35);

// s
//  1 `
// 	2 ~
// 	3 !
// 	4 @
// 	5 #
// 	6 $
// 	7 %
// 	8 ^
// 	9 &
// 	10 *
// 	11 (
// 	12 )
// 	13 -
// 	14 =
// 	15 +
// 	16 [
// 	17 ]
// 	18 {
// 	19 }
// 	20 "\"
// 	21 |
// 	22 ;
// 	23 :
// 	24 '
// 	25 "
// 	26 ,
// 	27 .
// 	28 <
// 	29 >
// 	30 /
// 	31 ?
//  32 space
//  33 \t
//  34 \r
//  35 \n

	CStatusGraphArc *arc_n3d1=new CStatusGraphArc(n3, n3d1, &s14);  // =
	CStatusGraphArc *arc_n7d1=new CStatusGraphArc(n7, n7d1, &s14);
	CStatusGraphArc *arc_n9d1=new CStatusGraphArc(n9, n9d1, &s9);   // &
	CStatusGraphArc *arc_n9d2=new CStatusGraphArc(n9, n9d2, &s14);
	CStatusGraphArc *arc_n10d1=new CStatusGraphArc(n10, n10d1, &s14);
// 	CArc *arc_n10d2=new CArc(n10, n10d2, &s30);  // /
	CStatusGraphArc *arc_n13d1=new CStatusGraphArc(n13, n13d1, &s13);  // -
	CStatusGraphArc *arc_n13d2=new CStatusGraphArc(n13, n13d2, &s14);
	CStatusGraphArc *arc_n13d3=new CStatusGraphArc(n13, n13d3, &s29);  // >
	CStatusGraphArc *arc_n14d1=new CStatusGraphArc(n14, n14d1, &s14);
	CStatusGraphArc *arc_n15d1=new CStatusGraphArc(n15, n15d1, &s15);  // +
	CStatusGraphArc *arc_n15d2=new CStatusGraphArc(n15, n15d2, &s14);
	CStatusGraphArc *arc_n20d1=new CStatusGraphArc(n20, n20d1, &s20);  // "\"
	CStatusGraphArc *arc_n20d2=new CStatusGraphArc(n20, n20d2, &rangeaz);
	CStatusGraphArc *arc_n20d3=new CStatusGraphArc(n20, n20d3, &s14);
	CStatusGraphArc *arc_n21d1=new CStatusGraphArc(n21, n21d1, &s21);  // |
	CStatusGraphArc *arc_n21d2=new CStatusGraphArc(n21, n21d2, &s14);
	CStatusGraphArc *arc_n23d1=new CStatusGraphArc(n23, n23d1, &s23);  // :
	CStatusGraphArc *arc_n27d1=new CStatusGraphArc(n27, n27d1, &s27);  // .
	CStatusGraphArc *arc_n27d1t1=new CStatusGraphArc(n27d1, n27d1t1, &s27);
	CStatusGraphArc *arc_n28d1=new CStatusGraphArc(n28, n28d1, &s28);  // <
	CStatusGraphArc *arc_n28d2=new CStatusGraphArc(n28, n28d2, &s14);
	CStatusGraphArc *arc_n28d3=new CStatusGraphArc(n28, n28d3, &s13);  // -
	CStatusGraphArc *arc_n29d1=new CStatusGraphArc(n29, n29d1, &s29);  // >
	CStatusGraphArc *arc_n29d2=new CStatusGraphArc(n29, n29d2, &s14);
	CStatusGraphArc *arc_n30d1=new CStatusGraphArc(n30, n30d1, &s14);
	CStatusGraphArc *arc_n30d2=new CStatusGraphArc(n30, n30d2, &s30);  // /
	CStatusGraphArc *arc_n30d2t1=new CStatusGraphArc(n30d2, n30d2t1, &notCRLF);
	CStatusGraphArc *arc_n30d2t1t1=new CStatusGraphArc(n30d2t1, n30d2t1, &notCRLF);
	CStatusGraphArc *arc_n30d2t1f1=new CStatusGraphArc(n30d2t1, n30d2t1f1, &CRLF);
	CStatusGraphArc *arc_n30d3=new CStatusGraphArc(n30, n30d3, &s10);  // *
	CStatusGraphArc *arc_n30d3t1=new CStatusGraphArc(n30d3, n30d3t1, &notStar);
	CStatusGraphArc *arc_n30d3t1t1=new CStatusGraphArc(n30d3t1, n30d3t1, &notStar);
	CStatusGraphArc *arc_n30d3t1f1=new CStatusGraphArc(n30d3t1, n30d3t1f1, &s10);  // *
	CStatusGraphArc *arc_n30d3f1t1=new CStatusGraphArc(n30d3t1f1, n30d3t1, &notGang);
	CStatusGraphArc *arc_n30d3t1f1f1=new CStatusGraphArc(n30d3t1f1, n30d3t1f1f1, &s30);

	m_graph->addArc(a1);
	m_graph->addArc(a2);
	m_graph->addArc(a3);
	m_graph->addArc(a4);
	m_graph->addArc(a5);
	m_graph->addArc(a6);
	m_graph->addArc(a7);
	m_graph->addArc(a8);
	m_graph->addArc(a9);
	m_graph->addArc(a10);
	m_graph->addArc(a11);
	m_graph->addArc(a12);
	m_graph->addArc(a13);
	m_graph->addArc(a14);
	m_graph->addArc(a15);
	m_graph->addArc(a16);
	m_graph->addArc(a17);
	m_graph->addArc(a18);
	m_graph->addArc(a19);
	m_graph->addArc(a20);
	m_graph->addArc(a21);
	m_graph->addArc(a22);
	m_graph->addArc(a23);
	m_graph->addArc(a24);
	m_graph->addArc(a25);
	m_graph->addArc(a26);
	m_graph->addArc(a27);
	m_graph->addArc(a28);
	m_graph->addArc(a29);
	m_graph->addArc(a30);
	m_graph->addArc(a31);
	m_graph->addArc(a32);
	m_graph->addArc(a33);
	m_graph->addArc(a34);
	m_graph->addArc(a35);

	m_graph->addArc(arc_n3d1);
	m_graph->addArc(arc_n7d1);
	m_graph->addArc(arc_n9d1);
	m_graph->addArc(arc_n9d2);
	m_graph->addArc(arc_n10d1);
// 	m_graph->addArc(arc_n10d2);
	m_graph->addArc(arc_n13d1);
	m_graph->addArc(arc_n13d2);
	m_graph->addArc(arc_n13d3);
	m_graph->addArc(arc_n14d1);
	m_graph->addArc(arc_n15d1);
	m_graph->addArc(arc_n15d2);
	m_graph->addArc(arc_n20d1);
	m_graph->addArc(arc_n20d2);
	m_graph->addArc(arc_n20d3);
	m_graph->addArc(arc_n21d1);
	m_graph->addArc(arc_n21d2);
	m_graph->addArc(arc_n23d1);
	m_graph->addArc(arc_n27d1);
	m_graph->addArc(arc_n27d1t1);
	m_graph->addArc(arc_n28d1);
	m_graph->addArc(arc_n28d2);
	m_graph->addArc(arc_n28d3);
	m_graph->addArc(arc_n29d1);
	m_graph->addArc(arc_n29d2);
	m_graph->addArc(arc_n30d1);
	m_graph->addArc(arc_n30d2);
	m_graph->addArc(arc_n30d2t1);
	m_graph->addArc(arc_n30d2t1t1);
	m_graph->addArc(arc_n30d2t1f1);
	m_graph->addArc(arc_n30d3);
	m_graph->addArc(arc_n30d3t1);
	m_graph->addArc(arc_n30d3t1t1);
	m_graph->addArc(arc_n30d3t1f1);
	m_graph->addArc(arc_n30d3f1t1);
	m_graph->addArc(arc_n30d3t1f1f1);

	m_graph->genRelationship(a1);
	m_graph->genRelationship(a2);
	m_graph->genRelationship(a3);
	m_graph->genRelationship(a4);
	m_graph->genRelationship(a5);
	m_graph->genRelationship(a6);
	m_graph->genRelationship(a7);
	m_graph->genRelationship(a8);
	m_graph->genRelationship(a9);
	m_graph->genRelationship(a10);
	m_graph->genRelationship(a11);
	m_graph->genRelationship(a12);
	m_graph->genRelationship(a13);
	m_graph->genRelationship(a14);
	m_graph->genRelationship(a15);
	m_graph->genRelationship(a16);
	m_graph->genRelationship(a17);
	m_graph->genRelationship(a18);
	m_graph->genRelationship(a19);
	m_graph->genRelationship(a20);
	m_graph->genRelationship(a21);
	m_graph->genRelationship(a22);
	m_graph->genRelationship(a23);
	m_graph->genRelationship(a24);
	m_graph->genRelationship(a25);
	m_graph->genRelationship(a26);
	m_graph->genRelationship(a27);
	m_graph->genRelationship(a28);
	m_graph->genRelationship(a29);
	m_graph->genRelationship(a30);
	m_graph->genRelationship(a31);
	m_graph->genRelationship(a32);
	m_graph->genRelationship(a33);
	m_graph->genRelationship(a34);
	m_graph->genRelationship(a35);
	
	m_graph->genRelationship(arc_n3d1);
	m_graph->genRelationship(arc_n7d1);
	m_graph->genRelationship(arc_n9d1);
	m_graph->genRelationship(arc_n9d2);
	m_graph->genRelationship(arc_n10d1);
// 	m_graph->genRelationship(arc_n10d2);
	m_graph->genRelationship(arc_n13d1);
	m_graph->genRelationship(arc_n13d2);
	m_graph->genRelationship(arc_n13d3);
	m_graph->genRelationship(arc_n14d1);
	m_graph->genRelationship(arc_n15d1);
	m_graph->genRelationship(arc_n15d2);
	m_graph->genRelationship(arc_n20d1);
	m_graph->genRelationship(arc_n20d2);
	m_graph->genRelationship(arc_n20d3);
	m_graph->genRelationship(arc_n21d1);
	m_graph->genRelationship(arc_n21d2);
	m_graph->genRelationship(arc_n23d1);
	m_graph->genRelationship(arc_n27d1);
	m_graph->genRelationship(arc_n27d1t1);
	m_graph->genRelationship(arc_n28d1);
	m_graph->genRelationship(arc_n28d2);
	m_graph->genRelationship(arc_n29d1);
	m_graph->genRelationship(arc_n29d2);
	m_graph->genRelationship(arc_n30d1);
	m_graph->genRelationship(arc_n30d2);
	m_graph->genRelationship(arc_n30d2t1);
	m_graph->genRelationship(arc_n30d2t1t1);
	m_graph->genRelationship(arc_n30d3);
	m_graph->genRelationship(arc_n30d3t1);
	m_graph->genRelationship(arc_n30d3t1t1);
	m_graph->genRelationship(arc_n30d3t1f1);
	m_graph->genRelationship(arc_n30d3f1t1);
	m_graph->genRelationship(arc_n30d3t1f1f1);

	m_isBuilt=TRUE;

	return TRUE;
}
