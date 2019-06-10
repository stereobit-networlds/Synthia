// RoomBase.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"
#include "lib0.h"
#include "SYNTHDoc.h"

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

#include "RoomBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomBase

IMPLEMENT_DYNAMIC( CRoomBase, CObject )

CRoomBase::CRoomBase()
{
	sep = NULL ;
	plakaki1 = plakaki2 = 0 ;
}

CRoomBase::~CRoomBase()
{
}

/*======================== ObjectToInventor ================*/

void CRoomBase::ObjectToInventor ( SoSeparator *root )
{
	// inherited action
	CGObject::ObjectToInventor(root) ;

	float	vert[50][3] ;
	float	norm[2][3] ;

	// prepare data
	for ( int i = 0 ; i < KoryfCount ; i++ )
	{
		vert[i][0] = Koryfsx[i] ;
		vert[i][1] = Koryfsy[i] + height ;
		vert[i][2] = Koryfsz[i] ;
	}
	norm[0][0] = 0. ;
	norm[0][1] = 1. ;
	norm[0][2] = 0. ;

	BOOL first_time = FALSE ;
	if (sep != NULL) 
		sep->removeAllChildren() ;
	else
	{
	    sep	= new SoSeparator ;
		first_time = TRUE ;
	}

	// setup coordinates
	SoCoordinate3 *c3	= new SoCoordinate3 ;
	c3->point.setValues(0,KoryfCount,vert) ;

	// setup faces
	SoFaceSet *fs = new SoFaceSet ;
	fs->numVertices.setValues(0,1,&KoryfCount) ;

	// setup normal
	SoNormal *nm = new SoNormal ;
	nm->vector.setValues(0,1,norm) ;
	SoNormalBinding *nb = new SoNormalBinding ;
	nb->value = SoNormalBinding::PER_FACE ;

	// setup material
	SoMaterial  *mat = new SoMaterial;
	mat->diffuseColor.setValue( 1., 1., 1. ); //WHITE

	// setup texture
	SoTexture2 *txt ;
	SoTexture2Transform *txtxf ;
	SoTextureCoordinatePlane *txtpl ;
	if (plakaki != "") 
    {
		txt = new SoTexture2 ;
		txt->filename.setValue("d:/ckosmos/synth/data/"+plakaki) ;
		txt->model = SoTexture2::DECAL ;
		txtxf = new SoTexture2Transform ;
		txtxf->translation.setValue(0.5,0.5) ;
		txtpl = new SoTextureCoordinatePlane ;
		txtpl->directionS.setValue(SbVec3f(1/plakaki1,0,0)) ; // x direction
		txtpl->directionT.setValue(SbVec3f(0,0,1/plakaki2)) ; // z direction
	}

	// setup graph
	if (plakaki != "") 
	{
		sep->addChild( txt );	
		sep->addChild( txtxf );	
		sep->addChild( txtpl );	
	}
	sep->addChild( nm );	
	sep->addChild( nb );	
	sep->addChild( mat );	
	sep->addChild( c3 );	
	sep->addChild( fs );

    SoPickStyle *ps = new SoPickStyle;
	sep->addChild(ps) ;
    ps->style.setValue(SoPickStyle::UNPICKABLE) ;

	SoDrawStyle *ds = new SoDrawStyle ;
	sep->addChild(ds) ;
	ds->style = SoDrawStyle::INVISIBLE ;
	
	SaveProperties() ;

	if (first_time) root->addChild(sep) ;
} 

/*======================== SaveProperties ===================*/

void CRoomBase::SaveProperties ()
{
	// inherited action
	CGObject::SaveProperties() ;

	sep->setName(name) ;  // set node name

	SoSeparator *attr = new SoSeparator ;
	attr->setName("Attributes") ;

	CLib0	lib ;
    lib.setSoSFFloatProp ( attr, SbName("Id02"), sdoc->ObjCount ) ; //save object's counter

	lib.setSoSFFloatProp ( attr, "rb_height", height ) ;
	lib.setSoSFIntProp	 ( attr, "KoryfCount", KoryfCount ) ;

	CString soff ;
	for ( int i = 0 ; i < KoryfCount ; i++ )
	{
		soff = lib.inttostr(i) ;
		lib.setSoSFFloatProp ( attr, SbName("rb_Koryfsx"+soff), Koryfsx[i] ) ;
		lib.setSoSFFloatProp ( attr, SbName("rb_Koryfsy"+soff), Koryfsy[i] ) ;
		lib.setSoSFFloatProp ( attr, SbName("rb_Koryfsz"+soff), Koryfsz[i] ) ;
	}

	lib.setSoSFStringProp ( attr, "rb_plakaki", plakaki ) ;
	lib.setSoSFFloatProp ( attr, "rb_plakaki1", plakaki1 ) ;
	lib.setSoSFFloatProp ( attr, "rb_plakaki2", plakaki2 ) ;

	sep->addChild( attr ) ;
}

/*======================== InventorToObject ================*/

void CRoomBase::InventorToObject ( SoSeparator *root )
{
	sep = root ;

	CLib0	lib ;
	KoryfCount	= lib.getSoSFIntProp("KoryfCount") ;
	height		= lib.getSoSFFloatProp("rb_height") ;

	CString soff ;
	for ( int i = 0 ; i < KoryfCount ; i++ )
	{
		soff = lib.inttostr(i) ;
		Koryfsx[i]	= lib.getSoSFFloatProp(SbName("rb_Koryfsx"+soff)) ;
		Koryfsy[i]	= lib.getSoSFFloatProp(SbName("rb_Koryfsy"+soff)) ;
		Koryfsz[i]	= lib.getSoSFFloatProp(SbName("rb_Koryfsz"+soff)) ;
	}

	plakaki    = lib.getSoSFStringProp("rb_plakaki") ;
	plakaki1   = lib.getSoSFFloatProp("rb_plakaki1") ;
	plakaki2   = lib.getSoSFFloatProp("rb_plakaki2") ;
}

/*======================= EditProperties ========================*/

int CRoomBase::EditProperties ( CDocument *d, SoSeparator *root ) 
{
	// inherited action
	CGObject::EditProperties(d,root) ;

	CRoomBasePro *dlg = new CRoomBasePro ;

	dlg->m_plakaki	= plakaki ;
	dlg->m_plakaki1	= plakaki1 ;
	dlg->m_plakaki2	= plakaki2 ;

	int res = dlg->DoModal() ;

	if (res == IDOK)   
	{
		plakaki	=	dlg->m_plakaki ;
		plakaki1=	dlg->m_plakaki1 ;
		plakaki2=	dlg->m_plakaki2 ;

		ObjectToInventor ( root ) ;
	}

	return res ;
}
/////////////////////////////////////////////////////////////////////////////
// CRoomWallPro dialog


CRoomBasePro::CRoomBasePro(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomBasePro::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoomBasePro)
	m_plakaki = _T("");
	m_plakaki1 = 0.0 ;
	m_plakaki2 = 0.0 ;
	//}}AFX_DATA_INIT
}


void CRoomBasePro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomBasePro)
	DDX_Text(pDX, IDC_PLAKAKI, m_plakaki);
	DDX_Text(pDX, IDC_PLAKAKI1, m_plakaki1);
	DDX_Text(pDX, IDC_PLAKAKI2, m_plakaki2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRoomBasePro, CDialog)
	//{{AFX_MSG_MAP(CRoomBasePro)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomWallPro message handlers
