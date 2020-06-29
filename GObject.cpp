// GObject.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"
#include "SYNTHDoc.h"
#include "SYNTHView.h"
#include "lib0.h"
#include "GObject.h"

#include "GExternal.h"
#include "RoomBase.h"
#include "RoomWall.h"
#include "WorldBase.h"

#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoRotation.h>

/////////////////////////////////////////////////////////////////////////////
// CGObject

IMPLEMENT_DYNAMIC( CGObject, CObject )

CGObject::CGObject()
{
	carrier_id   = -1; //init with invalid values
	carrier_side = -1; 
	object_side  = -1; 
	outlook = 0;


	totalx = totaly = totalz = 0; //init totals
}

CGObject::~CGObject()
{
}

void CGObject::ObjectToInventor ( SoSeparator *root ) 
{
}

void CGObject::SaveProperties() 
{
	CLib0 lib ;
	CString soff = lib.inttostr(offset) ;

/*
    //save id & offest
	lib.setSoSFIntProp ( attr, SbName("offset"+soff), offset ) ;
	lib.setSoSFIntProp ( attr, SbName("id"+soff), id ) ;

    //save type of object global refernce point...
	lib.setSoSFIntProp ( attr, "refpoint", object_refpoint ) ;
    //....save the values 
	lib.setSoSFFloatProp ( attr, "totalx", totalx ) ;
	lib.setSoSFFloatProp ( attr, "totaly", totaly ) ;
	lib.setSoSFFloatProp ( attr, "totalz", totalz ) ;

    //save box values

    // BASE PONTS
    lib.setSoSFFloatProp ( attr, SbName("ssx0"+soff), ssx[0] ) ;
    lib.setSoSFFloatProp ( attr, SbName("ssy0"+soff), ssy[0] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssz0"+soff), ssz[0] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssx1"+soff), ssx[1] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssy1"+soff), ssy[1] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssz1"+soff), ssz[1] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssx2"+soff), ssx[2] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssy2"+soff), ssy[2] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssz2"+soff), ssz[2] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssx3"+soff), ssx[3] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssy3"+soff), ssy[3] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssz3"+soff), ssz[3] ) ;

    // UP POINTS
	lib.setSoSFFloatProp ( attr, SbName("ssx4"+soff), ssx[4] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssy4"+soff), ssy[4] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssz4"+soff), ssz[4] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssx5"+soff), ssx[5] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssy5"+soff), ssy[5] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssz5"+soff), ssz[5] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssx6"+soff), ssx[6] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssy6"+soff), ssy[6] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssz6"+soff), ssz[6] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssx7"+soff), ssx[7] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssy7"+soff), ssy[7] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ssz7"+soff), ssz[7] ) ;


    //common object attribures
    lib.setSoSFIntProp ( attr, SbName("carrier"+soff), carrier_id ) ;
	lib.setSoSFIntProp ( attr, SbName("carrierSide"+soff), carrier_side ) ;
    lib.setSoSFIntProp ( attr, SbName("objectSide"+soff), object_side ) ;
	lib.setSoSFIntProp ( attr, SbName("outlook"+soff), outlook ) ;
	lib.setSoSFFloatProp ( attr, SbName("rotangle"+soff), rotangle ) ;
*/
}

void CGObject::InventorToObject ( SoSeparator *root ) 
{
	CLib0 lib ;
	CString soff = lib.inttostr(offset) ;

/*	//restore id & offset
	offset    = lib.getSoSFIntProp(SbName("offset"+soff)) ;
	id	      = lib.getSoSFIntProp(SbName("id"+soff)) ;

	//restore obj ref point type
	object_refpoint  = lib.getSoSFIntProp("refpoint") ;
    //restore values
	totalx    = lib.getSoSFFloatProp("totalx") ;
	totaly    = lib.getSoSFFloatProp("totaly") ;
	totalz    = lib.getSoSFFloatProp("totalz") ;

	//restore box data
	// BASE POINTS
	ssx[0] = lib.getSoSFFloatProp(SbName("ssx0"+soff)) ;
	ssy[0] = lib.getSoSFFloatProp(SbName("ssy0"+soff)) ;
	ssz[0] = lib.getSoSFFloatProp(SbName("ssz0"+soff)) ;
	ssx[1] = lib.getSoSFFloatProp(SbName("ssx1"+soff)) ;
	ssy[1] = lib.getSoSFFloatProp(SbName("ssy1"+soff)) ;
	ssz[1] = lib.getSoSFFloatProp(SbName("ssz1"+soff)) ;
	ssx[2] = lib.getSoSFFloatProp(SbName("ssx2"+soff)) ;
	ssy[2] = lib.getSoSFFloatProp(SbName("ssy2"+soff)) ;
	ssz[2] = lib.getSoSFFloatProp(SbName("ssz2"+soff)) ;
	ssx[3] = lib.getSoSFFloatProp(SbName("ssx3"+soff)) ;
	ssy[3] = lib.getSoSFFloatProp(SbName("ssy3"+soff)) ;
	ssz[3] = lib.getSoSFFloatProp(SbName("ssz3"+soff)) ;

    // UP POINTS
	ssx[4] = lib.getSoSFFloatProp(SbName("ssx4"+soff)) ;
	ssy[4] = lib.getSoSFFloatProp(SbName("ssy4"+soff)) ;
	ssz[4] = lib.getSoSFFloatProp(SbName("ssz4"+soff)) ;
	ssx[5] = lib.getSoSFFloatProp(SbName("ssx5"+soff)) ;
	ssy[5] = lib.getSoSFFloatProp(SbName("ssy5"+soff)) ;
	ssz[5] = lib.getSoSFFloatProp(SbName("ssz5"+soff)) ;
	ssx[6] = lib.getSoSFFloatProp(SbName("ssx6"+soff)) ;
	ssy[6] = lib.getSoSFFloatProp(SbName("ssy6"+soff)) ;
	ssz[6] = lib.getSoSFFloatProp(SbName("ssz6"+soff)) ;
	ssx[7] = lib.getSoSFFloatProp(SbName("ssx7"+soff)) ;
	ssy[7] = lib.getSoSFFloatProp(SbName("ssy7"+soff)) ;
	ssz[7] = lib.getSoSFFloatProp(SbName("ssz7"+soff)) ;

	//common object attributes
	carrier_id	= lib.getSoSFIntProp(SbName("carrier"+soff)) ;
	carrier_side= lib.getSoSFIntProp(SbName("carrierSide"+soff)) ;
	object_side = lib.getSoSFIntProp(SbName("objectSide"+soff)) ;
	outlook  	= lib.getSoSFIntProp(SbName("outlook"+soff)) ;
	rotangle	= lib.getSoSFFloatProp(SbName("rotangle"+soff)) ;
*/
}

void CGObject::GetBox()
{
}

int CGObject::EditProperties ( CDocument *d, SoSeparator *root ) 
{
	return IDOK ;
}

void CGObject::AddNewObject(SbVec3f p_point,SbVec3f p_normal)
{
}

//****************  ARRAY MANIPULATION COMMANDS  ******************
//Array routines
bool CGObject::IsArrayEqual(const int src[4], int dst[4])
{
	bool state;
	for (int i=0;i<4;i++)
      if (src[i]==dst[i]) state = true;
	                 else return false;
	return state;
}

void CGObject::ArrayEqual(const int src[4], int dst[4])
{
	for (int i=0;i<4;i++)
             (dst[i]=src[i]);
}

void CGObject::ZeroArray(int arr[4])
{
	for (int i=0;i<4;i++)
               (arr[i]=0);
}

//reverce the array [a,b,c,d] = [b,a,d,c]
void CGObject::ReverceArray(int dst[4])
{
  int r;

  r = dst[0];
  dst[0] = dst[1];
  dst[1] = r;

  r = dst[2];
  dst[2] = dst[3];
  dst[3] = r;
}

//reverce the array [a,b,c,d] = [b,c,d,a]
void CGObject::ReverceArray2(int dst[4])
{
  int r;

  r = dst[0];      //1st a,b,c,d = b,a,c,d
  dst[0] = dst[1];
  dst[1] = r;

  r = dst[1];      //2nd b,a,c,d = b,c,a,d 
  dst[1] = dst[2];
  dst[2] = r;

 /* r = dst[2];      //3rd b,c,a,d = b,c,d,a
  dst[2] = dst[3];
  dst[3] = r;*/
}

//*******************   MATH ROUTINES   ********************

//convert mire to radians and opposite...
float CGObject::RadiansToDegrees(float r)
{
   float degrees;

   degrees = (360 / (2*M_PI)) * r ;

   return degrees ;
}

float CGObject::DegreesToRadians(float m)
{
   float rads;

   rads = m * ((2*M_PI) / 360 );

   return rads ;
}

//get from a vector AB the normal (..by a rotation axis) 
//rXYZ = rotation axis
CGObject::GetVectorNormal(float Ax,float Ay,float Az,
                          float Bx,float By,float Bz,
						  float rX,float rY,float rZ,
						  float *nx,float *ny,float *nz)
{
    float Cx,Cy,Cz; 
	float outx,outy,outz;
	CGLib0 *glib = new CGLib0 ;
	
	//get the virtual point C on rotaxis
	Cx = Ax + rX;
	Cy = Ay + rY;
	Cz = Az + rZ;

	//get the normal of ABC
    glib->GetPolyNormal ( Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Cz, &outx,&outy,&outz ) ;

	*nx = outx;
	*ny = outy;
	*nz = outz;

	return 0;
}


//****************** INVENTOR OBJECT COMMANDS *************************

//make object visible 
void CGObject::MakeObjVisible()
{
     //make object invisible and unpickable
	 
	 //set draw style
	 SoDrawStyle	*ds = (SoDrawStyle *)sep->getChild(1) ;
     ds->style = SoDrawStyle::FILLED  ;
	 //set pick style
	 SoPickStyle *ps = (SoPickStyle *)sep->getChild(2) ;
     ps->style.setValue(SoPickStyle::SHAPE) ;
}

//make object invisible
void CGObject::MakeObjInvisible()
{
     //make object invisible and unpickable
	 
	 //set draw style
	 SoDrawStyle	*ds = (SoDrawStyle *)sep->getChild(1) ;
     ds->style = SoDrawStyle::INVISIBLE  ;
	 //set pick style
	 SoPickStyle *ps = (SoPickStyle *)sep->getChild(2) ;
     ps->style.setValue(SoPickStyle::UNPICKABLE) ;
}

//get object translation
SbVec3f CGObject::GetTranslation()
{
    SbVec3f vals ;

    SoTransform *trans = (SoTransform *)sep->getChild(0) ;
    vals = trans->translation.getValue();

	return vals ;
}

//set object translation
void CGObject::SetTranslation(SbVec3f vals)
{
    SoTransform *trans = (SoTransform *)sep->getChild(0) ;
	trans->translation	= vals;
}


//get the rotation angle... (return radians)
float CGObject::GetRotationAngle()
{
    SbVec3f Rotaxis ;
	float Rotangle ;

	SoTransform *tr = (SoTransform *)sep->getChild(0) ;    	   
    tr->rotation.getValue(Rotaxis , Rotangle); //get object rotation values

	return Rotangle ;
}

//set the rotation angle ... (return radians)
void CGObject::SetRotationAngle(float angle)
{
    SbVec3f Rotaxis ; 
	float Rotangle ;

	SoTransform *tr = (SoTransform *)sep->getChild(0) ;
	tr->rotation.getValue(Rotaxis , Rotangle);//<<<<<---- δεν παιρνει το rotaxis ???

	SbRotation *sbrot = new SbRotation(SbVec3f(0,1,0)/*Rotaxis*/,angle) ;//<<<<<----????
	tr->rotation.setValue(*sbrot) ;

}

//get the rotation axis...
SbVec3f CGObject::GetRotationAxis()
{
    SbVec3f Rotaxis ;
	float Rotangle ;

	SoTransform *tr = (SoTransform *)sep->getChild(0) ;  	   
    tr->rotation.getValue(Rotaxis , Rotangle); 

	return Rotaxis ;
}

//set the rotation axis ...
void CGObject::SetRotationAxis(SbVec3f axis)
{
    SbVec3f Rotaxis ;
	float Rotangle ;

	SoTransform *tr = (SoTransform *)sep->getChild(0) ;
    tr->rotation.getValue(Rotaxis , Rotangle);

	//set new rotation axis
	SbRotation *sbrot = new SbRotation(axis,Rotangle) ;
    tr->rotation.setValue(*sbrot) ;

	//update object rot axis...
	obj_raxisX = axis[0];
	obj_raxisY = axis[1];
	obj_raxisZ = axis[2];
}

//set the rotation axis and the angle...
void CGObject::SetObjRotation(int axonas,float angle)
{
	SoTransform *tr	= (SoTransform *)sep->getChild(0) ;
	SbRotation *sbrot = new SbRotation;

	switch (axonas)
	{
  	  case _X_ : sbrot->setValue(SbVec3f(1.,0.,0.),DegreesToRadians(angle));
	  case _Y_ : sbrot->setValue(SbVec3f(0.,1.,0.),DegreesToRadians(angle));
	  case _Z_ : sbrot->setValue(SbVec3f(0.,0.,1.),DegreesToRadians(angle));
    }
	tr->rotation.setValue(*sbrot) ;
}

//change the center of the object (rotation center)
void CGObject::SetObjectCenter(int cpoint)
{
   SbVec3f center;

   SoTransform *tr	= (SoTransform *)sep->getChild(0) ;

   tr->recenter(SbVec3f(0,0,0)); //reset to default

   switch (cpoint)
   {
      case _BKLEFT_ : center.setValue(0,0,0);                     break; //left back point = default
	  case _FRLEFT_ : center.setValue(0,0,GetBoxLength(_WIDTH_)); break; //left front point
	  case _BKRIGHT_: center.setValue(GetBoxLength(_LENGTH_),0,0);break; //right front point
	  case _FRRIGHT_: center.setValue(GetBoxLength(_LENGTH_),0,
				                      GetBoxLength(_WIDTH_));     break; //right back point
	  case _CENTER_ : center.setValue(GetBoxLength(_LENGTH_)/2,
				                      GetBoxLength(_HEIGHT_)/2,
					        		  GetBoxLength(_WIDTH_)/2);   break; //box center
	  default: center.setValue(0,0,0);                            break;
   }
   tr->recenter(center); 
}

//get the object's rotation matrix
SbMatrix CGObject::GetObjectMatrix()
{   
    SbVec3f Raxis ;
	float Rangle ;
	SbMatrix matrix;

	SoTransform *tr = (SoTransform *)sep->getChild(0) ;
	tr->rotation.getValue(Raxis , Rangle); 

	SbRotation *sbrot = new SbRotation(Raxis , Rangle); 
	sbrot->getValue(matrix); 

	return matrix;
}

//get the side object vector
SbVec3f CGObject::GetObjectVector()
{
	SbVec3f p1 , p2, dianisma ;
    int refp[4];

    switch (object_side)
    {
      case _FRONT_ : ArrayEqual(front ,refp); break;
	  case _RIGHT_ : ArrayEqual(right ,refp); break;
	  case _BACK_  : ArrayEqual(back  ,refp); break; 
	  case _LEFT_  : ArrayEqual(left  ,refp); break; 
      case _TOP_   : ArrayEqual(top   ,refp); break;
      case _BOTTOM_: ArrayEqual(bottom,refp); break;
    }

	p1.setValue(ssx[refp[0]],ssy[refp[0]],ssz[refp[0]]);
	p2.setValue(ssx[refp[1]],ssy[refp[1]],ssz[refp[1]]);

	dianisma = p2-p1;
			   
	return dianisma ;
}

//get object direction .. multiply vector by a matrix
SbVec3f CGObject::GetObjectDirection(SbVec3f source)
{
	SbMatrix mymatrix;
	SbVec3f target ;

	//multiply dianisma by matrix 
	mymatrix = GetObjectMatrix();
    mymatrix.multDirMatrix(source , target);

	return target ;
}

//get the normals internal corner
float CGObject::GetNormalsCorner(float x1,float y1,float z1,
					             float x2,float y2,float z2)
{
	SbVec3f axis;
	float angle,corner;

    SbRotation *sbrot = new SbRotation(SbVec3f(x1,y1,z1),SbVec3f(x2,y2,z2));
	SoRotation *r = new SoRotation;
	r->rotation.setValue(*sbrot) ;
	r->rotation.getValue(axis , angle);

	//get the normals internal corner ....
	corner = RadiansToDegrees(angle); 

	return corner;
}

//show carrier ref points as balls
void CGObject::ShowCarrierRefPoints(float sizeofpoints)
{
	int refp[4];
    int mycarrier = carrier_id;
    int myside = carrier_side;

    //get object's carrier
    CGObject *obj = ((CGObject*)sdoc->Obj[mycarrier]);

    switch (myside)
	{
        case _FRONT_ : ArrayEqual(front ,refp); break;
	    case _RIGHT_ : ArrayEqual(right ,refp); break;
	    case _BACK_  : ArrayEqual(back  ,refp); ReverceArray(refp); break; 
	    case _LEFT_  : ArrayEqual(left  ,refp); break; 
        case _TOP_   : ArrayEqual(top   ,refp); ReverceArray2(refp); break;
        case _BOTTOM_: ArrayEqual(bottom,refp); break;
	}

	SoSeparator *myroot = sdoc->root;
    
	//delete previous reference points from inventor...
	SoSeparator *prevref;
    SbName name = "Carrier_Points"; 
	prevref = (SoSeparator *)SoNode::getByName(name);
	if (prevref!=NULL) myroot->removeChild(prevref);

	if ((offset>0) && (myside!=_NOWHERE_)) //no worldbase 
    {
	  if (theApp.ShowRefPoints) //if true.. show reference points
	  {
	    //create the new reference points 
        SoSeparator *ref = new SoSeparator ;

        for (int i = 0 ; i < 3 ; i++)
		{
	      SoSeparator *mysep = new SoSeparator ;

          //setup transform
	      SoTransform *trans	= new SoTransform ;
          //put new translation
	      trans->translation.setValue(obj->ssx[refp[i]],
		                              obj->ssy[refp[i]],
			    					  obj->ssz[refp[i]]);

	      //setup draw style
	      SoDrawStyle *ds = new SoDrawStyle ;
	      ds->style = SoDrawStyle::FILLED ;

	      //init pick style
	      SoPickStyle *ps = new SoPickStyle;
          ps->style.setValue(SoPickStyle::UNPICKABLE) ;

	      mysep->addChild( trans ) ;
          mysep->addChild( ds );	
	      mysep->addChild( ps ) ;

	      // setup shape
	      SoSphere *sphere = new SoSphere ;
	      sphere->radius = sizeofpoints ;   //<<<--- size
	
	      // setup material
	      SoMaterial  *mat = new SoMaterial;
	      mat->diffuseColor.setValue( 1., 0., 0. ); 

          // setup graph
	      mysep->addChild( mat );	
	      mysep->addChild( sphere );

	      ref->addChild( mysep );
		}
	    ref->setName("Carrier_Points") ;  // set node name

	    myroot->addChild( ref );
	  }
	} //if ...
}

//show object ref points as balls
void CGObject::ShowObjectRefPoints(float sizeofpoints)
{
	int refp[4];

    switch (object_side)
	{
        case _FRONT_ : ArrayEqual(front ,refp); break;
	    case _RIGHT_ : ArrayEqual(right ,refp); break;
	    case _BACK_  : ArrayEqual(back  ,refp); break; 
	    case _LEFT_  : ArrayEqual(left  ,refp); break; 
        case _TOP_   : ArrayEqual(top   ,refp); break;
        case _BOTTOM_: ArrayEqual(bottom,refp); break;
	}

	SoSeparator *myroot = sdoc->root;
    
	//delete previous reference points from inventor...
	SoSeparator *prevref;
    SbName name = "Object_Points"; 
	prevref = (SoSeparator *)SoNode::getByName(name);
	if (prevref!=NULL) myroot->removeChild(prevref);

	if ((offset>0) && (object_side!=_NOWHERE_)) //no worldbase
	{
	  if (theApp.ShowRefPoints) //if true.. show reference points
	  {
        //create the new reference points 
        SoSeparator *ref = new SoSeparator ;

        for (int i = 0 ; i < 3 ; i++)
		{
	      SoSeparator *mysep = new SoSeparator ;

          //setup transform
	      SoTransform *trans	= new SoTransform ;
          //put new translation
	      trans->translation.setValue(ssx[refp[i]],
       	                              ssy[refp[i]],
		      					      ssz[refp[i]]);

	      //setup draw style
	      SoDrawStyle *ds = new SoDrawStyle ;
	      ds->style = SoDrawStyle::FILLED ;

	      //init pick style
	      SoPickStyle *ps = new SoPickStyle;
          ps->style.setValue(SoPickStyle::UNPICKABLE) ;

	      mysep->addChild( trans ) ;
          mysep->addChild( ds );	
	      mysep->addChild( ps ) ;

	      // setup shape
	      SoSphere *sphere = new SoSphere ;
	      sphere->radius = sizeofpoints ;   //<<<--- size
	
	      // setup material
	      SoMaterial  *mat = new SoMaterial;
	      mat->diffuseColor.setValue( 0., 0.5, 0.5 ); 

          // setup graph
	      mysep->addChild( mat );	
	      mysep->addChild( sphere );

	      ref->addChild( mysep );
		}
	    ref->setName("Object_Points") ;  // set node name

	    myroot->addChild( ref );
	  }
	}//if...
}


//show object box points as balls
void CGObject::ShowBoxPoints(float sizeofpoints)
{
	SoSeparator *myroot = sdoc->root;
    
	//delete previous box from inventor...
	SoSeparator *prevbox;
    SbName name = "Box_Points"; 
	prevbox = (SoSeparator *)SoNode::getByName(name);
	if (prevbox!=NULL) myroot->removeChild(prevbox);

	if (theApp.ShowRefPoints) //if true.. show reference points
	{
	  //create the new box of points 
      SoSeparator *ref = new SoSeparator ;

      for (int i = 0 ; i < 8 ; i++)
	  {
	    SoSeparator *mysep = new SoSeparator ;

        //setup transform
	    SoTransform *trans	= new SoTransform ;
        //put new translation
	    trans->translation.setValue(ssx[i],ssy[i],ssz[i]);

	    //setup draw style
	    SoDrawStyle *ds = new SoDrawStyle ;
	    ds->style = SoDrawStyle::FILLED ;

	    //init pick style
	    SoPickStyle *ps = new SoPickStyle;
        ps->style.setValue(SoPickStyle::UNPICKABLE) ;

	    mysep->addChild( trans ) ;
        mysep->addChild( ds );	
	    mysep->addChild( ps ) ;

	    // setup shape
	    SoSphere *sphere = new SoSphere ;
	    sphere->radius = sizeofpoints ;   //<<<--- size
	
	    // setup material
	    SoMaterial  *mat = new SoMaterial;
	    mat->diffuseColor.setValue( 1., 0., 0. ); 

        // setup graph
	    mysep->addChild( mat );	
	    mysep->addChild( sphere );

	    ref->addChild( mysep );
	  }
	  ref->setName("Box_Points") ;  // set node name

	  myroot->addChild( ref );
	}
}


//show translation point as ball
void CGObject::ShowTotalPoint(float sizeofpoints)
{
	SoSeparator *myroot = sdoc->root;
    
	//delete previous box from inventor...
	SoSeparator *prevtot;
    SbName name = "Total_Point"; 
	prevtot = (SoSeparator *)SoNode::getByName(name);
	if (prevtot!=NULL) myroot->removeChild(prevtot);

	if (theApp.ShowRefPoints) //if true.. show reference points
	{
	  //get total
	  SbVec3f tot = GetTranslation();

	  //create the point 
      SoSeparator *ref = new SoSeparator ;

	  SoSeparator *mysep = new SoSeparator ;

      //setup transform
	  SoTransform *trans	= new SoTransform ;
      //put new translation
	  trans->translation.setValue(/*tot[0],tot[1],tot[2]*/totalx,totaly,totalz);

	  //setup draw style
	  SoDrawStyle *ds = new SoDrawStyle ;
	  ds->style = SoDrawStyle::FILLED ;

	  //init pick style
	  SoPickStyle *ps = new SoPickStyle;
      ps->style.setValue(SoPickStyle::UNPICKABLE) ;

	  mysep->addChild( trans ) ;
      mysep->addChild( ds );	
	  mysep->addChild( ps ) ;

	  // setup shape
	  SoSphere *sphere = new SoSphere ;
	  sphere->radius = sizeofpoints ;   //<<<--- size
	
	  // setup material
	  SoMaterial  *mat = new SoMaterial;
	  mat->diffuseColor.setValue( 1., 1., 0. ); 

      // setup graph
	  mysep->addChild( mat );	
	  mysep->addChild( sphere );

	  ref->addChild( mysep );

	  ref->setName("Total_Point") ;  // set node name

	  myroot->addChild( ref );
	}
}

//show custom points
void CGObject::ShowCustomPoints(float sizeofpoints,
								float x1,float y1,float z1,
								float x2,float y2,float z2,
								float x3,float y3,float z3)
{
	float xp[3];
	float yp[3];
	float zp[3];

    xp[0] = x1; xp[1] = x2; xp[2] = x3;
    yp[0] = y1; yp[1] = y2; yp[2] = y3;
	zp[0] = z1; zp[1] = z2; zp[2] = z3;

	SoSeparator *myroot = sdoc->root;
    
	//delete previous reference points from inventor...
	SoSeparator *prevref;
    SbName name = "Custom_Points"; 
	prevref = (SoSeparator *)SoNode::getByName(name);
	if (prevref!=NULL) myroot->removeChild(prevref);

//	if (theApp.ShowRefPoints) //if true.. show reference points
//	{
        //create the new reference points 
        SoSeparator *ref = new SoSeparator ;

        for (int i = 0 ; i < 3 ; i++)
		{
	      SoSeparator *mysep = new SoSeparator ;

          //setup transform
	      SoTransform *trans	= new SoTransform ;
          //put new translation
	      trans->translation.setValue(xp[i],yp[i],zp[i]);

	      //setup draw style
	      SoDrawStyle *ds = new SoDrawStyle ;
	      ds->style = SoDrawStyle::FILLED ;

	      //init pick style
	      SoPickStyle *ps = new SoPickStyle;
          ps->style.setValue(SoPickStyle::UNPICKABLE) ;

	      mysep->addChild( trans ) ;
          mysep->addChild( ds );	
	      mysep->addChild( ps ) ;

	      // setup shape
	      SoSphere *sphere = new SoSphere ;
	      sphere->radius = sizeofpoints ;   //<<<--- size
	
	      // setup material
	      SoMaterial  *mat = new SoMaterial;
	      mat->diffuseColor.setValue( 0., 0.5, 0.5 ); 

          // setup graph
	      mysep->addChild( mat );	
	      mysep->addChild( sphere );

	      ref->addChild( mysep );
		}
	    ref->setName("Custom_Points") ;  // set node name

	    myroot->addChild( ref );
//	}//if...
}

void CGObject::ShowRefPoints(float size)
{
	ShowCarrierRefPoints(size);
	//ShowObjectRefPoints(size);
	ShowBoxPoints(size);
	ShowTotalPoint(size);
}

///select object
void CGObject::SelectObject()
{
	int child_no = -1 ; //init with invalid val

	switch (id)
	{
	   case _EXTERNAL_          : child_no = 4;  break; //Geometry node
	   case _ROOMWALL_          : child_no = 8;  break; //faceset node
	   //case ROOMBASE no need
	   //case WORLDBASE no need
	}
	if (child_no!=-1)
	{
	  sview->GetSelectionNode()->deselectAll(); //first deselect all...
	  sview->GetSelectionNode()->select(sep->getChild(child_no)) ; //after select
	}
	else
		AfxMessageBox("Invalid selection");
}

/*************************  SYNTHESIS COMMON ROUTINES   **********************/

//get - set the object's carrier side
void CGObject::SetCarrierSide(int side)
{
   carrier_side = side ;
}

//return the ref points of carrier
void CGObject::GetCarrierSide()
{
   int refp[4];
   int mycarrier = carrier_id;

   //get object's carrier
   CGObject *obj = ((CGObject*)sdoc->Obj[mycarrier]);

   switch (carrier_side)
   {
      case _FRONT_ : ArrayEqual(front ,refp); break;
	  case _RIGHT_ : ArrayEqual(right ,refp); break;
	  case _BACK_  : ArrayEqual(back  ,refp); ReverceArray(refp); break; 
	  case _LEFT_  : ArrayEqual(left  ,refp); break; 
      case _TOP_   : ArrayEqual(top   ,refp); ReverceArray2(refp); break;
      case _BOTTOM_: ArrayEqual(bottom,refp); break;
   }


   pointX1 = obj->ssx[refp[0]] ;
   pointY1 = obj->ssy[refp[0]] ;
   pointZ1 = obj->ssz[refp[0]] ;

   pointX2 = obj->ssx[refp[1]] ;
   pointY2 = obj->ssy[refp[1]] ;
   pointZ2 = obj->ssz[refp[1]] ;

   pointX3 = obj->ssx[refp[2]] ;
   pointY3 = obj->ssy[refp[2]] ;
   pointZ3 = obj->ssz[refp[2]] ;

}


//set /get objects side
void CGObject::SetObjectSide(int side)
{

   object_side = side ;

   //does not have any effect on walls... just set the object side
   switch (side)
   {
      case _BACK_  : outlook = 0;                  //=default side (standart for walls)
		             object_refpoint = _DNBKLEFT_;
					 rotangle+= 0; 
					 break;
      case _LEFT_  : outlook = 0;
		             object_refpoint = _DNFRLEFT_;
					 rotangle+= 270;
					 break;
	  case _FRONT_ : outlook = GetBoxLength(_WIDTH_);
		             object_refpoint = _DNFRRIGHT_;
					 rotangle+= 180;
					 break;
	  case _RIGHT_ : outlook = GetBoxLength(_LENGTH_); 
		             object_refpoint = _DNBKRIGHT_;
					 rotangle+= 90;
					 break;
	  case _TOP_   : outlook = 0;//GetBoxLength(_HEIGHT_);
		             object_refpoint = _UPBKLEFT_;
					 rotangle+= 45;//90; 
					 break;
      case _BOTTOM_: outlook = 0;
		             object_refpoint = _DNFRLEFT_;
					 rotangle+= 45;//270;
					 break;
      case _NOWHERE_:outlook = 0; //just zero
		             object_refpoint = _UNDEFINED_;
					 rotangle = 0;
		             break; 
   }
   if (rotangle>360) rotangle = (rotangle - 360); //fixing...
}

//return the objects ref points
void CGObject::GetObjectSide()
{
   int refp[4];

   switch (object_side)
   {
      case _FRONT_ : ArrayEqual(front ,refp); break;
	  case _RIGHT_ : ArrayEqual(right ,refp); break;
	  case _BACK_  : ArrayEqual(back  ,refp); break; 
	  case _LEFT_  : ArrayEqual(left  ,refp); break; 
      case _TOP_   : ArrayEqual(top   ,refp); break;
      case _BOTTOM_: ArrayEqual(bottom,refp); break;
   }


   obj_pointX1 = ssx[refp[0]] ;
   obj_pointY1 = ssy[refp[0]] ;
   obj_pointZ1 = ssz[refp[0]] ;

   obj_pointX2 = ssx[refp[1]] ;
   obj_pointY2 = ssy[refp[1]] ;
   obj_pointZ2 = ssz[refp[1]] ;

   obj_pointX3 = ssx[refp[2]] ;
   obj_pointY3 = ssy[refp[2]] ;
   obj_pointZ3 = ssz[refp[2]] ;

}

//get the normal of the active side
CGObject::GetObjectNormal(float *normx,float *normy,float *normz)
{
   int refp[4];
   float nx,ny,nz;

   switch (object_side)
   {
      case _FRONT_ : ArrayEqual(front ,refp); break;
	  case _RIGHT_ : ArrayEqual(right ,refp); break;
	  case _BACK_  : ArrayEqual(back  ,refp); ReverceArray(refp); break;
	  case _LEFT_  : ArrayEqual(left  ,refp); break;
      case _TOP_   : ArrayEqual(top   ,refp); break;
      case _BOTTOM_: ArrayEqual(bottom,refp); break;
   }

   CGLib0 *glib = new CGLib0 ;

	
   glib->GetPolyNormal ( ssx[refp[0]], ssy[refp[0]], ssz[refp[0]],
  					     ssx[refp[1]], ssy[refp[1]], ssz[refp[1]],						
					     ssx[refp[1]], ssy[refp[1]]+100, ssz[refp[1]],
					     &nx, &ny, &nz ) ;

   *normx = nx;
   *normy = ny;
   *normz = nz;

   return 0;
}

//get the carrier's normal of active side
CGObject::GetCarrierNormal(float *normx,float *normy,float *normz)
{
   int refp[4];
   float X1,Y1,Z1,X2,Y2,Z2;
   float nx,ny,nz;

   CGObject *obj = ((CGObject*)sdoc->Obj[carrier_id]);

   
   switch (carrier_side)
   {
      case _FRONT_ : ArrayEqual(front ,refp); break;
	  case _RIGHT_ : ArrayEqual(right ,refp); break;
	  case _BACK_  : ArrayEqual(back  ,refp); ReverceArray(refp); break;
	  case _LEFT_  : ArrayEqual(left  ,refp); break;
      case _TOP_   : ArrayEqual(top   ,refp); break;
      case _BOTTOM_: ArrayEqual(bottom,refp); break;
   }

   X1 = obj->ssx[refp[0]] ;
   Y1 = obj->ssy[refp[0]] ;
   Z1 = obj->ssz[refp[0]] ;

   X2 = obj->ssx[refp[1]] ;
   Y2 = obj->ssy[refp[1]] ;
   Z2 = obj->ssz[refp[1]] ;

   CGLib0 *glib = new CGLib0 ;
	
   glib->GetPolyNormal ( X1, Y1, Z1,
  					     X2, Y2, Z2,						
					     X2, Y2+100, Z2,
					     &nx, &ny, &nz ) ;

   *normx = nx;
   *normy = ny;
   *normz = nz;

   return 0;
}

//return the carrier active side length
float CGObject::GetCarrierLength()
{
	float objdist;

    //get carrier ref points
    GetCarrierSide();

	objdist =  sqrt( (pow( (pointX2 - pointX1), 2)) +
			         (pow( (pointY2 - pointY1), 2)) +
				     (pow( (pointZ2 - pointZ1), 2)) );

	//CLib0 lib;
	//AfxMessageBox("Carrier Lenght "+lib.floattostr(objdist));
	return fabs(objdist);
}


//return the active side lenght of object
float CGObject::GetObjectLength()
{
   float objdist ;

   //get object ref points
   GetObjectSide();

   objdist =  sqrt( (pow( (obj_pointX2-obj_pointX1), 2)) +
                    (pow( (obj_pointY2-obj_pointY1), 2)) +
		            (pow( (obj_pointZ2-obj_pointZ1), 2)) );

   return fabs(objdist);		   
}

//return the specified side lenght of box(object) 
float CGObject::GetBoxLength(int dimension)
{
   float objdist ;

   //get object box
   GetBox();

   switch (dimension)
   {
     case 1 : objdist =  sqrt( (pow( (ssx[3]-ssx[0]), 2)) +  //lenght
                               (pow( (ssy[3]-ssy[0]), 2)) +
		                       (pow( (ssz[3]-ssz[0]), 2)) ); break;
     case 2 : objdist =  sqrt( (pow( (ssx[0]-ssx[1]), 2)) +  //width
                               (pow( (ssy[0]-ssy[1]), 2)) +
		                       (pow( (ssz[0]-ssz[1]), 2)) ); break;
     case 3 : objdist =  sqrt( (pow( (ssx[0]-ssx[4]), 2)) +  //height
                               (pow( (ssy[0]-ssy[4]), 2)) +
		                       (pow( (ssz[0]-ssz[4]), 2)) ); break;
   }

   return fabs(objdist);		   
}


//get object x distance from carrier's ref points 
float CGObject::GetDistanceX()
{
	float d,f,d1; 
	float nx,ny,nz;

	  //get carrier + object ref points
      GetCarrierSide();
	  GetObjectSide();

	  //πρεπει να αφαιρειται το projection=outlook
	  //διοτι οι υπολογισμοι γινονται πανω στο επιπεδο του carrier
	  GetCarrierNormal(&nx,&ny,&nz);
	  float myoutlook = GetObjProjection();
      obj_pointX1 = obj_pointX1 - (nx * myoutlook);
	  obj_pointY1 = obj_pointY1 - (ny * myoutlook);
	  obj_pointZ1 = obj_pointZ1 - (nz * myoutlook);


	  //begin calculations...
	  //step 1 : calc d
      d = sqrt( (pow( (obj_pointX1 - pointX1), 2)) +  
		        (pow( (obj_pointY1 - pointY1), 2)) + 
				(pow( (obj_pointZ1 - pointZ1), 2)) );
	  d = fabs(d);
      //step 2 : calc f =cos(f)
      f = ( ( ((pointX2 - pointX1)*(obj_pointX1 - pointX1)) +
		      ((pointY2 - pointY1)*(obj_pointY1 - pointY1)) +
			  ((pointZ2 - pointZ1)*(obj_pointZ1 - pointZ1)) ) /
            ( fabs(d) *
			  sqrt( (pow( (pointX2 - pointX1), 2)) +
			        (pow( (pointY2 - pointY1), 2)) +
					(pow( (pointZ2 - pointZ1), 2)) )
			)
		  );
	  
	  //finally step 3 : calc d1 
      d1 = ( ( ((pointX2 - pointX1)*(obj_pointX1 - pointX1)) +
		       ((pointY2 - pointY1)*(obj_pointY1 - pointY1)) +
			   ((pointZ2 - pointZ1)*(obj_pointZ1 - pointZ1)) ) /
              ( sqrt( (pow( (pointX2 - pointX1), 2)) +
			          (pow( (pointY2 - pointY1), 2)) +
					  (pow( (pointZ2 - pointZ1), 2)) )
		      )
			);
	  //step 4 : calc d2
	  //d2 = ( fabs(d) * ( cos( (M_PI/2) - acos(f) ) ) );


	  //d1 = fabs(d1);
	  //d2 = fabs(d2);
      
	  return d1;

}

//get object y distance from carrier's ref points
float CGObject::GetDistanceY()
{
	float d,f,d2,t; 
	float nx,ny,nz;

	  //get carrier + object ref points
      GetCarrierSide();
	  GetObjectSide();

	  //CALIBRATE...
	  switch (object_side)
	  {
        case _BACK_   : break; //do nothing
        case _LEFT_   : break;
	    case _FRONT_  : outlook = outlook - GetBoxLength(_WIDTH_);  break;
	    case _RIGHT_  : outlook = outlook - GetBoxLength(_LENGTH_); break; 
	    case _TOP_    : break; //???
	    case _BOTTOM_ : break; //???
	    case _NOWHERE_: break;
	  }

	  //πρεπει να αφαιρειται το projection=outlook
	  //διοτι οι υπολογισμοι γινονται πανω στο επιπεδο του carrier
	  GetCarrierNormal(&nx,&ny,&nz);
	  float myoutlook = GetObjProjection();
      obj_pointX1 = obj_pointX1 - (nx * myoutlook);
	  obj_pointY1 = obj_pointY1 - (ny * myoutlook);
	  obj_pointZ1 = obj_pointZ1 - (nz * myoutlook);


	  //begin calculations...
	  //step 1 : calc d
      d = sqrt( (pow( (obj_pointX1 - pointX1), 2)) +  
		        (pow( (obj_pointY1 - pointY1), 2)) + 
				(pow( (obj_pointZ1 - pointZ1), 2)) );
	  d = fabs(d);
      //step 2 : calc f =cos(f)
      f = ( ( ((pointX2 - pointX1)*(obj_pointX1 - pointX1)) +
		      ((pointY2 - pointY1)*(obj_pointY1 - pointY1)) +
			  ((pointZ2 - pointZ1)*(obj_pointZ1 - pointZ1)) ) /
            ( fabs(d) *
			  sqrt( (pow( (pointX2 - pointX1), 2)) +
			        (pow( (pointY2 - pointY1), 2)) +
					(pow( (pointZ2 - pointZ1), 2)) )
			)
		  );

	  //step 3 : calc d2
	  t = ( cos( (M_PI/2) - acos(f) ) );
	  d2 = ( fabs(d) * t );

	  //d1 = fabs(d1);
	  //d2 = fabs(d2);
      
	  if (d2 < 1.0) d2 = 0.5; //minimum

	  return d2;
}


//get object height y distance from carrier
float CGObject::GetHeightDistance()
{
     return GetDistanceY() ;   
}

//get object left distance from carrier
float CGObject::GetLeftDistance()
{
	float d;

	d = GetDistanceX();

	//CALIBRATE...
	//αναλογα με την πλευρα τοποθετησης αφαιρειται η μετατοπιση
	switch (object_side)
	{
      case _BACK_   : break; //do nothing
      case _LEFT_   : d = d + GetBoxLength(_WIDTH_);  break;
	  case _FRONT_  : d = d - GetBoxLength(_LENGTH_); break;
	  case _RIGHT_  : d = d - GetBoxLength(_WIDTH_);  break; 
	  case _TOP_    : break; //???
	  case _BOTTOM_ : break; //???
	  case _NOWHERE_: break;
    }

    return d ;   
}

//get object left distance from carrier
float CGObject::GetRightDistance()
{
	float a1 ,a2 ,carrier_length , objLength;

	a1 = GetDistanceX();
    objLength = GetObjectLength(); 
	carrier_length = GetCarrierLength();

	a2 = (carrier_length - a1 - objLength);

	//CALIBRATE...
	//αναλογα με την πλευρα τοποθετησης προστιθεται η μετατοπιση
	switch (object_side)
	{
      case _BACK_   : break; //do nothing
      case _LEFT_   : a2 = a2 + GetBoxLength(_WIDTH_);  break;
	  case _FRONT_  : a2 = a2 + GetBoxLength(_LENGTH_); break;
	  case _RIGHT_  : a2 = a2 + GetBoxLength(_WIDTH_);  break; 
	  case _TOP_    : break; //???
	  case _BOTTOM_ : break; //???
	  case _NOWHERE_: break;
    }
 
	return a2;
}

//set object left distance from carrier
float CGObject::SetLeftDistance(float val)
{     
	return val;
}

//set object right distance from carrier
float CGObject::SetRightDistance(float val)
{
	float the_right ,carrier_length , objLength ;

    objLength = GetObjectLength();
	carrier_length = GetCarrierLength();

	the_right = (carrier_length - val - objLength);

	return the_right;
}

//υπολογιζω την νεα θεση του αντικειμένου πανω στην επιφάνεια του carrier του
CGObject::MoveOnCarrier(float d1, float d2,float *getx,float *gety,float *getz)
{
    float b,a;
    //get carrier + object ref points
    GetCarrierSide();
	GetObjectSide();

	//CALIBRATE...
	//αναλογα με την πλευρα τοποθετησης μετατοπιζεται το xyz
/*	switch (object_side)
	{
      case _BACK_   : break; //do nothing
      case _LEFT_   : d1 = d1 + GetBoxLength(_WIDTH_); break;
	  case _FRONT_  : d1 = d1 + GetBoxLength(_LENGTH_); break;
	  case _RIGHT_  : break; //do nothing
	  case _TOP_    : break; //???
	  case _BOTTOM_ : break; //???
	  case _NOWHERE_: break;
    }
*/
	//calculations...
	b = sqrt( (pow( (pointX2 - pointX1), 2)) +  
		      (pow( (pointY2 - pointY1), 2)) + 
			  (pow( (pointZ2 - pointZ1), 2)) );
	a = sqrt( (pow( (pointX3 - pointX1), 2)) +  
		      (pow( (pointY3 - pointY1), 2)) + 
			  (pow( (pointZ3 - pointZ1), 2)) );

    //set x y z translation on carrier
    *getx = ( (( (pointX2 - pointX1) / fabs(b) ) * d1 ) +
	 	      (( (pointX3 - pointX1) / fabs(a) ) * d2 ) + pointX1 ) ;

    *gety = ( (( (pointY2 - pointY1) / fabs(b) ) * d1 ) +
		      (( (pointY3 - pointY1) / fabs(a) ) * d2 ) + pointY1 ) ;

	*getz = ( (( (pointZ2 - pointZ1) / fabs(b) ) * d1 ) +
		      (( (pointZ3 - pointZ1) / fabs(a) ) * d2 ) + pointZ1 ) ;

	return 0;
}

//get the object projection (outlook) from its carrier
float CGObject::GetObjProjection()
{
	float result;

	GetCarrierSide();
	GetObjectSide();

	int refp[4];
	float mA,mB,mC,mD;
	CGLib0 *lib0 = new CGLib0 ;

	CGObject *obj = ((CGObject*)sdoc->Obj[carrier_id]);
	switch (carrier_side)
    {
      case _FRONT_ : ArrayEqual(front ,refp); break;
	  case _RIGHT_ : ArrayEqual(right ,refp); break;
	  case _BACK_  : ArrayEqual(back  ,refp); ReverceArray(refp); break;
	  case _LEFT_  : ArrayEqual(left  ,refp); break;
      case _TOP_   : ArrayEqual(top   ,refp); break;
      case _BOTTOM_: ArrayEqual(bottom,refp); break;
    }

	//get A,B,C,D
	lib0->GetPolyEquation(obj->ssx[refp[1]],obj->ssy[refp[1]],obj->ssz[refp[1]],
   	                      obj->ssx[refp[0]],obj->ssy[refp[0]],obj->ssz[refp[0]],
                          obj->ssx[refp[2]],obj->ssy[refp[2]],obj->ssz[refp[2]],
	    				  &mA , &mB , &mC , &mD); 
    //Apply type : d = Ax+By+Cz+D / sqrt(A^2+B^2+C^2)
	result = ( ((mA*obj_pointX1) + (mB*obj_pointY1) + (mC*obj_pointZ1) + mD) /
		        sqrt(pow(mA,2) + pow(mB,2) + pow(mC,2)) );


	//CALIBRATE...
	switch (object_side)
	{
      case _BACK_   : break; //do nothing
      case _LEFT_   : break;
	  case _FRONT_  : result = result + GetBoxLength(_WIDTH_);  break;
	  case _RIGHT_  : result = result + GetBoxLength(_LENGTH_); break; 
	  case _TOP_    : break; //???
	  case _BOTTOM_ : break; //???
	  case _NOWHERE_: break;
    }

	return result;
}

float CGObject::GetPolyType(float x1, float y1, float z1, 
						   float x2, float y2, float z2, 
					       float x3, float y3, float z3,
					       float x, float y, float z ) 
{
	float a,b,c;
	float out;

	a = ( ((y2-y1)*(z3-z1)) - ((y3-y1)*(z2-z1)) );
	b = ( ((z2-z1)*(x3-x1)) - ((z3-z1)*(x2-x1)) );
	c = ( ((x2-x1)*(y3-y1)) - ((x3-x1)*(y2-y1)) );

	out = ( (a*(x-x1))+(b*(y-y1))+(c*(z-z1)) );
	//out = ((a*x) - (a*x1)) + ((b*y) - (b*y1)) + ((c*z) - (c*z1)); 
	//out = ((a*x) + (b*y) + (c*z) + (-(a*x1)-(b*y1)-(c*z1)));

/*	ShowCustomPoints(150,x1,y1,z1,x2,y2,z2,x3,y3,z3);
	CLib0 lib;
	AfxMessageBox("Result :"+lib.floattostr(out)+"\n"+
		                "a :"+lib.floattostr(a)+"\n"+
		    	  	    "b :"+lib.floattostr(b)+"\n"+
					    "c :"+lib.floattostr(c)+"\n"+
				 	    "x :"+lib.floattostr(x)+"\n"+
					    "y :"+lib.floattostr(y)+"\n"+
					    "z :"+lib.floattostr(z)+"\n"+
				        "x1 :"+lib.floattostr(x1)+"\n"+
		    	  	    "y1 :"+lib.floattostr(y1)+"\n"+
					    "z1 :"+lib.floattostr(z1)+"\n"+
						"x2 :"+lib.floattostr(x2)+"\n"+
		    	  	    "y2 :"+lib.floattostr(y2)+"\n"+
					    "z2 :"+lib.floattostr(z2)+"\n"+
					    "x3 :"+lib.floattostr(x3)+"\n"+
		    	  	    "y3 :"+lib.floattostr(y3)+"\n"+
					    "z3 :"+lib.floattostr(z3));
*/
	return out;
}

//find the clicking side of object
void CGObject::FindCarrierSide(float x,float y,float z)
{
	CLib0 lib;
	CGLib0 *lib0 = new CGLib0 ;
	int mycarrier , counter , side[4],eureka ,finder ;
	float /*mA , mB , mC , mD ,*/ typos;

	mycarrier = carrier_id;

	ZeroArray(side);
	counter = 0;
	finder = 0;
	eureka = -1;

	CGObject *obj = ((CGObject*)sdoc->Obj[mycarrier]);
	     
	//0..5 = number of surfaces
	do//while ((counter<6) && (eureka==-1)) 
    {
	   switch (finder)
	   {
	       case 0 : ArrayEqual(front,side); break;
	       case 1 : ArrayEqual(right,side); break;
	       case 2 : ArrayEqual(back,side);  break;
	       case 3 : ArrayEqual(left,side);  break;
		   case 4 : ArrayEqual(top,side);   break;
		   case 5 : ArrayEqual(bottom,side);break;
	      default : AfxMessageBox("Array Error.."); break;		
	   }

   /*    lib0->GetPolyEquation(obj->ssx[side[0]],obj->ssy[side[0]],obj->ssz[side[0]],
   	                         obj->ssx[side[1]],obj->ssy[side[1]],obj->ssz[side[1]],
                             obj->ssx[side[2]],obj->ssy[side[2]],obj->ssz[side[2]],
						 	&mA , &mB , &mC , &mD); 
*/

	   typos = GetPolyType(obj->ssx[side[0]],obj->ssy[side[0]],obj->ssz[side[0]],
   	               obj->ssx[side[1]],obj->ssy[side[1]],obj->ssz[side[1]],
                   obj->ssx[side[2]],obj->ssy[side[2]],obj->ssz[side[2]],
	 			   x , y , z); 
	   //typos = ( (mA * x) + (mB * y) + (mC * z) + mD );

	   if ((typos > -2000) && (typos < 2000))
	   { 
	     eureka = finder; 
	     //goto out; 
	   }
	   else eureka = -1;

       counter+=1;
	   finder+=1;
	}while ((counter<6) && (eureka==-1)) ;

//out : ;
	//AfxMessageBox("result : "+lib.inttostr(typos));

/*	  	AfxMessageBox("Array "+lib.inttostr(side[0])+
	                          lib.inttostr(side[1])+
	        	              lib.inttostr(side[2])+
					          lib.inttostr(side[3])+"\n"+
                 "Refpoints "+lib.floattostr(obj->ssx[side[0]])+" "+
	                          lib.floattostr(obj->ssy[side[0]])+" "+
	        	              lib.floattostr(obj->ssz[side[0]])+"\n"+
					          lib.floattostr(obj->ssx[side[1]])+" "+
	                          lib.floattostr(obj->ssy[side[1]])+" "+
	        	              lib.floattostr(obj->ssz[side[1]])+"\n"+
							  lib.floattostr(obj->ssx[side[2]])+" "+
	                          lib.floattostr(obj->ssy[side[2]])+" "+
	        	              lib.floattostr(obj->ssz[side[2]])+"\n");

        AfxMessageBox("Result :"+lib.floattostr(typos)+"\n"+
		               "mA :"+lib.floattostr(mA)+"\n"+
		    	  	   "mB :"+lib.floattostr(mB)+"\n"+
					   "mC :"+lib.floattostr(mC)+"\n"+
					   "mD :"+lib.floattostr(mD)+"\n"+
 				   "eureka :"+lib.inttostr(eureka)+"\n"+
				 	    "x :"+lib.floattostr(x)+"\n"+
					    "y :"+lib.floattostr(y)+"\n"+
					    "z :"+lib.floattostr(z)+"\n"+
					 "mA*x :"+lib.floattostr(mA*x)+"\n"
                     "mB*y :"+lib.floattostr(mB*y)+"\n"
					 "mC*z :"+lib.floattostr(mC*y));
*/
		switch (eureka)
		{
		  case  -1 : carrier_side = _NOWHERE_;break;
		  case   0 : carrier_side = _FRONT_;  break;
		  case   1 : carrier_side = _RIGHT_;  break;
	      case   2 : carrier_side = _BACK_;   break;
		  case 	 3 : carrier_side = _LEFT_;   break;
		  case 	 4 : carrier_side = _TOP_;    break;
		  case 	 5 : carrier_side = _BOTTOM_; break;		
		}	


    

/*	counter = 0;
	for (int simia=0 ; simia<8 ; simia ++) //ενα αντικειμενο εχει 8 βασικα  σημεια που το περιγραφουν
    {
           if ( (fabs(x - obj->ssx[simia]) < 0.01 ) ||
			    (fabs(y - obj->ssy[simia]) < 0.01 ) ||
			    (fabs(z - obj->ssz[simia]) < 0.01 ) )
           {
               //that is reference point
			   side[counter]=simia; 
			   counter+=1;
           }
	}
	
	if (IsArrayEqual(front , side)) carrier_side = _FRONT_;
	else
	if (IsArrayEqual(left , side)) carrier_side = _LEFT_;
	else
	if (IsArrayEqual(back , side)) carrier_side = _BACK_;
	else
	if (IsArrayEqual(right , side)) carrier_side = _RIGHT_;
	else
	if (IsArrayEqual(top , side)) carrier_side = _TOP_;
	else
	if (IsArrayEqual(bottom , side)) carrier_side = _BOTTOM_;
	else
       carrier_side = _NOWHERE_;
*/
}

//test previous routine....
void CGObject::ClickSide(float x,float y,float z)
{
	CLib0 lib;
	CGLib0 *lib0 = new CGLib0 ;
	int counter, side[4], eureka, finder ;
	float mA , mB , mC , mD , typos;

	ZeroArray(side);
	counter = 0;
	finder = 0;
	eureka = -1;
	     
	//0..5 = number of surfaces
	while ((counter<6) && (eureka==-1)) 
    {
	   switch (finder)
	   {
	       case 0 : ArrayEqual(front,side); break;
	       case 1 : ArrayEqual(right,side); break;
	       case 2 : ArrayEqual(back,side);  break;
	       case 3 : ArrayEqual(left,side);  break;
		   case 4 : ArrayEqual(top,side);   break;
		   case 5 : ArrayEqual(bottom,side);break;
	      default : AfxMessageBox("Array Error.."); break;		
	   }

       lib0->GetPolyEquation(ssx[side[0]],ssy[side[0]],ssz[side[0]],
   	                         ssx[side[1]],ssy[side[1]],ssz[side[1]],
                             ssx[side[2]],ssy[side[2]],ssz[side[2]],
						 	&mA , &mB , &mC , &mD); 

	   typos = ( (mA * x) + (mB * y) + (mC * z) + mD );

	   if ((typos > -2000) && (typos < 2000))
	   { 
	     eureka = finder; 
	     //goto out; 
	   }
	   else eureka = -1;

       counter+=1;
	   finder+=1;
	}
//out : ;
		switch (eureka)
		{
		  case  -1 : AfxMessageBox("_NOWHERE_"); break;
		  case   0 : AfxMessageBox("_FRONT_");   break;
		  case   1 : AfxMessageBox("_RIGHT_");   break;
	      case   2 : AfxMessageBox("_BACK_");    break;
		  case 	 3 : AfxMessageBox("_LEFT_");    break;
		  case 	 4 : AfxMessageBox("_TOP_");     break;
		  case 	 5 : AfxMessageBox("_BOTTOM_");  break;
		}	
}



/////////////////////////////////////////////////////////////////////////////
// CGObject message handlers
