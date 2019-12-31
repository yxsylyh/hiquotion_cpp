// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkBinDataWH
#define _C_CkBinDataWH
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC HCkBinDataW CkBinDataW_Create(void);
CK_VISIBLE_PUBLIC void CkBinDataW_Dispose(HCkBinDataW handle);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_getLastMethodSuccess(HCkBinDataW cHandle);
CK_VISIBLE_PUBLIC void  CkBinDataW_putLastMethodSuccess(HCkBinDataW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkBinDataW_getNumBytes(HCkBinDataW cHandle);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_AppendBd(HCkBinDataW cHandle, HCkBinDataW binData);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_AppendBinary(HCkBinDataW cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_AppendBom(HCkBinDataW cHandle, const wchar_t *charset);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_AppendEncoded(HCkBinDataW cHandle, const wchar_t *encData, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_AppendEncodedSb(HCkBinDataW cHandle, HCkStringBuilderW sb, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_AppendSb(HCkBinDataW cHandle, HCkStringBuilderW sb, const wchar_t *charset);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_AppendString(HCkBinDataW cHandle, const wchar_t *str, const wchar_t *charset);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_Clear(HCkBinDataW cHandle);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_ContentsEqual(HCkBinDataW cHandle, HCkBinDataW binData);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_GetBinary(HCkBinDataW cHandle, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_GetBinaryChunk(HCkBinDataW cHandle, int offset, int numBytes, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_GetEncoded(HCkBinDataW cHandle, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkBinDataW_getEncoded(HCkBinDataW cHandle, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_GetEncodedChunk(HCkBinDataW cHandle, int offset, int numBytes, const wchar_t *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkBinDataW_getEncodedChunk(HCkBinDataW cHandle, int offset, int numBytes, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_GetEncodedSb(HCkBinDataW cHandle, const wchar_t *encoding, HCkStringBuilderW sb);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_LoadBinary(HCkBinDataW cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_LoadEncoded(HCkBinDataW cHandle, const wchar_t *encData, const wchar_t *encoding);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_LoadFile(HCkBinDataW cHandle, const wchar_t *path);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_RemoveChunk(HCkBinDataW cHandle, int offset, int numBytes);
CK_VISIBLE_PUBLIC BOOL CkBinDataW_WriteFile(HCkBinDataW cHandle, const wchar_t *path);
#endif
