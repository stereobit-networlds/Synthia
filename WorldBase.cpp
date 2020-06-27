// WorldBase.cpp: implementation of the CWorldBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SYNTH.h"

#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoText2.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/SbString.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoRotation.h>

#include "WorldBase.h"
#include "lib0.h"
#include "SYNTHDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC( CWorldBase, CObject )

CWorldBase::CWorldBase()
{
	sep = NULL ;
}

CWorldBase::~CWorldBase()
{

}

/*======================== ObjectToInventor ================*/

void CWorldBase::ObjectToInventor ( SoSeparator *root )
{
    CLib0 lib ;

	// inherited action
	CGObject::ObjectToInventor(root) ;

	BOOL first_time = FALSE ;
	if (sep != NULL) 
		sep->removeAllChildren() ;
	else
    {
	    sep	= new SoSeparator ;
		first_time = TRUE ;
	}

    //setup trans & rot
	SoTranslation	*trans	= new SoTranslation ;
	SoRotation		*rotat	= new SoRotation ;

	//setup draw style
	SoDrawStyle *ds = new SoDrawStyle ;
	ds->style = SoDrawStyle::FILLED ;

	//init pick style
	SoPickStyle *ps = new SoPickStyle;
    ps->style.setValue(SoPickStyle::SHAPE) ;

	sep->addChild( ds ) ;
    sep->addChild( trans );	
	sep->addChild( rotat );
	sep->addChild( ps ) ;

	// setup shape
	SoCube *cb	= new SoCube ;
	cb->width  = width ;
	cb->depth  = depth ;
	cb->height = height ;
	
	// setup material
	SoMaterial  *mat = new SoMaterial;
	mat->diffuseColor.setValue( 0., 1., 0. ); //Green

	sep->setName("WorldBase") ;  // set node name

	// setup graph
	sep->addChild( mat );	
	sep->addChild( cb );

	GetBox();    //<<<<<-------------------------------- εγκιβωτισμος
	
	SaveProperties() ;
	if (first_time) root->addChild(sep) ;
}

/*======================== SaveProperties ===================*/

void CWorldBase::SaveProperties()
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

	//set attributes invisible & unpickable...
	SoDrawStyle *ds = new SoDrawStyle ;
	attr->addChild(ds) ;
	ds->style = SoDrawStyle::INVISIBLE ;

	SoPickStyle *ps = new SoPickStyle;
	attr->addChild(ps) ;
    ps->style.setValue(SoPickStyle::UNPICKABLE) ;

	// add global fields
	CLib0 lib ;

	lib.setSoSFFloatProp ( attr, "width", width ) ;
	lib.setSoSFFloatProp ( attr, "depth", depth ) ;
	lib.setSoSFFloatProp ( attr, "height", height ) ;
	lib.setSoSFStringProp ( attr, "c_name", c_name.getString() ) ;
	lib.setSoSFStringProp ( attr, "c_address", c_address.getString() ) ;
	lib.setSoSFStringProp ( attr, "c_city", c_city.getString() ) ;
	lib.setSoSFStringProp ( attr, "c_tel", c_tel.getString() ) ;
	lib.setSoSFIntProp ( attr, "outspace", outspace ) ;

	sep->addChild(attr);
}

/*======================== InventorToObject ================*/

void CWorldBase::InventorToObject ( SoSeparator *root )
{
	sep = root ;

	//inherited action
	CGObject::InventorToObject(root);

	CLib0 lib ;
    
	c_name    = lib.getSoSFStringProp("c_name") ;
	c_address = lib.getSoSFStringProp("c_address") ;
	c_city    = lib.getSoSFStringProp("c_city") ;
	c_tel     = lib.getSoSFStringProp("c_tel") ;
	width     = lib.getSoSFFloatProp("width") ;
	depth     = lib.getSoSFFloatProp("depth") ;
	height    = lib.getSoSFFloatProp("height") ;
	outspace  = lib.getSoSFIntProp("outspace") ;
}

void CWorldBase::GetBox()
{
	// inherited action
	CGObject::GetBox() ;

	//assign min(xyz),max(xyz)to roombase box
    //επειδη το worldbase ειναι Inventor Cube εχουμε ηδη βαση των min max υπολογισει
	//τα width,depth και επειδη ο inventor τοποθετει εξ'ορισμου το Cube στο
	//κεντρο του coord system τα min,max για τον εγκιβωτισμο γινονται ...

	xmin = -width/2;
	ymin = -height/2;
	zmin = -depth/2;

	xmax = width/2;
	ymax = height/2;
	zmax = depth/2;

	//****** down
	ssx[0] = xmin;
    ssy[0] = ymin;
	ssz[0] = zmin;

	ssx[1] = xmin;
    ssy[1] = ymin;
	ssz[1] = zmax;

	ssx[2] = xmax;
    ssy[2] = ymin;
	ssz[2] = zmax;

	ssx[3] = xmax;
    ssy[3] = ymin;
	ssz[3] = zmin;

	//****** up
	ssx[4] = xmin;
    ssy[4] = ymax;
	ssz[4] = zmin;

	ssx[5] = xmin;
    ssy[5] = ymax;
	ssz[5] = zmax;

	ssx[6] = xmax;
    ssy[6] = ymax;
	ssz[6] = zmax;

	ssx[7] = xmax;
    ssy[7] = ymax;
	ssz[7] = zmin;
	
}


/*======================= EditProperties ========================*/

int CWorldBase::EditProperties  ( CDocument *d, SoSeparator *root ) 
{
	// inherited action
	CGObject::EditProperties(d,root) ;

	CWorldBasePro *dlg = new CWorldBasePro ;

	dlg->m_name     = c_name.getString() ;
	dlg->m_address  = c_address.getString() ;
	dlg->m_city		= c_city.getString() ;
	dlg->m_tel		= c_tel.getString() ;

	int res = dlg->DoModal() ;

	if (res == IDOK)   
	{
		c_name		= dlg->m_name ;
		c_address	= dlg->m_address ;
		c_city		= dlg->m_city ;
		c_tel		= dlg->m_tel ;

		// update property values

		ObjectToInventor(root) ;
		
		ShowRefPoints(150.0); //<<<----------------------- show points
	}

	return res ;
}


//command for add room base
void CWorldBase::AddNewObject(SbVec3f p_point, SbVec3f p_normal)
{
		float	len[20], angle[20] ;
		int		toix[20] ;
		int		pleyres ;
		float   World_Height ;
		float	fx[20], fy[20], fz[20] ;  //first point array
		float	nx[20], ny[20], nz[20] ;  //next point array 
		float   nrx[20],nry[20],nrz[20] ; //normals array 
		float	vx, vy, vz,len1,len0 ;
		SbVec3f p2_point;


		CLib0 lib ;
		CGLib0 *glib = new CGLib0 ;

		// inherited action
	    CGObject::AddNewObject(p_point,p_normal) ;

		// transfer data from arrays
		len[0] = sdoc->l[0] ;
		len[1] = sdoc->l[1] ;
		len[2] = sdoc->l[2] ;
		len[3] = sdoc->l[3] ;
		len[4] = sdoc->l[4] ;
		len[5] = sdoc->l[5] ;
		len[6] = sdoc->l[6] ;
		len[7] = sdoc->l[7] ;

		angle[0] = sdoc->a[0] ;
		angle[1] = sdoc->a[1] ;
		angle[2] = sdoc->a[2] ;
		angle[3] = sdoc->a[3] ;
		angle[4] = sdoc->a[4] ;
		angle[5] = sdoc->a[5] ;
		angle[6] = sdoc->a[6] ;
		angle[7] = sdoc->a[7] ;

		toix[0] = sdoc->t[0] ;
		toix[1] = sdoc->t[1] ;
		toix[2] = sdoc->t[2] ;
		toix[3] = sdoc->t[3] ;
		toix[4] = sdoc->t[4] ;
		toix[5] = sdoc->t[5] ;
		toix[6] = sdoc->t[6] ;
		toix[7] = sdoc->t[7] ;

		World_Height = 100; //υψος world

		// setup world base 
		CWorldBase *wb = new CWorldBase ;

		sdoc->Obj[sdoc->ObjCount] = wb ; 
		sdoc->ObjCount++ ;

		wb->offset  = 0 ;
		wb->id      = _WORLDBASE_ ;
		wb->name    = "WorldBase"+lib.inttostr(sdoc->ObjCount-1) ; //name + counter
		wb->height	= World_Height ;   
		wb->c_name  = "ΠΑΥΛΙΔΗΣ ΡΑΦΑΗΛ" ;
		wb->outspace = 1000*2 ;

		// calculate pleyres
		for ( int i = 0 ; i <= 7 ; i++ )
			if (len[i] == 0) break ;
		pleyres = i + 1 ;

		//zero min max
        wb->xmax = wb->xmin = wb->ymax = wb->ymin = wb->zmax = wb->zmin = 0 ;
		//calculate points
        for ( i = 0 ; i < pleyres ; i++)
		{
			if (i == 0)
			{
				fx[i] = p_point[0];
				fy[i] = -(World_Height/2) ;
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
  			               		      nx[i-1], ny[i-1]+100, nz[i-1],						
					                  nx[i-1], ny[i-1], nz[i-1],
					                 &vx, &vy, &vz ) ;
				nrx[i] = -vx;
				nry[i] = -vy;
				nrz[i] = -vz;
			}

			len0 = int(sin((180-angle[i])*3.1415926/180)*len[i]);
			len1 = int(cos((180-angle[i]) * 3.1415926 /180) * len[i]) ;
                
			//προσθεtουμε την μετατοπιση στον αξονα με 1 normal
			nx[i] = fx[i] + (nrx[i] * len0);
			ny[i] = -(World_Height/2);
			nz[i] = fz[i] + (nrz[i] * len0);
			//αντιστρεφουμε τα normals των x,z διοτι θελουμε
			//να προσθεσουμε την μετατοπιση στον αξονα με 0 normal
			//αφαιρουμε απο το nz για ομοιομορφια (mirroring) στους τοιχους
			nx[i] = nx[i] + (nrz[i] * len1);
			ny[i] = -(World_Height/2);
			nz[i] = nz[i] - (nrx[i] * len1);

			//find world edges...
			if (wb->xmax < nx[i]) wb->xmax = nx[i] ;
			wb->ymax = World_Height/2 ;
			if (wb->zmax < nz[i]) wb->zmax = nz[i] ;
			if (wb->xmin > nx[i]) wb->xmin = nx[i] ;
			wb->ymin = -(World_Height/2);
			if (wb->zmin > nz[i]) wb->zmin = nz[i] ;
		} // for i

		//υπολογιζονται βαση των min,max
		wb->width	= (wb->xmax - wb->xmin) + wb->outspace ;
		wb->depth	= (wb->zmax - wb->zmin) + wb->outspace ;

		wb->ObjectToInventor ( sdoc->root ) ;

		//το πρωτο σημείο του εγκιβωτισμου
		wb->totalx  = wb->ssx[0];
		wb->totaly  = wb->ssy[0];
		wb->totalz  = wb->ssz[0];
		wb->object_refpoint = _DNBKLEFT_;

		wb->carrier_id = -1; //nowhere (invalid)
		wb->SetCarrierSide(_NOWHERE_); 
		wb->object_side = -1; //none (invalid)
		wb->outlook = 0;

		wb->SaveProperties();
}



/////////////////////////////////////////////////////////////////////////////
// CWorldBasePro dialog


CWorldBasePro::CWorldBasePro(CWnd* pParent /*=NULL*/)
	: CDialog(CWorldBasePro::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWorldBasePro)
	m_address = _T("ΝΕΟΣ ΠΕΛΑΤΗΣ");
	m_city = _T("");
	m_name = _T("");
	m_tel = _T("");
	//}}AFX_DATA_INIT
}


void CWorldBasePro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorldBasePro)
	DDX_Text(pDX, IDC_ADDRESS, m_address);
	DDX_Text(pDX, IDC_CITY, m_city);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_TEL, m_tel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWorldBasePro, CDialog)
	//{{AFX_MSG_MAP(CWorldBasePro)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorldBasePro message handlers
