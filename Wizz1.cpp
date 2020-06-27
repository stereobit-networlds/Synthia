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
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWizz1 message handlers


