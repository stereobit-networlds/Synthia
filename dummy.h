#if !defined(AFX_DUMMY_H__3F9FA201_1D28_11D3_AB23_9F945C8DE264__INCLUDED_)
#define AFX_DUMMY_H__3F9FA201_1D28_11D3_AB23_9F945C8DE264__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// dummy.h : header file
//


#include <afxcview.h>   // Need this to use CTreeView
#include <afxcmn.h>     // Need this to use CTreeCtrl

/////////////////////////////////////////////////////////////////////////////
// dummy view

class dummy : public CTreeView
{
protected:
	dummy();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(dummy)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dummy)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~dummy();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(dummy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUMMY_H__3F9FA201_1D28_11D3_AB23_9F945C8DE264__INCLUDED_)
