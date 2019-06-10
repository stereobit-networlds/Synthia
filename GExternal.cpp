// GExternal.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"
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
	
	SoDrawStyle *ds = new SoDrawStyle ;
	sep->addChild(ds) ;
	ds->style = SoDrawStyle::INVISIBLE ;

	
	//SaveProperties() ;  ?????????????????? δεν παιρνουν σωστες τιμες τα saved πεδια (το offset ειναι ενας big num )
    
	CString& mycode = code.SpanExcluding(_T(" ")); //βγάζω τα κενά απο το τέλος του string
	sep->setName(SbName(mycode)); //set node name 

	root->addChild(sep) ;

} 

/*======================== SaveProperties ===================*/

void CGExternal::SaveProperties ()
{
	// inherited action
	CGObject::SaveProperties() ;

	//sep->setName(name) ;  // set node name

	CLib0 lib ;
	CString soff = lib.inttostr(offset) ;

	lib.setSoSFStringProp ( sep, SbName("ob_code"+soff), code ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_descr"+soff), descr ) ;
	
	lib.setSoSFStringProp ( sep, SbName("ob_eid0"+soff), eid_id[0] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid1"+soff), eid_id[1] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid2"+soff), eid_id[2] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid3"+soff), eid_id[3] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid4"+soff), eid_id[4] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid5"+soff), eid_id[5] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid6"+soff), eid_id[6] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid7"+soff), eid_id[7] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid8"+soff), eid_id[8] ) ;
	lib.setSoSFStringProp ( sep, SbName("ob_eid9"+soff), eid_id[9] ) ;

	lib.setSoSFIntProp ( sep, SbName("next"+soff), next_id ) ;
	lib.setSoSFIntProp ( sep, SbName("prior"+soff), prior_id ) ;
	lib.setSoSFIntProp ( sep, SbName("carrier"+soff), carrier_id ) ;
	lib.setSoSFIntProp ( sep, SbName("topoth"+soff), topoth ) ;
	
	lib.setSoSFFloatProp ( sep, SbName("yangle"+soff), yangle ) ;

	lib.setSoSFFloatProp ( sep, SbName("lbp0"+soff), left_base_point[0] ) ;
	lib.setSoSFFloatProp ( sep, SbName("lbp1"+soff), left_base_point[1] ) ;
	lib.setSoSFFloatProp ( sep, SbName("lbp2"+soff), left_base_point[2] ) ;
	lib.setSoSFFloatProp ( sep, SbName("rbp0"+soff), right_base_point[0] ) ;
	lib.setSoSFFloatProp ( sep, SbName("rbp1"+soff), right_base_point[1] ) ;
	lib.setSoSFFloatProp ( sep, SbName("rbp2"+soff), right_base_point[2] ) ;

	lib.setSoSFFloatProp ( sep, SbName("ltp0"+soff), left_top_point[0] ) ;
	lib.setSoSFFloatProp ( sep, SbName("ltp1"+soff), left_top_point[1] ) ;
	lib.setSoSFFloatProp ( sep, SbName("ltp2"+soff), left_top_point[2] ) ;
	lib.setSoSFFloatProp ( sep, SbName("rtp0"+soff), right_top_point[0] ) ;
	lib.setSoSFFloatProp ( sep, SbName("rtp1"+soff), right_top_point[1] ) ;
	lib.setSoSFFloatProp ( sep, SbName("rtp2"+soff), right_top_point[2] ) ;

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

	GExternalProp *dlg = new GExternalProp ;

	float xdist, ydist ;

	dlg->m_code		= code ;
	dlg->m_descr	= descr ;
	dlg->m_yangle	= yangle ;
	dlg->m_topoth	= topoth ;
	dlg->m_xdist	= xdist ;
	dlg->m_ydist	= ydist ;

	int res = dlg->DoModal() ;

	if (res == IDOK)   
	{
		code	= dlg->m_code ;
		descr	= dlg->m_descr ;
		yangle	= dlg->m_yangle ;
		topoth	= dlg->m_topoth ;
		xdist	= dlg->m_xdist ;
		ydist	= dlg->m_ydist ;

		ObjectToInventor ( root ) ;
	}

	return res ;
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
