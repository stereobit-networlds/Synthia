// IvfTreeView.h : header file
//
// Copyright (C) 1996 Template Graphics Software, Inc.
// All Rights Reserved.
//
// Author: Mike Heck
//
// An MFC view class, derived from CTreeView, that displays an Inventor
// scene graph using the Microsoft treeview control (same as you see in
// File Manager etc).
//
// If the scene graph contains an SoSelection node, then CIvfTreeView
// can optionally synchronize with the selection list.  Selecting an
// object in the scene graph will select the corresponding item in the
// tree and selecting an item in the tree will select the corresponding
// object in the scene graph.  Very handy for debugging.

/////////////////////////////////////////////////////////////////////////////
// CIvfTreeView view

#include <afxcview.h>   // Need this to use CTreeView
#include <afxcmn.h>     // Need this to use CTreeCtrl


// Inventor classes needed for function declarations
class SoNode;
class SoPath;
class SoSelection;


class CIvfTreeView : public CTreeView
{
protected:
	CIvfTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CIvfTreeView)

// Attributes
public:

// Operations
public:
    // Set the root node of the tree
    //
    // This may be, but is not required to be, the same as the selection node.
    // Only the root node and below will be displayed in the tree view.
    void SetRootNode( SoNode* pRootNode );
    SoNode *GetRootNode()
        { return m_pRootNode; }

    // Set the selection node to be "monitored" by the tree view
    //
    // This may be, but is not required to be, the same as the root node.
    // Only the root node and below will be displayed in the tree view.
    // This node must be specified for selections in the tree view to be
    // reflected in the graphics window.
    // The root node must be the same as, or a child of, the selection node.
    void SetSelectionNode( SoSelection *pSelectionNode );
    SoSelection *GetSelectionNode()
        { return m_pSelectionNode; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIvfTreeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CIvfTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

    // Utility functions specific to IvfTreeControl
    //
    // Given a node and an item in the treeView,
    // Add node's children (recursively descending the scenegraph) to the tree.
    // This function can used to create the entire tree or just a subtree.
    // This function does not check for pre-existing items, so callers should
    // generally delete all items first.
    //
    void AddNodeChildren( HTREEITEM hParentItem, SoNode *pNode );

    // Rebuild the treeview from scratch.
    // Delete current contents of tree and recreate it.
    //
    void UpdateTreeControl( SoNode* pSceneRoot );

    // Find the tree item corresponding to the specified node path.
    // Path must contain the root node, but does not necessarily start
    // with the root node (e.g., could start with the selection node).
    // A path uniquely defines a single item in the tree.
    //
    HTREEITEM GetItemFromPath( SoPath *path );

    // Construct the Inventor SoPath corresponding to an item in the tree.
    // Because the item tree "expands" multiply instanced subgraphs, there
    // is a unique node graph path corresponding to each item.
    // Returned path starts with node corresponding to root item of tree.
    // Returned path is not ref'd by this method.
    //
    SoPath *GetPathFromItem( HTREEITEM hItem );

    // Called from static node selection callback when something has been
    // selected (or deselected) in the graphics window.  Assuming:
    // The application's scene graph contains an SoSelection node and that
    // node is known to us via the SetSelectionNode method.
    //
    // Default implementation selects/deselects corresponding item.
    virtual void OnNodeSelection  (SoPath *path);
    virtual void OnNodeDeselection(SoPath *path);


    // Internal data
    SoNode      *m_pRootNode;
    SoSelection *m_pSelectionNode;


	// Generated message map functions
protected:
	//{{AFX_MSG(CIvfTreeView)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    static void StaticNodeSelectionCB(void *userData, SoPath *path);
    static void StaticNodeDeselectionCB(void *userData, SoPath *path);

};

/////////////////////////////////////////////////////////////////////////////
