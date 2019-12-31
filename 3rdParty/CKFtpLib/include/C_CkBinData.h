// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkBinData_H
#define _C_CkBinData_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC HCkBinData CkBinData_Create(void);
CK_VISIBLE_PUBLIC void CkBinData_Dispose(HCkBinData handle);
CK_VISIBLE_PUBLIC BOOL CkBinData_getLastMethodSuccess(HCkBinData cHandle);
CK_VISIBLE_PUBLIC void CkBinData_putLastMethodSuccess(HCkBinData cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkBinData_getNumBytes(HCkBinData cHandle);
CK_VISIBLE_PUBLIC BOOL CkBinData_getUtf8(HCkBinData cHandle);
CK_VISIBLE_PUBLIC void CkBinData_putUtf8(HCkBinData cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkBinData_AppendBd(HCkBinData cHandle, HCkBinData binData);
CK_VISIBLE_PUBLIC BOOL CkBinData_AppendBinary(HCkBinData cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkBinData_AppendBom(HCkBinData cHandle, const char *charset);
CK_VISIBLE_PUBLIC BOOL CkBinData_AppendEncoded(HCkBinData cHandle, const char *encData, const char *encoding);
CK_VISIBLE_PUBLIC BOOL CkBinData_AppendEncodedSb(HCkBinData cHandle, HCkStringBuilder sb, const char *encoding);
CK_VISIBLE_PUBLIC BOOL CkBinData_AppendSb(HCkBinData cHandle, HCkStringBuilder sb, const char *charset);
CK_VISIBLE_PUBLIC BOOL CkBinData_AppendString(HCkBinData cHandle, const char *str, const char *charset);
CK_VISIBLE_PUBLIC BOOL CkBinData_Clear(HCkBinData cHandle);
CK_VISIBLE_PUBLIC BOOL CkBinData_ContentsEqual(HCkBinData cHandle, HCkBinData binData);
CK_VISIBLE_PUBLIC BOOL CkBinData_GetBinary(HCkBinData cHandle, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkBinData_GetBinaryChunk(HCkBinData cHandle, int offset, int numBytes, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkBinData_GetEncoded(HCkBinData cHandle, const char *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkBinData_getEncoded(HCkBinData cHandle, const char *encoding);
CK_VISIBLE_PUBLIC BOOL CkBinData_GetEncodedChunk(HCkBinData cHandle, int offset, int numBytes, const char *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkBinData_getEncodedChunk(HCkBinData cHandle, int offset, int numBytes, const char *encoding);
CK_VISIBLE_PUBLIC BOOL CkBinData_GetEncodedSb(HCkBinData cHandle, const char *encoding, HCkStringBuilder sb);
CK_VISIBLE_PUBLIC BOOL CkBinData_LoadBinary(HCkBinData cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkBinData_LoadEncoded(HCkBinData cHandle, const char *encData, const char *encoding);
CK_VISIBLE_PUBLIC BOOL CkBinData_LoadFile(HCkBinData cHandle, const char *path);
CK_VISIBLE_PUBLIC BOOL CkBinData_RemoveChunk(HCkBinData cHandle, int offset, int numBytes);
CK_VISIBLE_PUBLIC BOOL CkBinData_WriteFile(HCkBinData cHandle, const char *path);
#endif
