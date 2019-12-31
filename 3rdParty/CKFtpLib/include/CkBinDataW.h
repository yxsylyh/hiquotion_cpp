// CkBinDataW.h: interface for the CkBinDataW class.
//
//////////////////////////////////////////////////////////////////////

// This header is generated for Chilkat v9.5.0

#ifndef _CkBinDataW_H
#define _CkBinDataW_H
	
#include "chilkatDefs.h"

#include "CkString.h"
#include "CkWideCharBase.h"

class CkByteData;
class CkStringBuilderW;



#if !defined(__sun__) && !defined(__sun)
#pragma pack (push, 8)
#endif
 

// CLASS: CkBinDataW
class CK_VISIBLE_PUBLIC CkBinDataW  : public CkWideCharBase
{
    private:
	

	// Don't allow assignment or copying these objects.
	CkBinDataW(const CkBinDataW &);
	CkBinDataW &operator=(const CkBinDataW &);

    public:
	CkBinDataW(void);
	virtual ~CkBinDataW(void);

	static CkBinDataW *createNew(void);
	

	
	void CK_VISIBLE_PRIVATE inject(void *impl);

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	

	// BEGIN PUBLIC INTERFACE

	// ----------------------
	// Properties
	// ----------------------
	// The number of bytes contained within the object.
	int get_NumBytes(void);



	// ----------------------
	// Methods
	// ----------------------
	// Appends the contents of another BinData to this object.
	bool AppendBd(CkBinDataW &binData);

	// Appends binary data to the current contents, if any.
	bool AppendBinary(CkByteData &data);

	// Appends the appropriate BOM (byte order mark), also known as a "preamble", for
	// the given charset. If the charset has no defined BOM, then nothing is appended. An
	// application would typically call this to append the utf-8, utf-16, or utf-32
	// BOM.
	bool AppendBom(const wchar_t *charset);

	// Appends encoded binary data to the current data. The encoding may be "Base64",
	// "modBase64", "base64Url", "Base32", "Base58", "QP" (for quoted-printable), "URL"
	// (for url-encoding), "Hex", or any of the encodings found at Chilkat Binary
	// Encodings List
	// <http://cknotes.com/chilkat-binary-encoding-list/> .
	bool AppendEncoded(const wchar_t *encData, const wchar_t *encoding);

	// Decodes the contents of sb and appends the decoded bytes to this object. The
	// encoding may be "Base64", "modBase64", "base64Url", "Base32", "Base58", "QP" (for
	// quoted-printable), "URL" (for url-encoding), "Hex", or any of the encodings
	// found at Chilkat Binary Encodings List
	// <http://cknotes.com/chilkat-binary-encoding-list/> .
	bool AppendEncodedSb(CkStringBuilderW &sb, const wchar_t *encoding);

	// Appends the contents of a StringBuilder to this object.
	bool AppendSb(CkStringBuilderW &sb, const wchar_t *charset);

	// Appends a string to this object. (This does not append the BOM. If a BOM is
	// required, the AppendBom method can be called to append the appropriate BOM.)
	bool AppendString(const wchar_t *str, const wchar_t *charset);

	// Clears the contents.
	bool Clear(void);

	// Return true if the contents of this object equals the contents of binData.
	bool ContentsEqual(CkBinDataW &binData);

	// Retrieves the binary data contained within the object.
	bool GetBinary(CkByteData &outBytes);

	// Retrieves a chunk of the binary data contained within the object.
	bool GetBinaryChunk(int offset, int numBytes, CkByteData &outBytes);

	// Retrieves the binary data as an encoded string. The encoding may be "Base64",
	// "modBase64", "base64Url", "Base32", "Base58", "QP" (for quoted-printable), "URL"
	// (for url-encoding), "Hex", or any of the encodings found at Chilkat Binary
	// Encodings List
	// <http://cknotes.com/chilkat-binary-encoding-list/> .
	bool GetEncoded(const wchar_t *encoding, CkString &outStr);
	// Retrieves the binary data as an encoded string. The encoding may be "Base64",
	// "modBase64", "base64Url", "Base32", "Base58", "QP" (for quoted-printable), "URL"
	// (for url-encoding), "Hex", or any of the encodings found at Chilkat Binary
	// Encodings List
	// <http://cknotes.com/chilkat-binary-encoding-list/> .
	const wchar_t *getEncoded(const wchar_t *encoding);
	// Retrieves the binary data as an encoded string. The encoding may be "Base64",
	// "modBase64", "base64Url", "Base32", "Base58", "QP" (for quoted-printable), "URL"
	// (for url-encoding), "Hex", or any of the encodings found at Chilkat Binary
	// Encodings List
	// <http://cknotes.com/chilkat-binary-encoding-list/> .
	const wchar_t *encoded(const wchar_t *encoding);

	// Retrieves a chunk of the binary data and returns it in encoded form. The encoding
	// may be "Base64", "modBase64", "base64Url", "Base32", "Base58", "QP" (for
	// quoted-printable), "URL" (for url-encoding), "Hex", or any of the encodings
	// found at Chilkat Binary Encodings List
	// <http://cknotes.com/chilkat-binary-encoding-list/> .
	bool GetEncodedChunk(int offset, int numBytes, const wchar_t *encoding, CkString &outStr);
	// Retrieves a chunk of the binary data and returns it in encoded form. The encoding
	// may be "Base64", "modBase64", "base64Url", "Base32", "Base58", "QP" (for
	// quoted-printable), "URL" (for url-encoding), "Hex", or any of the encodings
	// found at Chilkat Binary Encodings List
	// <http://cknotes.com/chilkat-binary-encoding-list/> .
	const wchar_t *getEncodedChunk(int offset, int numBytes, const wchar_t *encoding);
	// Retrieves a chunk of the binary data and returns it in encoded form. The encoding
	// may be "Base64", "modBase64", "base64Url", "Base32", "Base58", "QP" (for
	// quoted-printable), "URL" (for url-encoding), "Hex", or any of the encodings
	// found at Chilkat Binary Encodings List
	// <http://cknotes.com/chilkat-binary-encoding-list/> .
	const wchar_t *encodedChunk(int offset, int numBytes, const wchar_t *encoding);

	// Writes the encoded data to a StringBuilder. The encoding may be "Base64",
	// "modBase64", "base64Url", "Base32", "Base58", "QP" (for quoted-printable), "URL"
	// (for url-encoding), "Hex", or any of the encodings found at Chilkat Binary
	// Encodings List
	// <http://cknotes.com/chilkat-binary-encoding-list/> .
	bool GetEncodedSb(const wchar_t *encoding, CkStringBuilderW &sb);

	// Loads binary data and replaces the current contents, if any.
	bool LoadBinary(CkByteData &data);

	// Loads binary data from an encoded string, replacing the current contents, if
	// any. The encoding may be "Base64", "modBase64", "base64Url", "Base32", "Base58",
	// "QP" (for quoted-printable), "URL" (for url-encoding), "Hex", or any of the
	// encodings found at Chilkat Binary Encodings List
	// <http://cknotes.com/chilkat-binary-encoding-list/> .
	bool LoadEncoded(const wchar_t *encData, const wchar_t *encoding);

	// Loads data from a file.
	bool LoadFile(const wchar_t *path);

	// Removes a chunk of bytes from the binary data.
	bool RemoveChunk(int offset, int numBytes);

	// Writes the contents to a file.
	bool WriteFile(const wchar_t *path);





	// END PUBLIC INTERFACE


};
#if !defined(__sun__) && !defined(__sun)
#pragma pack (pop)
#endif


	
#endif
