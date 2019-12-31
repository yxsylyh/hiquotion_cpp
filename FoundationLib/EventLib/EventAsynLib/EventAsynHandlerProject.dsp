# Microsoft Developer Studio Project File - Name="EventAsynHandlerProject" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=EventAsynHandlerProject - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EventAsynHandlerProject.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EventAsynHandlerProject.mak" CFG="EventAsynHandlerProject - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EventAsynHandlerProject - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "EventAsynHandlerProject - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "EventAsynHandlerProject - Win32 Release"

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

!ELSEIF  "$(CFG)" == "EventAsynHandlerProject - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ    /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ    /c
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

# Name "EventAsynHandlerProject - Win32 Release"
# Name "EventAsynHandlerProject - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\EventAsynHandlerProject.cpp
# End Source File
# Begin Source File

SOURCE=.\EventAsynHandlerProject.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\EventAsynHandlerProject.h
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
# Begin Group "MultiThreadLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\MultiThreadLib\IThread.h
# End Source File
# Begin Source File

SOURCE=..\..\MultiThreadLib\ThreadBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\MultiThreadLib\ThreadBase.h
# End Source File
# Begin Source File

SOURCE=..\..\MultiThreadLib\ThreadEntry.h
# End Source File
# Begin Source File

SOURCE=..\..\MultiThreadLib\ThreadStatus.h
# End Source File
# End Group
# Begin Group "EventAsynLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EventAsynHandlerThread.cpp
# End Source File
# Begin Source File

SOURCE=.\EventAsynHandlerThread.h
# End Source File
# End Group
# Begin Group "ProductorConsumerLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\AdvancedLib\MultiThreadPattern\ProductorConsumerLib\ProductorConsumerPattern.h
# End Source File
# End Group
# Begin Group "EventLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\EventEmu-仿MFC的事件处理\Delegate.cpp"
# End Source File
# Begin Source File

SOURCE="..\EventEmu-仿MFC的事件处理\Delegate.h"
# End Source File
# Begin Source File

SOURCE="..\EventEmu-仿MFC的事件处理\IEvent.cpp"
# End Source File
# Begin Source File

SOURCE="..\EventEmu-仿MFC的事件处理\IEvent.h"
# End Source File
# Begin Source File

SOURCE="..\EventEmu-仿MFC的事件处理\IEventHandler.cpp"
# End Source File
# Begin Source File

SOURCE="..\EventEmu-仿MFC的事件处理\IEventHandler.h"
# End Source File
# Begin Source File

SOURCE="..\EventEmu-仿MFC的事件处理\IEventRaisable.cpp"
# End Source File
# Begin Source File

SOURCE="..\EventEmu-仿MFC的事件处理\IEventRaisable.h"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
