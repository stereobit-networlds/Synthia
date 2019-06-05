// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SYNTH.h"

#include "SYNTHView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
// BEGIN_IVWGEN
	ON_WM_QUERYNEWPALETTE()
	ON_WM_DROPFILES()
// END_IVWGEN
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,	// viewer indicator
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

// BEGIN_IVWGEN
	IvfOnCreate( this );
// END_IVWGEN

	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndStatusBar.SetPaneInfo(1, 1, SBPS_NORMAL, 60);
		//  use the small window for viewer type


        // TODO: Remove this if you don't want tool tips or a resizeable toolbar
        m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
                CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs


// BEGIN_IVWGEN
	cs.cx = 640;
	cs.cy = 480;
// END_IVWGEN
		 
	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

// BEGIN_IVWGEN
void CMainFrame::IvfSetStatusText(const char *pText)
{
	m_wndStatusBar.SetWindowText( pText );
}
// END_IVWGEN


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

// BEGIN_IVWGEN

BOOL CMainFrame::OnQueryNewPalette()
{
	IvfOnQueryNewPalette() ;
	return CMDIFrameWnd::OnQueryNewPalette();
}

#include <Ivf/IvfDocument.h>
void CMainFrame::OnDropFiles(HDROP hDropInfo) 
{
char newName[2048];
	::DragQueryFile(hDropInfo,0,newName,2048);

    if(! CIvfDocument::IvfIsInventorFile(newName) )
    {

          ::MessageBox( 
                    NULL,
                    "Attempt to drop an invalid file.",
                    "Viewer Error",
                    MB_OK | MB_ICONEXCLAMATION | MB_APPLMODAL 
                 );
        return; // Not a supported file
    }

	CFrameWnd::OnDropFiles(hDropInfo);
}


BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if(IvfOnCommand(wParam,lParam))
	return TRUE;
	return CMDIFrameWnd::OnCommand(wParam, lParam);
}


void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
        IvfOnUpdateFrameTitle(bAddToTitle,m_strTitle) ;
}
// END_IVWGEN

