// DeleteObj.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"
#include "DeleteObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DeleteObj dialog


DeleteObj::DeleteObj(CWnd* pParent /*=NULL*/)
	: CDialog(DeleteObj::IDD, pParent)
{
	//{{AFX_DATA_INIT(DeleteObj)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DeleteObj::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DeleteObj)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DeleteObj, CDialog)
	//{{AFX_MSG_MAP(DeleteObj)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DeleteObj message handlers
