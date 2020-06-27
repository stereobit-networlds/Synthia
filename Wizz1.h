#if !defined(AFX_WIZZ1_H__24DFAFE3_438F_11D3_AB23_87DBDE5B9C61__INCLUDED_)
#define AFX_WIZZ1_H__24DFAFE3_438F_11D3_AB23_87DBDE5B9C61__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Wizz1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizz1 dialog

class CWizz1 : public CDialog
{
// Construction
public:
	CWizz1(CWnd* pParent = NULL);   // standard constructor

	void SetArrayData();

// Dialog Data
	//{{AFX_DATA(CWizz1)
	enum { IDD = SYNTH_WIZZ1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizz1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWizz1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZZ1_H__24DFAFE3_438F_11D3_AB23_87DBDE5B9C61__INCLUDED_)



