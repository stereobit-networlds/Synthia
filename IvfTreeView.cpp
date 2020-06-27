// IvfTreeView.cpp : implementation file
//
// Copyright (C) 1996 Template Graphics Software Inc.
// All Rights Reserved.
//
// Author: Mike Heck
//
// An MFC view class that displays an Inventor scene graph
// using the Microsoft TreeView control.

#include "stdafx.h"
#include "SYNTH.h"
#include "IvfTreeView.h"

// Specific to IvfTreeView
#include "SYNTHDoc.h"
#include <Inventor/SoPath.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/actions/SoSearchAction.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIvfTreeView

IMPLEMENT_DYNCREATE(CIvfTreeView, CTreeView)

CIvfTreeView::CIvfTreeView()
{
    // Initialize member variables
    m_pRootNode = NULL;        
    m_pSelectionNode = NULL;
}

CIvfTreeView::~CIvfTreeView()
{
    // Release the scene graph root if necessary
    if (m_pRootNode) {
        m_pRootNode->unref();
        m_pRootNode = NULL;
    }

    // Release the selection node if necessary
    if (m_pSelectionNode) {
        m_pSelectionNode->removeSelectionCallback(
            CIvfTreeView::StaticNodeSelectionCB, this );
        m_pSelectionNode->removeDeselectionCallback(
            CIvfTreeView::StaticNodeDeselectionCB, this );

        m_pSelectionNode->unref();
        m_pSelectionNode = NULL;
    }
}


BEGIN_MESSAGE_MAP(CIvfTreeView, CTreeView)
	//{{AFX_MSG_MAP(CIvfTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIvfTreeView drawing

void CIvfTreeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();

    // No action required -- Inventor viewer handles this
}

/////////////////////////////////////////////////////////////////////////////
// CIvfTreeView diagnostics

#ifdef _DEBUG
void CIvfTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CIvfTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIvfTreeView message handlers

BOOL CIvfTreeView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
    // Modified for IvfTreeView example
	//return CTreeView::PreCreateWindow(cs);

    if (!CTreeView::PreCreateWindow(cs))
        return FALSE;

    // Set desired options for TreeView
    cs.style |= TVS_HASLINES | TVS_LINESATROOT |
              TVS_HASBUTTONS | TVS_SHOWSELALWAYS;

    return TRUE;
}

void CIvfTreeView::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	
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

void CIvfTreeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
    CSYNTHDoc *pDoc = (CSYNTHDoc *)GetDocument();
    
    // Re-generate tree view on scene graph change
    UpdateTreeControl( pDoc->IvfGetDocSceneGraph());	
}


/////////////////////////////////////////////////////////////////////////////
// CIvfTreeView specific functions

// Utility function
//
// Given a node and an item in the treeView,
// Add node's children (recursively descending the scenegraph) to the tree.
// This function can used to create the entire tree or just a subtree.
// This function does not check for pre-existing items, so callers should
// generally delete all items first.
//
void CIvfTreeView::AddNodeChildren( HTREEITEM hParentItem, SoNode *pNode )
{
    char textBuffer[256];
    HTREEITEM newItem;

    SoType nodeType = pNode->getTypeId();
    const char *itemText = nodeType.getName().getString(); // Class name
    const char *nodeName = pNode->getName().getString();

    // If node has an instance name, append it to the class name
    if (nodeName && *nodeName != '\0') {
        sprintf( textBuffer, "%s \"%s\"", itemText, nodeName );
        itemText = textBuffer;
    }

    // Add the node to the tree
    // Note: Store ptr to node as tree item's data value
    newItem = GetTreeCtrl().InsertItem( TVIF_TEXT | TVIF_PARAM,
                                        itemText,      // Item text
                                        0, 0, 0, 0,    // Images
                                        (LPARAM)pNode, // Parameter
                                        hParentItem,   // Parent
                                        TVI_LAST       // Insert after
                                      );

    // If node has children (is derived from SoGroup)
    // recurse and add the children items to the tree
    if (nodeType.isDerivedFrom(SoGroup::getClassTypeId())) {
        SoGroup *pGroup = (SoGroup *)pNode;
        for (int i = 0; i < pGroup->getNumChildren(); i++) {
            AddNodeChildren( newItem, pGroup->getChild(i) );
        }
    }
}


// Utility function
//
// Rebuild the treeview from scratch
//
void CIvfTreeView::UpdateTreeControl( SoNode* pSceneRoot )
{
    // Get the tree control contained in the tree view
    CTreeCtrl &tree = GetTreeCtrl();

    // Make sure tree control is empty
    // Note: Set current selection to NULL first to avoid getting
    //       spurious calls to OnSelChanged
    //tree.SelectItem( NULL );
    tree.DeleteAllItems();

    // Sanity check for empty document
    if (pSceneRoot == NULL)
        return;

    // Build the tree by adding the root node
    // AddNodeChildren will recursively descend the tree
    AddNodeChildren( TVI_ROOT, pSceneRoot );
}


// Set the root node of the tree
//
// This may be, but is not required to be, the same as the selection node.
// Only the root node and below will be displayed in the tree view.
void CIvfTreeView::SetRootNode( SoNode* pNewRootNode )
{
    // Release interest in current root (if any)
    if (m_pRootNode) {
        m_pRootNode->unref();
        m_pRootNode = NULL;
    }

    // Reference new root (if any)
    if (pNewRootNode) {
        m_pRootNode = pNewRootNode;
        m_pRootNode->ref();
    }

    // Recreate the tree
    // (empties the tree even if node is null)
    UpdateTreeControl( m_pRootNode );
}


// Set the selection node to be "monitored" by the tree view
//
// This may be, but is not required to be, the same as the root node.
// Only the root node and below will be displayed in the tree view.
void CIvfTreeView::SetSelectionNode( SoSelection *pNewSelNode )
{
    if (m_pSelectionNode) {
        // Remove callbacks from current node
        // (be sure to do this *before* unrefing the node!)
        m_pSelectionNode->removeSelectionCallback(
            CIvfTreeView::StaticNodeSelectionCB, this );
        m_pSelectionNode->removeDeselectionCallback(
            CIvfTreeView::StaticNodeDeselectionCB, this );

        m_pSelectionNode->unref();
        m_pSelectionNode = NULL;
    }

    if (pNewSelNode) {
        m_pSelectionNode = pNewSelNode;
        m_pSelectionNode->ref();

        m_pSelectionNode->addSelectionCallback(
            CIvfTreeView::StaticNodeSelectionCB, this );
        m_pSelectionNode->addDeselectionCallback(
            CIvfTreeView::StaticNodeDeselectionCB, this );
    }
}


// Utility function
// Locate the sibling item that corresponds to this node
static
HTREEITEM FindNodeInSiblings( CTreeCtrl &tree, SoNode *node, HTREEITEM item )
{
    SoNode *data;
    do {
        data = (SoNode*)tree.GetItemData( item );
        if (node == data)
            return item;
    } while (item = tree.GetNextSiblingItem( item ));
    return NULL;
}


// Utility function
// Find the tree item corresponding to the specified node path.
// Path must contain the root node, but does not necessarily start
// with the root node (e.g., could start with the selection node).
//
HTREEITEM CIvfTreeView::GetItemFromPath( SoPath *path )
{
    CTreeCtrl &tree = GetTreeCtrl();
    HTREEITEM hRootItem = tree.GetRootItem();
    HTREEITEM hItem = hRootItem;
    SoNode *data;
    SoNode *node;
    int pathLen = path->getLength();

    // Find the node in the path where the item tree begins!
    // Note: The selection path will always begin with the SoSelection
    //       node itself, but the item tree will usually begin with the
    //       root of the document's scene graph (below the SoSel node).
    int startIndex;
    data = (SoNode*)tree.GetItemData( hRootItem );
    for (startIndex = 0; startIndex < pathLen; startIndex++) {
        // Is this where we start?
        node = path->getNode( startIndex );
        if (node == data)
            break;
    }
    if (startIndex >= pathLen) {
        TRACE( "Selection path does not contain root of tree!!!" );
        return NULL;
    }
        
    int nodeIndex;
    // Loop over node selection path
    // At this point we've established that node at startIndex is
    // represented by the root item in the tree.
    for (nodeIndex = startIndex + 1; nodeIndex < pathLen; nodeIndex++) {
        // Get next node in path and next level of item tree
        node = path->getNode( nodeIndex );
        hItem = tree.GetChildItem( hItem );
        // Loop over items at this level
        hItem = FindNodeInSiblings( tree, node, hItem );
        if (hItem == NULL)
            break; // Couldn't find node in tree
    }
    return hItem;
}


// Overrideable, instance specific, node selection callback
//
// Called from static node selection callback when something has been
// selected in the graphics window.
void CIvfTreeView::OnNodeSelection( SoPath *path )
{
    // Trace the node path down through the item tree and return the
    // item corresponding to the "tail" node in the path
    HTREEITEM selectedItem = GetItemFromPath( path );

    // Mark this item as selected and make sure it is visible
    // (tree control will automatically expand and scroll)
    if (selectedItem) {
        GetTreeCtrl().SetItemState( selectedItem, TVIS_SELECTED, TVIS_SELECTED );
        GetTreeCtrl().EnsureVisible( selectedItem );
    }
}


// Overrideable, instance specific, node deselection callback
//
// Called from static node deselection callback when a previously
// selected object in the graphics window is deselected.
void CIvfTreeView::OnNodeDeselection( SoPath *path )
{
    // Trace the node path down through the item tree and return the
    // item corresponding to the "tail" node in the path
    HTREEITEM selectedItem = GetItemFromPath( path );

    // Mark this item as not selected
    if (selectedItem)
        GetTreeCtrl().SetItemState( selectedItem, 0, TVIS_SELECTED );
}


// Static node selection callback
void CIvfTreeView::StaticNodeSelectionCB( void *userData, SoPath *path )
{
    CIvfTreeView *pView = (CIvfTreeView*)userData;

    if (pView)
        pView->OnNodeSelection( path );
}



// Static node deselection callback
void CIvfTreeView::StaticNodeDeselectionCB( void *userData, SoPath *path )
{
    CIvfTreeView *pView = (CIvfTreeView*)userData;

    if (pView)
        pView->OnNodeDeselection( path );
}


// Utility function
// Construct the Inventor SoPath corresponding to an item in the tree.
//
// Because the item tree "expands" multiply instanced subgraphs, there
// is a unique node graph path corresponding to each item.
SoPath *CIvfTreeView::GetPathFromItem( HTREEITEM item )
{
    if (item == NULL)
        return (SoPath*)NULL;

    CTreeCtrl &tree = GetTreeCtrl();

    // Build list of nodes from bottom to top
    SbPList list;
    SoNode *node;
    do {
        node = (SoNode*)tree.GetItemData( item );
        list.append( node );
    } while( item = tree.GetParentItem( item ));

    // Build list of nodes from top to bottom
    int numItems = list.getLength();
    SoPath *path = new SoPath( numItems );
    path->ref();

    // Begin path with last (top most) node in list.
    // Note: List indices are zero based.
    node = (SoNode*)list[numItems - 1];
    path->setHead( node );

    // Fill in remainder of path
    for (int i = numItems - 2; i >= 0; i--) {
        node = (SoNode*)list[i];
        path->append( node );
    }
    return path;
}


// Called by tree control when selection changes
void CIvfTreeView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    // Get the new selected item.
    // Note: We don't worry about the old selected item because we'll
    //       get deselect callbacks from the selection node anyway.
    HTREEITEM hNewItem = pNMTreeView->itemNew.hItem;

#ifdef _DEBUG
    char dbuffer[256];
    switch (pNMTreeView->action) {
        case TVC_BYKEYBOARD:	// By a key stroke
            sprintf( dbuffer, "OnSelChanged item=0x%x action=TVC_BYKEYBOARD\n",
                     hNewItem );
            break;
        case TVC_BYMOUSE:	    // By a mouse click
            sprintf( dbuffer, "OnSelChanged item=0x%x action=TVC_BYMOUSE\n",
                     hNewItem );
            break;
        case TVC_UNKNOWN:	    // Unknown
            sprintf( dbuffer, "OnSelChanged item=0x%x action=TVC_UNKNOWN\n",
                     hNewItem );
            break;
        default:
            sprintf( dbuffer, "OnSelChanged item=0x%x action=?\n",
                     hNewItem );
            break;
    }
    TRACE( dbuffer );
#endif //_DEBUG

    // If there's no selection node to update, there's nothing to do
    // (nothing in Inventor to notify about the change).
    if (m_pSelectionNode == NULL)
        return;

    // If new selection is NONE, there's nothing to do
    if (hNewItem == NULL)
        return;

    // If action that caused selection is not a mouse click, ignore it
    // (sometimes we get selection changes for no obvious reason).
    if (pNMTreeView->action == TVC_UNKNOWN)
        return;

    // Get a reference to the tree control
    CTreeCtrl &tree = GetTreeCtrl();
    CString text = tree.GetItemText( hNewItem );    // debug

    // Get ptr to Inventor node corresponding to selected item
    SoNode *pNode = (SoNode*)tree.GetItemData( hNewItem );

    // If node is not a group or a shape then attempting to highlight
    // it in Inventor is pointless (and generates an annoying message
    // from the highlight action when using the debug library).  Also
    // skip highlighting groups with no children.
    //
    // In some cases the application might *want* to be able to
    // select other kinds of nodes even though they won't highlight,
    // but we'll leave that for another day.
    if (pNode->isOfType(SoGroup::getClassTypeId())) {
        SoGroup *pGroup = static_cast<SoGroup*>(pNode);
        if (pGroup->getNumChildren() < 1)
            return;
    }
    else if (!pNode->isOfType(SoShape::getClassTypeId()))
        return;

    // Construct a node path corresponding to selected item
    SoPath *pItemPath = GetPathFromItem( hNewItem );

    // If we were able to construct a valid path...
    if (pItemPath != NULL) {

        // Ref path so we can unref (delete) it later
        pItemPath->ref();

        // Make sure this path is valid with respect to selection node.
        // If path does not contain selection node it will be ignored.
        //
        // We will make the path contain the selection node, but that
        // will only work if the head of the path is a descendant of
        // the selection node.

        SoNode *pHead = pItemPath->getHead();

        // Search for head of item path below the selection node
        SoSearchAction search;
        search.setNode( pHead );
        search.setInterest( SoSearchAction::FIRST );
        search.apply( m_pSelectionNode );

        // If path from selection node to beginning of item path...
        SoPath *pSelPath = search.getPath();
        if (pSelPath != NULL) {

            // Ref this path also so we can unref (delete) it later
            pSelPath->ref();

            // Combine the two paths so we now have a complete path
            // from selection node to selected item (node).
            pSelPath->append( pItemPath );

            // Clear the selection list and make this the selection
            m_pSelectionNode->deselectAll();
            m_pSelectionNode->select( pSelPath );

            // Delete the selection path
            pSelPath->unref();
        }

        // Delete the item path
        pItemPath->unref();
    }
	
	*pResult = 0;
}
