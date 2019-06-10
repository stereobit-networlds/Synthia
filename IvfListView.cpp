// IvfListView.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"
#include "IvfListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IvfListView

IMPLEMENT_DYNCREATE(IvfListView, CListView)

IvfListView::IvfListView()
{
}

IvfListView::~IvfListView()
{
}


BEGIN_MESSAGE_MAP(IvfListView, CListView)
	//{{AFX_MSG_MAP(IvfListView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IvfListView drawing

void IvfListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// IvfListView diagnostics

#ifdef _DEBUG
void IvfListView::AssertValid() const
{
	CListView::AssertValid();
}

void IvfListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// IvfListView message handlers

/*
// addin by me 
BOOL CIvfListView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
    // Modified for IvfTreeView example
	//return CTreeView::PreCreateWindow(cs);

    if (!CListView::PreCreateWindow(cs))
        return FALSE;

     Set desired options for TreeView
    cs.style |= TVS_HASLINES | TVS_LINESATROOT |
                TVS_HASBUTTONS | TVS_SHOWSELALWAYS;
   
    return TRUE;
}

void CIvfListView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
    CSYNTHDoc *pDoc = (CSYNTHDoc *)GetDocument();
    
    // Expand root item (purely esthetic)
    //
    // Note: Originally did this in the SetRootNode function, but the
    //       change got overridden by some other call later, so there
    //       is a timing issue that requires the call to be here.
    HTREEITEM hRootItem = GetTreeCtrl().GetRootItem();
    if (hRootItem) {
        GetTreeCtrl().SelectItem( hRootItem );
        GetTreeCtrl().Expand( hRootItem, TVE_EXPAND );
    }
}

void CIvfListView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
    CSYNTHDoc *pDoc = (CSYNTHDoc *)GetDocument();
    
    // Re-generate tree view on scene graph change
    UpdateTreeControl( pDoc->IvfGetDocSceneGraph());	
}
*/


