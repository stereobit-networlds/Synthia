// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

// BEGIN_IVWGEN
#include <Ivf/IvfMainfrm.h>
// END_IVWGEN

// BEGIN_IVWGEN
class CMainFrame : public CMDIFrameWnd , public CIvfMainFrame
// END_IVWGEN
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
// BEGIN_IVWGEN
	protected:
	virtual BOOL OnCommand(WPARAM wParam,LPARAM lParam);
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle) ;
// END_IVWGEN
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// BEGIN_IVWGEN
public:
virtual void IvfSetStatusText(const char *pText);
// END_IVWGEN

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
// BEGIN_IVWGEN
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnDropFiles(HDROP hDropInfo);
// END_IVWGEN
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
