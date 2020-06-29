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
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTexture2Transform.h>
#include <Inventor/nodes/SoTextureCoordinatePlane.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoTransform.h>




/////////////////////////////////////////////////////////////////////////////
// CGExternal

IMPLEMENT_DYNAMIC( CGExternal, CObject )

CGExternal::CGExternal()
{
	sep = NULL ;

	next_id = 0;
	prior_id = 0;
	local_rot = 0;
	global_rot = 0;
	rotpoint = _BKLEFT_;
}

CGExternal::~CGExternal()
{
}


/*======================== ObjectToInventor ================*/

void CGExternal::ObjectToInventor ( SoSeparator *root )
{
	// inherited action
	CGObject::ObjectToInventor(root) ;

	GetBox();  //<<<<<-------------------------------- εγκιβωτισμος

	SaveProperties() ;     
	root->addChild(sep) ;
  
    //check for ...
	if (sdoc->BATTERY)  //battering ...
    {
       AttachObject();
    }
	
	if (sdoc->REPLACE)    //replace ...
    {
	   ReplaceObject(); 	 
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

	lib.setSoSFIntProp ( attr, SbName("rotpoint"+soff), rotpoint ) ;
	lib.setSoSFIntProp ( attr, SbName("local_rot"+soff), local_rot ) ;
	lib.setSoSFIntProp ( attr, SbName("global_rot"+soff), global_rot ) ;

	sep->addChild( attr ) ;
}

/*======================== InventorToObject ================*/

void CGExternal::InventorToObject ( SoSeparator *root )
{
	sep = root ;

	//inherited action
	CGObject::InventorToObject ( root );

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

	rotpoint	= lib.getSoSFIntProp(SbName("rotpoint"+soff)) ;
	local_rot	= lib.getSoSFIntProp(SbName("local_rot"+soff)) ;
	global_rot	= lib.getSoSFIntProp(SbName("global_rot"+soff)) ;
}

//με βαση την γωνια και τον αξονα περιστροφης υπολογιζουμε απο ενα 
//διανυσμα ΑΒ τον νεο σημειο Γ που θα προκυψει...
void CGExternal::GetBoxPoints(float Ax,float Ay,float Az,float Bx,float By,float Bz,
							  float fangle,float rotaxisX,float rotaxisY,float rotaxisZ,
							  float *Cx,float *Cy,float *Cz)
{
	float a,d1,d2;
	float Dx,Dy,Dz;
	float Fx,Fy,Fz;

	//find distance of AB ...
	a = sqrt( (pow( (Bx-Ax), 2)) +  
              (pow( (By-Ay), 2)) +
		      (pow( (Bz-Az), 2)) );

    d1 = a*cos(fangle*(M_PI/180.0)); //convert to radians
	d2 = a*sin(fangle*(M_PI/180.0));

    //get D point
    Dx = Ax + (d1/a) * (Bx - Ax);
    Dy = Ay + (d1/a) * (By - Ay);
	Dz = Az + (d1/a) * (Bz - Az);

	GetVectorNormal(Ax,Ay,Az,Bx,By,Bz,rotaxisX,rotaxisY,rotaxisZ,&Fx,&Fy,&Fz);

  /*  CLib0 lib;
	AfxMessageBox(lib.floattostr(Fx)+" "+
			      lib.floattostr(Fy)+" "+
				  lib.floattostr(Fz));*/
    //finaly ... 
    *Cx = Dx - (Fx*d2);
	*Cy = Dy - (Fy*d2);
	*Cz = Dz - (Fz*d2);
}

void CGExternal::RotateBox(int rp,float a)
{
	int p1;
   	switch (rp) //the object rotation point (center,backright,...)
	{
	  case _BKLEFT_ : p1=0; break; 
      case _FRLEFT_ : p1=1; break;
	  case _FRRIGHT_: p1=2; break;
	  case _BKRIGHT_: p1=3; break;
	  //case _CENTER_ : mypoint=???   break;
	}

    for (int i=0;i<4;i++)
	{
		if (i!=p1) //skip points on rotation axis
		{
		//rotate bottom box points
        GetBoxPoints(xbox[p1],ybox[p1],zbox[p1],
				     xbox[i],ybox[i],zbox[i],
				     /*global_rot*/a,obj_raxisX,obj_raxisY,obj_raxisZ,
				     &ssx[i],&ssy[i],&ssz[i]);
		//rotate up box points
		GetBoxPoints(xbox[p1+4],ybox[p1+4],zbox[p1+4],
				     xbox[i+4],ybox[i+4],zbox[i+4],
				     /*global_rot*/a,obj_raxisX,obj_raxisY,obj_raxisZ,
				     &ssx[i+4],&ssy[i+4],&ssz[i+4]);
		}
	}
}

void CGExternal::GetBox()
{
    int i;

	// inherited action
	CGObject::GetBox() ;

	//στην περιπτωση των externals τα min,max's ειναι τα ακροτατα σημεια
	//του αντικειμένου στο δικο του συστημα συντεταγμενων...
	//αρα οταν θελουμε τις global τιμες αρκει να προσθεσω τα totals = object translation

	//****** down
	ssx[0] = xmin + totalx ;
    ssy[0] = ymin + totaly ;
	ssz[0] = zmin + totalz ;

	ssx[1] = xmin + totalx ;
    ssy[1] = ymin + totaly ;
	ssz[1] = zmax + totalz ;

	ssx[2] = xmax + totalx ;
    ssy[2] = ymin + totaly ;
	ssz[2] = zmax + totalz ;

	ssx[3] = xmax + totalx ;
    ssy[3] = ymin + totaly ;
	ssz[3] = zmin + totalz ;

	//****** up
	ssx[4] = xmin + totalx ;
    ssy[4] = ymax + totaly ;
	ssz[4] = zmin + totalz ;

	ssx[5] = xmin + totalx ;
    ssy[5] = ymax + totaly ;
	ssz[5] = zmax + totalz ;

	ssx[6] = xmax + totalx ;
    ssy[6] = ymax + totaly ;
	ssz[6] = zmax + totalz ;

	ssx[7] = xmax + totalx ;
    ssy[7] = ymax + totaly ;
	ssz[7] = zmin + totalz ;

	//save init box translation...
	for (i=0;i<8;i++)
	{ 
	  xbox[i] = ssx[i];
	  ybox[i] = ssy[i];
	  zbox[i] = ssz[i];
	}

	//rotate box in it's init rotation...
	RotateBox(_BKLEFT_,rotangle); //rotate object in the init potition..
 
	//...and save box real translation
	for (i=0;i<8;i++)
	{ 
	  xbox[i] = ssx[i];
	  ybox[i] = ssy[i];
	  zbox[i] = ssz[i];
	}
}

/*======================= EditProperties ========================*/
int CGExternal::EditProperties ( CDocument *d, SoSeparator *root ) 
{
	CLib0 lib;
    float comparedistX,comparedistX1; //compare purpose
	float compL , compR ; //compare purpose
	float compangle;
	float x;

	// inherited action
	CGObject::EditProperties(d,root) ;

	//show attrs
	AfxMessageBox(" offset "+lib.inttostr(offset)+"\n Carrier "
		         +lib.inttostr(carrier_id)+"\n Car Side "
		         +lib.inttostr(carrier_side)+"\n Obj Side "
				 +lib.inttostr(object_side)+"\n Next "
		         +lib.inttostr(next_id)+"\n Previous "
				 +lib.inttostr(prior_id)+"\n Outlook "
				 +lib.inttostr(outlook));

	if ((carrier_side ==_NOWHERE_) || 
		(object_side == _NOWHERE_))
	{
       AfxMessageBox("Invalid object data");
	   return 0 ;
    }

	//reset rotation...
	//μηδενιζουμε την περιστροφη για να παρουμε τις σωστες τιμες των αποστασεων
	RotateObjectTo(0); 
	RotateBox(rotpoint,0);  

    //Calculate selected object distances
    left_d  = GetLeftDistance();
	right_d = GetRightDistance();

	//Calculate selected object or whole battering wall distances
	Ldist = GetBatteryLeftDistance();
	Rdist = GetBatteryRightDistance();

	//get object height
	up_d = GetDistanceY();

	//Get object rotation
	//rotangle = RadiansToMires(GetRotationAngle()); //no need 
	//get object projection
	//outlook = GetObjProjection(); //no need

	//restore rotation...
	//επαναφερουμε την περιστροφη για να μην φαινεται στον χρηστη η αλλαγη
	//θεσης του αντικειμενου κατα την προβολη των ιδιοτητων
	RotateObjectTo(local_rot);
	RotateBox(rotpoint,local_rot);

	GExternalProp *dlg = new GExternalProp ;

	dlg->m_code		= code ;
	dlg->m_descr	= descr ;
	dlg->m_yangle	= local_rot; compangle = local_rot; 
	dlg->m_xdist	= left_d ; comparedistX = left_d; 
	dlg->m_ydist	= up_d ; 
	dlg->m_leftdist = Ldist ; compL = Ldist;
	dlg->m_rightdist= Rdist ; compR = Rdist;
	dlg->m_x1dist   = right_d; comparedistX1 = right_d;
	dlg->m_outlook  = outlook ; 
	dlg->m_rotpoint = rotpoint ;

    dlg->m_objLen = GetObjectLength(); 
	dlg->m_batLen = GetBatteryLength(); 

	int res = dlg->DoModal() ;

	if (res == IDOK)   
	{
		sdoc->SaveUndo(); //save scene for undo... 

	    //reset rotation...
		SetObjectCenter(rotpoint); //use active rotation center
	    RotateObjectTo(0); 
		RotateBox(rotpoint,0);  

        ShowRefPoints(150.0); //<<<----------------------- show points
		AfxMessageBox("a");


		code	= dlg->m_code ;
		descr	= dlg->m_descr ;
		local_rot = dlg->m_yangle ;
		outlook	= dlg->m_outlook ;
        left_d  = dlg->m_xdist ; 
		up_d    = dlg->m_ydist ;
        Ldist   = dlg->m_leftdist ;
		Rdist   = dlg->m_rightdist ;
		right_d = dlg->m_x1dist ;
		rotpoint= dlg->m_rotpoint ;  //change rotation point

        x=left_d;

		// set x object (not buttering) translation
		if (fabs(left_d - comparedistX) > 0.001)
		{
			x = SetLeftDistance(left_d);
			goto out;
		}
		if (fabs(right_d - comparedistX1) > 0.001) 
		{
		    x = SetRightDistance(right_d);
			goto out;
		}
        // set x object or battering translation 
		if (fabs(Ldist - compL) > 0.001) 
		{
		    x = SetBatteryLeftDistance(Ldist);
			goto out;
        }
		if (fabs(Rdist - compR) > 0.001)
		{
			x = SetBatteryRightDistance(Rdist);
			goto out;
		}

		
out: ;  //object ...

		//move object...
	    SetObjectCenter(_BKLEFT_); //set the default rotation point (inventor ok!!!)
        MoveObjectTo(x,up_d) ;
		ProjectObjectTo(outlook);
		GetBox();

		ShowRefPoints(150.0); //<<<----------------------- show points
		AfxMessageBox("b");

		// set rotation
		SetObjectCenter(rotpoint); //set the new rotation point
        RotateObjectTo(local_rot);
	    RotateBox(rotpoint,local_rot);

		//SaveProperties() ;

        //battery...
		//RotateBattery();
		//MoveBattery();
		//ProjectBattery();
		
		ShowRefPoints(150.0); //<<<----------------------- show points
	}

	return res ;
}



//get a point and the normal direction and return global rotation 
float CGExternal::GetGlobalObjDirection(SbVec3f point,SbVec3f normal)
{
    float result ,bx,by,bz ,out;

    //first get the virtual point
    bx = point[0] + (1 * normal[0]);
	by = point[1] + (1 * normal[1]);
	bz = point[2] + (1 * normal[2]); 

	//init object in world space
	SoTransform *tr	= (SoTransform *)sep->getChild(0) ;
	SbRotation *sbrot = new SbRotation(SbVec3f(0,0,1),normal); //always on Z axis and object normal 
	tr->rotation.setValue(*sbrot) ;
    //...get the diference of vectors (corner)
	out = RadiansToDegrees(GetRotationAngle());

	if (bx>point[0])
	{   
		result = out;
	}
	else
	if (bx<point[0])
	{
        result = (360 - out); 
	}
	else
	if (bx==point[0])
	{
		if (bz>point[2]) out = 0;
		            else out = 180;
		result = out;
	}
	return result ;
}


void CGExternal::AddNewObject(SbVec3f p_point, SbVec3f p_normal)
{
		// inherited action
	    CGObject::AddNewObject(p_point,p_normal) ;

		CLib0 lib;
	/*	AfxMessageBox(lib.floattostr(p_point[0])+" "+
			          lib.floattostr(p_point[1])+" "+
					  lib.floattostr(p_point[2]));*/
		//set carrier
	    carrier_id = sdoc->obj_selector ;
		//find carrer side
		FindCarrierSide(p_point[0],p_point[1],p_point[2]); 

		if (carrier_side ==_NOWHERE_) 
		{
          AfxMessageBox("Invalid object data");	
		  //delete this object (it is the last and invisible)
		  DeleteObject(sdoc->ObjCount-1); 
		  //set object none...
		  sdoc->new_object = _NONE_ ;
		}
        else
		{
		  //set totals
		  totalx = p_point[0];
          totaly = p_point[1];
		  totalz = p_point[2];
          //set object rotation axis
          obj_raxisX = 0;
		  obj_raxisY = 1;
		  obj_raxisZ = 0;
		  //get real rotation..
		  rotangle = GetGlobalObjDirection(p_point,p_normal);
		  //set local rotation
		  local_rot = 0;
          //init object side...
		  SetObjectSide(theApp.ObjSidePosition);
          
		  //*****INVENTOR :
	      MakeObjVisible();
		  RotateObjectTo(local_rot);
	      SetTranslation(SbVec3f(totalx,totaly,totalz));
		  ProjectObjectTo(outlook); 

		  GetBox();   //<<<<<-------------------------------- εγκιβωτισμος

	      SaveProperties();
 
		  sdoc->new_object = _NONE_ ; 		
		  sdoc->obj_selector = sdoc->ObjCount-1 ;
		  //set battery on..
		  sdoc->BATTERY = true;

		  ShowRefPoints(150.0); //<<<----------------------- show points
		  SelectObject();
		}
}


float CGExternal::GetBatteryLength()
{
	float len , len1, len2, Lsum ,Rsum , sum;
    int my_prev , my_next ;
   
	Lsum = Rsum = 0 ;

	len = GetObjectLength();

	my_prev = prior_id ;
    
    while (my_prev!=0)
	{
       CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object 

	   //get prev object
	   my_prev = prv->prior_id ;
       len1 = prv->GetObjectLength();
	   Lsum = Lsum + len1; 
	}

	my_next = next_id ;

    while (my_next!=0)
	{
       CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object 

	   //get next object
	   my_next = nxt->next_id ;
	   len2 = nxt->GetObjectLength();
	   Rsum = Rsum + len2;
	}

    sum = (len + Lsum + Rsum); 

	return sum ;
}


float CGExternal::GetBatteryRightDistance()
{
	float rgt;
	int my_next ;

	rgt = GetRightDistance();
	my_next = next_id ;

	while (my_next!=0)
	{
       CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object

	   rgt = nxt->GetRightDistance();

	   //get next object
	   my_next = nxt->next_id ;
    } 

	return rgt;
}


float CGExternal::GetBatteryLeftDistance()
{
	float lft ;
	int my_prev ;

	lft = GetLeftDistance();     
	my_prev = prior_id ;

    while (my_prev!=0)
	{
       CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object 

	   lft = prv->GetLeftDistance();

	   //get prev object
	   my_prev = prv->prior_id ;
    }

	return lft;
}



float CGExternal::SetBatteryRightDistance(float val)
{
	float bright ,carrier_length , objLength, objLength2, objLsum;
	int my_next ;

	objLsum = 0;
    objLength = GetObjectLength();
	carrier_length = GetCarrierLength();

	bright = carrier_length - (val + objLength);

	my_next = next_id ;

	while (my_next!=0)
	{
       CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object
	   
	   objLength2 = nxt->GetObjectLength();
	   objLsum = objLsum + objLength2 ;

	   //get next object
	   my_next = nxt->next_id ;
    }
	//objLength = length of selected object / objLsum = sum length of the others
	bright = (carrier_length - val - objLsum - objLength); 

	return bright;
}

//set object x distance from wall limit (left distance)
float CGExternal::SetBatteryLeftDistance(float val)
{
	float bleft ,objLsum ,objLength;
	int my_prev ;

	objLsum = 0;
	bleft = val ;
      
	my_prev = prior_id ;
    while (my_prev!=0)
	{
       CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get next object 

	   objLength = prv->GetObjectLength();
	   objLsum = objLsum + objLength ;

	   //get prev object
	   my_prev = prv->prior_id ;
  
    }
	bleft = val + objLsum ;

	return bleft;
}


//move object on carrier surface
void CGExternal::MoveObjectTo(float d1,float d2)
{
	float objX,objY,objZ ;

	MoveOnCarrier(d1,d2,&objX,&objY,&objZ);

	//update totals
	totalx  = objX;
	totaly  = objY;
	totalz  = objZ;

	//INVENTOR:
	SetTranslation(SbVec3f(totalx , totaly , totalz));
}


//move all the battery objects...
void CGExternal::MoveBattery()
{
	int my_next, my_prev ;
	float px0,py0,pz0,px1,py1,pz1;


    px0 = ssx[_DNBKRIGHT_];  //get selected object right back point
	py0 = ssy[_DNBKRIGHT_];
	pz0 = ssz[_DNBKRIGHT_];
	px1 = ssx[_DNBKLEFT_];  //get selected object left back point
	py1 = ssy[_DNBKLEFT_];
	pz1 = ssz[_DNBKLEFT_];

	my_next    = next_id ;  //get the selected object next number
	my_prev    = prior_id ;  //get the selected object previous number

	//first move right objects of battering
    while (my_next!=0)
	{
       CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object

 	   nxt->totalx = px0; //set next object left point = selected right point
	   nxt->totaly = py0;
	   nxt->totalz = pz0;

	   //INVENTOR:
	   nxt->SetTranslation(SbVec3f(nxt->totalx,nxt->totaly,nxt->totalz));
	   nxt->GetBox();   //<<<<<-------------------------------- εγκιβωτισμος

	   px0 = nxt->ssx[_DNBKRIGHT_]; //save current back right point
	   py0 = nxt->ssy[_DNBKRIGHT_]; //for the next obj...
	   pz0 = nxt->ssz[_DNBKRIGHT_];

	   //get next object
	   my_next = nxt->next_id ; 
	}

	//secontary move left objects...
	while (my_prev!=0)
	{
       CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object

	   SbVec3f Length    = prv->GetObjectVector();  //get direction vector
	   SbVec3f dirLength = Length;//as is...

	   prv->totalx = px1 - dirLength[0]; 
	   prv->totaly = py1 - dirLength[1];
	   prv->totalz = pz1 - dirLength[2];

	   //INVENTOR:
	   prv->SetTranslation(SbVec3f(prv->totalx,prv->totaly,prv->totalz));
	   prv->GetBox();   //<<<<<-------------------------------- εγκιβωτισμος

	   px1 = prv->ssx[_DNBKLEFT_]; //save current back right point
	   py1 = prv->ssy[_DNBKLEFT_]; //for the next obj...
	   pz1 = prv->ssz[_DNBKLEFT_];
   
	   //get prev object
	   my_prev = prv->prior_id ;
	}
}

/********************* rotate object **************************/
void CGExternal::RotateObjectTo(float ang)
{
	//calculate real rotation ...
	global_rot = rotangle + ang ;
	if (global_rot>360) global_rot = (global_rot - 360);

    //rotate...
    SetRotationAngle(DegreesToRadians(global_rot));

}

//rotate all the battery objects...
void CGExternal::RotateBattery()
{
	int my_next, my_prev ;

	my_next    = next_id ;  //get the selected object next number
	my_prev    = prior_id ;  //get the selected object previous number

	//first rotate right objects of battering
    while (my_next!=0)
	{
       CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object

	   //INVENTOR:
	   nxt->SetRotationAngle(GetRotationAngle()); //set rotation = selected rotation(set param !!!)
	   nxt->GetBox();   //<<<<<-------------------------------- εγκιβωτισμος

	   //get next object
	   my_next = nxt->next_id ; 
	}

	//secontary rotate left objects...
	while (my_prev!=0)
	{
       CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object

	   //INVENTOR:
	   prv->SetRotationAngle(GetRotationAngle()); //set rotation = selected rotation(set param!!!!)
	   prv->GetBox();   //<<<<<-------------------------------- εγκιβωτισμος
   
	   //get prev object
	   my_prev = prv->prior_id ;
	}
}

//set object projection (=outlook)
void CGExternal::ProjectObjectTo(float projection)
{
	float nx,ny,nz;

	//set projection ( = outlook )
    GetCarrierNormal(&nx, &ny, &nz);

    totalx = totalx + (nx * projection);
	totaly = totaly + (ny * projection);
	totalz = totalz + (nz * projection);

	//INVENTOR:
	SetTranslation(SbVec3f(totalx , totaly , totalz));

}

//project all the battery objects... (calculate new outlook)
void CGExternal::ProjectBattery()
{
	int my_next, my_prev ;

	my_next    = next_id ;  //get the selected object next number
	my_prev    = prior_id ;  //get the selected object previous number

	//first calculate outlook for right objects of battering
    while (my_next!=0)
	{
       CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object
       
	   //get new outlook
	   nxt->outlook = nxt->GetObjProjection();

	   //get next object
	   my_next = nxt->next_id ; 
	}

	//secontary calculate for the left objects...
	while (my_prev!=0)
	{
       CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object

	   prv->outlook = prv->GetObjProjection();

	   //get prev object
	   my_prev = prv->prior_id ;
	}
}

//************** input object (battery) **************/
void CGExternal::AttachObject()
{
	float px,py,pz;

	//get selected object
	CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]); 

	//get common data
	object_refpoint = ext->object_refpoint;
	carrier_id	= ext->carrier_id ; 
	carrier_side = ext->carrier_side ;
	object_side = ext->object_side ;


	//new object battering ...
	switch (theApp.ObjDirection)
    {
	  case 1 : { //right 
		          totalx = ext->ssx[_DNBKRIGHT_];
				  totaly = ext->ssy[_DNBKRIGHT_];
				  totalz = ext->ssz[_DNBKRIGHT_];

		          //INVENTOR:
		          MakeObjVisible();
	              SetTranslation(SbVec3f(totalx,totaly,totalz));
				  //float nx,ny,nz;
				  //ext->GetCarrierNormal(&nx,&ny,&nz); //<<<<<<----- ?????
				  //SbRotation *sbrot = new SbRotation(SbVec3f(0,0,1),SbVec3f(nx,ny,nz));
	              SetRotationAngle(ext->GetRotationAngle());
				  GetBox();   //<<<<<-------------------------------- εγκιβωτισμος

                  //change new object attributes
				  outlook = GetObjProjection();//calculate outlook
		          next_id = ext->next_id ; //the next value of selected object
                  prior_id = sdoc->obj_selector ; //= ο αριθμος του επιλεγμένου object
	              //change selected object attributes
	              ext->next_id = sdoc->ObjCount-1 ; //= ο αριθμος του νεου object

				  //rebuild .................
				  px = ssx[_DNBKRIGHT_];  //get new object right back point
				  py = ssy[_DNBKRIGHT_];
				  pz = ssz[_DNBKRIGHT_];
				  int my_next = next_id ;  //get the new object next number
				  int meter = 0;

	              while (my_next!=0)
				  {
                     CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object

					 nxt->totalx = px; //set new object right back point as left(total) of next object
				     nxt->totaly = py;
				     nxt->totalz = pz;

		             //INVENTOR:
	                 nxt->SetTranslation(SbVec3f(nxt->totalx,nxt->totaly,nxt->totalz));
				     nxt->GetBox();   //<<<<<-------------------------------- εγκιβωτισμος

					 nxt->outlook = nxt->GetObjProjection();  //calculate outlook

					 px = nxt->ssx[_DNBKRIGHT_]; //save current back right point
				     py = nxt->ssy[_DNBKRIGHT_]; //for the next obj...
				     pz = nxt->ssz[_DNBKRIGHT_];

	                 //get next object
	                 my_next = nxt->next_id ; 
					 meter+=1;
				  }

				  if (next_id>0)
                  {
				    //save first next attributes
				    CGExternal *nxt = ((CGExternal*)sdoc->Obj[next_id]);
				    nxt->prior_id = sdoc->ObjCount-1 ; //= ο αριθμος του νεου object
	                nxt->SaveProperties();
                  }

				  break; 
               }
	          
      case 2 : { //left
		  		 SbVec3f Length    = GetObjectVector();  //get direction vector
	             SbVec3f dirLength = ext->GetObjectDirection(Length);

		         totalx = ext->ssx[_DNBKLEFT_] - dirLength[0];
				 totaly = ext->ssy[_DNBKLEFT_] - dirLength[1];
				 totalz = ext->ssz[_DNBKLEFT_] - dirLength[2];

		         //INVENTOR:
		         MakeObjVisible();
	             SetTranslation(SbVec3f(totalx,totaly,totalz));
	             SetRotationAngle(ext->GetRotationAngle());
				 GetBox();   //<<<<<-------------------------------- εγκιβωτισμος

                 //change new object attributes
				 outlook = GetObjProjection();  //calculate outlook
				 next_id = sdoc->obj_selector ; //= ο αριθμος του επιλεγμένου object
	             prior_id = ext->prior_id ; //the previous val of selected object
				 //change selected object attributes
	             ext->prior_id = sdoc->ObjCount-1 ; //= ο αριθμος του νεου object
                 
				 //rebuild ....................
				 px = ssx[_DNBKLEFT_];  //get new object left back point
				 py = ssy[_DNBKLEFT_];
				 pz = ssz[_DNBKLEFT_];
				 int my_prev = prior_id ;  //get the new object previous number
				 int meter = 0;

	             while (my_prev!=0)
				 {
                    CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object

					Length    = prv->GetObjectVector();  //get direction vector
	                dirLength = Length;//prv->GetObjectDirection(Length);

					prv->totalx = px - dirLength[0]; //set new object right back point as left(total) of next object
				    prv->totaly = py - dirLength[1];
				    prv->totalz = pz - dirLength[2];

		            //INVENTOR:
	                prv->SetTranslation(SbVec3f(prv->totalx,prv->totaly,prv->totalz));
				    prv->GetBox();   //<<<<<-------------------------------- εγκιβωτισμος

				    prv->outlook = prv->GetObjProjection();  //calculate outlook

					px = prv->ssx[_DNBKLEFT_]; //save current back left point
				    py = prv->ssy[_DNBKLEFT_]; //for the prev obj...
				    pz = prv->ssz[_DNBKLEFT_];

					//get next object
	                my_prev = prv->prior_id ;
	                meter+=1;
				 }
				 if (prior_id>0)
                 { 
                   //save first previous attributes
				   CGExternal *prv = ((CGExternal*)sdoc->Obj[prior_id]);
				   prv->next_id = sdoc->ObjCount-1 ; //= ο αριθμος του νεου object
	               prv->SaveProperties();
				 }

				 break; 
               }
    }
	SaveProperties();
	ext->SaveProperties();

	sdoc->new_object = _NONE_;  //δεν χρειάζεται να κάνουμε click για να εμφανιστει το αντικείμενο

	sdoc->obj_selector = sdoc->ObjCount-1 ;
    SelectObject();
	ShowRefPoints(150.0); //<<<----------------------- show points

	//.. and set battery on..
	sdoc->BATTERY = true;
	sdoc->SetModifiedFlag() ;
	sdoc->UpdateAllViews(NULL);  
}



//rebuild the battery objects at right or left and change the attributes
//delete mode ...
void CGExternal::DelRebuildButtery()
{
    int my_next, my_prev, meter;
	float px,py,pz;

	//check if there are battering ...
	my_next = next_id ;   //get the selected object next number
    my_prev = prior_id ;  //get the selected object previous number

    if ((my_next!=0) || (my_prev!=0))
    { 
	  meter=0; //zero meter
	  switch (theApp.ObjDirection)
	  {
	    case 1 : { //right
		          px = ssx[_DNBKLEFT_];  //get selected object left back point
				  py = ssy[_DNBKLEFT_];
				  pz = ssz[_DNBKLEFT_];

	              while (my_next!=0)
				  {
                     CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object

					 nxt->totalx = px; //set next object selected right back point
				     nxt->totaly = py;
				     nxt->totalz = pz;

		             //INVENTOR:
	                 nxt->SetTranslation(SbVec3f(nxt->totalx,nxt->totaly,nxt->totalz));
				     nxt->GetBox();   //<<<<<-------------------------------- εγκιβωτισμος

					 nxt->outlook = nxt->GetObjProjection();  //calculate outlook

					 px = nxt->ssx[_DNBKLEFT_]; //save current back left point
				     py = nxt->ssy[_DNBKLEFT_]; //for the next obj...
				     pz = nxt->ssz[_DNBKLEFT_];

	                 //get next object
	                 my_next = nxt->next_id ; 
				  	 meter+=1;
				  }
				  //Change the attributes of objects
	              if (next_id>0)
				  {
                    CGExternal *nxt = ((CGExternal*)sdoc->Obj[next_id]); //get first next of selected object
                    nxt->prior_id = prior_id;
	                nxt->SaveProperties();
				  }
				  break;
				 }
        case 2 : { //left
                  px = ssx[_DNBKRIGHT_];  //get selected object left back point
				  py = ssy[_DNBKRIGHT_];
				  pz = ssz[_DNBKRIGHT_];

	              while (my_prev!=0)
				  {
                     CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object

					 SbVec3f Length    = prv->GetObjectVector();  //get direction vector
	                 SbVec3f dirLength = Length;//as is...
	                  
					 prv->totalx = px - dirLength[0]; 
				     prv->totaly = py - dirLength[1];
				     prv->totalz = pz - dirLength[2];

		             //INVENTOR:
	                 prv->SetTranslation(SbVec3f(prv->totalx,prv->totaly,prv->totalz));
				     prv->GetBox();   //<<<<<-------------------------------- εγκιβωτισμος

					 prv->outlook = prv->GetObjProjection();  //calculate outlook

					 px = prv->ssx[_DNBKLEFT_]; //save current back left point
				     py = prv->ssy[_DNBKLEFT_]; //for the next obj...
				     pz = prv->ssz[_DNBKLEFT_];

					 //get prev object
	                 my_prev = prv->prior_id ;
	                 meter+=1;
				  }
				  //Change the attributes of objects
				  if (prior_id>0)
				  {
                     CGExternal *prv = ((CGExternal*)sdoc->Obj[prior_id]);  //get first prev of selected object 
	                 prv->next_id = next_id;
                     prv->SaveProperties();
				  }
				  break;
				 }
	  }

	  //change selected (deleted) object attributes
	  next_id = 0;
	  prior_id = 0;
	  carrier_id = 0;
	  carrier_side = _NONE_ ;
	  object_side = _NOWHERE_ ;

	  SaveProperties();
	} //if
}



//rebuild the battery objects at right or left and change the attributes
//delete object and break the battering in 2 butterings
//extent delete mode...
void CGExternal::ExtDelRebuildButtery()
{
	int the_next, the_prev;

	//check if there are battering ...
	the_next = next_id ;  //get the selected object next number
    the_prev = prior_id ;  //get the selected object previous number

    if ((the_next!=0) || (the_prev!=0))
    {
	  //..do nothing 
      //just set the atributes...
	  if (next_id!=0)
	  {
		//get next of selected object
        CGExternal *nxt = ((CGExternal*)sdoc->Obj[next_id]);       
        nxt->prior_id = 0; //break..
	    nxt->SaveProperties();
	  }
      if (prior_id!=0)
	  {
		//get prev of selected object 
        CGExternal *prv = ((CGExternal*)sdoc->Obj[prior_id]);     
	    prv->next_id = 0; //break..
        prv->SaveProperties();
	  }

	  //change selected (deleted) object attributes
	  next_id = 0;
	  prior_id = 0;
	  carrier_id = 0;
	  carrier_side = _NONE_ ;
	  object_side = _NOWHERE_ ;
	  SaveProperties();
	} //if
}


//delete object ... (if battery ..from battering)...
void CGExternal::DelObject(int aanum,int mode)
{
	if (IsAttachedObject(aanum)==false)
	{
	  //rebuild the battery -before- delete the selected object
	  if (mode==0) DelRebuildButtery(); 
	          else ExtDelRebuildButtery();

	  DeleteObject(aanum);
	}
	else
        AfxMessageBox("          Access denied.\n Other object(s) use this object.");
}



//************** replace object  **************/
void CGExternal::ReplaceObject()
{
	int mynext,myprior,mycarrier,myoutlook,mycarrier_side,myobj_side,obj_rp ;
    float tx,ty,tz , myangle ,mylocal_rot;

	//get selected-old object ...
	CGExternal *the_old = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]);//old

    //save selected-old data
	tx             = the_old->totalx;
    ty             = the_old->totaly;
	tz             = the_old->totalz;
	myangle        = the_old->rotangle;
	mylocal_rot    = the_old->local_rot;
	mynext         = the_old->next_id ;
	myprior        = the_old->prior_id ;
	mycarrier      = the_old->carrier_id ;
	mycarrier_side = the_old->carrier_side ;
	myobj_side     = the_old->object_side ;
	myoutlook      = the_old->outlook;
	obj_rp         = the_old->object_refpoint;


	//delete selected (old) object
	the_old->DelObject(sdoc->obj_selector,0);

	if ((mynext!=0) || (myprior!=0)) //more than one object battering
    {
      switch (theApp.ObjDirection)
	  {
  	    case 1 : { //right
			       if (myprior!=0)
                   {
					   //select previous object
					  CGExternal *prev_ext = ((CGExternal*)sdoc->Obj[myprior]);
					  prev_ext->SelectObject();
                      //set selector to prior object
                      sdoc->obj_selector = myprior ;

					  //Attach the object
					  AttachObject();
                   }
				   else
                   if (mynext!=0)
                   {
                      //select next object
					  CGExternal *next_ext = ((CGExternal*)sdoc->Obj[mynext]);
					  next_ext->SelectObject();
                      //set selector to next object
                      sdoc->obj_selector = mynext ;

					  //Attach the object
					  theApp.ObjDirection=2; //switch the direction
					  AttachObject();
					  theApp.ObjDirection=1; //..and set the previous direction 
                   }
	  	           break;
				 }
        case 2 : { //left ... same as above but opposite...
			       if (mynext!=0)
                   {
                      //select next object
					  CGExternal *next_ext = ((CGExternal*)sdoc->Obj[mynext]);
					  next_ext->SelectObject();
                      //set selector to next object
                      sdoc->obj_selector = mynext ;

					  //Attach the object
					  AttachObject();
                   }
				   else
                   if (myprior!=0)
                   {
                      //select previous object
					  CGExternal *prev_ext = ((CGExternal*)sdoc->Obj[myprior]);
					  prev_ext->SelectObject();
                      //set selector to prior object
                      sdoc->obj_selector = myprior ;

					  //Attach the object
					  theApp.ObjDirection=1; //switch the direction
					  AttachObject();
					  theApp.ObjDirection=2; //..and set the previous direction
                   }
		           break;
				 }
	  }
	}
	else //only one object
    {
	   object_refpoint = obj_rp;
	   rotangle = myangle; //get real rotation
	   local_rot = mylocal_rot; //get local rotation

	   //in this case get old totals
	   totalx = tx;
	   totaly = ty;
	   totalz = tz;

	   //*** INVENTOR rendering ***
	   MakeObjVisible();
	   SetTranslation(SbVec3f(totalx,totaly,totalz));
	   //SetRotationAngle(myangle);
	   RotateObjectTo(local_rot);
	   GetBox();   //<<<<<-------------------------------- εγκιβωτισμος

       //save new object attributes (get it from saved old-selected-replaced object)
	   next_id      = mynext ;
	   prior_id     = myprior ;
	   carrier_id   = mycarrier ;
	   carrier_side = mycarrier_side;
	   object_side  = myobj_side;
	   outlook      = myoutlook ;

	   SaveProperties();

	   SelectObject();
	   sdoc->obj_selector = sdoc->ObjCount-1 ;

	   ShowRefPoints(150.0); //<<<----------------------- show points

	   sdoc->new_object = _NONE_ ;  //δεν χρειάζεται να κάνουμε click για να εμφανιστει το αντικείμενο

	   //.. and set battery on..
	   sdoc->BATTERY = true;

	   sdoc->SetModifiedFlag() ;
	   sdoc->UpdateAllViews(NULL);   
    }
}



//Ungroup the selected object battering
void CGExternal::UnGroupObjects()
{
	int my_next, my_prev , meter;

	my_next = next_id ;  //get the selected object next number
	my_prev = prior_id ; //get the selected object previous number

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
	next_id = 0;
	prior_id = 0;
	SaveProperties();

}

//copy ...
void CGExternal::CopyObject(int aanumber)
{
        CLib0 lib;
        SoSeparator *clone ; 

        //save aanumber
		sdoc->LastCopy = aanumber;

		//initialize buffer...
		if (sview->sep_buffer!=NULL) sview->sep_buffer->removeAllChildren();
		else sview->sep_buffer = new SoSeparator ;

	    //copy object (geometry & attributes nodes) from inventor to buffer...
	    SoSeparator *myroot = sdoc->root;
        SbName name = "GExternal"+lib.inttostr(aanumber) ; 

	    clone = (SoSeparator *)SoNode::getByName(name);

		SoNode *myGeom = clone->getChild(4); //get "Geometry" 
	    sview->sep_buffer->addChild( myGeom );
		SoNode *myAttr = clone->getChild(5); //get "Attributes" 
	    sview->sep_buffer->addChild( myAttr );

		//copy data...
		CGExternal *copied = ((CGExternal*)sdoc->Obj[aanumber]);
		((CGExternal *) sdoc->external_buffer) = copied ;
}

//paste ...
void CGExternal::PasteObject()
{	    
	    CLib0 lib;

	    CGExternal *ob ;
        SoSeparator *sep ;

        //prepare counters and data..
		ob = new CGExternal ;
	    sdoc->Obj[sdoc->ObjCount] = ob ; sdoc->ObjCount++ ;
		ob->sep = new SoSeparator ;
		sep = ob->sep ;
 

		//*****create pasted object...
		SoTransform *xform = new SoTransform ;
		sep->addChild( xform ) ;

		SoDrawStyle *ds = new SoDrawStyle ;
		sep->addChild(ds) ;
		ds->style = SoDrawStyle::INVISIBLE ;

	    SoPickStyle *ps = new SoPickStyle;
	    sep->addChild(ps) ;
        ps->style.setValue(SoPickStyle::SHAPE) ;

	    SoMaterial  *mat = new SoMaterial; 
        sep->addChild(mat) ;
        
		//copy object (geometry & attributes) from buffer...
		SoNode *myGeom = sview->sep_buffer->getChild(0); //get "Geometry" 
	    sep->addChild( myGeom );
		SoNode *myAttr = sview->sep_buffer->getChild(1); //get "Attributes" 
	    sep->addChild( myAttr );
        //************ end of creation

		//finaly...set name & counters & data
	    //ob->offset = sdoc->ob_offset ; sdoc->ob_offset++ ;
		ob->name   = "GExternal" + lib.inttostr(sdoc->ObjCount-1); 
		ob->offset = sdoc->ObjCount-1;
        ob->id     = _EXTERNAL_;
		ob->code   = sdoc->external_buffer->code ;
		ob->descr  = sdoc->external_buffer->descr ;

		int i;
		for ( i = 0 ; i < 10 ; i++ )
			ob->eid_id[i] = sdoc->external_buffer->eid_id[i];


		//get min..max
		ob->xmin = sdoc->external_buffer->xmin ;
		ob->ymin = sdoc->external_buffer->ymin ;
		ob->zmin = sdoc->external_buffer->zmin ;
		ob->xmax = sdoc->external_buffer->xmax ;
		ob->ymax = sdoc->external_buffer->ymax ;
		ob->zmax = sdoc->external_buffer->zmax ;

		sdoc->new_object = _EXTERNAL_;

		ob->ObjectToInventor(sdoc->root) ;
}

//find if other objects is attached to this object
bool CGExternal::IsAttachedObject(int objno)
{
    int objs;
	bool attached = false ;
	int obj_sum = sdoc->ObjCount;

	//for objs=wallno because it is inpossible to have obj attached before this.
	for(objs = objno;objs < obj_sum ; objs++)
	{ 
      //WARNING : check for NULL pointers
	  if (sdoc->Obj[objs]!=NULL)
	  {
		//WARNING : the loop must be not check the object himself
		if ((sdoc->Obj[objs]->IsKindOf(RUNTIME_CLASS(CGExternal))) && (objs!=objno))
        {
          CGExternal *ext = ((CGExternal*)sdoc->Obj[objs]);
		  if (ext->carrier_id == objno ) 
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
void CGExternal::DeleteObject(int aanumber)
{
    CLib0 lib; 

    if (IsAttachedObject(aanumber)==false)
	{
		//deselect ...
	    sview->GetSelectionNode()->deselectAll();
        sdoc->obj_selector=-1;

        //delete object from inventor...
		SoSeparator *myroot = sdoc->root;
		SoSeparator *del_external;
        SbName name = "GExternal"+lib.inttostr(aanumber) ; 
		del_external = (SoSeparator *)SoNode::getByName(name);
		myroot->removeChild(del_external);

		//delete object from Object array
	    sdoc->Obj[aanumber]=NULL;
	}
	else
        AfxMessageBox("          Access denied.\n Other object(s) use this object.");

}

/////////////////////////////////////////////////////////////////////////////
// GExternalProp dialog


GExternalProp::GExternalProp(CWnd* pParent /*=NULL*/)
	: CDialog(GExternalProp::IDD, pParent)
{
	//{{AFX_DATA_INIT(GExternalProp)
	m_code = _T("");
	m_descr = _T("");
	m_xdist = 0.0f;
	m_yangle = 0.0f;
	m_ydist = 0.0f;
	m_leftdist = 0.0f;
	m_rightdist = 0.0f;
	m_x1dist = 0.0f;
	m_objLen = 0.0f;
	m_batLen = 0.0f;
	m_outlook = 0.0f;
	m_rotpoint = 0;
	//}}AFX_DATA_INIT
}


void GExternalProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GExternalProp)
	DDX_Text(pDX, IDC_CODE, m_code);
	DDX_Text(pDX, IDC_DESCR, m_descr);
	DDX_Text(pDX, IDC_XDIST, m_xdist);
    DDX_Text(pDX, IDC_YANGLE, m_yangle);	
	DDV_MinMaxFloat(pDX, m_yangle, 0.f, 360.f);
	DDX_Text(pDX, IDC_YDIST, m_ydist);
	DDV_MinMaxFloat(pDX, m_ydist, 0.f, 10000.f);
	DDX_Text(pDX, IDC_LEFT, m_leftdist);
	DDX_Text(pDX, IDC_RIGHT, m_rightdist);
	DDX_Text(pDX, IDC_X1DIST , m_x1dist);
	DDX_Text(pDX, IDC_OBJLEN, m_objLen);
	DDX_Text(pDX, IDC_BATLEN, m_batLen);
	DDX_Text(pDX, IDC_OUTLOOK, m_outlook);
	DDX_Text(pDX, IDC_ROTPOINT, m_rotpoint);
	DDV_MinMaxInt(pDX, m_rotpoint, 4000, 4004);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GExternalProp, CDialog)
	//{{AFX_MSG_MAP(GExternalProp)
        // NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GExternalProp message handlers

