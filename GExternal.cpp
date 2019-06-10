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
	
    SoPickStyle *ps = new SoPickStyle;
	sep->addChild(ps) ;
    ps->style.setValue(SoPickStyle::UNPICKABLE) ;

	SoDrawStyle *ds = new SoDrawStyle ;
	sep->addChild(ds) ;
	ds->style = SoDrawStyle::INVISIBLE ;
	
	SaveProperties() ; 
    
	root->addChild(sep) ;

	if (sdoc->BUTTERING)
    {
       AttachObject(sep);
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
	// inherited action
	CGObject::EditProperties(d,root) ;

	//Get reference points
	GetObjRefPoints();
    //Calculate object distances
    GetDistances(); 

	GExternalProp *dlg = new GExternalProp ;

	float comparedistX,comparedistY ; //compare purpose 

	dlg->m_code		= code ;
	dlg->m_descr	= descr ;
	dlg->m_yangle	= yangle ;
	dlg->m_topoth	= topoth ;
	dlg->m_xdist	= xdist ; comparedistX = xdist; 
	dlg->m_ydist	= ydist ; comparedistY = ydist;

	int res = dlg->DoModal() ;

	if (res == IDOK)   
	{
		code	= dlg->m_code ;
		descr	= dlg->m_descr ;
		yangle	= dlg->m_yangle ;
		topoth	= dlg->m_topoth ;
		xdist	= dlg->m_xdist ;
		ydist	= dlg->m_ydist ;

 		if ((xdist!=comparedistX) || (ydist!=comparedistY)) //if xdist,ydist value has change
        {
		  //calculate motion
	      MoveObjectTo(xdist,ydist) ;
        }

		SaveProperties() ;    
	}

	return res ;
}


//************************ ΑΛΛΑΓΗ ΘΕΣΗΣ *********************************
/*************************  get reference points  ********************/
void CGExternal::GetObjRefPoints()
{
	CLib0 lib;

	//get selection carrier
	carrier_id = ((CGExternal*)sdoc->Obj[sdoc->obj_selector])->carrier_id;
	next_id = ((CGExternal*)sdoc->Obj[sdoc->obj_selector])->next_id;
	prior_id = ((CGExternal*)sdoc->Obj[sdoc->obj_selector])->prior_id;
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

		// κατα σύμβαση παίρνουμε τις 2 πρώτες κορυφές της RoomBase
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

		// κατα σύμβαση παίρνουμε τις 2 πρώτες κορυφές της RoomWall
    }

	else        
	if (sdoc->Obj[carrier_id]->IsKindOf(RUNTIME_CLASS(CGExternal)))
	{
	    //do nothing 
    }
	
	
	AfxMessageBox("points :"+lib.floattostr(pointX1)+" "+lib.floattostr(pointY1)+" "+lib.floattostr(pointZ1)+
	                   " , "+lib.floattostr(pointX2)+" "+lib.floattostr(pointY2)+" "+lib.floattostr(pointZ2));
}


#define PI 3.1415926
/********************* GetDistances **************************/
void CGExternal::GetDistances()
{
    CLib0 lib;
	float objX,objY,objZ ;
	float d,f,d1,d2; 
	SbVec3f vals;

    
	SoSeparator *sep = ((CGExternal*)sdoc->Obj[sdoc->obj_selector])->sep ; //get node
    //test code
	//SoDrawStyle	*ds = (SoDrawStyle *)sep->getChild(0) ;  
	//ds->style = SoDrawStyle::FILLED ;
	
	SoNode *mynode ;
	mynode = sep->getChild(1);
	if (mynode->isOfType(SoTranslation::getClassTypeId())) //if it is translation node
    {     
      SoTranslation *trans = (SoTranslation *) mynode ; //get translation node
	  vals = trans->translation.getValue(); //get values
	  
	  objX = vals[0];
      objY = vals[1];
      objZ = vals[2];

	  AfxMessageBox("object :"+lib.floattostr(vals[0])+" "+lib.floattostr(vals[1])+" "+lib.floattostr(vals[2]));

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

	  AfxMessageBox("distances :"+lib.floattostr(d1)+" "+lib.floattostr(d2));
    }
	else
    {
	  AfxMessageBox("Unable to translate the object.");
    }

}

/********************* Move object **************************/
void CGExternal::MoveObjectTo(float d1,float d2)
{
    CLib0 lib;
	float objX,objY,objZ ;
	float b; 

	AfxMessageBox("distances :"+lib.floattostr(d1)+" "+lib.floattostr(d2));
	//calculations...
	b = sqrt( (pow( (pointX2-pointX1), 2)) +  
		      (pow( (pointY2-pointY1), 2)) + 
			  (pow( (pointZ2-pointZ1), 2)) );


    objX = ( ( (pointX2-pointX1) / fabs(b) ) * d1 + pointX1 ) ;
    objY = ( ( (pointY2-pointY1) / fabs(b) ) * d1  + d2 +pointY1 ) ;
	objZ = ( ( (pointZ2-pointZ1) / fabs(b) ) * d1 + pointZ1 ) ;

	AfxMessageBox("object :"+lib.floattostr(objX)+" "+
		                     lib.floattostr(objY)+" "+
				             lib.floattostr(objZ)) ;

	//put new translation
    SbVec3f vector ;
	vector.setValue(objX , objY , objZ);

	SoSeparator *sep = ((CGExternal*)sdoc->Obj[sdoc->obj_selector])->sep ;
	SoTranslation *trans = (SoTranslation *)sep->getChild(1) ;

	trans->translation	=  vector;
}

//**************** BUTTERING ************************
SbMatrix matrix ;
SbVec3f dianisma , destdianisma ;

void CGExternal::CalculateSelectedObjectDistance()
{
	//get left and right base points of selected object
    CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]);
    pointX1 = ext->left_base_point[0] ;
    pointY1 = ext->left_base_point[1] ;
    pointZ1 = ext->left_base_point[2] ;

    pointX2 = ext->right_base_point[0] ;
    pointY2 = ext->right_base_point[1] ;
    pointZ2 = ext->right_base_point[2] ;

    //get distances
    dianisma[0] = pointX2 - pointX1;
    dianisma[1] = pointY2 - pointY1;
    dianisma[2] = pointZ2 - pointZ1; 
			   
    //multiply dianisma by matrix 
    matrix.multVecMatrix(dianisma , destdianisma);
}

void CGExternal::CalculateNewObjectDistance()
{
	//get left and right base points of new object
    pointX1 = left_base_point[0] ;
    pointY1 = left_base_point[1] ;
	pointZ1 = left_base_point[2] ;

	pointX2 = right_base_point[0] ;
    pointY2 = right_base_point[1] ;
	pointZ2 = right_base_point[2] ;

	//get distances
	dianisma[0] = pointX2 - pointX1;
	dianisma[1] = pointY2 - pointY1;
	dianisma[2] = pointZ2 - pointZ1;

	//multiply dianisma by matrix
	matrix.multVecMatrix(dianisma , destdianisma);
}

//************** input object (buttering) **************/
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
               CalculateSelectedObjectDistance();

		       //new translation
	           NewTransaxis[0] = Transaxis[0] + destdianisma[0] ;
               NewTransaxis[1] = Transaxis[1] + destdianisma[1] ;
               NewTransaxis[2] = Transaxis[2] + destdianisma[2] ;

			   //rebuild buttering (if there are buttering)
			   RebuildRight();

			   //AfxMessageBox("Right");
			   break;
             }
      case 2 : { //left
		       CalculateNewObjectDistance();
			   
               //new translation 
	           NewTransaxis[0] = Transaxis[0] - destdianisma[0] ;
               NewTransaxis[1] = Transaxis[1] - destdianisma[1] ;
               NewTransaxis[2] = Transaxis[2] - destdianisma[2] ;

			   //rebuild buttering (if there are buttering)
			   RebuildLeft();

			   //AfxMessageBox("Left");
			   break;
             }
    }

	//set new object translation & rotation 
    SoDrawStyle	*ds = (SoDrawStyle *)obj_sep->getChild(0) ;
	SoTranslation *trans = (SoTranslation *)sep->getChild(1) ;
	SoRotation *rot	= (SoRotation *)sep->getChild(2) ;

	ds->style = SoDrawStyle::FILLED ;
	trans->translation	= NewTransaxis ; //put new (computed ) translation values
	rot->rotation.setValue(Rotaxis ,Rotangle) ; //put rotation values same as selected object

	sdoc->new_object = FALSE ;  //δεν χρειάζεται να κάνουμε click για να εμφανιστει το αντικείμενο

    //select the new object..
	sview->GetSelectionNode()->deselectAll();
	sview->GetSelectionNode()->select(obj_sep) ;
	sdoc->obj_selector = sdoc->ObjCount-1 ;
	//.. and set buttering on..
	sdoc->BUTTERING = true;

	sdoc->SetModifiedFlag() ;
	sdoc->UpdateAllViews(NULL);   
}

//******* standart change of attributes (no buttering) *******
void CGExternal::ChangeAttributes()
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
	             prior_id = sdoc->obj_selector ; //= ο αριθμος του επιλεγμένου object
	
	             SaveProperties();

	             //change selected object attributes
	             //set next pointer
	             ext->next_id = sdoc->ObjCount-1 ; //= ο αριθμος του νεου object
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
	             next_id = sdoc->obj_selector ; //= ο αριθμος του επιλεγμένου object
                 //set prior pointer
	             prior_id = 0 ; //nothing previous
	
	             SaveProperties();

	             //change selected object attributes
	             //set previous pointer
	             ext->prior_id = sdoc->ObjCount-1 ; //= ο αριθμος του νεου object
	             // no next
	             // no carrier
	             ext->SaveProperties();

				 break;
			   }
    }
}

//******* Buttering change of attributes  *******
void CGExternal::ChangeButteringAttributes()
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
	             prior_id = sdoc->obj_selector ; //= ο αριθμος του επιλεγμένου object
	
                 SaveProperties();

	             //change selected object attributes
	             //set next pointer
	             ext->next_id = sdoc->ObjCount-1 ; //= ο αριθμος του νεου object
	             // no prior
	             // no carrier
	             ext->SaveProperties();

	             //change next of selected (before rebuilding) object attributes
	             //no next (is the same)
	             //no carrier
	             //set previous pointer
	             nxt->prior_id = sdoc->ObjCount-1 ; //= ο αριθμος του νεου object

	             nxt->SaveProperties();

				 break;
			   }
      case 2 : { //left
                 CGExternal *prv = ((CGExternal*)sdoc->Obj[ext->prior_id]);       //get previous of selected object

	             //change new object attributes
	             //set carrier
	             carrier_id	= ext->carrier_id ; 
                 //set next pointer
	             next_id = sdoc->obj_selector ; //= ο αριθμος του επιλεγμένου object
                 //set prior pointer
	             prior_id = ext->prior_id ; //the previous of new object is now the previous of selected   
	
                 SaveProperties();

	             //change selected object attributes
	             //set previous pointer
	             ext->prior_id = sdoc->ObjCount-1 ; //= ο αριθμος του νεου object
	             // no next
	             // no carrier
	             ext->SaveProperties();

	             //change previous of selected (before rebuilding) object attributes
	             //no previous
	             //no carrier
	             //set next pointer
	             prv->next_id = sdoc->ObjCount-1 ; //= ο αριθμος του νεου object

	             prv->SaveProperties();

				 break;
			   }
    }
}

//rebuild the buttering objects at right and change the attributes
void CGExternal::RebuildRight()
{
    int my_next, meter;
	SbVec3f Values , NewValues ;

	//***** i need the distance of new object so..
	CalculateNewObjectDistance();

    CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]);  //get selected object
    my_next	= ext->next_id ;  //get the selected object next number

	meter=0;
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
	CLib0 lib;
	AfxMessageBox(lib.inttostr(meter));
    //Change the attributes of objects
	if (meter==0) //it means that there are not buttering
    {
       ChangeAttributes();
    }
	else
    {
	   ChangeButteringAttributes();
    }
}

//rebuild the buttering objects at left and change the attributes
void CGExternal::RebuildLeft()
{
    int my_prev, meter;
	SbVec3f Values , NewValues ;

	//***** i need the distance of new object so..
	CalculateNewObjectDistance();

    CGExternal *ext = ((CGExternal*)sdoc->Obj[sdoc->obj_selector]);  //get selected object
    my_prev	= ext->prior_id ;  //get the selected object prior number

	meter=0;
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
	CLib0 lib;
	AfxMessageBox(lib.inttostr(meter));
    //Change the attributes of objects
	if (meter==0) //it means that there are not buttering
    {
       ChangeAttributes();
    }
	else
    {
	   ChangeButteringAttributes();
    }
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GExternalProp, CDialog)
	//{{AFX_MSG_MAP(GExternalProp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GExternalProp message handlers
