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
	float depth ;
	float height ;
	float Koryfsx[8], Koryfsy[8], Koryfsz[8] ;

	CString		plakaki ;
	float		plakaki1, plakaki2 ;

	float xdist, ydist ,zdist ,rot ,left_d , right_d , up_d;

	float corner ;  //η γωνια του τοιχου με τον carrier τοιχο

// Operations
public:
	void ObjectToInventor ( SoSeparator *root ) ;
	void InventorToObject ( SoSeparator *root ) ;
	void SaveProperties() ;
	void GetBox() ;
	int  EditProperties ( CDocument *d, SoSeparator *root ) ;

	void AddNewObject(SbVec3f p_point, SbVec3f p_normal) ;

	void MoveCarrierObjects(float dx,float dy,float dz) ;
	void MoveObjectTo(float d1,float d2,float d3) ;
	void RotateCarrierObjects(float dx,float dy,float dz) ;
	void RotateObject(float crn) ;

	bool IsAttachedObject(int wallno) ;
	void DeleteObject(int aanumber) ;
	void CopyObject(int aanumber) ;
	void PasteObject() ;
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
	float	m_xdist;
	float	m_ydist;
	float	m_zdist;
	float	m_rot;
	float	m_left;
	float	m_right;
	float	m_up;
	float	m_objlength;
	float	m_outlook;
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
