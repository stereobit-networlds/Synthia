#if !defined(AFX_GOBJECT_H__6F3D3D21_8F47_11D2_81BC_BE09FAFB8E0E__INCLUDED_)
#define AFX_GOBJECT_H__6F3D3D21_8F47_11D2_81BC_BE09FAFB8E0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GObject.h : header file
//

#include <Inventor/nodes/SoSeparator.h>

/////////////////////////////////////////////////////////////////////////////
// CGObject window

class CGObject : public CObject
{
    DECLARE_DYNAMIC( CGObject )
// Construction
public:
	CGObject();

// Implementation
public:
	virtual ~CGObject();

	SoSeparator *sep ;

	void ObjectToInventor ( SoGroup *root ) ;
	void SaveProperties() ;
	int EditProperties ( CDocument *d, SoSeparator *root ) ;
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_GOBJECT_H__6F3D3D21_8F47_11D2_81BC_BE09FAFB8E0E__INCLUDED_)
