#if !defined(AFX_IVFLISTVIEW_H__9B39E481_1F9F_11D3_AB23_C47229FDC767__INCLUDED_)
#define AFX_IVFLISTVIEW_H__9B39E481_1F9F_11D3_AB23_C47229FDC767__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// IvfListView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// IvfListView view

//addin by me
#include <afxcview.h>   // Need this to use CTreeView
#include <afxcmn.h>     // Need this to use CTreeCtrl

class IvfListView : public CListView
{
protected:
	IvfListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(IvfListView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IvfListView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~IvfListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(IvfListView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IVFLISTVIEW_H__9B39E481_1F9F_11D3_AB23_C47229FDC767__INCLUDED_)
