#if !defined(AFX_GEXTERNAL_H__326C9C24_8F50_11D2_81BC_F1E9D6807A24__INCLUDED_)
#define AFX_GEXTERNAL_H__326C9C24_8F50_11D2_81BC_F1E9D6807A24__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GExternal.h : header file
//

#include "GObject.h"

/////////////////////////////////////////////////////////////////////////////
// CGExternal window

class CGExternal : public CGObject
{
    DECLARE_DYNAMIC( CGExternal )

// Construction
public:
	CGExternal();
	virtual ~CGExternal();

// Attributes
public:
	SbString name ;
	int offset ;

	CString eid_id[10] ;
	CString code, descr ;

    int pCount ;   // properties count
    CString  pval[10], pname[10] ;

	int next_id, prior_id, carrier_id ;

    int topoth ;   // apo aristera = 0, apo dexia = 1

    float yangle ;

    float back_vec[3][3] ;

    float left_top_point[3],
          right_top_point[3],
          left_base_point[3],
          right_base_point[3] ;   // in case of participation in a battery

    int back_side ;     // the back side syrface offset into the Syrfs[]

// Operations
public:
	void ObjectToInventor ( SoSeparator *root ) ;
	void InventorToObject ( SoSeparator *root ) ;
	void SaveProperties() ;
	int EditProperties ( CDocument *d, SoSeparator *root ) ;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// GExternalProp dialog

class GExternalProp : public CDialog
{
// Construction
public:
	GExternalProp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GExternalProp)
	enum { IDD = SYNTH_GEXTERNAL_PROP };
	CString	m_code;
	CString	m_descr;
	int		m_topoth;
	float	m_xdist;
	float	m_yangle;
	float	m_ydist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GExternalProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GExternalProp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEXTERNAL_H__326C9C24_8F50_11D2_81BC_F1E9D6807A24__INCLUDED_)
