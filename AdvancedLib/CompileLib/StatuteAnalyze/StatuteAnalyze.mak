# Microsoft Developer Studio Generated NMAKE File, Based on StatuteAnalyze.dsp
!IF $(CFG)" == "
CFG=StatuteAnalyze - Win32 Debug
!MESSAGE No configuration specified. Defaulting to StatuteAnalyze - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "StatuteAnalyze - Win32 Release" && "$(CFG)" != "StatuteAnalyze - Win32 Debug"
!MESSAGE 指定的配置 "$(CFG)" 无效.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF $(OS)" == "Windows_NT
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# 开始自定义宏
OutDir=.\Release
# 结束自定义宏

ALL : "$(OUTDIR)\StatuteAnalyze.exe"


CLEAN :
	-@erase "$(INTDIR)\ConcatRegularExpression.obj"
	-@erase "$(INTDIR)\DigitRegularExpression.obj"
	-@erase "$(INTDIR)\EmptyRegularExpression.obj"
	-@erase "$(INTDIR)\FileLog.obj"
	-@erase "$(INTDIR)\FileOperation.obj"
	-@erase "$(INTDIR)\FolderOperation.obj"
	-@erase "$(INTDIR)\FormattedString.obj"
	-@erase "$(INTDIR)\KernelLexer.obj"
	-@erase "$(INTDIR)\KernelLexStatusGraphBuilder.obj"
	-@erase "$(INTDIR)\KleenStarRegularExpression.obj"
	-@erase "$(INTDIR)\KleenStartPlusRegularExpression.obj"
	-@erase "$(INTDIR)\Lexer.obj"
	-@erase "$(INTDIR)\LexStatusGraph.obj"
	-@erase "$(INTDIR)\LexStatusMachine.obj"
	-@erase "$(INTDIR)\Log.obj"
	-@erase "$(INTDIR)\LogBuilder.obj"
	-@erase "$(INTDIR)\LogConfig.obj"
	-@erase "$(INTDIR)\LogDef.obj"
	-@erase "$(INTDIR)\LogLevel.obj"
	-@erase "$(INTDIR)\LowerRegularExpression.obj"
	-@erase "$(INTDIR)\MemManager.obj"
	-@erase "$(INTDIR)\NotRegularExpression.obj"
	-@erase "$(INTDIR)\OrRegularExpression.obj"
	-@erase "$(INTDIR)\RangeRegularExpression.obj"
	-@erase "$(INTDIR)\StatusGraphArc.obj"
	-@erase "$(INTDIR)\StatusGraphNode.obj"
	-@erase "$(INTDIR)\StatuteAnalyze.obj"
	-@erase "$(INTDIR)\StatuteAnalyze.pch"
	-@erase "$(INTDIR)\StatuteAnalyze.res"
	-@erase "$(INTDIR)\StatuteAnalyzer.obj"
	-@erase "$(INTDIR)\StatuteItemList.obj"
	-@erase "$(INTDIR)\StatuteList.obj"
	-@erase "$(INTDIR)\StatuteStatusGraph.obj"
	-@erase "$(INTDIR)\StatuteStatusGraphArc.obj"
	-@erase "$(INTDIR)\StatuteStatusGraphBuilder.obj"
	-@erase "$(INTDIR)\StatuteStatusGraphNode.obj"
	-@erase "$(INTDIR)\StatuteStatusMachine.obj"
	-@erase "$(INTDIR)\StatuteTreeNode.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StringExt.obj"
	-@erase "$(INTDIR)\StringRegularExpression.obj"
	-@erase "$(INTDIR)\SymbolRegularExpression.obj"
	-@erase "$(INTDIR)\tinystr.obj"
	-@erase "$(INTDIR)\tinyxml.obj"
	-@erase "$(INTDIR)\tinyxmlerror.obj"
	-@erase "$(INTDIR)\tinyxmlparser.obj"
	-@erase "$(INTDIR)\UpperRegularExpression.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\XmlOperation.obj"
	-@erase "$(OUTDIR)\StatuteAnalyze.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\StatuteAnalyze.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\StatuteAnalyze.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\StatuteAnalyze.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\StatuteAnalyze.pdb" /machine:I386 /out:"$(OUTDIR)\StatuteAnalyze.exe" 
LINK32_OBJS= \
	"$(INTDIR)\StatuteAnalyze.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MemManager.obj" \
	"$(INTDIR)\StatuteAnalyzer.obj" \
	"$(INTDIR)\StatuteItemList.obj" \
	"$(INTDIR)\StatuteList.obj" \
	"$(INTDIR)\StatuteStatusGraphBuilder.obj" \
	"$(INTDIR)\StatuteTreeNode.obj" \
	"$(INTDIR)\StatuteStatusGraph.obj" \
	"$(INTDIR)\StatuteStatusGraphArc.obj" \
	"$(INTDIR)\StatuteStatusGraphNode.obj" \
	"$(INTDIR)\StatuteStatusMachine.obj" \
	"$(INTDIR)\Lexer.obj" \
	"$(INTDIR)\LexStatusMachine.obj" \
	"$(INTDIR)\LexStatusGraph.obj" \
	"$(INTDIR)\StatusGraphArc.obj" \
	"$(INTDIR)\StatusGraphNode.obj" \
	"$(INTDIR)\FormattedString.obj" \
	"$(INTDIR)\StringExt.obj" \
	"$(INTDIR)\ConcatRegularExpression.obj" \
	"$(INTDIR)\DigitRegularExpression.obj" \
	"$(INTDIR)\EmptyRegularExpression.obj" \
	"$(INTDIR)\KleenStarRegularExpression.obj" \
	"$(INTDIR)\KleenStartPlusRegularExpression.obj" \
	"$(INTDIR)\LowerRegularExpression.obj" \
	"$(INTDIR)\NotRegularExpression.obj" \
	"$(INTDIR)\OrRegularExpression.obj" \
	"$(INTDIR)\RangeRegularExpression.obj" \
	"$(INTDIR)\StringRegularExpression.obj" \
	"$(INTDIR)\SymbolRegularExpression.obj" \
	"$(INTDIR)\UpperRegularExpression.obj" \
	"$(INTDIR)\KernelLexer.obj" \
	"$(INTDIR)\KernelLexStatusGraphBuilder.obj" \
	"$(INTDIR)\FileLog.obj" \
	"$(INTDIR)\Log.obj" \
	"$(INTDIR)\LogBuilder.obj" \
	"$(INTDIR)\LogConfig.obj" \
	"$(INTDIR)\LogDef.obj" \
	"$(INTDIR)\LogLevel.obj" \
	"$(INTDIR)\tinystr.obj" \
	"$(INTDIR)\tinyxml.obj" \
	"$(INTDIR)\tinyxmlerror.obj" \
	"$(INTDIR)\tinyxmlparser.obj" \
	"$(INTDIR)\XmlOperation.obj" \
	"$(INTDIR)\FileOperation.obj" \
	"$(INTDIR)\FolderOperation.obj" \
	"$(INTDIR)\StatuteAnalyze.res"

"$(OUTDIR)\StatuteAnalyze.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OutDir=.\Debug
# 结束自定义宏

ALL : "$(OUTDIR)\StatuteAnalyze.exe" "$(OUTDIR)\StatuteAnalyze.bsc"


CLEAN :
	-@erase "$(INTDIR)\ConcatRegularExpression.obj"
	-@erase "$(INTDIR)\ConcatRegularExpression.sbr"
	-@erase "$(INTDIR)\DigitRegularExpression.obj"
	-@erase "$(INTDIR)\DigitRegularExpression.sbr"
	-@erase "$(INTDIR)\EmptyRegularExpression.obj"
	-@erase "$(INTDIR)\EmptyRegularExpression.sbr"
	-@erase "$(INTDIR)\FileLog.obj"
	-@erase "$(INTDIR)\FileLog.sbr"
	-@erase "$(INTDIR)\FileOperation.obj"
	-@erase "$(INTDIR)\FileOperation.sbr"
	-@erase "$(INTDIR)\FolderOperation.obj"
	-@erase "$(INTDIR)\FolderOperation.sbr"
	-@erase "$(INTDIR)\FormattedString.obj"
	-@erase "$(INTDIR)\FormattedString.sbr"
	-@erase "$(INTDIR)\KernelLexer.obj"
	-@erase "$(INTDIR)\KernelLexer.sbr"
	-@erase "$(INTDIR)\KernelLexStatusGraphBuilder.obj"
	-@erase "$(INTDIR)\KernelLexStatusGraphBuilder.sbr"
	-@erase "$(INTDIR)\KleenStarRegularExpression.obj"
	-@erase "$(INTDIR)\KleenStarRegularExpression.sbr"
	-@erase "$(INTDIR)\KleenStartPlusRegularExpression.obj"
	-@erase "$(INTDIR)\KleenStartPlusRegularExpression.sbr"
	-@erase "$(INTDIR)\Lexer.obj"
	-@erase "$(INTDIR)\Lexer.sbr"
	-@erase "$(INTDIR)\LexStatusGraph.obj"
	-@erase "$(INTDIR)\LexStatusGraph.sbr"
	-@erase "$(INTDIR)\LexStatusMachine.obj"
	-@erase "$(INTDIR)\LexStatusMachine.sbr"
	-@erase "$(INTDIR)\Log.obj"
	-@erase "$(INTDIR)\Log.sbr"
	-@erase "$(INTDIR)\LogBuilder.obj"
	-@erase "$(INTDIR)\LogBuilder.sbr"
	-@erase "$(INTDIR)\LogConfig.obj"
	-@erase "$(INTDIR)\LogConfig.sbr"
	-@erase "$(INTDIR)\LogDef.obj"
	-@erase "$(INTDIR)\LogDef.sbr"
	-@erase "$(INTDIR)\LogLevel.obj"
	-@erase "$(INTDIR)\LogLevel.sbr"
	-@erase "$(INTDIR)\LowerRegularExpression.obj"
	-@erase "$(INTDIR)\LowerRegularExpression.sbr"
	-@erase "$(INTDIR)\MemManager.obj"
	-@erase "$(INTDIR)\MemManager.sbr"
	-@erase "$(INTDIR)\NotRegularExpression.obj"
	-@erase "$(INTDIR)\NotRegularExpression.sbr"
	-@erase "$(INTDIR)\OrRegularExpression.obj"
	-@erase "$(INTDIR)\OrRegularExpression.sbr"
	-@erase "$(INTDIR)\RangeRegularExpression.obj"
	-@erase "$(INTDIR)\RangeRegularExpression.sbr"
	-@erase "$(INTDIR)\StatusGraphArc.obj"
	-@erase "$(INTDIR)\StatusGraphArc.sbr"
	-@erase "$(INTDIR)\StatusGraphNode.obj"
	-@erase "$(INTDIR)\StatusGraphNode.sbr"
	-@erase "$(INTDIR)\StatuteAnalyze.obj"
	-@erase "$(INTDIR)\StatuteAnalyze.pch"
	-@erase "$(INTDIR)\StatuteAnalyze.res"
	-@erase "$(INTDIR)\StatuteAnalyze.sbr"
	-@erase "$(INTDIR)\StatuteAnalyzer.obj"
	-@erase "$(INTDIR)\StatuteAnalyzer.sbr"
	-@erase "$(INTDIR)\StatuteItemList.obj"
	-@erase "$(INTDIR)\StatuteItemList.sbr"
	-@erase "$(INTDIR)\StatuteList.obj"
	-@erase "$(INTDIR)\StatuteList.sbr"
	-@erase "$(INTDIR)\StatuteStatusGraph.obj"
	-@erase "$(INTDIR)\StatuteStatusGraph.sbr"
	-@erase "$(INTDIR)\StatuteStatusGraphArc.obj"
	-@erase "$(INTDIR)\StatuteStatusGraphArc.sbr"
	-@erase "$(INTDIR)\StatuteStatusGraphBuilder.obj"
	-@erase "$(INTDIR)\StatuteStatusGraphBuilder.sbr"
	-@erase "$(INTDIR)\StatuteStatusGraphNode.obj"
	-@erase "$(INTDIR)\StatuteStatusGraphNode.sbr"
	-@erase "$(INTDIR)\StatuteStatusMachine.obj"
	-@erase "$(INTDIR)\StatuteStatusMachine.sbr"
	-@erase "$(INTDIR)\StatuteTreeNode.obj"
	-@erase "$(INTDIR)\StatuteTreeNode.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\StringExt.obj"
	-@erase "$(INTDIR)\StringExt.sbr"
	-@erase "$(INTDIR)\StringRegularExpression.obj"
	-@erase "$(INTDIR)\StringRegularExpression.sbr"
	-@erase "$(INTDIR)\SymbolRegularExpression.obj"
	-@erase "$(INTDIR)\SymbolRegularExpression.sbr"
	-@erase "$(INTDIR)\tinystr.obj"
	-@erase "$(INTDIR)\tinystr.sbr"
	-@erase "$(INTDIR)\tinyxml.obj"
	-@erase "$(INTDIR)\tinyxml.sbr"
	-@erase "$(INTDIR)\tinyxmlerror.obj"
	-@erase "$(INTDIR)\tinyxmlerror.sbr"
	-@erase "$(INTDIR)\tinyxmlparser.obj"
	-@erase "$(INTDIR)\tinyxmlparser.sbr"
	-@erase "$(INTDIR)\UpperRegularExpression.obj"
	-@erase "$(INTDIR)\UpperRegularExpression.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\XmlOperation.obj"
	-@erase "$(INTDIR)\XmlOperation.sbr"
	-@erase "$(OUTDIR)\StatuteAnalyze.bsc"
	-@erase "$(OUTDIR)\StatuteAnalyze.exe"
	-@erase "$(OUTDIR)\StatuteAnalyze.ilk"
	-@erase "$(OUTDIR)\StatuteAnalyze.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\StatuteAnalyze.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\StatuteAnalyze.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\StatuteAnalyze.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\StatuteAnalyze.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\MemManager.sbr" \
	"$(INTDIR)\StatuteAnalyzer.sbr" \
	"$(INTDIR)\StatuteItemList.sbr" \
	"$(INTDIR)\StatuteList.sbr" \
	"$(INTDIR)\StatuteStatusGraphBuilder.sbr" \
	"$(INTDIR)\StatuteTreeNode.sbr" \
	"$(INTDIR)\StatuteStatusGraph.sbr" \
	"$(INTDIR)\StatuteStatusGraphArc.sbr" \
	"$(INTDIR)\StatuteStatusGraphNode.sbr" \
	"$(INTDIR)\StatuteStatusMachine.sbr" \
	"$(INTDIR)\Lexer.sbr" \
	"$(INTDIR)\LexStatusMachine.sbr" \
	"$(INTDIR)\LexStatusGraph.sbr" \
	"$(INTDIR)\StatusGraphArc.sbr" \
	"$(INTDIR)\StatusGraphNode.sbr" \
	"$(INTDIR)\FormattedString.sbr" \
	"$(INTDIR)\StringExt.sbr" \
	"$(INTDIR)\ConcatRegularExpression.sbr" \
	"$(INTDIR)\DigitRegularExpression.sbr" \
	"$(INTDIR)\EmptyRegularExpression.sbr" \
	"$(INTDIR)\KleenStarRegularExpression.sbr" \
	"$(INTDIR)\KleenStartPlusRegularExpression.sbr" \
	"$(INTDIR)\LowerRegularExpression.sbr" \
	"$(INTDIR)\NotRegularExpression.sbr" \
	"$(INTDIR)\OrRegularExpression.sbr" \
	"$(INTDIR)\RangeRegularExpression.sbr" \
	"$(INTDIR)\StringRegularExpression.sbr" \
	"$(INTDIR)\SymbolRegularExpression.sbr" \
	"$(INTDIR)\UpperRegularExpression.sbr" \
	"$(INTDIR)\KernelLexer.sbr" \
	"$(INTDIR)\KernelLexStatusGraphBuilder.sbr" \
	"$(INTDIR)\FileLog.sbr" \
	"$(INTDIR)\Log.sbr" \
	"$(INTDIR)\LogBuilder.sbr" \
	"$(INTDIR)\LogConfig.sbr" \
	"$(INTDIR)\LogDef.sbr" \
	"$(INTDIR)\LogLevel.sbr" \
	"$(INTDIR)\tinystr.sbr" \
	"$(INTDIR)\tinyxml.sbr" \
	"$(INTDIR)\tinyxmlerror.sbr" \
	"$(INTDIR)\tinyxmlparser.sbr" \
	"$(INTDIR)\XmlOperation.sbr" \
	"$(INTDIR)\FileOperation.sbr" \
	"$(INTDIR)\FolderOperation.sbr"

"$(OUTDIR)\StatuteAnalyze.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\StatuteAnalyze.pdb" /debug /machine:I386 /out:"$(OUTDIR)\StatuteAnalyze.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\StatuteAnalyze.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MemManager.obj" \
	"$(INTDIR)\StatuteAnalyzer.obj" \
	"$(INTDIR)\StatuteItemList.obj" \
	"$(INTDIR)\StatuteList.obj" \
	"$(INTDIR)\StatuteStatusGraphBuilder.obj" \
	"$(INTDIR)\StatuteTreeNode.obj" \
	"$(INTDIR)\StatuteStatusGraph.obj" \
	"$(INTDIR)\StatuteStatusGraphArc.obj" \
	"$(INTDIR)\StatuteStatusGraphNode.obj" \
	"$(INTDIR)\StatuteStatusMachine.obj" \
	"$(INTDIR)\Lexer.obj" \
	"$(INTDIR)\LexStatusMachine.obj" \
	"$(INTDIR)\LexStatusGraph.obj" \
	"$(INTDIR)\StatusGraphArc.obj" \
	"$(INTDIR)\StatusGraphNode.obj" \
	"$(INTDIR)\FormattedString.obj" \
	"$(INTDIR)\StringExt.obj" \
	"$(INTDIR)\ConcatRegularExpression.obj" \
	"$(INTDIR)\DigitRegularExpression.obj" \
	"$(INTDIR)\EmptyRegularExpression.obj" \
	"$(INTDIR)\KleenStarRegularExpression.obj" \
	"$(INTDIR)\KleenStartPlusRegularExpression.obj" \
	"$(INTDIR)\LowerRegularExpression.obj" \
	"$(INTDIR)\NotRegularExpression.obj" \
	"$(INTDIR)\OrRegularExpression.obj" \
	"$(INTDIR)\RangeRegularExpression.obj" \
	"$(INTDIR)\StringRegularExpression.obj" \
	"$(INTDIR)\SymbolRegularExpression.obj" \
	"$(INTDIR)\UpperRegularExpression.obj" \
	"$(INTDIR)\KernelLexer.obj" \
	"$(INTDIR)\KernelLexStatusGraphBuilder.obj" \
	"$(INTDIR)\FileLog.obj" \
	"$(INTDIR)\Log.obj" \
	"$(INTDIR)\LogBuilder.obj" \
	"$(INTDIR)\LogConfig.obj" \
	"$(INTDIR)\LogDef.obj" \
	"$(INTDIR)\LogLevel.obj" \
	"$(INTDIR)\tinystr.obj" \
	"$(INTDIR)\tinyxml.obj" \
	"$(INTDIR)\tinyxmlerror.obj" \
	"$(INTDIR)\tinyxmlparser.obj" \
	"$(INTDIR)\XmlOperation.obj" \
	"$(INTDIR)\FileOperation.obj" \
	"$(INTDIR)\FolderOperation.obj" \
	"$(INTDIR)\StatuteAnalyze.res"

"$(OUTDIR)\StatuteAnalyze.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("StatuteAnalyze.dep")
!INCLUDE "StatuteAnalyze.dep"
!ELSE 
!MESSAGE Warning: cannot find "StatuteAnalyze.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "StatuteAnalyze - Win32 Release" || "$(CFG)" == "StatuteAnalyze - Win32 Debug"
SOURCE=.\StatuteAnalyze.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\StatuteAnalyze.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\StatuteAnalyze.obj"	"$(INTDIR)\StatuteAnalyze.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"


!ENDIF 

SOURCE=.\StatuteAnalyze.rc

"$(INTDIR)\StatuteAnalyze.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\StatuteAnalyze.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StatuteAnalyze.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\StatuteAnalyze.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\StatuteAnalyze.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\MemManager\MemManager.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\MemManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\MemManager.obj"	"$(INTDIR)\MemManager.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\StatuteAnalyzer\StatuteAnalyzer.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\StatuteAnalyzer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\StatuteAnalyzer.obj"	"$(INTDIR)\StatuteAnalyzer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\StatuteAnalyzer\StatuteItemList.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\StatuteItemList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\StatuteItemList.obj"	"$(INTDIR)\StatuteItemList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\StatuteAnalyzer\StatuteList.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\StatuteList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\StatuteList.obj"	"$(INTDIR)\StatuteList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\StatuteAnalyzer\StatuteStatusGraphBuilder.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\StatuteStatusGraphBuilder.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\StatuteStatusGraphBuilder.obj"	"$(INTDIR)\StatuteStatusGraphBuilder.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\StatuteAnalyzer\StatuteTreeNode.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\StatuteTreeNode.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\StatuteTreeNode.obj"	"$(INTDIR)\StatuteTreeNode.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\StatuteStatusGraph\StatuteStatusGraph.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\StatuteStatusGraph.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\StatuteStatusGraph.obj"	"$(INTDIR)\StatuteStatusGraph.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\StatuteStatusGraph\StatuteStatusGraphArc.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\StatuteStatusGraphArc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\StatuteStatusGraphArc.obj"	"$(INTDIR)\StatuteStatusGraphArc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\StatuteStatusGraph\StatuteStatusGraphNode.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\StatuteStatusGraphNode.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\StatuteStatusGraphNode.obj"	"$(INTDIR)\StatuteStatusGraphNode.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\StatuteStatusMachine\StatuteStatusMachine.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\StatuteStatusMachine.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\StatuteStatusMachine.obj"	"$(INTDIR)\StatuteStatusMachine.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Lex\Lexer\Lexer.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\Lexer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\Lexer.obj"	"$(INTDIR)\Lexer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Lex\LexStatusMachine\LexStatusMachine.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\LexStatusMachine.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\LexStatusMachine.obj"	"$(INTDIR)\LexStatusMachine.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Lex\LexStatusGraph\LexStatusGraph.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\LexStatusGraph.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\LexStatusGraph.obj"	"$(INTDIR)\LexStatusGraph.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Lex\LexStatusGraph\StatusGraphArc.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\StatusGraphArc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\StatusGraphArc.obj"	"$(INTDIR)\StatusGraphArc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Lex\LexStatusGraph\StatusGraphNode.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\StatusGraphNode.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\StatusGraphNode.obj"	"$(INTDIR)\StatusGraphNode.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\StringExtLib\FormattedString.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\FormattedString.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\FormattedString.obj"	"$(INTDIR)\FormattedString.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\StringExtLib\StringExt.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\StringExt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\StringExt.obj"	"$(INTDIR)\StringExt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\ConcatRegularExpression.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\ConcatRegularExpression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\ConcatRegularExpression.obj"	"$(INTDIR)\ConcatRegularExpression.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\DigitRegularExpression.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\DigitRegularExpression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\DigitRegularExpression.obj"	"$(INTDIR)\DigitRegularExpression.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\EmptyRegularExpression.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\EmptyRegularExpression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\EmptyRegularExpression.obj"	"$(INTDIR)\EmptyRegularExpression.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\KleenStarRegularExpression.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\KleenStarRegularExpression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\KleenStarRegularExpression.obj"	"$(INTDIR)\KleenStarRegularExpression.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\KleenStartPlusRegularExpression.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\KleenStartPlusRegularExpression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\KleenStartPlusRegularExpression.obj"	"$(INTDIR)\KleenStartPlusRegularExpression.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\LowerRegularExpression.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\LowerRegularExpression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\LowerRegularExpression.obj"	"$(INTDIR)\LowerRegularExpression.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\NotRegularExpression.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\NotRegularExpression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\NotRegularExpression.obj"	"$(INTDIR)\NotRegularExpression.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\OrRegularExpression.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\OrRegularExpression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\OrRegularExpression.obj"	"$(INTDIR)\OrRegularExpression.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\RangeRegularExpression.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\RangeRegularExpression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\RangeRegularExpression.obj"	"$(INTDIR)\RangeRegularExpression.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\StringRegularExpression.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\StringRegularExpression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\StringRegularExpression.obj"	"$(INTDIR)\StringRegularExpression.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\SymbolRegularExpression.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\SymbolRegularExpression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\SymbolRegularExpression.obj"	"$(INTDIR)\SymbolRegularExpression.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\UpperRegularExpression.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\UpperRegularExpression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\UpperRegularExpression.obj"	"$(INTDIR)\UpperRegularExpression.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\KernelLex\KernelLexer\KernelLexer.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\KernelLexer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\KernelLexer.obj"	"$(INTDIR)\KernelLexer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\KernelLex\KernelLexer\KernelLexStatusGraphBuilder.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\KernelLexStatusGraphBuilder.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\KernelLexStatusGraphBuilder.obj"	"$(INTDIR)\KernelLexStatusGraphBuilder.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\FileLog.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\FileLog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\FileLog.obj"	"$(INTDIR)\FileLog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\Log.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\Log.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\Log.obj"	"$(INTDIR)\Log.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\LogBuilder.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\LogBuilder.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\LogBuilder.obj"	"$(INTDIR)\LogBuilder.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\LogConfig.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\LogConfig.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\LogConfig.obj"	"$(INTDIR)\LogConfig.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\LogDef.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\LogDef.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\LogDef.obj"	"$(INTDIR)\LogDef.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\LogLevel.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\LogLevel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\LogLevel.obj"	"$(INTDIR)\LogLevel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\tinystr.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\tinystr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\tinystr.obj"	"$(INTDIR)\tinystr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\tinyxml.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\tinyxml.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\tinyxml.obj"	"$(INTDIR)\tinyxml.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\tinyxmlerror.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\tinyxmlerror.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\tinyxmlerror.obj"	"$(INTDIR)\tinyxmlerror.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\tinyxmlparser.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\tinyxmlparser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\tinyxmlparser.obj"	"$(INTDIR)\tinyxmlparser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\FileLogLib\FileLogLib\XmlOperation.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\XmlOperation.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\XmlOperation.obj"	"$(INTDIR)\XmlOperation.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\FileSysLib\FileOperation.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\FileOperation.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\FileOperation.obj"	"$(INTDIR)\FileOperation.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\FoundationLib\FileSysLib\FolderOperation.cpp

!IF  "$(CFG)" == "StatuteAnalyze - Win32 Release"


"$(INTDIR)\FolderOperation.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StatuteAnalyze - Win32 Debug"


"$(INTDIR)\FolderOperation.obj"	"$(INTDIR)\FolderOperation.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StatuteAnalyze.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

