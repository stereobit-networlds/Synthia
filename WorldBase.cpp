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

	// setup shape
	SoCube *cb	= new SoCube ;
	cb->width  = width ;
	cb->depth  = depth ;
	cb->height = height ;
	
	// setup material
	SoMaterial  *mat = new SoMaterial;
	mat->diffuseColor.setValue( 1., 0., 0. ); //Red

	sep->setName("WorldBase") ;  // set node name

	// setup graph
	sep->addChild( mat );	
	sep->addChild( cb );

	SoPickStyle *ps = new SoPickStyle;
	sep->addChild(ps) ;
    ps->style.setValue(SoPickStyle::UNPICKABLE) ;

	SoDrawStyle *ds = new SoDrawStyle ;
	sep->addChild(ds) ;
	ds->style = SoDrawStyle::INVISIBLE ;
	
	SaveProperties() ;
	if (first_time) root->addChild(sep) ;
}

/*======================== SaveProperties ===================*/

void CWorldBase::SaveProperties ()
{
	// inherited action
	CGObject::SaveProperties() ;

	sep->setName(name) ;  // set node name

	SoSeparator *attr = new SoSeparator ;
	attr->setName("Attributes") ;
	// add global fields
	CLib0 lib ;
    lib.setSoSFFloatProp ( attr, SbName("Id01"), sdoc->ObjCount ) ; //save object's counter as id

	lib.setSoSFFloatProp ( attr, "width", width ) ;
	lib.setSoSFFloatProp ( attr, "depth", depth ) ;
	lib.setSoSFFloatProp ( attr, "height", height ) ;
	lib.setSoSFStringProp ( attr, "c_name", c_name.getString() ) ;
	lib.setSoSFStringProp ( attr, "c_address", c_address.getString() ) ;
	lib.setSoSFStringProp ( attr, "c_city", c_city.getString() ) ;
	lib.setSoSFStringProp ( attr, "c_tel", c_tel.getString() ) ;

	sep->addChild(attr);
}

/*======================== InventorToObject ================*/

void CWorldBase::InventorToObject ( SoSeparator *root )
{
	sep = root ;

	CLib0 lib ;
	c_name    = lib.getSoSFStringProp("c_name") ;
	c_address = lib.getSoSFStringProp("c_address") ;
	c_city    = lib.getSoSFStringProp("c_city") ;
	c_tel     = lib.getSoSFStringProp("c_tel") ;
	width     = lib.getSoSFFloatProp("width") ;
	depth     = lib.getSoSFFloatProp("depth") ;
	height    = lib.getSoSFFloatProp("height") ;
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
/*
		SoField *f ;
		f = SoDB::createGlobalField("c_name",SoSFString::getClassTypeId()) ;
		((SoSFString *)f)->setValue(c_name) ;
		f = SoDB::createGlobalField("c_city",SoSFString::getClassTypeId()) ;
		((SoSFString *)f)->setValue(c_city) ;
		f = SoDB::createGlobalField("c_address",SoSFString::getClassTypeId()) ;
		((SoSFString *)f)->setValue(c_address) ;
		f = SoDB::createGlobalField("c_tel",SoSFString::getClassTypeId()) ;
		((SoSFString *)f)->setValue(c_tel) ;

		d->SetTitle(c_name.getString()) ; // set the window caption
*/
		ObjectToInventor(root) ;
	}

	return res ;
}

/////////////////////////////////////////////////////////////////////////////
// CWorldBasePro dialog


CWorldBasePro::CWorldBasePro(CWnd* pParent /*=NULL*/)
	: CDialog(CWorldBasePro::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWorldBasePro)
	m_address = _T("меос пекатгс");
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
