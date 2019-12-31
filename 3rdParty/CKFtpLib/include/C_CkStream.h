// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkStream_H
#define _C_CkStream_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC void CkStream_setAbortCheck(HCkStream cHandle, BOOL (*fnAbortCheck)());
CK_VISIBLE_PUBLIC void CkStream_setPercentDone(HCkStream cHandle, BOOL (*fnPercentDone)(int pctDone));
CK_VISIBLE_PUBLIC void CkStream_setProgressInfo(HCkStream cHandle, void (*fnProgressInfo)(const char *name, const char *value));
CK_VISIBLE_PUBLIC void CkStream_setTaskCompleted(HCkStream cHandle, void (*fnTaskCompleted)(HCkTask hTask));

CK_VISIBLE_PUBLIC HCkStream CkStream_Create(void);
CK_VISIBLE_PUBLIC void CkStream_Dispose(HCkStream handle);
CK_VISIBLE_PUBLIC BOOL CkStream_getAbortCurrent(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_putAbortCurrent(HCkStream cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkStream_getCanRead(HCkStream cHandle);
CK_VISIBLE_PUBLIC BOOL CkStream_getCanWrite(HCkStream cHandle);
CK_VISIBLE_PUBLIC BOOL CkStream_getDataAvailable(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_getDebugLogFilePath(HCkStream cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkStream_putDebugLogFilePath(HCkStream cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkStream_debugLogFilePath(HCkStream cHandle);
CK_VISIBLE_PUBLIC int CkStream_getDefaultChunkSize(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_putDefaultChunkSize(HCkStream cHandle, int newVal);
CK_VISIBLE_PUBLIC BOOL CkStream_getEndOfStream(HCkStream cHandle);
CK_VISIBLE_PUBLIC BOOL CkStream_getIsWriteClosed(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_getLastErrorHtml(HCkStream cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkStream_lastErrorHtml(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_getLastErrorText(HCkStream cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkStream_lastErrorText(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_getLastErrorXml(HCkStream cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkStream_lastErrorXml(HCkStream cHandle);
CK_VISIBLE_PUBLIC BOOL CkStream_getLastMethodSuccess(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_putLastMethodSuccess(HCkStream cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC __int64 CkStream_getLength(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_putLength(HCkStream cHandle, __int64 newVal);
CK_VISIBLE_PUBLIC int CkStream_getLength32(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_putLength32(HCkStream cHandle, int newVal);
CK_VISIBLE_PUBLIC __int64 CkStream_getNumReceived(HCkStream cHandle);
CK_VISIBLE_PUBLIC __int64 CkStream_getNumSent(HCkStream cHandle);
CK_VISIBLE_PUBLIC int CkStream_getReadFailReason(HCkStream cHandle);
CK_VISIBLE_PUBLIC int CkStream_getReadTimeoutMs(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_putReadTimeoutMs(HCkStream cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkStream_getSinkFile(HCkStream cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkStream_putSinkFile(HCkStream cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkStream_sinkFile(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_getSourceFile(HCkStream cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkStream_putSourceFile(HCkStream cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkStream_sourceFile(HCkStream cHandle);
CK_VISIBLE_PUBLIC int CkStream_getSourceFilePart(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_putSourceFilePart(HCkStream cHandle, int newVal);
CK_VISIBLE_PUBLIC int CkStream_getSourceFilePartSize(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_putSourceFilePartSize(HCkStream cHandle, int newVal);
CK_VISIBLE_PUBLIC BOOL CkStream_getStringBom(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_putStringBom(HCkStream cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkStream_getStringCharset(HCkStream cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkStream_putStringCharset(HCkStream cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkStream_stringCharset(HCkStream cHandle);
CK_VISIBLE_PUBLIC BOOL CkStream_getUtf8(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_putUtf8(HCkStream cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkStream_getVerboseLogging(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_putVerboseLogging(HCkStream cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkStream_getVersion(HCkStream cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkStream_version(HCkStream cHandle);
CK_VISIBLE_PUBLIC int CkStream_getWriteFailReason(HCkStream cHandle);
CK_VISIBLE_PUBLIC int CkStream_getWriteTimeoutMs(HCkStream cHandle);
CK_VISIBLE_PUBLIC void CkStream_putWriteTimeoutMs(HCkStream cHandle, int newVal);
CK_VISIBLE_PUBLIC BOOL CkStream_ReadBytes(HCkStream cHandle, HCkByteData outBytes);
CK_VISIBLE_PUBLIC HCkTask CkStream_ReadBytesAsync(HCkStream cHandle);
CK_VISIBLE_PUBLIC BOOL CkStream_ReadBytesENC(HCkStream cHandle, const char *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkStream_readBytesENC(HCkStream cHandle, const char *encoding);
CK_VISIBLE_PUBLIC HCkTask CkStream_ReadBytesENCAsync(HCkStream cHandle, const char *encoding);
CK_VISIBLE_PUBLIC BOOL CkStream_ReadNBytes(HCkStream cHandle, int numBytes, HCkByteData outBytes);
CK_VISIBLE_PUBLIC HCkTask CkStream_ReadNBytesAsync(HCkStream cHandle, int numBytes);
CK_VISIBLE_PUBLIC BOOL CkStream_ReadNBytesENC(HCkStream cHandle, int numBytes, const char *encoding, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkStream_readNBytesENC(HCkStream cHandle, int numBytes, const char *encoding);
CK_VISIBLE_PUBLIC HCkTask CkStream_ReadNBytesENCAsync(HCkStream cHandle, int numBytes, const char *encoding);
CK_VISIBLE_PUBLIC BOOL CkStream_ReadString(HCkStream cHandle, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkStream_readString(HCkStream cHandle);
CK_VISIBLE_PUBLIC HCkTask CkStream_ReadStringAsync(HCkStream cHandle);
CK_VISIBLE_PUBLIC BOOL CkStream_ReadToCRLF(HCkStream cHandle, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkStream_readToCRLF(HCkStream cHandle);
CK_VISIBLE_PUBLIC HCkTask CkStream_ReadToCRLFAsync(HCkStream cHandle);
CK_VISIBLE_PUBLIC BOOL CkStream_ReadUntilMatch(HCkStream cHandle, const char *matchStr, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkStream_readUntilMatch(HCkStream cHandle, const char *matchStr);
CK_VISIBLE_PUBLIC HCkTask CkStream_ReadUntilMatchAsync(HCkStream cHandle, const char *matchStr);
CK_VISIBLE_PUBLIC void CkStream_Reset(HCkStream cHandle);
CK_VISIBLE_PUBLIC BOOL CkStream_RunStream(HCkStream cHandle);
CK_VISIBLE_PUBLIC HCkTask CkStream_RunStreamAsync(HCkStream cHandle);
CK_VISIBLE_PUBLIC BOOL CkStream_SaveLastError(HCkStream cHandle, const char *path);
CK_VISIBLE_PUBLIC BOOL CkStream_SetSinkStream(HCkStream cHandle, HCkStream strm);
CK_VISIBLE_PUBLIC BOOL CkStream_SetSourceBytes(HCkStream cHandle, HCkByteData sourceData);
CK_VISIBLE_PUBLIC BOOL CkStream_SetSourceStream(HCkStream cHandle, HCkStream strm);
CK_VISIBLE_PUBLIC BOOL CkStream_SetSourceString(HCkStream cHandle, const char *srcStr, const char *charset);
CK_VISIBLE_PUBLIC BOOL CkStream_WriteByte(HCkStream cHandle, int byteVal);
CK_VISIBLE_PUBLIC HCkTask CkStream_WriteByteAsync(HCkStream cHandle, int byteVal);
CK_VISIBLE_PUBLIC BOOL CkStream_WriteBytes(HCkStream cHandle, HCkByteData byteData);
CK_VISIBLE_PUBLIC HCkTask CkStream_WriteBytesAsync(HCkStream cHandle, HCkByteData byteData);
CK_VISIBLE_PUBLIC BOOL CkStream_WriteBytesENC(HCkStream cHandle, const char *byteData, const char *encoding);
CK_VISIBLE_PUBLIC HCkTask CkStream_WriteBytesENCAsync(HCkStream cHandle, const char *byteData, const char *encoding);
CK_VISIBLE_PUBLIC BOOL CkStream_WriteClose(HCkStream cHandle);
CK_VISIBLE_PUBLIC BOOL CkStream_WriteString(HCkStream cHandle, const char *str);
CK_VISIBLE_PUBLIC HCkTask CkStream_WriteStringAsync(HCkStream cHandle, const char *str);
#endif
