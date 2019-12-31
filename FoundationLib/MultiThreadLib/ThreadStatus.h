#pragma once

#include <string>
using namespace std;

enum ThreadStatus
{
	Created,
	Running,
	Paused,
	Stopped,
	ToStop,
	Closed,
	Terminated,
// 	Destroyed,
	Error,
};

class CThreadStatus
{
public:
	static std::string toString(ThreadStatus status)
	{
		std::string s="";
		switch(status)
		{
		case Created:
			s="已经创建";
			break;
		case Running:
			s="正在运行";
			break;
		case Paused:
			s="暂停运行";
			break;
		case Stopped:
			s="已经停止";
			break;
		case ToStop:
			s="准备停止";
			break;
		case Terminated:
			s="已强制终止";
			break;
		case Error:
			s="出现错误";
			break;
		}

		return s;
	}
};