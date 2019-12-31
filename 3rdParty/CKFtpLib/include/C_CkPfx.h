// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkPfx_H
#define _C_CkPfx_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC HCkPfx CkPfx_Create(void);
CK_VISIBLE_PUBLIC void CkPfx_Dispose(HCkPfx handle);
CK_VISIBLE_PUBLIC void CkPfx_getDebugLogFilePath(HCkPfx cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkPfx_putDebugLogFilePath(HCkPfx cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkPfx_debugLogFilePath(HCkPfx cHandle);
CK_VISIBLE_PUBLIC void CkPfx_getLastErrorHtml(HCkPfx cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkPfx_lastErrorHtml(HCkPfx cHandle);
CK_VISIBLE_PUBLIC void CkPfx_getLastErrorText(HCkPfx cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkPfx_lastErrorText(HCkPfx cHandle);
CK_VISIBLE_PUBLIC void CkPfx_getLastErrorXml(HCkPfx cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkPfx_lastErrorXml(HCkPfx cHandle);
CK_VISIBLE_PUBLIC BOOL CkPfx_getLastMethodSuccess(HCkPfx cHandle);
CK_VISIBLE_PUBLIC void CkPfx_putLastMethodSuccess(HCkPfx cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkPfx_getNumCerts(HCkPfx cHandle);
CK_VISIBLE_PUBLIC int CkPfx_getNumPrivateKeys(HCkPfx cHandle);
CK_VISIBLE_PUBLIC BOOL CkPfx_getUtf8(HCkPfx cHandle);
CK_VISIBLE_PUBLIC void CkPfx_putUtf8(HCkPfx cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkPfx_getVerboseLogging(HCkPfx cHandle);
CK_VISIBLE_PUBLIC void CkPfx_putVerboseLogging(HCkPfx cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkPfx_getVersion(HCkPfx cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkPfx_version(HCkPfx cHandle);
CK_VISIBLE_PUBLIC BOOL CkPfx_AddCert(HCkPfx cHandle, HCkCert cert, BOOL includeChain);
CK_VISIBLE_PUBLIC BOOL CkPfx_AddPrivateKey(HCkPfx cHandle, HCkPrivateKey privKey, HCkCertChain certChain);
CK_VISIBLE_PUBLIC HCkCert CkPfx_GetCert(HCkPfx cHandle, int index);
CK_VISIBLE_PUBLIC HCkPrivateKey CkPfx_GetPrivateKey(HCkPfx cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkPfx_LoadPem(HCkPfx cHandle, const char *pemStr, const char *password);
CK_VISIBLE_PUBLIC BOOL CkPfx_LoadPfxBytes(HCkPfx cHandle, HCkByteData pfxData, const char *password);
CK_VISIBLE_PUBLIC BOOL CkPfx_LoadPfxEncoded(HCkPfx cHandle, const char *encodedData, const char *encoding, const char *password);
CK_VISIBLE_PUBLIC BOOL CkPfx_LoadPfxFile(HCkPfx cHandle, const char *path, const char *password);
CK_VISIBLE_PUBLIC BOOL CkPfx_SaveLastError(HCkPfx cHandle, const char *path);
CK_VISIBLE_PUBLIC BOOL CkPfx_ToBinary(HCkPfx cHandle, const char *password, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkPfx_ToEncodedString(HCkPfx cHandle, const char *password, const char *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkPfx_toEncodedString(HCkPfx cHandle, const char *password, const char *encoding);
CK_VISIBLE_PUBLIC BOOL CkPfx_ToFile(HCkPfx cHandle, const char *password, const char *path);
CK_VISIBLE_PUBLIC HCkJavaKeyStore CkPfx_ToJavaKeyStore(HCkPfx cHandle, const char *alias, const char *password);
CK_VISIBLE_PUBLIC BOOL CkPfx_ToPem(HCkPfx cHandle, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkPfx_toPem(HCkPfx cHandle);
CK_VISIBLE_PUBLIC BOOL CkPfx_ToPemEx(HCkPfx cHandle, BOOL extendedAttrs, BOOL noKeys, BOOL noCerts, BOOL noCaCerts, const char *encryptAlg, const char *password, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkPfx_toPemEx(HCkPfx cHandle, BOOL extendedAttrs, BOOL noKeys, BOOL noCerts, BOOL noCaCerts, const char *encryptAlg, const char *password);
CK_VISIBLE_PUBLIC BOOL CkPfx_UseCertVault(HCkPfx cHandle, HCkXmlCertVault vault);
#endif
