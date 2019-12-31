#include "stdafx.h"
#include "Vmcp.h"
#include <c++\FoudationLib\StringExtLib\StringExt.h>

CString CVmcp::parameters2Text(CPointerMap<CString, CString>& parameters)
{
	CString text;
	CPointerMap<CString, CString>::iterator i;
	for (i = parameters.begin(); i != parameters.end(); i++)
	{
		CString para = (*i).first;
		CString value = (*i).second;
		text += para + "=" + value;
		text += "\n";
	}

	return text;
}

CString CVmcp::create(CString head, CString version, CString command, CPointerMap<CString, CString>& parameters)
{
	CString text;
	text.Format("%s\n%s\n%s\n", head, version, command);
	if((int)parameters.size()>0)
		text += parameters2Text(parameters);

	return text;
}

CString CVmcp::createHeartBeat()
{
	/*
		发送：
		VMCP
		1.0
		heartbeat
	*/
	m_parameters.clear();
	return create("VMCP", "1.0", "heartbeat", m_parameters);
}

CString CVmcp::createStart(CString serverIp, int serverPort, CString name)
{
	/*
		发送：
		VMCP
		1.0
		start
		ip=
		port=
		name=
	*/
	CString sport;
	sport.Format("%d", serverPort);
	m_parameters.clear();
	m_parameters.put("ip", serverIp);
	m_parameters.put("port", sport);
	m_parameters.put("name", name);
	return create("VMCP", "1.0", "start", m_parameters);
}

CString CVmcp::createStop()
{
	/*
		发送：
		VMCP
		1.0
		stop
	*/
	m_parameters.clear();
	return create("VMCP", "1.0", "stop", m_parameters);
}

CString CVmcp::createSuccessResponse(CString head, CString version, CString command, CPointerMap<CString, CString>& parameters)
{
	CString text;
	text.Format("%s\n%s\n%s\nOK\n", head, version, command);

	if ((int)parameters.size() > 0)
		text += parameters2Text(parameters);

	return text;
}

CString CVmcp::createFailureResponse(CString head, CString version, CString command, CString errMsgShown, CString errMsgKernel)
{
	CString text;
	text.Format("%s\n%s\n%s\nERROR\n%s\n%s", head, version, command, errMsgShown, errMsgKernel);
	return text;
}

BOOL CVmcp::parse(CString text, ParseResult& result, CString& parseErrMsg, ParseMode mode)
{
	if (text.GetLength() <= 0)
	{
		parseErrMsg = "传入参数（待解析文本）为空。";
		return FALSE;
	}

	CStringArray array;
	CStringExt::Split(text, array, "\n");
	if (array.GetCount() < 4)
	{
		parseErrMsg = "解析失败！文本行数小于4。";
		return FALSE;
	}

	if (array.GetAt(0) != "VMCP")
	{
		parseErrMsg = "解析失败！非 VMCP 协议。";
		return FALSE;
	}

	result.head = array.GetAt(0);
	result.version = array.GetAt(1);
	result.command = array.GetAt(2);

	int paraStartIndex = 3;
	switch (mode)
	{
	case serverParse:
		paraStartIndex = 3;
		result.result = TRUE;

		break;
	case clientParse:
		paraStartIndex = 4;

		if (array.GetAt(3) == "OK")
			result.result = TRUE;
		else
			result.result = FALSE;

		if (!result.result)
		{
			if (array.GetCount() > 4)
				result.errMsgShown = array.GetAt(4);
			if (array.GetCount() > 5)
				result.errMsgKernel = array.GetAt(5);

			return TRUE;
		}

		break;
	default:
		break;
	}

	result.parameters.clear();
	for (int i = paraStartIndex; i < array.GetCount(); i++)
	{
		CString paraLine = array.GetAt(i);
		if (paraLine.GetLength() <= 0)
			continue;

		CStringArray paraArray;
		CStringExt::Split(paraLine, paraArray, "=");
		if (paraArray.GetCount() < 2)
			continue;

		result.parameters.put(paraArray.GetAt(0), paraArray.GetAt(1));
	}

	return TRUE;
}

CString CVmcp::createHeartBeatResponse(CString status)
{
	/*
		接收：
		VMCP
		1.0
		heartbeat_response
		OK
		ffmpeg=running（或者为stopped、unknown。unknown表示获取ffmpeg程序信息失败）
	*/
	m_parametersResponded.clear();
	m_parametersResponded.put("ffmpeg", status);
	return createSuccessResponse("VMCP", "1.0", "heartbeat_response", m_parametersResponded);
}

CString CVmcp::createStartSuccessResponse(CString sdp)
{
	/*
		接收（启动成功时）：
		VMCP
		1.0
		start_response
		OK
		sdp=
	*/
	m_parametersResponded.clear();
	m_parametersResponded.put("sdp", sdp);
	return createSuccessResponse("VMCP", "1.0", "start_response", m_parametersResponded);
}

CString CVmcp::createStartFailureResponse(CString errMsgShown, CString errMsgKernel)
{
	return createFailureResponse("VMCP", "1.0", "start_response", errMsgShown, errMsgKernel);
}

CString CVmcp::createStopSuccessResponse()
{
	/*
		接收（关闭成功时）：
		VMCP
		1.0
		stop_response
		OK
	*/
	m_parametersResponded.clear();
	return createSuccessResponse("VMCP", "1.0", "stop_response", m_parametersResponded);
}

CString CVmcp::createStopFailureResponse(CString errMsgShown, CString errMsgKernel)
{
	return createFailureResponse("VMCP", "1.0", "stop_response", errMsgShown, errMsgKernel);
}

BOOL CVmcp::checkResponsedCommand(CString commandSent, CString commandResponded)
{
	if (commandSent != commandResponded + "_response")
		return FALSE;

	return TRUE;
}
