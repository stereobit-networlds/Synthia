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

	bool TheLightIs ;   //light editor ..true or false
	int ObjDirection ;  //variable for left,right...
	int ObjSidePosition ; //variable for front,left,back,right...
	int ShowRefPoints ; //αφαιρει - προσθέτει τα ref points

	float l[20] ,a[20] ;    //arrays for basic scene construction
	int t[20];

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
    afx_msg void OnRight();
	afx_msg void OnUpdateRight(CCmdUI* pCmdUI);
	afx_msg void OnLeft();
	afx_msg void OnUpdateLeft(CCmdUI* pCmdUI);
	afx_msg void OnShowrefpoints();
	afx_msg void OnUpdateShowrefpoints(CCmdUI* pCmdUI);
	afx_msg void OnObjsideBack();
	afx_msg void OnUpdateObjsideBack(CCmdUI* pCmdUI);
	afx_msg void OnObjsideLeft();
	afx_msg void OnUpdateObjsideLeft(CCmdUI* pCmdUI);
	afx_msg void OnObjsideFront();
	afx_msg void OnUpdateObjsideFront(CCmdUI* pCmdUI);
	afx_msg void OnObjsideRight();
	afx_msg void OnUpdateObjsideRight(CCmdUI* pCmdUI);
	afx_msg void OnObjsideTop();
	afx_msg void OnUpdateObjsideTop(CCmdUI* pCmdUI);
	afx_msg void OnObjsideBottom();
	afx_msg void OnUpdateObjsideBottom(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CSYNTHApp theApp;


/////////////////////////////////////////////////////////////////////////////
