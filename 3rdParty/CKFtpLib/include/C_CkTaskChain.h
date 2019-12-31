// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkTaskChain_H
#define _C_CkTaskChain_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC void CkTaskChain_setAbortCheck(HCkTaskChain cHandle, BOOL (*fnAbortCheck)());
CK_VISIBLE_PUBLIC void CkTaskChain_setPercentDone(HCkTaskChain cHandle, BOOL (*fnPercentDone)(int pctDone));
CK_VISIBLE_PUBLIC void CkTaskChain_setProgressInfo(HCkTaskChain cHandle, void (*fnProgressInfo)(const char *name, const char *value));
CK_VISIBLE_PUBLIC void CkTaskChain_setTaskCompleted(HCkTaskChain cHandle, void (*fnTaskCompleted)(HCkTask hTask));

CK_VISIBLE_PUBLIC HCkTaskChain CkTaskChain_Create(void);
CK_VISIBLE_PUBLIC void CkTaskChain_Dispose(HCkTaskChain handle);
CK_VISIBLE_PUBLIC void CkTaskChain_getDebugLogFilePath(HCkTaskChain cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkTaskChain_putDebugLogFilePath(HCkTaskChain cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkTaskChain_debugLogFilePath(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC BOOL CkTaskChain_getFinished(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC int CkTaskChain_getHeartbeatMs(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC void CkTaskChain_putHeartbeatMs(HCkTaskChain cHandle, int newVal);
CK_VISIBLE_PUBLIC BOOL CkTaskChain_getInert(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC void CkTaskChain_getLastErrorHtml(HCkTaskChain cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkTaskChain_lastErrorHtml(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC void CkTaskChain_getLastErrorText(HCkTaskChain cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkTaskChain_lastErrorText(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC void CkTaskChain_getLastErrorXml(HCkTaskChain cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkTaskChain_lastErrorXml(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC BOOL CkTaskChain_getLastMethodSuccess(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC void CkTaskChain_putLastMethodSuccess(HCkTaskChain cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkTaskChain_getLive(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC int CkTaskChain_getNumTasks(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC void CkTaskChain_getStatus(HCkTaskChain cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkTaskChain_status(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC int CkTaskChain_getStatusInt(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC BOOL CkTaskChain_getStopOnFailedTask(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC void CkTaskChain_putStopOnFailedTask(HCkTaskChain cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkTaskChain_getUtf8(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC void CkTaskChain_putUtf8(HCkTaskChain cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkTaskChain_getVerboseLogging(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC void CkTaskChain_putVerboseLogging(HCkTaskChain cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkTaskChain_getVersion(HCkTaskChain cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkTaskChain_version(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC BOOL CkTaskChain_Append(HCkTaskChain cHandle, HCkTask task);
CK_VISIBLE_PUBLIC BOOL CkTaskChain_Cancel(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC HCkTask CkTaskChain_GetTask(HCkTaskChain cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkTaskChain_Run(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC BOOL CkTaskChain_RunSynchronously(HCkTaskChain cHandle);
CK_VISIBLE_PUBLIC BOOL CkTaskChain_SaveLastError(HCkTaskChain cHandle, const char *path);
CK_VISIBLE_PUBLIC void CkTaskChain_SleepMs(HCkTaskChain cHandle, int numMs);
CK_VISIBLE_PUBLIC BOOL CkTaskChain_Wait(HCkTaskChain cHandle, int maxWaitMs);
#endif
