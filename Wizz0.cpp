// Wizz0.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"
#include "Wizz0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWizz0 *wizard0;

/////////////////////////////////////////////////////////////////////////////
// CWizz0 dialog


CWizz0::CWizz0(CWnd* pParent /*=NULL*/)
	: CDialog(CWizz0::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWizz0)
	m_angle0 = 0.0;
	m_angle1 = 0.0;
	m_angle2 = 0.0;
	m_angle3 = 0.0;
	m_angle4 = 0.0;
	m_angle5 = 0.0;
	m_angle6 = 0.0;
	m_angle7 = 0.0;
	m_length0 = 0.0;
	m_length1 = 0.0;
	m_length2 = 0.0;
	m_length3 = 0.0;
	m_length4 = 0.0;
	m_length5 = 0.0;
	m_length6 = 0.0;
	m_length7 = 0.0;
	m_toix0 = 0;
	m_toix1 = 0;
	m_toix2 = 0;
	m_toix3 = 0;
	m_toix4 = 0;
	m_toix5 = 0;
	m_toix6 = 0;
	m_toix7 = 0;
	//}}AFX_DATA_INIT
}


void CWizz0::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizz0)
	DDX_Text(pDX, IDC_ANGLE0, m_angle0);
	DDX_Text(pDX, IDC_ANGLE1, m_angle1);
	DDX_Text(pDX, IDC_ANGLE2, m_angle2);
	DDX_Text(pDX, IDC_ANGLE3, m_angle3);
	DDX_Text(pDX, IDC_ANGLE4, m_angle4);
	DDX_Text(pDX, IDC_ANGLE5, m_angle5);
	DDX_Text(pDX, IDC_ANGLE6, m_angle6);
	DDX_Text(pDX, IDC_ANGLE7, m_angle7);
	DDX_Text(pDX, IDC_MHKOS0, m_length0);
	DDX_Text(pDX, IDC_MHKOS1, m_length1);
	DDX_Text(pDX, IDC_MHKOS2, m_length2);
	DDX_Text(pDX, IDC_MHKOS3, m_length3);
	DDX_Text(pDX, IDC_MHKOS4, m_length4);
	DDX_Text(pDX, IDC_MHKOS5, m_length5);
	DDX_Text(pDX, IDC_MHKOS6, m_length6);
	DDX_Text(pDX, IDC_MHKOS7, m_length7);
	DDX_Text(pDX, IDC_TOIXOMA0, m_toix0);
	DDX_Text(pDX, IDC_TOIXOMA1, m_toix1);
	DDX_Text(pDX, IDC_TOIXOMA2, m_toix2);
	DDX_Text(pDX, IDC_TOIXOMA3, m_toix3);
	DDX_Text(pDX, IDC_TOIXOMA4, m_toix4);
	DDX_Text(pDX, IDC_TOIXOMA5, m_toix5);
	DDX_Text(pDX, IDC_TOIXOMA6, m_toix6);
	DDX_Text(pDX, IDC_TOIXOMA7, m_toix7);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizz0, CDialog)
	//{{AFX_MSG_MAP(CWizz0)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizz0 message handlers

void CWizz0::OnOK() 
{
	// TODO: Add extra validation here

	// transfer data from the dialog to arrays
	theApp.l[0] = (float)m_length0 ;
	theApp.l[1] = (float)m_length1 ;
	theApp.l[2] = (float)m_length2 ;
	theApp.l[3] = (float)m_length3 ;
	theApp.l[4] = (float)m_length4 ;
	theApp.l[5] = (float)m_length5 ;
	theApp.l[6] = (float)m_length6 ;
	theApp.l[7] = (float)m_length7 ;

	theApp.a[0] = (float)m_angle0 ;
	theApp.a[1] = (float)m_angle1 ;
	theApp.a[2] = (float)m_angle2 ;
	theApp.a[3] = (float)m_angle3 ;
	theApp.a[4] = (float)m_angle4 ;
	theApp.a[5] = (float)m_angle5 ;
	theApp.a[6] = (float)m_angle6 ;
	theApp.a[7] = (float)m_angle7 ;

	theApp.t[0] = m_toix0 ;
	theApp.t[1] = m_toix1 ;
	theApp.t[2] = m_toix2 ;
	theApp.t[3] = m_toix3 ;
	theApp.t[4] = m_toix4 ;
	theApp.t[5] = m_toix5 ;
	theApp.t[6] = m_toix6 ;
	theApp.t[7] = m_toix7 ;

	CDialog::OnOK();
}
