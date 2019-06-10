// GExternal.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"
#include "SYNTHdoc.h"
#include "SYNTHView.h"
#include "GExternal.h"
#include "RoomBase.h"
#include "RoomWall.h"
#include "WorldBase.h"
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
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoSelection.h>

SbMatrix matrix ;
SbVec3f dianisma , destdianisma ;

/////////////////////////////////////////////////////////////////////////////
// CGExternal

IMPLEMENT_DYNAMIC( CGExternal, CObject )

CGExternal::CGExternal()
{
	sep = NULL ;

	carrier_id = -1; //init with invalid value
	next_id = 0;
	prior_id = 0;

}

CGExternal::~CGExternal()
{
}



/*======================== ObjectToInventor ================*/

void CGExternal::ObjectToInventor ( SoSeparator *root )
{
	// inherited action
	CGObject::ObjectToInventor(root) ;

	SaveProperties() ; 
    
	root->addChild(sep) ;

	if (sdoc->BATTERING)  //battering ...
    {
       AttachObject(sep);
    }
	
	if (sdoc->REPLACE)    //replace ...
    {
	   ReplaceObject(sep); 	 
    }
} 

/*======================== SaveProperties ===================*/

void CGExternal::SaveProperties ()
{
	// inherited action
	CGObject::SaveProperties() ;
    
	sep->setName(name) ;  // set node name


	// find "Attributes"
	int mychild =sep->getNumChildren()-1;
	SoSeparator *myattr = (SoSeparator *)sep->getChild(mychild);
	const char *name = ((SoSeparator *)myattr)->getName().getString();  //get name
    
//	AfxMessageBox(name); 

	if (strcmp(name,"Attributes")==0) //Attributes exist delete it...
    {
		sep->removeChild(mychild);
    }

	SoSeparator *attr = new SoSeparator() ; //... rewrite attributes (case modify)
    attr->setName("Attributes") ;

	//set attributes invisible & unpickable...
    SoDrawStyle *ds = new SoDrawStyle ;
	attr->addChild(ds) ;
	ds->style = SoDrawStyle::INVISIBLE ;

	SoPickStyle *ps = new SoPickStyle;
	attr->addChild(ps) ;
    ps->style.setValue(SoPickStyle::UNPICKABLE) ;

  

	CLib0 lib ;
	CString soff = lib.inttostr(offset) ; 

	lib.setSoSFStringProp ( attr, SbName("ob_code"+soff), code ) ;
	lib.setSoSFStringProp ( attr, SbName("ob_descr"+soff), descr ) ;
	
	lib.setSoSFStringProp ( attr, SbName("ob_eid0"+soff), eid_id[0] ) ;
	lib.setSoSFStringProp ( attr, SbName("ob_eid1"+soff), eid_id[1] ) ;
	lib.setSoSFStringProp ( attr, SbName("ob_eid2"+soff), eid_id[2] ) ;
	lib.setSoSFStringProp ( attr, SbName("ob_eid3"+soff), eid_id[3] ) ;
	lib.setSoSFStringProp ( attr, SbName("ob_eid4"+soff), eid_id[4] ) ;
	lib.setSoSFStringProp ( attr, SbName("ob_eid5"+soff), eid_id[5] ) ;
	lib.setSoSFStringProp ( attr, SbName("ob_eid6"+soff), eid_id[6] ) ;
	lib.setSoSFStringProp ( attr, SbName("ob_eid7"+soff), eid_id[7] ) ;
	lib.setSoSFStringProp ( attr, SbName("ob_eid8"+soff), eid_id[8] ) ;
	lib.setSoSFStringProp ( attr, SbName("ob_eid9"+soff), eid_id[9] ) ;

	lib.setSoSFIntProp ( attr, SbName("next"+soff), next_id ) ;
	lib.setSoSFIntProp ( attr, SbName("prior"+soff), prior_id ) ;
	lib.setSoSFIntProp ( attr, SbName("carrier"+soff), carrier_id ) ;
	lib.setSoSFIntProp ( attr, SbName("topoth"+soff), topoth ) ;
	
	lib.setSoSFFloatProp ( attr, SbName("yangle"+soff), yangle ) ;

	lib.setSoSFFloatProp ( attr, SbName("lbp0"+soff), left_base_point[0] ) ;
	lib.setSoSFFloatProp ( attr, SbName("lbp1"+soff), left_base_point[1] ) ;
	lib.setSoSFFloatProp ( attr, SbName("lbp2"+soff), left_base_point[2] ) ;
	lib.setSoSFFloatProp ( attr, SbName("rbp0"+soff), right_base_point[0] ) ;
	lib.setSoSFFloatProp ( attr, SbName("rbp1"+soff), right_base_point[1] ) ;
	lib.setSoSFFloatProp ( attr, SbName("rbp2"+soff), right_base_point[2] ) ;

	lib.setSoSFFloatProp ( attr, SbName("ltp0"+soff), left_top_point[0] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ltp1"+soff), left_top_point[1] ) ;
	lib.setSoSFFloatProp ( attr, SbName("ltp2"+soff), left_top_point[2] ) ;
	lib.setSoSFFloatProp ( attr, SbName("rtp0"+soff), right_top_point[0] ) ;
	lib.setSoSFFloatProp ( attr, SbName("rtp1"+soff), right_top_point[1] ) ;
	lib.setSoSFFloatProp ( attr, SbName("rtp2"+soff), right_top_point[2] ) ;

	sep->addChild( attr ) ;
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

	next_id		= lib.getSoSFIntProp(SbName("next"+soff)) ;
	prior_id	= lib.getSoSFIntProp(SbName("prior"+soff)) ;
	carrier_id	= lib.getSoSFIntProp(SbName("carrier"+soff)) ;
	topoth		= lib.getSoSFIntProp(SbName("topoth"+soff)) ;

	yangle		= lib.getSoSFFloatProp(SbName("yangle"+soff)) ;

	left_base_point[0]	= lib.getSoSFFloatProp(SbName("lbp0"+soff)) ;
	left_base_point[1]	= lib.getSoSFFloatProp(SbName("lbp1"+soff)) ;
	left_base_point[2]	= lib.getSoSFFloatProp(SbName("lbp2"+soff)) ;
	right_base_point[0]	= lib.getSoSFFloatProp(SbName("rbp0"+soff)) ;
	right_base_point[1]	= lib.getSoSFFloatProp(SbName("rbp1"+soff)) ;
	right_base_point[2]	= lib.getSoSFFloatProp(SbName("rbp2"+soff)) ;

	left_top_point[0]	= lib.getSoSFFloatProp(SbName("ltp0"+soff)) ;
	left_top_point[1]	= lib.getSoSFFloatProp(SbName("ltp1"+soff)) ;
	left_top_point[2]	= lib.getSoSFFloatProp(SbName("ltp2"+soff)) ;
	right_top_point[0]	= lib.getSoSFFloatProp(SbName("rtp0"+soff)) ;
	right_top_point[1]	= lib.getSoSFFloatProp(SbName("rtp1"+soff)) ;
	right_top_point[2]	= lib.getSoSFFloatProp(SbName("rtp2"+soff)) ;
}

/*======================= EditProperties ========================*/
int CGExternal::EditProperties ( CDocument *d, SoSeparator *root ) 
{
    float comparedistX,comparedistY ; //compare purpose
	float compL , compR ;

	// inherited action
	CGObject::EditProperties(d,root) ;

	//get selected object
	CGExternal *selected = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]);
	//Get selected reference points
	GetObjRefPoints(selected);
    //Calculate selected object distances
    GetDistances(selected);
	//Calculate selected object or whole battering wall distances
	GetWallDistances(selected);

	GExternalProp *dlg = new GExternalProp ;

	dlg->m_code		= code ;
	dlg->m_descr	= descr ;
	dlg->m_yangle	= yangle ;
	dlg->m_topoth	= topoth ;
	dlg->m_xdist	= xdist ; comparedistX = xdist; 
	dlg->m_ydist	= ydist ; comparedistY = ydist;
	dlg->m_ldist    = Ldist ; compL = Ldist;
	dlg->m_rdist    = Rdist ; compR = Rdist;

	int res = dlg->DoModal() ;

	if (res == IDOK)   
	{
		code	= dlg->m_code ;
		descr	= dlg->m_descr ;
		yangle	= dlg->m_yangle ;
		topoth	= dlg->m_topoth ;
        xdist   = dlg->m_xdist ;
		ydist   = dlg->m_ydist ;
        Ldist   = dlg->m_ldist ;
		Rdist   = dlg->m_rdist ;

 		if ((xdist!=comparedistX) || (ydist!=comparedistY)) //if xdist,ydist value has change
        {
		  //calculate motion for selected object only
	      MoveObjectTo(selected,xdist,ydist) ;
        }

		if (Rdist!=compR) { SetWallDistances(selected ,1); }
         
		if (Ldist!=compL) { SetWallDistances(selected ,0); }

		SaveProperties() ;    
	}

	return res ;
}


//************************ ������ ����� *********************************
/*************************  get reference points  ********************/
void CGExternal::GetObjRefPoints(CGExternal *ext_obj)
{
	CLib0 lib;

	//get selection carrier
	carrier_id = ((CGExternal*)ext_obj)->carrier_id;

	next_id = ((CGExternal*)ext_obj)->next_id;
	prior_id = ((CGExternal*)ext_obj)->prior_id;
	AfxMessageBox(lib.inttostr(carrier_id)+" "+lib.inttostr(next_id)+" "+lib.inttostr(prior_id));

	//get points data x1,y1,z1 ,x2,y2,z2
	if (sdoc->Obj[carrier_id]->IsKindOf(RUNTIME_CLASS(CWorldBase)))
	{	
		//do nothing. Can't be worldbase
		//or maybe the points is the same with roombase ???
	}
	else 
	if (sdoc->Obj[carrier_id]->IsKindOf(RUNTIME_CLASS(CRoomBase)))
    {
		CRoomBase *rb =((CRoomBase*)sdoc->Obj[carrier_id]);

		pointX1 = rb->Koryfsx[0] ;
        pointY1 = rb->Koryfsy[0] ;
		pointZ1 = rb->Koryfsz[0] ;

		pointX2 = rb->Koryfsx[1] ;
        pointY2 = rb->Koryfsy[1] ;
		pointZ2 = rb->Koryfsz[1] ;

		// ���� ������� ��������� ��� 2 ������ ������� ��� RoomBase
    }
	else
	if (sdoc->Obj[carrier_id]->IsKindOf(RUNTIME_CLASS(CRoomWall)))
	{
        CRoomWall *rw = ((CRoomWall*)sdoc->Obj[carrier_id]);

		pointX1 = rw->Koryfsx[0] ;
        pointY1 = rw->Koryfsy[0] ;
		pointZ1 = rw->Koryfsz[0] ;

		pointX2 = rw->Koryfsx[1] ;
        pointY2 = rw->Koryfsy[1] ;
		pointZ2 = rw->Koryfsz[1] ;

		// ���� ������� ��������� ��� 2 ������ ������� ��� RoomWall
    }

	else        
	if (sdoc->Obj[carrier_id]->IsKindOf(RUNTIME_CLASS(CGExternal)))
	{
	    //do nothing 
    }
	
	
	//AfxMessageBox("points :"+lib.floattostr(pointX1)+" "+lib.floattostr(pointY1)+" "+lib.floattostr(pointZ1)+
	//" , "+lib.floattostr(pointX2)+" "+lib.floattostr(pointY2)+" "+lib.floattostr(pointZ2));
    //float x = (pointX2-pointX1);
	//AfxMessageBox(lib.floattostr(pointX1));
}


#define PI 3.1415926
/********************* GetDistances **************************/
void CGExternal::GetDistances(CGExternal *ext_obj)
{
    CLib0 lib;
	float objX,objY,objZ ;
	float d,f,d1,d2; 
	SbVec3f vals;

    
	SoSeparator *sep = ((CGExternal*)ext_obj)->sep ; //get node
	SoNode *mynode ;
	mynode = sep->getChild(1);
	if (mynode->isOfType(SoTranslation::getClassTypeId())) //if it is translation node
    {     
      SoTranslation *trans = (SoTranslation *) mynode ; //get translation node
	  vals = trans->translation.getValue(); //get values
	  
	  objX = vals[0];
      objY = vals[1];
      objZ = vals[2];

	  //AfxMessageBox("object :"+lib.floattostr(vals[0])+" "+lib.floattostr(vals[1])+" "+lib.floattostr(vals[2]));

	  //begin calculations...
	  //step 1 : calc d
      d = sqrt( (pow( (objX-pointX1), 2)) +  
		        (pow( (objY-pointY1), 2)) + 
				(pow( (objZ-pointZ1), 2)) );
	  d = fabs(d);
      //step 2 : calc f =cos(f)
      f = ( ( ((pointX2-pointX1)*(objX-pointX1)) +
		      ((pointY2-pointY1)*(objY-pointY1)) +
			  ((pointZ2-pointZ1)*(objZ-pointZ1)) ) /
            ( fabs(d) *
			  sqrt( (pow( (pointX2-pointX1), 2)) +
			        (pow( (pointY2-pointY1), 2)) +
					(pow( (pointZ2-pointZ1), 2)) )
			)
		  );
	  
	  //finally step 3 : calc d1 
      d1 = ( ( ((pointX2-pointX1)*(objX-pointX1)) +
		       ((pointY2-pointY1)*(objY-pointY1)) +
			   ((pointZ2-pointZ1)*(objZ-pointZ1)) ) /
              ( sqrt( (pow( (pointX2-pointX1), 2)) +
			          (pow( (pointY2-pointY1), 2)) +
					  (pow( (pointZ2-pointZ1), 2)) )
		      )
			);
	  //step 4 : calc d2
	  d2 = ( fabs(d) * ( cos( (PI/2) - acos(f) ) ) );


	  d1 = fabs(d1);
	  d2 = fabs(d2);
      
	  //transfer d1,d2
	  xdist = d1 ;
	  ydist = d2 ;

	  //check for non zero
	  if (xdist<1) xdist = .5 ;
	  if (ydist<1) ydist = .5 ;

	  //AfxMessageBox("distances :"+lib.floattostr(xdist)+" "+lib.floattostr(ydist));
    }
	else
    {
	  AfxMessageBox("Unable to translate the object.");
    }

}

/*** get the right and left wall distances from the object or battering ****/
void CGExternal::GetWallDistances(CGExternal *ext_obj)
{
	int my_next, my_prev ;
	SbVec3f values ;
	int meter ;
	float x1 , x2 , d ;
	CLib0 lib;

	//AfxMessageBox(lib.floattostr(pointX1));
    SoSeparator *sep = ((CGExternal*)ext_obj)->sep ; //get the selected object node 

	my_next = ext_obj->next_id ;  //get the selected object next number
	my_prev = ext_obj->prior_id ;  //get the selected object previous number

	//get translation of selected object ...
    SoTranslation *trans = (SoTranslation *)sep->getChild(1) ;
    values = trans->translation.getValue();

    //because we want the right distance calculate the object distance ...
	x1 = ext_obj->left_base_point[0] ;
	x2 = ext_obj->right_base_point[0] ;
	d = (x2 - x1);
 
    //finaly calculate the left and right distances of selected object ...
    Ldist =  values[0] - pointX2 ; 
    Rdist =  pointX1 - values[0] - d ; 

    //if battering ... find the very next and very previous left and right distances 
	meter=0;
    while (my_next!=0)
	{
       CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object
	   SoSeparator *sep = ((CGExternal*)nxt)->sep ; 

	   //get next object
	   my_next = nxt->next_id ;

	   //get translation ...
	   SoTranslation *trans = (SoTranslation *)sep->getChild(1) ;
	   values = trans->translation.getValue();

	   //because we want the right distance calculate the object distance ...
	   x1 = nxt->left_base_point[0] ;
	   x2 = nxt->right_base_point[0] ;
	   d = (x2 - x1);
 
       //finaly calculate the distance...
	   Rdist =  pointX1 - values[0] - d ; 

	   meter+=1; 
	}
    //CLib0 lib;
    //AfxMessageBox(lib.inttostr(meter));

    meter=0;
	while (my_prev!=0)
	{
       CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object
	   SoSeparator *sep = ((CGExternal*)prv)->sep ; 
	   
	   //get prev object
	   my_prev = prv->prior_id ;

	   //get translation ...
	   SoTranslation *trans = (SoTranslation *)sep->getChild(1) ;
	   values = trans->translation.getValue();

	   //the left distance ...
	   Ldist =  values[0] - pointX2 ; 

	   meter+=1;
	}
	//CLib0 lib;
    //AfxMessageBox(lib.inttostr(meter));
}

/*** set the right or left wall distances from the object or battering ****/
//0 =left , 1 =right
void CGExternal::SetWallDistances(CGExternal *ext_obj , int RightOrLeft)
{ 
	SbVec3f values ;
	float xL , xR ;
	float x1 , x2 , d ;
	CLib0 lib ;
   
	SoSeparator *sep = ((CGExternal*)ext_obj)->sep ; //get the selected object node 

	//get translation of selected object ...
    SoTranslation *trans = (SoTranslation *)sep->getChild(1) ;
    values = trans->translation.getValue();

	//calculations...
    if (RightOrLeft==0)  //left distance
	{
       
	   xL = pointX2 + Ldist ;
	   values[0] = xL ;
	}
	else  //right distance
	{
      
      //because we want the right distance calculate the object distance ...
      x1 = ext_obj->left_base_point[0] ;
	  x2 = ext_obj->right_base_point[0] ;
	  d = (x2 - x1);

      xR = pointX1 - d - Rdist ;
	  values[0] = xR ;
	}

    //}
	//put new translation
	trans->translation	= values;

	//move all the others battering objects
	MovRebuildButtering(ext_obj);
	
}

/********************* Move object **************************/
void CGExternal::MoveObjectTo(CGExternal *ext_obj,float d1,float d2)
{
    CLib0 lib;
	float objX,objY,objZ ;
	float b; 
	SbVec3f vector ;

	//AfxMessageBox("distances :"+lib.floattostr(d1)+" "+lib.floattostr(d2));
	//calculations...
	b = sqrt( (pow( (pointX2-pointX1), 2)) +  
		      (pow( (pointY2-pointY1), 2)) + 
			  (pow( (pointZ2-pointZ1), 2)) );


    objX = ( ( (pointX2-pointX1) / fabs(b) ) * d1 + pointX1 ) ;
    objY = ( ( (pointY2-pointY1) / fabs(b) ) * d1  + d2 +pointY1 ) ;
	objZ = ( ( (pointZ2-pointZ1) / fabs(b) ) * d1 + pointZ1 ) ;

	//AfxMessageBox("object :"+lib.floattostr(objX)+" "+
	//	                     lib.floattostr(objY)+" "+
	//			             lib.floattostr(objZ)) ;

	//put new translation
	vector.setValue(objX , objY , objZ);

	SoSeparator *sep = ((CGExternal*)ext_obj)->sep ;
	SoTranslation *trans = (SoTranslation *)sep->getChild(1) ;

	trans->translation	=  vector;

	//move all the others battering objects
	MovRebuildButtering(ext_obj);
}


//move all the battering objects...
//ext = the selected or base of battering object
void CGExternal::MovRebuildButtering(CGExternal *ext)
{
	int my_next, my_prev , meter;
	SbVec3f sourcevec , targetvec;
	SbVec3f Rotaxis ;
	float Rotangle ; 

    SoSeparator *sep = ((CGExternal*)ext)->sep ; //get the selected object translation 
	SoTranslation *trans = (SoTranslation *)sep->getChild(1) ;
    sourcevec = trans->translation.getValue(); //���� ������� ��� �� translation ��� ���� ��� ��� ����

	SoRotation *r = (SoRotation *)sep->getChild(2) ;
	r->rotation.getValue(Rotaxis , Rotangle); //get selected object rotation values

	SbRotation *sbrot = new SbRotation(Rotaxis , Rotangle); //get selected object rotation  
	sbrot->getValue(matrix);                                //and transfer it to the new
    //matrix multiply with the new rotation and the result is the real rotation of the new object

	my_next = ext->next_id ;  //get the selected object next number
	my_prev = ext->prior_id ;  //get the selected object previous number

	//init calculations for the next pointers
	//find the first value for the targetvec
	CalculateObjectDistance(ext);
	if ((my_next)!=0) targetvec = sourcevec + destdianisma ; 
    //if at right +destdianisma 

	//first move right objects of battering
	meter=0;
    while (my_next!=0)
	{
       CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object

	   //get next object
	   my_next = nxt->next_id ;

	   //put new translation for each object
	   SoSeparator *nxt_sep = ((CGExternal*)nxt)->sep ;
	   SoTranslation *trans = (SoTranslation *)nxt_sep->getChild(1) ;
	   trans->translation = targetvec;

	   //after calculate...
	   //calculate its distance and add it to the targetvec
       CalculateObjectDistance(nxt);
       targetvec = targetvec + destdianisma ;

	   meter+=1; 
	}

	//init calculations for the prev pointers
	//find the first value for the targetvec
	CalculateObjectDistance(ext); 
	if ((my_prev)!=0) targetvec = sourcevec ; //=sourcevec
    //if at right -destdianisma 

	//secontary move left objects...
    meter=0;
	while (my_prev!=0)
	{
       CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object
	   
	   //get prev object
	   my_prev = prv->prior_id ;

	   //first calculate...
       //calculate its distance and substrack it from the targetvec
       CalculateObjectDistance(prv);
       targetvec = targetvec - destdianisma ;

	   //put new translation for each object
	   SoSeparator *prv_sep = ((CGExternal*)prv)->sep ;
	   SoTranslation *trans = (SoTranslation *)prv_sep->getChild(1) ;
	   trans->translation = targetvec;

	   meter+=1;
	}
	//CLib0 lib;
    //AfxMessageBox(lib.inttostr(meter));
}

//**************** battering ************************
void CGExternal::CalculateObjectDistance(CGExternal *e_obj)
{
	float pX1 , pY1 , pZ1 ,
	      pX2 , pY2 , pZ2 ;

	//get left and right base points of selected object
    CGExternal *ext = ((CGExternal*)e_obj);
    pX1 = ext->left_base_point[0] ;
    pY1 = ext->left_base_point[1] ;
    pZ1 = ext->left_base_point[2] ;

    pX2 = ext->right_base_point[0] ;
    pY2 = ext->right_base_point[1] ;
    pZ2 = ext->right_base_point[2] ;

    //get distances
    dianisma[0] = pX2 - pX1;
    dianisma[1] = pY2 - pY1;
    dianisma[2] = pZ2 - pZ1; 
			   
    //multiply dianisma by matrix 
	//���� �� ���� ����������� ��� ����
    matrix.multVecMatrix(dianisma , destdianisma);
}


//************** input object (battering) **************/
void CGExternal::AttachObject(SoSeparator *obj_sep)
{
	CLib0 lib;
    SbVec3f Transaxis , NewTransaxis , Rotaxis ;
	float Rotangle ;

//  AfxMessageBox(lib.inttostr(sdoc->obj_selector));

    //get selected object translation & rotation
	SoSeparator *selected = ((CGExternal*)sdoc->Obj[sdoc->obj_selector])->sep ; //get selected object node

	SoTranslation *t = (SoTranslation *)selected->getChild(1) ; 
	SoRotation *r = (SoRotation *)selected->getChild(2) ;
    	
	Transaxis = t->translation.getValue(); //get selected object translation values   
    r->rotation.getValue(Rotaxis , Rotangle); //get selected object rotation values

	SbRotation *sbrot = new SbRotation(Rotaxis , Rotangle); //get selected object rotation  
	sbrot->getValue(matrix);                                //and transfer it to the new
    //matrix multiply with the new rotation and the result is the real rotation of the new object


	//calculate translation
	//AfxMessageBox(lib.inttostr(theApp.ObjDirection));
	switch (theApp.ObjDirection)
    {
	  case 1 : { //right
		       //get selected object
		       CGExternal *gext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]); 
               CalculateObjectDistance(gext);

		       //new translation
	           NewTransaxis[0] = Transaxis[0] + destdianisma[0] ;
               NewTransaxis[1] = Transaxis[1] + destdianisma[1] ;
               NewTransaxis[2] = Transaxis[2] + destdianisma[2] ;

			   //AfxMessageBox("Right");
			   break;
             }
      case 2 : { //left
		       //get new object
		       CGExternal *gext = ((CGExternal*)sdoc->Obj[sdoc->ObjCount-1]);
		       CalculateObjectDistance(gext);
			   
               //new translation 
	           NewTransaxis[0] = Transaxis[0] - destdianisma[0] ;
               NewTransaxis[1] = Transaxis[1] - destdianisma[1] ;
               NewTransaxis[2] = Transaxis[2] - destdianisma[2] ;

			   //AfxMessageBox("Left");
			   break;
             }
    }
	//rebuild battering (if there are battering) inserting mode
	InsRebuildButtering();

	//set new object translation & rotation 
    SoDrawStyle	*ds = (SoDrawStyle *)obj_sep->getChild(0) ;
	SoTranslation *trans = (SoTranslation *)sep->getChild(1) ;
	SoRotation *rot	= (SoRotation *)sep->getChild(2) ;

	ds->style = SoDrawStyle::FILLED ;
	trans->translation	= NewTransaxis ; //put new (computed ) translation values
	rot->rotation.setValue(Rotaxis ,Rotangle) ; //put rotation values same as selected object

	sdoc->new_object = FALSE ;  //��� ���������� �� ������� click ��� �� ���������� �� �����������

    //select the new object..
	sview->GetSelectionNode()->deselectAll();
	sview->GetSelectionNode()->select(obj_sep->getChild(4)) ; //get "geometry" node
	sdoc->obj_selector = sdoc->ObjCount-1 ;
	//.. and set battering on..
	sdoc->BATTERING = true;

	sdoc->SetModifiedFlag() ;
	sdoc->UpdateAllViews(NULL);   
}

//******* standart change of attributes  (end of battering) *******
void CGExternal::InsChangeAttributes()
{
	CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]);

	switch (theApp.ObjDirection)
    {
	  case 1 : { //right

	             //change new object attributes
	             //set carrier
	             carrier_id	= ext->carrier_id ; 
                 //set next pointer
	             next_id = 0 ; //nothing next
                 //set prior pointer
	             prior_id = sdoc->obj_selector ; //= � ������� ��� ����������� object
	
	             SaveProperties();

	             //change selected object attributes
	             //set next pointer
	             ext->next_id = sdoc->ObjCount-1 ; //= � ������� ��� ���� object
	             // no prior
	             // no carrier
	             ext->SaveProperties();

				 break;
			   }
      case 2 : { //left

	             //change new object attributes
	             //set carrier
	             carrier_id	= ext->carrier_id ; 
                 //set next pointer
	             next_id = sdoc->obj_selector ; //= � ������� ��� ����������� object
                 //set prior pointer
	             prior_id = 0 ; //nothing previous
	
	             SaveProperties();

	             //change selected object attributes
	             //set previous pointer
	             ext->prior_id = sdoc->ObjCount-1 ; //= � ������� ��� ���� object
	             // no next
	             // no carrier
	             ext->SaveProperties();

				 break;
			   }
    }
}

//******* change of attributes in the middle of the battering *******
void CGExternal::InsChangeMiddleAttributes()
{
    CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]); //get selected object

	switch (theApp.ObjDirection)
    {
	  case 1 : { //right
                 CGExternal *nxt = ((CGExternal*)sdoc->Obj[ext->next_id]);       //get next of selected object

	             //change new object attributes
	             //set carrier
	             carrier_id	= ext->carrier_id ; 
                 //set next pointer
	             next_id = ext->next_id ; //the next of new object is now the next of selected
                 //set prior pointer
	             prior_id = sdoc->obj_selector ; //= � ������� ��� ����������� object
	
                 SaveProperties();

	             //change selected object attributes
	             //set next pointer
	             ext->next_id = sdoc->ObjCount-1 ; //= � ������� ��� ���� object
	             // no prior
	             // no carrier
	             ext->SaveProperties();

	             //change next of selected (before rebuilding) object attributes
	             //no next (is the same)
	             //no carrier
	             //set previous pointer
	             nxt->prior_id = sdoc->ObjCount-1 ; //= � ������� ��� ���� object

	             nxt->SaveProperties();

				 break;
			   }
      case 2 : { //left
                 CGExternal *prv = ((CGExternal*)sdoc->Obj[ext->prior_id]);       //get previous of selected object

	             //change new object attributes
	             //set carrier
	             carrier_id	= ext->carrier_id ; 
                 //set next pointer
	             next_id = sdoc->obj_selector ; //= � ������� ��� ����������� object
                 //set prior pointer
	             prior_id = ext->prior_id ; //the previous of new object is now the previous of selected   
	
                 SaveProperties();

	             //change selected object attributes
	             //set previous pointer
	             ext->prior_id = sdoc->ObjCount-1 ; //= � ������� ��� ���� object
	             // no next
	             // no carrier
	             ext->SaveProperties();

	             //change previous of selected (before rebuilding) object attributes
	             //no previous
	             //no carrier
	             //set next pointer
	             prv->next_id = sdoc->ObjCount-1 ; //= � ������� ��� ���� object

	             prv->SaveProperties();

				 break;
			   }
    }
}

//rebuild the battering objects at right and left or change the attributes
//insert mode ....
void CGExternal::InsRebuildButtering()
{
    int my_next, my_prev, meter;
	SbVec3f Values , NewValues ;

	//***** i need the distance of new object so..
	CGExternal *gext = ((CGExternal*)sdoc->Obj[sdoc->ObjCount-1]);
    CalculateObjectDistance(gext);

    CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]);  //get selected object
	meter=0; //zero meter
	switch (theApp.ObjDirection)
    {
	  case 1 : { //right

                 my_next	= ext->next_id ;  //get the selected object next number

	             while (my_next!=0)
				 {
                    CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object
	                SoSeparator *nextsep = ((CGExternal*)sdoc->Obj[my_next])->sep ; //get next object node
                    SoTranslation *t = (SoTranslation *)nextsep->getChild(1) ;  //get translation node
	                Values = t->translation.getValue(); //get next object translation values

	                //new translation
                    NewValues[0] = Values[0] + destdianisma[0] ;
                    NewValues[1] = Values[1] + destdianisma[1] ;
                    NewValues[2] = Values[2] + destdianisma[2] ;

                    t->translation = NewValues ; //put new (computed ) translation values to next object

	                //get next object
	                my_next = nxt->next_id ;
	                meter+=1; 
				 }
				 break;
			   }
      case 2 : { //left

                 my_prev = ext->prior_id ;  //get the selected object prior number

	             while (my_prev!=0)
				 {
                    CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object
	                SoSeparator *prevsep = ((CGExternal*)sdoc->Obj[my_prev])->sep ; //get previous object node
                    SoTranslation *t = (SoTranslation *)prevsep->getChild(1) ;  //get translation node
	                Values = t->translation.getValue(); //get next object translation values

                    //new translation
                    NewValues[0] = Values[0] - destdianisma[0] ;
                    NewValues[1] = Values[1] - destdianisma[1] ;
                    NewValues[2] = Values[2] - destdianisma[2] ;

                    t->translation = NewValues ; //put new (computed ) translation values to previous object

					//get next object
	                my_prev = prv->prior_id ;
	                meter+=1;
				 }
				 break;
               }
	}

	//CLib0 lib;
	//AfxMessageBox(lib.inttostr(meter));

    //Change the attributes of objects
	if (meter==0) //it means that the new object is located at the end of battering
    {
       InsChangeAttributes();
    }
	else  //the object has insert somewhere -in- the  battering
    {
	   InsChangeMiddleAttributes();
    }
}




//******* Delete mode .. change attributes *********
void CGExternal::DelChangeAttributes()
{
    CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]); //get selected object

	if (ext->next_id!=0)
    {
      CGExternal *nxt = ((CGExternal*)sdoc->Obj[ext->next_id]);       //get next of selected object
      nxt->prior_id = ext->prior_id;
	  nxt->SaveProperties();
    }
    if (ext->prior_id!=0)
    {
      CGExternal *prv = ((CGExternal*)sdoc->Obj[ext->prior_id]);      //get prev of selected object 
	  prv->next_id = ext->next_id;
      prv->SaveProperties();
    }

	//change selected (deleted) object attributes
	ext->next_id = 0;
	ext->prior_id = 0;
	ext->carrier_id = 0;
	ext->SaveProperties();

}


//rebuild the battering objects at right or left and change the attributes
//delete mode...
//**** this routine called from delete routine of synthview file ******
void CGExternal::DelRebuildButtering()
{
    int my_next, my_prev, meter;
	SbVec3f Values , NewValues ;
	float pX1, pY1, pZ1 ;
    float pX2, pY2, pZ2 ;
	SbVec3f Rotaxis ;
	float Rotangle ;
	int the_next, the_prev;

    CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]);  //get selected object

	//check if there are battering ...
	the_next = ext->next_id ;  //get the selected object next number
    the_prev = ext->prior_id ;  //get the selected object previous number
    if ((the_next!=0) || (the_prev!=0))
    {
 
	  //find matrix 
	  SoSeparator *selected = ((CGExternal*)sdoc->Obj[sdoc->obj_selector])->sep ; //get selected object node
	  SoRotation *r = (SoRotation *)selected->getChild(2) ; 	   
      r->rotation.getValue(Rotaxis , Rotangle); //get selected object rotation values

	  SbRotation *sbrot = new SbRotation(Rotaxis , Rotangle); //get selected object rotation  
	  sbrot->getValue(matrix);                                //and transfer it to the new
      //matrix multiply with the new rotation and the result is the real rotation of the new object


      //calculate selected object distance
	  pX1 = ext->left_base_point[0] ;
      pY1 = ext->left_base_point[1] ;
      pZ1 = ext->left_base_point[2] ;

      pX2 = ext->right_base_point[0] ;
      pY2 = ext->right_base_point[1] ;
      pZ2 = ext->right_base_point[2] ;

      //get distances
      dianisma[0] = pX2 - pX1;
      dianisma[1] = pY2 - pY1;
      dianisma[2] = pZ2 - pZ1; 

	  //multiply dianisma by matrix 
      matrix.multVecMatrix(dianisma , destdianisma);

      //get selected object 
      //CalculateObjectDistance(ext); ��� �������������� � calculate ������� �� ���� ������� ������!!!!!

	  meter=0; //zero meter
	  switch (theApp.ObjDirection)
	  {
	    case 1 : { //right

                   my_next	= ext->next_id ;  //get the selected object next number

	               while (my_next!=0)
				   {
                      CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object
	                  SoSeparator *nextsep = ((CGExternal*)sdoc->Obj[my_next])->sep ; //get next object node
                      SoTranslation *t = (SoTranslation *)nextsep->getChild(1) ;  //get translation node
	                  Values = t->translation.getValue(); //get next object translation values

	                  //new translation
                      NewValues[0] = Values[0] - destdianisma[0] ;
                      NewValues[1] = Values[1] - destdianisma[1] ;
                      NewValues[2] = Values[2] - destdianisma[2] ;

                      t->translation = NewValues ; //put new (computed ) translation values to next object

	                  //get next object
	                  my_next = nxt->next_id ;
	                  meter+=1; 
				   }
				   break;
				 }
        case 2 : { //left

                   my_prev = ext->prior_id ;  //get the selected object prior number

	               while (my_prev!=0)
				   {
                      CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object
	                  SoSeparator *prevsep = ((CGExternal*)sdoc->Obj[my_prev])->sep ; //get previous object node
                      SoTranslation *t = (SoTranslation *)prevsep->getChild(1) ;  //get translation node
	                  Values = t->translation.getValue(); //get next object translation values

                      //new translation
                      NewValues[0] = Values[0] + destdianisma[0] ;
                      NewValues[1] = Values[1] + destdianisma[1] ;
                      NewValues[2] = Values[2] + destdianisma[2] ;

                      t->translation = NewValues ; //put new (computed ) translation values to previous object

					  //get prev object
	                  my_prev = prv->prior_id ;
	                  meter+=1;
				   }
				   break;
				 }
	  }

	  //CLib0 lib;
	  //AfxMessageBox(lib.inttostr(meter));

      //Change the attributes of objects
      DelChangeAttributes();

	} //if
}



//******* Extented Delete mode .. change attributes (break battering) *********
void CGExternal::ExtDelChangeAttributes()
{
    CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]); //get selected object

	if (ext->next_id!=0)
    {
      CGExternal *nxt = ((CGExternal*)sdoc->Obj[ext->next_id]);       //get next of selected object
      nxt->prior_id = 0; //break..
	  nxt->SaveProperties();
    }
    if (ext->prior_id!=0)
    {
      CGExternal *prv = ((CGExternal*)sdoc->Obj[ext->prior_id]);      //get prev of selected object 
	  prv->next_id = 0; //break..
      prv->SaveProperties();
    }

	//change selected (deleted) object attributes
	ext->next_id = 0;
	ext->prior_id = 0;
	ext->carrier_id = 0;
	ext->SaveProperties();

}


//rebuild the battering objects at right or left and change the attributes
//delete object and break the battering in 2 butterings
//extent delete mode...
//**** this routine called from delete routine of synthview file ******
void CGExternal::ExtDelRebuildButtering()
{
	int the_next, the_prev;

    CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]);  //get selected object

	//check if there are battering ...
	the_next = ext->next_id ;  //get the selected object next number
    the_prev = ext->prior_id ;  //get the selected object previous number
    if ((the_next!=0) || (the_prev!=0))
    {
	  //..do nothing 
      //just set the atributes...

      //Change the attributes of objects
      ExtDelChangeAttributes();

	} //if
}


//Ungroup the selected object battering
void CGExternal::UnGroupObjects()
{
	int my_next, my_prev , meter;

    CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]);  //get selected object
	my_next = ext->next_id ;  //get the selected object next number
	my_prev = ext->prior_id ;  //get the selected object previous number

	//first ungroup right objects of battering
	meter=0;
    while (my_next!=0)
	{
       CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object

	   //get next object
	   my_next = nxt->next_id ;

	   nxt->prior_id = 0; 
	   nxt->next_id =0; //after getting the next pointer zero him
      
	   nxt->SaveProperties();

	   meter+=1; 
	}

	//secontary ungroup left objects...
    meter=0;
	while (my_prev!=0)
	{
       CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object
	   
	   //get prev object
	   my_prev = prv->prior_id ;

	   prv->next_id = 0;
       prv->prior_id =0; //after getting the prev pointer zero him

	   prv->SaveProperties();

	   meter+=1;
	}

	//..at end ungroup selected object
	ext->next_id = 0;
	ext->prior_id = 0;
	ext->SaveProperties();

}


//************** replace object  **************/
void CGExternal::ReplaceObject(SoSeparator *obj_sep)
{
	int mynext,myprior,mycarrier ;
    SbVec3f Transaxis , Rotaxis ;
    float Rotangle ;

/*   
	//rebuild battering (if there are battering) replace mode
	RepRebuildButtering();
*/
	//get selected-old object translation and rotation
	SoSeparator *selected = ((CGExternal*)sdoc->Obj[sdoc->obj_selector])->sep ; //get selected object node
	SoTranslation *t = (SoTranslation *)selected->getChild(1) ; 
	SoRotation *r = (SoRotation *)selected->getChild(2) ;    	
	Transaxis = t->translation.getValue(); //get selected object translation values   
    r->rotation.getValue(Rotaxis , Rotangle); //get selected object rotation values

    //save selected-old object attributes
	CGExternal *the_old = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]);//old
	mynext = the_old->next_id ;
	myprior = the_old->prior_id ;
	mycarrier = the_old->carrier_id ;

    //delete the replaced-selected object
	sview->OnDelete();

	if ((mynext!=0) || (myprior!=0)) //more than one object battering
    {
      switch (theApp.ObjDirection)
	  {
  	    case 1 : { //right
			       if (myprior!=0)
                   {
					   //select previous object
                      SoSeparator *p = ((CGExternal*)sdoc->Obj[myprior])->sep ;
	                  sview->GetSelectionNode()->deselectAll();
	                  sview->GetSelectionNode()->select(p->getChild(4)) ; //get "geometry" node
                      //set selector to prior object
                      sdoc->obj_selector = myprior ;

					  //Attach the object
					  //...
					  //AfxMessageBox("");
					  AttachObject(obj_sep);
                   }
				   else
                   if (mynext!=0)
                   {
                      //select next object
                      SoSeparator *n = ((CGExternal*)sdoc->Obj[mynext])->sep ;
	                  sview->GetSelectionNode()->deselectAll();
	                  sview->GetSelectionNode()->select(n->getChild(4)) ; //get "geometry" node
                      //set selector to next object
                      sdoc->obj_selector = mynext ;

					  //Attach the object
					  //...
					  //AfxMessageBox("");
					  theApp.ObjDirection=2; //switch the direction
					  AttachObject(obj_sep);
					  theApp.ObjDirection=1; //..and set the previous direction 
                   }
	  	           break;
				 }
        case 2 : { //left ... same as above but opposite...
			       if (mynext!=0)
                   {
                      //select next object
                      SoSeparator *n = ((CGExternal*)sdoc->Obj[mynext])->sep ;
	                  sview->GetSelectionNode()->deselectAll();
	                  sview->GetSelectionNode()->select(n->getChild(4)) ; //get "geometry" node
                      //set selector to next object
                      sdoc->obj_selector = mynext ;

					  //Attach the object
					  //...
					  //AfxMessageBox("");
					  AttachObject(obj_sep);
                   }
				   else
                   if (myprior!=0)
                   {
                      //select previous object
                      SoSeparator *p = ((CGExternal*)sdoc->Obj[myprior])->sep ;
	                  sview->GetSelectionNode()->deselectAll();
	                  sview->GetSelectionNode()->select(p->getChild(4)) ; //get "geometry" node
                      //set selector to prior object
                      sdoc->obj_selector = myprior ;

					  //Attach the object
					  //...
					  //AfxMessageBox("");
					  theApp.ObjDirection=1; //switch the direction
					  AttachObject(obj_sep);
					  theApp.ObjDirection=2; //..and set the previous direction
                   }
		           break;
				 }
	  }
	}
	else //only one object
    {
	   //set new object translation & rotation 
       SoDrawStyle	*ds = (SoDrawStyle *)obj_sep->getChild(0) ;
	   SoTranslation *trans = (SoTranslation *)sep->getChild(1) ;
	   SoRotation *rot	= (SoRotation *)sep->getChild(2) ;
       //appear new object
	   ds->style = SoDrawStyle::FILLED ;
	   trans->translation	= Transaxis ; //put selected object translation values to the new object
	   rot->rotation.setValue(Rotaxis ,Rotangle) ; //put selected object rotation values to the new object

	   sdoc->new_object = FALSE ;  //��� ���������� �� ������� click ��� �� ���������� �� �����������
    }

	//save new object attributes (get it from saved old-selected-replaced object)
	CGExternal *the_new = ((CGExternal*)sdoc->Obj[sdoc->ObjCount-1]); //new
	the_new->next_id = mynext ;
	the_new->prior_id = myprior ;
	the_new->carrier_id = mycarrier ;
	the_new->SaveProperties();

    //select the new object..
	sview->GetSelectionNode()->deselectAll();
	sview->GetSelectionNode()->select(obj_sep->getChild(4)) ; //get "geometry" node
	sdoc->obj_selector = sdoc->ObjCount-1 ;
	//.. and set battering on..
	sdoc->BATTERING = true;

	sdoc->SetModifiedFlag() ;
	sdoc->UpdateAllViews(NULL);   
}


//rebuild the battering objects at right and left or change the attributes
//replace mode ....
void CGExternal::RepRebuildButtering()
{
	CLib0 lib ;
    int my_next, my_prev, meter;
	SbVec3f OldValues , NewValues , 
		    Selected_dist_values , 
			New_dist_values ;

	//get objects old and new 
	CGExternal *the_new = ((CGExternal*)sdoc->Obj[sdoc->ObjCount-1]); //new
	CGExternal *the_old = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]);//old  

    //change new object attributes (get it from old-selected-replaced object)
	the_new->next_id = the_old->next_id ;
	the_new->prior_id = the_old->prior_id ;
	the_new->carrier_id = the_old->carrier_id ;
	the_new->SaveProperties();


	//***** i need the distance of new object so..
    CalculateObjectDistance(the_new);
    New_dist_values = destdianisma ; //hold the new object dianisma

	//***** i need the distance of selected object so..
    CalculateObjectDistance(the_old);
    Selected_dist_values = destdianisma ; //hold the selected object dianisma 

	AfxMessageBox(lib.inttostr(Selected_dist_values[0] - New_dist_values[0]));

	meter=0; //zero meter
	switch (theApp.ObjDirection)
    {
	  case 1 : { //right

                 my_next	= the_new->next_id ;  //get the selected object next number

	             while (my_next!=0)
				 {
                    CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object
	                SoSeparator *nextsep = ((CGExternal*)sdoc->Obj[my_next])->sep ; //get next object node
                    SoTranslation *trn = (SoTranslation *)nextsep->getChild(1) ;  //get translation node
	                OldValues = trn->translation.getValue(); //get next object translation values

	                //new translation
                    NewValues[0] = OldValues[0] - (Selected_dist_values[0] - New_dist_values[0]) ;
                    NewValues[1] = OldValues[1] - (Selected_dist_values[1] - New_dist_values[1]) ;
                    NewValues[2] = OldValues[2] - (Selected_dist_values[2] - New_dist_values[2]) ;

                    //trn->translation = NewValues ; //put new (computed ) translation values to next object

	                //get next object
	                my_next = nxt->next_id ;
	                meter+=1; 
				 }
				 break;
			   }
      case 2 : { //left

                 my_prev = the_new->prior_id ;  //get the selected object prior number

	             while (my_prev!=0)
				 {
                    CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object
	                SoSeparator *prevsep = ((CGExternal*)sdoc->Obj[my_prev])->sep ; //get previous object node
                    SoTranslation *t = (SoTranslation *)prevsep->getChild(1) ;  //get translation node
	                OldValues = t->translation.getValue(); //get next object translation values

                    //new translation
                    NewValues[0] = OldValues[0] - (Selected_dist_values[0] - New_dist_values[0]) ;
                    NewValues[1] = OldValues[1] - (Selected_dist_values[1] - New_dist_values[1]) ;
                    NewValues[2] = OldValues[2] - (Selected_dist_values[2] - New_dist_values[2]) ;

                    t->translation = NewValues ; //put new (computed ) translation values to previous object

					//get next object
	                my_prev = prv->prior_id ;
	                meter+=1;
				 }
				 break;
               }
	}

	//CLib0 lib;
	AfxMessageBox(lib.inttostr(meter));
}


//paste ...
void CGExternal::PasteObject()
{
	    CLib0 lib;

	    CGExternal *ob = ((CGExternal *)sdoc->Copy_Obj[1]);

		//ob = new CGExternal ;
		sdoc->Obj[sdoc->ObjCount] = ob ; 
		sdoc->ObjCount++ ;
		ob->sep = sdoc->copysep ;
		//sep		= ob->sep ;

        ob->offset = sdoc->ob_offset ; sdoc->ob_offset++ ;
		ob->name   = "GExternal" + lib.inttostr(sdoc->ObjCount-1); //+ "/" + mycode ;
		ob->code   = code ;
		ob->descr  = descr ;

		ob->SaveProperties() ; 
    
	    sdoc->root->addChild(sdoc->copysep) ;

		AttachObject(sdoc->copysep);

}

//delete ...
void CGExternal::DeleteObject()
{
        CLib0 lib; 

        //delete object from inventor...
		SoSeparator *myroot = sdoc->root;
		SoSeparator *del_external;
        SbName name = "GExternal"+lib.inttostr(sdoc->obj_selector) ; 
		del_external = (SoSeparator *)SoNode::getByName(name);
		myroot->removeChild(del_external);

		//deselect ...
	    sview->GetSelectionNode()->deselectAll();

		//delete object from Object array
	    sdoc->Obj[sdoc->obj_selector]=NULL;
}

/////////////////////////////////////////////////////////////////////////////
// GExternalProp dialog


GExternalProp::GExternalProp(CWnd* pParent /*=NULL*/)
	: CDialog(GExternalProp::IDD, pParent)
{
	//{{AFX_DATA_INIT(GExternalProp)
	m_code = _T("");
	m_descr = _T("");
	m_topoth = 0;
	m_xdist = 0.0f;
	m_yangle = 0.0f;
	m_ydist = 0.0f;
	m_ldist = 0.0f;
	m_rdist = 0.0f;
	//}}AFX_DATA_INIT
}


void GExternalProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GExternalProp)
	DDX_Text(pDX, IDC_CODE, m_code);
	DDX_Text(pDX, IDC_DESCR, m_descr);
	DDX_Text(pDX, IDC_TOPOTH, m_topoth);
	DDX_Text(pDX, IDC_XDIST, m_xdist);
	DDX_Text(pDX, IDC_YANGLE, m_yangle);
	DDX_Text(pDX, IDC_YDIST, m_ydist);
	DDX_Text(pDX, IDC_LDIST, m_ldist);
	DDX_Text(pDX, IDC_RDIST, m_rdist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GExternalProp, CDialog)
	//{{AFX_MSG_MAP(GExternalProp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GExternalProp message handlers
