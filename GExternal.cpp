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
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoSelection.h>

#define PI 3.1415926


/////////////////////////////////////////////////////////////////////////////
// CGExternal

IMPLEMENT_DYNAMIC( CGExternal, CObject )

CGExternal::CGExternal()
{
	sep = NULL ;

	next_id = 0;
	prior_id = 0;
	totalx = totaly =totalz = 0; //init totals
}

CGExternal::~CGExternal()
{
}


/*======================== ObjectToInventor ================*/

void CGExternal::ObjectToInventor ( SoSeparator *root )
{
	// inherited action
	CGObject::ObjectToInventor(root) ;

	//το αντικειμενο εχει τοποθετηθει αορατο στην θεση 0,0,0
	//δεν χρειαζεται εγκιβωτισμος εδω διοτι τα globals ειναι 0,0,0
	//κανουμε τον εγκιβωτισμο στην AddNewObject οπου και το object
	//παιρνει την click θεση του
	//GetBox();  //<<<<<-------------------------------- εγκιβωτισμος


	SaveProperties() ;     
	root->addChild(sep) ;
  
    //check for ...
	if (sdoc->BATTERING)  //battering ...
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
	lib.setSoSFFloatProp ( attr, SbName("yangle"+soff), yangle ) ;

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
	yangle		= lib.getSoSFFloatProp(SbName("yangle"+soff)) ;
}

void CGExternal::GetBox()
{
	int simia;
	SbMatrix mymatrix;
	SbVec3f source , target;

	// inherited action
	CGObject::GetBox() ;

	//assign min(xyz),max(xyz) 
	//στην περιπτωση των externals τα min,max's ειναι τα ακροτατα σημεια
	//του αντικειμένου στο δικο του συστημα συντεταγμενων...
	//αρα οταν θελουμε τις global τιμες αρκει να προσθεσω τα totals = object translation

	//****** down
	ssx[0] = xmin ;//+ totalx;
    ssy[0] = ymin ;//+ totaly;
	ssz[0] = zmin ;//+ totalz;

	ssx[1] = xmin ;//+ totalx;
    ssy[1] = ymin ;//+ totaly;
	ssz[1] = zmax ;//+ totalz;

	ssx[2] = xmax ;//+ totalx;
    ssy[2] = ymin ;//+ totaly;
	ssz[2] = zmax ;//+ totalz;

	ssx[3] = xmax ;//+ totalx;
    ssy[3] = ymin ;//+ totaly;
	ssz[3] = zmin ;//+ totalz;

	//****** up
	ssx[4] = xmin ;//+ totalx;
    ssy[4] = ymax ;//+ totaly;
	ssz[4] = zmin ;//+ totalz;

	ssx[5] = xmin ;//+ totalx;
    ssy[5] = ymax ;//+ totaly;
	ssz[5] = zmax ;//+ totalz;

	ssx[6] = xmax ;//+ totalx;
    ssy[6] = ymax ;//+ totaly;
	ssz[6] = zmax ;//+ totalz;

	ssx[7] = xmax ;//+ totalx;
    ssy[7] = ymax ;//+ totaly;
	ssz[7] = zmin ;//+ totalz;

    //SET ROTATION
	//get matrix
	mymatrix = GetObjectMatrix();

	for (simia=0 ; simia<8 ; simia++)
	{
       source[0] = ssx[simia];
       source[1] = ssy[simia];
	   source[2] = ssz[simia];

	   //multiply matrix * simio
	   mymatrix.multVecMatrix(source , target);

	   ssx[simia] = target[0] + totalx;
	   ssy[simia] = target[1] + totaly;
	   ssz[simia] = target[2] + totalz;
	}

/*	for (int s=0;s<8;s++)
		AfxMessageBox("Globals "+lib.floattostr(ssx[s])+" "+
		                         lib.floattostr(ssy[s])+" "+
				                 lib.floattostr(ssz[s]));
*/
}

/*======================= EditProperties ========================*/
int CGExternal::EditProperties ( CDocument *d, SoSeparator *root ) 
{
	CLib0 lib;
    float comparedistX,comparedistX1,comparedistY ; //compare purpose
	float compL , compR , compAngle ,compOut ;
	float x,y,z,r;

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

	if ((carrier_side ==_NONE_) || 
		(object_side == _NOWHERE_))
	{
       AfxMessageBox("Invalid object data");
	   return 0 ;
    }

    //Calculate selected object distances
    xdist  = GetLeftDistance();
	x1dist = GetRightDistance();

	//Calculate selected object or whole battering wall distances
	Ldist = GetBatteryLeftDistance();
	Rdist = GetBatteryRightDistance();

	//get object height
	ydist = GetDistanceY();

	//Get object rotation
	yangle = RadiansToMires( GetRotationAngle() );

	GExternalProp *dlg = new GExternalProp ;

	dlg->m_code		= code ;
	dlg->m_descr	= descr ;
	dlg->m_yangle	= yangle ; compAngle = yangle ;
	dlg->m_xdist	= xdist ; comparedistX = xdist; 
	dlg->m_ydist	= ydist ; comparedistY = ydist;
	dlg->m_leftdist = Ldist ; compL = Ldist;
	dlg->m_rightdist= Rdist ; compR = Rdist;
	dlg->m_x1dist   = x1dist; comparedistX1 = x1dist;
	dlg->m_outlook  = outlook ; compOut = outlook ;

    dlg->m_objLen = GetObjectLength(); 
	dlg->m_batLen = GetBatteryLength(); 

	int res = dlg->DoModal() ;

	if (res == IDOK)   
	{
		sdoc->SaveUndo(); //save scene for undo...

		code	= dlg->m_code ;
		descr	= dlg->m_descr ;
		yangle	= dlg->m_yangle ;
		outlook	= dlg->m_outlook ;
        xdist   = dlg->m_xdist ; 
		ydist   = dlg->m_ydist ;
        Ldist   = dlg->m_leftdist ;
		Rdist   = dlg->m_rightdist ;
		x1dist  = dlg->m_x1dist ;

        x=xdist;
		y=ydist;
		z=outlook;
		r=MiresToRadians(yangle);

		//rotate...
		if (fabs(yangle - compAngle) > 0.01)
		{
			RotateObject(r ,0);
        }

        
		// set x object (not buttering) translation
		if (fabs(xdist - comparedistX) > 0.001)
		{
			x = SetLeftDistance(xdist);
			goto out;
		}
		if (fabs(x1dist - comparedistX1) > 0.001) 
		{
		    x = SetRightDistance(x1dist);
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

		
out: ;  //move...
        MoveObjectTo(x,y,z) ;
		MoveButtering(x,y,z);
		
		ShowRefPoints(150.0); //<<<----------------------- show points
	
		SaveProperties() ;    
	}

	return res ;
}



void CGExternal::AddNewObject(SbVec3f p_point, SbVec3f p_normal)
{
		// inherited action
	    CGObject::AddNewObject(p_point,p_normal) ;

		object_refpoint = _DNBKLEFT_;
		//set totals
		totalx = p_point[0];
        totaly = p_point[1];
		totalz = p_point[2];

		//set carrier
	    carrier_id = sdoc->obj_selector ;
		//find carrer side
		FindCarrierSide(p_point[0],p_point[1],p_point[2]); 
		//object's side
		object_side = _BACK_; //<<<<------------ = default side
		//set projection
		outlook = 0;

		if ((carrier_side ==_NONE_) || 
		    (object_side == _NOWHERE_))
		{
          AfxMessageBox("Invalid object data");	
		  //delete this object (it is the last and invisible)
		  DeleteObject(sdoc->ObjCount-1); 
		  sdoc->new_object = _NONE_ ;
		}
        else
		{
		  //*****INVENTOR rendering
		  SoSeparator *ext_sep = sep ;
		  MakeObjVisible();
		  SetTranslation(p_point);

	      float n1,n2,n3;
          GetCarrierNormal(&n1,&n2,&n3);
		  SoRotation *rot	= (SoRotation *)ext_sep->getChild(2) ;   
		  SbRotation *sbrot = new SbRotation(SbVec3f(0,0,1),SbVec3f(n1,n2,n3));
		  rot->rotation.setValue(*sbrot) ;
          //**********
		  //παιρνουμε τον εγκβωτισμο του μετα το click...
		  GetBox();   //<<<<<-------------------------------- εγκιβωτισμος

		  //MoveObjectTo(p_point[0],p_point[1],0);//<<<<<--------check it????
          
	      SaveProperties();
 
		  sdoc->new_object = _NONE_ ; 
		
		  SelectObject();
		  sdoc->obj_selector = sdoc->ObjCount-1 ;

		  ShowRefPoints(150.0); //<<<----------------------- show points

		  //.. and set battering on..
		  sdoc->BATTERING = true;
		}
}




//get matrix
SbMatrix CGExternal::GetObjectMatrix()
{   
    SbVec3f Raxis ;
	float Rangle ;
	SbMatrix matrix;

	SoSeparator *mysep = sep ;

	SoRotation *ext_r = (SoRotation *)mysep->getChild(2) ;
	ext_r->rotation.getValue(Raxis , Rangle); 

	SbRotation *sbrot = new SbRotation(Raxis , Rangle); 
	sbrot->getValue(matrix); 

	return matrix;
}


//get object vectors
SbVec3f CGExternal::GetObjectVectors()
{
	SbVec3f p1 , p2, dianisma ;

	//get left and right base points of selected object
    //CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]);
    p1[0] = left_base_point[0] ;
    p1[1] = left_base_point[1] ;
    p1[2] = left_base_point[2] ;

    p2[0] = right_base_point[0] ;
    p2[1] = right_base_point[1] ;
    p2[2] = right_base_point[2] ;

/*	p1[0] = ssx[0] ;//<<<<<---------------------- error ????
    p1[1] = ssy[0] ;
    p1[2] = ssz[0] ;

    p2[0] = ssx[3] ;
    p2[1] = ssy[3] ;
    p2[2] = ssz[3] ;

*/
    //get distances
    dianisma[0] = p2[0] - p1[0];
    dianisma[1] = p2[1] - p1[1];
    dianisma[2] = p2[2] - p1[2]; 
			   
	return dianisma ;
}

SbVec3f CGExternal::GetObjectDirection(SbVec3f source)
{
	SbMatrix mymatrix;
	SbVec3f target ;

	//multiply dianisma by matrix 
	mymatrix = GetObjectMatrix();
    mymatrix.multVecMatrix(source , target);

	return target ;
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


/********************* Move object **************************/
void CGExternal::MoveObjectTo(float d1,float d2,float d3)
{
    CLib0 lib;
	float objX,objY,objZ ;
	float nx,ny,nz;
	float b; 
	SbVec3f vector ;

	//get carrier + object ref points
    GetCarrierSide();
	GetObjectSide();

	//calculations...
	b = sqrt( (pow( (pointX2 - pointX1), 2)) +  
		      (pow( (pointY2 - pointY1), 2)) + 
			  (pow( (pointZ2 - pointZ1), 2)) );

    //set x y translation
    objX = ( ( (pointX2 - pointX1) / fabs(b) ) * d1 + pointX1 ) ;
    objY = ( ( (pointY2 - pointY1) / fabs(b) ) * d1  + d2 + pointY1 ) ;
	objZ = ( ( (pointZ2 - pointZ1) / fabs(b) ) * d1 + pointZ1 ) ;

	//set projection (z trnaslation) = outlook
    GetCarrierNormal(&nx, &ny, &nz);
    objX = objX + (nx * d3);
	objY = objY + (ny * d3);
	objZ = objZ + (nz * d3);

	//update totals
	totalx  = objX;
	totaly  = objY;
	totalz  = objZ;
    //update box
	GetBox();  //<<<<<-------------------------------- εγκιβωτισμος

	SaveProperties();

	//INVENTOR:put new translation
	vector.setValue(totalx , totaly , totalz);
	SetTranslation(vector);
}


//move all the battering objects...
void CGExternal::MoveButtering(float x,float y,float z)
{
	int my_next, my_prev ;
    float newdest,sumlength,length;

	newdest = GetLeftDistance(); 
	length = GetObjectLength();

	sumlength = 0;

	my_next    = next_id ;  //get the selected object next number
	my_prev    = prior_id ;  //get the selected object previous number

	//first move right objects of battering
    while (my_next!=0)
	{
       CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object

	   sumlength = sumlength + length;
       nxt->MoveObjectTo(newdest+sumlength , y , z);
	   length = nxt->GetObjectLength();

	   //get next object
	   my_next = nxt->next_id ;
	}

	sumlength = 0;

	//secontary move left objects...
	while (my_prev!=0)
	{
       CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object

	   sumlength = sumlength + prv->GetObjectLength();
       prv->MoveObjectTo(newdest-sumlength , y , z);
   
	   //get prev object
	   my_prev = prv->prior_id ;
	}
}


//rotate the object(s) (with different ways if buttering)
void CGExternal::RotateObject(float angle,int typeof)
{
	int my_next, my_prev ;
	SbVec3f values , Lv , Rv;
	int meter ;
	CLib0 lib;

	//case 0 = περιστροφη μονο του επιλεγμενου αντικειμένου
	//τα υπολοιπα αντικειμενα απλως ακολουθουν την μεταβολη της συστοιχιας
	SetRotationAngle(angle);

    //if battering...
	switch (typeof)
    {
	   case 0 : {
		          //do nothing 
		          //εκτελειται η παραπανω εντολη η οποα ειναι κοινη
		          //για ολες τις περιπτωσεις
		          break;
				}
	   case 1 : {
		          //τα υπολοιπα αντικειμενα μενουν στην σειρα χωρις 
		          //να αλλαξει η περιστροφη τους
	              //MovRebuildButtering();
	              break;
				}
       case 2 : {
		          //τα υπολοιπα αντικειμενα περιστρεφονται  
		          //οπως το επιλεγμένο
	              my_next = next_id ;  //get the selected object next number
	              my_prev = prior_id ;  //get the selected object previous number
	              meter=0;

                  while (my_next!=0)
				  {
                    CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object 

	                //get next object
	                my_next = nxt->next_id ;
	                nxt->SetRotationAngle(angle);
	                meter+=1; 
				  }

                  meter=0;
	              while (my_prev!=0)
				  {
                    CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object
	   
	                //get prev object
	                my_prev = prv->prior_id ;
	                prv->SetRotationAngle(angle);
	                meter+=1;
				  }
				  break;
				}

	   default : break;
	}
}


//************************************************************


//************** input object (battering) **************/
void CGExternal::AttachObject()
{
	//CLib0 lib;
	//int my_next, my_prev, meter ;
    float distance,length,newlength,height;

	SoSeparator *obj_sep = sep;  //get new object sep
	CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]); //get selected object

	object_refpoint = ext->object_refpoint;

	//get common data
	//set carrier
	carrier_id	= ext->carrier_id ; 
	//set carrier side
	carrier_side = ext->carrier_side ;
	//set outlook
    outlook = ext->outlook;
	//set object_side
	object_side = ext->object_side ;

    //****INVENTOR rendering
	float n1,n2,n3;
    GetCarrierNormal(&n1,&n2,&n3);
	MakeObjVisible();
	//SetTranslation(p_point); επειδη γινεται moveobject παρακατω δεν χρειαζεται...
	SoRotation *rot	= (SoRotation *)obj_sep->getChild(2) ;   
	SbRotation *sbrot = new SbRotation(SbVec3f(0,0,1),SbVec3f(n1,n2,n3)) ;
	rot->rotation.setValue(*sbrot) ;
	//***********************
    //get box for new object distances calculation
	GetBox();   //<<<<<-------------------------------- εγκιβωτισμος

	distance  = ext->GetLeftDistance(); //get selected left distance
	length = ext->GetObjectLength(); //get selected length
	newlength = GetObjectLength();   //get new length 
	height = ext->GetHeightDistance();  //get height 


	//new object battering ...
	switch (theApp.ObjDirection)
    {
	  case 1 : { //right
		          MoveObjectTo(distance+length,height,outlook); 

                  //change new object attributes
		          next_id = ext->next_id ; //the next value of selected object
                  prior_id = sdoc->obj_selector ; //= ο αριθμος του επιλεγμένου object
	              //change selected object attributes
	              ext->next_id = sdoc->ObjCount-1 ; //= ο αριθμος του νεου object

				  break; 
               }
	          
      case 2 : { //left
		         MoveObjectTo(distance-newlength,height,outlook);

                 //change new object attributes
				 next_id = sdoc->obj_selector ; //= ο αριθμος του επιλεγμένου object
	             prior_id = ext->prior_id ; //the previous val of selected object
				 //change selected object attributes
	             ext->prior_id = sdoc->ObjCount-1 ; //= ο αριθμος του νεου object

				 break; 
               }
    }

	//rebuild battering (if there are battering) inserting mode
	InsRebuildButtering();

	SaveProperties();
	ext->SaveProperties();

	sdoc->new_object = _NONE_;  //δεν χρειάζεται να κάνουμε click για να εμφανιστει το αντικείμενο

	sdoc->obj_selector = sdoc->ObjCount-1 ;
    SelectObject();

	ShowRefPoints(150.0); //<<<----------------------- show points

	//.. and set battering on..
	sdoc->BATTERING = true;
 
	sdoc->SetModifiedFlag() ;
	sdoc->UpdateAllViews(NULL);  
}


//rebuild the battering objects at right or left and change the attributes
//insert mode ....
void CGExternal::InsRebuildButtering()
{
    int my_next, my_prev, meter;
	float distance,length,height;

	//get selected object
    //CGExternal *e_ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]); 

	length = GetObjectLength();   //get new length 

	meter=0; //zero meter
	switch (theApp.ObjDirection)
    {
	  case 1 : { //right

                 my_next = next_id ;  //get the new object next number

	             while (my_next!=0)
				 {
                    CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object

                    distance  = nxt->GetLeftDistance(); //get object left distance
					height = nxt->GetHeightDistance();  //get object height
                    nxt->MoveObjectTo(distance+length,height,nxt->outlook);

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

                 my_prev = prior_id ;  //get the new object prior number

	             while (my_prev!=0)
				 {
                    CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object

					distance  = prv->GetLeftDistance(); //get object left distance
					height = prv->GetHeightDistance();  //get object height
                    prv->MoveObjectTo(distance-length,height,prv->outlook);

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
}




//rebuild the battering objects at right or left and change the attributes
//delete mode ...
void CGExternal::DelRebuildButtering()
{
    int my_next, my_prev, meter;
	int the_next, the_prev;
	float distance,length,height;

	//check if there are battering ...
	the_next = next_id ;   //get the selected object next number
    the_prev = prior_id ;  //get the selected object previous number

    if ((the_next!=0) || (the_prev!=0))
    { 
	  length = GetObjectLength();   //get length

	  meter=0; //zero meter
	  switch (theApp.ObjDirection)
	  {
	    case 1 : { //right

                   my_next	= next_id ;  //get the selected object next number

	               while (my_next!=0)
				   {
                      CGExternal *nxt = ((CGExternal*)sdoc->Obj[my_next]);  //get next object

					  distance  = nxt->GetLeftDistance(); //get object left distance
					  height = nxt->GetHeightDistance();  //get object height
                      nxt->MoveObjectTo(distance-length,height,nxt->outlook);

	                  //get next object
	                  my_next = nxt->next_id ;
	                  meter+=1; 
				   }
				   break;
				 }
        case 2 : { //left

                   my_prev = prior_id ;  //get the selected object prior number

	               while (my_prev!=0)
				   {
                      CGExternal *prv = ((CGExternal*)sdoc->Obj[my_prev]);  //get previous object
	                  
					  distance  = prv->GetLeftDistance(); //get object left distance
					  height = prv->GetHeightDistance();  //get object height
                      prv->MoveObjectTo(distance+length,height,prv->outlook);

					  //get prev object
	                  my_prev = prv->prior_id ;
	                  meter+=1;
				   }
				   break;
				 }
	  }

      //Change the attributes of objects
	  if (next_id!=0)
	  {
        CGExternal *nxt = ((CGExternal*)sdoc->Obj[next_id]);       //get next of selected object
        nxt->prior_id = prior_id;
	    nxt->SaveProperties();
	  }
      if (prior_id!=0)
	  {
        CGExternal *prv = ((CGExternal*)sdoc->Obj[prior_id]);      //get prev of selected object 
	    prv->next_id = next_id;
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



//rebuild the battering objects at right or left and change the attributes
//delete object and break the battering in 2 butterings
//extent delete mode...
void CGExternal::ExtDelRebuildButtering()
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


//delete object ... (if battering ..from battering)...
void CGExternal::DelObject(int aanum,int mode)
{
	if (IsAttachedObject(aanum)==false)
	{
	  //rebuild the battering -before- delete the selected object
	  if (mode==0) DelRebuildButtering(); 
	          else ExtDelRebuildButtering();

	  DeleteObject(aanum);
	}
	else
        AfxMessageBox("          Access denied.\n Other object(s) use this object.");
}



//************** replace object  **************/
void CGExternal::ReplaceObject()
{
	int mynext,myprior,mycarrier,myoutlook,mycarrier_side,myobj_side,obj_rp ;
    SbVec3f Transaxis , Rotaxis ;
    float Rotangle ,tx,ty,tz , myangle ;

	SoSeparator *obj_sep = sep;  //get new object sep
	//get selected-old object ...
	CGExternal *the_old = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]);//old

	//get selected-old object translation and rotation
	SoSeparator *selected = ((CGExternal*)the_old)->sep ; //get selected object node

	//SoTranslation *t = (SoTranslation *)selected->getChild(1) ; 
	SoRotation *r = (SoRotation *)selected->getChild(2) ;    	
	//Transaxis = t->translation.getValue(); //get selected object translation values   
    r->rotation.getValue(Rotaxis , Rotangle); //get selected object rotation values

    //save selected-old data
	tx             = the_old->totalx;
    ty             = the_old->totaly;
	tz             = the_old->totalz;
	myangle        = Rotangle;//GetRotationAngle();//the_old->yangle;<<----not work??????
	mynext         = the_old->next_id ;
	myprior        = the_old->prior_id ;
	mycarrier      = the_old->carrier_id ;
	mycarrier_side = the_old->carrier_side ;
	myobj_side     = the_old->object_side ;
	myoutlook      = the_old->outlook;
	obj_rp         = the_old->object_refpoint;


    //delete the old(replaced)-selected object
	//sview->OnDelete();
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
	   //in this case get old totals
	   totalx = tx;
	   totaly = ty;
	   totalz = tz;
	   GetBox();   //<<<<<-------------------------------- εγκιβωτισμος

	   //****INVENTOR rendering
	   //set new object rotation  <<--------------- να δινω την στροφη σε radians
	                           //    e.g. setRotationAngle(old_radians)
	   SoRotation *rot	= (SoRotation *)sep->getChild(2) ;
	   rot->rotation.setValue(Rotaxis ,Rotangle) ; //put selected object rotation values to the new object

       MakeObjVisible();
	   SetTranslation(SbVec3f(totalx,totaly,totalz)); 
	   //SetRotationAngle(myangle); //<<<<---------------????
       //***********************

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

	   //.. and set battering on..
	   sdoc->BATTERING = true;

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

		SoNode *myGeom = clone->getChild(5); //get "Geometry" 
	    sview->sep_buffer->addChild( myGeom );
		SoNode *myAttr = clone->getChild(6); //get "Attributes" 
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
	    SoTranslation	*trans	= new SoTranslation ;
	    SoRotation		*rot	= new SoRotation ;

		SoDrawStyle *ds = new SoDrawStyle ;
		sep->addChild(ds) ;
		ds->style = SoDrawStyle::INVISIBLE ;
	
	    sep->addChild ( trans ) ;
	    sep->addChild ( rot ) ;

	    SoPickStyle *ps = new SoPickStyle;
	    sep->addChild(ps) ;
        ps->style.setValue(SoPickStyle::SHAPE) ;

	    SoMaterial  *mat = new SoMaterial;
	    //mat->diffuseColor.setValue( k_red, k_green, k_blue ); 
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

		for ( i = 0 ; i < 3 ; i++ )
		{
			ob->left_base_point[i]	= sdoc->external_buffer->left_base_point[i] ;
			ob->right_base_point[i] = sdoc->external_buffer->right_base_point[i] ;
			ob->left_top_point[i]	= sdoc->external_buffer->left_top_point[i] ;
			ob->right_top_point[i]	= sdoc->external_buffer->right_top_point[i] ;
		}

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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GExternalProp, CDialog)
	//{{AFX_MSG_MAP(GExternalProp)
        // NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GExternalProp message handlers

