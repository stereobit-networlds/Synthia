// GExternal.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"
#include "GExternal.h"
#include "glib0.h"
#include "lib0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoNormal.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoNormalBinding.h>
#include <Inventor/nodes/SoText2.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTexture2Transform.h>
#include <Inventor/nodes/SoTextureCoordinatePlane.h>
#include <Inventor/nodes/SoComplexity.h>

#include <Inventor/nodes/SoCone.h>

/////////////////////////////////////////////////////////////////////////////
// CGExternal

IMPLEMENT_DYNAMIC( CGExternal, CObject )

CGExternal::CGExternal()
{
}

CGExternal::~CGExternal()
{
}

/*======================== ObjectToInventor ================*/

void CGExternal::ObjectToInventor ( SoSeparator *root )
{
	// inherited action
	CGObject::ObjectToInventor(root) ;
	
	SoDrawStyle *ds = new SoDrawStyle ;
	sep->addChild(ds) ;
	ds->style = SoDrawStyle::INVISIBLE ;
	
//	SaveProperties() ;

	//bill
	//SoMaterial  *my2Material = new SoMaterial;

	//my2Material->diffuseColor.setValue( 0., 0., 1. ); //Blue
	//root->addChild( my2Material );
	//root->addChild( new SoCone );

} 

/*======================== SaveProperties ===================*/

void CGExternal::SaveProperties ()
{
	// inherited action
	CGObject::SaveProperties() ;

	sep->setName(name) ;  // set node name

	CLib0 lib ;
	CString soff = lib.inttostr(offset) ;

	lib.setSoSFStringProp ( sep, SbName("ob_code"+soff), code ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_descr"+soff), descr ) ;
	
	lib.setSoSFStringProp ( sep, SbName("ob_eid0"+soff), eid_id[0] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid1"+soff), eid_id[1] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid2"+soff), eid_id[2] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid3"+soff), eid_id[3] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid4"+soff), eid_id[4] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid5"+soff), eid_id[5] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid6"+soff), eid_id[6] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid7"+soff), eid_id[7] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid8"+soff), eid_id[8] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid9"+soff), eid_id[9] ) ;
}

/*======================== InventorToObject ================*/

void CGExternal::InventorToObject ( SoSeparator *root )
{
	sep = root ;

	CLib0 lib ;
	CString soff = lib.inttostr(offset) ;

	code       = lib.getSoSFStringProp(SbName("ob_code"+soff)) ;
	descr      = lib.getSoSFStringProp(SbName("ob_descr"+soff)) ;

	eid_id[0]  = lib.getSoSFStringProp(SbName("ob_eid0"+soff)) ;
	eid_id[1]  = lib.getSoSFStringProp(SbName("ob_eid1"+soff)) ;
	eid_id[2]  = lib.getSoSFStringProp(SbName("ob_eid2"+soff)) ;
	eid_id[3]  = lib.getSoSFStringProp(SbName("ob_eid3"+soff)) ;
	eid_id[4]  = lib.getSoSFStringProp(SbName("ob_eid4"+soff)) ;
	eid_id[5]  = lib.getSoSFStringProp(SbName("ob_eid5"+soff)) ;
	eid_id[6]  = lib.getSoSFStringProp(SbName("ob_eid6"+soff)) ;
	eid_id[7]  = lib.getSoSFStringProp(SbName("ob_eid7"+soff)) ;
	eid_id[8]  = lib.getSoSFStringProp(SbName("ob_eid8"+soff)) ;
	eid_id[9]  = lib.getSoSFStringProp(SbName("ob_eid9"+soff)) ;
}

/*======================= EditProperties ========================*/

int CGExternal::EditProperties ( CDocument *d, SoSeparator *root ) 
{
	// inherited action
	CGObject::EditProperties(d,root) ;
	return 1 ;
}
