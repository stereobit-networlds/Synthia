#if !defined(AFX_GJGHJ_H__5F4046C1_1ABF_11D3_AB23_F0562172D864__INCLUDED_)
#define AFX_GJGHJ_H__5F4046C1_1ABF_11D3_AB23_F0562172D864__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// gjghj.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// gjghj dialog

class gjghj : public CDialog
{
// Construction
public:
	gjghj(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(gjghj)
	enum { IDD = SYNTH_GEXTERNAL_PROP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(gjghj)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(gjghj)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GJGHJ_H__5F4046C1_1ABF_11D3_AB23_F0562172D864__INCLUDED_)
