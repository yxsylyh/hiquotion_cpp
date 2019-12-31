#include "StdAfx.h"
#include "WebSocket.h"
#include <c++\foundationlib\eventlib\eventemu-仿mfc的事件处理\bufferinfoevent.h>
// #include "gettimeofday.h"

static int deny_deflate, longlived, mirror_lifetime, test_post;
static struct lws *wsi_dumb, *wsi_mirror;
static struct lws *wsi_multi[3];
static volatile int force_exit;
static unsigned int opts, rl_multi[3];
static int flag_no_mirror_traffic;
#if defined(LWS_USE_POLARSSL)
#else
#if defined(LWS_USE_MBEDTLS)
#else
#if defined(LWS_OPENSSL_SUPPORT) && defined(LWS_HAVE_SSL_CTX_set1_param)
char crl_path[1024] = "";
#endif
#endif
#endif

enum demo_protocols {

	PROTOCOL_DUMB_INCREMENT,
	PROTOCOL_LWS_MIRROR,

	/* always last */
	DEMO_PROTOCOL_COUNT
};


/*
* dumb_increment protocol
*
* since this also happens to be protocols[0], some callbacks that are not
* bound to a specific protocol also turn up here.
*/

static int
callback_dumb_increment(struct lws *wsi, enum lws_callback_reasons reason,
						void *user, void *in, size_t len)
{
	const char *which = "http";
	char which_wsi[10], buf[50 + LWS_PRE];
	int n;

	CWebSocket *websocket=(CWebSocket *)user;
// 	if(!websocket)
// 		return -1;

	switch (reason) {

	case LWS_CALLBACK_CLIENT_ESTABLISHED:
		lwsl_info("dumb: LWS_CALLBACK_CLIENT_ESTABLISHED\n");
		if(websocket)
		{
			websocket->setOpen(TRUE);
			IEvent e(websocket, "WSOpen");
			websocket->WSOpen.raiseEvent(websocket, &e);
		}
		break;

	case LWS_CALLBACK_CLOSED:
		lwsl_notice("dumb: LWS_CALLBACK_CLOSED\n");
		wsi_dumb = NULL;
		if(websocket)
		{
			IEvent e(websocket, "WSClose");
			websocket->WSClose.raiseEvent(websocket, &e);
			// 下面这句要放在这里（即最后），因为close会释放libwebsockets资源，那么回调函数也不能继续执行下去了，后面的代码会变成无效的，所以只能放在最后
			websocket->close();
		}
		break;

	case LWS_CALLBACK_CLIENT_RECEIVE:
		((char *)in)[len] = '\0';
		lwsl_info("rx %d '%s'\n", (int)len, (char *)in);
		if(websocket)
		{
			CBufferInfoEvent e(websocket, "WSReceiveData", (char *)in, len);
			websocket->WSReceiveData.raiseEvent(websocket, &e);
		}
		break;

		/* because we are protocols[0] ... */

	case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
		if (wsi == wsi_dumb) {
			which = "dumb";
			wsi_dumb = NULL;
		}
		if (wsi == wsi_mirror) {
			which = "mirror";
			wsi_mirror = NULL;
		}

		for (n = 0; n < ARRAY_SIZE(wsi_multi); n++)
			if (wsi == wsi_multi[n]) {
				sprintf(which_wsi, "multi %d", n);
				which = which_wsi;
				wsi_multi[n] = NULL;
			}

		lwsl_err("CLIENT_CONNECTION_ERROR: %s: %s %p\n", which, in);
		if(websocket)
		{
			IEvent e(websocket, "WSError", -1, "连接失败");
			websocket->WSError.raiseEvent(websocket, &e);
		}
		break;

	case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:
		if ((strcmp((const char *)in, "deflate-stream") == 0) && deny_deflate) {
			lwsl_notice("denied deflate-stream extension\n");
			return 1;
		}
		if ((strcmp((const char *)in, "x-webkit-deflate-frame") == 0))
			return 1;
		if ((strcmp((const char *)in, "deflate-frame") == 0))
			return 1;
		break;

	case LWS_CALLBACK_ESTABLISHED_CLIENT_HTTP:
		lwsl_notice("lws_http_client_http_response %d\n",
			lws_http_client_http_response(wsi));
		break;

	case LWS_CALLBACK_RECEIVE_CLIENT_HTTP:
		{
			char buffer[1024 + LWS_PRE];
			char *px = buffer + LWS_PRE;
			int lenx = sizeof(buffer) - LWS_PRE;

			lwsl_notice("LWS_CALLBACK_RECEIVE_CLIENT_HTTP\n");

			/*
			* Often you need to flow control this by something
			* else being writable.  In that case call the api
			* to get a callback when writable here, and do the
			* pending client read in the writeable callback of
			* the output.
			*/
			if (lws_http_client_read(wsi, &px, &lenx) < 0)
				return -1;
			while (lenx--)
				putchar(*px++);
		}
		break;

	case LWS_CALLBACK_CLIENT_WRITEABLE:
		lwsl_info("Client wsi %p writable\n", wsi);
		if(websocket)
		{
			IEvent e(websocket, "CanSendData");
			websocket->WSCanSendData.raiseEvent(websocket, &e);
		}
		break;

	case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER:
		if (test_post) {
			unsigned char **p = (unsigned char **)in, *end = (*p) + len;

			if (lws_add_http_header_by_token(wsi,
				WSI_TOKEN_HTTP_CONTENT_LENGTH,
				(unsigned char *)"29", 2, p, end))
				return -1;
			if (lws_add_http_header_by_token(wsi,
				WSI_TOKEN_HTTP_CONTENT_TYPE,
				(unsigned char *)"application/x-www-form-urlencoded", 33, p, end))
				return -1;

			/* inform lws we have http body to send */
			lws_client_http_body_pending(wsi, 1);
			lws_callback_on_writable(wsi);
		}
		break;

	case LWS_CALLBACK_CLIENT_HTTP_WRITEABLE:
		strcpy(buf + LWS_PRE, "text=hello&send=Send+the+form");
		n = lws_write(wsi, (unsigned char *)&buf[LWS_PRE], strlen(&buf[LWS_PRE]), LWS_WRITE_HTTP);
		if (n < 0)
			return -1;
		/* we only had one thing to send, so inform lws we are done
		* if we had more to send, call lws_callback_on_writable(wsi);
		* and just return 0 from callback.  On having sent the last
		* part, call the below api instead.*/
		lws_client_http_body_pending(wsi, 0);
		break;

	case LWS_CALLBACK_COMPLETED_CLIENT_HTTP:
		wsi_dumb = NULL;
		force_exit = 1;
		break;

#if defined(LWS_USE_POLARSSL)
#else
#if defined(LWS_USE_MBEDTLS)
#else
#if defined(LWS_OPENSSL_SUPPORT) && defined(LWS_HAVE_SSL_CTX_set1_param)
	case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS:
		if (crl_path[0]) {
			/* Enable CRL checking of the server certificate */
			X509_VERIFY_PARAM *param = X509_VERIFY_PARAM_new();
			X509_VERIFY_PARAM_set_flags(param, X509_V_FLAG_CRL_CHECK);
			SSL_CTX_set1_param((SSL_CTX*)user, param);
			X509_STORE *store = SSL_CTX_get_cert_store((SSL_CTX*)user);
			X509_LOOKUP *lookup = X509_STORE_add_lookup(store, X509_LOOKUP_file());
			int n = X509_load_cert_crl_file(lookup, crl_path, X509_FILETYPE_PEM);
			X509_VERIFY_PARAM_free(param);
			if (n != 1) {
				char errbuf[256];
				n = ERR_get_error();
				lwsl_err("LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS: SSL error: %s (%d)\n", ERR_error_string(n, errbuf), n);
				return 1;
			}
		}
		break;
#endif
#endif
#endif

	default:
		break;
	}

	return 0;
}


/* lws-mirror_protocol */


static int
callback_lws_mirror(struct lws *wsi, enum lws_callback_reasons reason,
					void *user, void *in, size_t len)
{
	unsigned char buf[LWS_PRE + 4096];
	unsigned int rands[4];
	int l = 0;
	int n;

	switch (reason) {
	case LWS_CALLBACK_CLIENT_ESTABLISHED:

		lwsl_notice("mirror: LWS_CALLBACK_CLIENT_ESTABLISHED\n");

		lws_get_random(lws_get_context(wsi), rands, sizeof(rands[0]));
		mirror_lifetime = 16384 + (rands[0] & 65535);
		/* useful to test single connection stability */
		if (longlived)
			mirror_lifetime += 500000;

		lwsl_info("opened mirror connection with "
			"%d lifetime\n", mirror_lifetime);

		/*
		* mirror_lifetime is decremented each send, when it reaches
		* zero the connection is closed in the send callback.
		* When the close callback comes, wsi_mirror is set to NULL
		* so a new connection will be opened
		*
		* start the ball rolling,
		* LWS_CALLBACK_CLIENT_WRITEABLE will come next service
		*/
		if (!flag_no_mirror_traffic)
			lws_callback_on_writable(wsi);
		break;

	case LWS_CALLBACK_CLOSED:
		lwsl_notice("mirror: LWS_CALLBACK_CLOSED mirror_lifetime=%d\n", mirror_lifetime);
		wsi_mirror = NULL;
		break;

	case LWS_CALLBACK_CLIENT_WRITEABLE:
		if (flag_no_mirror_traffic)
			return 0;
		for (n = 0; n < 1; n++) {
			lws_get_random(lws_get_context(wsi), rands, sizeof(rands));
			l += sprintf((char *)&buf[LWS_PRE + l],
				"c #%06X %u %u %u;",
				rands[0] & 0xffffff,	/* colour */
				rands[1] & 511,		/* x */
				rands[2] & 255,		/* y */
				(rands[3] & 31) + 1);	/* radius */
		}

		n = lws_write(wsi, &buf[LWS_PRE], l,
			(lws_write_protocol)(opts | LWS_WRITE_TEXT));
		if (n < 0)
			return -1;
		if (n < l) {
			lwsl_err("Partial write LWS_CALLBACK_CLIENT_WRITEABLE\n");
			return -1;
		}

		mirror_lifetime--;
		if (!mirror_lifetime) {
			lwsl_info("closing mirror session\n");
			return -1;
		}
		/* get notified as soon as we can write again */
		lws_callback_on_writable(wsi);
		break;

	default:
		break;
	}

	return 0;
}


/* list of supported protocols and callbacks */

static struct lws_protocols protocols[] = {
	{
		"dumb-increment-protocol,fake-nonexistant-protocol",
			callback_dumb_increment,
			0,
			102400,
	},
	{
		"fake-nonexistant-protocol,lws-mirror-protocol",
			callback_lws_mirror,
			0,
			1024000,
		},
		{ NULL, NULL, 0, 0 } /* end */
};

static const struct lws_extension exts[] = {
	{
		"permessage-deflate",
			lws_extension_callback_pm_deflate,
			"permessage-deflate; client_max_window_bits"
	},
	{
		"deflate-frame",
			lws_extension_callback_pm_deflate,
			"deflate_frame"
		},
		{ NULL, NULL, NULL /* terminator */ }
};

// static int ratelimit_connects(unsigned int *last, unsigned int secs)
// {
// 	struct timeval tv;
// 
// 	gettimeofday(&tv, NULL);
// 
// 	if (tv.tv_sec - (*last) < secs)
// 		return 0;
// 
// 	*last = tv.tv_sec;
// 
// 	return 1;
// }

CWebSocket::CWebSocket(void)
:m_context(NULL), m_isOpen(FALSE)
{
	memset(&m_createInfo, 0, sizeof m_createInfo);
	memset(&m_connectInfo, 0, sizeof(m_connectInfo));

	protocols[0].per_session_data_size=sizeof(m_userData);
	protocols[0].user=m_userData;

	// 	test_post=1;
}

CWebSocket::~CWebSocket(void)
{
}

// 返回值：
// 1，已经连接成功
// 0，成功
// -1，uri为空或解析失败
// -2，uri不是ws开头
// -3，创建 context 失败
// -4，连接失败
int CWebSocket::open( CString uri )
{
	if(m_isOpen)
		return 1;

	if(uri.GetLength()<=0)
		return -1;

	m_uri=uri;

	memset(&m_createInfo, 0, sizeof m_createInfo);
	memset(&m_connectInfo, 0, sizeof(m_connectInfo));
	if (lws_parse_uri(uri.GetBuffer(uri.GetLength()), &m_protocolWS, &m_connectInfo.address, &m_connectInfo.port, &m_uriPath))
		return -1;

	if (strcmp(m_protocolWS, "ws")!=0)  // 如果不相等
		return -2;

	CString path="/";
	path+=m_uriPath;
	m_connectInfo.path = path.GetBuffer(path.GetLength());

	m_createInfo.port = CONTEXT_PORT_NO_LISTEN;
	m_createInfo.protocols = protocols;
	m_createInfo.gid = -1;
	m_createInfo.uid = -1;
	m_createInfo.ws_ping_pong_interval = 0;

	m_context = lws_create_context(&m_createInfo);
	if (!m_context) {
		return -3;
	}

	m_thead.setContext(m_context);

	m_connectInfo.context = m_context;
	m_connectInfo.ssl_connection = 0;
	m_connectInfo.host = m_connectInfo.address;
	m_connectInfo.origin = m_connectInfo.address;
	m_connectInfo.ietf_version_or_minus_one = -1;
	m_connectInfo.client_exts = NULL; //exts;
// 	i.method = "POST";  // ws 方式可能不需要这句
	m_connectInfo.userdata=this;    // 这句加这是不是正确呢？
	m_connectInfo.protocol = protocols[PROTOCOL_DUMB_INCREMENT].name;
	m_connectInfo.pwsi = &wsi_multi[0];
	m_connectInfo.protocol = protocols[PROTOCOL_DUMB_INCREMENT].name;
	m_connectInfo.pwsi = &wsi_dumb;

	plws=lws_client_connect_via_info(&m_connectInfo);
	if(!plws)
		return -4;

// 	if (!wsi_mirror && ratelimit_connects(&rl_mirror, 2u)) {
// 		lwsl_notice("mirror: connecting\n");
// 		i.protocol = protocols[PROTOCOL_LWS_MIRROR].name;
// 		i.pwsi = &wsi_mirror;
// 		wsi_mirror = lws_client_connect_via_info(&i);
// 	}

	return 0;
}


int CWebSocket::startService()
{
	return m_thead.start();
}

void CWebSocket::pauseService()
{
	m_thead.pause();
}

void CWebSocket::resumeService()
{
	m_thead.start();
}

void CWebSocket::stopService()
{
	m_thead.stop();
}

// 返回值：
// 0，成功
// -1，请先打开连接
// -2，msg 为空
// -3，调用 lws_write 文本写入时，libwebsockets 抛出异常
int CWebSocket::sendMessage( CString msg )
{
	if(!m_isOpen)
		return -1;

	if(msg.GetLength()<=0)
		return -2;

// 	LWS_PRE
	int ret=0;
	unsigned char *c=new unsigned char[msg.GetLength()+1];
	memset(c, 0, msg.GetLength()+1);
	memcpy(c, msg.GetBuffer(msg.GetLength()), msg.GetLength());
	try
	{
// 		ret=lws_write(wsi_dumb, (unsigned char *)msg.GetBuffer(msg.GetLength()), msg.GetLength(), LWS_WRITE_TEXT);
		ret=lws_write(wsi_dumb, c, msg.GetLength()+1, LWS_WRITE_TEXT);
	}
	catch(...)
	{
		delete c;
		return -3;
	}

//	delete c;

	return ret;
}

// 返回值：
// 0，成功
// -1，请先打开连接
// -2，data 为空指针，或 length 长度非正
// -3，调用 lws_write 二进制写入时，libwebsockets 抛出异常
int CWebSocket::sendData( char *data, int length )
{
	if(!m_isOpen)
		return -1;

	if(!data || length<=0)
		return -2;

	int ret=0;
	try
	{
		ret=lws_write(wsi_dumb, (unsigned char *)data, length, LWS_WRITE_BINARY);
	}
	catch(...)
	{
		return -3;
	}

	return ret;
}

void CWebSocket::close()
{
	m_isOpen=FALSE;

	stopService();

	while(m_thead.getStatus()==Running || m_thead.getStatus()==ToStop)
	{
		continue;
	}

	try
	{
		lws_context_destroy(m_context);
	}
	catch(...)
	{

	}
}

void CWebSocket::setUserBuffer( unsigned char *buffer, int length )
{
	protocols[0].per_session_data_size=length;
	protocols[0].user=buffer;
}
