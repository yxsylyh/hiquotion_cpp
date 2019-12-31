; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWaveLibDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WaveLib.h"

ClassCount=4
Class1=CWaveLibApp
Class2=CWaveLibDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_WAVELIB_DIALOG

[CLS:CWaveLibApp]
Type=0
HeaderFile=WaveLib.h
ImplementationFile=WaveLib.cpp
Filter=N

[CLS:CWaveLibDlg]
Type=0
HeaderFile=WaveLibDlg.h
ImplementationFile=WaveLibDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=WaveLibDlg.h
ImplementationFile=WaveLibDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WAVELIB_DIALOG]
Type=1
Class=CWaveLibDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON_WAVE_TEST,button,1342242816

