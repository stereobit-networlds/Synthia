#if !defined(AFX_ROOMWALL_H__C2AB2684_87C1_11D2_81BC_444553540000__INCLUDED_)
#define AFX_ROOMWALL_H__C2AB2684_87C1_11D2_81BC_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RoomWall.h : header file
//

#include "GObject.h"

/////////////////////////////////////////////////////////////////////////////
// CRoomWall window

class CRoomWall : public CGObject
{
    DECLARE_DYNAMIC( CRoomWall )

// Construction
public:
	CRoomWall();
	virtual ~CRoomWall();

// Attributes
public:
	SbString name ;
	int offset ;
	float depth ;
	float height ;
	float Koryfsx[4], Koryfsy[4], Koryfsz[4] ;

	CString		plakaki ;
	float		plakaki1, plakaki2 ;

// Operations
public:
	void ObjectToInventor ( SoGroup *root ) ;
	void InventorToObject ( SoSeparator *root ) ;
	void SaveProperties() ;
	int EditProperties ( CDocument *d, SoSeparator *root ) ;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRoomWallPro dialog

class CRoomWallPro : public CDialog
{
// Construction
public:
	CRoomWallPro(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRoomWallPro)
	enum { IDD = SYNTH_ROOMWALL_PROP };
	float	m_height;
	float	m_width;
	CString	m_plakaki;
	float	m_plakaki1;
	float	m_plakaki2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoomWallPro)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRoomWallPro)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOMWALL_H__C2AB2684_87C1_11D2_81BC_444553540000__INCLUDED_)
