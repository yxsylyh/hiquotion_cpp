// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkOAuth2_H
#define _C_CkOAuth2_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC void CkOAuth2_setAbortCheck(HCkOAuth2 cHandle, BOOL (*fnAbortCheck)());
CK_VISIBLE_PUBLIC void CkOAuth2_setPercentDone(HCkOAuth2 cHandle, BOOL (*fnPercentDone)(int pctDone));
CK_VISIBLE_PUBLIC void CkOAuth2_setProgressInfo(HCkOAuth2 cHandle, void (*fnProgressInfo)(const char *name, const char *value));
CK_VISIBLE_PUBLIC void CkOAuth2_setTaskCompleted(HCkOAuth2 cHandle, void (*fnTaskCompleted)(HCkTask hTask));

CK_VISIBLE_PUBLIC HCkOAuth2 CkOAuth2_Create(void);
CK_VISIBLE_PUBLIC void CkOAuth2_Dispose(HCkOAuth2 handle);
CK_VISIBLE_PUBLIC void CkOAuth2_getAccessToken(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkOAuth2_putAccessToken(HCkOAuth2 cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkOAuth2_accessToken(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getAccessTokenResponse(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkOAuth2_accessTokenResponse(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC int CkOAuth2_getAuthFlowState(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getAuthorizationEndpoint(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkOAuth2_putAuthorizationEndpoint(HCkOAuth2 cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkOAuth2_authorizationEndpoint(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getClientId(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkOAuth2_putClientId(HCkOAuth2 cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkOAuth2_clientId(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getClientSecret(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkOAuth2_putClientSecret(HCkOAuth2 cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkOAuth2_clientSecret(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC BOOL CkOAuth2_getCodeChallenge(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_putCodeChallenge(HCkOAuth2 cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkOAuth2_getCodeChallengeMethod(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkOAuth2_putCodeChallengeMethod(HCkOAuth2 cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkOAuth2_codeChallengeMethod(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getDebugLogFilePath(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkOAuth2_putDebugLogFilePath(HCkOAuth2 cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkOAuth2_debugLogFilePath(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getFailureInfo(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkOAuth2_failureInfo(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getLastErrorHtml(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkOAuth2_lastErrorHtml(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getLastErrorText(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkOAuth2_lastErrorText(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getLastErrorXml(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkOAuth2_lastErrorXml(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC BOOL CkOAuth2_getLastMethodSuccess(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_putLastMethodSuccess(HCkOAuth2 cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkOAuth2_getListenPort(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_putListenPort(HCkOAuth2 cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkOAuth2_getLocalHost(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkOAuth2_putLocalHost(HCkOAuth2 cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkOAuth2_localHost(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getRedirectAllowHtml(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkOAuth2_putRedirectAllowHtml(HCkOAuth2 cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkOAuth2_redirectAllowHtml(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getRedirectDenyHtml(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkOAuth2_putRedirectDenyHtml(HCkOAuth2 cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkOAuth2_redirectDenyHtml(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getRefreshToken(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkOAuth2_putRefreshToken(HCkOAuth2 cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkOAuth2_refreshToken(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getScope(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkOAuth2_putScope(HCkOAuth2 cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkOAuth2_scope(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getTokenEndpoint(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkOAuth2_putTokenEndpoint(HCkOAuth2 cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkOAuth2_tokenEndpoint(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_getTokenType(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkOAuth2_putTokenType(HCkOAuth2 cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkOAuth2_tokenType(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC BOOL CkOAuth2_getUtf8(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_putUtf8(HCkOAuth2 cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkOAuth2_getVerboseLogging(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC void CkOAuth2_putVerboseLogging(HCkOAuth2 cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkOAuth2_getVersion(HCkOAuth2 cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkOAuth2_version(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC BOOL CkOAuth2_Cancel(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC BOOL CkOAuth2_Monitor(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC HCkTask CkOAuth2_MonitorAsync(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC BOOL CkOAuth2_RefreshAccessToken(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC HCkTask CkOAuth2_RefreshAccessTokenAsync(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC BOOL CkOAuth2_SaveLastError(HCkOAuth2 cHandle, const char *path);
CK_VISIBLE_PUBLIC void CkOAuth2_SleepMs(HCkOAuth2 cHandle, int millisec);
CK_VISIBLE_PUBLIC BOOL CkOAuth2_StartAuth(HCkOAuth2 cHandle, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkOAuth2_startAuth(HCkOAuth2 cHandle);
CK_VISIBLE_PUBLIC BOOL CkOAuth2_UseConnection(HCkOAuth2 cHandle, HCkSocket sock);
#endif
