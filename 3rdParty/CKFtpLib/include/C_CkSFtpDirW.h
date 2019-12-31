// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkSFtpDirWH
#define _C_CkSFtpDirWH
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC HCkSFtpDirW CkSFtpDirW_Create(void);
CK_VISIBLE_PUBLIC void CkSFtpDirW_Dispose(HCkSFtpDirW handle);
CK_VISIBLE_PUBLIC BOOL CkSFtpDirW_getLastMethodSuccess(HCkSFtpDirW cHandle);
CK_VISIBLE_PUBLIC void  CkSFtpDirW_putLastMethodSuccess(HCkSFtpDirW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkSFtpDirW_getNumFilesAndDirs(HCkSFtpDirW cHandle);
CK_VISIBLE_PUBLIC void CkSFtpDirW_getOriginalPath(HCkSFtpDirW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkSFtpDirW_originalPath(HCkSFtpDirW cHandle);
CK_VISIBLE_PUBLIC BOOL CkSFtpDirW_GetFilename(HCkSFtpDirW cHandle, int index, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkSFtpDirW_getFilename(HCkSFtpDirW cHandle, int index);
CK_VISIBLE_PUBLIC HCkSFtpFileW CkSFtpDirW_GetFileObject(HCkSFtpDirW cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkSFtpDirW_LoadTaskResult(HCkSFtpDirW cHandle, HCkTaskW task);
#endif
