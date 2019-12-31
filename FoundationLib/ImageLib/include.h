#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef ULONG_PTR
#define ULONG_PTR unsigned long*
#endif
#include <C++/FoudationLib/3rdParty/GDIPlus/Includes/gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

// GdiplusStartupInput m_gdiplusStartupInput; 
// ULONG_PTR m_pGdiToken;
// 
// #define GDI_START() GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);
// #define GDI_END() GdiplusShutdown(m_pGdiToken);
