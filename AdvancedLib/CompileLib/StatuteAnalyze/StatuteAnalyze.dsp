# Microsoft Developer Studio Project File - Name="StatuteAnalyze" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=StatuteAnalyze - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "StatuteAnalyze.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "StatuteAnalyze.mak" CFG="StatuteAnalyze - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StatuteAnalyze - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "StatuteAnalyze - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"

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

!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
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

# Name "StatuteAnalyze - Win32 Release"
# Name "StatuteAnalyze - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\StatuteAnalyze.cpp
# End Source File
# Begin Source File

SOURCE=.\StatuteAnalyze.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StatuteAnalyze.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "MemManager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MemManager\MemManager.cpp
# End Source File
# Begin Source File

SOURCE=.\MemManager\MemManager.h
# End Source File
# End Group
# Begin Group "StatuteAnalyzer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StatuteAnalyzer\IStatuteAnalyzer.h
# End Source File
# Begin Source File

SOURCE=.\StatuteAnalyzer\IStatuteStatusGraphBuilder.h
# End Source File
# Begin Source File

SOURCE=.\StatuteAnalyzer\StatuteAnalyzer.cpp
# End Source File
# Begin Source File

SOURCE=.\StatuteAnalyzer\StatuteAnalyzer.h
# End Source File
# Begin Source File

SOURCE=.\StatuteAnalyzer\StatuteItemList.cpp
# End Source File
# Begin Source File

SOURCE=.\StatuteAnalyzer\StatuteItemList.h
# End Source File
# Begin Source File

SOURCE=.\StatuteAnalyzer\StatuteList.cpp
# End Source File
# Begin Source File

SOURCE=.\StatuteAnalyzer\StatuteList.h
# End Source File
# Begin Source File

SOURCE=.\StatuteAnalyzer\StatuteStatusGraphBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\StatuteAnalyzer\StatuteStatusGraphBuilder.h
# End Source File
# Begin Source File

SOURCE=.\StatuteAnalyzer\StatuteTreeNode.cpp
# End Source File
# Begin Source File

SOURCE=.\StatuteAnalyzer\StatuteTreeNode.h
# End Source File
# End Group
# Begin Group "StatuteStatusGraph"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StatuteStatusGraph\StatuteStatusGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\StatuteStatusGraph\StatuteStatusGraph.h
# End Source File
# Begin Source File

SOURCE=.\StatuteStatusGraph\StatuteStatusGraphArc.cpp
# End Source File
# Begin Source File

SOURCE=.\StatuteStatusGraph\StatuteStatusGraphArc.h
# End Source File
# Begin Source File

SOURCE=.\StatuteStatusGraph\StatuteStatusGraphNode.cpp
# End Source File
# Begin Source File

SOURCE=.\StatuteStatusGraph\StatuteStatusGraphNode.h
# End Source File
# End Group
# Begin Group "StatuteStatusMachine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StatuteStatusMachine\StatuteStatusMachine.cpp
# End Source File
# Begin Source File

SOURCE=.\StatuteStatusMachine\StatuteStatusMachine.h
# End Source File
# End Group
# Begin Group "Lex"

# PROP Default_Filter ""
# Begin Group "Lexer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Lex\Lexer\Lexer.cpp
# End Source File
# Begin Source File

SOURCE=..\Lex\Lexer\Lexer.h
# End Source File
# End Group
# Begin Group "LexStatusMachine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Lex\LexStatusMachine\LexStatusMachine.cpp
# End Source File
# Begin Source File

SOURCE=..\Lex\LexStatusMachine\LexStatusMachine.h
# End Source File
# End Group
# Begin Group "LexStatusGraph"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Lex\LexStatusGraph\LexStatusGraph.cpp
# End Source File
# Begin Source File

SOURCE=..\Lex\LexStatusGraph\LexStatusGraph.h
# End Source File
# Begin Source File

SOURCE=..\Lex\LexStatusGraph\StatusGraphArc.cpp
# End Source File
# Begin Source File

SOURCE=..\Lex\LexStatusGraph\StatusGraphArc.h
# End Source File
# Begin Source File

SOURCE=..\Lex\LexStatusGraph\StatusGraphNode.cpp
# End Source File
# Begin Source File

SOURCE=..\Lex\LexStatusGraph\StatusGraphNode.h
# End Source File
# End Group
# End Group
# Begin Group "StringExtLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\FoundationLib\StringExtLib\FormattedString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\StringExtLib\FormattedString.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\StringExtLib\StringExt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\StringExtLib\StringExt.h
# End Source File
# End Group
# Begin Group "RegularRepression"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\ConcatRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\ConcatRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\DigitRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\DigitRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\EmptyRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\EmptyRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\IRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\KleenStarRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\KleenStarRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\KleenStartPlusRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\KleenStartPlusRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\LowerRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\LowerRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\NotRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\NotRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\OrRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\OrRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\RangeRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\RangeRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\StringRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\StringRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\SymbolRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\SymbolRegularExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\UpperRegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\UpperRegularExpression.h
# End Source File
# End Group
# Begin Group "KernelLex"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\KernelLex\KernelLexer\KernelLexer.cpp
# End Source File
# Begin Source File

SOURCE=..\KernelLex\KernelLexer\KernelLexer.h
# End Source File
# Begin Source File

SOURCE=..\KernelLex\KernelLexer\KernelLexStatusGraphBuilder.cpp
# End Source File
# Begin Source File

SOURCE=..\KernelLex\KernelLexer\KernelLexStatusGraphBuilder.h
# End Source File
# End Group
# Begin Group "Log"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\FileLog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\FileLogLib\FileLogLib\FileLog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\Log.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\FileLogLib\FileLogLib\Log.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\LogBuilder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\FileLogLib\FileLogLib\LogBuilder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\LogConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\FileLogLib\FileLogLib\LogConfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\LogDef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\FileLogLib\FileLogLib\LogDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\LogLevel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\FileLogLib\FileLogLib\LogLevel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\tinystr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\FileLogLib\FileLogLib\tinystr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\tinyxml.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\FileLogLib\FileLogLib\tinyxml.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\tinyxmlerror.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\tinyxmlparser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\XmlOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\FileLogLib\FileLogLib\XmlOperation.h
# End Source File
# End Group
# Begin Group "FileSysLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\FoundationLib\FileSysLib\FileOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\FileSysLib\FileOperation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FoundationLib\FileSysLib\FolderOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FoudationLib\FileSysLib\FolderOperation.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
