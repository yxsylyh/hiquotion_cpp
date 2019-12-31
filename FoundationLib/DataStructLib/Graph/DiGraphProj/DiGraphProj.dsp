# Microsoft Developer Studio Project File - Name="DiGraphProj" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=DiGraphProj - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DiGraphProj.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DiGraphProj.mak" CFG="DiGraphProj - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DiGraphProj - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "DiGraphProj - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DiGraphProj - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "DiGraphProj - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DiGraphProj - Win32 Release"
# Name "DiGraphProj - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DiGraphProj.cpp
# End Source File
# Begin Source File

SOURCE=.\DiGraphProj.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DiGraphProj.h
# End Source File
# Begin Source File

SOURCE=..\..\PointerList.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "DataStructLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Arc.cpp
# End Source File
# Begin Source File

SOURCE=.\Arc.h
# End Source File
# Begin Source File

SOURCE=.\DGConstructor.h
# End Source File
# Begin Source File

SOURCE=.\DiGraphic.cpp
# End Source File
# Begin Source File

SOURCE=.\DiGraphic.h
# End Source File
# Begin Source File

SOURCE=.\IArcWeight.cpp
# End Source File
# Begin Source File

SOURCE=.\IArcWeight.h
# End Source File
# Begin Source File

SOURCE=.\INodeData.cpp
# End Source File
# Begin Source File

SOURCE=.\INodeData.h
# End Source File
# Begin Source File

SOURCE=.\Node.cpp
# End Source File
# Begin Source File

SOURCE=.\Node.h
# End Source File
# Begin Source File

SOURCE=.\StatusGraphic.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusGraphic.h
# End Source File
# End Group
# Begin Group "RE2SGConverter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RE2SGConverter\RE2SGConverter.cpp
# End Source File
# Begin Source File

SOURCE=.\RE2SGConverter\RE2SGConverter.h
# End Source File
# End Group
# Begin Group "RegularExpressionLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\ConcatRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\ConcatRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\DigitRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\DigitRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\EmptyRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\EmptyRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\IRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\KleenStarRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\KleenStarRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\LowerRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\LowerRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\OrRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\OrRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\RangeRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\RangeRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\SymbolRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\SymbolRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\UpperRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\UpperRegularExpression.h
# End Source File
# End Group
# Begin Group "CharChecker"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\CharChecker\AndChecker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\CharChecker\AndChecker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\CharChecker\CharChecker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\CharChecker\CharChecker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\CharChecker\CharListChecker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\CharChecker\CharListChecker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\CharChecker\ICharChecker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\CharChecker\ICharChecker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\CharChecker\OrChecker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\CharChecker\OrChecker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\CharChecker\RangeCharChecker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\CharChecker\RangeCharChecker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\CharChecker\SymbolCharChecker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RegularExpressionLib\RegularExpressionProj\CharChecker\SymbolCharChecker.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
