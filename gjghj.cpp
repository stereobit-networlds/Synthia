// gjghj.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"
#include "gjghj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// gjghj dialog


gjghj::gjghj(CWnd* pParent /*=NULL*/)
	: CDialog(gjghj::IDD, pParent)
{
	//{{AFX_DATA_INIT(gjghj)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void gjghj::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(gjghj)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(gjghj, CDialog)
	//{{AFX_MSG_MAP(gjghj)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// gjghj message handlers
