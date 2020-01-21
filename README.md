# 说明
这是我这些年来使用 c/c++ 开发时积攒的代码库，有第三方的，有自行开发的。主要是 Windows 平台，多数基于MFC。<p/>
现在开源出来，希望能够给 c/c++ 开发者带来一些便利。<p/>
由于个人所用，错漏之处在所难免，适用范围也仅限于个人工作环境，可能不能适合所有操作系统平台以及任何场景。<p/>
欢迎提交对源码的修改，如果适合，会合并到 master 分支中（不建议新建分支）<p/>
对源码的修改尽量集中在以下内容：修正、修复源码的错漏，完善源码的既有功能、鲁棒性，使源码支持跨平台。如果您只是修改代码后适应您的工作场景，那么不建议提交代码修改，您个人用着方便即可。<p/>
类库中各个类的说明文档将逐渐添加，帮助开发者熟悉类库中的每个类，并且最终可以将类库中的代码应用到自己的项目中。<p/>

# 代码说明

目录|说明
---|---
FoundationLib|基础类库
AdvancedLib|本人认为比较高级的类库
Application|已经实现的应用
Hardware/card|硬件方面
3rdParty|第三方类库

# FoundationLib 代码分类说明

目录|说明
---|---
<a href='https://github.com/yxsylyh/hiquotion_cpp/blob/master/FoundationLib/BarCodeLib'>BarCodeLib</a>|条形码类
<a href='https://github.com/yxsylyh/hiquotion_cpp/blob/master/FoundationLib/Base64Lib'>Base64Lib</a>|Base64编解码类，<b>常用</b>
BitmapLib|Bitmap图像操作类
BoostSupport</a>|本来想在代码中支持Boost的，但未能实现
BufferLib|各种缓冲区操作类
<a href='https://github.com/yxsylyh/hiquotion_cpp/blob/master/FoundationLib/CameraLib'>CameraLib</a>|摄像头操作类（基于DirectX的，基于VFW的已废弃）
<a href='https://github.com/yxsylyh/hiquotion_cpp/blob/master/FoundationLib/ClipboardOperation'>ClipboardOperation</a>|剪切板操作类
<a href='https://github.com/yxsylyh/hiquotion_cpp/blob/master/FoundationLib/ColorSystemLib'>ColorSystemLib</a>|颜色系统转换类
CommandLine|命令行参数信息获取类
<a href='https://github.com/yxsylyh/hiquotion_cpp/blob/master/FoundationLib/DataStructLib'>DataStructLib</a>|数据结果类库（包括列表、hash表、树节点、图节点、自包含节点等等）
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/Db'>Db</a>|数据库操作类（包括Oracle OCCI、MySql、ADO等的包装类）
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/DeviceInfoLib'>DeviceInfoLib</a>|硬件信息类（获取硬盘序列号）
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/DialogOperationLib'>DialogOperationLib</a>|对话框操作类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/DialogPanelSwitcherLib'>DialogPanelSwitcherLib</a>|对话框面板切换类（类似TabControl中Panel切换的效果）
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/DialogSubWindow'>DialogSubWindow</a>|对话框子窗口类（将对话框嵌入到列表框或其他控件中）
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/DllOperationLib'>DllOperationLib</a>|DLL操作类
DoubleBufferLib|双缓冲（可能没怎么用）
DrawingEditorLib|界面绘制编辑器（未完成）
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/DrawingLib'>DrawingLib</a>|绘图元素类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/EventLib'>EventLib</a>|事件类，<b>非常常用</b>
EventProcessLib|事件处理类（未实现）
Exception|异常处理类
FTPLib|一个FTP类库，使用的是第三方lib文件（文件较大，未包含在该仓库中）
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/FileLogLib'>FileLogLib</a>|文件日志类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/FileSysLib'>FileSysLib</a>|文件系统操作类，<b>非常常用</b>
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/GUIDLIb'>GUIDLIb</a>|GUID生成类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/HTTPRequest'>HTTPRequest</a>|HTTPRequest操作类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/HardwareOperation'>HardwareOperation</a>|硬件操作类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/INILib'>INILib</a>|Ini文件操作类，<b>常用</b>
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/ImageLib'>ImageLib</a>|图像操作类
JrtpLib|jrtp协议操作类
LayoutLib|界面布局类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/LogLib'>LogLib</a>|日志类
MD5|MD5生成类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/MathLib'>MathLib</a>|数学函数类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/MonitorSystemLib'>MonitorSystemLib</a>|监控系统用到的类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/MovingLib'>MovingLib</a>|界面元素移动类。针对运动的起点和终点，在最小移动步长以及最大总移动时间（毫秒）的约束下，给出运动步长。
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/MultiThreadLib'>MultiThreadLib</a>|多线程操作类，<b>常用</b>
PortAudioLib|PortAudio操作类
ProtocolLib|各种协议类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/RandLib'>RandLib</a>|随机数类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/RegularExpressionLib'>RegularExpressionLib</a>|正则表达式类，<b>编译器项目的基础类库</b>
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/SafeControlLib'>SafeControlLib</a>|安全控件类（使ocx控件实现安全接口）
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/ShortcutLib'>ShortcutLib</a>|创建快捷方式类
SocketLib|Socket网络编程类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/StringExtLib'>StringExtLib</a>|字符串扩展类，<b>常用</b>
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/SystemInfoLib'>SystemInfoLib</a>|系统信息类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/SystemLib'>SystemLib</a>|系统相关的操作类（比如类似VB的DoEvents方法），<b>常用</b>
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/TWAINLIb'>TWAINLIb</a>|基于TWAIN协议的设备操作类（比如扫描仪、摄像头、高拍仪等等，需要事先安装相应的TWAIN驱动）
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/TimeLib'>TimeLib</a>|时间操作类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/TimerLib'>TimerLib</a>|定时器操作类，<b>常用</b>
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/UIControl'>UIControl</a>|自己实现的几个界面控件
UIHandlerLib|界面元素处理类（未完成）
UndoLib|undo操作类（未完成）
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/VersionLib'>VersionLib</a>|版本操作类
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/WaveLib'>WaveLib</a>|wav波形文件操作类
WebSocket-libWebsocket,支持ws和wss,客户端好像,估计废弃|（估计废弃）
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/WindowExLib'>WindowExLib</a>|窗口扩展类
XmlConfigGen|XML格式配置文件生成类（未完成，也有些复杂）
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/XmlOperationLib'>XmlOperationLib</a>|XML文件操作类，<b>常用</b>
<a href='https://github.com/yxsylyh/hiquotion_cpp/tree/master/FoundationLib/cxImageLib'>cxImageLib</a>|CXImage对应的类库（主要包含头文件）

# AdvancedLib 代码分类说明

目录|说明
---|---
Architecture|架构模式设计（管道框架已实现，过程框架暂未实现）
CodeGen/EntityGenerator|代码生成工具（实体类生成）
CodecLib|编解码类
<a href='https://github.com/yxsylyh/hiquotion_cpp/blob/master/FoundationLib/CompileLib'>CompileLib</a>|编译器类库（未完全实现）</b>
DesignPattern|设计模式（代理、责任链）
DesignerLib|设计器类库（未实现）
DllPlugin|Dll插件开发（只是框架）
IOCPLib|Windows基于IOCP高性能socket
MultiThreadPattern/ProductorConsumerLib|多线程设计模式（生产消费模式）
PEFormat/PEImporterTable|Windows可执行文件PE的文件结构之导入表
PokerLib|自己想做的一个扑克牌游戏所需的类库（游戏没有做完，遇到了点问题没法解决）
StudySystemLib|学习系统（未开始）
TaskDispatchLib-即将废弃|任务调度（即将废弃）
VlcPlayer|VLC播放器类库

# Application 说明

目录|说明
---|---
CodeDom-未完成|文档对象模型的实现（未完成）
MonitorSystem|Windows下的监控系统

# Hardware/card 说明

目录|说明
---|---
IDCard/ShenSi|神思身份证读卡器操作类库
SIDCard/DeCard|德卡USB口的社保卡读卡器
rf/mw|明华（M&W）奥汉射频卡读卡器操作类

# 3rdParty 第三方类库说明

下列表格内容主要来源于第三方，可能略有改动（只是已经记不得改哪了）

目录|说明
---|---
CKFtpLib|Ftp操作类库
DibLib|DIB图像操作类
G729A|G729a音频编解码操作类库
GDIPlus|GDI+操作类库
IOCP|IOCP操作类
ListCtrlCl|列表控件
PortAudio|PortAudio音频操作类库
PugiXmlLib|一种xml操作类，用起来比较方便，而且支持xpath
SortableStringArray|CStringArray的一个扩展，支持排序
Speex|Speex音频编解码操作类
SystemTrayLib|Windows系统托盘操作类
TinyXml|一种xml操作类，基本不用了，因为操作不方便
cxImage|图片处理类库
gridctrl|表格控件
jrtplib3|jrtp协议类库
jsonLib|json操作类
libwebsockets|websocket操作类
vlc|vlc类库
websocketpp-master|websocket操作类

# 一个已知问题
由于源码目录 foudationlib 修改成 foundationlib，而有些源码中在 #include 引用中未做修改，可能会出现编译错误的提示。只需要将文件夹名称修改即可。（修改后建议提交，谢谢！）
