// RoomWall.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"

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

#include "glib0.h"
#include "lib0.h"
#include "RoomWall.h"
#include "SYNTHDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomWall

IMPLEMENT_DYNAMIC( CRoomWall, CObject )

CRoomWall::CRoomWall()
{
	sep = NULL ;
	plakaki1 = plakaki2 = 0 ;
}

CRoomWall::~CRoomWall()
{
}

/*======================== ObjectToInventor ================*/

void CRoomWall::ObjectToInventor ( SoSeparator *root )
{
	// inherited action
	CGObject::ObjectToInventor(root) ;

	float	vert[30][3] ;
	float	norm[5][3] ;
	int 	numvert[5] ;
	float	nx, ny, nz ;

	BOOL first_time = FALSE ;
	if (sep != NULL) 
		sep->removeAllChildren() ;
	else
    {
	    sep	= new SoSeparator() ;
		first_time = TRUE ;
	}

	CGLib0 *lib = new CGLib0 ;
	
	lib->GetPolyNormal ( Koryfsx[0], Koryfsy[0], Koryfsz[0],
						 Koryfsx[1], Koryfsy[1]+100, Koryfsz[1],						
						 Koryfsx[1], Koryfsy[1], Koryfsz[1],
						 &nx, &ny, &nz ) ;

	// find Koryfs[2]
	Koryfsx[2] = Koryfsx[1] + depth * nx ;
	Koryfsy[2] = Koryfsy[1] + depth * ny ;
	Koryfsz[2] = Koryfsz[1] + depth * nz ;

	// find Koryfs[3]
	Koryfsx[3] = Koryfsx[0] + depth * nx ;
	Koryfsy[3] = Koryfsy[0] + depth * ny ;
	Koryfsz[3] = Koryfsz[0] + depth * nz ;

	// setup data
	// ... face 1
	vert[0][0] = Koryfsx[0] ; 
	vert[0][1] = Koryfsy[0] ; 
	vert[0][2] = Koryfsz[0] ;
	
	vert[1][0] = Koryfsx[1] ; 
	vert[1][1] = Koryfsy[1] ; 
	vert[1][2] = Koryfsz[1] ;

	vert[2][0] = Koryfsx[1] ; 
	vert[2][1] = Koryfsy[1]+height ; 
	vert[2][2] = Koryfsz[1] ;
	
	vert[3][0] = Koryfsx[0] ; 
	vert[3][1] = Koryfsy[0]+height ; 
	vert[3][2] = Koryfsz[0] ;
	lib->GetPolyNormal ( vert[0][0], vert[0][1], vert[0][2],
						 vert[1][0], vert[1][1], vert[1][2],	
						 vert[2][0], vert[2][1], vert[2][2],
						 &norm[0][0], &norm[0][1], &norm[0][2] ) ; 	
	numvert[0] = 4 ;

	// ... face 2
	vert[4][0] = Koryfsx[1] ; 
	vert[4][1] = Koryfsy[1] ; 
	vert[4][2] = Koryfsz[1] ;
	
	vert[5][0] = Koryfsx[2] ; 
	vert[5][1] = Koryfsy[2] ; 
	vert[5][2] = Koryfsz[2] ;
	
	vert[6][0] = Koryfsx[2] ; 
	vert[6][1] = Koryfsy[2]+height ; 
	vert[6][2] = Koryfsz[2] ;

	vert[7][0] = Koryfsx[1] ; 
	vert[7][1] = Koryfsy[1]+height ; 
	vert[7][2] = Koryfsz[1] ;
	lib->GetPolyNormal ( vert[4][0], vert[4][1], vert[4][2],
						 vert[5][0], vert[5][1], vert[5][2],	
						 vert[6][0], vert[6][1], vert[6][2],
						 &norm[1][0], &norm[1][1], &norm[1][2] ) ; 	
	numvert[1] = 4 ;

	// ... face 3
	vert[8][0] = Koryfsx[2] ; 
	vert[8][1] = Koryfsy[2] ; 
	vert[8][2] = Koryfsz[2] ;
	
	vert[9][0] = Koryfsx[3] ; 
	vert[9][1] = Koryfsy[3] ; 
	vert[9][2] = Koryfsz[3] ;
	
	vert[10][0] = Koryfsx[3] ; 
	vert[10][1] = Koryfsy[3]+height ; 
	vert[10][2] = Koryfsz[3] ;

	vert[11][0] = Koryfsx[2] ; 
	vert[11][1] = Koryfsy[2]+height ; 
	vert[11][2] = Koryfsz[2] ;
	lib->GetPolyNormal ( vert[8][0], vert[8][1], vert[8][2],
						 vert[9][0], vert[9][1], vert[9][2],	
						 vert[10][0], vert[10][1], vert[10][2],
						 &norm[2][0], &norm[2][1], &norm[2][2] ) ; 	
	numvert[2] = 4 ;

	// ... face 4
	vert[12][0] = Koryfsx[3] ; 
	vert[12][1] = Koryfsy[3] ; 
	vert[12][2] = Koryfsz[3] ;
	
	vert[13][0] = Koryfsx[0] ; 
	vert[13][1] = Koryfsy[0] ; 
	vert[13][2] = Koryfsz[0] ;
	
	vert[14][0] = Koryfsx[0] ; 
	vert[14][1] = Koryfsy[0]+height ; 
	vert[14][2] = Koryfsz[0] ;

	vert[15][0] = Koryfsx[3] ; 
	vert[15][1] = Koryfsy[3]+height ; 
	vert[15][2] = Koryfsz[3] ;
	lib->GetPolyNormal ( vert[12][0], vert[12][1], vert[12][2],
						 vert[13][0], vert[13][1], vert[13][2],	
						 vert[14][0], vert[14][1], vert[14][2],
						 &norm[3][0], &norm[3][1], &norm[3][2] ) ; 	
	numvert[3] = 4 ;

	// ... face 4
	vert[16][0] = Koryfsx[0] ; 
	vert[16][1] = Koryfsy[0]+height ; 
	vert[16][2] = Koryfsz[0] ;
	
	vert[17][0] = Koryfsx[1] ; 
	vert[17][1] = Koryfsy[1]+height ; 
	vert[17][2] = Koryfsz[1] ;
	
	vert[18][0] = Koryfsx[2] ; 
	vert[18][1] = Koryfsy[2]+height ; 
	vert[18][2] = Koryfsz[2] ;

	vert[19][0] = Koryfsx[3] ; 
	vert[19][1] = Koryfsy[3]+height ; 
	vert[19][2] = Koryfsz[3] ;
	lib->GetPolyNormal ( vert[16][0], vert[16][1], vert[16][2],
						 vert[17][0], vert[17][1], vert[17][2],	
						 vert[18][0], vert[18][1], vert[18][2],
						 &norm[4][0], &norm[4][1], &norm[4][2] ) ; 	
	numvert[4] = 4 ;

	int num_faces = 5 ;

	// setup coordinates
	SoCoordinate3 *c3	= new SoCoordinate3 ;
	c3->point.setValues(0,20,vert) ;

	// setup faces
	SoFaceSet *fs = new SoFaceSet ;
	fs->numVertices.setValues(0,num_faces,numvert) ;

	// setup normal
	SoNormal *nm = new SoNormal ;
	nm->vector.setValues(0,num_faces,norm) ;

	SoNormalBinding *nb = new SoNormalBinding ;
	nb->value = SoNormalBinding::PER_FACE ;

	// setup material
	SoMaterial  *mat = new SoMaterial;
	mat->diffuseColor.setValue( 1., 1., 1. ); // WHITE

	SoComplexity *com = new SoComplexity ;
	com->textureQuality = 0.5 ;

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
		// ÐÑÅÐÅÉ ÍÁ ËÇÖÅÉ ÕÐ ÏØÇ Ç ÊÁÔÅÕÈÕÍÓÇ ÊÁÔÁ ÔÏ (×,Æ) ÅÐÉÐÅÄÏ 
		CGLib0 glib ;
		float len = glib.GetDistance ( Koryfsx[0], Koryfsy[0], Koryfsz[0],
									  Koryfsx[1], Koryfsy[1], Koryfsz[1]) ;
		float dx = (Koryfsx[1]-Koryfsx[0])/len ;
		float dz = (Koryfsz[1]-Koryfsz[0])/len ;
		txtpl->directionS.setValue(SbVec3f(dx/plakaki1,0,dz/plakaki1)) ; // x,z direction
		txtpl->directionT.setValue(SbVec3f(0,1/plakaki2,0)) ; // y direction
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
	sep->addChild( com );	
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

void CRoomWall::SaveProperties ()
{
	// inherited action
	CGObject::SaveProperties() ;

	sep->setName(name) ;  // set node name

	SoSeparator *attr = new SoSeparator ;
	attr->setName("Attributes") ;

	CLib0 lib ;
	CString soff = lib.inttostr(offset) ;
    lib.setSoSFFloatProp ( attr, SbName("Id03_"+soff), sdoc->ObjCount ) ; //save object's counter as id

	lib.setSoSFFloatProp ( attr, SbName("height"+soff), height ) ;
	lib.setSoSFFloatProp ( attr, SbName("depth"+soff), depth ) ;

	lib.setSoSFFloatProp ( attr, SbName("Koryfsx0"+soff), Koryfsx[0] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsy0"+soff), Koryfsy[0] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsz0"+soff), Koryfsz[0] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsx1"+soff), Koryfsx[1] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsy1"+soff), Koryfsy[1] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsz1"+soff), Koryfsz[1] ) ;

	lib.setSoSFStringProp ( attr, SbName("rw_plakaki"+soff), plakaki ) ;
	lib.setSoSFFloatProp ( attr, SbName("rw_plakaki1"+soff), plakaki1 ) ;
	lib.setSoSFFloatProp ( attr, SbName("rw_plakaki2"+soff), plakaki2 ) ;

	sep->addChild( attr ) ;
}

/*======================== InventorToObject ================*/

void CRoomWall::InventorToObject ( SoSeparator *root )
{
	sep = root ;

	CLib0 lib ;
	CString soff = lib.inttostr(offset) ;
	depth     = lib.getSoSFFloatProp(SbName("depth"+soff)) ;
	height    = lib.getSoSFFloatProp(SbName("height"+soff)) ;

	Koryfsx[0] = lib.getSoSFFloatProp(SbName("Koryfsx0"+soff)) ;
	Koryfsy[0] = lib.getSoSFFloatProp(SbName("Koryfsy0"+soff)) ;
	Koryfsz[0] = lib.getSoSFFloatProp(SbName("Koryfsz0"+soff)) ;
	Koryfsx[1] = lib.getSoSFFloatProp(SbName("Koryfsx1"+soff)) ;
	Koryfsy[1] = lib.getSoSFFloatProp(SbName("Koryfsy1"+soff)) ;
	Koryfsz[1] = lib.getSoSFFloatProp(SbName("Koryfsz1"+soff)) ;

	plakaki    = lib.getSoSFStringProp(SbName("rw_plakaki"+soff)) ;
	plakaki1   = lib.getSoSFFloatProp(SbName("rw_plakaki1"+soff)) ;
	plakaki2   = lib.getSoSFFloatProp(SbName("rw_plakaki2"+soff)) ;
}

/*======================= EditProperties ========================*/

int CRoomWall::EditProperties ( CDocument *d, SoSeparator *root ) 
{
	// inherited action
	CGObject::EditProperties(d,root) ;

	CRoomWallPro *dlg = new CRoomWallPro ;

	dlg->m_width	= depth ;
	dlg->m_height	= height ;
	dlg->m_plakaki	= plakaki ;
	dlg->m_plakaki1	= plakaki1 ;
	dlg->m_plakaki2	= plakaki2 ;

	int res = dlg->DoModal() ;

	if (res == IDOK)   
	{
		depth	=	dlg->m_width ;
		height	=	dlg->m_height ;
		plakaki	=	dlg->m_plakaki ;
		plakaki1=	dlg->m_plakaki1 ;
		plakaki2=	dlg->m_plakaki2 ;

		ObjectToInventor ( root ) ;
	}

	return res ;
}
/////////////////////////////////////////////////////////////////////////////
// CRoomWallPro dialog


CRoomWallPro::CRoomWallPro(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomWallPro::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoomWallPro)
	m_height = 0.0;
	m_width = 0.0;
	m_plakaki = _T("");
	m_plakaki1 = 0.0 ;
	m_plakaki2 = 0.0 ;
	//}}AFX_DATA_INIT
}


void CRoomWallPro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomWallPro)
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDX_Text(pDX, IDC_PLAKAKI, m_plakaki);
	DDX_Text(pDX, IDC_PLAKAKI1, m_plakaki1);
	DDX_Text(pDX, IDC_PLAKAKI2, m_plakaki2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRoomWallPro, CDialog)
	//{{AFX_MSG_MAP(CRoomWallPro)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomWallPro message handlers
