// This is a generated source file for Chilkat version 9.5.0.65
#ifndef _C_CkHashtableWH
#define _C_CkHashtableWH
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC HCkHashtableW CkHashtableW_Create(void);
CK_VISIBLE_PUBLIC void CkHashtableW_Dispose(HCkHashtableW handle);
CK_VISIBLE_PUBLIC BOOL CkHashtableW_getLastMethodSuccess(HCkHashtableW cHandle);
CK_VISIBLE_PUBLIC void  CkHashtableW_putLastMethodSuccess(HCkHashtableW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkHashtableW_AddFromXmlSb(HCkHashtableW cHandle, HCkStringBuilderW sbXml);
CK_VISIBLE_PUBLIC BOOL CkHashtableW_AddInt(HCkHashtableW cHandle, const wchar_t *key, int value);
CK_VISIBLE_PUBLIC BOOL CkHashtableW_AddQueryParams(HCkHashtableW cHandle, const wchar_t *queryParams);
CK_VISIBLE_PUBLIC BOOL CkHashtableW_AddStr(HCkHashtableW cHandle, const wchar_t *key, const wchar_t *value);
CK_VISIBLE_PUBLIC void CkHashtableW_Clear(HCkHashtableW cHandle);
CK_VISIBLE_PUBLIC BOOL CkHashtableW_ClearWithNewCapacity(HCkHashtableW cHandle, int capacity);
CK_VISIBLE_PUBLIC BOOL CkHashtableW_Contains(HCkHashtableW cHandle, const wchar_t *key);
CK_VISIBLE_PUBLIC BOOL CkHashtableW_ContainsIntKey(HCkHashtableW cHandle, int key);
CK_VISIBLE_PUBLIC BOOL CkHashtableW_GetKeys(HCkHashtableW cHandle, HCkStringTableW strTable);
CK_VISIBLE_PUBLIC int CkHashtableW_LookupInt(HCkHashtableW cHandle, const wchar_t *key);
CK_VISIBLE_PUBLIC BOOL CkHashtableW_LookupStr(HCkHashtableW cHandle, const wchar_t *key, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkHashtableW_lookupStr(HCkHashtableW cHandle, const wchar_t *key);
CK_VISIBLE_PUBLIC BOOL CkHashtableW_Remove(HCkHashtableW cHandle, const wchar_t *key);
CK_VISIBLE_PUBLIC BOOL CkHashtableW_ToXmlSb(HCkHashtableW cHandle, HCkStringBuilderW sbXml);
#endif
