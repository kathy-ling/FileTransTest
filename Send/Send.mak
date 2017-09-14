# Microsoft Developer Studio Generated NMAKE File, Based on Send.dsp
!IF $(CFG)" == "
CFG=Send - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Send - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Send - Win32 Release" && "$(CFG)" != "Send - Win32 Debug"
!MESSAGE 指定的配置 "$(CFG)" 无效.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Send.mak" CFG="Send - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Send - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Send - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF $(OS)" == "Windows_NT
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Send - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# 开始自定义宏
OutDir=.\Release
# 结束自定义宏

ALL : "$(OUTDIR)\Send.exe" "$(OUTDIR)\Send.bsc"


CLEAN :
	-@erase "$(INTDIR)\Send.obj"
	-@erase "$(INTDIR)\Send.pch"
	-@erase "$(INTDIR)\Send.res"
	-@erase "$(INTDIR)\Send.sbr"
	-@erase "$(INTDIR)\SendDlg.obj"
	-@erase "$(INTDIR)\SendDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TcpClient.obj"
	-@erase "$(INTDIR)\TcpClient.sbr"
	-@erase "$(INTDIR)\Thread.obj"
	-@erase "$(INTDIR)\Thread.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Send.bsc"
	-@erase "$(OUTDIR)\Send.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Send.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Send.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Send.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Send.sbr" \
	"$(INTDIR)\SendDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TcpClient.sbr" \
	"$(INTDIR)\Thread.sbr"

"$(OUTDIR)\Send.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Send.pdb" /machine:I386 /out:"$(OUTDIR)\Send.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Send.obj" \
	"$(INTDIR)\SendDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TcpClient.obj" \
	"$(INTDIR)\Thread.obj" \
	"$(INTDIR)\Send.res"

"$(OUTDIR)\Send.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Send - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OutDir=.\Debug
# 结束自定义宏

ALL : "$(OUTDIR)\Send.exe" "$(OUTDIR)\Send.bsc"


CLEAN :
	-@erase "$(INTDIR)\Send.obj"
	-@erase "$(INTDIR)\Send.pch"
	-@erase "$(INTDIR)\Send.res"
	-@erase "$(INTDIR)\Send.sbr"
	-@erase "$(INTDIR)\SendDlg.obj"
	-@erase "$(INTDIR)\SendDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TcpClient.obj"
	-@erase "$(INTDIR)\TcpClient.sbr"
	-@erase "$(INTDIR)\Thread.obj"
	-@erase "$(INTDIR)\Thread.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Send.bsc"
	-@erase "$(OUTDIR)\Send.exe"
	-@erase "$(OUTDIR)\Send.ilk"
	-@erase "$(OUTDIR)\Send.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Send.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Send.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Send.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Send.sbr" \
	"$(INTDIR)\SendDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TcpClient.sbr" \
	"$(INTDIR)\Thread.sbr"

"$(OUTDIR)\Send.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Send.pdb" /debug /machine:I386 /nodefaultlib:"MSVCRT" /out:"$(OUTDIR)\Send.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Send.obj" \
	"$(INTDIR)\SendDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TcpClient.obj" \
	"$(INTDIR)\Thread.obj" \
	"$(INTDIR)\Send.res"

"$(OUTDIR)\Send.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Send.dep")
!INCLUDE "Send.dep"
!ELSE 
!MESSAGE Warning: cannot find "Send.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Send - Win32 Release" || "$(CFG)" == "Send - Win32 Debug"
SOURCE=.\Send.cpp

"$(INTDIR)\Send.obj"	"$(INTDIR)\Send.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Send.pch"


SOURCE=.\Send.rc

"$(INTDIR)\Send.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\SendDlg.cpp

"$(INTDIR)\SendDlg.obj"	"$(INTDIR)\SendDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Send.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Send - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Send.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Send.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Send - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Send.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Send.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TcpClient.cpp

"$(INTDIR)\TcpClient.obj"	"$(INTDIR)\TcpClient.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Send.pch"


SOURCE=.\Thread.cpp

"$(INTDIR)\Thread.obj"	"$(INTDIR)\Thread.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Send.pch"



!ENDIF 

