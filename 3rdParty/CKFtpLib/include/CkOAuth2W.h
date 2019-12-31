// CkOAuth2W.h: interface for the CkOAuth2W class.
//
//////////////////////////////////////////////////////////////////////

// This header is generated for Chilkat v9.5.0

#ifndef _CkOAuth2W_H
#define _CkOAuth2W_H
	
#include "chilkatDefs.h"

#include "CkString.h"
#include "CkClassWithCallbacksW.h"

class CkTaskW;
class CkSocketW;
class CkBaseProgressW;



#if !defined(__sun__) && !defined(__sun)
#pragma pack (push, 8)
#endif
 

// CLASS: CkOAuth2W
class CK_VISIBLE_PUBLIC CkOAuth2W  : public CkClassWithCallbacksW
{
    private:
	bool m_cbOwned;

	// Don't allow assignment or copying these objects.
	CkOAuth2W(const CkOAuth2W &);
	CkOAuth2W &operator=(const CkOAuth2W &);

    public:
	CkOAuth2W(void);
	virtual ~CkOAuth2W(void);

	static CkOAuth2W *createNew(void);
	

	CkOAuth2W(bool bCallbackOwned);
	static CkOAuth2W *createNew(bool bCallbackOwned);

	
	void CK_VISIBLE_PRIVATE inject(void *impl);

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	CkBaseProgressW *get_EventCallbackObject(void) const;
	void put_EventCallbackObject(CkBaseProgressW *progress);


	// BEGIN PUBLIC INTERFACE

	// ----------------------
	// Properties
	// ----------------------
	// When the OAuth2 three-legged authorization has successfully completed in the
	// background thread, this property contains the access_token.
	// 
	// For example, a successful Google API JSON response looks like this:
	//  {
	//              "access_token": "ya29.Ci9ZA-Z0Q7vtnch8xxxxxxxxxxxxxxgDVOOV97-IBvTt958xxxxxx1sasw",
	//              "token_type": "Bearer",
	// 
	//             "expires_in": 3600,
	// 
	//             "refresh_token": "1/fYjEVR-3Oq9xxxxxxxxxxxxxxLzPtlNOeQ"
	// }
	// 
	void get_AccessToken(CkString &str);
	// When the OAuth2 three-legged authorization has successfully completed in the
	// background thread, this property contains the access_token.
	// 
	// For example, a successful Google API JSON response looks like this:
	//  {
	//              "access_token": "ya29.Ci9ZA-Z0Q7vtnch8xxxxxxxxxxxxxxgDVOOV97-IBvTt958xxxxxx1sasw",
	//              "token_type": "Bearer",
	// 
	//             "expires_in": 3600,
	// 
	//             "refresh_token": "1/fYjEVR-3Oq9xxxxxxxxxxxxxxLzPtlNOeQ"
	// }
	// 
	const wchar_t *accessToken(void);
	// When the OAuth2 three-legged authorization has successfully completed in the
	// background thread, this property contains the access_token.
	// 
	// For example, a successful Google API JSON response looks like this:
	//  {
	//              "access_token": "ya29.Ci9ZA-Z0Q7vtnch8xxxxxxxxxxxxxxgDVOOV97-IBvTt958xxxxxx1sasw",
	//              "token_type": "Bearer",
	// 
	//             "expires_in": 3600,
	// 
	//             "refresh_token": "1/fYjEVR-3Oq9xxxxxxxxxxxxxxLzPtlNOeQ"
	// }
	// 
	void put_AccessToken(const wchar_t *newVal);

	// When the OAuth2 three-legged authorization has completed in the background
	// thread, this property contains the response that contains the access_token, the
	// optional refresh_token, and any other information included in the final
	// response. If the authorization was denied, then this contains the error
	// response.
	// 
	// For example, a successful JSON response for a Google API looks like this:
	//  {
	//              "access_token": "ya29.Ci9ZA-Z0Q7vtnch8xxxxxxxxxxxxxxgDVOOV97-IBvTt958xxxxxx1sasw",
	//              "token_type": "Bearer",
	// 
	//             "expires_in": 3600,
	// 
	//             "refresh_token": "1/fYjEVR-3Oq9xxxxxxxxxxxxxxLzPtlNOeQ"
	// }
	// 
	// Note: Not all responses are JSON. A successful Facebook response is plain text
	// and looks like this:
	// access_token=EAAZALuOC1wAwBAKH6FKnxOkjfEPOIkYUlabbliyskquOfVbSkgVM3lUFtsiZDCGmT1H8TidCKWUMbQ3cOU38CZAEd82vrdOayDBJ0lYqWDTVmCsO95SiiZCX09X2lAoP5eZAdZC1RIwRIXbn2UBZBhYD5hSVBETBx6AZD&expires=5134653
	// 
	void get_AccessTokenResponse(CkString &str);
	// When the OAuth2 three-legged authorization has completed in the background
	// thread, this property contains the response that contains the access_token, the
	// optional refresh_token, and any other information included in the final
	// response. If the authorization was denied, then this contains the error
	// response.
	// 
	// For example, a successful JSON response for a Google API looks like this:
	//  {
	//              "access_token": "ya29.Ci9ZA-Z0Q7vtnch8xxxxxxxxxxxxxxgDVOOV97-IBvTt958xxxxxx1sasw",
	//              "token_type": "Bearer",
	// 
	//             "expires_in": 3600,
	// 
	//             "refresh_token": "1/fYjEVR-3Oq9xxxxxxxxxxxxxxLzPtlNOeQ"
	// }
	// 
	// Note: Not all responses are JSON. A successful Facebook response is plain text
	// and looks like this:
	// access_token=EAAZALuOC1wAwBAKH6FKnxOkjfEPOIkYUlabbliyskquOfVbSkgVM3lUFtsiZDCGmT1H8TidCKWUMbQ3cOU38CZAEd82vrdOayDBJ0lYqWDTVmCsO95SiiZCX09X2lAoP5eZAdZC1RIwRIXbn2UBZBhYD5hSVBETBx6AZD&expires=5134653
	// 
	const wchar_t *accessTokenResponse(void);

	// Indicates the current progress of the OAuth2 three-legged authorization flow.
	// Possible values are:
	// 
	// 0: Idle. No OAuth2 has yet been attempted.
	// 1: Waiting for Redirect. The OAuth2 background thread is waiting to receive the
	// redirect HTTP request from the browser.
	// 2: Waiting for Final Response. The OAuth2 background thread is waiting for the
	// final access token response.
	// 3: Completed with Success. The OAuth2 flow has completed, the background thread
	// exited, and the successful JSON response is available in AccessTokenResponse
	// property.
	// 4: Completed with Access Denied. The OAuth2 flow has completed, the background
	// thread exited, and the error JSON is available in AccessTokenResponse property.
	// 5: Failed Prior to Completion. The OAuth2 flow failed to complete, the
	// background thread exited, and the error information is available in the
	// FailureInfo property.
	// 
	int get_AuthFlowState(void);

	// The URL used to obtain an authorization grant. For example, the Google APIs
	// authorization endpoint is "https://accounts.google.com/o/oauth2/v2/auth". (In
	// three-legged OAuth2, this is the very first point of contact that begins the
	// OAuth2 authentication flow.)
	void get_AuthorizationEndpoint(CkString &str);
	// The URL used to obtain an authorization grant. For example, the Google APIs
	// authorization endpoint is "https://accounts.google.com/o/oauth2/v2/auth". (In
	// three-legged OAuth2, this is the very first point of contact that begins the
	// OAuth2 authentication flow.)
	const wchar_t *authorizationEndpoint(void);
	// The URL used to obtain an authorization grant. For example, the Google APIs
	// authorization endpoint is "https://accounts.google.com/o/oauth2/v2/auth". (In
	// three-legged OAuth2, this is the very first point of contact that begins the
	// OAuth2 authentication flow.)
	void put_AuthorizationEndpoint(const wchar_t *newVal);

	// The "client_id" that identifies the application.
	// 
	// For example, if creating an app to use a Google API, one would create a client
	// ID by:
	//     Logging into the Google API Console (https://console.developers.google.com).
	//     Navigate to "Credentials".
	//     Click on "Create Credentials"
	//     Choose "OAuth client ID"
	//     Select the "Other" application type.
	//     Name your app and click "Create", and a client_id and client_secret will be
	//     generated.
	// Other API's, such as Facebook, should have something similar for generating a
	// client ID and client secret.
	// 
	void get_ClientId(CkString &str);
	// The "client_id" that identifies the application.
	// 
	// For example, if creating an app to use a Google API, one would create a client
	// ID by:
	//     Logging into the Google API Console (https://console.developers.google.com).
	//     Navigate to "Credentials".
	//     Click on "Create Credentials"
	//     Choose "OAuth client ID"
	//     Select the "Other" application type.
	//     Name your app and click "Create", and a client_id and client_secret will be
	//     generated.
	// Other API's, such as Facebook, should have something similar for generating a
	// client ID and client secret.
	// 
	const wchar_t *clientId(void);
	// The "client_id" that identifies the application.
	// 
	// For example, if creating an app to use a Google API, one would create a client
	// ID by:
	//     Logging into the Google API Console (https://console.developers.google.com).
	//     Navigate to "Credentials".
	//     Click on "Create Credentials"
	//     Choose "OAuth client ID"
	//     Select the "Other" application type.
	//     Name your app and click "Create", and a client_id and client_secret will be
	//     generated.
	// Other API's, such as Facebook, should have something similar for generating a
	// client ID and client secret.
	// 
	void put_ClientId(const wchar_t *newVal);

	// The "client_secret" for the application. Application credentials (i.e. what
	// identifies the application) consist of a client_id and client_secret. See the
	// ClientId property for more information.
	// 
	// Is the Client Secret Really a Secret?
	// 
	// This deserves some explanation. For a web-based application (where the code is
	// on the web server) and the user interacts with the application in a browser,
	// then YES, the client secret MUST be kept secret at all times. One does not want
	// to be interacting with a site that claims to be "Application XYZ" but is
	// actually an impersonator. But the Chilkat OAuth2 class is for desktop
	// applications and scripts (i.e. things that run on the local computer, not in a
	// browser).
	// 
	// Consider Mozilla Thunderbird. It is an application installed on your computer.
	// Thunderbird uses OAuth2 authentication for GMail accounts in the same way as
	// this OAuth2 API. When you add a GMail account and need to authenticate for the
	// 1st time, you'll get a popup window (a browser) where you interactively grant
	// authorization to Thunderbird. You implicitly know the Thunderbird application is
	// running because you started it. There can be no impersonation unless your
	// computer has already been hacked and when you thought you started Thunderbird,
	// you actually started some rogue app. But if you already started some rogue app,
	// then all has already been lost.
	// 
	// It is essentially impossible for desktop applications to embed a secret key
	// (such as the client secret) and assure confidentiality (i.e. that the key cannot
	// be obtained by some hacker. An application can hide the secret, and can make it
	// difficult to access, but in the end the secret cannot be assumed to be safe.
	// Therefore, the client_secret, for desktop (installed) applications is not
	// actually secret. One should still take care to shroud the client secret to some
	// extent, but know that whatever is done cannot be deemed secure. But this is OK.
	// The reason it is OK is that implicitly, when a person starts an application
	// (such as Thunderbird), the identity of the application is known. If a fake
	// Thunderbird was started, then all has already been lost. The security of the
	// system is in preventing the fake/rogue applications in the 1st place. If that
	// security has already been breached, then nothing else really matters.
	// 
	void get_ClientSecret(CkString &str);
	// The "client_secret" for the application. Application credentials (i.e. what
	// identifies the application) consist of a client_id and client_secret. See the
	// ClientId property for more information.
	// 
	// Is the Client Secret Really a Secret?
	// 
	// This deserves some explanation. For a web-based application (where the code is
	// on the web server) and the user interacts with the application in a browser,
	// then YES, the client secret MUST be kept secret at all times. One does not want
	// to be interacting with a site that claims to be "Application XYZ" but is
	// actually an impersonator. But the Chilkat OAuth2 class is for desktop
	// applications and scripts (i.e. things that run on the local computer, not in a
	// browser).
	// 
	// Consider Mozilla Thunderbird. It is an application installed on your computer.
	// Thunderbird uses OAuth2 authentication for GMail accounts in the same way as
	// this OAuth2 API. When you add a GMail account and need to authenticate for the
	// 1st time, you'll get a popup window (a browser) where you interactively grant
	// authorization to Thunderbird. You implicitly know the Thunderbird application is
	// running because you started it. There can be no impersonation unless your
	// computer has already been hacked and when you thought you started Thunderbird,
	// you actually started some rogue app. But if you already started some rogue app,
	// then all has already been lost.
	// 
	// It is essentially impossible for desktop applications to embed a secret key
	// (such as the client secret) and assure confidentiality (i.e. that the key cannot
	// be obtained by some hacker. An application can hide the secret, and can make it
	// difficult to access, but in the end the secret cannot be assumed to be safe.
	// Therefore, the client_secret, for desktop (installed) applications is not
	// actually secret. One should still take care to shroud the client secret to some
	// extent, but know that whatever is done cannot be deemed secure. But this is OK.
	// The reason it is OK is that implicitly, when a person starts an application
	// (such as Thunderbird), the identity of the application is known. If a fake
	// Thunderbird was started, then all has already been lost. The security of the
	// system is in preventing the fake/rogue applications in the 1st place. If that
	// security has already been breached, then nothing else really matters.
	// 
	const wchar_t *clientSecret(void);
	// The "client_secret" for the application. Application credentials (i.e. what
	// identifies the application) consist of a client_id and client_secret. See the
	// ClientId property for more information.
	// 
	// Is the Client Secret Really a Secret?
	// 
	// This deserves some explanation. For a web-based application (where the code is
	// on the web server) and the user interacts with the application in a browser,
	// then YES, the client secret MUST be kept secret at all times. One does not want
	// to be interacting with a site that claims to be "Application XYZ" but is
	// actually an impersonator. But the Chilkat OAuth2 class is for desktop
	// applications and scripts (i.e. things that run on the local computer, not in a
	// browser).
	// 
	// Consider Mozilla Thunderbird. It is an application installed on your computer.
	// Thunderbird uses OAuth2 authentication for GMail accounts in the same way as
	// this OAuth2 API. When you add a GMail account and need to authenticate for the
	// 1st time, you'll get a popup window (a browser) where you interactively grant
	// authorization to Thunderbird. You implicitly know the Thunderbird application is
	// running because you started it. There can be no impersonation unless your
	// computer has already been hacked and when you thought you started Thunderbird,
	// you actually started some rogue app. But if you already started some rogue app,
	// then all has already been lost.
	// 
	// It is essentially impossible for desktop applications to embed a secret key
	// (such as the client secret) and assure confidentiality (i.e. that the key cannot
	// be obtained by some hacker. An application can hide the secret, and can make it
	// difficult to access, but in the end the secret cannot be assumed to be safe.
	// Therefore, the client_secret, for desktop (installed) applications is not
	// actually secret. One should still take care to shroud the client secret to some
	// extent, but know that whatever is done cannot be deemed secure. But this is OK.
	// The reason it is OK is that implicitly, when a person starts an application
	// (such as Thunderbird), the identity of the application is known. If a fake
	// Thunderbird was started, then all has already been lost. The security of the
	// system is in preventing the fake/rogue applications in the 1st place. If that
	// security has already been breached, then nothing else really matters.
	// 
	void put_ClientSecret(const wchar_t *newVal);

	// Optional. Set this to true to send a code_challenge (as per RFC 7636) with the
	// authorization request. The default value is false.
	bool get_CodeChallenge(void);
	// Optional. Set this to true to send a code_challenge (as per RFC 7636) with the
	// authorization request. The default value is false.
	void put_CodeChallenge(bool newVal);

	// Optional. Only applies when the CodeChallenge property is set to true.
	// Possible values are "plain" or "S256". The default is "S256".
	void get_CodeChallengeMethod(CkString &str);
	// Optional. Only applies when the CodeChallenge property is set to true.
	// Possible values are "plain" or "S256". The default is "S256".
	const wchar_t *codeChallengeMethod(void);
	// Optional. Only applies when the CodeChallenge property is set to true.
	// Possible values are "plain" or "S256". The default is "S256".
	void put_CodeChallengeMethod(const wchar_t *newVal);

	// If the OAuth2 three-legged authorization failed prior to completion (the
	// AuthFlowState = 5), then information about the failure is contained in this
	// property. This property is automatically cleared when OAuth2 authorization
	// starts (i.e. when StartAuth is called).
	void get_FailureInfo(CkString &str);
	// If the OAuth2 three-legged authorization failed prior to completion (the
	// AuthFlowState = 5), then information about the failure is contained in this
	// property. This property is automatically cleared when OAuth2 authorization
	// starts (i.e. when StartAuth is called).
	const wchar_t *failureInfo(void);

	// The port number to listen for the redirect URI request sent by the browser. If
	// set to 0, then a random unused port is used. The default value of this property
	// is 0.
	// 
	// In most cases, using a random unused port is the best choice. In some OAuth2
	// situations, such as with Facebook, a specific port number must be chosen. This
	// is due to the fact that Facebook requires an APP to have a Site URL, which must
	// exactly match the redirect_uri used in OAuth2 authorization. For example, the
	// Facebook Site URL might be "http://localhost:3017/" if port 3017 is the listen
	// port.
	// 
	int get_ListenPort(void);
	// The port number to listen for the redirect URI request sent by the browser. If
	// set to 0, then a random unused port is used. The default value of this property
	// is 0.
	// 
	// In most cases, using a random unused port is the best choice. In some OAuth2
	// situations, such as with Facebook, a specific port number must be chosen. This
	// is due to the fact that Facebook requires an APP to have a Site URL, which must
	// exactly match the redirect_uri used in OAuth2 authorization. For example, the
	// Facebook Site URL might be "http://localhost:3017/" if port 3017 is the listen
	// port.
	// 
	void put_ListenPort(int newVal);

	// Defaults to "localhost". This should typically remain at the default value. It
	// is the loopback domain or IP address used for the redirect_uri. For example,
	// "http://localhost:2012/". (assuming 2012 was used or randomly chosen as the
	// listen port number) If the desired redirect_uri is to be
	// "http://127.0.0.1:2012/", then set this property equal to "127.0.0.1".
	void get_LocalHost(CkString &str);
	// Defaults to "localhost". This should typically remain at the default value. It
	// is the loopback domain or IP address used for the redirect_uri. For example,
	// "http://localhost:2012/". (assuming 2012 was used or randomly chosen as the
	// listen port number) If the desired redirect_uri is to be
	// "http://127.0.0.1:2012/", then set this property equal to "127.0.0.1".
	const wchar_t *localHost(void);
	// Defaults to "localhost". This should typically remain at the default value. It
	// is the loopback domain or IP address used for the redirect_uri. For example,
	// "http://localhost:2012/". (assuming 2012 was used or randomly chosen as the
	// listen port number) If the desired redirect_uri is to be
	// "http://127.0.0.1:2012/", then set this property equal to "127.0.0.1".
	void put_LocalHost(const wchar_t *newVal);

	// The HTML returned to the browser when access is allowed by the end-user. The
	// default value is HTMl that contains a META refresh to
	// https://www.chilkatsoft.com/oauth2_allowed.html. Your application should set
	// this property to display whatever HTML is desired when access is granted.
	void get_RedirectAllowHtml(CkString &str);
	// The HTML returned to the browser when access is allowed by the end-user. The
	// default value is HTMl that contains a META refresh to
	// https://www.chilkatsoft.com/oauth2_allowed.html. Your application should set
	// this property to display whatever HTML is desired when access is granted.
	const wchar_t *redirectAllowHtml(void);
	// The HTML returned to the browser when access is allowed by the end-user. The
	// default value is HTMl that contains a META refresh to
	// https://www.chilkatsoft.com/oauth2_allowed.html. Your application should set
	// this property to display whatever HTML is desired when access is granted.
	void put_RedirectAllowHtml(const wchar_t *newVal);

	// The HTML returned to the browser when access is denied by the end-user. The
	// default value is HTMl that contains a META refresh to
	// https://www.chilkatsoft.com/oauth2_denied.html. Your application should set this
	// property to display whatever HTML is desired when access is denied.
	void get_RedirectDenyHtml(CkString &str);
	// The HTML returned to the browser when access is denied by the end-user. The
	// default value is HTMl that contains a META refresh to
	// https://www.chilkatsoft.com/oauth2_denied.html. Your application should set this
	// property to display whatever HTML is desired when access is denied.
	const wchar_t *redirectDenyHtml(void);
	// The HTML returned to the browser when access is denied by the end-user. The
	// default value is HTMl that contains a META refresh to
	// https://www.chilkatsoft.com/oauth2_denied.html. Your application should set this
	// property to display whatever HTML is desired when access is denied.
	void put_RedirectDenyHtml(const wchar_t *newVal);

	// When the OAuth2 three-legged authorization has successfully completed in the
	// background thread, this property contains the refresh_token, if present.
	// 
	// For example, a successful Google API JSON response looks like this:
	//  {
	//              "access_token": "ya29.Ci9ZA-Z0Q7vtnch8xxxxxxxxxxxxxxgDVOOV97-IBvTt958xxxxxx1sasw",
	//              "token_type": "Bearer",
	// 
	//             "expires_in": 3600,
	// 
	//             "refresh_token": "1/fYjEVR-3Oq9xxxxxxxxxxxxxxLzPtlNOeQ"
	// }
	// 
	void get_RefreshToken(CkString &str);
	// When the OAuth2 three-legged authorization has successfully completed in the
	// background thread, this property contains the refresh_token, if present.
	// 
	// For example, a successful Google API JSON response looks like this:
	//  {
	//              "access_token": "ya29.Ci9ZA-Z0Q7vtnch8xxxxxxxxxxxxxxgDVOOV97-IBvTt958xxxxxx1sasw",
	//              "token_type": "Bearer",
	// 
	//             "expires_in": 3600,
	// 
	//             "refresh_token": "1/fYjEVR-3Oq9xxxxxxxxxxxxxxLzPtlNOeQ"
	// }
	// 
	const wchar_t *refreshToken(void);
	// When the OAuth2 three-legged authorization has successfully completed in the
	// background thread, this property contains the refresh_token, if present.
	// 
	// For example, a successful Google API JSON response looks like this:
	//  {
	//              "access_token": "ya29.Ci9ZA-Z0Q7vtnch8xxxxxxxxxxxxxxgDVOOV97-IBvTt958xxxxxx1sasw",
	//              "token_type": "Bearer",
	// 
	//             "expires_in": 3600,
	// 
	//             "refresh_token": "1/fYjEVR-3Oq9xxxxxxxxxxxxxxLzPtlNOeQ"
	// }
	// 
	void put_RefreshToken(const wchar_t *newVal);

	// This is an optional setting that defines the scope of access. For example,
	// Google API scopes are listed here:
	// https://developers.google.com/identity/protocols/googlescopes
	// 
	// For example, if wishing to grant OAuth2 authorization for Google Drive, one
	// would set this property to "https://www.googleapis.com/auth/drive".
	// 
	void get_Scope(CkString &str);
	// This is an optional setting that defines the scope of access. For example,
	// Google API scopes are listed here:
	// https://developers.google.com/identity/protocols/googlescopes
	// 
	// For example, if wishing to grant OAuth2 authorization for Google Drive, one
	// would set this property to "https://www.googleapis.com/auth/drive".
	// 
	const wchar_t *scope(void);
	// This is an optional setting that defines the scope of access. For example,
	// Google API scopes are listed here:
	// https://developers.google.com/identity/protocols/googlescopes
	// 
	// For example, if wishing to grant OAuth2 authorization for Google Drive, one
	// would set this property to "https://www.googleapis.com/auth/drive".
	// 
	void put_Scope(const wchar_t *newVal);

	// The URL for exchanging an authorization grant for an access token. For example,
	// the Google APIs token endpoint is "https://www.googleapis.com/oauth2/v4/token".
	// (In three-legged OAuth2, this is the very last point of contact that ends the
	// OAuth2 authentication flow.)
	void get_TokenEndpoint(CkString &str);
	// The URL for exchanging an authorization grant for an access token. For example,
	// the Google APIs token endpoint is "https://www.googleapis.com/oauth2/v4/token".
	// (In three-legged OAuth2, this is the very last point of contact that ends the
	// OAuth2 authentication flow.)
	const wchar_t *tokenEndpoint(void);
	// The URL for exchanging an authorization grant for an access token. For example,
	// the Google APIs token endpoint is "https://www.googleapis.com/oauth2/v4/token".
	// (In three-legged OAuth2, this is the very last point of contact that ends the
	// OAuth2 authentication flow.)
	void put_TokenEndpoint(const wchar_t *newVal);

	// When the OAuth2 three-legged authorization has successfully completed in the
	// background thread, this property contains the token_type, if present.
	// 
	// A successful Google API JSON response looks like this:
	//  {
	//              "access_token": "ya29.Ci9ZA-Z0Q7vtnch8xxxxxxxxxxxxxxgDVOOV97-IBvTt958xxxxxx1sasw",
	//              "token_type": "Bearer",
	// 
	//             "expires_in": 3600,
	// 
	//             "refresh_token": "1/fYjEVR-3Oq9xxxxxxxxxxxxxxLzPtlNOeQ"
	// }
	// 
	// Note: Some responses may not included a "token_type" param. In that case, this
	// property will remain empty.
	// 
	void get_TokenType(CkString &str);
	// When the OAuth2 three-legged authorization has successfully completed in the
	// background thread, this property contains the token_type, if present.
	// 
	// A successful Google API JSON response looks like this:
	//  {
	//              "access_token": "ya29.Ci9ZA-Z0Q7vtnch8xxxxxxxxxxxxxxgDVOOV97-IBvTt958xxxxxx1sasw",
	//              "token_type": "Bearer",
	// 
	//             "expires_in": 3600,
	// 
	//             "refresh_token": "1/fYjEVR-3Oq9xxxxxxxxxxxxxxLzPtlNOeQ"
	// }
	// 
	// Note: Some responses may not included a "token_type" param. In that case, this
	// property will remain empty.
	// 
	const wchar_t *tokenType(void);
	// When the OAuth2 three-legged authorization has successfully completed in the
	// background thread, this property contains the token_type, if present.
	// 
	// A successful Google API JSON response looks like this:
	//  {
	//              "access_token": "ya29.Ci9ZA-Z0Q7vtnch8xxxxxxxxxxxxxxgDVOOV97-IBvTt958xxxxxx1sasw",
	//              "token_type": "Bearer",
	// 
	//             "expires_in": 3600,
	// 
	//             "refresh_token": "1/fYjEVR-3Oq9xxxxxxxxxxxxxxLzPtlNOeQ"
	// }
	// 
	// Note: Some responses may not included a "token_type" param. In that case, this
	// property will remain empty.
	// 
	void put_TokenType(const wchar_t *newVal);



	// ----------------------
	// Methods
	// ----------------------
	// Cancels an OAuth2 authorization flow that is in progress.
	bool Cancel(void);

	// Monitors an already started OAuth2 authorization flow and returns when it is
	// finished.
	bool Monitor(void);

	// Creates an asynchronous task to call the Monitor method with the arguments
	// provided. (Async methods are available starting in Chilkat v9.5.0.52.)
	// The caller is responsible for deleting the object returned by this method.
	CkTaskW *MonitorAsync(void);

	// Sends a refresh request to the token endpoint to obtain a new access token.
	// After a successful refresh request, the AccessToken and RefreshToken properties
	// will be updated with new values.
	// 
	// Note: This method can only be called if the ClientId, ClientSecret, RefreshToken
	// and TokenEndpoint properties contain valid values.
	// 
	bool RefreshAccessToken(void);

	// Creates an asynchronous task to call the RefreshAccessToken method with the
	// arguments provided. (Async methods are available starting in Chilkat v9.5.0.52.)
	// The caller is responsible for deleting the object returned by this method.
	CkTaskW *RefreshAccessTokenAsync(void);

	// Convenience method to force the calling thread to sleep for a number of
	// milliseconds.
	void SleepMs(int millisec);

	// Initiates the three-legged OAuth2 flow. The various properties, such as
	// ClientId, ClientSecret, Scope, CodeChallenge, AuthorizationEndpoint, and
	// TokenEndpoint, should be set prior to calling this method.
	// 
	// This method does two things:
	//     Forms and returns a URL that is to be loaded in a browser.
	//     Starts a background thread that listens on a randomly selected unused port
	//     to receive the redirect request from the browser. The receiving of the request
	//     from the browser, and the sending of the HTTP request to complete the
	//     three-legged OAuth2 flow is done entirely in the background thread. The
	//     application controls this behavior by setting the various properties beforehand.
	// The return value is the URL to be loaded (navigated to) in a popup or embedded
	// browser.
	// 
	bool StartAuth(CkString &outStr);
	// Initiates the three-legged OAuth2 flow. The various properties, such as
	// ClientId, ClientSecret, Scope, CodeChallenge, AuthorizationEndpoint, and
	// TokenEndpoint, should be set prior to calling this method.
	// 
	// This method does two things:
	//     Forms and returns a URL that is to be loaded in a browser.
	//     Starts a background thread that listens on a randomly selected unused port
	//     to receive the redirect request from the browser. The receiving of the request
	//     from the browser, and the sending of the HTTP request to complete the
	//     three-legged OAuth2 flow is done entirely in the background thread. The
	//     application controls this behavior by setting the various properties beforehand.
	// The return value is the URL to be loaded (navigated to) in a popup or embedded
	// browser.
	// 
	const wchar_t *startAuth(void);

	// Calling this method is optional, and is only required if a proxy (HTTP or
	// SOCKS), an SSH tunnel, or if special connection related socket options need to
	// be used. When UseConnection is not called, the connection to the token endpoint
	// is a direct connection using TLS (or not) based on the TokenEndpoint. (If the
	// TokenEndpoint begins with "https://", then TLS is used.)
	// 
	// This method sets the socket object to be used for sending the requests to the
	// token endpoint in the background thread. The sock can be an already-connected
	// socket, or a socket object that is not yet connected. In some cases, such as for
	// a connection through an SSH tunnel, the sock must already be connected. In other
	// cases, an unconnected sock can be provided because the purpose for providing the
	// socket object is to specify settings such as for HTTP or SOCKS proxies.
	// 
	bool UseConnection(CkSocketW &sock);





	// END PUBLIC INTERFACE


};
#if !defined(__sun__) && !defined(__sun)
#pragma pack (pop)
#endif


	
#endif
