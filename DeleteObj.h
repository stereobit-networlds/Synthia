#if !defined(AFX_DELETEOBJ_H__71196E41_2644_11D3_AB23_444553540000__INCLUDED_)
#define AFX_DELETEOBJ_H__71196E41_2644_11D3_AB23_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DeleteObj.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DeleteObj dialog

class DeleteObj : public CDialog
{
// Construction
public:
	DeleteObj(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DeleteObj)
	enum { IDD = SYNTH_DELETE_OBJ };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DeleteObj)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DeleteObj)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELETEOBJ_H__71196E41_2644_11D3_AB23_444553540000__INCLUDED_)
