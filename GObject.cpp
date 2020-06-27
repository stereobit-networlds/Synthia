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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoSelection.h>

#define PI 3.1415926

/////////////////////////////////////////////////////////////////////////////
// CGObject

IMPLEMENT_DYNAMIC( CGObject, CObject )

CGObject::CGObject()
{
	carrier_id   = -1; //init with invalid values
	carrier_side = -1; 
	object_side  = -1; 
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

//****************  GENERAL COMMANDS  ******************
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

float CGObject::RadiansToMires(float r)
{
   float mires;

   mires = (360 / (2*PI)) * r ;

   return mires ;
}

float CGObject::MiresToRadians(float m)
{
   float rads;

   rads = m * ((2*PI) / 360 );

   return m ;
}

//****************** INVENTOR COMMANDS *************************

//make object visible 
void CGObject::MakeObjVisible()
{
     //make object invisible and unpickable
	 SoSeparator *mysep = sep ;	 //get node
	 
	 //set draw style
	 SoDrawStyle	*ds = (SoDrawStyle *)mysep->getChild(0) ;
     ds->style = SoDrawStyle::FILLED  ;
	 //set pick style
	 SoPickStyle *ps = (SoPickStyle *)mysep->getChild(3) ;
     ps->style.setValue(SoPickStyle::SHAPE) ;
}

//make object invisible
void CGObject::MakeObjInvisible()
{
     //make object invisible and unpickable
	 SoSeparator *mysep = sep ;	 //get node
	 
	 //set draw style
	 SoDrawStyle	*ds = (SoDrawStyle *)mysep->getChild(0) ;
     ds->style = SoDrawStyle::INVISIBLE  ;
	 //set pick style
	 SoPickStyle *ps = (SoPickStyle *)mysep->getChild(3) ;
     ps->style.setValue(SoPickStyle::UNPICKABLE) ;
}

//get translation
SbVec3f CGObject::GetTranslation()
{
    SbVec3f vals ;

    SoSeparator *mysep = sep ;
    SoTranslation *trans = (SoTranslation *)mysep->getChild(1) ;
    vals = trans->translation.getValue();

	return vals ;
}

//set translation
void CGObject::SetTranslation(SbVec3f vals)
{
	SoSeparator *mysep = sep ;
    SoTranslation *trans = (SoTranslation *)mysep->getChild(1) ;
	trans->translation	= vals;
}


//get the rotation angle...
float CGObject::GetRotationAngle()
{
    SbVec3f Rotaxis ;
	float Rotangle ;

	//get selected object rotation
	SoSeparator *mysep = sep ; //get object node
	SoRotation *ro = (SoRotation *)mysep->getChild(2) ;
    	   
    ro->rotation.getValue(Rotaxis , Rotangle); //get object rotation values

	return Rotangle ;
}

//set rotation angle ...
void CGObject::SetRotationAngle(float angle)
{
    SbVec3f Rotaxis ;

	//get selected object rotation
	SoSeparator *mysep = sep ; //get object node
	SoRotation *ro = (SoRotation *)mysep->getChild(2) ;

	SbRotation *sbrot = new SbRotation(SbVec3f(0,1,0),angle) ;
	ro->rotation.setValue(*sbrot) ;

}

//get the rotation axis...
SbVec3f CGObject::GetRotationAxis()
{
    SbVec3f Rotaxis ;
	float Rotangle ;

	//get selected object rotation
	SoSeparator *mysep = sep ; //get object node
	SoRotation *ro = (SoRotation *)mysep->getChild(2) ;
    	   
    ro->rotation.getValue(Rotaxis , Rotangle); 

	return Rotaxis ;
}

//set rotate axis ...
void CGObject::SetRotationAxis(SbVec3f axis)
{
    SbVec3f Rotaxis ;
	float Rotangle ;

	//get selected object rotation
	SoSeparator *mysep = sep ; //get object node

	SoRotation *ro = (SoRotation *)mysep->getChild(2) ;
    ro->rotation.getValue(Rotaxis , Rotangle);

	//set new rotation
    ro->rotation.setValue(axis ,Rotangle) ;
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
	    case _BACK_  : ArrayEqual(back  ,refp); break; 
	    case _LEFT_  : ArrayEqual(left  ,refp); break; 
        case _TOP_   : ArrayEqual(top   ,refp); break;
        case _BOTTOM_: ArrayEqual(bottom,refp); break;
	}

	SoSeparator *myroot = sdoc->root;
    
	//delete previous reference points from inventor...
	SoSeparator *prevref;
    SbName name = "Carrier_Reference"; 
	prevref = (SoSeparator *)SoNode::getByName(name);
	if (prevref!=NULL) myroot->removeChild(prevref);

	if ((offset>0) && (myside!=_NOWHERE_)) //no worldbase 
    {
	  if (theApp.ShowRefPoints) //if true.. show reference points
	  {
	    //create the new reference points 
        SoSeparator *ref = new SoSeparator ;

        for (int i = 0 ; i < 2 ; i++)
		{
	      SoSeparator *mysep = new SoSeparator ;

          //setup trans & rot
	      SoTranslation	*trans	= new SoTranslation ;
          //put new translation
	      trans->translation.setValue(obj->ssx[refp[i]],
		                              obj->ssy[refp[i]],
			    					  obj->ssz[refp[i]]);
	      SoRotation *rotat	= new SoRotation ;

	      //setup draw style
	      SoDrawStyle *ds = new SoDrawStyle ;
	      ds->style = SoDrawStyle::FILLED ;

	      //init pick style
	      SoPickStyle *ps = new SoPickStyle;
          ps->style.setValue(SoPickStyle::UNPICKABLE) ;

	      mysep->addChild( ds ) ;
          mysep->addChild( trans );	
	      mysep->addChild( rotat );
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
	    ref->setName("Carrier_Reference") ;  // set node name

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
    SbName name = "Object_Reference"; 
	prevref = (SoSeparator *)SoNode::getByName(name);
	if (prevref!=NULL) myroot->removeChild(prevref);

	if ((offset>0) && (object_side!=_NOWHERE_)) //no worldbase
	{
	  if (theApp.ShowRefPoints) //if true.. show reference points
	  {
        //create the new reference points 
        SoSeparator *ref = new SoSeparator ;

        for (int i = 0 ; i < 2 ; i++)
		{
	      SoSeparator *mysep = new SoSeparator ;

          //setup trans & rot
	      SoTranslation	*trans	= new SoTranslation ;
          //put new translation
	      trans->translation.setValue(ssx[refp[i]],
       	                              ssy[refp[i]],
		      					      ssz[refp[i]]);
	      SoRotation  *rotat = new SoRotation ;

	      //setup draw style
	      SoDrawStyle *ds = new SoDrawStyle ;
	      ds->style = SoDrawStyle::FILLED ;

	      //init pick style
	      SoPickStyle *ps = new SoPickStyle;
          ps->style.setValue(SoPickStyle::UNPICKABLE) ;

	      mysep->addChild( ds ) ;
          mysep->addChild( trans );	
	      mysep->addChild( rotat );
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
	    ref->setName("Object_Reference") ;  // set node name

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

        //setup trans & rot
	    SoTranslation	*trans	= new SoTranslation ;
        //put new translation
	    trans->translation.setValue(ssx[i],ssy[i],ssz[i]);
	    SoRotation  *rotat = new SoRotation ;

	    //setup draw style
	    SoDrawStyle *ds = new SoDrawStyle ;
	    ds->style = SoDrawStyle::FILLED ;

	    //init pick style
	    SoPickStyle *ps = new SoPickStyle;
        ps->style.setValue(SoPickStyle::UNPICKABLE) ;

	    mysep->addChild( ds ) ;
        mysep->addChild( trans );	
	    mysep->addChild( rotat );
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

void CGObject::ShowRefPoints(float size)
{
	ShowCarrierRefPoints(size);
	//ShowObjectRefPoints(size);
	ShowBoxPoints(size);
}

/****************** SELECT OBJECT ********************/
void CGObject::SelectObject()
{
	int child_no = -1 ; //init with invalid val

	switch (id)
	{
	   case _EXTERNAL_          : child_no = 5;  break; //Geometry node
	   case _ROOMWALL_          : child_no = 9;  break; //faceset node
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

void CGObject::SetCarrierSide(int side)
{
   carrier_side = side ;
}


void CGObject::GetCarrierSide()
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
      case _TOP_   : ArrayEqual(top   ,refp); break;
      case _BOTTOM_: ArrayEqual(bottom,refp); break;
   }

   pointX1 = obj->ssx[refp[0]] ;
   pointY1 = obj->ssy[refp[0]] ;
   pointZ1 = obj->ssz[refp[0]] ;

   pointX2 = obj->ssx[refp[1]] ;
   pointY2 = obj->ssy[refp[1]] ;
   pointZ2 = obj->ssz[refp[1]] ;

}



void CGObject::SetObjectSide(int side)
{
   object_side = side ;
}

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

}


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
  					     ssx[refp[1]], ssy[refp[1]]+100, ssz[refp[1]],						
					     ssx[refp[1]], ssy[refp[1]], ssz[refp[1]],
					     &nx, &ny, &nz ) ;

   *normx = -nx;
   *normy = -ny;
   *normz = -nz;

   return 0;
}

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
  					     X2, Y2+100, Z2,						
					     X2, Y2, Z2,
					     &nx, &ny, &nz ) ;

   *normx = -nx;
   *normy = -ny;
   *normz = -nz;

   return 0;
}


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


//calculate lenght of object
float CGObject::GetObjectLength()
{
   float objdist ;

   //get object ref points
   GetObjectSide();

   objdist =  sqrt( (pow( (obj_pointX2-obj_pointX1), 2)) +
                    (pow( (obj_pointY2-obj_pointY1), 2)) +
		            (pow( (obj_pointZ2-obj_pointZ1), 2)) );

   //CLib0 lib;
   //AfxMessageBox("Object Lenght "+lib.floattostr(objdist));
   return fabs(objdist);		   
}


//get object x distance from carrier 
float CGObject::GetDistanceX()
{
	float d,f,d1; 

	  //get carrier + object ref points
      GetCarrierSide();
	  GetObjectSide();

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
	  //d2 = ( fabs(d) * ( cos( (PI/2) - acos(f) ) ) );


	  //d1 = fabs(d1);
	  //d2 = fabs(d2);
      
	  return d1;

}

//get object y distance from carrier 
float CGObject::GetDistanceY()
{
	float d,f,d2,t; 
	float nx,ny,nz;

	  //get carrier + object ref points
      GetCarrierSide();
	  GetObjectSide();

	  //πρεπει να αφαιρειται το projection=outlook
	  //διοτι οι υπολογισμοι γινονται πανω στο επιπεδο του carrier
	  GetCarrierNormal(&nx,&ny,&nz);
      obj_pointX1 = obj_pointX1 - (nx * outlook) ;
	  obj_pointY1 = obj_pointY1 - (ny * outlook) ;
	  obj_pointZ1 = obj_pointZ1 - (nz * outlook) ;

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
	  t = ( cos( (PI/2) - acos(f) ) );
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
     return GetDistanceX() ;   
}

//get object left distance from carrier
float CGObject::GetRightDistance()
{
	float a1 ,a2 ,carrier_length , objLength;

	a1 = GetDistanceX();
    objLength = GetObjectLength(); 
	carrier_length = GetCarrierLength();

	a2 = (carrier_length - a1 - objLength);
 
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



void CGObject::FindCarrierSide(float x,float y,float z)
{
	CLib0 lib;
	CGLib0 *lib0 = new CGLib0 ;
	int mycarrier , counter , side[4],eureka ,finder ;
	float mA , mB , mC , mD , typos;

	mycarrier = carrier_id;

	ZeroArray(side);
	counter = 0;
	finder = 0;
	eureka = -1;

	CGObject *obj = ((CGObject*)sdoc->Obj[mycarrier]);
	     
	//0..5 = number of surfaces
	while ((counter<6) || (eureka!=-1)) 
    {
	   switch (finder)
	   {
	       case 0 : ArrayEqual(front,side); break;
	       case 1 : ArrayEqual(right,side); break;
	       case 2 : ArrayEqual(back,side);  break;
	       case 3 : ArrayEqual(left,side);  break;
		   case 4 : ArrayEqual(top,side);   break;
		   case 5 : ArrayEqual(bottom,side);break;
	      default : AfxMessageBox("Array Error.."); goto out; break;		
	   }
/*	   AfxMessageBox("Array "+lib.inttostr(side[0])+
	                          lib.inttostr(side[1])+
	        	              lib.inttostr(side[2])+
					          lib.inttostr(side[3]));
*/
	   AfxMessageBox("Refpoints "+lib.inttostr(obj->ssx[side[0]])+" "+
	                          lib.inttostr(obj->ssy[side[0]])+" "+
	        	              lib.inttostr(obj->ssz[side[0]])+"\n"+
					          lib.inttostr(obj->ssx[side[1]])+" "+
	                          lib.inttostr(obj->ssy[side[1]])+" "+
	        	              lib.inttostr(obj->ssz[side[1]])+"\n"+
							  lib.inttostr(obj->ssx[side[2]])+" "+
	                          lib.inttostr(obj->ssy[side[2]])+" "+
	        	              lib.inttostr(obj->ssz[side[2]]) );

       lib0->GetPolyEquation(obj->ssx[side[0]],obj->ssy[side[0]],obj->ssz[side[0]],
   	                         obj->ssx[side[1]],obj->ssy[side[1]],obj->ssz[side[1]],
                             obj->ssx[side[2]],obj->ssy[side[2]],obj->ssz[side[2]],
						 	&mA , &mB , &mC , &mD); 

	   typos = ( (mA * x) + (mB * y) + (mC * z) + mD );

	   if ((typos > -2000) && (typos < 2000))
	   { 
	     eureka = finder; 
	     goto out; 
	   }
	   else eureka = -1;

       counter = counter+1;
	   finder = finder+1;
	}

out : ;	
        AfxMessageBox("Result :"+lib.floattostr(typos)+"\n"+
		              "mA :"+lib.floattostr(mA)+"\n"+
		    	  	  "mB :"+lib.floattostr(mB)+"\n"+
					  "mC :"+lib.floattostr(mC)+"\n"+
					  "mD :"+lib.floattostr(mD)+"\n"+
					  "eureka :"+lib.inttostr(eureka)+"\n"+
					  "x :"+lib.floattostr(x)+"\n"+
					  "y :"+lib.floattostr(y)+"\n"+
					  "z :"+lib.floattostr(z));

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

	//AfxMessageBox("Ref points "+lib.floattostr(pointX1)+" "+
	//	                        lib.floattostr(pointY1)+" "+
	//			                lib.floattostr(pointZ1));
}





/////////////////////////////////////////////////////////////////////////////
// CGObject message handlers
