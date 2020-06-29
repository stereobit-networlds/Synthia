// SYNTHDoc.h : interface of the CSYNTHDoc class
//
/////////////////////////////////////////////////////////////////////////////
// BEGIN_IVWGEN
#include <Ivf/IvfDocument.h>
// END_IVWGEN

#include "GLib0.h"
#include "WorldBase.h"
#include "GExternal.h"

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
	int	new_object ;	    // true if a new objcect is added
	int ob_offset ;			// counter for the GExternal objects

	int obj_selector ;      // my selection generated number 
	int obj_type ;          // object type 

	bool BATTERY ;
	bool REPLACE ;
    bool copy_mode ;        //boolean for copy/paste
	CGExternal *external_buffer ; //my data buffer for copy/paste

	int LastCopy ;          // last copied object number buffer
	bool UndoParam ;        // undo parameter

	bool Wizard ;           //wizard action basic scene building

	void InventorToObjects() ;
	void OpenSceneFile(int filetype) ;
	bool OnNewWizzard() ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSYNTHDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void SaveUndo();
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
    virtual void IvfSceneGraphChanged(); //IvfTreeView hack

// Generated message map functions
protected:
	//{{AFX_MSG(CSYNTHDoc)
	afx_msg void OnFileImport();
	afx_msg void OnUpdateFileImport(CCmdUI *pCmdUI);
	afx_msg void OnViewpoints();
	afx_msg void OnUpdateViewpoints(CCmdUI *pCmdUI);
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileReload();
	afx_msg void OnUpdateFileReload(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

extern CSYNTHDoc *sdoc ;
	
/////////////////////////////////////////////////////////////////////////////
