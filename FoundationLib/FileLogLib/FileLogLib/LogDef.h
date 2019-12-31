#if !defined(LOGDEF_H)
#define LOGDEF_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Log.h"
#include <string>

void LOG_START();
void LOG_END();

void LOG(std::string msg);
void LOG0(enum eLogLevel level, std::string msg);

void LOG_EXCEPTION(std::string msg);
void LOG_INFO(std::string msg);
void LOG_WARNING(std::string msg);
void LOG_DEBUG(std::string msg);

#endif // !defined(LOGDEF_H)
