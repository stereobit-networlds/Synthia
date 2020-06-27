// SelectObj.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTHDoc.h"
#include "SYNTHView.h"
#include "SYNTH.h"
#include "SelectObj.h"
#include "LObj2.h"
#include "Lib0.h"
#include "GLib0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSelection.h>


CSelectObj::CSelectObj(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectObj::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectObj)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CSelectObj::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectObj)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectObj, CDialog)
	//{{AFX_MSG_MAP(CSelectObj)
	ON_CBN_SELCHANGE(SYNTH_CB_MONTELO, OnSelchangeCbMontelo)
	ON_BN_CLICKED(SYNTH_NEXT, OnNext)
	ON_BN_CLICKED(SYNTH_PRIOR, OnPrior)
	ON_CBN_SELCHANGE(SYNTH_CB_ANTIK, OnSelchangeCbAntik)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//============================= OnInitDialog ===============================

BOOL CSelectObj::OnInitDialog()
{
	CDialog::OnInitDialog();

	view = new CIvfExaminerViewer ;
	static int cArgs[]= { 
		FALSE,		// Decoration
		FALSE,	    // URL Display
		FALSE,		// Viewpoints
		FALSE};		// URL Fetch

	CWnd *pWnd = GetDlgItem(IDC_VIEWER) ;
	view->IvfCreateComponent(pWnd,(void *)cArgs) ;

	SoSeparator *root = new SoSeparator ;
	root->ref() ;
	view->IvfSetSceneGraph( root ) ;
	view->IvfViewAll() ;

	// get the combo boxes
	montelo		= (CComboBox *)GetDlgItem(SYNTH_CB_MONTELO) ;
	yliko		= (CComboBox *)GetDlgItem(SYNTH_CB_YLIKO) ;
	portaki		= (CComboBox *)GetDlgItem(SYNTH_CB_PORTAKI) ;
	syrtari		= (CComboBox *)GetDlgItem(SYNTH_CB_SYRTARI) ;
	xeroyl		= (CComboBox *)GetDlgItem(SYNTH_CB_XEROYL) ;
	mpaza		= (CComboBox *)GetDlgItem(SYNTH_CB_MPAZA) ;
	antik		= (CComboBox *)GetDlgItem(SYNTH_CB_ANTIK) ;

	rs_eidh0= theApp.rs_eidh0 ;
	rs_omad	= theApp.rs_omad ;
	rs_mrec	= theApp.rs_mrec ;

	// load "montelo"
	COleVariant var ;
    rs_omad->MoveFirst() ;
    while (!rs_omad->IsEOF())
	{
		var = rs_omad->GetFieldValue("OMAD_D") ;
		montelo->AddString(V_BSTRT(&var)) ;

		rs_omad->MoveNext() ;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

/*======================== OnSelchangeCbMontelo ===================*/

void CSelectObj::OnSelchangeCbMontelo() 
{
	COleVariant var, mont_id, fomad, fmrec ;
	CString mont ;

	yliko->Clear() ;
	portaki->Clear() ;
	syrtari->Clear() ;
	xeroyl->Clear() ;
	mpaza->Clear() ;
	antik->Clear() ;
	
	montelo->GetLBText(montelo->GetCurSel(),mont) ;
	rs_omad->SetCurrentIndex("OMAD_D") ;
	if (rs_omad->Seek("=",&COleVariant(mont,VT_BSTRT)))
		mont_id = rs_omad->GetFieldValue("OMAD") ;
	else 
		return ;

	// load "yliko"
    rs_eidh0->MoveFirst() ;
    while (!rs_eidh0->IsEOF())
	{
		fmrec	= rs_eidh0->GetFieldValue("_MREC") ; 
		fomad	= rs_eidh0->GetFieldValue("OMAD") ; 

		if ((fomad.dblVal == mont_id.dblVal) && (fmrec.dblVal == 3))
		{
			var = rs_eidh0->GetFieldValue("EIDH0_D") ;
			yliko->AddString(V_BSTRT(&var)) ;
		}
		rs_eidh0->MoveNext() ;
	}

	// load "portaki"
    rs_eidh0->MoveFirst() ;
    while (!rs_eidh0->IsEOF())
	{
		fmrec	= rs_eidh0->GetFieldValue("_MREC") ; 
		fomad	= rs_eidh0->GetFieldValue("OMAD") ; 

		if ((fomad.dblVal == mont_id.dblVal) && (fmrec.dblVal == 2))
		{
			var = rs_eidh0->GetFieldValue("EIDH0_D") ;
			portaki->AddString(V_BSTRT(&var)) ;
		}
		rs_eidh0->MoveNext() ;
	}

	// load "syrtari"
    rs_eidh0->MoveFirst() ;
    while (!rs_eidh0->IsEOF())
	{
		fmrec	= rs_eidh0->GetFieldValue("_MREC") ; 
		fomad	= rs_eidh0->GetFieldValue("OMAD") ; 

		if ((fomad.dblVal == mont_id.dblVal) && (fmrec.dblVal == 4))
		{
			var = rs_eidh0->GetFieldValue("EIDH0_D") ;
			syrtari->AddString(V_BSTRT(&var)) ;
		}
		rs_eidh0->MoveNext() ;
	}

	// load "xeroyl"
    rs_eidh0->MoveFirst() ;
    while (!rs_eidh0->IsEOF())
	{
		fmrec	= rs_eidh0->GetFieldValue("_MREC") ; 
		fomad	= rs_eidh0->GetFieldValue("OMAD") ; 

		if ((fomad.dblVal == mont_id.dblVal) && (fmrec.dblVal == 5))
		{
			var = rs_eidh0->GetFieldValue("EIDH0_D") ;
			xeroyl->AddString(V_BSTRT(&var)) ;
		}
		rs_eidh0->MoveNext() ;
	}

	// load "mpaza"
    rs_eidh0->MoveFirst() ;
    while (!rs_eidh0->IsEOF())
	{
		fmrec	= rs_eidh0->GetFieldValue("_MREC") ; 
		fomad	= rs_eidh0->GetFieldValue("OMAD") ; 

		if ((fomad.dblVal == mont_id.dblVal) && (fmrec.dblVal == 6))
		{
			var = rs_eidh0->GetFieldValue("EIDH0_D") ;
			mpaza->AddString(V_BSTRT(&var)) ;
		}
		rs_eidh0->MoveNext() ;
	}

	// load "antik"
    rs_eidh0->MoveFirst() ;
    while (!rs_eidh0->IsEOF())
	{
		fmrec	= rs_eidh0->GetFieldValue("_MREC") ; 
		fomad	= rs_eidh0->GetFieldValue("OMAD") ; 

		if ((fomad.dblVal == mont_id.dblVal) && 
			((fmrec.dblVal == 1) || (fmrec.dblVal == 7)))
		{
			var = rs_eidh0->GetFieldValue("EIDH0_C") ;
			antik->AddString(V_BSTRT(&var)) ;
		}
		rs_eidh0->MoveNext() ;
	}
}

//=========================== OnNext ========================

void CSelectObj::OnNext() 
{
	antik->SetCurSel(antik->GetCurSel()+1) ;	
	Draw() ;
}

//=========================== OnPrior =========================

void CSelectObj::OnPrior() 
{
	antik->SetCurSel(antik->GetCurSel()-1) ;		
	Draw() ;
}

//========================== OnSelchangeCbAntik ================

void CSelectObj::OnSelchangeCbAntik() 
{
	// display the object on the Examiner Viewer
	Draw() ;
}

/*============================ Get_eidh_id =======================*/

BOOL CSelectObj::Get_eidh_id()
{
	COleVariant mont_id ;
	CString buf, buf1 ;
	CLib0 lib ;

//	for ( int i = 0 ; i < 10 ; i++ )
//		eid_id[i] = 0 ;

    // load MONDELO
	montelo->GetLBText(montelo->GetCurSel(),buf1) ;
	rs_omad->SetCurrentIndex("OMAD_D") ;
	if (rs_omad->Seek("=",&COleVariant(buf1,VT_BSTRT)))
		mont_id = rs_omad->GetFieldValue("OMAD") ;
	else
		return FALSE ;	

     // load ANTIKEIMENO
	antik->GetLBText(antik->GetCurSel(),buf1) ;
    if (buf1 == "") return FALSE ;
	rs_eidh0->SetCurrentIndex("OEIDH0_C") ;
    if (rs_eidh0->Seek("=",&mont_id,&COleVariant(buf1,VT_BSTRT))) 
	{
		eid_id[0]= rs_eidh0->GetFieldValue("EIDH0") ;
		mrec_id	 = rs_eidh0->GetFieldValue("_MREC") ;
	}
	else
		return FALSE ;

     // load PORTAKIA
	portaki->GetLBText(portaki->GetCurSel(),buf1) ;
	rs_eidh0->SetCurrentIndex("OEIDH0_D") ;
    if (rs_eidh0->Seek("=",&mont_id,&COleVariant(buf1,VT_BSTRT))) 
		eid_id[1] = rs_eidh0->GetFieldValue("EIDH0") ;

    // load SYRTARIA
	syrtari->GetLBText(syrtari->GetCurSel(),buf1) ;
	rs_eidh0->SetCurrentIndex("OEIDH0_D") ;
    if (rs_eidh0->Seek("=",&mont_id,&COleVariant(buf1,VT_BSTRT))) 
		eid_id[2] = rs_eidh0->GetFieldValue("EIDH0") ;

    // load YLIKO
	yliko->GetLBText(yliko->GetCurSel(),buf1) ;
	rs_eidh0->SetCurrentIndex("OEIDH0_D") ;
    if (rs_eidh0->Seek("=",&mont_id,&COleVariant(buf1,VT_BSTRT))) 
		eid_id[3] = rs_eidh0->GetFieldValue("EIDH0") ;

    // load MPAZA
    mpaza->GetLBText(mpaza->GetCurSel(),buf1) ;
	rs_eidh0->SetCurrentIndex("OEIDH0_D") ;
    if (rs_eidh0->Seek("=",&mont_id,&COleVariant(buf1,VT_BSTRT))) 
		eid_id[4] = rs_eidh0->GetFieldValue("EIDH0") ;

	return TRUE ;
}

void CSelectObj::OnOK() 
{
	LObj2 obj2 ;
	CLib0 lib ;
	CString eidh0_c ;

	Get_eidh_id() ;

	antik->GetLBText(antik->GetCurSel(),eidh0_c) ;
	rs_eidh0->SetCurrentIndex("EIDH0_C") ;
	if (rs_eidh0->Seek("=",&COleVariant(eidh0_c,VT_BSTRT)))
	{
		rs_mrec->SetCurrentIndex("_MREC") ;
		if (rs_mrec->Seek("=",&rs_eidh0->GetFieldValue("_MREC"))) 
		{
			sdoc->SaveUndo(); //save scene for undo...
			sdoc->new_object = _EXTERNAL_ ;
			obj2.CreateObject( TRUE, sdoc->root, eid_id, rs_eidh0, rs_mrec ) ;
//			SoSelection *sel = sview->IvfGetSelectionNode() ;
//			sel->select(sdoc->root->getChild(sdoc->root->getNumChildren()-1)) ;
		}
	}

	CDialog::OnOK() ;
}

/*============================ Draw ===========================*/

void CSelectObj::Draw()
{
	LObj2 obj2 ;
	CLib0 lib ;
	CString eidh0_c ;
	SoSeparator *root = (SoSeparator *)view->IvfGetSceneGraph() ;
	root->removeAllChildren() ;

	if (!Get_eidh_id()) AfxMessageBox("get_eidh_id error") ;

	antik->GetLBText(antik->GetCurSel(),eidh0_c) ;
	rs_eidh0->SetCurrentIndex("EIDH0_C") ;
	if (rs_eidh0->Seek("=",&COleVariant(eidh0_c,VT_BSTRT)))
	{
		rs_mrec->SetCurrentIndex("_MREC") ;
		if (rs_mrec->Seek("=",&rs_eidh0->GetFieldValue("_MREC"))) 
		{
			obj2.CreateObject( FALSE, root, eid_id, rs_eidh0, rs_mrec ) ;
			view->IvfViewAll() ;
		}
		else
			AfxMessageBox("seek mrec error") ;
	}
	else
		AfxMessageBox("seek eidh0 error") ;
}
