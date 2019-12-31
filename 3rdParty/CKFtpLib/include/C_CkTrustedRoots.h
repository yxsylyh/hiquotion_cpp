// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkTrustedRoots_H
#define _C_CkTrustedRoots_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC void CkTrustedRoots_setAbortCheck(HCkTrustedRoots cHandle, BOOL (*fnAbortCheck)());
CK_VISIBLE_PUBLIC void CkTrustedRoots_setPercentDone(HCkTrustedRoots cHandle, BOOL (*fnPercentDone)(int pctDone));
CK_VISIBLE_PUBLIC void CkTrustedRoots_setProgressInfo(HCkTrustedRoots cHandle, void (*fnProgressInfo)(const char *name, const char *value));
CK_VISIBLE_PUBLIC void CkTrustedRoots_setTaskCompleted(HCkTrustedRoots cHandle, void (*fnTaskCompleted)(HCkTask hTask));

CK_VISIBLE_PUBLIC HCkTrustedRoots CkTrustedRoots_Create(void);
CK_VISIBLE_PUBLIC void CkTrustedRoots_Dispose(HCkTrustedRoots handle);
CK_VISIBLE_PUBLIC void CkTrustedRoots_getDebugLogFilePath(HCkTrustedRoots cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkTrustedRoots_putDebugLogFilePath(HCkTrustedRoots cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkTrustedRoots_debugLogFilePath(HCkTrustedRoots cHandle);
CK_VISIBLE_PUBLIC void CkTrustedRoots_getLastErrorHtml(HCkTrustedRoots cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkTrustedRoots_lastErrorHtml(HCkTrustedRoots cHandle);
CK_VISIBLE_PUBLIC void CkTrustedRoots_getLastErrorText(HCkTrustedRoots cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkTrustedRoots_lastErrorText(HCkTrustedRoots cHandle);
CK_VISIBLE_PUBLIC void CkTrustedRoots_getLastErrorXml(HCkTrustedRoots cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkTrustedRoots_lastErrorXml(HCkTrustedRoots cHandle);
CK_VISIBLE_PUBLIC BOOL CkTrustedRoots_getLastMethodSuccess(HCkTrustedRoots cHandle);
CK_VISIBLE_PUBLIC void CkTrustedRoots_putLastMethodSuccess(HCkTrustedRoots cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkTrustedRoots_getNumCerts(HCkTrustedRoots cHandle);
CK_VISIBLE_PUBLIC BOOL CkTrustedRoots_getTrustSystemCaRoots(HCkTrustedRoots cHandle);
CK_VISIBLE_PUBLIC void CkTrustedRoots_putTrustSystemCaRoots(HCkTrustedRoots cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkTrustedRoots_getUtf8(HCkTrustedRoots cHandle);
CK_VISIBLE_PUBLIC void CkTrustedRoots_putUtf8(HCkTrustedRoots cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkTrustedRoots_getVerboseLogging(HCkTrustedRoots cHandle);
CK_VISIBLE_PUBLIC void CkTrustedRoots_putVerboseLogging(HCkTrustedRoots cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkTrustedRoots_getVersion(HCkTrustedRoots cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkTrustedRoots_version(HCkTrustedRoots cHandle);
CK_VISIBLE_PUBLIC BOOL CkTrustedRoots_Activate(HCkTrustedRoots cHandle);
CK_VISIBLE_PUBLIC BOOL CkTrustedRoots_AddCert(HCkTrustedRoots cHandle, HCkCert cert);
CK_VISIBLE_PUBLIC BOOL CkTrustedRoots_AddJavaKeyStore(HCkTrustedRoots cHandle, HCkJavaKeyStore keystore);
CK_VISIBLE_PUBLIC HCkTask CkTrustedRoots_AddJavaKeyStoreAsync(HCkTrustedRoots cHandle, HCkJavaKeyStore keystore);
CK_VISIBLE_PUBLIC BOOL CkTrustedRoots_Deactivate(HCkTrustedRoots cHandle);
CK_VISIBLE_PUBLIC HCkCert CkTrustedRoots_GetCert(HCkTrustedRoots cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkTrustedRoots_LoadCaCertsPem(HCkTrustedRoots cHandle, const char *path);
CK_VISIBLE_PUBLIC HCkTask CkTrustedRoots_LoadCaCertsPemAsync(HCkTrustedRoots cHandle, const char *path);
CK_VISIBLE_PUBLIC BOOL CkTrustedRoots_SaveLastError(HCkTrustedRoots cHandle, const char *path);
#endif
