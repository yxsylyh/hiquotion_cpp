// CkRest.h: interface for the CkRest class.
//
//////////////////////////////////////////////////////////////////////

// This header is generated for Chilkat v9.5.0

#ifndef _CkRest_H
#define _CkRest_H
	
#include "chilkatDefs.h"

#include "CkString.h"
#include "CkClassWithCallbacks.h"

class CkStringBuilder;
class CkTask;
class CkBinData;
class CkByteData;
class CkStream;
class CkUrl;
class CkAuthAws;
class CkAuthAzureAD;
class CkAuthAzureSAS;
class CkAuthAzureStorage;
class CkAuthGoogle;
class CkOAuth1;
class CkOAuth2;
class CkSocket;
class CkBaseProgress;



#if !defined(__sun__) && !defined(__sun)
#pragma pack (push, 8)
#endif
 

// CLASS: CkRest
class CK_VISIBLE_PUBLIC CkRest  : public CkClassWithCallbacks
{
    private:

	// Don't allow assignment or copying these objects.
	CkRest(const CkRest &);
	CkRest &operator=(const CkRest &);

    public:
	CkRest(void);
	virtual ~CkRest(void);

	static CkRest *createNew(void);
	void CK_VISIBLE_PRIVATE inject(void *impl);

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	CkBaseProgress *get_EventCallbackObject(void) const;
	void put_EventCallbackObject(CkBaseProgress *progress);


	// BEGIN PUBLIC INTERFACE

	// ----------------------
	// Properties
	// ----------------------
	// If this property is set to false, then no MIME header folding will be
	// automatically applied to any request header. The default is true. This
	// property is provided to satisfy certain providers, such as Quickbooks, that
	// require all MIME headers to be single unfolded lines regardless of length.
	bool get_AllowHeaderFolding(void);
	// If this property is set to false, then no MIME header folding will be
	// automatically applied to any request header. The default is true. This
	// property is provided to satisfy certain providers, such as Quickbooks, that
	// require all MIME headers to be single unfolded lines regardless of length.
	void put_AllowHeaderFolding(bool newVal);

	// Controls whether non us-ascii HTTP request headers are automatically Q/B
	// encoded. The default value is true.
	// 
	// Q/B encoded headers explicitly indicate the charset and byte representation, and
	// appear as such: =?utf-8?Q?...?= or =?utf-8?B?...?=, where the charset may be
	// "utf-8" or any other possible charset.
	// 
	// If this property is set to false, then no Q/B encoding is applied to any
	// request header.
	// 
	bool get_AllowHeaderQB(void);
	// Controls whether non us-ascii HTTP request headers are automatically Q/B
	// encoded. The default value is true.
	// 
	// Q/B encoded headers explicitly indicate the charset and byte representation, and
	// appear as such: =?utf-8?Q?...?= or =?utf-8?B?...?=, where the charset may be
	// "utf-8" or any other possible charset.
	// 
	// If this property is set to false, then no Q/B encoding is applied to any
	// request header.
	// 
	void put_AllowHeaderQB(bool newVal);

	// The value of the Authorization HTTP request header (if needed).
	void get_Authorization(CkString &str);
	// The value of the Authorization HTTP request header (if needed).
	const char *authorization(void);
	// The value of the Authorization HTTP request header (if needed).
	void put_Authorization(const char *newVal);

	// If the Connect method fails, this property can be checked to determine the
	// reason for failure.
	// 
	// Possible values are:
	// 0 = success
	// 
	// Normal (non-SSL) sockets:
	// 1 = empty hostname
	// 2 = DNS lookup failed
	// 3 = DNS timeout
	// 4 = Aborted by application.
	// 5 = Internal failure.
	// 6 = Connect Timed Out
	// 7 = Connect Rejected (or failed for some other reason)
	// 
	// SSL/TLS:
	// 100 = TLS internal error.
	// 101 = Failed to send client hello.
	// 102 = Unexpected handshake message.
	// 103 = Failed to read server hello.
	// 104 = No server certificate.
	// 105 = Unexpected TLS protocol version.
	// 106 = Server certificate verify failed (the server certificate is expired or the cert's signature verification failed).
	// 107 = Unacceptable TLS protocol version.
	// 109 = Failed to read handshake messages.
	// 110 = Failed to send client certificate handshake message.
	// 111 = Failed to send client key exchange handshake message.
	// 112 = Client certificate's private key not accessible.
	// 113 = Failed to send client cert verify handshake message.
	// 114 = Failed to send change cipher spec handshake message.
	// 115 = Failed to send finished handshake message.
	// 116 = Server's Finished message is invalid.
	// 
	int get_ConnectFailReason(void);

	// This property is only valid in programming environment and languages that allow
	// for event callbacks.
	// 
	// Specifies the time interval in milliseconds between AbortCheck events. A value
	// of 0 (the default) indicate that no AbortCheck events will fire. Any REST method
	// can be aborted via the AbortCheck event.
	// 
	int get_HeartbeatMs(void);
	// This property is only valid in programming environment and languages that allow
	// for event callbacks.
	// 
	// Specifies the time interval in milliseconds between AbortCheck events. A value
	// of 0 (the default) indicate that no AbortCheck events will fire. Any REST method
	// can be aborted via the AbortCheck event.
	// 
	void put_HeartbeatMs(int newVal);

	// The value of the Host HTTP request header.
	void get_Host(CkString &str);
	// The value of the Host HTTP request header.
	const char *host(void);
	// The value of the Host HTTP request header.
	void put_Host(const char *newVal);

	// The maximum amount of time to wait for additional incoming data when receiving,
	// or the max time to wait to send additional data. The default value is 30000 (30
	// seconds). This is not an overall max timeout. Rather, it is the maximum time to
	// wait when receiving or sending has halted.
	int get_IdleTimeoutMs(void);
	// The maximum amount of time to wait for additional incoming data when receiving,
	// or the max time to wait to send additional data. The default value is 30000 (30
	// seconds). This is not an overall max timeout. Rather, it is the maximum time to
	// wait when receiving or sending has halted.
	void put_IdleTimeoutMs(int newVal);

	// The full MIME header (not including the HTTP start line which contains the
	// status code and status text), of the last request sent.
	void get_LastRequestHeader(CkString &str);
	// The full MIME header (not including the HTTP start line which contains the
	// status code and status text), of the last request sent.
	const char *lastRequestHeader(void);

	// The full start line of the last request sent. (The start line begins with the
	// HTTP verb, such as GET, POST, etc., is followed by the URI path, and ends with
	// the HTTP version.)
	void get_LastRequestStartLine(CkString &str);
	// The full start line of the last request sent. (The start line begins with the
	// HTTP verb, such as GET, POST, etc., is followed by the URI path, and ends with
	// the HTTP version.)
	const char *lastRequestStartLine(void);

	// The number of response header fields. The first response header field is at
	// index 0.
	int get_NumResponseHeaders(void);

	// Only used for multipart requests. Selects the target MIME part for calls to
	// AddHeader, RemoveHeader, SetMultipartBodyBinary, SetMultipartBodyString,
	// SetMultipartBodyStream, etc. The default is an empty string and indicates the
	// top-level header. A string value of "1" would indicate the 1st sub-part in a
	// multipart request. A string value of "1.2" would indicate the 2nd sub-part under
	// the 1st sub-part.
	// 
	// It is unlikely you'll ever encounter the need for nested multipart requests
	// (i.e. part selectors such as "1.2") Also, most REST requests are NOT multipart,
	// and therefore this feature is rarely used. An example of a multipart REST
	// request would be for a Google Drive upload, where the top-level Content-Type is
	// multipart/related, the1st sub-part contains the JSON meta-data, and the 2nd
	// sub-part contains the file data.
	// 
	void get_PartSelector(CkString &str);
	// Only used for multipart requests. Selects the target MIME part for calls to
	// AddHeader, RemoveHeader, SetMultipartBodyBinary, SetMultipartBodyString,
	// SetMultipartBodyStream, etc. The default is an empty string and indicates the
	// top-level header. A string value of "1" would indicate the 1st sub-part in a
	// multipart request. A string value of "1.2" would indicate the 2nd sub-part under
	// the 1st sub-part.
	// 
	// It is unlikely you'll ever encounter the need for nested multipart requests
	// (i.e. part selectors such as "1.2") Also, most REST requests are NOT multipart,
	// and therefore this feature is rarely used. An example of a multipart REST
	// request would be for a Google Drive upload, where the top-level Content-Type is
	// multipart/related, the1st sub-part contains the JSON meta-data, and the 2nd
	// sub-part contains the file data.
	// 
	const char *partSelector(void);
	// Only used for multipart requests. Selects the target MIME part for calls to
	// AddHeader, RemoveHeader, SetMultipartBodyBinary, SetMultipartBodyString,
	// SetMultipartBodyStream, etc. The default is an empty string and indicates the
	// top-level header. A string value of "1" would indicate the 1st sub-part in a
	// multipart request. A string value of "1.2" would indicate the 2nd sub-part under
	// the 1st sub-part.
	// 
	// It is unlikely you'll ever encounter the need for nested multipart requests
	// (i.e. part selectors such as "1.2") Also, most REST requests are NOT multipart,
	// and therefore this feature is rarely used. An example of a multipart REST
	// request would be for a Google Drive upload, where the top-level Content-Type is
	// multipart/related, the1st sub-part contains the JSON meta-data, and the 2nd
	// sub-part contains the file data.
	// 
	void put_PartSelector(const char *newVal);

	// This property only applies to the FullRequest* methods, which are methods that
	// both send an HTTP request and receive the response. (It also only applies to
	// programming languages that support event callbacks.) It determines whether
	// percentage completion is tracked for the sending of the HTTP request, or for the
	// downloading the HTTP response. The default value is false, which is to measure
	// the percent completion when receiving the response.
	// 
	// For example: If the REST request is to download a file, then this property
	// should remain at the default value of false. If the REST request is to upload
	// a file (using a Full* method), then set this property to true. Also note if a
	// server sends an HTTP response in the chunked encoding, it is not possible to
	// measure percent completion because the HTTP client has no way of knowing the
	// total size of the HTTP response.
	// 
	bool get_PercentDoneOnSend(void);
	// This property only applies to the FullRequest* methods, which are methods that
	// both send an HTTP request and receive the response. (It also only applies to
	// programming languages that support event callbacks.) It determines whether
	// percentage completion is tracked for the sending of the HTTP request, or for the
	// downloading the HTTP response. The default value is false, which is to measure
	// the percent completion when receiving the response.
	// 
	// For example: If the REST request is to download a file, then this property
	// should remain at the default value of false. If the REST request is to upload
	// a file (using a Full* method), then set this property to true. Also note if a
	// server sends an HTTP response in the chunked encoding, it is not possible to
	// measure percent completion because the HTTP client has no way of knowing the
	// total size of the HTTP response.
	// 
	void put_PercentDoneOnSend(bool newVal);

	// The full response MIME header (not including the HTTP start line which contains
	// the status code and status text).
	void get_ResponseHeader(CkString &str);
	// The full response MIME header (not including the HTTP start line which contains
	// the status code and status text).
	const char *responseHeader(void);

	// The response status code.
	int get_ResponseStatusCode(void);

	// The status message corresponding to the response status code.
	void get_ResponseStatusText(CkString &str);
	// The status message corresponding to the response status code.
	const char *responseStatusText(void);

	// If true, then methods that upload data are sent non-chunked if possible. For
	// example, if the FullRequestStream method is called where the stream is a file
	// stream, then the size of the content is known and the HTTP request will be sent
	// using a Content-Length header instead of using a Transfer-Encoding: chunked
	// upload. If false, then the chunked transfer encoding is used. The default
	// value of this property is true.
	bool get_StreamNonChunked(void);
	// If true, then methods that upload data are sent non-chunked if possible. For
	// example, if the FullRequestStream method is called where the stream is a file
	// stream, then the size of the content is known and the HTTP request will be sent
	// using a Content-Length header instead of using a Transfer-Encoding: chunked
	// upload. If false, then the chunked transfer encoding is used. The default
	// value of this property is true.
	void put_StreamNonChunked(bool newVal);



	// ----------------------
	// Methods
	// ----------------------
	// Adds an HTTP request header. If the header field already exists, then it is
	// replaced.
	bool AddHeader(const char *name, const char *value);


	// Adds a query parameter. If the query parameter already exists, then it is
	// replaced.
	bool AddQueryParam(const char *name, const char *value);


	// Adds the query parameters from the queryString. The queryString is a query string of the
	// format field1=value1&field2=value2&field3=value3... where each value is URL
	// encoded.
	bool AddQueryParams(const char *queryString);


	// Adds a query parameter. If the query parameter already exists, then it is
	// replaced. The parameter value is passed in a StringBuilder object.
	bool AddQueryParamSb(const char *name, CkStringBuilder &value);


	// Removes all HTTP request headers.
	bool ClearAllHeaders(void);


	// Removes all sub-parts from a request. This is useful when preparing the REST
	// object to send a new request after a multipart request has just been sent.
	bool ClearAllParts(void);


	// Clears all query parameters.
	bool ClearAllQueryParams(void);


	// Clears the response body stream set by calling SetResponseBodyStream.
	void ClearResponseBodyStream(void);


	// Establishes an initial connection to a REST server. The hostname can be a domain
	// name or an IP address. Both IPv4 and IPv6 addresses are supported. The port is
	// the port, which is typically 80 or 443. If SSL/TLS is required, then tls should
	// be set to true. The autoReconnect indicates whether connection should automatically be
	// established as needed for subsequent REST requests.
	// 
	// Note: This method is for simple connections that do not require any proxies
	// (HTTP or SOCKS), or SSH tunneling. If a proxy, SSH tunnel, or any other advanced
	// socket feature is required, the Chilkat Socket API can be used to establish the
	// connection. The UseConnection method can then be called to use the
	// pre-established socket connection.
	// 
	bool Connect(const char *hostname, int port, bool tls, bool autoReconnect);

	// Establishes an initial connection to a REST server. The hostname can be a domain
	// name or an IP address. Both IPv4 and IPv6 addresses are supported. The port is
	// the port, which is typically 80 or 443. If SSL/TLS is required, then tls should
	// be set to true. The autoReconnect indicates whether connection should automatically be
	// established as needed for subsequent REST requests.
	// 
	// Note: This method is for simple connections that do not require any proxies
	// (HTTP or SOCKS), or SSH tunneling. If a proxy, SSH tunnel, or any other advanced
	// socket feature is required, the Chilkat Socket API can be used to establish the
	// connection. The UseConnection method can then be called to use the
	// pre-established socket connection.
	// 
	CkTask *ConnectAsync(const char *hostname, int port, bool tls, bool autoReconnect);


	// Closes the connection with the HTTP server if one is open. This method can be
	// called to ensure the connection is closed. The maxWaitMs is the maximum time in
	// milliseconds to wait for a clean close. If the connection is through an SSH
	// tunnel, this closes the logical channel within the SSH tunnel, and not the
	// connection with the SSH server itself.
	bool Disconnect(int maxWaitMs);

	// Closes the connection with the HTTP server if one is open. This method can be
	// called to ensure the connection is closed. The maxWaitMs is the maximum time in
	// milliseconds to wait for a clean close. If the connection is through an SSH
	// tunnel, this closes the logical channel within the SSH tunnel, and not the
	// connection with the SSH server itself.
	CkTask *DisconnectAsync(int maxWaitMs);


	// Sends a complete REST request (header + binary body) and receives the full
	// response. The binary body of the request is passed in binData. The response body is
	// returned in responseBody (replacing whatever contents responseBody may have previously held).
	bool FullRequestBd(const char *httpVerb, const char *uriPath, CkBinData &binData, CkStringBuilder &responseBody);

	// Sends a complete REST request (header + binary body) and receives the full
	// response. The binary body of the request is passed in binData. The response body is
	// returned in responseBody (replacing whatever contents responseBody may have previously held).
	CkTask *FullRequestBdAsync(const char *httpVerb, const char *uriPath, CkBinData &binData, CkStringBuilder &responseBody);


	// Sends a complete REST request (header + body) and receives the full response. It
	// is assumed that the request body is binary, and the response body is a string
	// (such as JSON or XML). The response body is returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqBinaryBody, ReadResponseHeader, ReadRespBodyString.
	// 
	bool FullRequestBinary(const char *httpVerb, const char *uriPath, CkByteData &bodyBytes, CkString &outStr);

	// Sends a complete REST request (header + body) and receives the full response. It
	// is assumed that the request body is binary, and the response body is a string
	// (such as JSON or XML). The response body is returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqBinaryBody, ReadResponseHeader, ReadRespBodyString.
	// 
	const char *fullRequestBinary(const char *httpVerb, const char *uriPath, CkByteData &bodyBytes);
	// Sends a complete REST request (header + body) and receives the full response. It
	// is assumed that the request body is binary, and the response body is a string
	// (such as JSON or XML). The response body is returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqBinaryBody, ReadResponseHeader, ReadRespBodyString.
	// 
	CkTask *FullRequestBinaryAsync(const char *httpVerb, const char *uriPath, CkByteData &bodyBytes);


	// Sends a complete application/x-www-form-urlencoded HTTP request and receives the
	// full response. The request body is composed of the URL encoded query params. It
	// is assumed that the response body is a string (such as JSON or XML). The
	// response body is returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqFormUrlEncoded, ReadResponseHeader, ReadRespBodyString.
	// 
	bool FullRequestFormUrlEncoded(const char *httpVerb, const char *uriPath, CkString &outStr);

	// Sends a complete application/x-www-form-urlencoded HTTP request and receives the
	// full response. The request body is composed of the URL encoded query params. It
	// is assumed that the response body is a string (such as JSON or XML). The
	// response body is returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqFormUrlEncoded, ReadResponseHeader, ReadRespBodyString.
	// 
	const char *fullRequestFormUrlEncoded(const char *httpVerb, const char *uriPath);
	// Sends a complete application/x-www-form-urlencoded HTTP request and receives the
	// full response. The request body is composed of the URL encoded query params. It
	// is assumed that the response body is a string (such as JSON or XML). The
	// response body is returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqFormUrlEncoded, ReadResponseHeader, ReadRespBodyString.
	// 
	CkTask *FullRequestFormUrlEncodedAsync(const char *httpVerb, const char *uriPath);


	// Sends a complete multipart REST request (header + multipart body) and receives
	// the full response. It is assumed that the response body is a string (such as
	// JSON or XML). The response body is returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqMultipart, ReadResponseHeader, ReadRespBodyString.
	// 
	bool FullRequestMultipart(const char *httpVerb, const char *uriPath, CkString &outStr);

	// Sends a complete multipart REST request (header + multipart body) and receives
	// the full response. It is assumed that the response body is a string (such as
	// JSON or XML). The response body is returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqMultipart, ReadResponseHeader, ReadRespBodyString.
	// 
	const char *fullRequestMultipart(const char *httpVerb, const char *uriPath);
	// Sends a complete multipart REST request (header + multipart body) and receives
	// the full response. It is assumed that the response body is a string (such as
	// JSON or XML). The response body is returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqMultipart, ReadResponseHeader, ReadRespBodyString.
	// 
	CkTask *FullRequestMultipartAsync(const char *httpVerb, const char *uriPath);


	// Sends a complete REST request and receives the full response. It is assumed that
	// the response body is a string (such as JSON or XML). The response body is
	// returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqNoBody, ReadResponseHeader, ReadRespBodyString.
	// 
	bool FullRequestNoBody(const char *httpVerb, const char *uriPath, CkString &outStr);

	// Sends a complete REST request and receives the full response. It is assumed that
	// the response body is a string (such as JSON or XML). The response body is
	// returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqNoBody, ReadResponseHeader, ReadRespBodyString.
	// 
	const char *fullRequestNoBody(const char *httpVerb, const char *uriPath);
	// Sends a complete REST request and receives the full response. It is assumed that
	// the response body is a string (such as JSON or XML). The response body is
	// returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqNoBody, ReadResponseHeader, ReadRespBodyString.
	// 
	CkTask *FullRequestNoBodyAsync(const char *httpVerb, const char *uriPath);


	// The same as FullRequestNoBody, except returns the response body in the binData.
	// This method is useful for downloading binary files.
	bool FullRequestNoBodyBd(const char *httpVerb, const char *uriPath, CkBinData &binData);

	// The same as FullRequestNoBody, except returns the response body in the binData.
	// This method is useful for downloading binary files.
	CkTask *FullRequestNoBodyBdAsync(const char *httpVerb, const char *uriPath, CkBinData &binData);


	// The same as FullRequestNoBody, except returns the response body in the sb.
	bool FullRequestNoBodySb(const char *httpVerb, const char *uriPath, CkStringBuilder &sb);

	// The same as FullRequestNoBody, except returns the response body in the sb.
	CkTask *FullRequestNoBodySbAsync(const char *httpVerb, const char *uriPath, CkStringBuilder &sb);


	// Sends a complete REST request (header + body string) and receives the full
	// response. The body of the request is passed in requestBody. The response body is
	// returned in responseBody (replacing whatever contents responseBody may have previously held).
	bool FullRequestSb(const char *httpVerb, const char *uriPath, CkStringBuilder &requestBody, CkStringBuilder &responseBody);

	// Sends a complete REST request (header + body string) and receives the full
	// response. The body of the request is passed in requestBody. The response body is
	// returned in responseBody (replacing whatever contents responseBody may have previously held).
	CkTask *FullRequestSbAsync(const char *httpVerb, const char *uriPath, CkStringBuilder &requestBody, CkStringBuilder &responseBody);


	// Sends a complete REST request and receives the full response. It is assumed that
	// the response body is a string (such as JSON or XML). The response body is
	// returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqStream, ReadResponseHeader, ReadRespBodyString.
	// 
	bool FullRequestStream(const char *httpVerb, const char *uriPath, CkStream &stream, CkString &outStr);

	// Sends a complete REST request and receives the full response. It is assumed that
	// the response body is a string (such as JSON or XML). The response body is
	// returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqStream, ReadResponseHeader, ReadRespBodyString.
	// 
	const char *fullRequestStream(const char *httpVerb, const char *uriPath, CkStream &stream);
	// Sends a complete REST request and receives the full response. It is assumed that
	// the response body is a string (such as JSON or XML). The response body is
	// returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqStream, ReadResponseHeader, ReadRespBodyString.
	// 
	CkTask *FullRequestStreamAsync(const char *httpVerb, const char *uriPath, CkStream &stream);


	// Sends a complete REST request (header + body string) and receives the full
	// response. It is assumed that both the request and response bodies are strings
	// (such as JSON or XML). The response body is returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqStringBody, ReadResponseHeader, ReadRespBodyString.
	// 
	bool FullRequestString(const char *httpVerb, const char *uriPath, const char *bodyText, CkString &outStr);

	// Sends a complete REST request (header + body string) and receives the full
	// response. It is assumed that both the request and response bodies are strings
	// (such as JSON or XML). The response body is returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqStringBody, ReadResponseHeader, ReadRespBodyString.
	// 
	const char *fullRequestString(const char *httpVerb, const char *uriPath, const char *bodyText);
	// Sends a complete REST request (header + body string) and receives the full
	// response. It is assumed that both the request and response bodies are strings
	// (such as JSON or XML). The response body is returned.
	// 
	// This method is the equivalent of making the following calls in sequence:
	// SendReqStringBody, ReadResponseHeader, ReadRespBodyString.
	// 
	CkTask *FullRequestStringAsync(const char *httpVerb, const char *uriPath, const char *bodyText);


	// Reads the response body. Should only be called after ReadResponseHeader has been
	// called, and should only be called when it is already known that the response
	// body is binary, such as for JPG images or other non-text binary file types. The
	// response body is received into responseBody (replacing whatever contents responseBody may have
	// previously held).
	bool ReadRespBd(CkBinData &responseBody);

	// Reads the response body. Should only be called after ReadResponseHeader has been
	// called, and should only be called when it is already known that the response
	// body is binary, such as for JPG images or other non-text binary file types. The
	// response body is received into responseBody (replacing whatever contents responseBody may have
	// previously held).
	CkTask *ReadRespBdAsync(CkBinData &responseBody);


	// Reads the response body. Should only be called after ReadResponseHeader has been
	// called, and should only be called when it is already known that the response
	// body is binary, such as for JPG images or other non-text binary file types.
	bool ReadRespBodyBinary(CkByteData &outBytes);

	// Reads the response body. Should only be called after ReadResponseHeader has been
	// called, and should only be called when it is already known that the response
	// body is binary, such as for JPG images or other non-text binary file types.
	CkTask *ReadRespBodyBinaryAsync(void);


	// Reads the response body to the stream. If autoSetStreamCharset is true, then the stream's
	// StringCharset property will automatically get set based on the charset, if any,
	// indicated in the response header. If the response is binary, then autoSetStreamCharset is
	// ignored.
	bool ReadRespBodyStream(CkStream &stream, bool autoSetStreamCharset);

	// Reads the response body to the stream. If autoSetStreamCharset is true, then the stream's
	// StringCharset property will automatically get set based on the charset, if any,
	// indicated in the response header. If the response is binary, then autoSetStreamCharset is
	// ignored.
	CkTask *ReadRespBodyStreamAsync(CkStream &stream, bool autoSetStreamCharset);


	// Reads the response body. Should only be called after ReadResponseHeader has been
	// called, and should only be called when it is already known that the response
	// body will be a string (such as XML, JSON, etc.)
	bool ReadRespBodyString(CkString &outStr);

	// Reads the response body. Should only be called after ReadResponseHeader has been
	// called, and should only be called when it is already known that the response
	// body will be a string (such as XML, JSON, etc.)
	const char *readRespBodyString(void);
	// Reads the response body. Should only be called after ReadResponseHeader has been
	// called, and should only be called when it is already known that the response
	// body will be a string (such as XML, JSON, etc.)
	CkTask *ReadRespBodyStringAsync(void);


	// Reads the HTTP response header. If the HTTP response includes a body, then the
	// application must call the desired method to read the response body. Otherwise,
	// the HTTP request / response is finished after reading the response header (such
	// as for a GET request). The contents of the response header are available in
	// various properties and methods.
	// 
	// The HTTP response status code is returned (such as 200 for a typical success
	// response). If an error occurred such that no response was received, then a value
	// of -1 is returned.
	// 
	int ReadResponseHeader(void);

	// Reads the HTTP response header. If the HTTP response includes a body, then the
	// application must call the desired method to read the response body. Otherwise,
	// the HTTP request / response is finished after reading the response header (such
	// as for a GET request). The contents of the response header are available in
	// various properties and methods.
	// 
	// The HTTP response status code is returned (such as 200 for a typical success
	// response). If an error occurred such that no response was received, then a value
	// of -1 is returned.
	// 
	CkTask *ReadResponseHeaderAsync(void);


	// Reads the response body. Should only be called after ReadResponseHeader has been
	// called, and should only be called when it is already known that the response
	// body will be a string (such as XML, JSON, etc.) The response body is stored in
	// responseBody. (replacing whatever contents responseBody may have previously held).
	bool ReadRespSb(CkStringBuilder &responseBody);

	// Reads the response body. Should only be called after ReadResponseHeader has been
	// called, and should only be called when it is already known that the response
	// body will be a string (such as XML, JSON, etc.) The response body is stored in
	// responseBody. (replacing whatever contents responseBody may have previously held).
	CkTask *ReadRespSbAsync(CkStringBuilder &responseBody);


	// If the response was a redirect and contains a Location header field, this method
	// returns the redirect URL.
	// The caller is responsible for deleting the object returned by this method.
	CkUrl *RedirectUrl(void);


	// Removes all headers having the given name.
	bool RemoveHeader(const char *name);


	// Removes all query params having the given name.
	bool RemoveQueryParam(const char *name);


	// Returns the value of the response header indicated by name.
	bool ResponseHdrByName(const char *name, CkString &outStr);

	// Returns the value of the response header indicated by name.
	const char *responseHdrByName(const char *name);

	// Returns the name of the Nth response header field. (Chilkat always uses 0-based
	// indexing. The first header field is at index 0.)
	bool ResponseHdrName(int index, CkString &outStr);

	// Returns the name of the Nth response header field. (Chilkat always uses 0-based
	// indexing. The first header field is at index 0.)
	const char *responseHdrName(int index);

	// Returns the value of the Nth response header field. (Chilkat always uses 0-based
	// indexing. The first header field is at index 0.)
	bool ResponseHdrValue(int index, CkString &outStr);

	// Returns the value of the Nth response header field. (Chilkat always uses 0-based
	// indexing. The first header field is at index 0.)
	const char *responseHdrValue(int index);

	// Sends a REST request that cotnains a binary body. The httpVerb is the HTTP verb
	// (also known as the HTTP method), such as "PUT". The uriPath is the path of the
	// resource URI. The body contains the bytes of the HTTP request body.
	bool SendReqBd(const char *httpVerb, const char *uriPath, CkBinData &body);

	// Sends a REST request that cotnains a binary body. The httpVerb is the HTTP verb
	// (also known as the HTTP method), such as "PUT". The uriPath is the path of the
	// resource URI. The body contains the bytes of the HTTP request body.
	CkTask *SendReqBdAsync(const char *httpVerb, const char *uriPath, CkBinData &body);


	// Sends a REST request that cotnains a binary body. The httpVerb is the HTTP verb
	// (also known as the HTTP method), such as "PUT". The uriPath is the path of the
	// resource URI. The body contains the bytes of the HTTP request body.
	bool SendReqBinaryBody(const char *httpVerb, const char *uriPath, CkByteData &body);

	// Sends a REST request that cotnains a binary body. The httpVerb is the HTTP verb
	// (also known as the HTTP method), such as "PUT". The uriPath is the path of the
	// resource URI. The body contains the bytes of the HTTP request body.
	CkTask *SendReqBinaryBodyAsync(const char *httpVerb, const char *uriPath, CkByteData &body);


	// Sends an application/x-www-form-urlencoded HTTP request where the body is
	// composed of the URL encoded query params. The httpVerb is the HTTP verb (also known
	// as the HTTP method), such as "POST". The uriPath is the path of the resource URI.
	// If the Content-Type header was set, it is ignored and instead the Content-Type
	// of the request will be "application/x-www-form-urlencoded".
	bool SendReqFormUrlEncoded(const char *httpVerb, const char *uriPath);

	// Sends an application/x-www-form-urlencoded HTTP request where the body is
	// composed of the URL encoded query params. The httpVerb is the HTTP verb (also known
	// as the HTTP method), such as "POST". The uriPath is the path of the resource URI.
	// If the Content-Type header was set, it is ignored and instead the Content-Type
	// of the request will be "application/x-www-form-urlencoded".
	CkTask *SendReqFormUrlEncodedAsync(const char *httpVerb, const char *uriPath);


	// Sends a multipart REST request. The httpVerb is the HTTP verb (also known as the
	// HTTP method), such as "GET". The uriPath is the path of the resource URI.
	bool SendReqMultipart(const char *httpVerb, const char *uriPath);

	// Sends a multipart REST request. The httpVerb is the HTTP verb (also known as the
	// HTTP method), such as "GET". The uriPath is the path of the resource URI.
	CkTask *SendReqMultipartAsync(const char *httpVerb, const char *uriPath);


	// Sends a REST request that cotnains no body. The httpVerb is the HTTP verb (also
	// known as the HTTP method), such as "GET". The uriPath is the path of the resource
	// URI.
	bool SendReqNoBody(const char *httpVerb, const char *uriPath);

	// Sends a REST request that cotnains no body. The httpVerb is the HTTP verb (also
	// known as the HTTP method), such as "GET". The uriPath is the path of the resource
	// URI.
	CkTask *SendReqNoBodyAsync(const char *httpVerb, const char *uriPath);


	// Sends a REST request that cotnains a text body, such as XML or JSON. The httpVerb is
	// the HTTP verb (also known as the HTTP method), such as "PUT". The uriPath is the
	// path of the resource URI. The bodySb contains the text of the HTTP request body.
	bool SendReqSb(const char *httpVerb, const char *uriPath, CkStringBuilder &bodySb);

	// Sends a REST request that cotnains a text body, such as XML or JSON. The httpVerb is
	// the HTTP verb (also known as the HTTP method), such as "PUT". The uriPath is the
	// path of the resource URI. The bodySb contains the text of the HTTP request body.
	CkTask *SendReqSbAsync(const char *httpVerb, const char *uriPath, CkStringBuilder &bodySb);


	// Sends a REST request that cotnains a binary or text body that is obtained by
	// reading from the stream. The httpVerb is the HTTP verb (also known as the HTTP
	// method), such as "PUT". The uriPath is the path of the resource URI.
	bool SendReqStreamBody(const char *httpVerb, const char *uriPath, CkStream &stream);

	// Sends a REST request that cotnains a binary or text body that is obtained by
	// reading from the stream. The httpVerb is the HTTP verb (also known as the HTTP
	// method), such as "PUT". The uriPath is the path of the resource URI.
	CkTask *SendReqStreamBodyAsync(const char *httpVerb, const char *uriPath, CkStream &stream);


	// Sends a REST request that cotnains a text body, such as XML or JSON. The httpVerb is
	// the HTTP verb (also known as the HTTP method), such as "PUT". The uriPath is the
	// path of the resource URI. The bodyText contains the text of the HTTP request body.
	bool SendReqStringBody(const char *httpVerb, const char *uriPath, const char *bodyText);

	// Sends a REST request that cotnains a text body, such as XML or JSON. The httpVerb is
	// the HTTP verb (also known as the HTTP method), such as "PUT". The uriPath is the
	// path of the resource URI. The bodyText contains the text of the HTTP request body.
	CkTask *SendReqStringBodyAsync(const char *httpVerb, const char *uriPath, const char *bodyText);


	// Sets the authorization service provider for Amazon AWS REST requests. An
	// application that sets an AWS authentication provider need not explicitly set the
	// Authorization property. Each REST request is automatically signed and
	// authenticated using the authProvider.
	bool SetAuthAws(CkAuthAws &authProvider);


	// Sets the Azure AD (Active Directory) authorization service provider.
	bool SetAuthAzureAD(CkAuthAzureAD &authProvider);


	// Provides the information for Azure SAS (Shared Access Signature) authorization.
	// Calling this method will cause the "Authorization: SharedAccessSignature ..."
	// header to be automatically added to all requests.
	bool SetAuthAzureSas(CkAuthAzureSAS &authProvider);


	// Sets the authorization service provider for Azure Storage Service requests.
	bool SetAuthAzureStorage(CkAuthAzureStorage &authProvider);


	// Sets the username and password to be used for Basic authentication. This method should
	// be called when Basic authentication is required. It should only be used with
	// secure SSL/TLS connections. Calling this method will cause the "Authorization:
	// Basic ..." header to be automatically added to all requests. In many cases, a
	// REST API will support Basic authentication where the username is a client ID or
	// account ID, and the password is a client secret or token.
	bool SetAuthBasic(const char *username, const char *password);


	// Sets the authorization service provider for Google API requests.
	bool SetAuthGoogle(CkAuthGoogle &authProvider);


	// Sets the authentication provider for REST API requests needing OAuth 1.0 (and
	// OAuth 1.0a) authentication. If useQueryParams is true, then the OAuth1 authentication
	// information and signature is passed in query parameters. Otherwise it is passed
	// in an Authorization header.
	bool SetAuthOAuth1(CkOAuth1 &authProvider, bool useQueryParams);


	// Sets the authentication provider for REST API requests needing standards-based
	// OAuth 2.0 authentication. This is for the case where a desktop/native/mobile
	// application will be popping up a web browser, or embedding a web browser, to get
	// authorization interactively from end-user of the application.
	bool SetAuthOAuth2(CkOAuth2 &authProvider);


	// Only used for multipart requests. Sets the binary content of the multipart body
	// indicated by the PartSelector.
	bool SetMultipartBodyBd(CkBinData &bodyData);


	// Only used for multipart requests. Sets the binary content of the multipart body
	// indicated by the PartSelector.
	bool SetMultipartBodyBinary(CkByteData &bodyData);


	// Only used for multipart requests. Sets the text content of the multipart body
	// indicated by the PartSelector.
	bool SetMultipartBodySb(CkStringBuilder &bodySb);


	// Only used for multipart requests. Sets the stream source of the multipart body
	// indicated by the PartSelector.
	bool SetMultipartBodyStream(CkStream &stream);


	// Only used for multipart requests. Sets the text content of the multipart body
	// indicated by the PartSelector.
	bool SetMultipartBodyString(const char *bodyText);


	// Only applies to the Full* methods, such as FullRequestNoBody, FullRequestBinary,
	// FullRequestStream, etc. When set, the response body is streamed directly to
	// responseStream, if (and only if) the HTTP response status code equals expectedStatus.
	// 
	// If the response body was streamed to responseStream, then the string return value of the
	// Full* method instead becomes "OK" for success. If an attempt was made to stream
	// the response body but it failed, then "FAIL" is returned. If the response body
	// was not streamed because the response status code was not equal to expectedStatus, then
	// the returned string contains the server's error response.
	// 
	// If autoSetStreamCharset is true, then the expectedStatus's StringCharset property will automatically get
	// set based on the charset, if any, indicated in the response header. If the
	// response is binary, then autoSetStreamCharset is ignored.
	// 
	bool SetResponseBodyStream(int expectedStatus, bool autoSetStreamCharset, CkStream &responseStream);


	// Sets the connection to be used for sending the REST request. The connection should be
	// an already-connected socket. It may be a TLS connection, an unencrypted
	// connection, through an HTTP proxy, a SOCKS proxy, or even through SSH tunnels.
	// All of the connection related functionality is handled by the Chilkat Socket
	// API.
	// 
	// The autoReconnect indicates whether connection should automatically be established as
	// needed for subsequent REST requests.
	// 
	bool UseConnection(CkSocket &connection, bool autoReconnect);






	// END PUBLIC INTERFACE


};
#if !defined(__sun__) && !defined(__sun)
#pragma pack (pop)
#endif


	
#endif
