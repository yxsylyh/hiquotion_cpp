// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkCsrWH
#define _C_CkCsrWH
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC HCkCsrW CkCsrW_Create(void);
CK_VISIBLE_PUBLIC void CkCsrW_Dispose(HCkCsrW handle);
CK_VISIBLE_PUBLIC void CkCsrW_getCommonName(HCkCsrW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCsrW_putCommonName(HCkCsrW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCsrW_commonName(HCkCsrW cHandle);
CK_VISIBLE_PUBLIC void CkCsrW_getCompany(HCkCsrW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCsrW_putCompany(HCkCsrW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCsrW_company(HCkCsrW cHandle);
CK_VISIBLE_PUBLIC void CkCsrW_getCompanyDivision(HCkCsrW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCsrW_putCompanyDivision(HCkCsrW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCsrW_companyDivision(HCkCsrW cHandle);
CK_VISIBLE_PUBLIC void CkCsrW_getCountry(HCkCsrW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCsrW_putCountry(HCkCsrW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCsrW_country(HCkCsrW cHandle);
CK_VISIBLE_PUBLIC void CkCsrW_getDebugLogFilePath(HCkCsrW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCsrW_putDebugLogFilePath(HCkCsrW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCsrW_debugLogFilePath(HCkCsrW cHandle);
CK_VISIBLE_PUBLIC void CkCsrW_getEmailAddress(HCkCsrW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCsrW_putEmailAddress(HCkCsrW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCsrW_emailAddress(HCkCsrW cHandle);
CK_VISIBLE_PUBLIC void CkCsrW_getLastErrorHtml(HCkCsrW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkCsrW_lastErrorHtml(HCkCsrW cHandle);
CK_VISIBLE_PUBLIC void CkCsrW_getLastErrorText(HCkCsrW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkCsrW_lastErrorText(HCkCsrW cHandle);
CK_VISIBLE_PUBLIC void CkCsrW_getLastErrorXml(HCkCsrW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkCsrW_lastErrorXml(HCkCsrW cHandle);
CK_VISIBLE_PUBLIC BOOL CkCsrW_getLastMethodSuccess(HCkCsrW cHandle);
CK_VISIBLE_PUBLIC void  CkCsrW_putLastMethodSuccess(HCkCsrW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkCsrW_getLocality(HCkCsrW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCsrW_putLocality(HCkCsrW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCsrW_locality(HCkCsrW cHandle);
CK_VISIBLE_PUBLIC void CkCsrW_getState(HCkCsrW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkCsrW_putState(HCkCsrW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkCsrW_state(HCkCsrW cHandle);
CK_VISIBLE_PUBLIC BOOL CkCsrW_getVerboseLogging(HCkCsrW cHandle);
CK_VISIBLE_PUBLIC void  CkCsrW_putVerboseLogging(HCkCsrW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkCsrW_getVersion(HCkCsrW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkCsrW_version(HCkCsrW cHandle);
CK_VISIBLE_PUBLIC BOOL CkCsrW_GenCsrBd(HCkCsrW cHandle, HCkPrivateKeyW privKey, HCkBinDataW csrData);
CK_VISIBLE_PUBLIC BOOL CkCsrW_GenCsrPem(HCkCsrW cHandle, HCkPrivateKeyW privKey, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCsrW_genCsrPem(HCkCsrW cHandle, HCkPrivateKeyW privKey);
CK_VISIBLE_PUBLIC BOOL CkCsrW_GetSubjectField(HCkCsrW cHandle, const wchar_t *oid, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkCsrW_getSubjectField(HCkCsrW cHandle, const wchar_t *oid);
CK_VISIBLE_PUBLIC BOOL CkCsrW_LoadCsrPem(HCkCsrW cHandle, const wchar_t *csrPemStr);
CK_VISIBLE_PUBLIC BOOL CkCsrW_SaveLastError(HCkCsrW cHandle, const wchar_t *path);
CK_VISIBLE_PUBLIC BOOL CkCsrW_SetSubjectField(HCkCsrW cHandle, const wchar_t *oid, const wchar_t *value, const wchar_t *asnType);
#endif
