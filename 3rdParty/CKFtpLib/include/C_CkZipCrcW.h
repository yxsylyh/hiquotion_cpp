// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkZipCrcWH
#define _C_CkZipCrcWH
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC void CkZipCrcW_setAbortCheck(HCkZipCrcW cHandle, BOOL (*fnAbortCheck)());
CK_VISIBLE_PUBLIC void CkZipCrcW_setPercentDone(HCkZipCrcW cHandle, BOOL (*fnPercentDone)(int pctDone));
CK_VISIBLE_PUBLIC void CkZipCrcW_setProgressInfo(HCkZipCrcW cHandle, void (*fnProgressInfo)(const wchar_t *name, const wchar_t *value));
CK_VISIBLE_PUBLIC void CkZipCrcW_setTaskCompleted(HCkZipCrcW cHandle, void (*fnTaskCompleted)(HCkTaskW hTask));

CK_VISIBLE_PUBLIC HCkZipCrcW CkZipCrcW_Create(void);
CK_VISIBLE_PUBLIC void CkZipCrcW_Dispose(HCkZipCrcW handle);
CK_VISIBLE_PUBLIC BOOL CkZipCrcW_getLastMethodSuccess(HCkZipCrcW cHandle);
CK_VISIBLE_PUBLIC void  CkZipCrcW_putLastMethodSuccess(HCkZipCrcW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkZipCrcW_BeginStream(HCkZipCrcW cHandle);
CK_VISIBLE_PUBLIC unsigned long CkZipCrcW_CalculateCrc(HCkZipCrcW cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC unsigned long CkZipCrcW_EndStream(HCkZipCrcW cHandle);
CK_VISIBLE_PUBLIC unsigned long CkZipCrcW_FileCrc(HCkZipCrcW cHandle, const wchar_t *path);
CK_VISIBLE_PUBLIC HCkTaskW CkZipCrcW_FileCrcAsync(HCkZipCrcW cHandle, const wchar_t *path);
CK_VISIBLE_PUBLIC void CkZipCrcW_MoreData(HCkZipCrcW cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkZipCrcW_ToHex(HCkZipCrcW cHandle, int crc, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkZipCrcW_toHex(HCkZipCrcW cHandle, int crc);
#endif
