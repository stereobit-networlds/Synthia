// GExternal.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"
#include "SYNTHdoc.h"
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
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/nodes/SoTranslation.h>

/////////////////////////////////////////////////////////////////////////////
// CGExternal

IMPLEMENT_DYNAMIC( CGExternal, CObject )

CGExternal::CGExternal()
{
	sep = NULL ;
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
    
	//code for sep name = code 
	//CString& mycode = code.SpanExcluding(_T(" ")); //βγάζω τα κενά απο το τέλος του string
	//sep->setName(SbName(mycode)); //set node name 

	root->addChild(sep) ;

} 

/*======================== SaveProperties ===================*/

void CGExternal::SaveProperties ()
{
	// inherited action
	CGObject::SaveProperties() ;
    
	sep->setName(name) ;  // set node name

	SoSeparator *attr = new SoSeparator ;
	attr->setName("Attributes") ;

	CLib0 lib ;
	CString soff = lib.inttostr(offset) ; 

	lib.setSoSFFloatProp ( attr, SbName("Id04_"+soff), sdoc->ObjCount ) ; //save object's counter as id

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

float xdist, ydist ;

int CGExternal::EditProperties ( CDocument *d, SoSeparator *root ) 
{
	// inherited action
	CGObject::EditProperties(d,root) ;

	//Get reference points
	GetPoints();
	//Calculate object distances
	GetDistances();

	GExternalProp *dlg = new GExternalProp ;

	//float xdist, ydist ;
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
		  //calculate new state
	      FindNewState(xdist,ydist) ;
        }
 
		//ObjectToInventor ( root ) ; οχι απαραιτητο γιατι ξαναβαζει το external 2η φορα
		//SaveProperties() ;    οχι γιατι ξαναπροσθετει
		//πρεπει να γινει modify ρουτινα
	}

	return res ;
}
 
/****************************  get points ****************************/
void CGExternal::GetPoints()
{
	CLib0 lib;

	//int carrier_attr = lib.getSoSFIntProp(SbName("carrier"+soff)) ;
	//i can't read carrier because i don't know the soff 

	int CarrierDum = 0; //=roomwall0

	//get points data x1,y1,z1 ,x2,y2,z2
	int ofs = CarrierDum; 

	if (ofs>=0) // αυτο σημαίνει οτι το ofs ειναι RoomWall+ofs
    {
	  CString soff = lib.inttostr(ofs) ; ; // ofs must be the carrier

      pointX1 = lib.getSoSFFloatProp ( SbName("Koryfsx0"+soff) ) ;
      pointY1 = lib.getSoSFFloatProp ( SbName("Koryfsy0"+soff) ) ;
      pointZ1 = lib.getSoSFFloatProp ( SbName("Koryfsz0"+soff) ) ;

      pointX2 = lib.getSoSFFloatProp ( SbName("Koryfsx1"+soff) ) ;
      pointY2 = lib.getSoSFFloatProp ( SbName("Koryfsy1"+soff) ) ;
      pointZ2 = lib.getSoSFFloatProp ( SbName("Koryfsz1"+soff) ) ;
    }
	else // <0  αυτο σημαίνει οτι το ofs είναι RoomBase or WorldBase
	{
      if (ofs == -1) // αυτο σημαίνει οτι το ofs είναι RoomBase και επειδη είναι μοναδικό object ...
      {
        pointX1 = lib.getSoSFFloatProp ( SbName("rb_Koryfsx0") ) ;
        pointY1 = lib.getSoSFFloatProp ( SbName("rb_Koryfsy0") ) ;
        pointZ1 = lib.getSoSFFloatProp ( SbName("rb_Koryfsz0") ) ;

        pointX2 = lib.getSoSFFloatProp ( SbName("rb_Koryfsx1") ) ;
        pointY2 = lib.getSoSFFloatProp ( SbName("rb_Koryfsy1") ) ;
        pointZ2 = lib.getSoSFFloatProp ( SbName("rb_Koryfsz1") ) ;
	    // κατα σύμβαση παίρνουμε τις 2 πρώτες κορυφές της RoomBase
      }
	  else 
	  if (ofs == -2) // αυτο σημαίνει οτι το ofs είναι WorldBase και επειδη είναι μοναδικό object ...
      {
        pointX1 = lib.getSoSFFloatProp ( SbName("rb_Koryfsx0") ) ;
        pointY1 = lib.getSoSFFloatProp ( SbName("rb_Koryfsy0") ) ;
        pointZ1 = lib.getSoSFFloatProp ( SbName("rb_Koryfsz0") ) ;

        pointX2 = lib.getSoSFFloatProp ( SbName("rb_Koryfsx1") ) ;
        pointY2 = lib.getSoSFFloatProp ( SbName("rb_Koryfsy1") ) ;
        pointZ2 = lib.getSoSFFloatProp ( SbName("rb_Koryfsz1") ) ;
	    // κατα σύμβαση παίρνουμε τις 2 πρώτες κορυφές της WorldBase
      }
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

    
	SoSeparator *sep = ((CGExternal*)sdoc->Obj[sdoc->SelId])->sep ; //get node
    //test code
	SoDrawStyle	*ds = (SoDrawStyle *)sep->getChild(0) ;  
	ds->style = SoDrawStyle::FILLED ;
	
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
	  d = abs(d);
      //step 2 : calc f =cos(f)
      f = ( ( ((pointX2-pointX1)*(objX-pointX1)) +
		      ((pointY2-pointY1)*(objY-pointY1)) +
			  ((pointZ2-pointZ1)*(objZ-pointZ1)) ) /
            ( abs(d) *
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
	  d2 = ( abs(d) * ( cos( (PI/2) - acos(f) ) ) );


	  d1 = abs(d1);
	  d2 = abs(d2);
      
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

/********************* FindNewSimio **************************/
void CGExternal::FindNewState(float d1,float d2)
{
    CLib0 lib;
	float objX,objY,objZ ;
	float b; 

	AfxMessageBox("distances :"+lib.floattostr(d1)+" "+lib.floattostr(d2));
	//calculations...
	b = sqrt( (pow( (pointX2-pointX1), 2)) +  
		      (pow( (pointY2-pointY1), 2)) + 
			  (pow( (pointZ2-pointZ1), 2)) );


    objX = ( ( (pointX2-pointX1) / abs(b) ) * d1 ) ;
    objY = ( ( ( (pointY2-pointY1) / abs(b) ) * d1 ) + d2 ) ;
	objZ = ( ( (pointZ2-pointZ1) / abs(b) ) * d1 ) ;

	AfxMessageBox("object :"+lib.floattostr(objX)+" "+
		                     lib.floattostr(objY)+" "+
				             lib.floattostr(objZ)) ;

	//put new translation
    SbVec3f vector ;
	vector.setValue(objX , objY , objZ);

	SoSeparator *sep = ((CGExternal*)sdoc->Obj[sdoc->SelId])->sep ;
	SoTranslation *trans = (SoTranslation *)sep->getChild(1) ;

	trans->translation	=  vector;
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
