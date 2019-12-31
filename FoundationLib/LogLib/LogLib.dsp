# Microsoft Developer Studio Project File - Name="LogLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=LogLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LogLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LogLib.mak" CFG="LogLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LogLib - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "LogLib - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LogLib - Win32 Release"

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

!ELSEIF  "$(CFG)" == "LogLib - Win32 Debug"

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

# Name "LogLib - Win32 Release"
# Name "LogLib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\FileLog.cpp
# End Source File
# Begin Source File

SOURCE=.\ILog.cpp
# End Source File
# Begin Source File

SOURCE=..\INILib\IniOperation.cpp
# End Source File
# Begin Source File

SOURCE=.\LogBuilderBase.cpp
# End Source File
# Begin Source File

SOURCE=.\LogConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\LogLevel.cpp
# End Source File
# Begin Source File

SOURCE=.\LogLib.cpp
# End Source File
# Begin Source File

SOURCE=.\LogLib.rc
# End Source File
# Begin Source File

SOURCE=.\LogLibLog.cpp
# End Source File
# Begin Source File

SOURCE=.\LogList.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenLog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\FileLog.h
# End Source File
# Begin Source File

SOURCE=.\ILog.h
# End Source File
# Begin Source File

SOURCE=..\INILib\IniOperation.h
# End Source File
# Begin Source File

SOURCE=.\LogBuilderBase.h
# End Source File
# Begin Source File

SOURCE=.\LogConfig.h
# End Source File
# Begin Source File

SOURCE=.\LogLevel.h
# End Source File
# Begin Source File

SOURCE=.\LogLib.h
# End Source File
# Begin Source File

SOURCE=.\LogLibLog.h
# End Source File
# Begin Source File

SOURCE=.\LogList.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScreenLog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Test"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LogBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\LogBuilder.h
# End Source File
# Begin Source File

SOURCE=.\Remark.cpp
# End Source File
# Begin Source File

SOURCE=.\Remark.h
# End Source File
# End Group
# Begin Group "FileSysLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\FileSysLib\FileOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\FileSysLib\FileOperation.h
# End Source File
# Begin Source File

SOURCE=..\FileSysLib\FolderOperation.cpp
# End Source File
# Begin Source File

SOURCE=..\FileSysLib\FolderOperation.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
