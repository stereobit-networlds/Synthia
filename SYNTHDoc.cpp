// SYNTHDoc.cpp : implementation of the CSYNTHDoc class
//

#include "stdafx.h"
#include "SYNTH.h"

#include "Resource.h"

#include "SYNTHDoc.h"
#include "SYNTHView.h"
#include "IvfTreeView.h"

#include "Wizz0.h"
#include "lib0.h"
#include "RoomBase.h"
#include "RoomWall.h"
#include "WorldBase.h"
#include "GExternal.h"
#include "SelectObj.h"

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
	ON_UPDATE_COMMAND_UI(IDM_VIEWPOINTS, OnUpdateViewpoints)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_RELOAD, OnFileReload)
	ON_UPDATE_COMMAND_UI(ID_FILE_RELOAD, OnUpdateFileReload)
	ON_COMMAND(SYNTH_NEW_SPHERE, OnNewSphere)
	ON_COMMAND(SYNTH_PROPERTIES, OnProperties)
	ON_COMMAND(SYNTH_KATAXKOYZIN, OnKataxkoyzin)
	ON_COMMAND(SYNTH_SELECT, OnSelectObj)
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

  new_object = FALSE ;  
  ob_offset = 0; //external object counte+

}

CSYNTHDoc::~CSYNTHDoc()
{
	//root->unref(); //destroy scene    δεν χρειάζεται !!!!
}

BOOL CSYNTHDoc::OnNewDocument()
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

void CSYNTHDoc::OnUpdateViewpoints(CCmdUI* pCmdUI) 
{
	IvfOnUpdateViewpoints(pCmdUI);
}

static char spv_save_suffix[] = ".iv";
static char spv_save_filter[] =
   "Inventor Files (*.iv)\0*.iv\0Vrml Files (*.wrl)\0*.wrl\0BMP Files (*.bmp)\0*.bmp\0";

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

		// Note: Saving may change the file type, e.g. from Inventor to VRML 
		switch (save_dlg.m_ofn.nFilterIndex)
		{
			case 1: 	// .iv file
			IvfSetFileType(IVF_FILETYPE_IV);
			stat = OnSaveDocument(save_dlg.m_ofn.lpstrFile);
			break;

			// Set filetype to Inventor in case it was VRML.
			case 2:	// .wrl file
			if (IvfGetFileType() == IVF_FILETYPE_IV)
				IvfSetFileType(IVF_FILETYPE_VRML);
			stat = OnSaveDocument(save_dlg.m_ofn.lpstrFile);
			break;
			
			//  VRML requires new header - need to set the filetype.
            //  Don't change if file was read in as VRML or VRML2.
			case 3:	// .bmp file
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

	IvfDeleteContents();
	OnOpenDocument(GetPathName());
	if (pApp->IvfIsMdi()) IvfSceneGraphChanged();
	//  an mdi app needs to treat the single
	//  frame as an SDI to reload.
}

void CSYNTHDoc::OnUpdateFileReload(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pSceneRoot != NULL);
}



void CSYNTHDoc::IvfSetupUrlFetchCallback(void)
{
	CIvfDocument::IvfSetupUrlFetchCallback();
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
	SoSeparator *mroot = new SoSeparator;
	SoSphere *mySphere = new SoSphere ;
	mroot->addChild(mySphere) ;
	IvfSetSceneGraph(mroot) ;		
*/
   
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
   testsep = (SoSeparator *)SoNode::getByName("WorldBase");
   if (testsep==NULL)
   {   
	   AfxMessageBox("Το αρχείο δεν είναι τύπου SYNTHESIS");
	   return;
   }

   root = sep;
   IvfSetSceneGraph( root );
   InventorToObjects();

   //SetModifiedFlag();
   UpdateAllViews(NULL);
}


void CSYNTHDoc::OnProperties() 
{
	POSITION pos ;
	CView *pView ;

	pos = GetFirstViewPosition() ;   
	if (pos != NULL) 
		pView = GetNextView(pos);        //εβγαλα το Ivf απο το GetSelectionNode για να βλεπει την m_pSelectionNode
	SoSelection *pSel = ((CSYNTHView *)pView)->GetSelectionNode();
	SetSelectedObj(pSel) ;

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

//	if (res == IDOK) 
//	{
		SetModifiedFlag();
		UpdateAllViews(NULL);   
//	} 	
}

void CSYNTHDoc::OnKataxkoyzin() 
{
	// Ανοίγει το παράθυρο καταχώρησης της κουζίνας

	CWizz0 *dlg = new CWizz0 ;
   
	if (dlg->DoModal() == IDOK)   
	{

		// setup ΚΑΤΑΧΩΡΗΣΗ ΚΟΥΖΙΝΑΣ

		float	x, y, z, x0, y0, z0,
				x00, y00, z00, vx, vy, vz, sx, sy, sz,
				xmax, xmin, zmax, zmin, len1 ;
		float	xx[20], yy[20], zz[20] ;
		float	len[20], angle[20] ;
		int		toix[20] ;
		int		pleyres ;
		CLib0	lib ;

		// transfer data from the dialog
		len[0] = dlg->m_length0 ;
		len[1] = dlg->m_length1 ;
		len[2] = dlg->m_length2 ;
		len[3] = dlg->m_length3 ;
		len[4] = dlg->m_length4 ;
		len[5] = dlg->m_length5 ;
		len[6] = dlg->m_length6 ;
		len[7] = dlg->m_length7 ;

		angle[0] = dlg->m_angle0 ;
		angle[1] = dlg->m_angle1 ;
		angle[2] = dlg->m_angle2 ;
		angle[3] = dlg->m_angle3 ;
		angle[4] = dlg->m_angle4 ;
		angle[5] = dlg->m_angle5 ;
		angle[6] = dlg->m_angle6 ;
		angle[7] = dlg->m_angle7 ;

		toix[0] = dlg->m_toix0 ;
		toix[1] = dlg->m_toix1 ;
		toix[2] = dlg->m_toix2 ;
		toix[3] = dlg->m_toix3 ;
		toix[4] = dlg->m_toix4 ;
		toix[5] = dlg->m_toix5 ;
		toix[6] = dlg->m_toix6 ;
		toix[7] = dlg->m_toix7 ;

		// calculate pleyres
		for ( int i = 0 ; i <= 7 ; i++ )
			if (len[i] == 0) break ;
		pleyres = i + 1 ;

        xmax = xmin = zmax = zmin = 0 ;
		for ( i = 0 ; i < pleyres ; i++)
		{
			if (i == 0)
			{
			    x0 = 0 ;
				y0 = 0 ;
				z0 = 0 ;
				x = 0 ;
				y = 0 ;
				z = len[i] ;
			}
			else 
			{
				CGLib0 *glib = new CGLib0 ;
				glib->GetPolyNormal( x0, y0, z0, x00, y00, z00, x0, y0+1, z0, &vx, &vy, &vz ) ;
				len1 = int(cos((180-angle[i]) * 3.1415926 /180) * len[i]) ;
				sx  = (x0-x00) * (len1+len[i-1]) / len[i-1] + x00 ;
				sy  = (y0-y00) * (len1+len[i-1]) / len[i-1] + y00 ;
				sz  = (z0-z00) * (len1+len[i-1]) / len[i-1] + z00 ;
				glib->GetPolyDistandPoint ( vx, vy, vz, sx, sy, sz, sin((180-angle[i])*3.1415926/180)*len[i],
											&x, &y, &z ) ;
			}

			x00 = x0 ;
			y00 = y0 ;
			z00 = z0 ;
			x0 = x ;
			y0 = y ;
			z0 = z ;

			if (xmax < x) xmax = x ;
			if (zmax < z) zmax = z ;
			if (xmin > x) xmin = x ;
			if (zmin > z) zmin = z ;

			// set room base coordinates
			xx[i] = x0 ; yy[i] = y0 ; zz[i] = z0 ;
		} // for i

		root = new SoSeparator ;
		root->ref() ;
		

		// setup world base 
		CWorldBase *wb = new CWorldBase ;
		ObjCount = 0 ;
		SelId	 = 0 ;
		Obj[ObjCount] = wb ; ObjCount++ ;
		wb->name    = "WorldBase" ;
		wb->width	= xmax-xmin + 2000 ;
		wb->depth	= zmax-zmin + 2000 ;
		wb->height	= 100 ;
		wb->c_name  = "ΠΑΥΛΙΔΗΣ ΡΑΦΑΗΛ" ;
		wb->ObjectToInventor ( root ) ;

		// setup the room base
		CRoomBase *rb = new CRoomBase ;
		Obj[ObjCount] = rb ; ObjCount++ ;
		rb->name   = "RoomBase" ;
		rb->height = 5 ;
		rb->KoryfCount = pleyres ;
		for ( i = 0 ; i < pleyres ; i++ )
		{
			rb->Koryfsx[i]	= xx[i] - wb->width/2 + 1000 ;
			rb->Koryfsy[i]	= wb->height ;
			rb->Koryfsz[i]	= zz[i] - wb->depth/2 + 1000 ;
		}

		rb->ObjectToInventor(root) ;

		// setup the walls
    	CRoomWall *rw[10] ;

		int off = 0 ;
		for ( i = 0 ; i < pleyres ; i++ )
		{
			if (toix[i] == 0) continue ;
			rw[off] = new CRoomWall ;
			Obj[ObjCount] = rw[off] ; ObjCount++ ;
			rw[off]->name   = "RoomWall" + lib.inttostr(off) ;
			rw[off]->offset = off ;
			rw[off]->depth	= 3 ;
			rw[off]->height	= 3000 ;
			rw[off]->Koryfsx[0] = rb->Koryfsx[i] ;
			rw[off]->Koryfsy[0] = rb->Koryfsy[i] ;
			rw[off]->Koryfsz[0] = rb->Koryfsz[i] ;
			if (i > 0)
			{
				rw[off]->Koryfsx[1] = rb->Koryfsx[i-1] ;
				rw[off]->Koryfsy[1] = rb->Koryfsy[i-1] ;
				rw[off]->Koryfsz[1] = rb->Koryfsz[i-1] ;
			}
			else          
			{
				rw[off]->Koryfsx[1] = rb->Koryfsx[pleyres-1] ;
				rw[off]->Koryfsy[1] = rb->Koryfsy[pleyres-1] ;
				rw[off]->Koryfsz[1] = rb->Koryfsz[pleyres-1] ;
			}
			rw[off]->ObjectToInventor ( root ) ;
			off++ ;
		}

        
		IvfSetSceneGraph( root );

   		SetModifiedFlag();
		UpdateAllViews(NULL);   
	} 
}

/*======================== SetSelectedObj ========================*/

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
  CLib0 lib;
  //char *file;

   	// Open the data file
   SoInput in;   
   //lib.CStringToChar(myFile,file);
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
   testsep = (SoSeparator *)SoNode::getByName("WorldBase");
   if (testsep==NULL)
   {   
	   AfxMessageBox("Το αρχείο δεν είναι τύπου SYNTHESIS");
	   return;
   }

   root = sep;
   IvfSetSceneGraph( root );
   InventorToObjects();

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

//	IvfSetSceneGraph(m_pSceneRoot);
//	root = m_pSceneRoot; 


	ObjCount  = 0 ;
	ob_offset = 0 ;

	for ( int i = 0 ; i < root->getNumChildren() ; i++ )
	{
		name = root->getChild(i)->getName().getString() ;
		if (strcmp(name,"WorldBase")==0) 
		{
			wb = new CWorldBase ;
			wb->name = "WorldBase" ;
			wb->InventorToObject((SoSeparator *)root->getChild(i)) ;
			Obj[ObjCount] = wb ; ObjCount++ ;
		}
		else
		if (strcmp(name,"RoomBase")==0) 
		{
			rb = new CRoomBase ;
			rb->name = "RoomBase" ;
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
			ob_offset = ob->offset + 1 ;
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

	}
	
}


/////////////////////////////////////////////////////////////////////////////
// TreeView section

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



