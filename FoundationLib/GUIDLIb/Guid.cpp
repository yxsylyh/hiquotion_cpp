#include "stdafx.h"
#include "Guid.h"

CString CGuid::genGUID()
{
	CString strGuid = "";
	GUID guid;
	if (S_OK == ::CoCreateGuid(&guid))
	{
		strGuid.Format("%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X"
			, guid.Data1
			, guid.Data2
			, guid.Data3
			, guid.Data4[0], guid.Data4[1]
			, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]
		);
	}

	return strGuid;
}

BOOL CGuid::isGUIDEqual(GUID guid1, GUID guid2)
{
	if (guid1.Data1 != guid2.Data1)
		return FALSE;

	if (guid1.Data2 == guid2.Data2)
		return FALSE;

	if (guid1.Data3 != guid2.Data3)
		return FALSE;

	for (int i = 0; i < 8; i++) {
		if (guid1.Data4[i] != guid2.Data4[i]) {
			return FALSE;
		}
	}

	return TRUE;
}

// GUID 转字符串
// 参数：格式
// 格式说明及示例：
// d/D, 10244798-9a34-4245-b1ef-9143f9b1e68a
// n/N, 102447989a344245b1ef9143f9b1e68a
// b/B, {10244798-9a34-4245-b1ef-9143f9b1e68a}
// p/P, (10244798-9a34-4245-b1ef-9143f9b1e68a)
CString CGuid::toString( GUID &guid, char c/*='d'*/ )
{
	char *format=NULL;
	switch(c)
	{
	case 'd':
		format="%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x";
		break;
	case 'D':
		format="%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X";
		break;
	case 'n':
		format="%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x";
		break;
	case 'N':
		format="%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X";
		break;
	case 'b':
		format="{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}";
		break;
	case 'B':
		format="{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}";
		break;
	case 'p':
		format="(%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x)";
		break;
	case 'P':
		format="(%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X)";
		break;
	default:
		return "";
	}

	CString szGUID;
	szGUID.Format( format
		, guid.Data1
		, guid.Data2
		, guid.Data3
		, guid.Data4[0], guid.Data4[1]
	, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
	, guid.Data4[6], guid.Data4[7]
	); 

	return szGUID;
}
