# Microsoft Developer Studio Generated NMAKE File, Based on Recv.dsp
!IF $(CFG)" == "
CFG=Recv - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Recv - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Recv - Win32 Release" && "$(CFG)" != "Recv - Win32 Debug"
!MESSAGE 指定的配置 "$(CFG)" 无效.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Recv.mak" CFG="Recv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Recv - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Recv - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Recv - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# 开始自定义宏
OutDir=.\Release
# 结束自定义宏

ALL : "$(OUTDIR)\Recv.exe" "$(OUTDIR)\Recv.bsc"


CLEAN :
	-@erase "$(INTDIR)\Recv.obj"
	-@erase "$(INTDIR)\Recv.pch"
	-@erase "$(INTDIR)\Recv.res"
	-@erase "$(INTDIR)\Recv.sbr"
	-@erase "$(INTDIR)\RecvDlg.obj"
	-@erase "$(INTDIR)\RecvDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\SysUtils.obj"
	-@erase "$(INTDIR)\SysUtils.sbr"
	-@erase "$(INTDIR)\TcpServer.obj"
	-@erase "$(INTDIR)\TcpServer.sbr"
	-@erase "$(INTDIR)\Thread.obj"
	-@erase "$(INTDIR)\Thread.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Recv.bsc"
	-@erase "$(OUTDIR)\Recv.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Recv.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Recv.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Recv.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Recv.sbr" \
	"$(INTDIR)\RecvDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\SysUtils.sbr" \
	"$(INTDIR)\TcpServer.sbr" \
	"$(INTDIR)\Thread.sbr"

"$(OUTDIR)\Recv.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Recv.pdb" /machine:I386 /out:"$(OUTDIR)\Recv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Recv.obj" \
	"$(INTDIR)\RecvDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SysUtils.obj" \
	"$(INTDIR)\TcpServer.obj" \
	"$(INTDIR)\Thread.obj" \
	"$(INTDIR)\Recv.res"

"$(OUTDIR)\Recv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Recv - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OutDir=.\Debug
# 结束自定义宏

ALL : "$(OUTDIR)\Recv.exe" "$(OUTDIR)\Recv.bsc"


CLEAN :
	-@erase "$(INTDIR)\Recv.obj"
	-@erase "$(INTDIR)\Recv.pch"
	-@erase "$(INTDIR)\Recv.res"
	-@erase "$(INTDIR)\Recv.sbr"
	-@erase "$(INTDIR)\RecvDlg.obj"
	-@erase "$(INTDIR)\RecvDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\SysUtils.obj"
	-@erase "$(INTDIR)\SysUtils.sbr"
	-@erase "$(INTDIR)\TcpServer.obj"
	-@erase "$(INTDIR)\TcpServer.sbr"
	-@erase "$(INTDIR)\Thread.obj"
	-@erase "$(INTDIR)\Thread.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Recv.bsc"
	-@erase "$(OUTDIR)\Recv.exe"
	-@erase "$(OUTDIR)\Recv.ilk"
	-@erase "$(OUTDIR)\Recv.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Recv.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Recv.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Recv.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Recv.sbr" \
	"$(INTDIR)\RecvDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\SysUtils.sbr" \
	"$(INTDIR)\TcpServer.sbr" \
	"$(INTDIR)\Thread.sbr"

"$(OUTDIR)\Recv.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Recv.pdb" /debug /machine:I386 /nodefaultlib:"MSVCRT" /out:"$(OUTDIR)\Recv.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Recv.obj" \
	"$(INTDIR)\RecvDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SysUtils.obj" \
	"$(INTDIR)\TcpServer.obj" \
	"$(INTDIR)\Thread.obj" \
	"$(INTDIR)\Recv.res"

"$(OUTDIR)\Recv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Recv.dep")
!INCLUDE "Recv.dep"
!ELSE 
!MESSAGE Warning: cannot find "Recv.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Recv - Win32 Release" || "$(CFG)" == "Recv - Win32 Debug"
SOURCE=.\Recv.cpp

"$(INTDIR)\Recv.obj"	"$(INTDIR)\Recv.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Recv.pch"


SOURCE=.\Recv.rc

"$(INTDIR)\Recv.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\RecvDlg.cpp

"$(INTDIR)\RecvDlg.obj"	"$(INTDIR)\RecvDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Recv.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Recv - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Recv.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Recv.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Recv - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Recv.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Recv.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\SysUtils.cpp

"$(INTDIR)\SysUtils.obj"	"$(INTDIR)\SysUtils.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Recv.pch"


SOURCE=.\TcpServer.cpp

"$(INTDIR)\TcpServer.obj"	"$(INTDIR)\TcpServer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Recv.pch"


SOURCE=.\Thread.cpp

"$(INTDIR)\Thread.obj"	"$(INTDIR)\Thread.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Recv.pch"



!ENDIF 

