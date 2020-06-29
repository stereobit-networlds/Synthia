// SYNTH.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SYNTH.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "SYNTHDoc.h"
#include "SYNTHView.h"

#include "lib0.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSYNTHApp

BEGIN_MESSAGE_MAP(CSYNTHApp, CWinApp)
	//{{AFX_MSG_MAP(CSYNTHApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_INFO, OnFileViewInfo)
	ON_UPDATE_COMMAND_UI(ID_FILE_INFO, OnUpdateFileViewInfo)
	ON_COMMAND(ID_OBJECT_RIGHT, OnRight)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_RIGHT, OnUpdateRight)
    ON_COMMAND(ID_OBJECT_LEFT, OnLeft)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_LEFT, OnUpdateLeft)
	ON_COMMAND(ID_SHOWREFPOINTS, OnShowrefpoints)
	ON_UPDATE_COMMAND_UI(ID_SHOWREFPOINTS, OnUpdateShowrefpoints)
	ON_COMMAND(ID_OBJSIDE_BACK, OnObjsideBack)
	ON_UPDATE_COMMAND_UI(ID_OBJSIDE_BACK, OnUpdateObjsideBack)
	ON_COMMAND(ID_OBJSIDE_LEFT, OnObjsideLeft)
	ON_UPDATE_COMMAND_UI(ID_OBJSIDE_LEFT, OnUpdateObjsideLeft)
	ON_COMMAND(ID_OBJSIDE_FRONT, OnObjsideFront)
	ON_UPDATE_COMMAND_UI(ID_OBJSIDE_FRONT, OnUpdateObjsideFront)
	ON_COMMAND(ID_OBJSIDE_RIGHT, OnObjsideRight)
	ON_UPDATE_COMMAND_UI(ID_OBJSIDE_RIGHT, OnUpdateObjsideRight)
	ON_COMMAND(ID_OBJSIDE_TOP, OnObjsideTop)
	ON_UPDATE_COMMAND_UI(ID_OBJSIDE_TOP, OnUpdateObjsideTop)
	ON_COMMAND(ID_OBJSIDE_BOTTOM, OnObjsideBottom)
	ON_UPDATE_COMMAND_UI(ID_OBJSIDE_BOTTOM, OnUpdateObjsideBottom)
	//}}AFX_MSG_MAP

	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSYNTHApp construction

CSYNTHApp::CSYNTHApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	//<<<<<<<<<<<  initialization  >>>>>>>>>>>
	//init light editor
	TheLightIs = false ; //no 
    //init direction ...left,right... 
	ObjDirection = 1;
	//init side object position...
	ObjSidePosition = 2003 ; //=_BACK_
	//init ref points rendering
	ShowRefPoints = 0;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSYNTHApp object

CSYNTHApp theApp;

// BEGIN_IVWGEN
IVF_AFX_CONVERSION_METHOD(CSYNTHView,CSYNTHDoc)
// END_IVWGEN


/////////////////////////////////////////////////////////////////////////////
// CSYNTHApp initialization

BOOL CSYNTHApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

// BEGIN_IVWGEN
	static int cArgs[]= {
		TRUE,		// Decoration
		TRUE,	// URL Display
		TRUE,					// Viewpoints
		TRUE};		// URL Fetch

	IVF_INIT_INSTANCE(
		 this,
		 IvfCvtAfxView,
		 IvfCvtIvfComponent,
		 NULL,
		 NULL,
		 IvfCvtAfxDoc,
		 IvfCvtIvfDoc,
		 IvfCvtAfxFrame,
		 (void *)cArgs,
		 FALSE);
// END_IVWGEN

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_SYNTHTYPE,
		RUNTIME_CLASS(CSYNTHDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSYNTHView));
	AddDocTemplate(pDocTemplate);

// BEGIN_IVWGEN
	CIvfApp::m_pDocTemplate = pDocTemplate;
// END_IVWGEN


	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;

	m_pMainWnd = pMainFrame;

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
			//  need to intercept FileNew so we can
			//  call our own OnFileNew directly
	   {
	   //OnFileNew();  //<<<<<<<<<<<<<-----------------  new at begin.......
	   if (!m_pMainWnd) return(FALSE);
	   m_nCmdShow = SW_SHOWNORMAL;
	   }

	else if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// OPEN DATABASE / DATASETS
	// open the database 
	if (!m_database.IsOpen())
	{
		try
		{
			m_database.Open("/CKOSMOS/SYNTH/DATA/DATA.mdb");
		}
		catch (CDaoException* e)
		{
			// Assume failure is becauase we couldn't find the file
			AfxMessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
		}
	}

	// create the table defs, recordsets

	tdf_eidh0 = new CDaoTableDef(&m_database) ;
	tdf_omad  = new CDaoTableDef(&m_database) ;
	tdf_mrec  = new CDaoTableDef(&m_database) ;

	tdf_eidh0->Open("EIDH0") ;
	tdf_omad->Open("OMAD") ;
	tdf_mrec->Open("_MREC") ;

	rs_eidh0 = new CDaoRecordset ;
	rs_omad	 = new CDaoRecordset ;
	rs_mrec  = new CDaoRecordset ;

	// open EIDH0 dataset
	try
	{
		rs_eidh0->Open(tdf_eidh0);
	}
	catch (CDaoException* e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
	}

	// open OMAD dataset
	try
	{
		rs_omad->Open(tdf_omad);
	}
	catch (CDaoException* e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
	}
	// open _MREC dataset
	try
	{
		rs_mrec->Open(tdf_mrec);
	}
	catch (CDaoException* e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#include <Ivf/Viewers/IvfRenderArea.h>

class CAboutDlg : public CDialog, public CIvfRenderArea
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
// BEGIN_IVWGEN
	virtual BOOL OnInitDialog();
// END_IVWGEN
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// BEGIN_IVWGEN
BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	static int cArgs[]= {FALSE,FALSE,FALSE,FALSE};

	CWnd *pWnd = GetDlgItem(IDC_ABOUT_TEXT) ;
	IvfCreateComponent(pWnd,(void *)cArgs);

#if _MSC_VER < 1100
	IvfSpinText("MICROSOFT\nVisual C++\n4.2");

#else
	IvfSpinText("MICROSOFT\nVisual C++\n5.0");

#endif

	return TRUE;
}
// END_IVWGEN

// App command to run the dialog
void CSYNTHApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSYNTHApp commands

static char *def_ext[] = {NULL,".sn3", ".iv", ".wrl"};
#define NUM_EXT_VALS	4

// BEGIN_IVWGEN
void CSYNTHApp::OnFileOpen() 
{

	const char szFilter[] =
	"Synthesis Files (*.sn3)\0*.sn3\0Inventor Files (*.iv)\0*.iv\0Vrml Files (*.wrl)\0*.wrl\0";


	const char szTitle[] = "Open File";

	CFileDialog openDlg(TRUE);

	openDlg.m_ofn.lpstrTitle = szTitle;
	openDlg.m_ofn.lpstrFilter = szFilter ;
	openDlg.m_ofn.nFilterIndex = m_nLastOpenedFilterIX;
	openDlg.m_ofn.lpstrCustomFilter = NULL;
	openDlg.m_ofn.lpstrDefExt = def_ext[m_nLastOpenedFilterIX];
	openDlg.m_ofn.nMaxCustFilter = 0;

	openDlg.m_ofn.Flags |= (OFN_HIDEREADONLY | OFN_PATHMUSTEXIST) ;

	if (openDlg.DoModal() == IDOK)
	{
		CIvfDocument *pIvfDoc = IvfGetDocument();
		if (pIvfDoc &&
			pIvfDoc->m_eOpenType == CIvfDocument::IVFDOC_OPEN_IMPORT)
			pIvfDoc->IvfOnOpenDocumentMessage(openDlg.m_ofn.lpstrFile) ;
		else
		{
			CString newName = openDlg.m_ofn.lpstrFile;
			CSYNTHDoc *pDoc =
   		    (CSYNTHDoc *)OpenDocumentFile(newName);

			if (openDlg.m_ofn.nFilterIndex < NUM_EXT_VALS)
					m_nLastOpenedFilterIX = openDlg.m_ofn.nFilterIndex;

			pDoc->OpenSceneFile(openDlg.m_ofn.nFilterIndex);
		}
	}
}


int CSYNTHApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class

    IvfExitInstance();
	
	return CWinApp::ExitInstance();
}


BOOL CSYNTHApp::OnIdle(LONG lCount) 
{
	CIvfApp::IvfOnIdle(lCount);
	
	return CWinApp::OnIdle(lCount);
}


//  PreTranslateMessage -
//  thread messages are forwarded to the document for handling.
//
BOOL CSYNTHApp::PreTranslateMessage(MSG *pMsg) 
{
   CIvfDocument *pDoc = IvfGetDocument();
   if (!(pDoc && pDoc->IvfPreTranslateMessage(pMsg)))
      return CWinApp::PreTranslateMessage(pMsg);

return(TRUE);
}

void CSYNTHApp::OnFileViewInfo() 
{
CIvfDocument *pIvfDoc = IvfGetDocument();
pIvfDoc->OnFileViewInfo();
}

void CSYNTHApp::OnUpdateFileViewInfo(CCmdUI* pCmdUI) 
{
pCmdUI->Enable(TRUE);
}


//  OnFileNew --
//  Overridden to prevent prompt for filetype in case of multiple
//  document types.
void CSYNTHApp::OnFileNew()
{
POSITION pos = GetFirstDocTemplatePosition();
CDocTemplate* pTemplate = GetNextDocTemplate(pos);
pTemplate->OpenDocumentFile(NULL);

}
// END_IVWGEN

//******************************************************** my routines

//<<<<<<<<<<<<<<<   ÊÁÔÅÕÈÕÍÓÇ ÓÕÍÈÅÓÇÓ   >>>>>>>>>>>>>>>>>>>>>
void CSYNTHApp::OnRight()
{
  ObjDirection = 1;
}

void CSYNTHApp::OnUpdateRight(CCmdUI* pCmdUI) 
{
    ASSERT( ObjDirection != NULL );
    if (ObjDirection == 1)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}

void CSYNTHApp::OnLeft()
{
  ObjDirection = 2;
}

void CSYNTHApp::OnUpdateLeft(CCmdUI* pCmdUI) 
{
    ASSERT( ObjDirection != NULL );
    if (ObjDirection == 2)
        //pCmdUI->Enable( TRUE );	
		pCmdUI->SetCheck(TRUE);
    else
        //pCmdUI->Enable( FALSE );
		pCmdUI->SetCheck(FALSE);
}

//<<<<<<<<<<<<<<<   SHOW REFERENCE POINTS   >>>>>>>>>>>>>>>>>>>>>
void CSYNTHApp::OnShowrefpoints() 
{
	// TODO: Add your command handler code here
	if (ShowRefPoints) ShowRefPoints = 0;
	              else ShowRefPoints = 1;
}

void CSYNTHApp::OnUpdateShowrefpoints(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if (ShowRefPoints)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);	
}

//<<<<<<<<<<<<<<<   ÐËÅÕÑÁ ÔÏÐÏÈÅÔÇÓÇÓ ÔÏÕ ÁÍÔÉÊÅÉÌÅÍÏÕ   >>>>>>>>>>>>>>>>>>>>>
void CSYNTHApp::OnObjsideBack() 
{
	// TODO: Add your command handler code here
	ObjSidePosition = 2003;
}

void CSYNTHApp::OnUpdateObjsideBack(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (ObjSidePosition==2003)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
	
}

void CSYNTHApp::OnObjsideLeft() 
{
	// TODO: Add your command handler code here
	ObjSidePosition = 2000;
}

void CSYNTHApp::OnUpdateObjsideLeft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (ObjSidePosition==2000)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}

void CSYNTHApp::OnObjsideFront() 
{
	// TODO: Add your command handler code here
	ObjSidePosition = 2001;
}

void CSYNTHApp::OnUpdateObjsideFront(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (ObjSidePosition==2001)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}

void CSYNTHApp::OnObjsideRight() 
{
	// TODO: Add your command handler code here
	ObjSidePosition = 2002;
}

void CSYNTHApp::OnUpdateObjsideRight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (ObjSidePosition==2002)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}

void CSYNTHApp::OnObjsideTop() 
{
	// TODO: Add your command handler code here
	ObjSidePosition = 2004;
	
}

void CSYNTHApp::OnUpdateObjsideTop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (ObjSidePosition==2004)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}

void CSYNTHApp::OnObjsideBottom() 
{
	// TODO: Add your command handler code here
	ObjSidePosition = 2005;
}

void CSYNTHApp::OnUpdateObjsideBottom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (ObjSidePosition==2005)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}
