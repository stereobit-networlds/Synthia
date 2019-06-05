// SYNTH.h : main header file for the SYNTH application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

// BEGIN_IVWGEN
#include <Ivf/IvfApp.h>
// END_IVWGEN

/////////////////////////////////////////////////////////////////////////////
// CSYNTHApp:
// See SYNTH.cpp for the implementation of this class
//

// BEGIN_IVWGEN
class CSYNTHApp : public CWinApp , public CIvfApp
// END_IVWGEN
{
public:
	CSYNTHApp();
	long m_nLastOpenedFilterIX;

	CDaoDatabase	m_database ;
	CDaoTableDef	*tdf_eidh0, *tdf_omad, *tdf_mrec ;
	CDaoRecordset	*rs_eidh0, *rs_omad, *rs_mrec ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSYNTHApp)
	public:
	virtual BOOL InitInstance();
// BEGIN_IVWGEN
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	virtual BOOL PreTranslateMessage(MSG *pMsg);
// END_IVWGEN
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSYNTHApp)
	afx_msg void OnAppAbout();
        afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileViewInfo();
	afx_msg void OnUpdateFileViewInfo(CCmdUI *pCmdUI);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CSYNTHApp theApp;


/////////////////////////////////////////////////////////////////////////////
