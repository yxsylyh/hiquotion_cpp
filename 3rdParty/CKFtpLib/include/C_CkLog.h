// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkLog_H
#define _C_CkLog_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC HCkLog CkLog_Create(void);
CK_VISIBLE_PUBLIC void CkLog_Dispose(HCkLog handle);
CK_VISIBLE_PUBLIC void CkLog_getDebugLogFilePath(HCkLog cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkLog_putDebugLogFilePath(HCkLog cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkLog_debugLogFilePath(HCkLog cHandle);
CK_VISIBLE_PUBLIC void CkLog_getLastErrorHtml(HCkLog cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkLog_lastErrorHtml(HCkLog cHandle);
CK_VISIBLE_PUBLIC void CkLog_getLastErrorText(HCkLog cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkLog_lastErrorText(HCkLog cHandle);
CK_VISIBLE_PUBLIC void CkLog_getLastErrorXml(HCkLog cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkLog_lastErrorXml(HCkLog cHandle);
CK_VISIBLE_PUBLIC BOOL CkLog_getLastMethodSuccess(HCkLog cHandle);
CK_VISIBLE_PUBLIC void CkLog_putLastMethodSuccess(HCkLog cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkLog_getUtf8(HCkLog cHandle);
CK_VISIBLE_PUBLIC void CkLog_putUtf8(HCkLog cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkLog_getVerboseLogging(HCkLog cHandle);
CK_VISIBLE_PUBLIC void CkLog_putVerboseLogging(HCkLog cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkLog_getVersion(HCkLog cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkLog_version(HCkLog cHandle);
CK_VISIBLE_PUBLIC void CkLog_Clear(HCkLog cHandle, const char *initialTag);
CK_VISIBLE_PUBLIC void CkLog_EnterContext(HCkLog cHandle, const char *tag);
CK_VISIBLE_PUBLIC void CkLog_LeaveContext(HCkLog cHandle);
CK_VISIBLE_PUBLIC void CkLog_LogData(HCkLog cHandle, const char *tag, const char *message);
CK_VISIBLE_PUBLIC void CkLog_LogDataBase64(HCkLog cHandle, const char *tag, HCkByteData data);
CK_VISIBLE_PUBLIC void CkLog_LogDataHex(HCkLog cHandle, const char *tag, HCkByteData data);
CK_VISIBLE_PUBLIC void CkLog_LogDataMax(HCkLog cHandle, const char *tag, const char *message, int maxNumChars);
CK_VISIBLE_PUBLIC void CkLog_LogDateTime(HCkLog cHandle, const char *tag, BOOL gmt);
CK_VISIBLE_PUBLIC void CkLog_LogError(HCkLog cHandle, const char *message);
CK_VISIBLE_PUBLIC void CkLog_LogInfo(HCkLog cHandle, const char *message);
CK_VISIBLE_PUBLIC void CkLog_LogInt(HCkLog cHandle, const char *tag, int value);
CK_VISIBLE_PUBLIC void CkLog_LogInt64(HCkLog cHandle, const char *tag, __int64 value);
CK_VISIBLE_PUBLIC void CkLog_LogTimestamp(HCkLog cHandle, const char *tag);
CK_VISIBLE_PUBLIC BOOL CkLog_SaveLastError(HCkLog cHandle, const char *path);
#endif
