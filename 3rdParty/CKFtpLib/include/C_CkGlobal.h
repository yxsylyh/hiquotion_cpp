// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkGlobal_H
#define _C_CkGlobal_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC HCkGlobal CkGlobal_Create(void);
CK_VISIBLE_PUBLIC void CkGlobal_Dispose(HCkGlobal handle);
CK_VISIBLE_PUBLIC int CkGlobal_getAnsiCodePage(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC void CkGlobal_putAnsiCodePage(HCkGlobal cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkGlobal_getDebugLogFilePath(HCkGlobal cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkGlobal_putDebugLogFilePath(HCkGlobal cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkGlobal_debugLogFilePath(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC int CkGlobal_getDefaultNtlmVersion(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC void CkGlobal_putDefaultNtlmVersion(HCkGlobal cHandle, int newVal);
CK_VISIBLE_PUBLIC BOOL CkGlobal_getDefaultUtf8(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC void CkGlobal_putDefaultUtf8(HCkGlobal cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkGlobal_getDnsTimeToLive(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC void CkGlobal_putDnsTimeToLive(HCkGlobal cHandle, int newVal);
CK_VISIBLE_PUBLIC BOOL CkGlobal_getEnableDnsCaching(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC void CkGlobal_putEnableDnsCaching(HCkGlobal cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkGlobal_getLastErrorHtml(HCkGlobal cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkGlobal_lastErrorHtml(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC void CkGlobal_getLastErrorText(HCkGlobal cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkGlobal_lastErrorText(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC void CkGlobal_getLastErrorXml(HCkGlobal cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkGlobal_lastErrorXml(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC BOOL CkGlobal_getLastMethodSuccess(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC void CkGlobal_putLastMethodSuccess(HCkGlobal cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkGlobal_getMaxThreads(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC void CkGlobal_putMaxThreads(HCkGlobal cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkGlobal_getThreadPoolLogPath(HCkGlobal cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkGlobal_putThreadPoolLogPath(HCkGlobal cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkGlobal_threadPoolLogPath(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC int CkGlobal_getUnlockStatus(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC BOOL CkGlobal_getUtf8(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC void CkGlobal_putUtf8(HCkGlobal cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkGlobal_getVerboseLogging(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC void CkGlobal_putVerboseLogging(HCkGlobal cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkGlobal_getVersion(HCkGlobal cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkGlobal_version(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC BOOL CkGlobal_DnsClearCache(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC BOOL CkGlobal_FinalizeThreadPool(HCkGlobal cHandle);
CK_VISIBLE_PUBLIC BOOL CkGlobal_SaveLastError(HCkGlobal cHandle, const char *path);
CK_VISIBLE_PUBLIC BOOL CkGlobal_UnlockBundle(HCkGlobal cHandle, const char *bundleUnlockCode);
#endif
