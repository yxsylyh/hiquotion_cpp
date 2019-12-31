#pragma once

#include <c++\FoudationLib\DataStructLib\PointerMap.h>

/*
	Request格式
	VMCP
	1.0
	<command>
	<command data>（每个参数一行，参数名和参数值之间用=分割）

	Respond成功时格式
	VMCP
	1.0
	<command>_response
	OK
	<respond data>（每个参数一行，参数名和参数值之间用=分割，参数值多行时用;代替换行）

	Respond失败时格式
	VMCP
	1.0
	<command>_response
	ERROR
	<error message shown>
	<error message kernel>

	command包括：
	heartbeat（心跳）
	start（开启）
	stop（停止）

	1、heartbeat

	发送：
	VMCP
	1.0
	heartbeat

	接收：
	VMCP
	1.0
	heartbeat_response
	OK
	ffmpeg=running（或者为stopped、unknown。unknown表示获取ffmpeg程序信息失败）

	2、start

	发送：
	VMCP
	1.0
	start
	ip=
	port=
	name=
	（说明：启动成功后，返回的sdp为“sdp://<ip>:<port>/<name>.sdp”。）

	接收（启动成功时）：
	VMCP
	1.0
	start_response
	OK
	sdp=

	接收（启动失败时）：
	VMCP
	1.0
	start_response
	ERROR
	<error message shown>
	<error message kernel>

	3、stop

	发送：
	VMCP
	1.0
	stop

	接收（关闭成功时）：
	VMCP
	1.0
	stop_response
	OK

	接收（关闭失败时）：
	VMCP
	1.0
	stop_response
	ERROR
	<error message shown>
	<error message kernel>
*/

struct ParseResult
{
	CString head;
	CString version;
	CString command;
	BOOL result;
	CPointerMap<CString, CString> parameters;
	CString errMsgShown;
	CString errMsgKernel;
};

enum ParseMode
{
	serverParse,
	clientParse,
};


// VMC Application protocol class
class CVmcp
{
public:
	CVmcp() {}
	~CVmcp() {}

	CString parameters2Text(CPointerMap<CString, CString>& parameters);
	CString create(CString head, CString version, CString command, CPointerMap<CString, CString>& parameters);

	CString createHeartBeat();
	CString createStart(CString serverIp, int serverPort, CString name);
	CString createStop();

	CString createSuccessResponse(CString head, CString version, CString command, CPointerMap<CString, CString>& parameters);
	CString createFailureResponse(CString head, CString version, CString command, CString errMsgShown, CString errMsgKernel);
	BOOL parse(CString text, ParseResult& result, CString& parseErrMsg, ParseMode mode = serverParse);

	CString createHeartBeatResponse(CString status);
	CString createStartSuccessResponse(CString sdp);
	CString createStartFailureResponse(CString errMsgShown, CString errMsgKernel);
	CString createStopSuccessResponse();
	CString createStopFailureResponse(CString errMsgShown, CString errMsgKernel);

	BOOL checkResponsedCommand(CString commandSent, CString commandResponded);

protected:
	CPointerMap<CString, CString> m_parameters;
	CPointerMap<CString, CString> m_parametersResponded;
};

