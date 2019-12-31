#include "stdafx.h"
#include "LogDef.h"

CLog mylog;

void LOG_START(){mylog.writeLogHead();}
void LOG_END(){mylog.writeLogEnd();}

void LOG(std::string msg){mylog.writeLn(msg);}
void LOG0(enum eLogLevel level, std::string msg){mylog.writeLn(level, msg);}

void LOG_EXCEPTION(std::string msg){mylog.writeException(msg);}
void LOG_INFO(std::string msg){mylog.writeInfo(msg);}
void LOG_WARNING(std::string msg){mylog.writeWarning(msg);}
void LOG_DEBUG(std::string msg){mylog.writeDebug(msg);}
