// Wizz1.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"
#include "Wizz1.h"
#include "SYNTHDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWizz1 dialog


CWizz1::CWizz1(CWnd* pParent /*=NULL*/)
	: CDialog(CWizz1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWizz1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWizz1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizz1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizz1, CDialog)
	//{{AFX_MSG_MAP(CWizz1)
	ON_BN_CLICKED(IDC_SCENE01, OnScene01)
	ON_BN_CLICKED(IDC_SCENE02, OnScene02)
	ON_BN_CLICKED(IDC_SCENE03, OnScene03)
	ON_BN_CLICKED(IDC_SCENE04, OnScene04)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWizz1 message handlers



void CWizz1::OnScene01() 
{
	// TODO: Add your control notification handler code here

	//set data to pseudo arrays...
        wizlen[0] = 5000 ;
		wizlen[1] = 5000 ;
		wizlen[2] = 5000 ;
		wizlen[3] = 5000 ;
		wizlen[4] = 0 ;
		wizlen[5] = 0 ;
		wizlen[6] = 0 ;
		wizlen[7] = 0 ;

		wizang[0] = 90 ;
		wizang[1] = 90 ;
		wizang[2] = 90 ;
		wizang[3] = 90 ;
		wizang[4] = 0 ;
		wizang[5] = 0 ;
		wizang[6] = 0 ;
		wizang[7] = 0 ;

		wizw[0] = 1 ;
		wizw[1] = 1 ;
		wizw[2] = 0 ;
		wizw[3] = 0 ;
		wizw[4] = 0 ;
		wizw[5] = 0 ;
		wizw[6] = 0 ;
		wizw[7] = 0 ;
}

void CWizz1::OnScene02() 
{
	// TODO: Add your control notification handler code here

	//set data to pseudo arrays...
        wizlen[0] = 5000 ;
		wizlen[1] = 5000 ;
		wizlen[2] = 5000 ;
		wizlen[3] = 5000 ;
		wizlen[4] = 0 ;
		wizlen[5] = 0 ;
		wizlen[6] = 0 ;
		wizlen[7] = 0 ;

		wizang[0] = 90 ;
		wizang[1] = 90 ;
		wizang[2] = 90 ;
		wizang[3] = 90 ;
		wizang[4] = 0 ;
		wizang[5] = 0 ;
		wizang[6] = 0 ;
		wizang[7] = 0 ;

		wizw[0] = 1 ;
		wizw[1] = 1 ;
		wizw[2] = 0 ;
		wizw[3] = 0 ;
		wizw[4] = 0 ;
		wizw[5] = 0 ;
		wizw[6] = 0 ;
		wizw[7] = 0 ;
}

void CWizz1::OnScene03() 
{
	// TODO: Add your control notification handler code here

	//set data to pseudo arrays...
        wizlen[0] = 5000 ;
		wizlen[1] = 5000 ;
		wizlen[2] = 5000 ;
		wizlen[3] = 5000 ;
		wizlen[4] = 0 ;
		wizlen[5] = 0 ;
		wizlen[6] = 0 ;
		wizlen[7] = 0 ;

		wizang[0] = 90 ;
		wizang[1] = 90 ;
		wizang[2] = 90 ;
		wizang[3] = 90 ;
		wizang[4] = 0 ;
		wizang[5] = 0 ;
		wizang[6] = 0 ;
		wizang[7] = 0 ;

		wizw[0] = 1 ;
		wizw[1] = 1 ;
		wizw[2] = 0 ;
		wizw[3] = 0 ;
		wizw[4] = 0 ;
		wizw[5] = 0 ;
		wizw[6] = 0 ;
		wizw[7] = 0 ;
}

void CWizz1::OnScene04() 
{
	// TODO: Add your control notification handler code here
	
	//set data to pseudo arrays...
        wizlen[0] = 5000 ;
		wizlen[1] = 5000 ;
		wizlen[2] = 5000 ;
		wizlen[3] = 5000 ;
		wizlen[4] = 0 ;
		wizlen[5] = 0 ;
		wizlen[6] = 0 ;
		wizlen[7] = 0 ;

		wizang[0] = 90 ;
		wizang[1] = 90 ;
		wizang[2] = 90 ;
		wizang[3] = 90 ;
		wizang[4] = 0 ;
		wizang[5] = 0 ;
		wizang[6] = 0 ;
		wizang[7] = 0 ;

		wizw[0] = 1 ;
		wizw[1] = 1 ;
		wizw[2] = 0 ;
		wizw[3] = 0 ;
		wizw[4] = 0 ;
		wizw[5] = 0 ;
		wizw[6] = 0 ;
		wizw[7] = 0 ;
}



void CWizz1::OnOK() 
{
	// TODO: Add extra validation here

	//set data to real arrays...
        theApp.l[0] = wizlen[0];
		theApp.l[1] = wizlen[1];
		theApp.l[2] = wizlen[2];
		theApp.l[3] = wizlen[3];
		theApp.l[4] = wizlen[4];
		theApp.l[5] = wizlen[5];
		theApp.l[6] = wizlen[6];
		theApp.l[7] = wizlen[7];

		theApp.a[0] = wizang[0];
		theApp.a[1] = wizang[1];
		theApp.a[2] = wizang[2];
		theApp.a[3] = wizang[3];
		theApp.a[4] = wizang[4];
		theApp.a[5] = wizang[5];
		theApp.a[6] = wizang[6];
		theApp.a[7] = wizang[7];

		theApp.t[0] = wizw[0];
		theApp.t[1] = wizw[1];
		theApp.t[2] = wizw[2];
		theApp.t[3] = wizw[3];
		theApp.t[4] = wizw[4];
		theApp.t[5] = wizw[5];
		theApp.t[6] = wizw[6];
		theApp.t[7] = wizw[7];
	
	CDialog::OnOK();
}

