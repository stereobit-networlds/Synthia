// dummy.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"
#include "dummy.h"

#include "SYNTHDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dummy

IMPLEMENT_DYNCREATE(dummy, CTreeView)

dummy::dummy()
{
}

dummy::~dummy()
{
}


BEGIN_MESSAGE_MAP(dummy, CTreeView)
	//{{AFX_MSG_MAP(dummy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dummy drawing

void dummy::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// dummy diagnostics

#ifdef _DEBUG
void dummy::AssertValid() const
{
	CTreeView::AssertValid();
}

void dummy::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// dummy message handlers
