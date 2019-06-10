; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=DeleteObj
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SYNTH.h"
LastPage=0

ClassCount=23
Class1=CSYNTHApp
Class2=CSYNTHDoc
Class3=CSYNTHView
Class4=CMainFrame

ResourceCount=21
Resource1=IDD_ABOUTBOX
Resource2=SYNTH_SELECT_OBJ
Resource3=SYNTH_SELECT_OBJ (Greek)
Class5=CAboutDlg
Class6=CChildFrame
Resource4=SYNTH_ROOMBASE_PROP
Class7=CWorldBase
Resource5=IDR_SYNTHTYPE
Class8=CWorldBasePro
Resource6=IDR_MAINFRAME
Class9=CWizz0
Class10=CGLib0
Class11=CRoomBase
Class12=CRoomWall
Resource7=SYNTH_WIZZ0
Resource8=SYNTH_ROOMWALL_PROP (Greek)
Class13=CRoomWallPro
Class14=CSelectObj
Class15=LObj2
Class16=CGObject
Class17=CGExternal
Resource9=SYNTH_WORLDBASE_PROP
Class18=CRoomBasePro
Resource10=SYNTH_ROOMWALL_PROP
Resource11=SYNTH_GEXTERNAL_PROP
Class19=GExternalProp
Resource12=SYNTH_ROOMBASE_PROP (Greek)
Resource13=IDD_ABOUTBOX (English (U.S.))
Resource14=SYNTH_WIZZ0 (Greek)
Resource15=SYNTH_WORLDBASE_PROP (Greek)
Resource16=IDR_MAINFRAME (English (U.S.))
Resource17=IDR_MAINFRAME (Greek)
Resource18=IDR_MYTBAR (English (U.S.))
Class20=CIvfTreeView
Class21=dummy
Class22=IvfListView
Resource19=IDR_SYNTHTYPE (Greek)
Class23=DeleteObj
Resource20=SYNTH_DELETE_OBJ (Greek)
Resource21=SYNTH_GEXTERNAL_PROP (Greek)

[CLS:CSYNTHApp]
Type=0
HeaderFile=SYNTH.h
ImplementationFile=SYNTH.cpp
Filter=N
LastObject=65535

[CLS:CSYNTHDoc]
Type=0
HeaderFile=SYNTHDoc.h
ImplementationFile=SYNTHDoc.cpp
Filter=N
LastObject=CSYNTHDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CSYNTHView]
Type=0
HeaderFile=SYNTHView.h
ImplementationFile=SYNTHView.cpp
Filter=C
LastObject=ID_VIEW_STATUS_BAR

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M

[CLS:CAboutDlg]
Type=0
HeaderFile=SYNTH.cpp
ImplementationFile=SYNTH.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_RELOAD
Command4=ID_FILE_IMPORT
Command5=ID_FILE_PRINT_SETUP
Command6=ID_FILE_MRU_FILE1
Command7=ID_FILE_INFO
Command8=ID_APP_EXIT
Command9=ID_VIEW_TOOLBAR
Command10=ID_VIEW_STATUS_BAR
Command11=ID_HELP_FINDER
Command12=ID_APP_ABOUT
CommandCount=12

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=9
Command8=ID_APP_ABOUT
Command9=ID_CONTEXT_HELP

[MNU:IDR_SYNTHTYPE]
Type=1
Class=CSYNTHView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_RELOAD
Command4=ID_FILE_IMPORT
Command5=ID_FILE_CLOSE
Command6=ID_FILE_SAVE
Command7=ID_FILE_SAVE_AS
Command8=ID_FILE_PRINT
Command9=ID_FILE_PRINT_PREVIEW
Command10=ID_FILE_PRINT_SETUP
Command11=ID_FILE_INFO
Command12=ID_APP_EXIT
Command13=ID_EDIT_UNDO
Command14=ID_EDIT_CUT
Command15=ID_EDIT_COPY
Command16=ID_EDIT_PASTE
Command17=SYNTH_NEW_SPHERE
Command18=SYNTH_PROPERTIES
Command19=SYNTH_KATAXKOYZIN
Command20=SYNTH_SELECT
Command21=ID_VIEW_TOOLBAR
Command22=ID_VIEW_STATUS_BAR
Command23=ID_VIEW_PICEDIT
Command24=ID_WINDOW_NEW
Command25=ID_WINDOW_CASCADE
Command26=ID_WINDOW_TILE_HORZ
Command27=ID_WINDOW_ARRANGE
Command28=IDM_VIEWPOINTS
Command29=ID_HELP_FINDER
Command30=ID_APP_ABOUT
CommandCount=30

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=16
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_CONTEXT_HELP
CommandCount=9

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
CommandCount=16

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_ABOUT_TEXT,static,1342308352

[DLG:SYNTH_WORLDBASE_PROP]
Type=1
Class=CWorldBasePro
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NAME,edit,1350631552
Control4=IDC_ADDRESS,edit,1350631552
Control5=IDC_CITY,edit,1350631552
Control6=IDC_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354
Control9=IDC_STATIC,static,1342308354
Control10=IDC_TEL,edit,1350631552

[CLS:CWorldBasePro]
Type=0
HeaderFile=WorldBase.h
ImplementationFile=WorldBase.cpp
BaseClass=CDialog
Filter=D
LastObject=CWorldBasePro
VirtualFilter=dWC

[DLG:SYNTH_WIZZ0]
Type=1
Class=CWizz0
ControlCount=50
Control1=IDC_MHKOS0,edit,1350631552
Control2=IDC_ANGLE0,edit,1350631552
Control3=IDC_TOIXOMA0,edit,1350631552
Control4=IDC_MHKOS1,edit,1350631552
Control5=IDC_ANGLE1,edit,1350631552
Control6=IDC_TOIXOMA1,edit,1350631552
Control7=IDC_MHKOS2,edit,1350631552
Control8=IDC_ANGLE2,edit,1350631552
Control9=IDC_TOIXOMA2,edit,1350631552
Control10=IDC_MHKOS3,edit,1350631552
Control11=IDC_ANGLE3,edit,1350631552
Control12=IDC_TOIXOMA3,edit,1350631552
Control13=IDC_MHKOS4,edit,1350631552
Control14=IDC_ANGLE4,edit,1350631552
Control15=IDC_TOIXOMA4,edit,1350631552
Control16=IDC_MHKOS5,edit,1350631552
Control17=IDC_ANGLE5,edit,1350631552
Control18=IDC_TOIXOMA5,edit,1350631552
Control19=IDC_MHKOS6,edit,1350631552
Control20=IDC_ANGLE6,edit,1350631552
Control21=IDC_TOIXOMA6,edit,1350631552
Control22=IDC_MHKOS7,edit,1350631552
Control23=IDC_ANGLE7,edit,1350631552
Control24=IDC_TOIXOMA7,edit,1350631552
Control25=IDCANCEL,button,1342242816
Control26=IDOK,button,1342242817
Control27=IDC_STATIC,static,1342308354
Control28=IDC_STATIC,static,1342308354
Control29=IDC_STATIC,static,1342308354
Control30=IDC_STATIC,static,1342308354
Control31=IDC_STATIC,static,1342308354
Control32=IDC_STATIC,static,1342308354
Control33=IDC_STATIC,static,1342308354
Control34=IDC_STATIC,static,1342308354
Control35=IDC_STATIC,static,1342308354
Control36=IDC_STATIC,static,1342308354
Control37=IDC_STATIC,static,1342308354
Control38=IDC_STATIC,static,1342308354
Control39=IDC_STATIC,static,1342308354
Control40=IDC_STATIC,static,1342308354
Control41=IDC_STATIC,static,1342308354
Control42=IDC_STATIC,static,1342308354
Control43=IDC_STATIC,static,1342308354
Control44=IDC_STATIC,static,1342308354
Control45=IDC_STATIC,static,1342308354
Control46=IDC_STATIC,static,1342308354
Control47=IDC_STATIC,static,1342308354
Control48=IDC_STATIC,static,1342308354
Control49=IDC_STATIC,static,1342308354
Control50=IDC_STATIC,static,1342308354

[CLS:CWizz0]
Type=0
HeaderFile=Wizz0.h
ImplementationFile=Wizz0.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CWizz0

[CLS:CGLib0]
Type=0
HeaderFile=\Ckosmos\lib\glib0.h
ImplementationFile=\ckosmos\lib\glib0.cpp
BaseClass=CWnd
LastObject=CGLib0

[CLS:CRoomWallPro]
Type=0
HeaderFile=RoomWall.h
ImplementationFile=RoomWall.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=65535

[DLG:SYNTH_SELECT_OBJ]
Type=1
Class=CSelectObj
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_VIEWER,static,1342308352
Control5=SYNTH_NEXT,button,1342242816
Control6=SYNTH_PRIOR,button,1342242816
Control7=SYNTH_CB_MONTELO,combobox,1344340226
Control8=SYNTH_CB_YLIKO,combobox,1344340226
Control9=SYNTH_CB_PORTAKI,combobox,1344340226
Control10=SYNTH_CB_SYRTARI,combobox,1344340226
Control11=SYNTH_CB_XEROYL,combobox,1344340226
Control12=SYNTH_CB_MPAZA,combobox,1344340226
Control13=SYNTH_CB_ANTIK,combobox,1344340226
Control14=IDC_STATIC,static,1342308354
Control15=IDC_STATIC,static,1342308354
Control16=IDC_STATIC,static,1342308354
Control17=IDC_STATIC,static,1342308354
Control18=IDC_STATIC,static,1342308354
Control19=IDC_STATIC,static,1342308354
Control20=IDC_STATIC,static,1342308354

[CLS:CSelectObj]
Type=0
HeaderFile=SelectObj.h
ImplementationFile=SelectObj.cpp
BaseClass=CDialog
Filter=D
LastObject=CSelectObj
VirtualFilter=dWC

[CLS:LObj2]
Type=0
HeaderFile=LObj2.h
ImplementationFile=LObj2.cpp
BaseClass=generic CWnd
Filter=W
LastObject=ID_APP_ABOUT

[CLS:CGExternal]
Type=0
HeaderFile=GExternal.h
ImplementationFile=GExternal.cpp
BaseClass=generic CWnd
Filter=W

[DLG:SYNTH_ROOMWALL_PROP]
Type=1
Class=CRoomBasePro
ControlCount=10
Control1=IDC_WIDTH,edit,1350631552
Control2=IDC_HEIGHT,edit,1350631552
Control3=IDC_PLAKAKI,edit,1350631552
Control4=IDC_PLAKAKI1,edit,1350631552
Control5=IDC_PLAKAKI2,edit,1350631552
Control6=IDCANCEL,button,1342242816
Control7=IDOK,button,1342242817
Control8=65535,static,1342308354
Control9=65535,static,1342308354
Control10=65535,static,1342308354

[DLG:SYNTH_ROOMBASE_PROP]
Type=1
Class=CRoomBasePro
ControlCount=6
Control1=IDC_PLAKAKI,edit,1350631552
Control2=IDC_PLAKAKI1,edit,1350631552
Control3=IDC_PLAKAKI2,edit,1350631552
Control4=IDCANCEL,button,1342242816
Control5=IDOK,button,1342242817
Control6=65535,static,1342308354

[CLS:CRoomBasePro]
Type=0
HeaderFile=roombase.h
ImplementationFile=roombase.cpp
BaseClass=CDialog

[DLG:SYNTH_GEXTERNAL_PROP]
Type=1
Class=GExternalProp
ControlCount=14
Control1=IDC_CODE,edit,1350631552
Control2=IDC_DESCR,edit,1350631552
Control3=IDC_YANGLE,edit,1350631552
Control4=IDCANCEL,button,1342242816
Control5=IDOK,button,1342242817
Control6=65535,static,1342308354
Control7=65535,static,1342308354
Control8=65535,static,1342308354
Control9=IDC_TOPOTH,edit,1350631552
Control10=65535,static,1342308354
Control11=IDC_XDIST,edit,1350631552
Control12=65535,static,1342308354
Control13=IDC_YDIST,edit,1350631552
Control14=65535,static,1342308354

[CLS:GExternalProp]
Type=0
HeaderFile=GExternal.h
ImplementationFile=GExternal.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:SYNTH_GEXTERNAL_PROP (Greek)]
Type=1
Class=GExternalProp
ControlCount=18
Control1=IDC_CODE,edit,1350631552
Control2=IDC_DESCR,edit,1350631552
Control3=IDC_YANGLE,edit,1350631552
Control4=IDCANCEL,button,1342242816
Control5=IDOK,button,1342242817
Control6=65535,static,1342308354
Control7=65535,static,1342308354
Control8=65535,static,1342308354
Control9=IDC_TOPOTH,edit,1350631552
Control10=65535,static,1342308354
Control11=IDC_XDIST,edit,1350631552
Control12=65535,static,1342308354
Control13=IDC_YDIST,edit,1350631552
Control14=65535,static,1342308354
Control15=IDC_LDIST,edit,1350631552
Control16=IDC_RDIST,edit,1350631552
Control17=65535,static,1342308354
Control18=65535,static,1342308354

[DLG:SYNTH_ROOMBASE_PROP (Greek)]
Type=1
Class=CRoomBasePro
ControlCount=6
Control1=IDC_PLAKAKI,edit,1350631552
Control2=IDC_PLAKAKI1,edit,1350631552
Control3=IDC_PLAKAKI2,edit,1350631552
Control4=IDCANCEL,button,1342242816
Control5=IDOK,button,1342242817
Control6=65535,static,1342308354

[DLG:SYNTH_ROOMWALL_PROP (Greek)]
Type=1
Class=CRoomBasePro
ControlCount=10
Control1=IDC_WIDTH,edit,1350631552
Control2=IDC_HEIGHT,edit,1350631552
Control3=IDC_PLAKAKI,edit,1350631552
Control4=IDC_PLAKAKI1,edit,1350631552
Control5=IDC_PLAKAKI2,edit,1350631552
Control6=IDCANCEL,button,1342242816
Control7=IDOK,button,1342242817
Control8=65535,static,1342308354
Control9=65535,static,1342308354
Control10=65535,static,1342308354

[DLG:SYNTH_SELECT_OBJ (Greek)]
Type=1
Class=CSelectObj
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_VIEWER,static,1342308352
Control5=SYNTH_NEXT,button,1342242816
Control6=SYNTH_PRIOR,button,1342242816
Control7=SYNTH_CB_MONTELO,combobox,1344340226
Control8=SYNTH_CB_YLIKO,combobox,1344340226
Control9=SYNTH_CB_PORTAKI,combobox,1344340226
Control10=SYNTH_CB_SYRTARI,combobox,1344340226
Control11=SYNTH_CB_XEROYL,combobox,1344340226
Control12=SYNTH_CB_MPAZA,combobox,1344340226
Control13=SYNTH_CB_ANTIK,combobox,1344340226
Control14=IDC_STATIC,static,1342308354
Control15=IDC_STATIC,static,1342308354
Control16=IDC_STATIC,static,1342308354
Control17=IDC_STATIC,static,1342308354
Control18=IDC_STATIC,static,1342308354
Control19=IDC_STATIC,static,1342308354
Control20=IDC_STATIC,static,1342308354

[DLG:SYNTH_WIZZ0 (Greek)]
Type=1
Class=CWizz0
ControlCount=50
Control1=IDC_MHKOS0,edit,1350631552
Control2=IDC_ANGLE0,edit,1350631552
Control3=IDC_TOIXOMA0,edit,1350631552
Control4=IDC_MHKOS1,edit,1350631552
Control5=IDC_ANGLE1,edit,1350631552
Control6=IDC_TOIXOMA1,edit,1350631552
Control7=IDC_MHKOS2,edit,1350631552
Control8=IDC_ANGLE2,edit,1350631552
Control9=IDC_TOIXOMA2,edit,1350631552
Control10=IDC_MHKOS3,edit,1350631552
Control11=IDC_ANGLE3,edit,1350631552
Control12=IDC_TOIXOMA3,edit,1350631552
Control13=IDC_MHKOS4,edit,1350631552
Control14=IDC_ANGLE4,edit,1350631552
Control15=IDC_TOIXOMA4,edit,1350631552
Control16=IDC_MHKOS5,edit,1350631552
Control17=IDC_ANGLE5,edit,1350631552
Control18=IDC_TOIXOMA5,edit,1350631552
Control19=IDC_MHKOS6,edit,1350631552
Control20=IDC_ANGLE6,edit,1350631552
Control21=IDC_TOIXOMA6,edit,1350631552
Control22=IDC_MHKOS7,edit,1350631552
Control23=IDC_ANGLE7,edit,1350631552
Control24=IDC_TOIXOMA7,edit,1350631552
Control25=IDCANCEL,button,1342242816
Control26=IDOK,button,1342242817
Control27=IDC_STATIC,static,1342308354
Control28=IDC_STATIC,static,1342308354
Control29=IDC_STATIC,static,1342308354
Control30=IDC_STATIC,static,1342308354
Control31=IDC_STATIC,static,1342308354
Control32=IDC_STATIC,static,1342308354
Control33=IDC_STATIC,static,1342308354
Control34=IDC_STATIC,static,1342308354
Control35=IDC_STATIC,static,1342308354
Control36=IDC_STATIC,static,1342308354
Control37=IDC_STATIC,static,1342308354
Control38=IDC_STATIC,static,1342308354
Control39=IDC_STATIC,static,1342308354
Control40=IDC_STATIC,static,1342308354
Control41=IDC_STATIC,static,1342308354
Control42=IDC_STATIC,static,1342308354
Control43=IDC_STATIC,static,1342308354
Control44=IDC_STATIC,static,1342308354
Control45=IDC_STATIC,static,1342308354
Control46=IDC_STATIC,static,1342308354
Control47=IDC_STATIC,static,1342308354
Control48=IDC_STATIC,static,1342308354
Control49=IDC_STATIC,static,1342308354
Control50=IDC_STATIC,static,1342308354

[DLG:SYNTH_WORLDBASE_PROP (Greek)]
Type=1
Class=CWorldBasePro
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NAME,edit,1350631552
Control4=IDC_ADDRESS,edit,1350631552
Control5=IDC_CITY,edit,1350631552
Control6=IDC_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354
Control9=IDC_STATIC,static,1342308354
Control10=IDC_TEL,edit,1350631552

[MNU:IDR_MAINFRAME (Greek)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_RELOAD
Command4=ID_FILE_IMPORT
Command5=ID_FILE_PRINT_SETUP
Command6=ID_FILE_MRU_FILE1
Command7=ID_FILE_INFO
Command8=ID_APP_EXIT
Command9=ID_VIEW_TOOLBAR
Command10=ID_VIEW_STATUS_BAR
Command11=ID_HELP_FINDER
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_SYNTHTYPE (Greek)]
Type=1
Class=CSYNTHView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_RELOAD
Command4=ID_FILE_IMPORT
Command5=ID_FILE_CLOSE
Command6=ID_FILE_SAVE
Command7=ID_FILE_SAVE_AS
Command8=ID_FILE_PRINT
Command9=ID_FILE_PRINT_PREVIEW
Command10=ID_FILE_PRINT_SETUP
Command11=ID_FILE_INFO
Command12=ID_APP_EXIT
Command13=ID_EDIT_UNDO
Command14=ID_EDIT_CUT
Command15=ID_EXTENTED_CUT
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_REPLACE
Command19=ID_UNGROUP
Command20=SYNTH_NEW_SPHERE
Command21=SYNTH_PROPERTIES
Command22=SYNTH_KATAXKOYZIN
Command23=SYNTH_SELECT
Command24=ID_OBJECT_RIGHT
Command25=ID_OBJECT_LEFT
Command26=ID_VIEW_TOOLBAR
Command27=ID_VIEW_STATUS_BAR
Command28=ID_VIEW_PICEDIT
Command29=ID_WINDOW_NEW
Command30=ID_WINDOW_CASCADE
Command31=ID_WINDOW_TILE_HORZ
Command32=ID_WINDOW_ARRANGE
Command33=IDM_VIEWPOINTS
Command34=ID_HELP_FINDER
Command35=ID_APP_ABOUT
CommandCount=35

[CLS:dummy]
Type=0
HeaderFile=dummy.h
ImplementationFile=dummy.cpp
BaseClass=CTreeView
Filter=C

[CLS:IvfListView]
Type=0
HeaderFile=IvfListView.h
ImplementationFile=IvfListView.cpp
BaseClass=CListView
Filter=C
LastObject=ID_APP_ABOUT

[CLS:CIvfTreeView]
Type=0
HeaderFile=ivftreeview.h
ImplementationFile=ivftreeview.cpp
BaseClass=CTreeView
Filter=C

[DLG:SYNTH_DELETE_OBJ (Greek)]
Type=1
Class=DeleteObj
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308353

[CLS:DeleteObj]
Type=0
HeaderFile=DeleteObj.h
ImplementationFile=DeleteObj.cpp
BaseClass=CDialog
Filter=D
LastObject=DeleteObj

[TB:IDR_MYTBAR (English (U.S.))]
Type=1
Command1=ID_BUTTON32828
Command2=ID_BUTTON32829
CommandCount=2

