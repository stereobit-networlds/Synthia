// WorldBase.h: interface for the CWorldBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORLDBASE_H__A29306EB_848F_11D2_81BC_444553540000__INCLUDED_)
#define AFX_WORLDBASE_H__A29306EB_848F_11D2_81BC_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GObject.h"
#include "resource.h"
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/SbString.h>

class CWorldBase  : public CGObject 
{
    DECLARE_DYNAMIC( CWorldBase )
public:
	CWorldBase() ;
	virtual ~CWorldBase() ;

	SbString name ;
	float width, height, depth ;
	int outspace ;
	SbString c_name, c_address, c_city, c_tel ;

	void ObjectToInventor ( SoSeparator *root ) ;
	void InventorToObject ( SoSeparator *root ) ;
	void SaveProperties() ;
	void GetBox() ;
	int EditProperties ( CDocument *d, SoSeparator *root ) ;

	void AddNewObject(SbVec3f p_point, SbVec3f p_normal);
} ;

#endif // !defined(AFX_WORLDBASE_H__A29306EB_848F_11D2_81BC_444553540000__INCLUDED_)
/////////////////////////////////////////////////////////////////////////////
// CWorldBasePro dialog

class CWorldBasePro : public CDialog
{
// Construction
public:
	CWorldBasePro(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWorldBasePro)
	enum { IDD = SYNTH_WORLDBASE_PROP };
	CString	m_address;
	CString	m_city;
	CString	m_name;
	CString	m_tel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorldBasePro)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWorldBasePro)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
