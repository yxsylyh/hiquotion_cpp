// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkSFtpDir_H
#define _C_CkSFtpDir_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC HCkSFtpDir CkSFtpDir_Create(void);
CK_VISIBLE_PUBLIC void CkSFtpDir_Dispose(HCkSFtpDir handle);
CK_VISIBLE_PUBLIC BOOL CkSFtpDir_getLastMethodSuccess(HCkSFtpDir cHandle);
CK_VISIBLE_PUBLIC void CkSFtpDir_putLastMethodSuccess(HCkSFtpDir cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkSFtpDir_getNumFilesAndDirs(HCkSFtpDir cHandle);
CK_VISIBLE_PUBLIC void CkSFtpDir_getOriginalPath(HCkSFtpDir cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkSFtpDir_originalPath(HCkSFtpDir cHandle);
CK_VISIBLE_PUBLIC BOOL CkSFtpDir_getUtf8(HCkSFtpDir cHandle);
CK_VISIBLE_PUBLIC void CkSFtpDir_putUtf8(HCkSFtpDir cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkSFtpDir_GetFilename(HCkSFtpDir cHandle, int index, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkSFtpDir_getFilename(HCkSFtpDir cHandle, int index);
CK_VISIBLE_PUBLIC HCkSFtpFile CkSFtpDir_GetFileObject(HCkSFtpDir cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkSFtpDir_LoadTaskResult(HCkSFtpDir cHandle, HCkTask task);
#endif
