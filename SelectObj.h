#if !defined(AFX_SELECTOBJ_H__3BD7D4B1_8BA9_11D2_81BC_FC811E81490D__INCLUDED_)
#define AFX_SELECTOBJ_H__3BD7D4B1_8BA9_11D2_81BC_FC811E81490D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SelectObj.h : header file
//

#include <Ivf/Viewers/IvfExaminerViewer.h>

/////////////////////////////////////////////////////////////////////////////
// CSelectObj dialog

class CSelectObj : public CDialog
{
// Construction
public:
	CSelectObj(CWnd* pParent = NULL);   // standard constructor

	CIvfExaminerViewer *view ;

	CComboBox	*montelo, *yliko, *portaki, *syrtari, 
				*xeroyl, *mpaza, *antik ;

	CDaoRecordset *rs_eidh0, *rs_omad, *rs_mrec ;

	COleVariant eid_id[10], mrec_id ; 

	BOOL Get_eidh_id() ;
	void Draw() ;

// Dialog Data
	//{{AFX_DATA(CSelectObj)
	enum { IDD = SYNTH_SELECT_OBJ };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectObj)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectObj)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCbMontelo();
	afx_msg void OnNext();
	afx_msg void OnPrior();
	afx_msg void OnSelchangeCbAntik();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTOBJ_H__3BD7D4B1_8BA9_11D2_81BC_FC811E81490D__INCLUDED_)

