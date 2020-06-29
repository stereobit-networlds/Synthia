#if !defined(AFX_GOBJECT_H__6F3D3D21_8F47_11D2_81BC_BE09FAFB8E0E__INCLUDED_)
#define AFX_GOBJECT_H__6F3D3D21_8F47_11D2_81BC_BE09FAFB8E0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GObject.h : header file
//

#include <Inventor/nodes/SoSeparator.h>

/////////////////////////////////////////////////////////////////////////////
// CGObject window

class CGObject : public CObject
{
    DECLARE_DYNAMIC( CGObject )
// Construction
public:
	CGObject();

// Implementation
public:
	virtual ~CGObject();

	int offset ;                   //object offset = a/a
	int id ;                       //object id = kind of object
	int carrier_id, carrier_side ; //id and side of reference object
	int object_side ;              //the objects's side of connection with reference object
	int outlook ;                  // αποσταση απο την επιφανια αναφορας

	float pointX1,pointY1,pointZ1;  //carrier reference points
	float pointX2,pointY2,pointZ2;
	float pointX3,pointY3,pointZ3;
	float obj_pointX1,obj_pointY1,obj_pointZ1;  //object reference points
	float obj_pointX2,obj_pointY2,obj_pointZ2;
	float obj_pointX3,obj_pointY3,obj_pointZ3;

	float ssx[8], ssy[8], ssz[8] ; //εγκιβωτισμος
	float xmax,ymax,zmax,xmin,ymin,zmin;

	float totalx,totaly,totalz ;   //το ακριβές σημειο xyz του 0 σημείου
	int object_refpoint ;          //το σημείο συμφωνα με το οποιο γίνονται οι υπολογισμοι

	float rotangle ;               //η περιστροφη του αντικειμένου
	float left_d , right_d , up_d; //μετατοπισεις στην επιφανια του carrier
	float obj_raxisX,obj_raxisY,obj_raxisZ; //ο αξονας περιστροφής του αντικειμένου

	SoSeparator *sep ;



	void ObjectToInventor ( SoSeparator *root ) ;
	void SaveProperties() ;
	void InventorToObject( SoSeparator *root );
	void GetBox() ;
	 int EditProperties ( CDocument *d, SoSeparator *root ) ;
	void AddNewObject(SbVec3f p_point,SbVec3f p_normal);

	 bool IsArrayEqual(const int src[4], int dst[4]);
     void ArrayEqual(const int src[4], int dst[4]);
	 void ZeroArray(int arr[4]);
     void ReverceArray(int dst[4]);
	 void ReverceArray2(int dst[4]);
	float RadiansToDegrees(float r);
	float DegreesToRadians(float m);
	      GetVectorNormal(float Ax,float Ay,float Az,
                          float Bx,float By,float Bz,
						  float rX,float rY,float rZ,
						  float *nx,float *ny,float *nz) ;
	float GetPolyType(float x1, float y1, float z1, 
	  			      float x2, float y2, float z2, 
					  float x3, float y3, float z3,
					  float x, float y, float z ) ; 

	    void MakeObjInvisible() ;
        void MakeObjVisible() ;
	 SbVec3f GetTranslation() ;
        void SetTranslation(SbVec3f vals) ;
	   float GetRotationAngle() ;
	    void SetRotationAngle(float angle) ;
	 SbVec3f GetRotationAxis() ;
	    void SetRotationAxis(SbVec3f axis) ;
		void SetObjRotation(int axonas,float angle) ;
		void SetObjectCenter(int cpoint) ;
	SbMatrix GetObjectMatrix() ;
	 SbVec3f GetObjectVector() ;
	 SbVec3f GetObjectDirection(SbVec3f source) ;
	   float GetNormalsCorner(float x1,float y1,float z1,
	   				          float x2,float y2,float z2);

	void ShowCarrierRefPoints(float sizeofpoints) ;
	void ShowObjectRefPoints(float sizeofpoints) ;
	void ShowBoxPoints(float sizeofpoints) ;
	void ShowRefPoints(float size) ;
	void ShowTotalPoint(float sizeofpoints) ;
	void ShowCustomPoints(float sizeofpoints,
						  float x1,float y1,float z1,
						  float x2,float y2,float z2,
						  float x3,float y3,float z3) ;
	void SelectObject() ;

	void SetCarrierSide(int side) ;
	void GetCarrierSide() ;
	void SetObjectSide(int side) ;
	void GetObjectSide() ;
	     GetObjectNormal(float *normx,float *normy,float *normz) ;
		 GetCarrierNormal(float *normx,float *normy,float *normz) ;	
   float GetCarrierLength() ;
   float GetObjectLength() ;
   float GetBoxLength(int dimension) ;
   float GetDistanceX() ;
   float GetDistanceY() ;
   float GetHeightDistance();
   float GetLeftDistance() ;
   float GetRightDistance() ;
   float SetLeftDistance(float val) ;
   float SetRightDistance(float val) ;
         MoveOnCarrier(float d1, float d2,float *getx,float *gety,float *getz) ;
   float GetObjProjection() ;

   void FindCarrierSide(float x,float y,float z) ;
   void ClickSide(float x,float y,float z) ;
};

//axis def
#define _X_   0
#define _Y_   1
#define _Z_   2

//object definitions
#define _NONE_        0
#define _WORLDBASE_   1000
#define _ROOMBASE_    1001
#define _ROOMWALL_    1002
#define _EXTERNAL_    1003

//side's array definition
const int left[4]   = {0, 1, 4, 5};
const int front[4]  = {1, 2, 5, 6};
const int right[4]  = {2, 3, 6, 7};
const int back[4]   = {0, 3, 4, 7};
const int top[4]    = {4, 5, 6, 7};
const int bottom[4] = {0, 1, 2, 3};

//object side definitions
#define _NOWHERE_     0
#define _LEFT_        2000
#define _FRONT_       2001
#define _RIGHT_       2002
#define _BACK_        2003
#define _TOP_         2004
#define _BOTTOM_      2005

//object's corner definition
#define _DNBKLEFT_     0
#define _DNFRLEFT_     1
#define _DNFRRIGHT_    2
#define _DNBKRIGHT_    3
#define _UPBKLEFT_     4
#define _UPFRLEFT_     5
#define _UPFRRIGHT_    6
#define _UPBKRIGHT_    7
#define _UNDEFINED_ 9999  

//object's 3dimensions (x,y,z = length,width,height)
#define _LENGTH_    1
#define _WIDTH_     2
#define _HEIGHT_    3

//object rotation points
#define _CENTER_     4000
#define _BKLEFT_     4001
#define _FRLEFT_     4002
#define _BKRIGHT_    4003
#define _FRRIGHT_    4004


/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_GOBJECT_H__6F3D3D21_8F47_11D2_81BC_BE09FAFB8E0E__INCLUDED_)
