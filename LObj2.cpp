// LObj2.cpp : implementation file
//

#include "stdafx.h"
#include "SYNTH.h"
#include "SYNTHDoc.h"
#include "GExternal.h"
#include "Lib0.h"
#include "GLib0.h"

#include "LObj2.h"

#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoRotation.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LObj2

LObj2::LObj2()
{
}

LObj2::~LObj2()
{
}

/*========================== TableToObject ======================*/

void LObj2::TableToObject ( char *dd, char *mm ) 
{
	int i, j, k, l, off ;
	CLib0 lib ;
	char val[100], i_id[100] ;

    lib.getvar( dd, mm, "≈…ƒœ”", NULL, val ) ;   eidos    = lib.strtoint(val) ;
    lib.getvar( dd, mm, "’ÿœ”", NULL, val ) ;    height0  = lib.strtofloat(val) ;
    lib.getvar( dd, mm, "≈–¡ÕŸ", NULL, val ) ;   pano_kal = lib.strtoint(val) ;
    lib.getvar( dd, mm, " ¡‘Ÿ", NULL, val ) ;    kato_kal = lib.strtoint(val) ;
    lib.getvar( dd, mm, "–À≈’—≈”", NULL, val ) ; pleyres  = lib.strtoint(val) ;
    for ( i = 0 ; i < pleyres ; i++ ) 
	{
		sprintf(i_id,"%d",i+1) ;
        lib.getvar( dd, mm, "–À_Ã« ", i_id, val ) ;  len[i]	= lib.strtofloat(val) ;
        lib.getvar( dd, mm, "–À_√ŸÕ", i_id, val ) ;  angle[i]= lib.strtofloat(val) ;
        lib.getvar( dd, mm, "–À_‘œ…◊", i_id, val ) ; toix[i] = lib.strtoint(val) ;
	}

    lib.getvar( dd, mm, "–À«»œ”_ ¡Ã–", NULL, val ) ;    curv_count = lib.strtoint(val) ;
    for ( i = 0 ; i < curv_count ; i++ )
	{
		sprintf(i_id,"%d",i+1) ;
        lib.getvar( dd, mm, " ¡Ã–", i_id, val ) ;       curv_sides[i] = lib.strtoint(val) ;
        lib.getvar( dd, mm, "‘’–œ”_ ¡Ã–", i_id, val ) ; curv_type[i]  = lib.strtoint(val) ;
        lib.getvar( dd, mm, "√ŸÕ…¡_ ¡Ã–", i_id, val ) ; curv_angle[i] = lib.strtofloat(val) ;
	}

    // read the second part of the object
    off = 1 ;
	sprintf(i_id,"%d",off) ;
    lib.getvar( dd, mm, "V", i_id, val ) ; off = off + 1 ; anal_count = lib.strtoint(val) ;

    for ( i = 0 ; i < anal_count ; i++ ) 
	{
		sprintf(i_id,"%d",off) ;
        lib.getvar( dd, mm, "V", i_id, val ) ; off = off + 1 ; anal_sides[i] = lib.strtoint(val) ;
	}

    for ( i = 0 ; i < anal_count ; i++ ) 
	{
		sprintf(i_id,"%d",off) ;
        lib.getvar( dd, mm, "V", i_id, val) ; off = off + 1 ; zcount[i] = lib.strtoint(val) ;
        for ( j = 0 ; j < zcount[i] ; j++ ) 
		{
			sprintf(i_id,"%d",off) ;
            lib.getvar( dd, mm, "V", i_id, val) ; off = off + 1 ; zheight[i][j] = lib.strtofloat(val) ;
			sprintf(i_id,"%d",off) ;
            lib.getvar( dd, mm, "V", i_id, val) ; off = off + 1 ; zccount[i][j] = lib.strtoint(val) ;
            for ( k = 0 ; k < zccount[i][j] ; k++ ) 
			{
				sprintf(i_id,"%d",off) ;
                lib.getvar( dd, mm, "V", i_id, val) ; off = off + 1 ; zcwidth[i][j][k] = lib.strtofloat(val) ;
				sprintf(i_id,"%d",off) ;
                lib.getvar( dd, mm, "V", i_id, val) ; off = off + 1 ; zcobjcount[i][j][k] = lib.strtoint(val) ;
                for ( l = 0 ; l < zcobjcount[i][j][k] ; l++ ) 
				{
					sprintf(i_id,"%d",off) ;
                    lib.getvar( dd, mm, "V", i_id, val) ; off = off + 1 ; objheight[i][j][k][l] = lib.strtofloat(val) ;
					sprintf(i_id,"%d",off) ;
                    lib.getvar( dd, mm, "V", i_id, val) ; off = off + 1 ; objdepth[i][j][k][l] = lib.strtofloat(val) ;
					sprintf(i_id,"%d",off) ;
                    lib.getvar( dd, mm, "V", i_id, val) ; off = off + 1 ; objtype[i][j][k][l] = lib.strtoint(val) ;
				}
			}
		}
	}
}

/*========================== CreateObject =====================*/

void LObj2::CreateObject ( BOOL add, SoSeparator *root, COleVariant eid_id[10],
						   CDaoRecordset *dt, CDaoRecordset *mt ) 
{
	CGLib0	glib ;
	CLib0	lib ;
	float	xx[10], yy[10], zz[10] ;
	char	val[100] ;
	int		i, j, k, l ;
	float   zh ;
	CString code, descr ;

	code   = dt->GetFieldValue("EIDH0_C").pbVal ;
	descr  = dt->GetFieldValue("EIDH0_D").pbVal ;

	char dd[50000] ;
	char mm[50000] ;
	dd[0] = NULL ;
	mm[0] = NULL ;
	strcat(dd,(char *)dt->GetFieldValue("_MEMO").pbVal) ;
	strcat(mm,(char *)mt->GetFieldValue("_MEMO").pbVal) ;

	// give values to "this" object taken from the "dt" table
	TableToObject(dd,mm) ;

    // load PORTAKI
    CString por_txt = "" ;
	dt->SetCurrentIndex("EIDH0") ;
	if (dt->Seek("=",&eid_id[1]))
	{
		mt->SetCurrentIndex("_MREC") ;
		if (mt->Seek("=",&dt->GetFieldValue("_MREC"))) 
		{
			dd[0] = NULL ;
			mm[0] = NULL ;
			strcat(dd,(char *)dt->GetFieldValue("_MEMO").pbVal) ;
			strcat(mm,(char *)mt->GetFieldValue("_MEMO").pbVal) ;

			lib.getvar( dd, mm, "≈… œÕ¡", NULL, val ) ; 
			por_txt = val ;
			por_txt = por_txt + ".jpg" ;
		} 
		else
			AfxMessageBox("error 1") ;
	}
	else
		AfxMessageBox("error 2") ;

    // load SYRTARI
    CString syr_txt = "" ;
	dt->SetCurrentIndex("EIDH0") ;
	if (dt->Seek("=",&eid_id[2]))
	{
		mt->SetCurrentIndex("_MREC") ;
		if (mt->Seek("=",&dt->GetFieldValue("_MREC"))) 
		{
			dd[0] = NULL ;
			mm[0] = NULL ;
			strcat(dd,(char *)dt->GetFieldValue("_MEMO").pbVal) ;
			strcat(mm,(char *)mt->GetFieldValue("_MEMO").pbVal) ;
			lib.getvar( dd, mm, "≈… œÕ¡", NULL, val ) ; 
			syr_txt = val ;
			syr_txt = syr_txt + ".jpg" ;
		} 
		else
			AfxMessageBox("error 3") ;
	}
	else
		AfxMessageBox("error 4") ;
	
	// load KASSOMA
    float k_red = 1, k_green = 1, k_blue = 1 ;
	dt->SetCurrentIndex("EIDH0") ;
	if (dt->Seek("=",&eid_id[3]))
	{
		mt->SetCurrentIndex("_MREC") ;
		if (mt->Seek("=",&dt->GetFieldValue("_MREC"))) 
		{
			dd[0] = NULL ;
			mm[0] = NULL ;
			strcat(dd,(char *)dt->GetFieldValue("_MEMO").pbVal) ;
			strcat(mm,(char *)mt->GetFieldValue("_MEMO").pbVal) ;
			lib.getvar( dd, mm, " œ  …Õœ", NULL, val ) ; k_red = lib.strtofloat(val)/255.0 ;
			lib.getvar( dd, mm, "–—¡”…Õœ", NULL, val ) ; k_green = lib.strtofloat(val)/255.0 ;
			lib.getvar( dd, mm, "Ã–À≈", NULL, val ) ;    k_blue = lib.strtofloat(val)/255.0 ;
		} 
		else
			AfxMessageBox("error 5") ;
	}
	else
		AfxMessageBox("error 6") ;

	// load MPAZA
    float m_red = 1, m_green = 1, m_blue = 1 ;
	dt->SetCurrentIndex("EIDH0") ;
	if (dt->Seek("=",&eid_id[4]))
	{
		mt->SetCurrentIndex("_MREC") ;
		if (mt->Seek("=",&dt->GetFieldValue("_MREC"))) 
		{
			dd[0] = NULL ;
			mm[0] = NULL ;
			strcat(dd,(char *)dt->GetFieldValue("_MEMO").pbVal) ;
			strcat(mm,(char *)mt->GetFieldValue("_MEMO").pbVal) ;
			lib.getvar( dd, mm, " œ  …Õœ", NULL, val ) ; m_red = lib.strtofloat(val)/255.0 ;
			lib.getvar( dd, mm, "–—¡”…Õœ", NULL, val ) ; m_green = lib.strtofloat(val)/255.0 ;
			lib.getvar( dd, mm, "Ã–À≈", NULL, val ) ;    m_blue = lib.strtofloat(val)/255.0 ;
		} 
		else
			AfxMessageBox("error 7") ;
	}
	else
		AfxMessageBox("error 8") ;

	// ... START CREATING THE OBJECT
    glib.DefinePolygon000 ( pleyres, len, angle, 10, xx, yy, zz ) ;

    SoSeparator *sep ;
	CGExternal *ob ;
	
	// CREATE THE GObject ...
	if (add)
	{
		ob = new CGExternal ;
		sdoc->Obj[sdoc->ObjCount] = ob ; sdoc->ObjCount++ ;
		ob->sep = new SoSeparator ;
		sep		= ob->sep ;
	}
	else
		sep = new SoSeparator ;

	SoTranslation	*trans	= new SoTranslation ;
	SoRotation		*rot	= new SoRotation ;

	if ( add )
	{
		SoDrawStyle *ds = new SoDrawStyle ;
		sep->addChild(ds) ;
		ds->style = SoDrawStyle::INVISIBLE ;
	}
	sep->addChild ( trans ) ;
	sep->addChild ( rot ) ;

	// setup material for kassoma
	SoMaterial  *mat_kas = new SoMaterial;
	mat_kas->diffuseColor.setValue( k_red, k_green, k_blue ); 

	// setup material for mpaza
	SoMaterial  *mat_mpa = new SoMaterial;
	mat_mpa->diffuseColor.setValue( m_red, m_green, m_blue ); 

	// setup texture for portaki
	SoTexture2 *txt_por ;
	if (por_txt != "") 
    {
		txt_por = new SoTexture2 ;
		txt_por->filename.setValue("d:/ckosmos/synth/data/"+por_txt) ;
		txt_por->model = SoTexture2::DECAL ;
	}
	else
		txt_por = NULL ;

	// setup texture for syrtari
	SoTexture2 *txt_syr ;
	if (syr_txt != "") 
    {
		txt_syr = new SoTexture2 ;
		txt_syr->filename.setValue("d:/ckosmos/synth/data/"+syr_txt) ;
		txt_syr->model = SoTexture2::DECAL ;
	}
	else
		txt_syr = NULL ;

    // battery variables
    float left_base_point[3], right_base_point[3],
          left_top_point[3], right_top_point[3] ;

	SoNode *b ;

	// setup base
	if (kato_kal == 0) 
	{
		b = glib.CreatePrisma ( mat_kas, NULL, 0, 15, pleyres, xx, yy, zz ) ;
		sep->addChild( b );

		left_base_point[0] = xx[0] ;
		left_base_point[1] = yy[0] ;
		left_base_point[2] = zz[0] ;
		right_base_point[0] = xx[pleyres-1] ;
		right_base_point[1] = yy[pleyres-1] ;
		right_base_point[2] = zz[pleyres-1] ;
	}

	// setup top
	if (pano_kal == 0)
	{
		for ( i = 0 ; i < pleyres ; i++ )
			yy[i] = yy[i] + height0*10 ;
		b = glib.CreatePrisma ( mat_kas, NULL, 0, 15, pleyres, xx, yy, zz ) ;
		sep->addChild( b );

		left_top_point[0] = xx[0] ;
		left_top_point[1] = yy[0] ;
		left_top_point[2] = zz[0] ;
		right_top_point[0] = xx[pleyres-1] ;
		right_top_point[1] = yy[pleyres-1] ;
		right_top_point[2] = zz[pleyres-1] ;
		
		for ( i = 0 ; i < pleyres ; i++ )
			yy[i] = yy[i] - height0*10 ;
	}

	// ... draw any selves
	for ( j = 0 ; j < anal_count ; j++ )
	{
		zh = 0 ;
		for ( k = 0 ; k < zcount[j] ; k++ )
		{
			if (k == zcount[j]-1) continue ;
			zh = zh + zheight[j][k]*10 ;
			for ( i = 0 ; i < pleyres ; i++ )
				yy[i] = yy[i] + zh ;
			b = glib.CreatePrisma ( mat_kas, NULL, 0, 10, pleyres, xx, yy, zz ) ;
			sep->addChild( b );
			for ( i = 0 ; i < pleyres ; i++ )
				yy[i] = yy[i] - zh ;
		}
	}

	// ... draw the non-analyzed sides
	int	  anal_i = 0 ;
	for ( i = 0 ; i < pleyres ; i++ )
	{
		// do not draw the analyzed sides
		if ( anal_i < anal_count )
		{
			if (anal_sides[anal_i] == i+1) 
			{
				anal_i++ ;
				continue ;
			}
		}

		if ( toix[i] == 1 ) 
		{
			// ... ÏÂ ÙÔ ‹˜ÔÚ ÒÔÚ Ù· Ï›Û·
			if ( i < pleyres-1 )
				b = glib.CreateFrame0 ( mat_kas, NULL, 0, 0, 15, height0*10, 
										xx[i], yy[i], zz[i],
										xx[i+1], yy[i+1], zz[i+1] ) ;
			else
				b = glib.CreateFrame0 ( mat_kas, NULL, 0, 0, 15, height0*10, 
										xx[i], yy[i], zz[i],
										xx[0], yy[0], zz[0] ) ;
			sep->addChild( b );			
		}
	}

    // ====== draw the second part of the object

	SoTexture2 *txt ;
	SoMaterial *mat ;

	float x0, y0, z0, rx, ry, rz, len1, zcw, hh, tx, ty, tz, 
			v1x, v1y, v1z, h1x, h1y, h1z, v2x, v2y, v2z, h2x, h2y, h2z ;

    for ( i = 0 ; i < anal_count ; i++ )
	{
		x0 = xx[anal_sides[i]-1] ;      // bottom-left point
        y0 = yy[anal_sides[i]-1] ;
        z0 = zz[anal_sides[i]-1] ;
        rx = xx[anal_sides[i]] ;        // bottom-right point
        ry = yy[anal_sides[i]] ;
        rz = zz[anal_sides[i]] ;

		// define the width of the analysed face
		len1 = glib.GetDistance ( x0, y0, z0, rx, ry, rz ) ;
		// define the left-top point of the ortho parall
		tx = x0 ; ty = y0 + height0*10 ; tz = z0 ;

        zh = 0 ;
        for ( j = 0 ; j < zcount[i] ; j++ )
		{
			zcw = 0 ;
            for ( k = 0 ; k < zccount[i][j] ; k++ )
			{
				hh = 0 ;
				for ( l = 0 ; l < zcobjcount[i][j][k] ; l++ )
				{
					if ( objtype[i][j][k][l] != 0 )   // <> empty
					{
                        if (objtype[i][j][k][l] == 6) 
							mat = mat_mpa ;
						else
							mat = mat_kas ;
						txt = NULL ;
                        if (objtype[i][j][k][l] == 1)
							txt = txt_syr ;
                        if (objtype[i][j][k][l] == 2)
							txt = txt_por ;

                        v1x = (tx-x0)*(zh+hh)/(height0*10) ;
                        v1y = (ty-y0)*(zh+hh)/(height0*10) ;
                        v1z = (tz-z0)*(zh+hh)/(height0*10) ;
                        h1x = (rx-x0)*zcw/len1 ;
                        h1y = (ry-y0)*zcw/len1 ;
                        h1z = (rz-z0)*zcw/len1 ;
                        v2x = (tx-x0)*(zh+hh)/(height0*10) ;
                        v2y = (ty-y0)*(zh+hh)/(height0*10) ;
                        v2z = (tz-z0)*(zh+hh)/(height0*10) ;
                        h2x = (rx-x0)*(zcw+zcwidth[i][j][k]*10)/len1 ;
                        h2y = (ry-y0)*(zcw+zcwidth[i][j][k]*10)/len1 ;
                        h2z = (rz-z0)*(zcw+zcwidth[i][j][k]*10)/len1 ;
			
						b = glib.CreateFrame0 ( mat, txt, 2, 0, objdepth[i][j][k][l]*10, objheight[i][j][k][l]*10, 
												x0+v1x+h1x, y0+v1y+h1y, z0+v1z+h1z,
												x0+v2x+h2x, y0+v2y+h2y, z0+v2z+h2z ) ;
						sep->addChild( b );			
					}
                    hh = hh + objheight[i][j][k][l]*10 ;
				}
                zcw = zcw + zcwidth[i][j][k]*10 ;
			}
            zh = zh + zheight[i][j]*10 ;
		}
    }

	// CREATE THE GObject ...
	if (add)
	{
		ob->offset = sdoc->ob_offset ; sdoc->ob_offset++ ;
		ob->name   = "GExternal"  + lib.inttostr(ob->offset) ;;
		ob->code   = code ;
		ob->descr  = descr ;
		for ( i = 0 ; i < 10 ; i++ )
			ob->eid_id[i] = eid_id[i].pbVal ;

		for ( i = 0 ; i < 3 ; i++ )
		{
			ob->left_base_point[i]	= left_base_point[i] ;
			ob->right_base_point[i] = right_base_point[i] ;
			ob->left_top_point[i]	= left_top_point[i] ;
			ob->right_top_point[i]	= right_top_point[i] ;
		}

		ob->ObjectToInventor(root) ;
	}
	else
		root->addChild( sep ) ;
}

/////////////////////////////////////////////////////////////////////////////
// LObj2 message handlers
