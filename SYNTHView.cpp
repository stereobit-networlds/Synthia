// SYNTHView.cpp : implementation of the CSYNTHView class
//

#include "stdafx.h"
#include "SYNTH.h"

#include "SYNTHDoc.h"
#include "SYNTHView.h"
#include "GExternal.h"
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
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_VIEW_VIEWINGMODE, OnViewViewmodesViewingmode)
	ON_COMMAND(ID_VIEW_SELECTIONMODE, OnViewViewmodesSelectionmode)
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
}

CSYNTHView::~CSYNTHView()
{
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
SbBool writePickedPath ( SoNode *root, const SbViewportRegion &viewport,  
										const SbVec2s &cursorPosition ) ;
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

	m_nEnableSelection = TRUE;

	SoSelection *pSelectionNode = IvfGetSelectionNode();
	pSelectionNode->policy = SoSelection::SHIFT ;
	pSelectionNode->addSelectionCallback(selectionCallback, NULL);
	pSelectionNode->addDeselectionCallback(deselectionCallback, NULL);

	myHandleBox = new SoHandleBoxManip;
	myHandleBox->ref();
	myTrackball = new SoTrackballManip;
	myTrackball->ref();
	myTransformBox = new SoTransformBoxManip;
	myTransformBox->ref();

	sdoc = GetDocument() ;
	sdoc->new_object = FALSE ;
	sview = this ;

	SoMouseButtonEvent  myMouseEvent;

	// Add an event callback to catch mouse button presses.
	// The callback is set up later on.
	SoEventCallback *EventCB = new SoEventCallback;
	pSelectionNode->addChild(EventCB);

	// Set up the event callback. We want to pass the root of the
	// entire scene graph (including the camera) as the userData,
	// so we get the scene manager's version of the scene graph
	// root.
	EventCB->addEventCallback ( SoMouseButtonEvent::getClassTypeId(),
									MousePressCB,
									m_pViewer->getSceneManager()->getSceneGraph());


	// set the document's selected object
	GetDocument()->SetSelectedObj(pSelectionNode) ;



    // Use a bounding box to highlight selected objects
    m_pViewer->setGLRenderAction( new SoBoxHighlightRenderAction() );

    // Tell viewer to automatically redraw when selection changes
    // (so the highlight will be drawn in the right place)
    m_pViewer->redrawOnSelectionChange( pSelectionNode ) ;

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


void CSYNTHView::OnEditCut() 
{
	IvfOnEditCut();	
}

void CSYNTHView::OnUpdateEditCut(CCmdUI* pCmdUI)
{
	IvfOnUpdateEditCut(pCmdUI);
}

void CSYNTHView::OnEditCopy() 
{
	IvfOnEditCopy();	
}

void CSYNTHView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	IvfOnUpdateEditCopy(pCmdUI);
}


void CSYNTHView::OnEditPaste() 
{
	CDocument *pDoc = CIvfApp::IvfGetAfxDocument(this);
	pDoc->SetModifiedFlag();
	IvfOnEditPaste();	
}


void CSYNTHView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	IvfOnUpdateEditPaste(pCmdUI);
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

/*======================= selectionCallback =============*/

void selectionCallback(   void *, SoPath *selectionPath )
{
	// Attach the manipulator.
	// Use the convenience routine to get a path to
	// the transform that effects the selected object.
//	SoPath *xformPath = createTransformPath(selectionPath);
//	if (xformPath == NULL) return;
//	xformPath->ref();

//	transformBoxPath = xformPath ;
//	myTransformBox->replaceNode(xformPath) ;
/*
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
//	if (deselectionPath->getTail()->isOfType(SoCube::getClassTypeId())) 
//	{
//		myTransformBox->replaceManip(transformBoxPath,NULL);
//		transformBoxPath->unref();
//	}
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
	if (!sdoc->new_object) return FALSE ;

	SoRayPickAction PickAction(viewport);

	// Set an 8-pixel wide region around the pixel
	PickAction.setPoint(cursorPosition);
	PickAction.setRadius(8.0);

	// Start a pick traversal
	PickAction.apply(root) ;
	const SoPickedPoint *PickedPoint =  PickAction.getPickedPoint();
	if (PickedPoint == NULL) return FALSE;

	const SbVec3f *pp = &PickedPoint->getPoint() ;
	const SbVec3f *nn = &PickedPoint->getNormal() ;

	picked_point	= *pp ;
	picked_normal	= *nn ;

//	CLib0 lib ;
//	AfxMessageBox(lib.floattostr((*pp)[0])+" "+lib.floattostr((*pp)[1])+" "+lib.floattostr((*pp)[2])) ;

	return TRUE;
}

//======================== MousePressCB =====================

void MousePressCB(void *userData, SoEventCallback *eventCB)
{
  	if ( sdoc->new_object ) 
	{

     	SoSeparator *root = (SoSeparator *) userData;
	    const SoEvent *event = eventCB->getEvent();

    	const SbViewportRegion &myRegion = eventCB->getAction()->getViewportRegion();
	    writePickedPath(root, myRegion, event->getPosition(myRegion));  
    	eventCB->setHandled();


		SoSeparator *sep = ((CGExternal*)sdoc->Obj[sdoc->ObjCount-1])->sep ;
		
		SoDrawStyle	*ds = (SoDrawStyle *)sep->getChild(0) ;
		SoTranslation *trans = (SoTranslation *)sep->getChild(1) ;
		SoRotation *rot	= (SoRotation *)sep->getChild(2) ;

		ds->style = SoDrawStyle::FILLED ;
		trans->translation	= picked_point ;

		SbRotation *sbrot = new SbRotation(SbVec3f(0,0,1),picked_normal) ;
		rot->rotation.setValue(*sbrot) ;
		
		sdoc->new_object = FALSE ;
		
		sdoc->SetModifiedFlag() ;
		sdoc->UpdateAllViews(NULL);   // !!! οχι ολα γιατι "τρέμει" η σύνθεση (βελτιωση)

	}
}

