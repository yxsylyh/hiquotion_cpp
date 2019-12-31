// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkPfxWH
#define _C_CkPfxWH
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC HCkPfxW CkPfxW_Create(void);
CK_VISIBLE_PUBLIC void CkPfxW_Dispose(HCkPfxW handle);
CK_VISIBLE_PUBLIC void CkPfxW_getDebugLogFilePath(HCkPfxW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkPfxW_putDebugLogFilePath(HCkPfxW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkPfxW_debugLogFilePath(HCkPfxW cHandle);
CK_VISIBLE_PUBLIC void CkPfxW_getLastErrorHtml(HCkPfxW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkPfxW_lastErrorHtml(HCkPfxW cHandle);
CK_VISIBLE_PUBLIC void CkPfxW_getLastErrorText(HCkPfxW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkPfxW_lastErrorText(HCkPfxW cHandle);
CK_VISIBLE_PUBLIC void CkPfxW_getLastErrorXml(HCkPfxW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkPfxW_lastErrorXml(HCkPfxW cHandle);
CK_VISIBLE_PUBLIC BOOL CkPfxW_getLastMethodSuccess(HCkPfxW cHandle);
CK_VISIBLE_PUBLIC void  CkPfxW_putLastMethodSuccess(HCkPfxW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkPfxW_getNumCerts(HCkPfxW cHandle);
CK_VISIBLE_PUBLIC int CkPfxW_getNumPrivateKeys(HCkPfxW cHandle);
CK_VISIBLE_PUBLIC BOOL CkPfxW_getVerboseLogging(HCkPfxW cHandle);
CK_VISIBLE_PUBLIC void  CkPfxW_putVerboseLogging(HCkPfxW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkPfxW_getVersion(HCkPfxW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkPfxW_version(HCkPfxW cHandle);
CK_VISIBLE_PUBLIC BOOL CkPfxW_AddCert(HCkPfxW cHandle, HCkCertW cert, BOOL includeChain);
CK_VISIBLE_PUBLIC BOOL CkPfxW_AddPrivateKey(HCkPfxW cHandle, HCkPrivateKeyW privKey, HCkCertChainW certChain);
CK_VISIBLE_PUBLIC HCkCertW CkPfxW_GetCert(HCkPfxW cHandle, int index);
CK_VISIBLE_PUBLIC HCkPrivateKeyW CkPfxW_GetPrivateKey(HCkPfxW cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkPfxW_LoadPem(HCkPfxW cHandle, const wchar_t *pemStr, const wchar_t *password);
CK_VISIBLE_PUBLIC BOOL CkPfxW_LoadPfxBytes(HCkPfxW cHandle, HCkByteData pfxData, const wchar_t *password);
CK_VISIBLE_PUBLIC BOOL CkPfxW_LoadPfxEncoded(HCkPfxW cHandle, const wchar_t *encodedData, const wchar_t *encoding, const wchar_t *password);
CK_VISIBLE_PUBLIC BOOL CkPfxW_LoadPfxFile(HCkPfxW cHandle, const wchar_t *path, const wchar_t *password);
CK_VISIBLE_PUBLIC BOOL CkPfxW_SaveLastError(HCkPfxW cHandle, const wchar_t *path);
CK_VISIBLE_PUBLIC BOOL CkPfxW_ToBinary(HCkPfxW cHandle, const wchar_t *password, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkPfxW_ToEncodedString(HCkPfxW cHandle, const wchar_t *password, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkPfxW_toEncodedString(HCkPfxW cHandle, const wchar_t *password, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkPfxW_ToFile(HCkPfxW cHandle, const wchar_t *password, const wchar_t *path);
CK_VISIBLE_PUBLIC HCkJavaKeyStoreW CkPfxW_ToJavaKeyStore(HCkPfxW cHandle, const wchar_t *alias, const wchar_t *password);
CK_VISIBLE_PUBLIC BOOL CkPfxW_ToPem(HCkPfxW cHandle, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkPfxW_toPem(HCkPfxW cHandle);
CK_VISIBLE_PUBLIC BOOL CkPfxW_ToPemEx(HCkPfxW cHandle, BOOL extendedAttrs, BOOL noKeys, BOOL noCerts, BOOL noCaCerts, const wchar_t *encryptAlg, const wchar_t *password, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkPfxW_toPemEx(HCkPfxW cHandle, BOOL extendedAttrs, BOOL noKeys, BOOL noCerts, BOOL noCaCerts, const wchar_t *encryptAlg, const wchar_t *password);
CK_VISIBLE_PUBLIC BOOL CkPfxW_UseCertVault(HCkPfxW cHandle, HCkXmlCertVaultW vault);
#endif
