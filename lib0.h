#if !defined(AFX_LIB0_H__B1008AA6_8DB7_11D2_81BC_A5113812E41F__INCLUDED_)
#define AFX_LIB0_H__B1008AA6_8DB7_11D2_81BC_A5113812E41F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// lib0.h : header file
//

#include <Inventor/nodes/SoSeparator.h>

/////////////////////////////////////////////////////////////////////////////
// CLib0 object

class CLib0 : public CObject
{
// Construction
public:
	CLib0();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLib0)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLib0();

	void	getvar(	char *dd, char *mm, 
					char *vname1, char *vname2, char *value ) ; 
	float	strtofloat	( char *value ) ;
	int		strtoint	( char *value ) ;
	CString floattostr	( float fl ) ;
	CString inttostr	( int i ) ;
	void	CStringToChar ( CString cstr, char *chr ) ;

	void	setSoSFFloatProp ( SoSeparator *sep, SbName pname, float val ) ; 
	float	getSoSFFloatProp ( SbName pname ) ; 
	void	setSoSFIntProp	( SoSeparator *sep, SbName pname, int val ) ; 
	int		getSoSFIntProp  ( SbName pname ) ; 
	void	setSoSFStringProp ( SoSeparator *sep, SbName pname, CString val ) ; 
	CString	getSoSFStringProp ( SbName pname ) ; 
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIB0_H__B1008AA6_8DB7_11D2_81BC_A5113812E41F__INCLUDED_)
