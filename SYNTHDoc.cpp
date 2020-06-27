// SYNTHDoc.cpp : implementation of the CSYNTHDoc class
//

#include "stdafx.h"
#include "SYNTH.h"

#include "Resource.h"

#include "SYNTHDoc.h"
#include "SYNTHView.h"
#include "IvfTreeView.h"

#include "Wizz0.h"
#include "Wizz1.h"
#include "lib0.h"
#include "RoomBase.h"
#include "RoomWall.h"
#include "WorldBase.h"
#include "GExternal.h"
#include "SelectObj.h"
#include "DeleteObj.h"

#include <Inventor/manips/SoHandleBoxManip.h>
#include <Inventor/manips/SoTrackballManip.h>
#include <Inventor/manips/SoTransformBoxManip.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSYNTHDoc

IMPLEMENT_DYNCREATE(CSYNTHDoc, CDocument)

BEGIN_MESSAGE_MAP(CSYNTHDoc, CDocument)
	//{{AFX_MSG_MAP(CSYNTHDoc)
	ON_COMMAND(ID_FILE_IMPORT, OnFileImport)
	ON_UPDATE_COMMAND_UI(ID_FILE_IMPORT, OnUpdateFileImport)
	ON_COMMAND(IDM_VIEWPOINTS, OnViewpoints)
	ON_UPDATE_COMMAND_UI(IDM_VIEWPOINTS, OnUpdateViewpoints)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_RELOAD, OnFileReload)
	ON_UPDATE_COMMAND_UI(ID_FILE_RELOAD, OnUpdateFileReload)
	ON_COMMAND(SYNTH_NEW_SPHERE, OnNewSphere)
	ON_COMMAND(SYNTH_PROPERTIES, OnProperties)
	ON_UPDATE_COMMAND_UI(SYNTH_PROPERTIES, OnUpdateProperties)
	ON_COMMAND(SYNTH_KATAXKOYZIN, OnKataxkoyzin)
	ON_COMMAND(SYNTH_SELECT, OnSelectObj)
	ON_UPDATE_COMMAND_UI(SYNTH_SELECT, OnUpdateSelectObj)
	ON_COMMAND(ID_EDIT_CUT, OnDelete)
	ON_COMMAND(ID_EXTENTED_CUT, OnExtDelete)
	ON_COMMAND(ID_UNGROUP, OnUnGroup)
	ON_COMMAND(ID_REPLACE, OnReplaceObj)
	ON_UPDATE_COMMAND_UI(ID_REPLACE, OnUpdateReplaceObj)
	ON_COMMAND(ID_EDIT_UNDO, OnUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateUndo)
	ON_COMMAND(SYNTH_ADDWALL, OnAddwall)
	ON_UPDATE_COMMAND_UI(SYNTH_ADDWALL, OnUpdateAddwall)
	ON_COMMAND(SYNTH_JUMP, OnJump)
	ON_UPDATE_COMMAND_UI(SYNTH_JUMP, OnUpdateJump)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSYNTHDoc	*sdoc ;
SbVec3f		picked_point ;
SbVec3f		picked_normal ;

CSYNTHDoc::CSYNTHDoc()
{
	// TODO: add one-time construction code here

// BEGIN_IVWGEN
	m_bContainsCamera = FALSE;
	m_eOpenType = IVFDOC_OPEN_NORMAL;
// END_IVWGEN

  new_object = _NONE_ ;
  root = NULL;

  //init counters
  ObjCount  = 0; //general object counter
  ob_offset = 0; //external object counter
        
  obj_selector = -1 ;      // my selection generated number (αντικαθιστα το SelId στην επιλογή )
  BATTERING = false ;
  REPLACE = false ;
  copy_mode = false ; 
  UndoParam = false ;
  Wizard = false ;
}

CSYNTHDoc::~CSYNTHDoc()
{
	//root->unref(); //destroy scene    δεν χρειάζεται !!!!
}

BOOL CSYNTHDoc::OnNewDocument()
{
	if (OnNewWizzard()==true)
    {
	  if (!CDocument::OnNewDocument())
	     return FALSE;

	  // TODO: add reinitialization code here
	  // (SDI documents will reuse this document)
	 
      // BEGIN_IVWGEN
         IvfOnNewDocument();
      // END_IVWGEN

      return TRUE;
    }
	else
      return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CSYNTHDoc serialization

void CSYNTHDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
// BEGIN_IVWGEN
            IvfOnSaveDocument(ar.GetFile()->m_hFile) ;
// END_IVWGEN
 
	}
	else
	{
// BEGIN_IVWGEN
		IvfOnOpenDocument(ar.GetFile()->m_hFile) ;
// END_IVWGEN
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSYNTHDoc diagnostics

#ifdef _DEBUG
void CSYNTHDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSYNTHDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSYNTHDoc commands


//  OnFileImport --
//  yet another special file open scenario.  still want to route
//  through OpenDocument to handle menus, urls, etc., but don't
//  want to actually update the document per se.  This just gets
//  added to the current doc.
//
void CSYNTHDoc::OnFileImport()
{
	m_eOpenType = IVFDOC_OPEN_IMPORT;
	theApp.OnFileOpen();
}

void CSYNTHDoc::OnUpdateFileImport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pSceneRoot != NULL);
}

BOOL CSYNTHDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	return(IvfOnOpenDocumentMessage(lpszPathName));
}

//add by me
void CSYNTHDoc::OnViewpoints() 
{
	//IvfResetToHomePosition();


}

void CSYNTHDoc::OnUpdateViewpoints(CCmdUI* pCmdUI) 
{
	IvfOnUpdateViewpoints(pCmdUI);
}

static char spv_save_suffix[] = ".iv";
static char spv_save_filter[] =
   "Synthesis Files (*.sn3)\0*.sn3\0Inventor Files (*.iv)\0*.iv\0Vrml Files (*.wrl)\0*.wrl\0BMP Files (*.bmp)\0*.bmp\0";

void CSYNTHDoc::OnFileSaveAs() 
{
	CFileDialog save_dlg(FALSE);
                        //  create the dialog

	save_dlg.m_ofn.lpstrFilter = spv_save_filter ;
	save_dlg.m_ofn.nFilterIndex = 1L;
	save_dlg.m_ofn.lpstrCustomFilter = NULL;
	save_dlg.m_ofn.lpstrDefExt = spv_save_suffix+1;
	save_dlg.m_ofn.nMaxCustFilter = 0;
    save_dlg.m_ofn.lpstrFile[0] = '\0';

	CLib0 lib ;
	lib.CStringToChar ( ((CWorldBase *)Obj[0])->c_name.getString(), save_dlg.m_ofn.lpstrFile ) ;

	save_dlg.m_ofn.Flags |= (OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT) ;


	if (save_dlg.DoModal() != IDCANCEL)
	{
		BOOL stat = FALSE;

		UndoParam = false ; //disable undo...

		// Note: Saving may change the file type, e.g. from Inventor to VRML 
		switch (save_dlg.m_ofn.nFilterIndex)
		{
			case 1: 	// .sn3 synthesis file
			IvfSetFileType(IVF_FILETYPE_IV);
			stat = OnSaveDocument(save_dlg.m_ofn.lpstrFile);
			break;

			case 2: 	// .iv file
			IvfSetFileType(IVF_FILETYPE_IV);
			stat = OnSaveDocument(save_dlg.m_ofn.lpstrFile);
			break;

			// Set filetype to Inventor in case it was VRML.
			case 3:	// .wrl file
			if (IvfGetFileType() == IVF_FILETYPE_IV)
				IvfSetFileType(IVF_FILETYPE_VRML);
			stat = OnSaveDocument(save_dlg.m_ofn.lpstrFile);
			break;
			
			//  VRML requires new header - need to set the filetype.
            //  Don't change if file was read in as VRML or VRML2.
			case 4:	// .bmp file
			{
				CSYNTHView *t_view = (CSYNTHView *)CIvfApp::IvfGetAfxView();
				stat = t_view->SaveAsBitmap(save_dlg.m_ofn.lpstrFile);
			}
			break;
			
			//  .bmp is totally different - let view handle.
		}
	}
}

BOOL CSYNTHDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	BOOL stat;
	CSYNTHView *pView = (CSYNTHView *)CIvfApp::IvfGetAfxView();

	//  pView->SendMessage(WM_COMMAND, ID_VIEW_VIEWINGMODE, 0);
	//  don't need this any more ??

	stat = CDocument::OnSaveDocument(lpszPathName);

	return(stat);
}

void CSYNTHDoc::OnFileReload() 
{
	CIvfApp *pApp = CIvfApp::IvfGetApp();

	//IvfDeleteContents(); 

	OnOpenDocument(GetPathName());
	if (pApp->IvfIsMdi()) IvfSceneGraphChanged(); 

	InventorToObjects(); //get data...

	//  an mdi app needs to treat the single
	//  frame as an SDI to reload.
}

void CSYNTHDoc::OnUpdateFileReload(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pSceneRoot != NULL);
	//pCmdUI->Enable(sview->GetSelectionNode != NULL);
}



void CSYNTHDoc::IvfSetupUrlFetchCallback(void)
{
	CIvfDocument::IvfSetupUrlFetchCallback();
}

//for undo purpose *********************
void CSYNTHDoc::SaveUndo()
{
	//first way ... write to disk
	BOOL stat = FALSE;

	IvfSetFileType(IVF_FILETYPE_IV);
	stat = OnSaveDocument("Synth_.iv");

	//second way write to memory...
	//....

	UndoParam = true;
}

void CSYNTHDoc::OnUndo() 
{
	CIvfApp *pApp = CIvfApp::IvfGetApp();

	if ( new_object )  //αυτο σημαινει οτι αν προκειται να κανουμε click για νεο αντικειμενο ακυρωνεται
    {
		if (Obj[ObjCount-1]->IsKindOf(RUNTIME_CLASS(CGExternal)))
        {
		  CGExternal  *external_obj ;

		  //delete object from inventor...ειναι το τελευταιο και αορατο
		  external_obj->DeleteObject(ObjCount-1);

		  new_object = _NONE_;

		  UpdateAllViews(NULL);
        }
		else
        if (Obj[ObjCount-1]->IsKindOf(RUNTIME_CLASS(CRoomWall)))
        {
          new_object = _NONE_; //just undo new object
        }
    }
	else //αλλιως φερε το αντιγραφο
    {
	  IvfDeleteContents();
	  OnOpenDocument("Synth_.iv");
	  if (pApp->IvfIsMdi()) IvfSceneGraphChanged();

	  InventorToObjects(); //get data...
    }

	UndoParam = false; //if undo disable it...

    SetModifiedFlag();
}

void CSYNTHDoc::OnUpdateUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(UndoParam);
}

//**************************************


//***** τις καλω απο το doc διοτι πρεπει να κανω το ModifiedFlag On
/******** delete the selected object ************/
void CSYNTHDoc::OnDelete() 
{
	// Ανοίγει το παράθυρο διαγραφής αντικειμένου
	DeleteObj *dlg = new DeleteObj ;
   
	if (dlg->DoModal() == IDOK)   
	{
      sview->OnDelete(); //call delete of view
	  SetModifiedFlag();
	  UpdateAllViews(NULL); 
	}

}

/******** extent delete of selected object ************/
void CSYNTHDoc::OnExtDelete() 
{
	// Ανοίγει το παράθυρο διαγραφής αντικειμένου
	DeleteObj *dlg = new DeleteObj ;
   
	if (dlg->DoModal() == IDOK)   
	{
      sview->OnExtDelete(); //call extented delete of view
	  SetModifiedFlag();
	  UpdateAllViews(NULL); 
	}

}

//******** Ungroup objects
void CSYNTHDoc::OnUnGroup()
{
	sview->OnUnGroup(); 
	SetModifiedFlag();
}

#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSelection.h>


#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoLight.h>
#include <Inventor/nodekits/SoWrapperKit.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/win/SoWinDirectionalLightEditor.h>
#include <Inventor/win/SoWinMaterialEditor.h>


void CSYNTHDoc::OnNewSphere() 
{
	// TODO: Add your command handler code here
	
//	if ( m_pSceneRoot == NULL )
//	{
//		SoSelection *selectionRoot = new SoSelection;
//		selectionRoot->ref() ;
//		selectionRoot->policy = SoSelection::SINGLE ;
//		selectionRoot-> addSelectionCallback(mySelectionCB) ;
//		selectionRoot-> addDeselectionCallback(myDeselectionCB) ;

		// Create the scene graph
		//m_pSceneRoot = new SoSeparator ;
		//m_pSceneRoot->ref() ;
//		selectionRoot->addChild(m_pSceneRoot) ;
//	}
/* this is Ok
	SoSeparator *root = new SoSeparator;
	SoSphere *mySphere = new SoSphere ;
	root->addChild(mySphere) ;
	IvfSetSceneGraph(root) ;		
*/
/**************** open file and light editor *********
	// Open the data file
   SoInput in;   
   char *datafile = "test02.iv";
   if (! in.openFile(datafile)) {
      AfxMessageBox("Cannot open %s for reading.");
      return;
   }

   // Read the input file
   SoNode *n;
   SoSeparator *sep = new SoSeparator; 
   root = new SoSeparator ;  //my global root 
   root->ref() ;

   while ((SoDB::read(&in, n) != FALSE) && (n != NULL))
      sep->addChild(n);

   // look if the file is a synth file
   SoSeparator *testsep ;
   testsep = (SoSeparator *)SoNode::getByName("WorldBase0");
   if (testsep==NULL)
   {   
	   AfxMessageBox("Το αρχείο δεν είναι τύπου SYNTHESIS");
	   return;
   }

   root = sep;

   // Build the material editor in its own window
   SoWinDirectionalLightEditor *myLEditor = new SoWinDirectionalLightEditor
   		(NULL,"Light Editor",TRUE);

   // Build the material editor in its own window
   SoWinMaterialEditor *myEditor = new SoWinMaterialEditor
   		(NULL,"Material Editor",FALSE);

   SoDirectionalLight *myLight = new SoDirectionalLight;
   root->addChild(myLight);
   SoMaterial *mymaterial = new SoMaterial;
   root->addChild(mymaterial);

   IvfSetSceneGraph( root );

   InventorToObjects();

   myEditor->attach(mymaterial);
   myEditor->show();

   SoPath *lightpath = new SoPath(myLight);
   myLEditor->attach(lightpath);
   myLEditor->show();

  // sview->DrawBox(0.0,550.0,1000.0,
  //                1000.0,3000.0,1000.0);

   //SetModifiedFlag();
   //UpdateAllViews(NULL);
********************************************/


   COLORREF m_OptionColorGlBack;
   CSYNTHApp *pApp = (CSYNTHApp *)AfxGetApp();
   CColorDialog dlg(m_OptionColorGlBack);
   if(dlg.DoModal()==IDOK)
   {
	   //get RGB
       /*pView->m_ClearColorRed   = (float)GetRValue(pApp->m_OptionColorGlBack) / 255.0f;
	   pView->m_ClearColorGreen = (float)GetGValue(pApp->m_OptionColorGlBack) / 255.0f;
	   pView->m_ClearColorBlue  = (float)GetBValue(pApp->m_OptionColorGlBack) / 255.0f;
*/
   }
}


void CSYNTHDoc::OnProperties() 
{
	POSITION pos ;
	CView *pView ;

	pos = GetFirstViewPosition() ;   
	if (pos != NULL) 
		pView = GetNextView(pos);

	// ΑΠΕΝΕΡΓΟΠΟΙΗΣΗ ΤΟΥ INVENTOR ΣΤΗΝ ΑΝΑΖΗΤΗΣΗΣ ΤΗΣ ΕΠΙΛΟΓΗ 
	                                          //εβγαλα το Ivf απο το GetSelectionNode για να βλεπει την m_pSelectionNode
	//SoSelection *pSel = ((CSYNTHView *)pView)->GetSelectionNode();
	//SetSelectedObj(pSel) ;

	// ΕΝΕΡΓΟΠΟΙΗΣΗ ΤΟΥ OBJ_SELECTOR
    SelId =obj_selector ;

	// Ανοίγει το παράθυρο ιδιοτήτων του επιλεγμένου αντικειμένου
	int res ;
	if (SelId < 0) return ;

//    CLib0 lib;
//    AfxMessageBox(lib.inttostr(SelId));

	if (Obj[SelId]->IsKindOf(RUNTIME_CLASS(CWorldBase)))
		res = ((CWorldBase*)Obj[SelId])->EditProperties(this,root) ;
	else
	if (Obj[SelId]->IsKindOf(RUNTIME_CLASS(CRoomBase)))
		res = ((CRoomBase*)Obj[SelId])->EditProperties(this,root) ;
	else
	if (Obj[SelId]->IsKindOf(RUNTIME_CLASS(CRoomWall)))
		res = ((CRoomWall*)Obj[SelId])->EditProperties(this,root) ;
	else
	if (Obj[SelId]->IsKindOf(RUNTIME_CLASS(CGExternal)))
		res = ((CGExternal*)Obj[SelId])->EditProperties(this,root) ;

	if (res == IDOK) 
	{
		SetModifiedFlag();
		UpdateAllViews(NULL);   
	} 	
}

void CSYNTHDoc::OnUpdateProperties(CCmdUI* pCmdUI) 
{
	// Properties is only valid if at least one object is selected
    //ASSERT( obj_selector != NULL );
    if (obj_selector >= 0)
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
}


void CSYNTHDoc::Init()
{ 
		int meter ;

        //begin....
		//make the object array
		for (meter=0 ; meter <= 100 ; meter++)
			         Obj[meter]=NULL;
		//init counters
        ObjCount  = 0; //general object counter
        ob_offset = 0; //external object counter
        
        obj_selector = -1 ;      // my selection generated number (αντικαθιστα το SelId στην επιλογή )
        BATTERING = false ;
        REPLACE = false ;
        copy_mode = false ; 
        UndoParam = false ;
        Wizard = false ;
		new_object = _NONE_ ;
}

void CSYNTHDoc::CreateBasicScene()
{
	   	CLib0	lib ;
		bool    rebuild ;

        Init();


		root = m_pSceneRoot;
    	rebuild = sview->StartScene();


		//init points
		picked_point[0] = 0;
		picked_point[1] = 0;
		picked_point[2] = 0;
		picked_normal[0] = 1; picked_normal[1] = 0; picked_normal[2] = 0;

		// setup world base 
        CWorldBase *world ;
		world->AddNewObject(picked_point, picked_normal);

		// setup the room base
        CRoomBase *rbase ;
		rbase->AddNewObject(picked_point, picked_normal);

		// setup the walls (init for first time) 
		//get base
		CRoomBase  *rb = ((CRoomBase *)sdoc->Obj[1]);   
		//get first base koryfi
		picked_point[0] = rb->Koryfsx[0];
		picked_point[1] = rb->Koryfsy[0];
		picked_point[2] = rb->Koryfsz[0];

		CRoomWall *wll;
		wll->AddNewObject(picked_point, picked_normal);



		if (!rebuild) IvfSetSceneGraph( root );

   	    SetModifiedFlag();
	    UpdateAllViews(NULL);
}


bool CSYNTHDoc::OnNewWizzard()
{
	CWizz1 *dlg = new CWizz1 ;

    Wizard = false ;
   
	if (dlg->DoModal() == IDOK)   
	{
	    //set data to arrays...
        l[0] = 5000 ;
		l[1] = 5000 ;
		l[2] = 5000 ;
		l[3] = 5000 ;
		l[4] = 0 ;
		l[5] = 0 ;
		l[6] = 0 ;
		l[7] = 0 ;

		a[0] = 90 ;
		a[1] = 90 ;
		a[2] = 90 ;
		a[3] = 90 ;
		a[4] = 0 ;
		a[5] = 0 ;
		a[6] = 0 ;
		a[7] = 0 ;

		t[0] = 1 ;
		t[1] = 1 ;
		t[2] = 0 ;
		t[3] = 0 ;
		t[4] = 0 ;
		t[5] = 0 ;
		t[6] = 0 ;
		t[7] = 0 ;
       
		//enable wizzard

		Wizard = true ;
		
    }
	return Wizard;
}

void CSYNTHDoc::OnKataxkoyzin() 
{
	// Ανοίγει το παράθυρο καταχώρησης της κουζίνας

	CWizz0 *dlg = new CWizz0 ;
   
	if (dlg->DoModal() == IDOK)   
	{
		// transfer data from the dialog to arrays
		l[0] = dlg->m_length0 ;
		l[1] = dlg->m_length1 ;
		l[2] = dlg->m_length2 ;
		l[3] = dlg->m_length3 ;
		l[4] = dlg->m_length4 ;
		l[5] = dlg->m_length5 ;
		l[6] = dlg->m_length6 ;
		l[7] = dlg->m_length7 ;

		a[0] = dlg->m_angle0 ;
		a[1] = dlg->m_angle1 ;
		a[2] = dlg->m_angle2 ;
		a[3] = dlg->m_angle3 ;
		a[4] = dlg->m_angle4 ;
		a[5] = dlg->m_angle5 ;
		a[6] = dlg->m_angle6 ;
		a[7] = dlg->m_angle7 ;

		t[0] = dlg->m_toix0 ;
		t[1] = dlg->m_toix1 ;
		t[2] = dlg->m_toix2 ;
		t[3] = dlg->m_toix3 ;
		t[4] = dlg->m_toix4 ;
		t[5] = dlg->m_toix5 ;
		t[6] = dlg->m_toix6 ;
		t[7] = dlg->m_toix7 ;

        CreateBasicScene();
	}
	
}

/*======================== SetSelectedObj ========================*/
// ΑΠΕΝΕΡΓΟΠΟΙΗΜΕΝΗ !!!
void CSYNTHDoc::SetSelectedObj ( SoSelection *sel ) 
{
//	theApp.DoMessageBox(buff,MB_OK,0) ;
	int j ;
	int x,x1 ;

	SoSeparator *path ;
	SelId = -1 ; // no current selection
	for ( int i = 0 ; i < ObjCount ; i++ )
	{
		if (Obj[i]->IsKindOf(RUNTIME_CLASS(CWorldBase)))
			path = ((CWorldBase*)Obj[i])->sep ;
		else
		if (Obj[i]->IsKindOf(RUNTIME_CLASS(CRoomBase)))
			path = ((CRoomBase*)Obj[i])->sep ;
		else
		if (Obj[i]->IsKindOf(RUNTIME_CLASS(CRoomWall)))
			path = ((CRoomWall*)Obj[i])->sep ;
		else
		if (Obj[i]->IsKindOf(RUNTIME_CLASS(CGExternal))) 
			path = ((CGExternal*)Obj[i])->sep ;
		
//***********************
// Maximum search level 3
//***********************        
		CLib0 lib;
//	    AfxMessageBox(lib.inttostr(path->getNumChildren()));

		for ( j = 0 ; j < path->getNumChildren() ; j++ )   //level 1
        {
			SoNode *mynode ;
			mynode = path->getChild(j) ;
			if (mynode->isOfType(SoGroup::getClassTypeId()))  //if separator
            {
               SoSeparator *ss ;
			   ss = (SoSeparator *) mynode ;
               //AfxMessageBox(lib.inttostr(ss->getNumChildren())) ;
               for ( x = 0 ; x < ss->getNumChildren() ; x++ )  // level 2
			   {
                   SoNode *mynode1 ;
			       mynode1 = ss->getChild(x) ;
				   if (mynode1->isOfType(SoGroup::getClassTypeId())) // if separator
				   {
                     SoSeparator *ss1 ;
			         ss1 = (SoSeparator *) mynode1 ;
					 //AfxMessageBox(lib.inttostr(ss1->getNumChildren())) ;
                     for ( x1 = 0 ; x1 < ss1->getNumChildren() ; x1++ )  // level 3
					 {
				       if (sel->isSelected(ss1->getChild(x1))) 
					   { 
				         SelId = i ;
				         goto out ;
					   }
                     }
				   }
				   else  // if other
				   {
				     if (sel->isSelected(ss->getChild(x))) 
					 { 
				        SelId = i ;
				        goto out ;
					 }
				   }	
               }
			}	
            else  //if other
            {
			  if (sel->isSelected(path->getChild(j))) 
			  {
		    		SelId = i ;
		    		goto out ;
			  }
			}  
		}
	}
out : ;
}

/********************** OpenSYNTHFile ****************************/
void CSYNTHDoc::OpenSYNTHFile()
{ 
   IvfSceneGraphChanged();
   InventorToObjects(); 

   OnFileReload(); //κανουμε reload για να βγαλει ο inventor το δευτερο eventcallback που δημιουργειται κατα το φορτωμα
}

/*===================== InventorToObjects =======================*/

void CSYNTHDoc::InventorToObjects()
{
	CWorldBase	*wb ;
	CRoomBase	*rb ;
	CRoomWall	*rw ;
	CGExternal  *ob ;
	const char	*name ;
	char		dummy[10] ;
	CLib0		lib ;

    root = m_pSceneRoot;

	ObjCount  = 0 ;
	ob_offset = 0 ;

	for ( int i = 0 ; i < root->getNumChildren() ; i++ )
	{
        CString id = lib.inttostr(i) ;

		name = root->getChild(i)->getName().getString() ;
		if (strcmp(name,"WorldBase0")==0) 
		{
			wb = new CWorldBase ;
			wb->name = "WorldBase0" ;
			wb->InventorToObject((SoSeparator *)root->getChild(i)) ;
			Obj[ObjCount] = wb ; ObjCount++ ;
		}
		else
		if (strcmp(name,"RoomBase1")==0) 
		{
			rb = new CRoomBase ;
			rb->name = "RoomBase1" ;
			rb->InventorToObject((SoSeparator *)root->getChild(i)) ;
			Obj[ObjCount] = rb ; ObjCount++ ;
		}
		else
		if (strncmp(name,"RoomWall",8)==0) 
		{
			rw = new CRoomWall ;
			sscanf(name,"%8s%d",dummy,&rw->offset) ;  // get the offset
			rw->name   = "RoomWall" + lib.inttostr(rw->offset) ;
			rw->InventorToObject((SoSeparator *)root->getChild(i)) ;
			Obj[ObjCount] = rw ; ObjCount++ ;
		}
		else
		if (strncmp(name,"GExternal",9)==0) 
		{
			ob = new CGExternal ;
			sscanf(name,"%9s%d",dummy,&ob->offset) ;  // get the offset
			ob->name   = "GExternal" + lib.inttostr(ob->offset) ;
			ob->InventorToObject((SoSeparator *)root->getChild(i)) ;
			Obj[ObjCount] = ob ; ObjCount++ ;
			ob_offset++;
			//AfxMessageBox(lib.inttostr(ob->carrier_id));==0?????????
		}
	}
}

/*============================ SelectObj ==========================*/

void CSYNTHDoc::OnSelectObj() 
{
	// Ανοίγει το παράθυρο επιλογής αντικειμένου
	CSelectObj *dlg = new CSelectObj ;
   
	if (dlg->DoModal() == IDOK)   
	{
       //τοποθετειται το αντεικιμενο αορατο στην θεση 0,0,0
	}
	
}


void CSYNTHDoc::OnUpdateSelectObj(CCmdUI* pCmdUI)
{
//  CSelect Object is only valid if a scene has created
    if ( root != NULL )
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE ); 
}


/*============================ ReplaceObj ==========================*/

void CSYNTHDoc::OnReplaceObj() 
{
    //check selection
	if (Obj[obj_selector]->IsKindOf(RUNTIME_CLASS(CGExternal)))
    {
      //enable the replace
	  REPLACE = true ;
	  //disable the battering ...
	  BATTERING = false ;

	  // Ανοίγει το παράθυρο επιλογής αντικειμένου
	  CSelectObj *dlg = new CSelectObj ;
   
	  if (dlg->DoModal() == IDOK)   
	  {
        //disable the replace
		REPLACE = false ;
	  } 
    }
	else
	  AfxMessageBox("Invalid selection. Access denied.");	  
}

void CSYNTHDoc::OnUpdateReplaceObj(CCmdUI* pCmdUI)
{
//  replace Object is only valid if a scene has created
	if (( root != NULL ) && (obj_selector>0))
    {
		if (Obj[obj_selector]->IsKindOf(RUNTIME_CLASS(CGExternal)))
        {
          pCmdUI->Enable( TRUE );	
        }
		else
          pCmdUI->Enable( FALSE );
    }
    else
        pCmdUI->Enable( FALSE );
}




void CSYNTHDoc::OnAddwall() 
{
	// TODO: Add your command handler code here

	CWizz0 *dlg = new CWizz0 ;
   
    SbVec3f test;

	if (dlg->DoModal() == IDOK)   
	{
		SaveUndo(); //save scene for undo...

		// transfer data from the dialog to arrays
		l[0] = dlg->m_length0 ;
		l[1] = dlg->m_length1 ;
		l[2] = dlg->m_length2 ;
		l[3] = dlg->m_length3 ;
		l[4] = dlg->m_length4 ;
		l[5] = dlg->m_length5 ;
		l[6] = dlg->m_length6 ;
		l[7] = dlg->m_length7 ;

		a[0] = dlg->m_angle0 ;
		a[1] = dlg->m_angle1 ;
		a[2] = dlg->m_angle2 ;
		a[3] = dlg->m_angle3 ;
		a[4] = dlg->m_angle4 ;
		a[5] = dlg->m_angle5 ;
		a[6] = dlg->m_angle6 ;
		a[7] = dlg->m_angle7 ;

		t[0] = dlg->m_toix0 ;
		t[1] = dlg->m_toix1 ;
		t[2] = dlg->m_toix2 ;
		t[3] = dlg->m_toix3 ;
		t[4] = dlg->m_toix4 ;
		t[5] = dlg->m_toix5 ;
		t[6] = dlg->m_toix6 ;
		t[7] = dlg->m_toix7 ;


		new_object = _ROOMWALL_ ;   
			
	}	
}

void CSYNTHDoc::OnUpdateAddwall(CCmdUI* pCmdUI) 
{

	//  Add wall only if a scene has created
    if ( root != NULL )
        pCmdUI->Enable( TRUE );	
    else
        pCmdUI->Enable( FALSE );
	
}

void CSYNTHDoc::OnJump() 
{
	if (Obj[obj_selector]->IsKindOf(RUNTIME_CLASS(CGExternal)))
    {
      SaveUndo(); //save scene for undo...
	  new_object = _EXTERNAL_;  	//just say new object = external
    }
    else
      AfxMessageBox("No valid selection.");

	
}

void CSYNTHDoc::OnUpdateJump(CCmdUI* pCmdUI) 
{
    if (( root != NULL ) && (obj_selector>0))
    {
		if (Obj[obj_selector]->IsKindOf(RUNTIME_CLASS(CGExternal)))
        {
          pCmdUI->Enable( TRUE );	
        }
		else
          pCmdUI->Enable( FALSE );
    }
    else
        pCmdUI->Enable( FALSE );
	
}


/////////////////////////////////////////////////////////////////////////////
// TreeView section overwrite

void CSYNTHDoc::IvfSceneGraphChanged()
{
    CIvfDocument::IvfSceneGraphChanged();

    POSITION pos;
    SoSelection *pSelNode = NULL;

    // Find the Inventor (IVF) view and get its selection node
    pos = GetFirstViewPosition();
    CSYNTHView *pSYNTHView;
    while (pSYNTHView = (CSYNTHView*)GetNextView(pos)) {
        if (pSYNTHView->IsKindOf(RUNTIME_CLASS(CSYNTHView))) {
            pSelNode = pSYNTHView->GetSelectionNode();
            break;
        }
    }

    // Find the tree view and tell it which nodes to watch
    pos = GetFirstViewPosition();
    CIvfTreeView *pTreeView;
    while (pTreeView = (CIvfTreeView*)GetNextView(pos)) {
        if (pTreeView->IsKindOf(RUNTIME_CLASS(CIvfTreeView))) {
            pTreeView->SetRootNode( IvfGetDocSceneGraph() );
            pTreeView->SetSelectionNode( pSelNode );
            break;
        }
    }
}


