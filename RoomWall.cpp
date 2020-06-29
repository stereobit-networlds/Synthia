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
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTexture2Transform.h>
#include <Inventor/nodes/SoTextureCoordinatePlane.h>
#include <Inventor/nodes/SoTextureCoordinateEnvironment.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoTransform.h>

#include "glib0.h"
#include "lib0.h"
#include "RoomWall.h"
#include "RoomBase.h"
#include "SYNTHDoc.h"
#include "SYNTHView.h"
#include "GExternal.h"

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
	xdist = ydist = zdist = 0 ;
	rotangle = 0 ;
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

	//init transform
    SoTransform	*trans	= new SoTransform ;

	//setup draw style
	SoDrawStyle *ds = new SoDrawStyle ;
	ds->style = SoDrawStyle::FILLED ;

	//init pick style
	SoPickStyle *ps = new SoPickStyle;
    ps->style.setValue(SoPickStyle::SHAPE) ;

	// setup material
	SoMaterial  *mat = new SoMaterial;
	mat->diffuseColor.setValue( 1., 1., 1. ); // WHITE

	sep->addChild( trans ) ;
    sep->addChild( ds );	
	sep->addChild( ps ) ;
	sep->addChild( mat );


	CGLib0 *lib = new CGLib0 ;
	
	lib->GetPolyNormal ( Koryfsx[0], Koryfsy[0], Koryfsz[0],
						 Koryfsx[1], Koryfsy[1]+100, Koryfsz[1],						
						 Koryfsx[1], Koryfsy[1], Koryfsz[1],
						 &nx, &ny, &nz ) ;
    //BASE POINTS
	// find Koryfs[2] = C
	Koryfsx[2] = Koryfsx[1] + depth * nx ;
	Koryfsy[2] = Koryfsy[1] + depth * ny ;
	Koryfsz[2] = Koryfsz[1] + depth * nz ;

	// find Koryfs[3] = D
	Koryfsx[3] = Koryfsx[0] + depth * nx ;
	Koryfsy[3] = Koryfsy[0] + depth * ny ;
	Koryfsz[3] = Koryfsz[0] + depth * nz ;

	//UP POINTS
	// find Koryfs[4] = A'
	Koryfsx[4] = Koryfsx[0] ;
	Koryfsy[4] = Koryfsy[0] + height ;
	Koryfsz[4] = Koryfsz[0]  ;

	// find Koryfs[5] = B'
	Koryfsx[5] = Koryfsx[1] ;
	Koryfsy[5] = Koryfsy[1] + height ;
	Koryfsz[5] = Koryfsz[1] ;

	// find Koryfs[6] = C'
	Koryfsx[6] = Koryfsx[2] ;
	Koryfsy[6] = Koryfsy[2] + height ;
	Koryfsz[6] = Koryfsz[2] ;

	// find Koryfs[7] = D'
	Koryfsx[7] = Koryfsx[3] ;
	Koryfsy[7] = Koryfsy[3] + height ;
	Koryfsz[7] = Koryfsz[3] ;

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

	// ... face 5
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

	SoComplexity *com = new SoComplexity ;
	com->textureQuality = 0.5 ;

	// setup texture
	SoTexture2 *txt ;
	SoTexture2Transform *txtxf ;
	SoTextureCoordinatePlane *txtpl ;
	//SoTextureCoordinateEnvironment *txtpl ; future use...
	if (plakaki != "") 
    {
		txt = new SoTexture2 ;
		txt->filename.setValue("d:/ckosmos/synth/data/"+plakaki) ;
		txt->model = SoTexture2::DECAL ;
		txtxf = new SoTexture2Transform ;
		txtxf->translation.setValue(0.5,0.5) ;
		txtpl = new SoTextureCoordinatePlane ;
		// ΠΡΕΠΕΙ ΝΑ ΛΗΦΕΙ ΥΠ ΟΨΗ Η ΚΑΤΕΥΘΥΝΣΗ ΚΑΤΑ ΤΟ (Χ,Ζ) ΕΠΙΠΕΔΟ 
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
	sep->addChild( c3 );	
	sep->addChild( fs );

	
	GetBox();  //<<<<<-------------------------------- εγκιβωτισμος

	SaveProperties() ;
	if (first_time) root->addChild(sep) ;
} 


/*======================== SaveProperties ===================*/

void CRoomWall::SaveProperties ()
{
	// inherited action
	CGObject::SaveProperties() ;

	sep->setName(name) ;  // set node name

	// find "Attributes"
	int mychild =sep->getNumChildren()-1;
	SoSeparator *myattr = (SoSeparator *)sep->getChild(mychild);
	const char *name = ((SoSeparator *)myattr)->getName().getString();  //get name

	if (strcmp(name,"Attributes")==0) //Attributes exist delete it...
    {
		sep->removeChild(mychild);
    }

	SoSeparator *attr = new SoSeparator ;
	attr->setName("Attributes") ;

    //set attributes invisible & unpickable
	SoDrawStyle *ds = new SoDrawStyle ;
	attr->addChild(ds) ;
	ds->style = SoDrawStyle::INVISIBLE ;

	SoPickStyle *ps = new SoPickStyle;
	attr->addChild(ps) ;
    ps->style.setValue(SoPickStyle::UNPICKABLE) ;

	CLib0 lib ;
	CString soff = lib.inttostr(offset) ;
 
	lib.setSoSFFloatProp ( attr, SbName("height"+soff), height ) ;
	lib.setSoSFFloatProp ( attr, SbName("depth"+soff), depth ) ;

	// BASE PONTS
	lib.setSoSFFloatProp ( attr, SbName("Koryfsx0"+soff), Koryfsx[0] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsy0"+soff), Koryfsy[0] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsz0"+soff), Koryfsz[0] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsx1"+soff), Koryfsx[1] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsy1"+soff), Koryfsy[1] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsz1"+soff), Koryfsz[1] ) ;

	lib.setSoSFFloatProp ( attr, SbName("Koryfsx2"+soff), Koryfsx[2] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsy2"+soff), Koryfsy[2] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsz2"+soff), Koryfsz[2] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsx3"+soff), Koryfsx[3] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsy3"+soff), Koryfsy[3] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsz3"+soff), Koryfsz[3] ) ;

    // UP POINTS
	lib.setSoSFFloatProp ( attr, SbName("Koryfsx4"+soff), Koryfsx[4] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsy4"+soff), Koryfsy[4] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsz4"+soff), Koryfsz[4] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsx5"+soff), Koryfsx[5] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsy5"+soff), Koryfsy[5] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsz5"+soff), Koryfsz[5] ) ;

	lib.setSoSFFloatProp ( attr, SbName("Koryfsx6"+soff), Koryfsx[6] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsy6"+soff), Koryfsy[6] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsz6"+soff), Koryfsz[6] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsx7"+soff), Koryfsx[7] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsy7"+soff), Koryfsy[7] ) ;
	lib.setSoSFFloatProp ( attr, SbName("Koryfsz7"+soff), Koryfsz[7] ) ;

	lib.setSoSFStringProp ( attr, SbName("rw_plakaki"+soff), plakaki ) ;
	lib.setSoSFFloatProp ( attr, SbName("rw_plakaki1"+soff), plakaki1 ) ;
	lib.setSoSFFloatProp ( attr, SbName("rw_plakaki2"+soff), plakaki2 ) ;

	sep->addChild( attr ) ;
}

/*======================== InventorToObject ================*/

void CRoomWall::InventorToObject ( SoSeparator *root )
{
	sep = root ;

	//inherited action
	CGObject::InventorToObject (root);

	CLib0 lib ;
	CString soff = lib.inttostr(offset) ;

	depth     = lib.getSoSFFloatProp(SbName("depth"+soff)) ;
	height    = lib.getSoSFFloatProp(SbName("height"+soff)) ;

	// BASE POINTS
	Koryfsx[0] = lib.getSoSFFloatProp(SbName("Koryfsx0"+soff)) ;
	Koryfsy[0] = lib.getSoSFFloatProp(SbName("Koryfsy0"+soff)) ;
	Koryfsz[0] = lib.getSoSFFloatProp(SbName("Koryfsz0"+soff)) ;
	Koryfsx[1] = lib.getSoSFFloatProp(SbName("Koryfsx1"+soff)) ;
	Koryfsy[1] = lib.getSoSFFloatProp(SbName("Koryfsy1"+soff)) ;
	Koryfsz[1] = lib.getSoSFFloatProp(SbName("Koryfsz1"+soff)) ;

	Koryfsx[2] = lib.getSoSFFloatProp(SbName("Koryfsx2"+soff)) ;
	Koryfsy[2] = lib.getSoSFFloatProp(SbName("Koryfsy2"+soff)) ;
	Koryfsz[2] = lib.getSoSFFloatProp(SbName("Koryfsz2"+soff)) ;
	Koryfsx[3] = lib.getSoSFFloatProp(SbName("Koryfsx3"+soff)) ;
	Koryfsy[3] = lib.getSoSFFloatProp(SbName("Koryfsy3"+soff)) ;
	Koryfsz[3] = lib.getSoSFFloatProp(SbName("Koryfsz3"+soff)) ;

    // UP POINTS
	Koryfsx[4] = lib.getSoSFFloatProp(SbName("Koryfsx4"+soff)) ;
	Koryfsy[4] = lib.getSoSFFloatProp(SbName("Koryfsy4"+soff)) ;
	Koryfsz[4] = lib.getSoSFFloatProp(SbName("Koryfsz4"+soff)) ;
	Koryfsx[5] = lib.getSoSFFloatProp(SbName("Koryfsx5"+soff)) ;
	Koryfsy[5] = lib.getSoSFFloatProp(SbName("Koryfsy5"+soff)) ;
	Koryfsz[5] = lib.getSoSFFloatProp(SbName("Koryfsz5"+soff)) ;

	Koryfsx[6] = lib.getSoSFFloatProp(SbName("Koryfsx6"+soff)) ;
	Koryfsy[6] = lib.getSoSFFloatProp(SbName("Koryfsy6"+soff)) ;
	Koryfsz[6] = lib.getSoSFFloatProp(SbName("Koryfsz6"+soff)) ;
	Koryfsx[7] = lib.getSoSFFloatProp(SbName("Koryfsx7"+soff)) ;
	Koryfsy[7] = lib.getSoSFFloatProp(SbName("Koryfsy7"+soff)) ;
	Koryfsz[7] = lib.getSoSFFloatProp(SbName("Koryfsz7"+soff)) ;


	plakaki    = lib.getSoSFStringProp(SbName("rw_plakaki"+soff)) ;
	plakaki1   = lib.getSoSFFloatProp(SbName("rw_plakaki1"+soff)) ;
	plakaki2   = lib.getSoSFFloatProp(SbName("rw_plakaki2"+soff)) ;
}

void CRoomWall::GetBox()
{
	// inherited action
	CGObject::GetBox() ;

	//assign koryfs to box 
	//επειδη ο τοιχοσ ειναι ενα κανονικο ορθογωνιο παραλ/δο οι κορυφες του
	//αντιστοιχουν στον εγκιβωτισμο
	int m;

	for (m=0 ; m<8 ; m++)
    {
		ssx[m] = Koryfsx[m];
        ssy[m] = Koryfsy[m];
		ssz[m] = Koryfsz[m];
	}
}

/*======================= EditProperties ========================*/

int CRoomWall::EditProperties ( CDocument *d, SoSeparator *root ) 
{
    float cdistX, cdistY, cdistZ, cRot ;
	float cleft , cright , compOut, cup , x ;
	SbVec3f vals ;

	// inherited action
	CGObject::EditProperties(d,root) ;

	CLib0 lib;
	AfxMessageBox(" offset "+lib.inttostr(offset)+"\n Carrier "
		               +lib.inttostr(carrier_id)+"\n Side"
		               +lib.inttostr(carrier_side)+"\n Obj Side"
					   +lib.inttostr(object_side)+"\n rotation "
					   +lib.inttostr(rotangle));


	if ((carrier_side ==_NOWHERE_) || 
		(object_side == _NOWHERE_))
	{
       AfxMessageBox("Invalid object data");
	   return 0 ;
    }

	xdist = Koryfsx[0];
	ydist = Koryfsy[0];
	zdist = Koryfsz[0];

	//get rotation angle ...
	//rotangle = corner;

    //Calculate selected object distances
    left_d  = GetLeftDistance();
	right_d = GetRightDistance();
	up_d    = GetDistanceY();

	CRoomWallPro *dlg = new CRoomWallPro ;

	dlg->m_width	= depth ;
	dlg->m_height	= height ;
	dlg->m_plakaki	= plakaki ;
	dlg->m_plakaki1	= plakaki1 ;
	dlg->m_plakaki2	= plakaki2 ;
	dlg->m_xdist    = xdist ;    cdistX = xdist ;
	dlg->m_ydist    = ydist ;    cdistY = ydist ;
	dlg->m_zdist    = zdist ;    cdistZ = zdist ;
	dlg->m_rot      = rotangle ; cRot   = rotangle ;
	dlg->m_left	    = left_d  ;  cleft  = left_d ; 
	dlg->m_right	= right_d ;  cright = right_d ;
	dlg->m_up   	= up_d ;     cup    = up_d ;
	dlg->m_outlook  = outlook ;  compOut = outlook ;

	dlg->m_objlength = GetObjectLength();

	int res = dlg->DoModal() ;

	if (res == IDOK)   
	{
		sdoc->SaveUndo(); //save scene for undo...

		depth	=	dlg->m_width ;
		height	=	dlg->m_height ;
		plakaki	=	dlg->m_plakaki ;
		plakaki1=	dlg->m_plakaki1 ;
		plakaki2=	dlg->m_plakaki2 ;
		xdist   =   dlg->m_xdist ; 
		ydist   =   dlg->m_ydist ;
		zdist   =   dlg->m_zdist ; 
		rotangle=   dlg->m_rot ;
		left_d  =   dlg->m_left ;
		right_d =   dlg->m_right ;
		up_d    =   dlg->m_up ;
		outlook =   dlg->m_outlook ;

		// set object translation ... 
		/*if ( (fabs(xdist - cdistX) > 0.001) ||
			 (fabs(ydist - cdistY) > 0.001) ||
			 (fabs(zdist - cdistZ) > 0.001) ) 
		{ 
			// absolute x,y,z moving method..............HIDDEN!!!!!!
			//ΘΑ ΧΡΕΙΑΣΤΕΙ ΟΤΑΝ ΘΑ ΓΙΝΕΤΑΙ ΚΙΝΙΣΗ ΑΠ' ΕΥΘΕΙΑΣ ΣΤΟΝ INVENTOR

			//set & save new koryfs 
			Koryfsx[0] = Koryfsx[0] + (xdist - cdistX) ;
      	    Koryfsy[0] = Koryfsy[0] + (ydist - cdistY) ;
		    Koryfsz[0] = Koryfsz[0] + (zdist - cdistZ) ;

			Koryfsx[1] = Koryfsx[1] + (xdist - cdistX) ;
      	    Koryfsy[1] = Koryfsy[1] + (ydist - cdistY) ;
		    Koryfsz[1] = Koryfsz[1] + (zdist - cdistZ) ;

			ObjectToInventor ( root ) ;

			//move all the other children object
		    MoveCarrierObjects((xdist-cdistX),
			                   (ydist-cdistY),
			                   (zdist-cdistZ));
		}
		else
        {*/
          //standart method

          // set x object translation 
		  if (fabs(left_d - cleft) > 0.001)
		  {
		 	x = SetLeftDistance(left_d); 
			goto out;
		  }
		  else  
			  x = GetLeftDistance(); //get the current setting

		  if (fabs(right_d - cright) > 0.001) 
		  {
		    x = SetRightDistance(right_d);
			goto out;
		  }
		  else 
			  x = GetLeftDistance(); //get the current setting
		 

out : ;	  //move...
	      RotateObjectTo(rotangle);
          MoveObjectTo(x,up_d,outlook) ;                      
		/*}*/
    }

	//select it.. ...
  	SoSeparator *wall = sep ;
    sview->GetSelectionNode()->deselectAll();
    if (plakaki=="") sview->GetSelectionNode()->select(wall->getChild(8)) ; //get faceset node
	            else sview->GetSelectionNode()->select(wall->getChild(11)) ;

	return res ;
}



//command for insert walls
void CRoomWall::AddNewObject(SbVec3f p_point, SbVec3f p_normal)
{
		float	len[20], angle[20] ;
		int		toix[20] ;
		int		pleyres ;
		float   myHeight , world_height , room_height ;
		float	fx[20], fy[20], fz[20] ;  //first point array
		float	nx[20], ny[20], nz[20] ;  //next point array 
		float   nrx[20],nry[20],nrz[20] ; //normals array 
		float	vx, vy, vz, len1, len0 ;
		bool    first_time;

		CLib0 lib ;
		CGLib0 *glib = new CGLib0 ;

		// inherited action
	    CGObject::AddNewObject(p_point,p_normal) ;


		//START WALL CONSTUCTION
		int dd =100; //=wall depth ????

		// transfer data from arrays
		len[0] = theApp.l[0] ;
		len[1] = theApp.l[1] ;
		len[2] = theApp.l[2] ;
		len[3] = theApp.l[3] ;
		len[4] = theApp.l[4] ;
		len[5] = theApp.l[5] ;
		len[6] = theApp.l[6] ;
		len[7] = theApp.l[7] ;

		angle[0] = theApp.a[0] ;
		angle[1] = theApp.a[1] ;
		angle[2] = theApp.a[2] ;
		angle[3] = theApp.a[3] ;
		angle[4] = theApp.a[4] ;
		angle[5] = theApp.a[5] ;
		angle[6] = theApp.a[6] ;
		angle[7] = theApp.a[7] ;

		toix[0] = theApp.t[0] ;
		toix[1] = theApp.t[1] ;
		toix[2] = theApp.t[2] ;
		toix[3] = theApp.t[3] ;
		toix[4] = theApp.t[4] ;
		toix[5] = theApp.t[5] ;
		toix[6] = theApp.t[6] ;
		toix[7] = theApp.t[7] ;

		//get wall base height = room height + world height
		CWorldBase *wr = ((CWorldBase*)sdoc->Obj[0]);
		ASSERT(wr);
		world_height = wr->height/2; //../2 because it is half under zero and half up..
		CRoomBase *rb = ((CRoomBase*)sdoc->Obj[1]);
		ASSERT(rb);
		room_height = rb->height;

		myHeight = world_height + room_height;

		//in case of first time of build wall (wizard) 
		first_time = false; 
		//check if first time
		if ((p_point[0]==rb->Koryfsx[0]) && 
			(p_point[1]==rb->Koryfsy[0]) && 
			(p_point[2]==rb->Koryfsz[0]))
		{
			first_time = true;
        }

		//in case of clicking on base ...
		if (p_normal[1]!=0)  //αυτο σημαινει οτι το click εγινε στην βαση
        {
			p_normal[0] = 0;
			p_normal[1] = 0;
			p_normal[2] = 1; //set normal in z axis
        }

		// calculate pleyres
		for ( int i = 0 ; i <= 7 ; i++ )
			if (len[i] == 0) break ;
		pleyres = i + 1 ;


        //calculate points
        for ( i = 0 ; i < pleyres ; i++)
		{
			if (i == 0)
			{
				fx[i] = p_point[0];
				fy[i] = myHeight ;
				fz[i] = p_point[2];

				nrx[i] = p_normal[0];
				nry[i] = p_normal[1];
				nrz[i] = p_normal[2];
			}
			else 
			{
				//check angle....
				fx[i] = nx[i-1] ; 
				fy[i] = ny[i-1] ;
				fz[i] = nz[i-1] ;

				//παιρνω το normal της πλευρας του προηγουμενου τοιχου ...
                glib->GetPolyNormal ( fx[i-1], fy[i-1], fz[i-1],
  			               		      nx[i-1], ny[i-1], nz[i-1],						
					                  nx[i-1], ny[i-1]+100, nz[i-1],
					                 &vx, &vy, &vz ) ;

			    //Συγκοληση σημειων - τοιχων  
			    /*if ((angle[i]>181) && (angle[i]<=360))
				{
                  fx[i] = fx[i] - dd;//(vx * dd) ; 
				  fy[i] = fy[i] ;//(vy * dd) ;
				  fz[i] = fz[i] - dd;//(vz * dd) ;
				}*/
            
				nrx[i] = vx;
				nry[i] = vy;
				nrz[i] = vz; 
			}

			len0 = int(sin((180-angle[i]) * M_PI/180) * len[i]);
			len1 = int(cos((180-angle[i]) * M_PI/180) * len[i]) ;
                
			//προσθεtουμε την μετατοπιση στον αξονα με 1 normal
			nx[i] = fx[i] + (nrx[i] * len0);
			ny[i] = myHeight;
			nz[i] = fz[i] + (nrz[i] * len0);
			//αντιστρεφουμε τα normals των x,z διοτι θελουμε
			//να προσθεσουμε την μετατοπιση στον αξονα με 0 normal 
			//αφαιρουμε απο το nz για ομοιομορφια στους τοιχους
			nx[i] = nx[i] + (nrz[i] * len1);
			ny[i] = myHeight;
			nz[i] = nz[i] - (nrx[i] * len1);
			
		} // for i



        // setup the walls
    	CRoomWall *rw[10] ;

		int off = 0 ;
		for ( i = 0 ; i < pleyres ; i++ )
		{
            if (toix[i] == 0) continue ; 

			rw[off] = new CRoomWall ;

			sdoc->Obj[sdoc->ObjCount] = rw[off] ; 
			sdoc->ObjCount++ ;

			rw[off]->offset = sdoc->ObjCount-1;
			rw[off]->id     = _ROOMWALL_;
			rw[off]->name   = "RoomWall" + lib.inttostr(sdoc->ObjCount-1) ; //name + counter 
			rw[off]->depth	= 100 ;
			rw[off]->height	= 3000 ;           

			//get array data...
    	  	rw[off]->Koryfsx[0] = fx[i];
		    rw[off]->Koryfsy[0] = fy[i];
		    rw[off]->Koryfsz[0] = fz[i];

			rw[off]->Koryfsx[1] = nx[i] ;
			rw[off]->Koryfsy[1] = ny[i] ;
			rw[off]->Koryfsz[1] = nz[i] ;

			rw[off]->ObjectToInventor( sdoc->root ) ;

			//SET ATTRIBUTES...
			//WARNING : επειδη η κατασκευη τοιχων γινεται αυτοματοποιημενα
			//          μεσω wizzard ισχυει ¨:
			//          Ο πρωτος τοιχος εχει carrier το roombase (ή το 
			//          click_point carier για την προσθεση τοιχων μετα)
			//          ενω οι υπολοιποι εχουν τον προηγουμενο τοιχο...**
			//          και η object_side ισουται με την _RIGHT_ πλευρα παντα !!!!

			//set carrier
	        if (off==0) 
			{   
				if (first_time) rw[off]->carrier_id = 1; //=base
				           else	rw[off]->carrier_id = sdoc->obj_selector ;
            }
			else rw[off]->carrier_id = sdoc->ObjCount-2 ;//!!!!! =previous wall 

            //set carrier side
			if (off==0)
			{   
				if (first_time) rw[off]->SetCarrierSide(_TOP_); //top side of base
				           else rw[off]->FindCarrierSide(p_point[0],
							                             p_point[1],
														 p_point[2]);
            }
			else {
			   //** αναλογα με το angle τοποθετειται και το αντικειμενο
			   if ((angle[i]>=0) && (angle[i]<180))  rw[off]->SetCarrierSide(_LEFT_);
			   if ((angle[i]>180) && (angle[i]<=360)) rw[off]->SetCarrierSide(_RIGHT_); 
			   if (/*(angle[i]==0) || (angle[i]==360) ||*/ (angle[i]==180)) //???
				                                     rw[off]->SetCarrierSide(_FRONT_);
			}

			//set object side
			if (off==0) 
			{   
				if (first_time) rw[off]->SetObjectSide(_BACK_); //??BOTTOM 
				           else rw[off]->SetObjectSide(_BACK_);
            }
			else rw[off]->SetObjectSide(_BACK_); 


			//init outlook
    		if ((angle[i]>=0) && (angle[i]<=180)) rw[off]->outlook = 0; 
			                                 else rw[off]->outlook = -dd;//????

			//set rotation
			if ((angle[i]>=0) && (angle[i]<=180)) rw[off]->rotangle  = angle[i];
			                                 else rw[off]->rotangle  = (360 - angle[i]);


			//get totals = το πρωτο σημείο του εγκιβωτισμου
		    rw[off]->totalx  = rw[off]->ssx[0];
		    rw[off]->totaly  = rw[off]->ssy[0];
		    rw[off]->totalz  = rw[off]->ssz[0];

			rw[off]->SaveProperties();

            off++ ;
        }

		sdoc->new_object = _NONE_ ; 
		
		if (!first_time) //else inventor error
        {
		  //GET THE LAST OF WALLS (NEW) OBJECT
		  CRoomWall *w = ((CRoomWall*)sdoc->Obj[sdoc->ObjCount-1]) ;
		  w->SelectObject();
		  sdoc->obj_selector = sdoc->ObjCount-1 ;
        }

		sdoc->SetModifiedFlag();
        sdoc->UpdateAllViews(NULL);
}

  


//********************* move carrier objects *********************
void CRoomWall::MoveCarrierObjects(float dx, float dy, float dz)
{
    int i,selection ;
    SbVec3f vectors;

    selection = offset ;

	//for i=1 και οχι 0 διοτι το worldbase δεν εχει carrier_id
    for (i=1 ; i < sdoc->ObjCount ; i++)
	{
      if (sdoc->Obj[i]!=NULL)
      {
        CGObject *obj = ((CGObject*)sdoc->Obj[i]); //get object

	    if (obj->carrier_id == selection) //if carrier
		{
		   if (obj->IsKindOf(RUNTIME_CLASS(CRoomWall)))
		   {
			 CRoomWall *wal = (CRoomWall *)obj;

			 //update totals
			 wal->totalx  = wal->totalx + dx;
		     wal->totaly  = wal->totaly + dy;
		     wal->totalz  = wal->totalz + dz;

			 //προκειται να ξαναδημιουργηθει ο τοιχος αρα
			 //αλλαζω τισ κορυφες του και με την objecttoinventor
			 //γινεται εγκιβωτισμος εκ' νεου...
			 wal->Koryfsx[0] = wal->Koryfsx[0] + dx ;
       	     wal->Koryfsy[0] = wal->Koryfsy[0] + dy ;
		     wal->Koryfsz[0] = wal->Koryfsz[0] + dz ;

			 wal->Koryfsx[1] = wal->Koryfsx[1] + dx ;
      	     wal->Koryfsy[1] = wal->Koryfsy[1] + dy ;
		     wal->Koryfsz[1] = wal->Koryfsz[1] + dz ;

			 wal->ObjectToInventor ( sdoc->root ) ;

			 //<<<<<<<--------!!!!!!!!----------->>>>>>>>>>
			 //εκτελειται η ιδια ρουτινα μεσα στον εαυτο της για αλλο τοιχιο (RECURSION)
			 wal->MoveCarrierObjects(dx,dy,dz);
           }
		   else        
	       if (obj->IsKindOf(RUNTIME_CLASS(CGExternal)))
		   {
			 CGExternal *ext = (CGExternal *)obj;
			 //update totals
			 ext->totalx  = ext->totalx + dx;
		     ext->totaly  = ext->totaly + dy;
		     ext->totalz  = ext->totalz + dz;

			 ext->GetBox();

			 //INVENTOR:put new translation
	         vectors.setValue(ext->totalx , ext->totaly , ext->totalz);
	         ext->SetTranslation(vectors);
		   }
		}
	  }
	}
}


/********************* Move object **************************/
void CRoomWall::MoveObjectTo(float d1,float d2,float d3)
{
	float pX,pY,pZ ;
	float dX,dY,dZ ;
	float nnx , nny , nnz ;

	//προκειται να ξαναδημιουργηθει ο τοιχος αρα
	//αλλαζω τισ κορυφες του και με την objecttoinventor
	//γινεται εγκιβωτισμος εκ' νεου...

	//save prev values
	pX = Koryfsx[0] ;
	pY = Koryfsy[0] ;
	pZ = Koryfsz[0] ;

	MoveOnCarrier(d1,d2,&Koryfsx[0],&Koryfsy[0],&Koryfsz[0]);

    //add outlook
	GetCarrierNormal(&nnx, &nny, &nnz);
    Koryfsx[0] = Koryfsx[0] + (nnx * d3);
	Koryfsy[0] = Koryfsy[0] + (nny * d3);
	Koryfsz[0] = Koryfsz[0] + (nnz * d3);

    //find diafora
	dX = Koryfsx[0] - pX ;
	dY = Koryfsy[0] - pY ;
	dZ = Koryfsz[0] - pZ ;
   
	//set koryf[1] values
	Koryfsx[1] = Koryfsx[1] + dX ;
    Koryfsy[1] = Koryfsy[1] + dY ;
	Koryfsz[1] = Koryfsz[1] + dZ ;
	//AfxMessageBox(lib.inttostr(nnx)+" "+lib.inttostr(nny)+" "+lib.inttostr(nnz));


	ObjectToInventor(sdoc->root);

	//update totals
	totalx  = ssx[0];
	totaly  = ssy[0];
	totalz  = ssz[0];
	SaveProperties();

	SelectObject();
	ShowRefPoints(150.0); //<<<----------------------- show points

    //move all children objects...  
	MoveCarrierObjects(dX,dY,dZ) ;
}


//********************* rotate carrier objects *********************
//dif_crn = διαφορα νεας με παλαια γωνια
void CRoomWall::RotateCarrierObjects(float dx, float dy, float dz)
{
    int i,father_obj ;
	float len01 , len02, dist ,fnx ,fny ,fnz, pxX0, pyY0, pzZ0, length;
    SbVec3f vectors;
	CLib0 lib;

    father_obj = offset;

	//for i=offset+1 διοτι δεν υπαρχει περιπτωση να αφορα προηγουμενα objs 
    for (i=offset+1 ; i < sdoc->ObjCount ; i++)
	{
      if (sdoc->Obj[i]!=NULL)
      {
        CGObject *obj = ((CGObject*)sdoc->Obj[i]); //get object

	    if (obj->carrier_id == father_obj) //if carrier
		{
		   //προκειται να ξαναδημιουργηθει ο τοιχος αρα
		   //αλλαζω τισ κορυφες του και με την objecttoinventor
		   //γινεται εγκιβωτισμος εκ' νεου...
		   if (obj->IsKindOf(RUNTIME_CLASS(CRoomWall)))
		   {
			 CRoomWall *wal = (CRoomWall *)obj;

			 //calculate carrier's distance to add or sub.....

	    	 //get the carrier reference points
	         //wal->GetCarrierSide();
	         //get the object reference points
	         //wal->GetObjectSide();

			 dist = wal->GetLeftDistance();

             //update totals
			 wal->totalx  = wal->totalx + dx;
		     //wal->totaly  = wal->totaly + dy;
		     wal->totalz  = wal->totalz + dz;

			 //set koryf[0]
			 wal->Koryfsx[0] = wal->Koryfsx[0] + dx ;//- len02;//(fnx * dx) ;
       	     //wal->Koryfsy[0] = wal->Koryfsy[0] + dy + len01;//(fny * dy) ;
		     wal->Koryfsz[0] = wal->Koryfsz[0] + dz ;//- len01;//(fnz * dz) ;

             //set koryf[1]
             //save prev values
	         pxX0 = Koryfsx[1] ;
	         pyY0 = Koryfsy[1] ;
	         pzZ0 = Koryfsz[1] ;

	         //get koryf1 - koryf0 length
	         length = sqrt( (pow( (wal->Koryfsx[1]-wal->Koryfsx[0]), 2)) +
                            (pow( (wal->Koryfsy[1]-wal->Koryfsy[0]), 2)) +
	                        (pow( (wal->Koryfsz[1]-wal->Koryfsz[0]), 2)) );

			 //παιρνω το normal της πλευρας του carrier τοιχου ...
	         wal->GetCarrierNormal(&fnx,&fny,&fnz);

	         len01 = int(sin((180-wal->rotangle) * M_PI/180) * fabs(dist));
			 len02 = int(cos((180-wal->rotangle) * M_PI/180) * fabs(dist));
			 //AfxMessageBox(lib.floattostr(len01));

             //προσθεtουμε την μετατοπιση στον αξονα με 1 normal
	         wal->Koryfsx[1] = wal->Koryfsx[0] + (fnx * len01);
	         //wal->Koryfsy[1] = wal->Koryfsy[1] + (fny * len0);//myHeight;
	         wal->Koryfsz[1] = wal->Koryfsz[0] + (fnz * len01);

	         //αντιστρεφουμε τα normals των x,z διοτι θελουμε
	         //να προσθεσουμε την μετατοπιση στον αξονα με 0 normal 
	         //αφαιρουμε απο το nz για mirroring στους τοιχους
	         wal->Koryfsx[1] = wal->Koryfsx[1] + (fnz * len02);
	         //wal->Koryfsy[1] = wal->Koryfsz[1] + (fny * len1);//myHeight;
	         wal->Koryfsz[1] = wal->Koryfsz[1] - (fnx * len02);


			 wal->ObjectToInventor ( sdoc->root ) ;

			 //<<<<<<<--------!!!!!!!!----------->>>>>>>>>>
			 //εκτελειται η ιδια ρουτινα μεσα στον εαυτο της για αλλο τοιχιο (RECURSION)
			 wal->RotateCarrierObjects((wal->Koryfsx[1]-pxX0),
		                               (wal->Koryfsy[1]-pyY0),
					                   (wal->Koryfsz[1]-pzZ0)) ;
           }
		   else        
	       if (obj->IsKindOf(RUNTIME_CLASS(CGExternal)))
		   {
			 CGExternal *ext = (CGExternal *)obj;
			 //update totals
			 ext->totalx  = ext->totalx + dx;
		     ext->totaly  = ext->totaly + dy;
		     ext->totalz  = ext->totalz + dz;

			 //INVENTOR:put new translation
	         vectors.setValue(ext->totalx , ext->totaly , ext->totalz);
	         ext->SetTranslation(vectors);
		   }
		}
	  }
	}
}


//change corner - rotate object
void CRoomWall::RotateObjectTo(float crn)
{
    float length,cnx,cny,cnz,len0,len1;
	float pxX,pyY,pzZ;
    //CLib0 lib;
	//CGLib0 *glib = new CGLib0 ;

    //προκειται να ξαναδημιουργηθει ο τοιχος αρα
	//αλλαζω τις κορυφες του και με την objecttoinventor
	//γινεται εγκιβωτισμος εκ' νεου...

	//(η κορυφη 0 παραμενει ανεπηρεαστη στην περιστροφη διοτι η περιστροφη γινεται με
	// αξονα αυτη. Αρα και τα total δεν επηρεαζονται)

	//save prev values
	pxX = Koryfsx[1] ;
	pyY = Koryfsy[1] ;
	pzZ = Koryfsz[1] ;

	//get koryf1 - koryf0 length
	length  =  sqrt( (pow( (Koryfsx[1]-Koryfsx[0]), 2)) +
                     (pow( (Koryfsy[1]-Koryfsy[0]), 2)) +
	                 (pow( (Koryfsz[1]-Koryfsz[0]), 2)) );
	//AfxMessageBox(lib.floattostr(length));

	//παιρνω το normal της πλευρας του carrier τοιχου ...
	GetCarrierNormal(&cnx,&cny,&cnz);

	//calculate Koryfs[1] lengths to add..
	len0 = int(sin((180-crn) * M_PI/180) * fabs(length));
	len1 = int(cos((180-crn) * M_PI/180) * fabs(length));
                
	//προσθεtουμε την μετατοπιση στον αξονα με 1 normal
	Koryfsx[1] = Koryfsx[0] + (cnx * len0);
	//Koryfsy[1] = Koryfsy[1] + (cny * len0);//myHeight;
	Koryfsz[1] = Koryfsz[0] + (cnz * len0);

	//αντιστρεφουμε τα normals των x,z διοτι θελουμε
	//να προσθεσουμε την μετατοπιση στον αξονα με 0 normal 
	//αφαιρουμε απο το nz για mirroring στους τοιχους
	Koryfsx[1] = Koryfsx[1] + (cnz * len1);
	//Koryfsy[1] = Koryfsz[1] + (cny * len1);//myHeight;
	Koryfsz[1] = Koryfsz[1] - (cnx * len1);

	//save corner
	rotangle = crn; //save new value to the wall properties

	ObjectToInventor( sdoc->root ) ;

	//move all children objects...  
	RotateCarrierObjects((Koryfsx[1]-pxX),
		                 (Koryfsy[1]-pyY),
					     (Koryfsz[1]-pzZ)) ;

}

//*************** other commands  ****************

//find if other objects is attached to this wall
bool CRoomWall::IsAttachedObject(int wallno)
{
    int objs;
	bool attached = false ;
	int obj_sum = sdoc->ObjCount;

	//for objs=wallno because it is inpossible to have obj attached before this.
	for(objs = wallno;objs < obj_sum ; objs++)
	{
      //WARNING : check for NULL pointers
	  if (sdoc->Obj[objs]!=NULL)
	  {
		//WARNING : the loop must be not check the object himself

        /*if ((sdoc->Obj[objs]->IsKindOf(RUNTIME_CLASS(CRoomWall))) && (objs!=wallno))
        {
          CRoomWall *wall = ((CRoomWall*)sdoc->Obj[objs]);
		  if (wall->carrier_id == wallno ) 
		  {
			  attached = true ;
			  return attached; 
          }
        }*/
		if ((sdoc->Obj[objs]->IsKindOf(RUNTIME_CLASS(CGExternal))) && (objs!=wallno))
        {
          CGExternal *ext = ((CGExternal*)sdoc->Obj[objs]);
		  if (ext->carrier_id == wallno ) 
		  {
			  attached = true ;
			  return attached; 
          }
        }
      }
	}
	return attached ;
}


//delete ...
void CRoomWall::DeleteObject(int aanumber)
{
    CLib0 lib;
	int objs;
	int obj_sum = sdoc->ObjCount;

	//AfxMessageBox(lib.inttostr(aanumber));

	if (IsAttachedObject(aanumber)==false)
    {
        //get deleted (not yet) object
        CRoomWall *delWall = ((CRoomWall*)sdoc->Obj[aanumber]);
        
		//check for walls which use it .. if use it his carrier = base
		for(objs = 1;objs < obj_sum ; objs++)
		{
          //WARNING : check for NULL pointers
	      if (sdoc->Obj[objs]!=NULL)
		  {
		    //WARNING : the loop must be not check the object himself
            if ((sdoc->Obj[objs]->IsKindOf(RUNTIME_CLASS(CRoomWall))) && (objs!=aanumber))
			{
				CRoomWall *wall = ((CRoomWall*)sdoc->Obj[objs]);
		        if (wall->carrier_id == aanumber ) 
				{
                  wall->carrier_id = 1; //base
		          wall->SetCarrierSide(_TOP_); //top side of base
		          wall->SetObjectSide(_BOTTOM_); //bottom side of wall
		          wall->outlook = 0;
		          wall->rotangle = 0; 
                }
			}
          }
		}

		//deselect ...
	    sview->GetSelectionNode()->deselectAll();
		sdoc->obj_selector=-1;

        //delete object from inventor...
		SoSeparator *myroot = sdoc->root;
		SoSeparator *del_wall;
        SbName myname = "RoomWall"+lib.inttostr(aanumber) ; 
		del_wall = (SoSeparator *)SoNode::getByName(myname);
		myroot->removeChild(del_wall);

		//delete object from Object array
	    sdoc->Obj[aanumber]=NULL;

     }
	 else
		 AfxMessageBox("          Access denied.\n Other object(s) use this object.");
}


//copy ...
void CRoomWall::CopyObject(int aanumber)
{
        //just save aanumber=copied object
		sdoc->LastCopy = aanumber;
}

//paste ...
void CRoomWall::PasteObject()
{	    
	   //CLib0 lib;
	   float walldist;
   
	   //just get copied wall distance and angle=corner and add new wall

       //get copied object
       CRoomWall *copiedWall = ((CRoomWall*)sdoc->Obj[sdoc->LastCopy]);

       //zero data arrays
	   for (int i=0;i<8;i++)
	   {
		   theApp.l[i]=0;
		   theApp.a[i]=0;
		   theApp.t[i]=0;
       }

       //set data
	   //wall distance is between koryf0 and koryf1
       walldist =  sqrt( (pow( (copiedWall->Koryfsx[1] - copiedWall->Koryfsx[0]), 2)) +
                         (pow( (copiedWall->Koryfsy[1] - copiedWall->Koryfsy[0]), 2)) +
		                 (pow( (copiedWall->Koryfsz[1] - copiedWall->Koryfsz[0]), 2)) );

	   theApp.l[0]=walldist;
	   theApp.a[0]=copiedWall->rotangle;
	   theApp.t[0]=1;

       sdoc->new_object =_ROOMWALL_ ;

	   //AfxMessageBox(lib.floattostr(walldist));
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
	m_xdist = 0.0f;
	m_ydist = 0.0f;
	m_zdist = 0.0f;
	m_rot = 0.0f;
	m_left = 0.0f;
	m_right = 0.0f;
	m_up = 0.0f;
	m_objlength = 0.0f;
	m_outlook = 0.0f;
	//}}AFX_DATA_INIT
}


void CRoomWallPro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomWallPro)
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDV_MinMaxFloat(pDX, m_height, 0.f, 10000.f);
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDX_Text(pDX, IDC_PLAKAKI, m_plakaki);
	DDX_Text(pDX, IDC_PLAKAKI1, m_plakaki1);
	DDX_Text(pDX, IDC_PLAKAKI2, m_plakaki2);
	DDX_Text(pDX, IDC_XDIST, m_xdist);
	DDX_Text(pDX, IDC_YDIST, m_ydist);
	DDV_MinMaxFloat(pDX, m_ydist, 0.f, 10000.f);
	DDX_Text(pDX, IDC_ZDIST, m_zdist);
	DDX_Text(pDX, IDC_ROT, m_rot);
	DDV_MinMaxFloat(pDX, m_rot, 0.f, 180.f);
	DDX_Text(pDX, IDC_LeftDIST, m_left);
	DDX_Text(pDX, IDC_RightDIST, m_right);
	DDX_Text(pDX, IDC_UP, m_up);
	DDV_MinMaxFloat(pDX, m_up, 0.f, 10000.f);
	DDX_Text(pDX, IDC_OBJLEN, m_objlength);
	DDX_Text(pDX, IDC_OUTLOOK, m_outlook);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRoomWallPro, CDialog)
	//{{AFX_MSG_MAP(CRoomWallPro)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomWallPro message handlers
