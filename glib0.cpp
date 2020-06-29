// glib0.cpp : implementation file
//

#include "stdafx.h"
#include "..\SYNTH\SYNTH.h"
#include "glib0.h"

#include <math.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoNormal.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoNormalBinding.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLib0

CGLib0::CGLib0()
{
}

CGLib0::~CGLib0()
{
}


/*========================== GetPolyEquation ============================*/

CGLib0::GetPolyEquation ( float x1, float y1, float z1, float x2, float y2, float z2, 
					           float x3, float y3, float z3,
					           float *A, float *B, float *C, float *D ) 
{
     *A = (y1*z3-y3*z1)-(y2*z3-y3*z2)-(y1*z2-y2*z1) ;
     *B = (x3*z1-x1*z3)-(x3*z2-z3*x2)-(x2*z1-x1*z2) ;
     *C = (x1*y3-x3*y1)-(y3*x2-y2*x3)-(x1*y2-y1*x2) ;
     *D = x1*(y2*z3-y3*z2)-x2*(y1*z3-y3*z1)+x3*(y1*z2-y2*z1) ;

	 return 0 ;
} 

/*========================== GetPolyNormal ==============================*/

CGLib0::GetPolyNormal ( float x1, float y1, float z1, float x2, float y2, float z2, 
					    float x3, float y3, float z3,
					    float *x, float *y, float *z ) 
{
	float len ;

     // cross product
     *x = (y1-y2)*(z2-z3)-(z1-z2)*(y2-y3) ;
     *y = (z1-z2)*(x2-x3)-(x1-x2)*(z2-z3) ;
     *z = (x1-x2)*(y2-y3)-(y1-y2)*(x2-x3) ;
     // lenght
     len = sqrt((*x)*(*x)+(*y)*(*y)+(*z)*(*z)) ;

     if ( len < fabs(0.00001) ) len = 1.0 ;
     *x = *x / len ;
     *y = *y / len ;
     *z = *z / len ;

	 return 0 ;
} 

/*======================== GetPolyDistandPoint ========================*/

CGLib0::GetPolyDistandPoint ( float nx, float ny, float nz, 
						      float x0, float y0, float z0, float dist,
                              float *x, float *y, float *z ) 
{
     // (nx, ny, nz) normal vector
     // (x0, y0, z0) projection ) { (x,y,z) point on the polygon
     // dist the distance (+/-) ) { (x,y,z) from the polygon
     *x = x0 + dist*nx ;
     *y = y0 + dist*ny ;
     *z = z0 + dist*nz ;

	 return 0 ;
} 

/*================================== DefinePolygon000 ===============================*/

CGLib0::DefinePolygon000 ( int pleyres, float *len, float *angle, float mult,
    					   float *xx, float *yy, float *zz ) 
{
	int i ;
	float x0, y0, z0, x00, y00, z00, x, y, z,
		   vx, vy, vz, sx, sy, sz, len1 ;

     // its supposed that all points are on the (x,z) i.e. y == 0, syrface
     for ( i = 0 ; i <= pleyres-1 ; i++ ) 
	 {
         if ( i == 0 ) 
		 {
            x0 = 0 ;
            y0 = 0 ;
            z0 = 0 ;
            x  = 0 ;
            y  = 0 ;
            z  = len[i]*mult ;
         }
         else 
		 {
            GetPolyNormal( x0, y0, z0, x00, y00, z00, x0, y0+1, z0, &vx, &vy, &vz ) ;
            len1 = int(cos((180-angle[i]) * M_PI/180) * len[i]*mult) ;
            sx  = (x0-x00) * (len1+len[i-1]*10) / (len[i-1]*10) + x00 ;
            sy  = (y0-y00) * (len1+len[i-1]*10) / (len[i-1]*10) + y00 ;
            sz  = (z0-z00) * (len1+len[i-1]*10) / (len[i-1]*10) + z00 ;
            GetPolyDistandPoint ( vx, vy, vz, sx, sy, sz, sin((180-angle[i])*M_PI/180)*len[i]*mult,
                                  &x, &y, &z ) ;
         } ;

         x00 = x0 ;
         y00 = y0 ;
         z00 = z0 ;
         x0  = x ;
         y0  = y ;
         z0  = z ;

         // set the base coordinates
         *(xx+i) = x00 ; *(yy+i) = y00 ; *(zz+i) = z00 ;
     } ;

	 return 0 ;
} 

//=============================== GetDistance ===================================

float CGLib0::GetDistance ( float x1, float y1, float z1, float x2, float y2, float z2 ) 
{
     return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1)) ;
}

/*================================== CreatePrisma ===============================*/

SoNode *CGLib0::CreatePrisma (	SoMaterial *mat, SoTexture2 *txt, int txt_side,
								float height, int pleyres, 
								float *x, float *y, float *z ) 
{
	SoSeparator *sep = new SoSeparator ;
	SoTexture2  *txt0 ;

	// ... set the material
	sep->addChild( mat );	

	txt0 = NULL ;

	// ... create the base
	SoNode *base ;
	if (txt_side == pleyres && txt != NULL) txt0 = txt ;
	base = CreatePolygon ( txt0, 0, pleyres, x, y, z ) ;

	sep->addChild( base );	

	// ... add the sides
	
	SoNode *sd ;
	float norm[3] ;
	GetPolyNormal ( x[0], y[0], z[0], x[1], y[1], z[1], 
					x[2], y[2], z[2], &norm[0], &norm[1], &norm[2] ) ;

	float xx[100], yy[100], zz[100] ;

	for ( int i = 0 ; i < pleyres ; i++ )
	{
		xx[0] = x[i] ;
		yy[0] = y[i] ;
		zz[0] = z[i] ;
		if ( i < pleyres-1 ) 
		{
			xx[1] = x[i+1] ;
			yy[1] = y[i+1] ;
			zz[1] = z[i+1] ;
		}
		else
		{
			xx[1] = x[0] ;
			yy[1] = y[0] ;
			zz[1] = z[0] ;
		}
		GetPolyDistandPoint ( norm[0], norm[1], norm[2],
						      xx[1], yy[1], zz[1], height,
							  &xx[2], &yy[2], &zz[2] ) ;
		GetPolyDistandPoint ( norm[0], norm[1], norm[2],
						      xx[0], yy[0], zz[0], height,
							  &xx[3], &yy[3], &zz[3] ) ;

		if (txt_side == i && txt != NULL) txt0 = txt ;
		sd = CreatePolygon ( txt0, 1, 4, xx, yy, zz ) ;

	    if (txt != NULL) sep->addChild( txt ) ;
		sep->addChild( sd ) ;
	}

	// ... add the top
	SoNode *top ;
	for ( i = 0 ; i < pleyres ; i++ )
		GetPolyDistandPoint ( norm[0], norm[1], norm[2],
						      x[i], y[i], z[i], height,
							  &xx[i], &yy[i], &zz[i] ) ;
	
	if (txt_side == pleyres+1 && txt != NULL) txt0 = txt ;
	top = CreatePolygon ( txt0, 1, pleyres, xx, yy, zz ) ;
    
	sep->addChild( top );	

	return sep ;
}

/*================================== CreatePolygon ===============================*/

SoNode *CGLib0::CreatePolygon (	SoTexture2 *txt, 
								int side, int pleyres, 
								float *x, float *y, float *z ) 
{
	SoSeparator *sep = new SoSeparator ;

	float	vert[50][3] ;
	float	norm[2][3] ;

	// prepare data
	for ( int i = 0 ; i < pleyres ; i++ )
	{
		vert[i][0] = x[i] ;
		vert[i][1] = y[i] ;
		vert[i][2] = z[i] ;
	}
	GetPolyNormal ( x[0], y[0], z[0], x[1], y[1], z[1], 
					x[2], y[2], z[2], 
					&norm[0][0], &norm[0][1], &norm[0][2] ) ;

	if ( side == 0 )
	{
		norm[0][0] = -norm[0][0] ;
		norm[0][1] = -norm[0][1] ;
		norm[0][2] = -norm[0][2] ;
	}

	// setup coordinates
	SoCoordinate3 *c3	= new SoCoordinate3 ;
	c3->point.setValues(0,pleyres,vert) ;

	// setup faces
	SoFaceSet *fs = new SoFaceSet ;
	fs->numVertices.setValues(0,1,&pleyres) ;

	// setup normal
	SoNormal *nm = new SoNormal ;
	nm->vector.setValues(0,1,norm) ;
	SoNormalBinding *nb = new SoNormalBinding ;
	nb->value = SoNormalBinding::PER_FACE ;

    if (txt) sep->addChild( txt ) ;
	sep->addChild( nm );	
	sep->addChild( nb );	
	sep->addChild( c3 );	
	sep->addChild( fs );

	return sep ;
}

//================================ CreateFrame0 ==============================

SoNode *CGLib0::CreateFrame0 ( SoMaterial *mat, SoTexture2 *txt, int txt_side,
								int mode, float width, float height, 
								float x1, float y1, float z1,
								float x2, float y2, float z2 )
{
	float nx, ny, nz, xs[4], ys[4], zs[4] ;

	xs[0] = x1 ; ys[0] = y1 ; zs[0] = z1 ;
	xs[1] = x2 ; ys[1] = y2 ; zs[1] = z2 ;

	if ( mode == 0 ) // put the body on left of 1 - 2
		GetPolyNormal ( xs[0], ys[0], zs[0], 
						xs[0], ys[0]+100, zs[0],   // ψευδοσημείο
						xs[1], ys[1], zs[1], &nx, &ny, &nz ) ;
	else             // put the body on right or on midle of 1 - 2
		GetPolyNormal ( xs[0], ys[0]+100, zs[0],   // ψευδοσημείο
						xs[0], ys[0], zs[0], 
						xs[1], ys[1], zs[1], &nx, &ny, &nz ) ;

	xs[2] = xs[1] + nx * width ;  
	ys[2] = ys[1] + ny * width ;
	zs[2] = zs[1] + nz * width ;
	xs[3] = xs[0] + nx * width ;  
	ys[3] = ys[0] + ny * width ;
	zs[3] = zs[0] + nz * width ;

	return CreatePrisma ( mat, txt, txt_side, height, 4, xs, ys, zs ) ;
}

/////////////////////////////////////////////////////////////////////////////
// CGLib0 message handlers
