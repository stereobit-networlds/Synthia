// SYNTHDoc.h : interface of the CSYNTHDoc class
//
/////////////////////////////////////////////////////////////////////////////
// BEGIN_IVWGEN
#include <Ivf/IvfDocument.h>
// END_IVWGEN


#include "GLib0.h"
#include "WorldBase.h"

#include <Inventor/SbLinear.h>

// BEGIN_IVWGEN
class CSYNTHDoc : public CDocument , public CIvfDocument
{
// END_IVWGEN
protected: // create from serialization only
	CSYNTHDoc();
	DECLARE_DYNCREATE(CSYNTHDoc)

	BOOLEAN m_bContainsCamera;

// Attributes
public:

// Operations
public:

	SoSeparator *root ;		// the scene root

	CObject *Obj[100] ;		// then various RoomBase, WorldBase, ...
	int ObjCount ;			// number of Objs
	int SelId ;				// selected Obj[SelId]
	BOOL	new_object ;	// true if a new objcect is added
	int    proto ;          // true (1) if first extObj is added
	int ob_offset ;			// counter for the GExternal objects

	void SetSelectedObj ( SoSelection *sel ) ;
	void InventorToObjects() ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSYNTHDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSYNTHDoc();
	virtual void IvfSetupUrlFetchCallback(void);
	BOOL HasAnchors(void) { return (m_pAnchorList != NULL); }
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSYNTHDoc)
	afx_msg void OnFileImport();
	afx_msg void OnUpdateFileImport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewpoints(CCmdUI *pCmdUI);
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileReload();
	afx_msg void OnUpdateFileReload(CCmdUI *pCmdUI);
	afx_msg void OnNewBox();
	afx_msg void OnNewSphere();
	afx_msg void OnProperties();
	afx_msg void OnKataxkoyzin();
	afx_msg void OnSelectObj();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

extern CSYNTHDoc	*sdoc ;
extern SbVec3f		picked_point ;
extern SbVec3f		picked_normal ;

/////////////////////////////////////////////////////////////////////////////
