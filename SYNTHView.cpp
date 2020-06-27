// SYNTHView.cpp : implementation of the CSYNTHView class
//

#include "stdafx.h"
#include "SYNTH.h"

#include "SYNTHDoc.h"
#include "SYNTHView.h"
#include "GExternal.h"
#include "RoomWall.h"
#include "Lib0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <Inventor/nodes/SoSelection.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <Inventor/actions/SoBoxHighlightRenderAction.h>
#include <Inventor/nodes/SoUnits.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoText2.h>

#include <Inventor/Win/SoWinClipboard.h>    
#include <Inventor/SoLists.h>             

#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/win/SoWinDirectionalLightEditor.h>
#include <Inventor/win/SoWinMaterialEditor.h>

/////////////////////////////////////////////////////////////////////////////
// CSYNTHView

IMPLEMENT_DYNCREATE(CSYNTHView, CView)

BEGIN_MESSAGE_MAP(CSYNTHView, CView)
	//{{AFX_MSG_MAP(CSYNTHView)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_PICEDIT, OnViewPicedit)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PICEDIT, OnUpdateViewPicedit)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EXTENTED_CUT, OnUpdateExtentedCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_VIEW_SELECTIONMODE, OnViewViewmodesSelectionmode)
	ON_COMMAND(ID_VIEW_VIEWINGMODE, OnViewViewmodesViewingmode)
	ON_UPDATE_COMMAND_UI(ID_UNGROUP, OnUpdateUnGroup)
	ON_COMMAND(ID_HIDEBASE, OnHidebase)
	ON_UPDATE_COMMAND_UI(ID_HIDEBASE, OnUpdateHidebase)
	ON_COMMAND(ID_HIDEWALLS, OnHidewalls)
	ON_UPDATE_COMMAND_UI(ID_HIDEWALLS, OnUpdateHidewalls)
	ON_COMMAND(ID_HIDEOBJS, OnHideobjs)
	ON_UPDATE_COMMAND_UI(ID_HIDEOBJS, OnUpdateHideobjs)
	ON_COMMAND(ID_HIDESELECTION, OnHideselection)
	ON_UPDATE_COMMAND_UI(ID_HIDESELECTION, OnUpdateHideselection)
	ON_COMMAND(ID_SHOWALL, OnShowall)
	ON_UPDATE_COMMAND_UI(ID_SHOWALL, OnUpdateShowall)
	ON_COMMAND(ID_CHBACKCOLOR, OnChbackcolor)
	ON_UPDATE_COMMAND_UI(ID_CHBACKCOLOR, OnUpdateChbackcolor)
	ON_COMMAND(ID_HOMEPOSITION, OnHomeposition)
	ON_UPDATE_COMMAND_UI(ID_HOMEPOSITION, OnUpdateHomeposition)
	ON_COMMAND(ID_SETHOMEPOSITION, OnSethomeposition)
	ON_UPDATE_COMMAND_UI(ID_SETHOMEPOSITION, OnUpdateSethomeposition)
	ON_COMMAND(ID_HEADLIGHT, OnHeadlight)
	ON_UPDATE_COMMAND_UI(ID_HEADLIGHT, OnUpdateHeadlight)
	ON_COMMAND(ID_INVDECORATION, OnInvdecoration)
	ON_UPDATE_COMMAND_UI(ID_INVDECORATION, OnUpdateInvdecoration)
	ON_COMMAND(ID_DRAW_AS_IS, OnDrawAsIs)
	ON_UPDATE_COMMAND_UI(ID_DRAW_AS_IS, OnUpdateDrawAsIs)
	ON_COMMAND(ID_DRAW_HIDDEN_LINE, OnDrawHiddenLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_HIDDEN_LINE, OnUpdateDrawHiddenLine)
	ON_COMMAND(ID_DRAW_NO_TEXTURE, OnDrawNoTexture)
	ON_UPDATE_COMMAND_UI(ID_DRAW_NO_TEXTURE, OnUpdateDrawNoTexture)
	ON_COMMAND(ID_DRAW_LOW_COMP, OnDrawLowComp)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LOW_COMP, OnUpdateDrawLowComp)
	ON_COMMAND(ID_DRAW_LINE, OnDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, OnUpdateDrawLine)
	ON_COMMAND(ID_DRAW_POINT, OnDrawPoint)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POINT, OnUpdateDrawPoint)
	ON_COMMAND(ID_DRAW_BBOX, OnDrawBbox)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BBOX, OnUpdateDrawBbox)
	ON_COMMAND(ID_VIEWING, OnViewing)
	ON_UPDATE_COMMAND_UI(ID_VIEWING, OnUpdateViewing)
	ON_COMMAND(ID_DIRLIGHT, OnDirlight)
	ON_UPDATE_COMMAND_UI(ID_DIRLIGHT, OnUpdateDirlight)
	ON_COMMAND(ID_UNGROUP, OnUnGroup)
	ON_COMMAND(ID_MATERIALEDIT, OnMaterialedit)
	ON_UPDATE_COMMAND_UI(ID_MATERIALEDIT, OnUpdateMaterialedit)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CSYNTHView	*sview ;

CSYNTHView::CSYNTHView()
{
	// TODO: add construction code here
// IVF_EXAMPLE_BEGIN
    m_pSelectionNode = NULL;    // Initialize new member variable
    m_nEnableSelection = TRUE;  // Set existing member variable
    m_pClipboard = NULL;    // windows clipboard

	sep_buffer = NULL;      //separator buffer

	headlight_option  = 0; //OFF
	decoration_option = 1; //ON
	drawStyle_option  = 3; //NO TEXTURE

// IVF_EXAMPLE_END
   
}

CSYNTHView::~CSYNTHView()
{
// IVF_EXAMPLE_BEGIN
    // Don't delete Inventor nodes, just decrement the ref count
    if (m_pSelectionNode != NULL)
        m_pSelectionNode->unref();

	if (m_pClipboard != NULL) { //SelectB
        delete m_pClipboard;
        m_pClipboard = NULL;
	}
// IVF_EXAMPLE_END
}

BOOL CSYNTHView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSYNTHView drawing

void CSYNTHView::OnDraw(CDC* pDC)
{
	CSYNTHDoc* pDoc = GetDocument();
	CSYNTHDoc* sdoc = GetDocument(); //add by me  <----------------------- !!!!!
	ASSERT_VALID(pDoc);
}

#include <Inventor/manips/SoHandleBoxManip.h>
#include <Inventor/manips/SoTrackballManip.h>
#include <Inventor/manips/SoTransformBoxManip.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodekits/SoWrapperKit.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoLight.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/nodes/SoEventCallback.h>

//my light editor
SoWinDirectionalLightEditor *myLEditor ;
//my material editor
SoWinMaterialEditor *myMEditor ;

SbBool isTransformable(SoNode *myNode) ;
SoPath *createTransformPath(SoPath *inputPath) ;
void selectionCallback(   void *, SoPath *selectionPath ) ;
void deselectionCallback( void *, SoPath *deselectionPath) ;

SoPath *pickFilterCallback (void *, const SoPickedPoint *pick);
SoPath *pickFilterCB(void *, const SoPickedPoint *pick) ;

SbBool writePickedPath ( SoNode *root, const SbViewportRegion &viewport,  
										const SbVec2s &cursorPosition ) ;

void GetPickObjectID(SoPath *path);

void MousePressCB(void *userData, SoEventCallback *eventCB ) ;

SoHandleBoxManip    *myHandleBox;
SoTrackballManip    *myTrackball;
SoTransformBoxManip *myTransformBox;
SoPath *handleBoxPath    = NULL;
SoPath *trackballPath    = NULL;
SoPath *transformBoxPath = NULL;

void CSYNTHView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
    IvfOnInitialUpdate(this) ;


    if (m_pSelectionNode == NULL) { 
        // Create the SoSelection node that will be root of scene graph
        m_pSelectionNode = new SoSelection;
        m_pSelectionNode->ref();

//  	m_nEnableSelection = TRUE; has defined already in construction

//	    SoSelection *pSelectionNode = IvfGetSelectionNode();
	    m_pSelectionNode->policy = SoSelection::SHIFT ;
//	    m_pSelectionNode->addSelectionCallback(selectionCallback, NULL);
//      m_pSelectionNode->addDeselectionCallback(deselectionCallback, NULL);
        m_pSelectionNode->setPickFilterCallback(pickFilterCB);

/*
	myHandleBox = new SoHandleBoxManip;
	myHandleBox->ref();
	myTrackball = new SoTrackballManip;
	myTrackball->ref();
	myTransformBox = new SoTransformBoxManip;
	myTransformBox->ref();
*/
	   sdoc = GetDocument() ;
	   sview = this ;

	   SoMouseButtonEvent  myMouseEvent;

	   // Add an event callback to catch mouse button presses.
       // The callback is set up later on.
	   SoEventCallback *EventCB = new SoEventCallback;
	   m_pSelectionNode->addChild(EventCB);

	   // Set up the event callback. We want to pass the root of the
	   // entire scene graph (including the camera) as the userData,
	   // so we get the scene manager's version of the scene graph
	   // root.
	   EventCB->addEventCallback ( SoMouseButtonEvent::getClassTypeId(),
							       MousePressCB,
								   m_pViewer->getSceneManager()->getSceneGraph());
      
	   // set the document's selected object
	   GetDocument()->SetSelectedObj(m_pSelectionNode) ;

	   // Set our selection node as the scene graph root node
       m_pViewer->setSceneGraph( m_pSelectionNode );



       // Use a bounding box to highlight selected objects
       m_pViewer->setGLRenderAction( new SoBoxHighlightRenderAction() );

       // Tell viewer to automatically redraw when selection changes
       // (so the highlight will be drawn in the right place)
       m_pViewer->redrawOnSelectionChange( m_pSelectionNode ) ;

	} 

	// Create an instance of the clipboard and associate with our window
    if (m_pClipboard == NULL) 
	{
        m_pClipboard = new SoWinClipboard( GetSafeHwnd() );
    }

	//if wizard enabled ... make scene automatically
	if (sdoc->Wizard) sdoc->CreateBasicScene();
    
}

/////////////////////////////////////////////////////////////////////////////
// CSYNTHView printing

BOOL CSYNTHView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSYNTHView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	IvfOnBeginPrinting();
}

void CSYNTHView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
	IvfOnEndPrinting();
}

void CSYNTHView::OnPrint(CDC* pDC, CPrintInfo*)
{
	IvfOnPrint(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CSYNTHView diagnostics

#ifdef _DEBUG
void CSYNTHView::AssertValid() const
{
	CView::AssertValid();
}

void CSYNTHView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSYNTHDoc* CSYNTHView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSYNTHDoc)));
	return (CSYNTHDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSYNTHView message handlers

// BEGIN_IVWGEN
void CSYNTHView::OnDestroy()
{
	CView::OnDestroy();
	IvfOnDestroy();

/*	if (myLEditor->isAttached()) 
	{
		if (myLEditor->isVisible()) myLEditor->hide(); //hide first
		myLEditor->detach(); //<<<------ kill directional light
	}*/
}
// END_IVWGEN

// BEGIN_IVWGEN
int CSYNTHView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	IvfOnCreate(lpCreateStruct);
	
	return 0;
}

void CSYNTHView::OnPaint() 
{
	// IvfOnPaint just does a BeginPaint/EndPaint
	//
	// The view's window does not need to be painted because it is
	// completely covered by the Inventor viewer window (which will
	// automatically paint itself as long as it gets the WM_PAINT).
	// However we still need to "validate" the paint rect so we won't
	// keep getting paint messages over and over.

	CIvfComponent::IvfOnPaint( this ) ;
}

BOOL CSYNTHView::OnEraseBkgnd(CDC* pDC) 
{
	// We don't want to waste cpu cycles painting the background of
	// the view window because it is always completely covered by
	// the Inventor viewer window.  DefWindowProc will draw the back-
	// ground unless we return TRUE from this message handler, which
        // is actually all that IvfOnEraseBkgnd does right now...

	return IvfOnEraseBkgnd(pDC);
}

BOOL CSYNTHView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if( IvfOnCmdMsg( nID, nCode, pExtra, pHandlerInfo ) )
		return TRUE;
	else
		return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

// END_IVWGEN

// BEGIN_IVWGEN
void CSYNTHView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	CSYNTHDoc* pDoc = GetDocument();
	CSYNTHDoc* sdoc = GetDocument(); //add by me  <----------------------- !!!!!
			  //  need the document pointer

        // TODO: Add your specialized code here and/or call the base class

	if(bActivate && pActivateView == (CView *)this) {
        // Moved component creation here so we can avoid creating
        // it when we are not even active.  If we're here then it's
        // certain that we're active and have a frame window.

      	if (m_pComponent == NULL) {
        	// Get pointer that was passed into IVF_INIT_INSTANCE
	        int *cArgs = (int *)CIvfApp::IvfCreateArgs();
        	ASSERT_VALID(pDoc);

	    IvfCreateComponent( this, cArgs ) ;

	    if (pDoc->IvfGetDocSceneGraph() != NULL) IvfResetComponent(pDoc);
			// scenegraph was already loaded, but
			// the component could not be initialized.
			// do it now.

	    IvfSetBackgroundColor(pDoc->IvfGetBgColor());
        }

        // For some reason MS-Word doesn't pass WM_QUERYNEWPALETTE to us
        // (although this works fine in the test container).
        // This call will force Inventor to realize its palette.

        IvfOnActivateComponent(pActivateView) ;

			//  don't want this happening in normal
			//  standalone scenario
			//  note also that Word activates and deactivates
			//  us several times.  Make sure the doc is
			//  considered modified for every activation.
        }
	else if(!bActivate && pDeactiveView == (CView *)this) {
	IvfOnDeactivateComponent() ;
	}
CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
// END_IVWGEN


void CSYNTHView::OnViewPicedit () 
{ 
	if (IvfIsViewing()) OnViewViewmodesSelectionmode();
	else		    OnViewViewmodesViewingmode();
} 


void CSYNTHView::OnUpdateViewPicedit (CCmdUI* pCmdUI)
{ 
	if (IsDocLoaded())
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(GetViewerViewMode() == ID_VIEW_VIEWINGMODE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(FALSE);
	}
}


void CSYNTHView::OnEditCopy() 
{
/*    // Get list of all selected objects
    Time eventTime = time(NULL);
	const SoPathList *pPathList = m_pSelectionNode->getList();
    ASSERT( pPathList != NULL );

    // Copy all selected objects to clipboard
    if (pPathList->getLength() > 0)
        m_pClipboard->copy( (SoPathList*)pPathList, eventTime );
*/


	//**************** my routine
	//if the object is GExternal type...
    if (sdoc->Obj[sdoc->obj_selector]->IsKindOf(RUNTIME_CLASS(CGExternal)))
    {
      CGExternal *myext;

	  myext->CopyObject(sdoc->obj_selector);
	  sdoc->copy_mode = true ;
    }
	else //if it is RoomWall type...
	if (sdoc->Obj[sdoc->obj_selector]->IsKindOf(RUNTIME_CLASS(CRoomWall)))
    {
	  CRoomWall *mywall;

	  mywall->CopyObject(sdoc->obj_selector);
	  sdoc->copy_mode = true ;
    }
	else
      AfxMessageBox("Invalid selection. Access denied.");
}

void CSYNTHView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
    // Copy is only valid if at least one object is selected
    ASSERT( m_pSelectionNode != NULL );
    if (m_pSelectionNode->getNumSelected() > 0)
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
}

void CSYNTHView::OnEditCut() 
{
    // Copy all selected objects to clipboard
    OnEditCopy();

    // Loop over all selected objects
    int i = m_pSelectionNode->getNumSelected() - 1;

    while (i >= 0) {
        // Get next path
        SoPath *pPath = (*m_pSelectionNode)[i];
        pPath->ref();
	
        // Deselect this path
        m_pSelectionNode->deselect(i);

        // Remove the tail node from the graph
        // 1) Get parent of tail node (which must be a group).
        // 2) Remove tail node from the group.
        SoGroup *pGroup = (SoGroup *) pPath->getNodeFromTail( 1 );
        pGroup->removeChild( pPath->getTail() );

        pPath->unref();  
        i--;
    }   
}

void CSYNTHView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
    // Cut is only valid if at least one object is selected
    ASSERT( m_pSelectionNode != NULL );
    if (m_pSelectionNode->getNumSelected() > 0)
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
}

//****************************** 
//ειναι ίδια με την OnEditCut... (future use??) 
void CSYNTHView::OnExtentedCut() 
{
    // Copy all selected objects to clipboard
    OnEditCopy();

    // Loop over all selected objects
    int i = m_pSelectionNode->getNumSelected() - 1;

    while (i >= 0) {
        // Get next path
        SoPath *pPath = (*m_pSelectionNode)[i];
        pPath->ref();
	
        // Deselect this path
        m_pSelectionNode->deselect(i);

        // Remove the tail node from the graph
        // 1) Get parent of tail node (which must be a group).
        // 2) Remove tail node from the group.
        SoGroup *pGroup = (SoGroup *) pPath->getNodeFromTail( 1 );
        pGroup->removeChild( pPath->getTail() );

        pPath->unref();  
        i--;
    }   
}

void CSYNTHView::OnUpdateExtentedCut(CCmdUI* pCmdUI) 
{
    // Cut is only valid if at least one object is selected
    ASSERT( m_pSelectionNode != NULL );
    if (m_pSelectionNode->getNumSelected() > 0)
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
}
//**********************************

void CSYNTHView::OnPasteCB( void *data, SoPathList *pList )
{
    // Get ptr to view that requested paste
    ASSERT( data != NULL );
    CSYNTHView *pView = (CSYNTHView*)data;

    // Get number of objects (pick paths) to be pasted
    ASSERT( pList != NULL );
    int numPath = pList->getLength();

    // Unselect any current selections
    pView->m_pSelectionNode->deselectAll();

    // Loop over objects to be pasted
    for (int i = 0; i < numPath; i++) {
        SoPath *pPath = (*pList)[i];
        ASSERT( pPath != NULL);

        SoNode *pNode = pPath->getHead();
        ASSERT( pNode != NULL );

        // If top of path is another selection node
        // (and it usually will be if it was copied or cut)
        // just add its children to the scene graph.
        // Otherwise we'll have multiple selection nodes
        // and the user will see very puzzling behavior!
        if (pNode->isOfType(SoSelection::getClassTypeId())) {

            SoGroup *pGroup = (SoGroup*)pNode;        
            int numKids = pGroup->getNumChildren();

            for (int j = 0; j < numKids; j++) {    
                SoNode *pNode = pGroup->getChild( j );
                ASSERT( pNode != NULL);
                // Add object to toplevel node and select it
                pView->m_pSelectionNode->addChild( pNode );
                pView->m_pSelectionNode->select( pNode );
            }
        }
        else {
            // Add object to toplevel node and select it
            pView->m_pSelectionNode->addChild( pNode );
            pView->m_pSelectionNode->select( pNode );
        }
    }
}

void CSYNTHView::OnEditPaste() 
{
    // Request current contents of clipboard
    // On completion the callback will be called.
    // It's a static function so pass it "this" as the data word.
//    Time eventTime = time(NULL);
//	m_pClipboard->paste( eventTime, CSYNTHView::OnPasteCB, this );


    sdoc->SaveUndo(); //save scene for undo...

	CGObject *object = ((CGObject*)sdoc->Obj[sdoc->LastCopy]);

	if (object->IsKindOf(RUNTIME_CLASS(CGExternal)))
    {
	  CGExternal *ext ;
      ext->PasteObject(); 
	}
	else
	if (object->IsKindOf(RUNTIME_CLASS(CRoomWall)))
    {
      CRoomWall *wll ;
      wll->PasteObject(); 
    } 
	else 
		AfxMessageBox("Invalid data. Paste ignored..");
	//sdoc->copy_mode = false ; //end of copy/paste
}

void CSYNTHView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
    // Update "Paste" UI items
    // Paste is only valid if there is something in the clipboard
    //if (IsClipboardFormatAvailable(CF_TEXT))

    if (sdoc->copy_mode==true)
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
}



BOOL CSYNTHView::IsDocLoaded(void)
{
	CSYNTHDoc *t_doc = GetDocument();
	return(t_doc->IvfGetDocSceneGraph() != NULL);
}

BOOL CSYNTHView::IsSelected(void)
{
	return(IvfIsSelected());
}

BOOL CSYNTHView::SaveAsBitmap( LPCTSTR pFilename )
{
	return(IvfSaveAsBitmap(pFilename));
}

UINT CSYNTHView::GetViewerViewMode(void)
{
	UINT r_stat = 0;

	if (IsDocLoaded())
	{
		r_stat = (IvfIsViewing())? ID_VIEW_VIEWINGMODE :
            		      ID_VIEW_SELECTIONMODE;
	}
	return(r_stat);
}

void CSYNTHView::OnViewViewmodesSelectionmode() 
{
	IvfViewmodesSelectionmode();
}

void CSYNTHView::OnViewViewmodesViewingmode() 
{
	IvfViewmodesViewingmode();
}


/**************************/
void CSYNTHView::OnDelete()
{
	//CLib0 lib;

	if (sdoc->obj_selector>0) //delete only walls, roombase ,externals
    {
	  sdoc->SaveUndo(); //save scene for undo...

      CGObject *obj = (CGObject*)sdoc->Obj[sdoc->obj_selector]; 
	  //if the object is GExternal type...
      if (obj->IsKindOf(RUNTIME_CLASS(CGExternal)))
      {
         CGExternal  *ext_obj = (CGExternal*)obj;

		 //delete object from inventor...
		 ext_obj->DelObject(sdoc->obj_selector,0);
	  }
	  else
      //if the object is RoomWall type...
      if (sdoc->Obj[sdoc->obj_selector]->IsKindOf(RUNTIME_CLASS(CRoomWall)))
      {
         CRoomWall *Wall_obj = (CRoomWall*)obj;

		 //delete object from inventor...
		 Wall_obj->DeleteObject(sdoc->obj_selector);
	  }
      else  AfxMessageBox("Invalid selection. Access denied."); 
	}
	else AfxMessageBox("Access denied."); 
}

void CSYNTHView::OnExtDelete()
{
	if (sdoc->obj_selector>0) //delete only walls, roombase ,externals
    {
	  sdoc->SaveUndo(); //save scene for undo...

	  CGObject *obj = (CGObject*)sdoc->Obj[sdoc->obj_selector]; 

	  //if the object is GExternal type...
      if (obj->IsKindOf(RUNTIME_CLASS(CGExternal)))
      {
	     CGExternal  *ext_obj = (CGExternal*)obj;
		 
         //delete object from inventor...
		 ext_obj->DelObject(sdoc->obj_selector,1);
      }
      else //OnExtentedCut(); 
           AfxMessageBox("Invalid selection. Access denied."); 
	}
	else AfxMessageBox("Invalid selection. Access denied."); 
}


void CSYNTHView::OnUnGroup()
{
	if (sdoc->obj_selector>0) //ungroup only externals
    {
	  CGObject *obj = (CGObject*)sdoc->Obj[sdoc->obj_selector];
	  //if the object is GExternal type...
      if (obj->IsKindOf(RUNTIME_CLASS(CGExternal)))
      {
		 CGExternal  *ext = (CGExternal*)obj;
         sdoc->SaveUndo(); //save scene for undo...

         //do the job...
		 ext->UnGroupObjects();
      }
      else AfxMessageBox("Invalid selection. Access denied."); 
	}
	else AfxMessageBox("Invalid selection. Access denied."); 

}

void CSYNTHView::OnUpdateUnGroup(CCmdUI* pCmdUI) 
{
    ASSERT( m_pSelectionNode != NULL );
    if (m_pSelectionNode->getNumSelected() > 0)
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
}
//***********************************  FIRST BUILD OF SCENE

bool CSYNTHView::StartScene()
{
	    int meter ;
        
        CSYNTHDoc* sdoc = GetDocument();
		sview = this;

        //make the root....
		if (sdoc->root!=NULL) 
        { 
    		//deselect ...
	        GetSelectionNode()->deselectAll();
         
			//root->removeAllChildren(); //οχι ολα γιατι σβηνει και το mouse callback =child 0
             
			SoSeparator *myRoot;
			myRoot = (SoSeparator *)SoNode::getByName("World_Space");
			int rootchilds =myRoot->getNumChildren()-1;

			//AfxMessageBox(lib.inttostr(rootchilds));

            //meter<2 διοτι δεν θελω να σβησω το callback και το directionalLight
			for (meter=rootchilds ; meter>2 ; meter--)
            {
				SoSeparator *mys = (SoSeparator *)myRoot->getChild(meter);
				myRoot->removeChild(meter);
            }
			
            return true;
        }
		else
        {
		  //material editor 
          myMEditor = new SoWinMaterialEditor
   		  (NULL,"Material Editor",TRUE);

		  // light editor 
          myLEditor = new SoWinDirectionalLightEditor
   		  (NULL,"Light Editor",TRUE);

		  sdoc->root = new SoSeparator ;
		  sdoc->root->ref() ;
		  sdoc->root->setName("World_Space");
 
		  //add light
 		  SoDirectionalLight *myLight = new SoDirectionalLight;
          sdoc->root->addChild(myLight);
          //attach light
		  /*SoPath **/lightpath = new SoPath(myLight);
          myLEditor->attach(lightpath);
          //myLEditor->show();

		  return  false;
        }
}

/*======================= selectionCallback =============*/

void selectionCallback(   void *, SoPath *selectionPath )
{
	// Attach the manipulator.
	// Use the convenience routine to get a path to
	// the transform that effects the selected object.

	SoPath *xformPath = createTransformPath(selectionPath);
	if (xformPath == NULL) return;
	xformPath->ref();
/*
	transformBoxPath = xformPath ;
	myTransformBox->replaceNode(xformPath) ;

	sdoc->SetSelectedObj(sview->IvfGetSelectionNode()) ;

	if (sdoc->SelId >= 0) 
	{
		transformBoxPath = xformPath ;
		myTransformBox->replaceNode(xformPath) ;
	}

	if (selectionPath->getTail()->isOfType(SoCube::getClassTypeId())) 
	{
		transformBoxPath = xformPath ;
		myTransformBox->replaceNode(xformPath) ;
	}
*/
}

//======================= deselectionCallback ====================

void deselectionCallback( void *, SoPath *deselectionPath)
{
/*
AfxMessageBox("deselectionCallback") ;
	if (deselectionPath->getTail()->isOfType(SoCube::getClassTypeId())) 
	{
		myTransformBox->replaceManip(transformBoxPath,NULL);
		transformBoxPath->unref();
	}
*/
}

//======================= pickFilterCallback ===================

SoPath *pickFilterCallback (void *, const SoPickedPoint *pick)
{
	const SbVec3f *pp = &pick->getPoint() ;
	const SbVec3f *nn = &pick->getNormal() ;

   SoPath *filteredPath = NULL;
    
   // See if the picked object is a manipulator. 
   // If so, change the path so it points to the object the manip
   // is attached to.
   SoPath *p = pick->getPath();
   SoNode *n = p->getTail();
   if (n->isOfType(SoTransformManip::getClassTypeId())) {
      // Manip picked! We know the manip is attached
      // to its next sibling. Set up and return that path.
      int manipIndex = p->getIndex(p->getLength() - 1);
      filteredPath = p->copy(0, p->getLength() - 1);
      filteredPath->append(manipIndex + 1); // get next sibling
   }
   else filteredPath = p;
    
   return filteredPath;

}

//*********************** pickFilterCB ************************
//toplevel
SoPath *pickFilterCB(void *, const SoPickedPoint *pick)
{
  //See whitch child of selection got picked
  SoPath *p = pick->getPath();

  int i;
  SoNode *n;
  for (i=p->getLength()-1;i>=0;i--)
  {
	  n = p->getNode(i);
	  if (n->isOfType(SoSeparator::getClassTypeId()))
		  break;
  }

//change bounding box  
  const char *name = ((SoSeparator *)n)->getName().getString();//get name
  if (strcmp(name,"")==0) //it is external 
	  return p->copy(0,i-1); 
  else                    //it is roomwall,worldbase ...
	  //return p->copy(0,i+1);
      return p; //no change

  return p;
}


/*===================== createTransformPath =================*/
//  Create a path to the transform node that affects the tail
//  of the input path.  Three possible cases:
//   [1] The path-tail is a node kit. Just ask the node kit for
//       a path to the part called "transform"
//   [2] The path-tail is NOT a group.  Search siblings of path
//       tail from right to left until you find a transform. If
//       none is found, or if another transformable object is 
//       found (shape,group,light,or camera), then insert a 
//       transform just to the left of the tail. This way, the 
//       manipulator only effects the selected object.
//   [3] The path-tail IS a group.  Search its children left to
//       right until a transform is found. If a transformable
//       node is found first, insert a transform just left of 
//       that node.  This way the manip will affect all nodes
//       in the group.
SoPath *createTransformPath(SoPath *inputPath)
{
   int pathLength = inputPath->getLength();
   if (pathLength < 2) // Won't be able to get parent of tail
      return NULL;

   SoNode *tail = inputPath->getTail();

   // CASE 1: The tail is a node kit.
   // Nodekits have built in policy for creating parts.
   // The kit copies inputPath, then extends it past the 
   // kit all the way down to the transform. It creates the
   // transform if necessary.
   if (tail->isOfType(SoBaseKit::getClassTypeId())) {
      SoBaseKit *kit = (SoBaseKit *) tail;
      return kit->createPathToPart("transform",TRUE,inputPath);
   }

   SoTransform *editXf = NULL;
   SoGroup     *parent;
   SbBool      existedBefore = FALSE;

   // CASE 2: The tail is not a group.
   SbBool isTailGroup;
   isTailGroup = tail->isOfType(SoGroup::getClassTypeId());
   if (!isTailGroup) {
      // 'parent' is node above tail. Search under parent right
      // to left for a transform. If we find a 'movable' node
      // insert a transform just left of tail.  
      parent = (SoGroup *) inputPath->getNode(pathLength - 2);
      int tailIndx = parent->findChild(tail);

      for (int i = tailIndx; (i >= 0) && (editXf == NULL);i--){
         SoNode *myNode = parent->getChild(i);
         if (myNode->isOfType(SoTransform::getClassTypeId()))
            editXf = (SoTransform *) myNode;
         else if (i != tailIndx && (isTransformable(myNode)))
            break;
      }
      if (editXf == NULL) {
	 existedBefore = FALSE;
         editXf = new SoTransform;
         parent->insertChild(editXf, tailIndx);
      }
      else
	 existedBefore = TRUE;
   }
   // CASE 3: The tail is a group.
   else {
      // Search the children from left to right for transform 
      // nodes. Stop the search if we come to a movable node.
      // and insert a transform before it.
      parent = (SoGroup *) tail;
      for (int i = 0;
         (i < parent->getNumChildren()) && (editXf == NULL); 
	 i++) {
         SoNode *myNode = parent->getChild(i);
         if (myNode->isOfType(SoTransform::getClassTypeId()))
            editXf = (SoTransform *) myNode;
         else if (isTransformable(myNode))
            break;
      }
      if (editXf == NULL) {
	 existedBefore = FALSE;
         editXf = new SoTransform;
         parent->insertChild(editXf, i);
      }
      else 
	 existedBefore = TRUE;
   }

   // Create 'pathToXform.' Copy inputPath, then make last
   // node be editXf.
   SoPath *pathToXform = NULL;
   pathToXform = inputPath->copy();
   pathToXform->ref();
   if (!isTailGroup) // pop off the last entry.
      pathToXform->pop();
   // add editXf to the end
   int xfIndex   = parent->findChild(editXf);
   pathToXform->append(xfIndex);
   pathToXform->unrefNoDelete();

   return(pathToXform);
}

/*========================= isTransformable ====================*/

// Is this node of a type that is influenced by transforms?
SbBool isTransformable(SoNode *myNode)
{
   if (myNode->isOfType(SoGroup::getClassTypeId())
      || myNode->isOfType(SoShape::getClassTypeId())
      || myNode->isOfType(SoCamera::getClassTypeId())
      || myNode->isOfType(SoLight::getClassTypeId()))
      return TRUE;
   else 
      return FALSE;
}

// ====================== writePickedPath =====================

SbBool writePickedPath ( SoNode *root, const SbViewportRegion &viewport, 
										const SbVec2s &cursorPosition )
{
	SoRayPickAction PickAction(viewport);

	// Set an 8-pixel wide region around the pixel
	PickAction.setPoint(cursorPosition);
	PickAction.setRadius(8.0);

	// Start a pick traversal
	PickAction.apply(root) ;
	SoPickedPoint *PickedPoint =  PickAction.getPickedPoint();

	if (PickedPoint == NULL) return FALSE;

	SoPath *p = PickedPoint->getPath();
	GetPickObjectID(p);                 //find my object id

	const SbVec3f *pp = &PickedPoint->getPoint() ;
	const SbVec3f *nn = &PickedPoint->getNormal() ;

	picked_point	= *pp ;
	picked_normal	= *nn ;

	return TRUE;
}

//********************* GetPickObjectID *********************
//Η ρουτινα αυτη  βρίσκει το id του clicked object και κανει attach τον Matterial Editor. 
//επιστρεφει το ονομα ως τυπου αντικειμένου και το νουμερο του ονοματος ως object counter
void GetPickObjectID(SoPath *path)
{
	CLib0 lib;
	int my_id ;

	my_id = -1; //initializate my_id=selector with invalid number
	sdoc->BATTERING = false ; //init battering  
	SoNode *myNode; //init node for search material (attach editor)

	int length = path->getLength(); //get length
	if (length > 2)
    {
      //SoNode *tail = myHitPath->getTail(); //get tail
	  SoSeparator *parent = (SoSeparator *)path->getNode(length-2); //get parent 
	  const char *name = ((SoSeparator *)parent)->getName().getString();  //get name
	  //AfxMessageBox(name) ;
      
      if (strncmp(name,"WorldBase",9)==0)
      {
		  //get the wall number
          char *digits = "0123456789";
		  char *mynum ;

		  mynum = strpbrk(name,digits) ; //get the number from name
          my_id = lib.strtoint(mynum);

		  //get material node
		  myNode = parent->getChild(4);
      }

	  if (strncmp(name,"RoomBase",8)==0) 
      {
		  //get the wall number
          char *digits = "0123456789";
		  char *mynum ;

		  mynum = strpbrk(name,digits) ; //get the number from name
          my_id = lib.strtoint(mynum);

		  //get material node
		  myNode = parent->getChild(4);
      }

	  if (strncmp(name,"RoomWall",8)==0)
      {
		  //get the wall number
          char *digits = "0123456789";
		  char *mynum ;

		  mynum = strpbrk(name,digits) ; //get the number from name
          my_id = lib.strtoint(mynum);

		  //get material node
		  myNode = parent->getChild(4);
      }

	  if (strcmp(name,"")==0)
      {
		 // must be external
         SoSeparator *ofparent = (SoSeparator *)path->getNode(length-5); //get parent of parent
		 const char *name = ((SoSeparator *)ofparent)->getName().getString();//get name
	     //AfxMessageBox(name) ; //all ok !!!

		 if (strncmp(name,"GExternal",9)==0) 
		 {
			 char *digits = "0123456789";
		     char *mynum ;
			 
		     mynum = strpbrk(name,digits) ; //get the object number from name 
             my_id = lib.strtoint(mynum);     // convert to int

			 sdoc->BATTERING = true;

			 //get material node (ofparent !!!)
		     myNode = ofparent->getChild(4);
		 }
		 else
         {
			 AfxMessageBox("Unknown Object ,2");
         }
      }


      sdoc->obj_selector = my_id ; //set selector

	  if (my_id!=-1) //αυτο σημαινει οτι το object ειναι εγκυρο
      { 
	    CGObject *obj = (CGObject*)sdoc->Obj[my_id];

		sdoc->obj_type = obj->id ; //get the object type

	    obj->ShowRefPoints(150.0); //<<<------------- show points

		//attach material editor
		if (myNode->isOfType(SoMaterial::getClassTypeId())) //if it is material node
		{
		   SoMaterial *mat = (SoMaterial*)myNode;
		   myMEditor->attach(mat);
		}
      }
	  else
      {
		  sdoc->obj_type = _NONE_;
	  	  AfxMessageBox("Invalid Object");
      }
	}
    else
	{
		AfxMessageBox("Unknown Object ,1");
    } 
}

//======================== MousePressCB =====================

void MousePressCB(void *userData, SoEventCallback *eventCB)
{
	SoSeparator *root = (SoSeparator *) userData;
	const SoEvent *event = eventCB->getEvent();

    // Check for mouse button being pressed
    if (SO_MOUSE_PRESS_EVENT(event, ANY))
	{
		const SbViewportRegion &myRegion = eventCB->getAction()->getViewportRegion();
		writePickedPath(root, myRegion, event->getPosition(myRegion));
		eventCB->setHandled();
	}

	/*CLib0 lib;
    AfxMessageBox("click point "+lib.floattostr(picked_point[0])+" "+
		          lib.floattostr(picked_point[1])+" "+
				  lib.floattostr(picked_point[2]));  */

	if ( sdoc->new_object ) 
	{
		if (sdoc->new_object ==_EXTERNAL_)
        {
          CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->ObjCount-1]) ; //get last input
		  ext->AddNewObject(picked_point, picked_normal);
        }
		else
        if (sdoc->new_object ==_ROOMWALL_)
        {
          CRoomWall *wll; //get nothing ...walls build in
		  wll->AddNewObject(picked_point, picked_normal);
        }
		else
			AfxMessageBox("Access denied : Unknown Object");

		sdoc->SetModifiedFlag() ;
		sdoc->UpdateAllViews(NULL);   // !!! οχι ολα γιατι "τρέμει" η σύνθεση (βελτιωση)		
	}
}

/************************  OPENGL ???? ************************/
void CSYNTHView::DrawBox(float x1,float y1,float z1,
			             float x2,float y2,float z2)
{
   float s[10][3];

   s[0][0] = x1;  s[0][1] = y1;  s[0][2] = z1;
   s[1][0] = x2;  s[1][1] = y2;  s[1][2] = z2;
 /*  s[2][0] = x3;  s[2][1] = y3;  s[2][2] = z3;
   s[3][0] = x4;  s[3][1] = y4;  s[3][2] = z4;
*/
   glColor3f(0.0, 7.0, 0.0);

   glBegin(GL_LINES);

   glVertex3fv(s[0]);
   glVertex3fv(s[1]);
 /*  glVertex3fv(s[2]);
   glVertex3fv(s[3]);
   glVertex3fv(s[4]);
   glVertex3fv(s[5]);
*/
   glEnd();
}

///////////////////////////////////////////////////////////////////////
// Overrides of IVF member functions


// IVF_EXAMPLE_BEGIN
// This method forces the component to use the scene graph pointed to
// by pRoot instead of the scene graph contained in the document.
void CSYNTHView::IvfSetSceneGraph(SoNode *pRoot)
{
    // Note: We may get called with NULL from IvfOnInitialUpdate.
    //       We may even get called before m_pSelectionNode has
    //       been created.  Just live with it for now.
    if (pRoot != NULL && m_pSelectionNode != NULL) {

        // Instead of setting the document's scene graph directly into the
        // viewer we add it to our selection node (which is already set
        // in the viewer).
        m_pSelectionNode->addChild( pRoot );
        
        // Some viewers (eg. Walk and Fly) only recompute scene size
        // in setSceneGraph -- change notification is not good enough.
        m_pViewer->setSceneGraph( m_pSelectionNode );

    }
}
// IVF_EXAMPLE_END

// IVF_EXAMPLE_BEGIN
// This method returns the scene graph contained in the component.
SoNode *CSYNTHView::IvfGetSceneGraph()
{
    // Instead of returning the scene graph set into the viewer (which
    // is actually our selection node) we return the first child of
    // our selection node.
    //
    // Note: We may get called from IvfOnInitialUpdate before the
    //       m_pSelectionNode has been created.  Just be paranoid.
    if (m_pSelectionNode && m_pSelectionNode->getNumChildren() > 0)

        return m_pSelectionNode->getChild( 0 );
    else
        return NULL;
}
// IVF_EXAMPLE_END

// IVF_EXAMPLE_BEGIN
// This method causes the component to unreference it's scene graph.
void CSYNTHView::IvfReleaseSceneGraph()
{
    // Instead of setting the viewer's scene graph (which is actually
    // our selection node) to NULL, we deselect and remove all the
    // children of our selection node.  The viewer's sensor will notice
    // the change and automatically redraw.
    if (m_pSelectionNode != NULL) {
        m_pSelectionNode->deselectAll();
        m_pSelectionNode->removeAllChildren();
    }
}
// IVF_EXAMPLE_END




/************************  SCENE HIDE/SHOW ************************/
void CSYNTHView::OnHidebase() 
{
	// TODO: Add your command handler code here
	CGObject *worldobj = (CGObject*)sdoc->Obj[0];
	worldobj->MakeObjInvisible();
	CGObject *baseobj = (CGObject*)sdoc->Obj[1];
	baseobj->MakeObjInvisible();
}

void CSYNTHView::OnUpdateHidebase(CCmdUI* pCmdUI) 
{
	//  hide base if a scene has created
    if ( sdoc->root != NULL )
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE ); 
}

void CSYNTHView::OnHidewalls() 
{
	// TODO: Add your command handler code here
    int i;
	for (i=0; i<sdoc->ObjCount ; i++)
	{
       if (sdoc->Obj[i]->IsKindOf(RUNTIME_CLASS(CRoomWall)))
       {
		   //WARNING : check for NULL pointers
	       if (sdoc->Obj[i]!=NULL)
		   {
		     CRoomWall *wall = (CRoomWall*)sdoc->Obj[i];
		     wall->MakeObjInvisible();
		   }
	   }
	}	
}

void CSYNTHView::OnUpdateHidewalls(CCmdUI* pCmdUI) 
{
	//  hide walls if a scene has created
    if ( sdoc->root != NULL )
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE ); 	
}

void CSYNTHView::OnHideobjs() 
{
	// TODO: Add your command handler code here
	int i;
	for (i=0; i<sdoc->ObjCount ; i++)
	{
       if (sdoc->Obj[i]->IsKindOf(RUNTIME_CLASS(CGExternal)))
       {
		   //WARNING : check for NULL pointers
	       if (sdoc->Obj[i]!=NULL)
		   {
		     CGExternal *ext = (CGExternal*)sdoc->Obj[i];
		     ext->MakeObjInvisible();
		   }
	   }
	}
}

void CSYNTHView::OnUpdateHideobjs(CCmdUI* pCmdUI) 
{
    //  hide other objects (externals) if a scene has created
    if ( sdoc->root != NULL )
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE ); 
}

void CSYNTHView::OnHideselection() 
{
	// TODO: Add your command handler code here
	CGObject *obj = (CGObject*)sdoc->Obj[sdoc->obj_selector];

	obj->MakeObjInvisible();
}

void CSYNTHView::OnUpdateHideselection(CCmdUI* pCmdUI) 
{
	// hide is only valid if at least one object is selected
    ASSERT( m_pSelectionNode != NULL );
    if (m_pSelectionNode->getNumSelected() > 0)
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );	
}

void CSYNTHView::OnShowall() 
{
	// TODO: Add your command handler code here
	int i;
	for (i=0; i<sdoc->ObjCount ; i++)
	{
	   //WARNING : check for NULL pointers
	   if (sdoc->Obj[i]!=NULL)
	   {
         CGObject *obj = (CGObject*)sdoc->Obj[i];
	     obj->MakeObjVisible();
	   }
	} 
}

void CSYNTHView::OnUpdateShowall(CCmdUI* pCmdUI) 
{
	//  show all objects if a scene has created
    if ( sdoc->root != NULL )
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE ); 
}


/************************  VIEWER PROPERTIES ************************/
void CSYNTHView::OnChbackcolor() 
{
	// TODO: Add your command handler code here
   COLORREF m_OptionColorGlBack;
   //CSYNTHApp *pApp = (CSYNTHApp *)AfxGetApp();
   CColorDialog dlg(m_OptionColorGlBack);
   if(dlg.DoModal()==IDOK)
   {
	   //get RGB
       m_ClearColorRed   = (float)GetRValue(m_OptionColorGlBack) / 255.0f;
	   m_ClearColorGreen = (float)GetGValue(m_OptionColorGlBack) / 255.0f;
	   m_ClearColorBlue  = (float)GetBValue(m_OptionColorGlBack) / 255.0f;

   	   m_pViewer->setBackgroundColor(SbColor(m_ClearColorRed,
		                                     m_ClearColorGreen,
											 m_ClearColorBlue));
		   //0.8,0.8,0.8));
   }
}

void CSYNTHView::OnUpdateChbackcolor(CCmdUI* pCmdUI) 
{
	//  change background colorshow if a scene has created
    if ( sdoc->root != NULL )
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
}


void CSYNTHView::OnHomeposition() 
{
	// TODO: Add your command handler code here
	m_pViewer->resetToHomePosition();
}

void CSYNTHView::OnUpdateHomeposition(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_pViewer != NULL )
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
}

void CSYNTHView::OnSethomeposition() 
{
	// TODO: Add your command handler code here
	m_pViewer->saveHomePosition();
}

void CSYNTHView::OnUpdateSethomeposition(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_pViewer != NULL )
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
}

void CSYNTHView::OnHeadlight() 
{
	// TODO: Add your command handler code here
	if (headlight_option) headlight_option = 0;
	                 else headlight_option = 1;

	m_pViewer->setHeadlight(headlight_option);
}

void CSYNTHView::OnUpdateHeadlight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (headlight_option)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}

void CSYNTHView::OnInvdecoration() 
{
	// TODO: Add your command handler code here
	if (decoration_option) decoration_option = 0;
	                  else decoration_option = 1;

	m_pViewer->setDecoration(decoration_option);
}

void CSYNTHView::OnUpdateInvdecoration(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (decoration_option)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}

void CSYNTHView::OnDrawAsIs() 
{
	// TODO: Add your command handler code here
	drawStyle_option = 1;
	m_pViewer->setDrawStyle(SoWinViewer::INTERACTIVE,
		                    SoWinViewer::VIEW_AS_IS);
}

void CSYNTHView::OnUpdateDrawAsIs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (drawStyle_option==1)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}

void CSYNTHView::OnDrawHiddenLine() 
{
	// TODO: Add your command handler code here
	drawStyle_option = 2;
	m_pViewer->setDrawStyle(SoWinViewer::INTERACTIVE,
		                    SoWinViewer::VIEW_HIDDEN_LINE);
}

void CSYNTHView::OnUpdateDrawHiddenLine(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (drawStyle_option==2)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}

void CSYNTHView::OnDrawNoTexture() 
{
	// TODO: Add your command handler code here
	drawStyle_option = 3;
	m_pViewer->setDrawStyle(SoWinViewer::INTERACTIVE,
		                    SoWinViewer::VIEW_NO_TEXTURE);
}

void CSYNTHView::OnUpdateDrawNoTexture(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (drawStyle_option==3)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}

void CSYNTHView::OnDrawLowComp() 
{
	// TODO: Add your command handler code here
	drawStyle_option = 4;
	m_pViewer->setDrawStyle(SoWinViewer::INTERACTIVE,
		                    SoWinViewer::VIEW_LOW_COMPLEXITY);
}

void CSYNTHView::OnUpdateDrawLowComp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (drawStyle_option==4)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}

void CSYNTHView::OnDrawLine() 
{
	// TODO: Add your command handler code here
	drawStyle_option = 5;
	m_pViewer->setDrawStyle(SoWinViewer::INTERACTIVE,
		                    SoWinViewer::VIEW_LINE);
}

void CSYNTHView::OnUpdateDrawLine(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (drawStyle_option==5)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}

void CSYNTHView::OnDrawPoint() 
{
	// TODO: Add your command handler code here
	drawStyle_option = 6;
	m_pViewer->setDrawStyle(SoWinViewer::INTERACTIVE,
		                    SoWinViewer::VIEW_POINT);
}

void CSYNTHView::OnUpdateDrawPoint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (drawStyle_option==6)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}

void CSYNTHView::OnDrawBbox() 
{
	// TODO: Add your command handler code here
	drawStyle_option = 7;
	m_pViewer->setDrawStyle(SoWinViewer::INTERACTIVE,
		                    SoWinViewer::VIEW_BBOX);
}

void CSYNTHView::OnUpdateDrawBbox(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (drawStyle_option==7)	
		pCmdUI->SetCheck(TRUE);
    else
		pCmdUI->SetCheck(FALSE);
}

/***********************  ΚΑΤΑΣΤΑΣΗ ΕΠΙΛΟΓΗΣ/ΕΞΕΤΑΣΗΣ  **********************/
void CSYNTHView::OnViewing() 
{
    if (m_pViewer->isViewing())
		m_pViewer->setViewing(0);
	else
		m_pViewer->setViewing(1);
}

void CSYNTHView::OnUpdateViewing(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	ASSERT(m_pViewer);
	if (m_pViewer!=NULL)
	{
	  pCmdUI->Enable( TRUE );

	  if (m_pViewer->isViewing())	
	  	pCmdUI->SetCheck(TRUE);
      else
	 	pCmdUI->SetCheck(FALSE);
	}
	else
		pCmdUI->Enable( FALSE );
}

/****************** DIRECTIONAL LIGHT WINDOW ********************/
void CSYNTHView::OnDirlight() 
{
	// TODO: Add your command handler code here
	if (myLEditor->isAttached())
	{
	  if (myLEditor->isVisible()) myLEditor->hide();
	                         else myLEditor->show();
	}
	else
		AfxMessageBox("No Light resource available");
}

void CSYNTHView::OnUpdateDirlight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (myLEditor->isAttached())
	{
	  pCmdUI->Enable( TRUE );

	  if (myLEditor->isVisible())	
	  	pCmdUI->SetCheck(TRUE);
      else
		pCmdUI->SetCheck(FALSE);
	}
	else
		pCmdUI->Enable( FALSE );
}
/****************** MATERIAL WINDOW ********************/
void CSYNTHView::OnMaterialedit() 
{
	// TODO: Add your command handler code here
	if (myMEditor->isAttached())
	{
	  if (myMEditor->isVisible()) myMEditor->hide();
	                         else myMEditor->show();
	}
	else
		AfxMessageBox("No material resource available");
}

void CSYNTHView::OnUpdateMaterialedit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (myMEditor->isAttached())
	{
	  pCmdUI->Enable( TRUE );

	  if (myMEditor->isVisible())	
	  	pCmdUI->SetCheck(TRUE);
      else
		pCmdUI->SetCheck(FALSE);
	}
	else
		pCmdUI->Enable( FALSE );
}
