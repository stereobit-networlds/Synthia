#if !defined(AFX_ROOMBASE_H__EB9B0081_87B5_11D2_81BC_444553540000__INCLUDED_)
#define AFX_ROOMBASE_H__EB9B0081_87B5_11D2_81BC_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RoomBase.h : header file
//

#include "GObject.h"
#include <Inventor/nodes/SoSeparator.h>

/////////////////////////////////////////////////////////////////////////////
// CRoomBase window

class CRoomBase : public CGObject
{
    DECLARE_DYNAMIC( CRoomBase )

// Construction
public:
	CRoomBase() ; 
	virtual ~CRoomBase() ;

// Attributes
public:

	SbString name ;
	float	height, Koryfsx[10], Koryfsy[10], Koryfsz[10] ;
	int		KoryfCount ;
	
	CString		plakaki ;
	float		plakaki1, plakaki2 ;

// Operations
public:

	void ObjectToInventor ( SoSeparator *root ) ;
	void InventorToObject ( SoSeparator *root ) ;
	void SaveProperties() ;
	int EditProperties ( CDocument *d, SoSeparator *root ) ;
};

#endif // !defined(AFX_ROOMBASE_H__EB9B0081_87B5_11D2_81BC_444553540000__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRoomBasePro dialog

class CRoomBasePro : public CDialog
{
// Construction
public:
	CRoomBasePro(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRoomBasePro)
	enum { IDD = SYNTH_ROOMBASE_PROP };
	CString	m_plakaki;
	float	m_plakaki1;
	float	m_plakaki2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoomBasePro)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRoomBasePro)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

