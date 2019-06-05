#if !defined(AFX_CGLIB0_H__FA982304_877A_11D2_81BC_444553540000__INCLUDED_)
#define AFX_CGLIB0_H__FA982304_877A_11D2_81BC_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// cglib0.h : header file
//

#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTexture2.h>

// GPoint structure

struct GPoint
{
	float x ;
	float y ;
	float z ;
} ;

/////////////////////////////////////////////////////////////////////////////
// CGLib0 class

class CGLib0 : public CObject
{
// Construction
public:
	CGLib0();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLib0)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGLib0();

	GetPolyEquation ( float x1, float y1, float z1, float x2, float y2, float z2, 
				      float x3, float y3, float z3,
					  float *A, float *B, float *C, float *D ) ;
	GetPolyNormal ( float x1, float y1, float z1, float x2, float y2, float z2, 
				    float x3, float y3, float z3,
					float *x, float *y, float *z ) ;
	GetPolyDistandPoint ( float nx, float ny, float nz, 
					      float x0, float y0, float z0, float dist,
                          float *x, float *y, float *z ) ;
	DefinePolygon000 ( int pleyres, float *len, float *angle, float mult,
					   float *xx, float *yy, float *zz ) ;

	float GetDistance ( float x1, float y1, float z1, 
						float x2, float y2, float z2 ) ; 
	SoNode *CreatePrisma (	SoMaterial *mat, SoTexture2 *txt, int txt_side,
							float height, int pleyres, 
							float *x, float *y, float *z ) ;
	SoNode *CreatePolygon (	SoTexture2 *txt, 
								int side, int pleyres, 
								float *x, float *y, float *z ) ;
	SoNode *CGLib0::CreateFrame0 ( SoMaterial *mat, SoTexture2 *txt, int txt_side,
									int mode, float width, float height, 
									float x1, float y1, float z1,
									float x2, float y2, float z2 ) ;
} ;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGLIB0_H__FA982304_877A_11D2_81BC_444553540000__INCLUDED_)
