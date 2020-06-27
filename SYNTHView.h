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

// We'll need an instance of SoWinClipboard for cut/copy/paste
class SoWinClipboard;   //SelectB
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

	SoSeparator *sep_buffer;  //aux node for copy/paste 

    SoSelection *GetSelectionNode()
        { return m_pSelectionNode; }

	SoPath *lightpath;

    // Colors
	float m_ClearColorRed;
	float m_ClearColorGreen;
	float m_ClearColorBlue;

	//options
	int headlight_option ;
	int decoration_option ;
	int drawStyle_option ;

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
    
	void OnDelete();
	void OnExtDelete();
	void OnUnGroup();
	bool StartScene();
    void DrawBox(float x1,float y1,float z1,
			     float x2,float y2,float z2);

protected:
// IVF_EXAMPLE_BEGIN
    // Selection node to manage selection
    SoSelection *m_pSelectionNode; 

    SoWinClipboard *m_pClipboard;   //SelectB

    static void OnPasteCB( void *data, SoPathList *pList );
// IVF_EXAMPLE_END


// Generated message map functions
protected:
	//{{AFX_MSG(CSYNTHView)
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnViewPicedit();
	afx_msg void OnUpdateViewPicedit(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnExtentedCut();
	afx_msg void OnUpdateExtentedCut(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnViewViewmodesSelectionmode();
	afx_msg void OnViewViewmodesViewingmode();
	afx_msg void OnUpdateUnGroup(CCmdUI* pCmdUI);
	afx_msg void OnHidebase();
	afx_msg void OnUpdateHidebase(CCmdUI* pCmdUI);
	afx_msg void OnHidewalls();
	afx_msg void OnUpdateHidewalls(CCmdUI* pCmdUI);
	afx_msg void OnHideobjs();
	afx_msg void OnUpdateHideobjs(CCmdUI* pCmdUI);
	afx_msg void OnHideselection();
	afx_msg void OnUpdateHideselection(CCmdUI* pCmdUI);
	afx_msg void OnShowall();
	afx_msg void OnUpdateShowall(CCmdUI* pCmdUI);
	afx_msg void OnChbackcolor();
	afx_msg void OnUpdateChbackcolor(CCmdUI* pCmdUI);
	afx_msg void OnHomeposition();
	afx_msg void OnUpdateHomeposition(CCmdUI* pCmdUI);
	afx_msg void OnSethomeposition();
	afx_msg void OnUpdateSethomeposition(CCmdUI* pCmdUI);
	afx_msg void OnHeadlight();
	afx_msg void OnUpdateHeadlight(CCmdUI* pCmdUI);
	afx_msg void OnInvdecoration();
	afx_msg void OnUpdateInvdecoration(CCmdUI* pCmdUI);
	afx_msg void OnDrawAsIs();
	afx_msg void OnUpdateDrawAsIs(CCmdUI* pCmdUI);
	afx_msg void OnDrawHiddenLine();
	afx_msg void OnUpdateDrawHiddenLine(CCmdUI* pCmdUI);
	afx_msg void OnDrawNoTexture();
	afx_msg void OnUpdateDrawNoTexture(CCmdUI* pCmdUI);
	afx_msg void OnDrawLowComp();
	afx_msg void OnUpdateDrawLowComp(CCmdUI* pCmdUI);
	afx_msg void OnDrawLine();
	afx_msg void OnUpdateDrawLine(CCmdUI* pCmdUI);
	afx_msg void OnDrawPoint();
	afx_msg void OnUpdateDrawPoint(CCmdUI* pCmdUI);
	afx_msg void OnDrawBbox();
	afx_msg void OnUpdateDrawBbox(CCmdUI* pCmdUI);
	afx_msg void OnViewing();
	afx_msg void OnUpdateViewing(CCmdUI* pCmdUI);
	afx_msg void OnDirlight();
	afx_msg void OnUpdateDirlight(CCmdUI* pCmdUI);
	afx_msg void OnMaterialedit();
	afx_msg void OnUpdateMaterialedit(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SYNTHView.cpp
inline CSYNTHDoc* CSYNTHView::GetDocument()
   { return (CSYNTHDoc*)m_pDocument; }
#endif

extern CSYNTHView	*sview ;

/////////////////////////////////////////////////////////////////////////////
