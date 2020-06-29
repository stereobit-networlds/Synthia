// SYNTHView.cpp : implementation of the CSYNTHView class
//

#include "stdafx.h"
#include "SYNTH.h"

#include "SYNTHDoc.h"
#include "SYNTHView.h"
#include "Lib0.h"

#include "GExternal.h"
#include "RoomBase.h"
#include "WorldBase.h"
#include "RoomWall.h"
#include "DeleteObj.h"
#include "SelectObj.h"
#include "Wizz0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <Inventor/nodes/SoSelection.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <Inventor/Win/viewers/SoWinWalkViewer.h>
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
#include <Inventor/win/SoWinColorEditor.h>

#include <Ivf/Viewers/IvfSceneViewer.h>
#include <Inventor/nodes/SoCylinder.h>

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
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EXTENTED_CUT, OnExtentedCut)
	ON_UPDATE_COMMAND_UI(ID_EXTENTED_CUT, OnUpdateExtentedCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_UNGROUP, OnUpdateUngroup)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_VIEW_SELECTIONMODE, OnViewViewmodesSelectionmode)
	ON_COMMAND(ID_VIEW_VIEWINGMODE, OnViewViewmodesViewingmode)
	ON_COMMAND(ID_UNGROUP, OnUngroup)
	ON_COMMAND(SYNTH_PROJECT, OnNewProject)
	ON_UPDATE_COMMAND_UI(SYNTH_PROJECT, OnUpdateNewProject)
	ON_COMMAND(SYNTH_PROPERTIES, OnProperties)
	ON_UPDATE_COMMAND_UI(SYNTH_PROPERTIES, OnUpdateProperties)
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
	ON_COMMAND(ID_MATERIALEDIT, OnMaterialedit)
	ON_UPDATE_COMMAND_UI(ID_MATERIALEDIT, OnUpdateMaterialedit)
	ON_COMMAND(SYNTH_ADDWALL, OnAddwall)
	ON_UPDATE_COMMAND_UI(SYNTH_ADDWALL, OnUpdateAddwall)
	ON_COMMAND(SYNTH_SELECT, OnSelectExternal)
	ON_UPDATE_COMMAND_UI(SYNTH_SELECT, OnUpdateSelectExternal)
	ON_COMMAND(ID_REPLACE, OnReplace)
	ON_UPDATE_COMMAND_UI(ID_REPLACE, OnUpdateReplace)
	ON_COMMAND(SYNTH_JUMP, OnJump)
	ON_UPDATE_COMMAND_UI(SYNTH_JUMP, OnUpdateJump)
	ON_COMMAND(ID_EDIT_UNDO, OnUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateUndo)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CSYNTHView	*sview ;
SbVec3f		picked_point ;   //gobal picked point
SbVec3f		picked_normal ;  //global picked normal

CSYNTHView::CSYNTHView()
{
	// TODO: add construction code here
// IVF_EXAMPLE_BEGIN
//	pdoc->root = NULL;
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

	if (m_pClipboard != NULL) 
	{ 
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
        // Create the SoSelection node that will be pdoc->root of scene graph
        m_pSelectionNode = new SoSelection;
        m_pSelectionNode->ref();
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


	   SoMouseButtonEvent  myMouseEvent;

	   // Add an event callback to catch mouse button presses.
       // The callback is set up later on.
	   SoEventCallback *EventCB = new SoEventCallback;
	   m_pSelectionNode->addChild(EventCB);

	   // Set up the event callback. We want to pass the pdoc->root of the
	   // entire scene graph (including the camera) as the userData,
	   // so we get the scene manager's version of the scene graph
	   // pdoc->root.
	   EventCB->addEventCallback ( SoMouseButtonEvent::getClassTypeId(),
		                           CSYNTHView::MousePressCB,this);
								   //m_pViewer->getSceneManager()->getSceneGraph());

	   // Set our selection node as the scene graph pdoc->root node
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
    CSYNTHDoc* pdoc = GetDocument() ;
	if (pdoc->Wizard) StartScene();
    
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

	//detach light editor...
	if (myLEditor->isAttached()) 
	{
		if (myLEditor->isVisible()) myLEditor->hide();
		myLEditor->detach(); 
	}

	IvfOnDestroy();
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

		//add by me.. on activate show light editor...
	    if (myLEditor->isAttached())
		{
	      //if (myLEditor->isVisible()) myLEditor->show();
          if (theApp.TheLightIs) myLEditor->show();
		}

        }
	else if(!bActivate && pDeactiveView == (CView *)this) {
	IvfOnDeactivateComponent() ;

	  //add by me.. on deactivate hide light editor...
	  if (myLEditor->isAttached())
	  {
	    if (myLEditor->isVisible()) myLEditor->hide();
		//if (theApp.TheLightIs) myLEditor->hide();
	  }
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

//undo...
void CSYNTHView::OnUndo() 
{
	//CIvfApp *pApp = CIvfApp::IvfGetApp();
	CSYNTHDoc* pdoc = GetDocument();

	if ( pdoc->new_object )  //αυτο σημαινει οτι αν προκειται να κανουμε click για νεο αντικειμενο ακυρωνεται
    {
		if (pdoc->Obj[pdoc->ObjCount-1]->IsKindOf(RUNTIME_CLASS(CGExternal)))
        {
		  CGExternal  *external_obj ;

		  //delete object from inventor...ειναι το τελευταιο και αορατο
		  external_obj->DeleteObject(pdoc->ObjCount-1);

		  pdoc->new_object = _NONE_;

		  pdoc->UpdateAllViews(NULL);
        }
		else
        if (pdoc->Obj[pdoc->ObjCount-1]->IsKindOf(RUNTIME_CLASS(CRoomWall)))
        {
          pdoc->new_object = _NONE_; //just undo new object
        }
    }
	else //αλλιως φερε το αντιγραφο
    {
	  //IvfDeleteContents();
	  //OnOpenDocument("Synth_.iv");
	  //if (pApp->IvfIsMdi()) IvfSceneGraphChanged();

	  //InventorToObjects(); //get data...
    }

	pdoc->UndoParam = false; //if undo disable it...

    pdoc->SetModifiedFlag();
}

void CSYNTHView::OnUpdateUndo(CCmdUI* pCmdUI) 
{
	CSYNTHDoc* pdoc = GetDocument();

	pCmdUI->Enable(pdoc->UndoParam);
}

void CSYNTHView::OnEditCopy() 
{
    CSYNTHDoc* pdoc = GetDocument();

	//if the object is GExternal type...
    if (pdoc->Obj[pdoc->obj_selector]->IsKindOf(RUNTIME_CLASS(CGExternal)))
    {
      CGExternal *myext;

	  myext->CopyObject(pdoc->obj_selector);
	  pdoc->copy_mode = true ;
    }
	else //if it is RoomWall type...
	if (pdoc->Obj[pdoc->obj_selector]->IsKindOf(RUNTIME_CLASS(CRoomWall)))
    {
	  CRoomWall *mywall;

	  mywall->CopyObject(pdoc->obj_selector);
	  pdoc->copy_mode = true ;
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
	CSYNTHDoc* pdoc = GetDocument();

    // Ανοίγει το παράθυρο διαγραφής αντικειμένου
	DeleteObj *dlg = new DeleteObj ;
   
	if (dlg->DoModal() == IDOK)   
	{
      if (pdoc->obj_selector>0) //delete only walls, roombase ,externals
	  {
	    pdoc->SaveUndo(); //save scene for undo...

        CGObject *obj = (CGObject*)pdoc->Obj[pdoc->obj_selector]; 
	    //if the object is GExternal type...
        if (obj->IsKindOf(RUNTIME_CLASS(CGExternal)))
		{
          CGExternal  *ext_obj = (CGExternal*)obj;
		  ext_obj->DelObject(sdoc->obj_selector,0);
		}
	    else
        //if the object is RoomWall type...
        if (pdoc->Obj[pdoc->obj_selector]->IsKindOf(RUNTIME_CLASS(CRoomWall)))
		{
          CRoomWall *Wall_obj = (CRoomWall*)obj;
		  Wall_obj->DeleteObject(pdoc->obj_selector);
		}
        else  AfxMessageBox("Invalid selection. Access denied."); 
	  }
	  else AfxMessageBox("Access denied."); 
   

	  pdoc->SetModifiedFlag();
	  pdoc->UpdateAllViews(NULL); 
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
 
void CSYNTHView::OnExtentedCut() 
{
	CSYNTHDoc* pdoc = GetDocument();

    // Ανοίγει το παράθυρο διαγραφής αντικειμένου
	DeleteObj *dlg = new DeleteObj ;
   
	if (dlg->DoModal() == IDOK)   
	{
      if (pdoc->obj_selector>0) //delete only walls, roombase ,externals
	  { 
	    pdoc->SaveUndo(); //save scene for undo...

	    CGObject *obj = (CGObject*)pdoc->Obj[pdoc->obj_selector]; 
	    //if the object is GExternal type...
        if (obj->IsKindOf(RUNTIME_CLASS(CGExternal)))
		{
	      CGExternal  *ext_obj = (CGExternal*)obj;
		  ext_obj->DelObject(pdoc->obj_selector,1);
		}
        else 
          AfxMessageBox("Invalid selection. Access denied."); 
	  }
	  else 
		AfxMessageBox("Invalid selection. Access denied."); 

	  pdoc->SetModifiedFlag();
	  pdoc->UpdateAllViews(NULL); 
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


void CSYNTHView::OnEditPaste() 
{
	CSYNTHDoc* pdoc = GetDocument();

    pdoc->SaveUndo(); //save scene for undo...

	CGObject *object = ((CGObject*)pdoc->Obj[pdoc->LastCopy]);

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
}

void CSYNTHView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
    CSYNTHDoc* pdoc = GetDocument();

    if (pdoc->copy_mode==true)
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
}

//replace selected object...
void CSYNTHView::OnReplace() 
{
	CSYNTHDoc* pdoc = GetDocument();

    //check selection
	if (pdoc->Obj[pdoc->obj_selector]->IsKindOf(RUNTIME_CLASS(CGExternal)))
    {
      //enable the replace
	  pdoc->REPLACE = true ;
	  //disable the battering ...
	  pdoc->BATTERY = false ;

	  // Ανοίγει το παράθυρο επιλογής αντικειμένου
	  CSelectObj *dlg = new CSelectObj ;
   
	  if (dlg->DoModal() == IDOK)   
	  {
        //disable the replace
		pdoc->REPLACE = false ;
	  } 
    }
	else
	  AfxMessageBox("Invalid selection. Access denied.");	  
}

void CSYNTHView::OnUpdateReplace(CCmdUI* pCmdUI)
{
	CSYNTHDoc* pdoc = GetDocument();

    //  replace Object is only valid if a scene has created
	ASSERT(pdoc->root!=NULL);
	if (( pdoc->root != NULL ) && (pdoc->obj_selector>0))
    {
		if (pdoc->Obj[pdoc->obj_selector]->IsKindOf(RUNTIME_CLASS(CGExternal)))
        {
          pCmdUI->Enable( TRUE );	
        }
		else
          pCmdUI->Enable( FALSE );
    }
    else
        pCmdUI->Enable( FALSE );
}

//transfer selected object ...
void CSYNTHView::OnJump() 
{
	CSYNTHDoc* pdoc = GetDocument();

	if (pdoc->Obj[pdoc->obj_selector]->IsKindOf(RUNTIME_CLASS(CGExternal)))
    {
      pdoc->SaveUndo(); //save scene for undo...
	  pdoc->new_object = _EXTERNAL_;  	//just say new object = external
    }
    else
      AfxMessageBox("No valid selection.");

	
}

void CSYNTHView::OnUpdateJump(CCmdUI* pCmdUI) 
{
	CSYNTHDoc* pdoc = GetDocument();

	ASSERT(pdoc->root!=NULL);
    if (( pdoc->root != NULL ) && (pdoc->obj_selector>0))
    {
		if (pdoc->Obj[pdoc->obj_selector]->IsKindOf(RUNTIME_CLASS(CGExternal)))
        {
          pCmdUI->Enable( TRUE );	
        }
		else
          pCmdUI->Enable( FALSE );
    }
    else
        pCmdUI->Enable( FALSE );
	
}

//ungroup battery objects...
void CSYNTHView::OnUngroup()
{ 
	CSYNTHDoc* pdoc = GetDocument();

	if (pdoc->obj_selector>0) //ungroup only externals
    {
	  CGObject *obj = (CGObject*)pdoc->Obj[pdoc->obj_selector];
	  //if the object is GExternal type...
      if (obj->IsKindOf(RUNTIME_CLASS(CGExternal)))
      {
		 CGExternal  *ext = (CGExternal*)obj;
         pdoc->SaveUndo(); //save scene for undo...

         //do the job...
		 ext->UnGroupObjects();
      }
      else 
		AfxMessageBox("Invalid selection. Access denied."); 
	}
	else 
	  AfxMessageBox("Invalid selection. Access denied."); 

	pdoc->SetModifiedFlag();
}

void CSYNTHView::OnUpdateUngroup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	ASSERT( m_pSelectionNode != NULL );
    if (m_pSelectionNode->getNumSelected() > 0)
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


//start the main scene creation...
void CSYNTHView::StartScene()
{
        CSYNTHDoc* pdoc = GetDocument();

		if (pdoc->root!=NULL) 
        { 
    		//deselect ...
	        GetSelectionNode()->deselectAll();
         
			//pdoc->root->removeAllChildren(); //οχι ολα γιατι σβηνει και το mouse callback =child 0
             
			SoSeparator *myroot;
			myroot = (SoSeparator *)SoNode::getByName("World_Space");
			int rootchilds =myroot->getNumChildren()-1;

			//AfxMessageBox(lib.inttostr(pdoc->rootchilds));

            //meter>1 διοτι δεν θελω να σβησω το callback(0) και το directionalLight(1)
			for (int meter=rootchilds ; meter>1 ; meter--)
            {
				SoSeparator *mys = (SoSeparator *)myroot->getChild(meter);
				myroot->removeChild(meter);
            }
			CreateScene(); //just create...
        }
		else
        {
		  //material editor 
          myMEditor = new SoWinMaterialEditor
   		  (NULL,"Material Editor",TRUE);

		  // light editor 
          myLEditor = new SoWinDirectionalLightEditor
   		  (NULL,"My Light Editor",TRUE);

		  pdoc->root = new SoSeparator ;
		  pdoc->root->ref() ;
		  pdoc->root->setName("World_Space");
 
		  //add light
 		  SoDirectionalLight *myLight = new SoDirectionalLight;
          pdoc->root->addChild(myLight);
          //attach light
		  lightpath = new SoPath(myLight);
          myLEditor->attach(lightpath);
          //myLEditor->show();

		  CreateScene();
		  pdoc->IvfSetSceneGraph( pdoc->root );
        }
		pdoc->SetModifiedFlag();
	    pdoc->UpdateAllViews(NULL);
}

//create the scene ... called by the startscene
void CSYNTHView::CreateScene()
{
		CSYNTHDoc* pdoc = GetDocument();

	    //init points
		picked_point[0] = 0;
		picked_point[1] = 0;
		picked_point[2] = 0;
		picked_normal[0] = 1; //???
		picked_normal[1] = 0; 
		picked_normal[2] = 0;

/*		// setup world base 
        CWorldBase *world ;
		world->AddNewObject(picked_point, picked_normal);

		// setup the room base
        CRoomBase *rbase ;
		rbase->AddNewObject(picked_point, picked_normal);

		// setup the walls (init for first time) 
		//get first koryf of base 
		picked_point[0] = rbase->Koryfsx[0];
		picked_point[1] = rbase->Koryfsy[0];
		picked_point[2] = rbase->Koryfsz[0];

		CRoomWall *wll;
		wll->AddNewObject(picked_point, picked_normal);*/


		SoSeparator *pSep   = new SoSeparator;
        SoMaterial  *pMat   = new SoMaterial;
        SoCylinder  *pCyl   = new SoCylinder;
        SoPickStyle *pStyle = new SoPickStyle;

        pStyle->style = SoPickStyle::UNPICKABLE;

        pdoc->root->addChild( pSep );
        pdoc->root->addChild( pStyle );

        pSep->addChild( pMat );
        pSep->addChild( pCyl );

}

//start new project on existing window...
void CSYNTHView::OnNewProject() 
{
	CSYNTHDoc* pdoc = GetDocument();
	CWizz0 *dlg = new CWizz0 ;    //wizard 0 open
   
	if (dlg->DoModal() == IDOK)   
	{
        StartScene();
	}
	
}

void CSYNTHView::OnUpdateNewProject(CCmdUI* pCmdUI) 
{
	CSYNTHDoc* pdoc = GetDocument();
    // Copy is only valid if at least one object is selected
    ASSERT( pdoc->root != NULL );
    if (pdoc->root != NULL)
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
}


//add wall object...
void CSYNTHView::OnAddwall() 
{
	// TODO: Add your command handler code here

	CWizz0 *dlg = new CWizz0 ;
   
	CSYNTHDoc* pdoc = GetDocument();
	if (dlg->DoModal() == IDOK)   
	{
		pdoc->SaveUndo(); //save scene for undo...
		pdoc->new_object = _ROOMWALL_ ;   			
	}	
}

void CSYNTHView::OnUpdateAddwall(CCmdUI* pCmdUI) 
{
    CSYNTHDoc* pdoc = GetDocument();
	//  Add wall only if a scene has created
	ASSERT(pdoc->root!=NULL);
    if ( pdoc->root != NULL )
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
	
}


//add a new external object...
void CSYNTHView::OnSelectExternal() 
{
	// Ανοίγει το παράθυρο επιλογής αντικειμένου
	CSelectObj *dlg = new CSelectObj ;
   
	if (dlg->DoModal() == IDOK)   
	{
       //τοποθετειται το αντεικιμενο αορατο στην θεση 0,0,0
	}	
}

void CSYNTHView::OnUpdateSelectExternal(CCmdUI* pCmdUI)
{
	CSYNTHDoc* pdoc = GetDocument();
//  CSelect Object is only valid if a scene has created
    if ( pdoc->root != NULL )
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE ); 
}

//objects properties
void CSYNTHView::OnProperties() 
{
	CSYNTHDoc* pdoc = GetDocument();
	int Selection = pdoc->obj_selector; //get object selection number

	// Ανοίγει το παράθυρο ιδιοτήτων του επιλεγμένου αντικειμένου
	int res ;
	if (Selection < 0) return ;

	if (pdoc->Obj[Selection]->IsKindOf(RUNTIME_CLASS(CWorldBase)))
		res = ((CWorldBase*)pdoc->Obj[Selection])->EditProperties(pdoc,pdoc->root) ;
	else
	if (pdoc->Obj[Selection]->IsKindOf(RUNTIME_CLASS(CRoomBase)))
		res = ((CRoomBase*)pdoc->Obj[Selection])->EditProperties(pdoc,pdoc->root) ;
	else
	if (pdoc->Obj[Selection]->IsKindOf(RUNTIME_CLASS(CRoomWall)))
		res = ((CRoomWall*)pdoc->Obj[Selection])->EditProperties(pdoc,pdoc->root) ;
	else
	if (pdoc->Obj[Selection]->IsKindOf(RUNTIME_CLASS(CGExternal)))
		res = ((CGExternal*)pdoc->Obj[Selection])->EditProperties(pdoc,pdoc->root) ;

	if (res == IDOK) 
	{
		pdoc->SetModifiedFlag();
		pdoc->UpdateAllViews(NULL);   
	} 	
}

void CSYNTHView::OnUpdateProperties(CCmdUI* pCmdUI) 
{
	// Properties is only valid if at least one object is selected
	CSYNTHDoc* pdoc = GetDocument();

    if (pdoc->obj_selector >= 0)
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
}

//add a sphere
void CSYNTHView::AddSphere(SbVec3f p_point,SbVec3f p_normal)
{
	 CSYNTHDoc* pdoc = GetDocument();

	 //save for undo
	 pdoc->SaveUndo();

	 //create sphere
	 SoSeparator *mysep = new SoSeparator ;
          
     SoTransform *trans	= new SoTransform ;
     trans->translation.setValue(p_point);

     SoDrawStyle *ds = new SoDrawStyle ;
	 ds->style = SoDrawStyle::FILLED ;

	 mysep->addChild( trans );
     mysep->addChild( ds );	

	 // setup shape
	 SoSphere *sphere = new SoSphere ;
	 sphere->radius = (float).1 ;
	
	 // setup material
	 SoMaterial  *mat = new SoMaterial;
	 mat->diffuseColor.setValue( 0., 0.5, 0.5 ); 

     // setup graph
	 mysep->addChild( mat );	
	 mysep->addChild( sphere );

	 mysep->setName("Sphere");
     pdoc->root->addChild(mysep);


     pdoc->SetModifiedFlag();
	 pdoc->UpdateAllViews(NULL);
	 //pdoc->IvfSetSceneGraph( mypdoc->root ); //???????????????? κολαει
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

SbBool CSYNTHView::writePickedPath ( SoNode *root, const SbViewportRegion &viewport, 
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
void CSYNTHView::GetPickObjectID(SoPath *path)
{
	CLib0 lib;
	int my_id ;

	CSYNTHDoc* pdoc = GetDocument();

	my_id = -1; //initializate my_id=selector with invalid number
	pdoc->BATTERY = false ; //init battering  
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
		  myNode = parent->getChild(3);
      }

	  if (strncmp(name,"RoomBase",8)==0) 
      {
		  //get the wall number
          char *digits = "0123456789";
		  char *mynum ;

		  mynum = strpbrk(name,digits) ; //get the number from name
          my_id = lib.strtoint(mynum);

		  //get material node
		  myNode = parent->getChild(3);
      }

	  if (strncmp(name,"RoomWall",8)==0)
      {
		  //get the wall number
          char *digits = "0123456789";
		  char *mynum ;

		  mynum = strpbrk(name,digits) ; //get the number from name
          my_id = lib.strtoint(mynum);

		  //get material node
		  myNode = parent->getChild(3);
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

			 pdoc->BATTERY = true;

			 //get material node (ofparent !!!)
		     myNode = ofparent->getChild(3);
		 }
		 else
         {
			 AfxMessageBox("Unknown Object ,2");
         }
      }


      pdoc->obj_selector = my_id ; //set selector

	  if (my_id!=-1) //αυτο σημαινει οτι το object ειναι εγκυρο
      { 
	    CGObject *obj = (CGObject*)pdoc->Obj[my_id];

		pdoc->obj_type = obj->id ; //get the object type

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
   	      pdoc->obj_type = _NONE_;
	  	  AfxMessageBox("Invalid Object");
      }
	}
    else
	{
		AfxMessageBox("Unknown Object ,1");
    } 
}

void CSYNTHView::AddObjects()
{
	CSYNTHDoc* pdoc = GetDocument();

   	if ( pdoc->new_object ) 
	{
		if (pdoc->new_object ==_EXTERNAL_)
        {
          //CGExternal *ext = ((CGExternal*)pdoc->Obj[pdoc->ObjCount-1]) ; //get last input
		  //ext->AddNewObject(picked_point, picked_normal);
			AfxMessageBox("1");
        }
		else
        if (pdoc->new_object ==_ROOMWALL_)
        {
          //CRoomWall *wll; //get nothing ...walls build in
		  //wll->AddNewObject(picked_point, picked_normal);
			AfxMessageBox("2");
        }
		else
			AfxMessageBox("Access denied : Unknown Object");

		pdoc->SetModifiedFlag() ;
		pdoc->UpdateAllViews(NULL);   // !!! οχι ολα γιατι "τρέμει" η σύνθεση (βελτιωση)		
	}
}

//======================== MousePressCB =====================

void CSYNTHView::MousePressCB(void *userData, SoEventCallback *eventCB)
{
	CSYNTHView *pThis = (CSYNTHView *)userData;
	//SoSeparator *pdoc->root = (SoSeparator *) userData;

	const SoEvent *event = eventCB->getEvent();

    // Check for mouse button being pressed
    if (SO_MOUSE_PRESS_EVENT(event, ANY))
	{
		const SbViewportRegion &myRegion = eventCB->getAction()->getViewportRegion();
		pThis->writePickedPath(pThis->m_pViewer->getSceneManager()->getSceneGraph(),
			                   myRegion,
						       event->getPosition(myRegion));
		eventCB->setHandled();

		pThis->AddSphere(picked_point,picked_normal);
		pThis->AddObjects();
	}
}

///////////////////////////////////////////////////////////////////////
// Overrides of IVF member functions


// IVF_EXAMPLE_BEGIN
// This method forces the component to use the scene graph pointed to
// by ppdoc->root instead of the scene graph contained in the document.
void CSYNTHView::IvfSetSceneGraph(SoNode *proot)
{
    // Note: We may get called with NULL from IvfOnInitialUpdate.
    //       We may even get called before m_pSelectionNode has
    //       been created.  Just live with it for now.
    if (proot != NULL && m_pSelectionNode != NULL) {

        // Instead of setting the document's scene graph directly into the
        // viewer we add it to our selection node (which is already set
        // in the viewer).
        m_pSelectionNode->addChild( proot );
        
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
    if ( m_pViewer != NULL )
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
    if ( m_pViewer != NULL )
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
    if ( m_pViewer != NULL )
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
    if ( m_pViewer != NULL )
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE ); 
}


/************************  VIEWER PROPERTIES ************************/

void CSYNTHView::OnChbackcolor() 
{
   // TODO: Add your command handler code here

   //WINDOWS METHOD....
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

	   CLib0 lib;
	   AfxMessageBox(lib.floattostr(m_ClearColorRed)+" "+
	  	             lib.floattostr(m_ClearColorGreen)+" "+
					 lib.floattostr(m_ClearColorBlue));
		   //0.8,0.8,0.8));

	   //****************************************************
	   CSYNTHDoc* pdoc=GetDocument();
	   IvfDestroyComponent();  //destroy current ...

/*	   //first method ...
       static int cArgs[]= { 
		TRUE,		// Decoration
		FALSE,	    // URL Display
		TRUE,		// Viewpoints
		FALSE       // URL Fetch
	   };		

	   pDoc->IvfCreateComponent(this,(void *)cArgs); //create new viewer...
	   if (pDoc->IvfGetDocSceneGraph() != NULL) pDoc->IvfResetComponent(pDoc);
       m_pViewer->setSceneGraph( m_pSelectionNode );
       m_pViewer->setGLRenderAction( new SoBoxHighlightRenderAction() );
       m_pViewer->redrawOnSelectionChange( m_pSelectionNode ) ;
       //pDoc->IvfSetSceneGraph(pDoc->pdoc->root);
*/

	   //second method... 
       m_pViewer = new SoWinWalkViewer(GetSafeHwnd());
	   //m_pViewer->setAutoRedraw(1);
	   m_pViewer->setSceneGraph( m_pSelectionNode );
       m_pViewer->setGLRenderAction( new SoBoxHighlightRenderAction() );
       m_pViewer->redrawOnSelectionChange( m_pSelectionNode ) ;
	   pdoc->IvfSetSceneGraph(pdoc->root);
	   m_pViewer->show();
   }  

   //INVENTOR METHOD....
   //SoWinColorEditor *myCEditor = new SoWinColorEditor(NULL,"Edit Background Color",TRUE);
   //myCEditor->show();
   //......
}

void CSYNTHView::OnUpdateChbackcolor(CCmdUI* pCmdUI) 
{
	//  change background colorshow if a scene has created
    if ( m_pViewer != NULL )
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
	if ((theApp.TheLightIs == true) || (myLEditor->isVisible()))
	{
		 theApp.TheLightIs = false;
	}
	else theApp.TheLightIs = true;
	
	switch (theApp.TheLightIs)
	{
		case true  : myLEditor->show(); break;
		case false : myLEditor->hide(); break;
	}
}

void CSYNTHView::OnUpdateDirlight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (myLEditor->isAttached())
	{
      pCmdUI->Enable( TRUE );
	  if ((theApp.TheLightIs == true) || (myLEditor->isVisible()))
	  {
	    pCmdUI->SetCheck( TRUE );
	  }
	  else
	    pCmdUI->SetCheck( FALSE );
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



