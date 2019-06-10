// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "SYNTH.h"

#include "ChildFrm.h"

#include "SYNTHDoc.h"
#include "SYNTHView.h"
#include <afxcview.h>   //need this to use CTreeView
#include "IvfTreeView.h"
#include "dummy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}



BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers


BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT lpcs,CCreateContext* pContext)
{
    BOOL bRet;

	// For this example use a static splitter because we always want to
	// have two panes and they may be views onto different documents.
	//
	// Note: The 2nd and 3rd params are "num_rows" and "num_cols".
	// We want the window split into two side-by-side panes.
	if (!m_wndSplitter.CreateStatic( this, 1, 2 ))
		return FALSE;

	int thirdWidth = lpcs->cx / 3;

	// A static splitter requires that all the panes be created here.
	bRet = m_wndSplitter.CreateView( 0, 0,
		RUNTIME_CLASS(CSYNTHView), CSize(2*thirdWidth,1), pContext );

	bRet = m_wndSplitter.CreateView( 0, 1,
		RUNTIME_CLASS(CIvfTreeView), CSize(thirdWidth,1), pContext );

	return TRUE;

//**********<<<<< from book mfc
//	return m_wndSplitter.Create(this, 2, 2, CSize(1,1), pContext) ;
}


