// SYNTHView.cpp : implementation of the CSYNTHView class
//

#include "stdafx.h"
#include "SYNTH.h"

#include "SYNTHDoc.h"
#include "SYNTHView.h"
#include "GExternal.h"
#include "Lib0.h"
//#include "DeleteObj.h"

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


/////////////////////////////////////////////////////////////////////////////
// CSYNTHView

IMPLEMENT_DYNCREATE(CSYNTHView, CView)

BEGIN_MESSAGE_MAP(CSYNTHView, CView)
	//{{AFX_MSG_MAP(CSYNTHView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
// BEGIN_IVWGEN
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_PICEDIT, OnViewPicedit)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PICEDIT, OnUpdateViewPicedit)
	//ON_COMMAND(ID_EDIT_CUT, OnDelete)  this command called from OnDelete of doc
	//ON_COMMAND(ID_EDIT_CUT, OnEditCut) redirect this command to "OnDelete"
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	//ON_COMMAND(ID_EDIT_CUT, OnExtDelete)  this command called from OnExtDelete of doc
	//ON_COMMAND(ID_EXTENTED_CUT, OnExtentedCut) redirect this command to "OnExtDelete" 
	ON_UPDATE_COMMAND_UI(ID_EXTENTED_CUT, OnUpdateExtentedCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_VIEW_VIEWINGMODE, OnViewViewmodesViewingmode)
	ON_COMMAND(ID_VIEW_SELECTIONMODE, OnViewViewmodesSelectionmode)
	ON_COMMAND(ID_UNGROUP, OnUnGroup)
	ON_UPDATE_COMMAND_UI(ID_UNGROUP, OnUpdateUnGroup)
// END_IVWGEN
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

    m_pClipboard = NULL;    //SelectB

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


// IVF_EXAMPLE_BEGIN
    if (m_pSelectionNode == NULL) { //---/
        // Create the SoSelection node that will be root of scene graph
        m_pSelectionNode = new SoSelection;
        m_pSelectionNode->ref();


// IVF EXAMPLE_End


//	m_nEnableSelection = TRUE; has defined already in construction

//	SoSelection *pSelectionNode = IvfGetSelectionNode();
	m_pSelectionNode->policy = SoSelection::SHIFT ;
	//m_pSelectionNode->addSelectionCallback(selectionCallback, NULL);
	//m_pSelectionNode->addDeselectionCallback(deselectionCallback, NULL);
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

	} //---/

	// Create an instance of the clipboard and associate with our window
    if (m_pClipboard == NULL) {
        m_pClipboard = new SoWinClipboard( GetSafeHwnd() );
    }
    
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
    // Get list of all selected objects
    Time eventTime = time(NULL);
	const SoPathList *pPathList = m_pSelectionNode->getList();
    ASSERT( pPathList != NULL );

    // Copy all selected objects to clipboard
    if (pPathList->getLength() > 0)
        m_pClipboard->copy( (SoPathList*)pPathList, eventTime );

	// Copy the object to my copy array
	sdoc->Copy_Obj[1] = sdoc->Obj[sdoc->obj_selector];
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
    Time eventTime = time(NULL);
	m_pClipboard->paste( eventTime, CSYNTHView::OnPasteCB, this );

/*
    LObj2 obj2;

	sdoc->new_object = TRUE ;
	obj2.CreateObject( TRUE, sdoc->root, eid_id, rs_eidh0, rs_mrec ) ;

    Η ιδεα είναι εφοσον στο oncopy εχουμε σωσει το array index και τα eid_id κλπ.
	σ'αυτο το σημειο κανουμε createobject οπως στο select

    Αυτο σημαινει οτι ο υπαρχον κωδικας του copy paste ( μεσω winClipboard )
	δεν χρειαζεται
*/
}

void CSYNTHView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
    // Update "Paste" UI items
    // Paste is only valid if there is something in the clipboard
    if (IsClipboardFormatAvailable(CF_TEXT))
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
    CGExternal  *external_obj ;

	if (sdoc->obj_selector>0) //delete only walls, roombase ,externals
    {
	  //if the object is GExternal type...
      if (sdoc->Obj[sdoc->obj_selector]->IsKindOf(RUNTIME_CLASS(CGExternal)))
      {
         //.. my delete .. (make object invisible)
	     SoSeparator *sep = ((CGExternal*)sdoc->Obj[sdoc->obj_selector])->sep ;		
	     SoDrawStyle	*ds = (SoDrawStyle *)sep->getChild(0) ;
         ds->style = SoDrawStyle::INVISIBLE  ;

         //rebuild the buttering -before- delete the selected object
         external_obj->DelRebuildButtering(); 
      }
      //OnEditCut(); //call OnEditCut (ετοιμη ρουτινα) delete the selected object  (κολλαει μετά στην εισαγωγη object)
      else  AfxMessageBox("Access denied."); 

	  //delete object from Object array
	  sdoc->Obj[sdoc->obj_selector]=NULL;
	  //deselect ...
	  GetSelectionNode()->deselectAll();
	}
	else AfxMessageBox("Access denied."); 
}

void CSYNTHView::OnExtDelete()
{
    CGExternal  *external_obj ;

	if (sdoc->obj_selector>0) //delete only walls, roombase ,externals
    {
	  //if the object is GExternal type...
      if (sdoc->Obj[sdoc->obj_selector]->IsKindOf(RUNTIME_CLASS(CGExternal)))
      {
         //.. my delete .. (make object invisible)
	     SoSeparator *sep = ((CGExternal*)sdoc->Obj[sdoc->obj_selector])->sep ;		
	     SoDrawStyle	*ds = (SoDrawStyle *)sep->getChild(0) ;
         ds->style = SoDrawStyle::INVISIBLE  ;
         //rebuild the buttering -before- delete the selected object
         external_obj->ExtDelRebuildButtering(); 
      }
      else //OnExtentedCut(); 
           AfxMessageBox("Invalid selection. Access denied."); 

	  //delete object from Object array
	  sdoc->Obj[sdoc->obj_selector]=NULL;
	  //deselect ...
	  GetSelectionNode()->deselectAll();
	}
	else AfxMessageBox("Invalid selection. Access denied."); 
}


void CSYNTHView::OnUnGroup()
{
	CGExternal  *external_obj ;

	if (sdoc->obj_selector>0) //ungroup only externals
    {
	  //if the object is GExternal type...
      if (sdoc->Obj[sdoc->obj_selector]->IsKindOf(RUNTIME_CLASS(CGExternal)))
      {
         //do the job...
		 external_obj->UnGroupObjects();
      }
      else AfxMessageBox("Invalid selection. Access denied."); 
	}
	else AfxMessageBox("Invalid selection. Access denied."); 

}

void CSYNTHView::OnUpdateUnGroup(CCmdUI* pCmdUI) 
{
    ASSERT( m_pSelectionNode != NULL );
    if (m_pSelectionNode->getNumSelected() > 0)
   // {
    //if the object is GExternal type...
    //if (sdoc->Obj[sdoc->obj_selector]->IsKindOf(RUNTIME_CLASS(CGExternal)))
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
   //}
}
//***********************************

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
	  return p->copy(0,i+1);
      //return p;

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
//Η ρουτινα αυτη  βρίσκει το id του clicked object. 
//επιστρεφει το ονομα ως τυπου αντικειμένου και το νουμερο του ονοματος ως object counter
void GetPickObjectID(SoPath *path)
{
	CLib0 lib;
	int id ;

	id = -1; //initializate id=selector with invalid number
	sdoc->BUTTERING = false ; //init buttering  

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
          id = lib.strtoint(mynum);
      }
	  if (strncmp(name,"RoomBase",8)==0)
      {
		  //get the wall number
          char *digits = "0123456789";
		  char *mynum ;

		  mynum = strpbrk(name,digits) ; //get the number from name
          id = lib.strtoint(mynum);
      }
	  if (strncmp(name,"RoomWall",8)==0)
      {
		  //get the wall number
          char *digits = "0123456789";
		  char *mynum ;

		  mynum = strpbrk(name,digits) ; //get the number from name
          id = lib.strtoint(mynum);
      }
	  if (strcmp(name,"")==0)
      {
		 // must be external
         SoSeparator *ofparent = (SoSeparator *)path->getNode(length-4); //get parent of parent
		 const char *name = ((SoSeparator *)ofparent)->getName().getString();//get name
	     //AfxMessageBox(name) ; //all ok !!!

		 if (strncmp(name,"GExternal",9)==0) 
		 {
			 char *digits = "0123456789";
		     char *mynum ;
			 
		     mynum = strpbrk(name,digits) ; //get the object number from name 
             id = lib.strtoint(mynum);     // convert to int

			 sdoc->BUTTERING = true;
		 }
		 else
         {
			 AfxMessageBox("Unknown Object ,2");
         }
      }

      sdoc->obj_selector = id ;
	  if (id!=-1) //αυτο σημαινει οτι το object ειναι εγκυρο
      {
        //do something....
        //sdoc->obj_selector = id ;
		sdoc->obj_type = name ;
		//AfxMessageBox(lib.inttostr(sdoc->obj_selector)+" "+sdoc->obj_type);
      }
	  else
      {
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
	CLib0 lib;
	SoSeparator *root = (SoSeparator *) userData;
	const SoEvent *event = eventCB->getEvent();

    // Check for mouse button being pressed
    if (SO_MOUSE_PRESS_EVENT(event, ANY))
	{
		const SbViewportRegion &myRegion = eventCB->getAction()->getViewportRegion();
		writePickedPath(root, myRegion, event->getPosition(myRegion));
		eventCB->setHandled();
	}

	if ( sdoc->new_object ) 
	{
		SoSeparator *sep = ((CGExternal*)sdoc->Obj[sdoc->ObjCount-1])->sep ;
		
		SoDrawStyle	*ds = (SoDrawStyle *)sep->getChild(0) ;
		SoTranslation *trans = (SoTranslation *)sep->getChild(1) ;
		SoRotation *rot	= (SoRotation *)sep->getChild(2) ;

		ds->style = SoDrawStyle::FILLED ;
		trans->translation	= picked_point ;

		SbRotation *sbrot = new SbRotation(SbVec3f(0,0,1),picked_normal) ;
		rot->rotation.setValue(*sbrot) ;

		//set carrier
		CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->ObjCount-1]) ;
	    ext->carrier_id = sdoc->obj_selector ;
	    ext->SaveProperties();
        //AfxMessageBox(lib.inttostr( ext->carrier_id ) );

		sdoc->new_object = FALSE ; 
		
		//select it..
		sview->GetSelectionNode()->deselectAll();
		sview->GetSelectionNode()->select(sep) ;
		sdoc->obj_selector = sdoc->ObjCount-1 ;
		//.. and set buttering on..
		sdoc->BUTTERING = true;


		sdoc->SetModifiedFlag() ;
		sdoc->UpdateAllViews(NULL);   // !!! οχι ολα γιατι "τρέμει" η σύνθεση (βελτιωση)
		
	}
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




