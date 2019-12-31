; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDialogItem
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SoftList.h"

ClassCount=6
Class1=CSoftListApp
Class2=CSoftListDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_SOFTLIST_DIALOG
Resource2=IDR_MAINFRAME
Class4=CSoftListBox
Resource3=IDD_ABOUTBOX
Class5=CListItemDlg
Class6=CDialogItem
Resource4=IDD_DIALOG_LIST_ITEM

[CLS:CSoftListApp]
Type=0
HeaderFile=SoftList.h
ImplementationFile=SoftList.cpp
Filter=N
LastObject=CSoftListApp

[CLS:CSoftListDlg]
Type=0
HeaderFile=SoftListDlg.h
ImplementationFile=SoftListDlg.cpp
Filter=D
LastObject=CSoftListDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=SoftListDlg.h
ImplementationFile=SoftListDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SOFTLIST_DIALOG]
Type=1
Class=CSoftListDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SOFT_LIST,listbox,1352728865

[CLS:CSoftListBox]
Type=0
HeaderFile=SoftListBox.h
ImplementationFile=SoftListBox.cpp
BaseClass=CCheckListBox
Filter=W
LastObject=CSoftListBox
VirtualFilter=bWC

[DLG:IDD_DIALOG_LIST_ITEM]
Type=1
Class=CListItemDlg
ControlCount=7
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC_NAME,static,1342308352
Control4=IDC_STATIC_SIZE,static,1342308352
Control5=IDC_BUTTON_INSTALL,button,1342242816
Control6=IDC_STATIC_DESCRIPTION,static,1342308352
Control7=IDC_STATIC_ICON,static,1342177795

[CLS:CListItemDlg]
Type=0
HeaderFile=ListItemDlg.h
ImplementationFile=ListItemDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CListItemDlg

[CLS:CDialogItem]
Type=0
HeaderFile=DialogItem.h
ImplementationFile=DialogItem.cpp
BaseClass=CDialog
Filter=W
LastObject=CDialogItem
VirtualFilter=dWC

