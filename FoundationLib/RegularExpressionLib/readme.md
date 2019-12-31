# 正则表达式库

首先有一个基类或称为接口，叫IRegularExpression，有一个accept()方法，用来确定给定的字符是否满足该正则表达式，从而得知自动机的下一个状态是否可以接受。该方法的参数是一个字符。

包含如下正则表达式类：

文件名|说明
----|----
ConcatRegularExpression.h|连接两个正则表达式的正则表达式
DigitRegularExpression.h|表示数字的正则表达式
EmptyRegularExpression.h|表示空的正则表达式
KleenStarRegularExpression.h|表示克林闭包的正则表达式
KleenStartPlusRegularExpression.h|同上，但不允许出现空的正则表达式
LowerRegularExpression.h|表示小写字母正则表达式
NotRegularExpression.h|表示取非的正则表达式
OrRegularExpression.h|表示或的正则表达式
RangeRegularExpression.h|表示类似[a-z]的正则表达式
StringRegularExpression.h|表示多个字符连接的正则表达式
SymbolRegularExpression.h|表示字符的正则表达式
UpperRegularExpression.h|表示大写字母的正则表达式
