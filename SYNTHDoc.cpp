// SYNTHDoc.cpp : implementation of the CSYNTHDoc class
//

#include "stdafx.h"
#include "SYNTH.h"

#include "Resource.h"

#include "SYNTHDoc.h"
#include "SYNTHView.h"
#include "IvfTreeView.h"

#include "lib0.h"
#include "Wizz1.h"
#include "RoomBase.h"
#include "RoomWall.h"
#include "WorldBase.h"
#include "GExternal.h"


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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSYNTHDoc	*sdoc ;

CSYNTHDoc::CSYNTHDoc()
{
	// TODO: add one-time construction code here

// BEGIN_IVWGEN
	m_bContainsCamera = FALSE;
	m_eOpenType = IVFDOC_OPEN_NORMAL;
// END_IVWGEN

  //init graph
  root = NULL;

  //init counters
  ObjCount  = 0; //general object counter
  ob_offset = 0; //external object counter
        
  obj_selector = -1 ;      
  BATTERY = false ;
  REPLACE = false ;
  copy_mode = false ; 
  UndoParam = false ;
  Wizard = false ;
  new_object = _NONE_ ;

  //make the object array
  for (int meter=0 ; meter <= 100 ; meter++)
  {
     Obj[meter]=NULL;
  }
}

CSYNTHDoc::~CSYNTHDoc()
{
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

	//in case of synthesis get worldbase->name
	//CLib0 lib ;
	//lib.CStringToChar ( ((CWorldBase *)Obj[0])->c_name.getString(), save_dlg.m_ofn.lpstrFile ) ;

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

	IvfDeleteContents(); 
	OnOpenDocument(GetPathName());
	if (pApp->IvfIsMdi()) IvfSceneGraphChanged(); 
	//  an mdi app needs to treat the single
	//  frame as an SDI to reload.

	//InventorToObjects(); //get data...
}

void CSYNTHDoc::OnUpdateFileReload(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pSceneRoot != NULL);
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


//open the scene selecct wizard...
bool CSYNTHDoc::OnNewWizzard()
{
	CWizz1 *dlg = new CWizz1 ;

    Wizard = false ; //init wizard
   
	if (dlg->DoModal() == IDOK)   
	{
		//enable wizzard
		Wizard = true ;		
    }
	return Wizard;
}



/********************** OpenSceneFile ****************************/
void CSYNTHDoc::OpenSceneFile(int filetype)
{ 
   root = m_pSceneRoot;
   IvfSceneGraphChanged();

   switch (filetype)
   {
     case 1 : InventorToObjects(); break; //SYNTH file (*.sn3)
	 case 2 : break; //inventor file (*.iv) 
	 case 3 : break; //vrml file  (*.wrl)
   }

   //OnFileReload(); 
   //κανουμε reload για να βγαλει ο inventor το δευτερο eventcallback που δημιουργειται κατα το φορτωμα????
}

/*===================== InventorToObjects =======================*/

void CSYNTHDoc::InventorToObjects()
{
/*	CWorldBase	*wb ;
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
	}*/
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


