// GObject.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"
#include "GObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGObject

IMPLEMENT_DYNAMIC( CGObject, CObject )

CGObject::CGObject()
{
}

CGObject::~CGObject()
{
}

void CGObject::ObjectToInventor ( SoGroup *root ) 
{
}

void CGObject::SaveProperties() 
{
}

int CGObject::EditProperties ( CDocument *d, SoSeparator *root ) 
{
	return IDOK ;
}


/////////////////////////////////////////////////////////////////////////////
// CGObject message handlers
