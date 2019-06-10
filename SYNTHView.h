// SYNTHView.h : interface of the CSYNTHView class
//
/////////////////////////////////////////////////////////////////////////////

// BEGIN_IVWGEN
#include "resource.h"
#include <Ivf/Viewers/IvfExaminerViewer.h>
// END_IVWGEN

// IVF_EXAMPLE_BEGIN
// We'll use an SoSelection node as the "real" root of the scene
// graph contained in the component (to get selection behavior).
class SoSelection;
// IVF_EXAMPLE_END


class CSYNTHDoc;

// BEGIN_IVWGEN
class CSYNTHView : public CView , public CIvfExaminerViewer
// END_IVWGEN
{
protected: // create from serialization only
	CSYNTHView();
	DECLARE_DYNCREATE(CSYNTHView)


// Attributes
public:
	CSYNTHDoc* GetDocument();

    SoSelection *GetSelectionNode()
        { return m_pSelectionNode; }


	BOOL IsDocLoaded();
	BOOL IsSelected();
	UINT GetViewerViewMode();

// Operations
public:
	BOOL SaveAsBitmap(LPCTSTR pFilename);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSYNTHView)
public:
// BEGIN_IVWGEN
	virtual void OnInitialUpdate();
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
// END_IVWGEN

// IVF_EXAMPLE_BEGIN
	// This method forces the component to use the scene graph pointed to
	// by pRoot instead of the scene graph contained in the document.
	virtual void		IvfSetSceneGraph(SoNode *pRoot);

	// This method returns the scene graph contained in the component.
	virtual SoNode *	IvfGetSceneGraph();

	// This method causes the component to unreference it's scene graph.
	virtual void		IvfReleaseSceneGraph();
// IVF_EXAMPLE_END


	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSYNTHView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// IVF_EXAMPLE_BEGIN
    // Selection node to manage selection
    SoSelection *m_pSelectionNode;
// IVF_EXAMPLE_END


// Generated message map functions
protected:
	//{{AFX_MSG(CSYNTHView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
// BEGIN_IVWGEN
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnViewPicedit();
	afx_msg void OnUpdateViewPicedit(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnViewViewmodesSelectionmode();
	afx_msg void OnViewViewmodesViewingmode();
// END_IVWGEN
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SYNTHView.cpp
inline CSYNTHDoc* CSYNTHView::GetDocument()
   { return (CSYNTHDoc*)m_pDocument; }
#endif

extern CSYNTHView	*sview ;

/////////////////////////////////////////////////////////////////////////////
