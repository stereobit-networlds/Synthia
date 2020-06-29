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
#include <Inventor/nodes/SoTransform.h>

#include "RoomBase.h"
#include "RoomWall.h"
#include "GExternal.h"

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
	float	norm[50][3] ;
                
	int 	numvert[50] ;
	int i , n;

	CGLib0 *lib = new CGLib0 ;
    

	//find top points ... βαση των base points 
    for ( i = 0 ; i < KoryfCount ; i++ )
	{
		Koryfsx[i+KoryfCount]	= Koryfsx[i] ;
		Koryfsy[i+KoryfCount]	= Koryfsy[i] + height ;  
		Koryfsz[i+KoryfCount]	= Koryfsz[i] ;
	}

	//setup plaina
	n = 0;
	for ( i = 0 ; i < KoryfCount ; i++ )
	{
		vert[n][0] = Koryfsx[i] ;
		vert[n][1] = Koryfsy[i] ;
		vert[n][2] = Koryfsz[i] ; 

		vert[n+1][0] = Koryfsx[i] ;
		vert[n+1][1] = Koryfsy[i] + height ;
		vert[n+1][2] = Koryfsz[i] ;


    	if (i<(KoryfCount-1))
        {
	    	vert[n+2][0] = Koryfsx[i+1] ;
		    vert[n+2][1] = Koryfsy[i+1] + height ;
		    vert[n+2][2] = Koryfsz[i+1] ; 
		
	    	vert[n+3][0] = Koryfsx[i+1] ;
		    vert[n+3][1] = Koryfsy[i+1] ;
		    vert[n+3][2] = Koryfsz[i+1] ; 
		}
		else  //close the circle
		{
		    vert[n+2][0] = Koryfsx[0] ;
		    vert[n+2][1] = Koryfsy[0] + height ;
		    vert[n+2][2] = Koryfsz[0] ; 
		
	    	vert[n+3][0] = Koryfsx[0] ;
		    vert[n+3][1] = Koryfsy[0] ;
		    vert[n+3][2] = Koryfsz[0] ; 
		}
 	

		lib->GetPolyNormal ( vert[n][0], vert[n][1], vert[n][2],
						     vert[n+1][0], vert[n+1][1], vert[n+1][2],	
						     vert[n+2][0], vert[n+2][1], vert[n+2][2],
						    &norm[i][0], &norm[i][1], &norm[i][2] ) ; 
		numvert[i] = 4;
		n+=4;
	}
    //setup upbase
	//n , i =  the last values fom the previous for..
	for ( int k = 0 ; k < KoryfCount ; k++ )
	{
		vert[n+k][0] = Koryfsx[k] ;
		vert[n+k][1] = Koryfsy[k] + height ;
		vert[n+k][2] = Koryfsz[k] ; 	
	}
    numvert[i] = KoryfCount;

	norm[i][0] = 0. ;
	norm[i][1] = 1. ;
	norm[i][2] = 0. ;



	int num_faces = KoryfCount + 1 ; //+ = the upper face ..

	BOOL first_time = FALSE ;
	if (sep != NULL) 
		sep->removeAllChildren() ;
	else
	{
	    sep	= new SoSeparator ;
		first_time = TRUE ;
	}

	//setup transform
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

	// setup coordinates
	SoCoordinate3 *c3	= new SoCoordinate3 ;
	c3->point.setValues(0,(KoryfCount*4)+20,vert) ; 

	// setup faces
	SoFaceSet *fs = new SoFaceSet ;
	fs->numVertices.setValues(0,num_faces,numvert) ;

	// setup normal
	SoNormal *nm = new SoNormal ;
	nm->vector.setValues(0,num_faces,norm) ;

	SoNormalBinding *nb = new SoNormalBinding ;
	nb->value = SoNormalBinding::PER_FACE ;

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
	sep->addChild( c3 );	
	sep->addChild( fs );

	GetBox();  //<<<<<-------------------------------- εγκιβωτισμος

	SaveProperties() ;
	if (first_time) root->addChild(sep) ;
} 

/*======================== SaveProperties ===================*/

void CRoomBase::SaveProperties ()
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

	CLib0	lib ;

	lib.setSoSFFloatProp ( attr, "rb_height", height ) ;
	lib.setSoSFIntProp	 ( attr, "KoryfCount", KoryfCount ) ;

	CString soff ;      //x2 επειδη καταχωρουμε και τα points της βασης
	for ( int i = 0 ; i < (KoryfCount*2)-1 ; i++ )
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

	//inherited action
	CGObject::InventorToObject(root);

	CLib0	lib ;

	KoryfCount	= lib.getSoSFIntProp("KoryfCount") ;
	height		= lib.getSoSFFloatProp("rb_height") ;

	CString soff ;       //x2 = διαβαζουμε πρωτα τα points της βασης και μετα της κορυφης
	for ( int i = 0 ; i < (KoryfCount*2)-1 ; i++ )
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


void CRoomBase::GetBox()
{
	// inherited action
	CGObject::GetBox() ;

	//ymax is allways the height of room
	ymax = height;

	//assign min(xyz),max(xyz)to roombase box
	//τα min,max προστιθονται στην πρωτη κορυφη του πολυγωνου
	//διοτι τα σημεια τησ βασης ειναι υπολογισμενα με βαση το 0,0,0
	//ομως η κορυφη εχει μετατοπιστει ωστε το κεντρο της βασης να 
	//ειναι το κεντρο του coord system

	//****** down
	ssx[0] = Koryfsx[0] + xmin;
    ssy[0] = Koryfsy[0] + ymin;
	ssz[0] = Koryfsz[0] + zmin;

	ssx[1] = Koryfsx[0] + xmin;
    ssy[1] = Koryfsy[0] + ymin;
	ssz[1] = Koryfsz[0] + zmax;

	ssx[2] = Koryfsx[0] + xmax;
    ssy[2] = Koryfsy[0] + ymin;
	ssz[2] = Koryfsz[0] + zmax;

	ssx[3] = Koryfsx[0] + xmax;
    ssy[3] = Koryfsy[0] + ymin;
	ssz[3] = Koryfsz[0] + zmin;

	//****** up
	ssx[4] = Koryfsx[0] + xmin;
    ssy[4] = Koryfsy[0] + ymax;
	ssz[4] = Koryfsz[0] + zmin;

	ssx[5] = Koryfsx[0] + xmin;
    ssy[5] = Koryfsy[0] + ymax;
	ssz[5] = Koryfsz[0] + zmax;

	ssx[6] = Koryfsx[0] + xmax;
    ssy[6] = Koryfsy[0] + ymax;
	ssz[6] = Koryfsz[0] + zmax;

	ssx[7] = Koryfsx[0] + xmax;
    ssy[7] = Koryfsy[0] + ymax;
	ssz[7] = Koryfsz[0] + zmin;

}

/*======================= EditProperties ========================*/

int CRoomBase::EditProperties ( CDocument *d, SoSeparator *root ) 
{
	float compheight;

	// inherited action
	CGObject::EditProperties(d,root) ;

	CRoomBasePro *dlg = new CRoomBasePro ;

	dlg->m_height   = height ;  compheight = height ;
	dlg->m_plakaki	= plakaki ;
	dlg->m_plakaki1	= plakaki1 ;
	dlg->m_plakaki2	= plakaki2 ;

	int res = dlg->DoModal() ;

	if (res == IDOK)   
	{
		sdoc->SaveUndo(); //save scene for undo...

        height   =  dlg->m_height ;
		plakaki	 =	dlg->m_plakaki ;
		plakaki1 =	dlg->m_plakaki1 ;
		plakaki2 =	dlg->m_plakaki2 ;

		if (fabs(height - compheight) > 0.001)
        {
           MoveCarrierObjects((height - compheight));
        }

		ObjectToInventor ( root ) ;
		
		ShowRefPoints(150.0); //<<<----------------------- show points
	}

	return res ;
}

//move the whole scene up to base
void CRoomBase::MoveCarrierObjects(float high)
{
	int i;
	SbVec3f vectors ;

	//i=1 και οχι 0 διοτι το worldbase δεν εχει carrier_id
	for(i=1 ; i<sdoc->ObjCount ; i++) 
    {
	  if (sdoc->Obj[i]!=NULL)
      {
        CGObject *obj = ((CGObject*)sdoc->Obj[i]); //get object

		//CLib0 lib;
		//AfxMessageBox(lib.inttostr(obj->carrier_id));

		if (obj->carrier_id == 1) //= roombase
		{
           if (obj->IsKindOf(RUNTIME_CLASS(CRoomWall)))
		   {
			   //προκειται να ξαναδημιουργηθει ο τοιχος αρα
			   //αλλαζω τισ κορυφες του και με την objecttoinventor
			   //γινεται εγκιβωτισμος εκ' νεου...

	           //set object translation...change only height = y

			   //move all children objects...
			   CRoomWall *wall = (CRoomWall *)obj;

			   //update totals
			   wall->totalx  = wall->totalx ;
		       wall->totaly  = wall->totaly + high;
		       wall->totalz  = wall->totalz ;

			   wall->Koryfsx[0] = wall->Koryfsx[0] ;
      	       wall->Koryfsy[0] = wall->Koryfsy[0] + high ;
		       wall->Koryfsz[0] = wall->Koryfsz[0] ;

			   wall->Koryfsx[1] = wall->Koryfsx[1] ;
      	       wall->Koryfsy[1] = wall->Koryfsy[1] + high ;
		       wall->Koryfsz[1] = wall->Koryfsz[1] ;

			   wall->ObjectToInventor ( sdoc->root ) ;

			   //move the walls carriers (this routine called from wall for recursion...)
			   wall->MoveCarrierObjects(0,high,0);
           }
		   else
		   if (obj->IsKindOf(RUNTIME_CLASS(CGExternal)))
		   {
			   CGExternal *ext = (CGExternal *)obj;
			   //update totals
			   ext->totalx  = ext->totalx;
		       ext->totaly  = ext->totaly + high;
		       ext->totalz  = ext->totalz;

			   ext->GetBox();

			   //INVENTOR:put new translation
	           vectors.setValue(ext->totalx , ext->totaly , ext->totalz);
	           ext->SetTranslation(vectors);
           }
		}
      }
    }
}



//command for add room base
void CRoomBase::AddNewObject(SbVec3f p_point, SbVec3f p_normal)
{
		float	len[20], angle[20] ;
		int		toix[20] ;
		int		pleyres ;
		float	fx[20], fy[20], fz[20] ;  //first point array
		float	nx[20], ny[20], nz[20] ;  //next point array 
		float   nrx[20],nry[20],nrz[20] ; //normals array 
		float	vx, vy, vz,len1,len0,Room_Height ;

		CLib0 lib ;
		CGLib0 *glib = new CGLib0 ;

		// inherited action
	    CGObject::AddNewObject(p_point,p_normal) ;

		int dd=100;  //<<<<<<<<<<--------------- wall depth

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

		Room_Height = 500;

		//επειδή το world εχει δημιουργηθει σαν inventor box με ymin =-wry/2.0.+wry/2
        //room base ...ymin = world height/2
		CWorldBase *wr = ((CWorldBase*)sdoc->Obj[0]);


		// setup the room base
		CRoomBase *rb = new CRoomBase ;

		sdoc->Obj[sdoc->ObjCount] = rb ;
		sdoc->ObjCount++ ;

		rb->offset = 1 ;
		rb->id     = _ROOMBASE_ ;
		rb->name   = "RoomBase"+lib.inttostr(sdoc->ObjCount-1) ; //name + counter 
		rb->height = Room_Height ;   

		// calculate pleyres
		for ( int i = 0 ; i <= 7 ; i++ )
			if (len[i] == 0) break ;
		pleyres = i + 1 ;

		//calculate points
		rb->xmax = rb->xmin = rb->ymax = rb->ymin = rb->zmax = rb->zmin = 0 ;
        for ( i = 0 ; i < pleyres ; i++)
		{
			if (i == 0)
			{
				fx[i] = p_point[0];
				fy[i] = wr->height/2;
				fz[i] = p_point[2];

				nrx[i] = p_normal[0];
				nry[i] = p_normal[1];
				nrz[i] = p_normal[2];
			}
			else 
			{
				fx[i] = nx[i-1] ; 
				fy[i] = ny[i-1] ;
				fz[i] = nz[i-1] ;

				//παιρνω το normal της πλευρας του προηγουμενου τοιχου ...
                glib->GetPolyNormal ( fx[i-1], fy[i-1], fz[i-1],
  			               		      nx[i-1], ny[i-1], nz[i-1],						
					                  nx[i-1], ny[i-1]+100, nz[i-1],
					                 &vx, &vy, &vz ) ;
				nrx[i] = vx;
				nry[i] = vy;
				nrz[i] = vz;
			}

			len0 = int(sin((180-angle[i]) * M_PI/180) * len[i]);
			len1 = int(cos((180-angle[i]) * M_PI/180) * len[i]) ;
                
			//προσθεtουμε την μετατοπιση στον αξονα με 1 normal
			nx[i] = fx[i] + (nrx[i] * len0);
			ny[i] = fy[i] + (nry[i] * len0); //myHeight;
			nz[i] = fz[i] + (nrz[i] * len0);
			//αντιστρεφουμε τα normals των x,z διοτι θελουμε
			//να προσθεσουμε την μετατοπιση στον αξονα με 0 normal 
			//αφαιρουμε απο το nz για ομοιομορφια στους τοιχους
			nx[i] = nx[i] + (nrz[i] * len1);
			ny[i] = nx[i] + (nry[i] * len1); //myHeight;
			nz[i] = nz[i] - (nrx[i] * len1);

			//find base edges (box)...
			if (rb->xmax < nx[i]) rb->xmax = nx[i] ;
            rb->ymax = (wr->height/2) + Room_Height ;
			if (rb->zmax < nz[i]) rb->zmax = nz[i] ;
			if (rb->xmin > nx[i]) rb->xmin = nx[i] ;
            rb->ymin = wr->height/2;
			if (rb->zmin > nz[i]) rb->zmin = nz[i] ;
			
		} // for i
        

		rb->KoryfCount = pleyres ;
		//base points
		for ( i = 0 ; i < pleyres ; i++ )
		{
			//get calculated points
			rb->Koryfsx[i]	= fx[i] - wr->width/2 + wr->outspace/2;
			rb->Koryfsy[i]	= wr->height/2;
			rb->Koryfsz[i]	= fz[i] - wr->depth/2 + wr->outspace/2;
		}


		rb->ObjectToInventor(sdoc->root) ;

		//set attr..
		rb->carrier_id = 0; //worldbase
		rb->SetCarrierSide(_TOP_); //top of worldbase
		rb->SetObjectSide(_BOTTOM_); //bottom of roombase
		//rb->outlook = 0;
		//το πρωτο σημείο του εγκιβωτισμου
		rb->totalx  = rb->ssx[0];
		rb->totaly  = rb->ssy[0];
		rb->totalz  = rb->ssz[0];
		//rb->object_refpoint = _DNBKLEFT_;

		rb->SaveProperties();
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
	m_height = 0.0f;
	//}}AFX_DATA_INIT
}


void CRoomBasePro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomBasePro)
	DDX_Text(pDX, IDC_PLAKAKI, m_plakaki);
	DDX_Text(pDX, IDC_PLAKAKI1, m_plakaki1);
	DDX_Text(pDX, IDC_PLAKAKI2, m_plakaki2);
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDV_MinMaxFloat(pDX, m_height, 0.f, 10000.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRoomBasePro, CDialog)
	//{{AFX_MSG_MAP(CRoomBasePro)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomWallPro message handlers
