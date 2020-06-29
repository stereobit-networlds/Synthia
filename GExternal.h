#if !defined(AFX_GEXTERNAL_H__326C9C24_8F50_11D2_81BC_F1E9D6807A24__INCLUDED_)
#define AFX_GEXTERNAL_H__326C9C24_8F50_11D2_81BC_F1E9D6807A24__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GExternal.h : header file
//

#include "GObject.h"

/////////////////////////////////////////////////////////////////////////////
// CGExternal window

class CGExternal : public CGObject
{
    DECLARE_DYNAMIC( CGExternal )

// Construction
public:
	CGExternal();
	virtual ~CGExternal();

// Attributes
public:
	SbString name ;

	CString eid_id[10] ;
	CString code, descr ;

    CString  pval[10], pname[10] ;

	int next_id, prior_id ; //next and previous indexes
    float Ldist , Rdist ;   //battery distance from carrier (left and right)
	int rotpoint ; //the rotation point of object (backright,center,...)

    float local_rot ; //the local object rotation (begin as 0)
	float global_rot; //the global object rotation = (CObject)rotangle(=first global)+local_rot
	float xbox[8], ybox[8], zbox[8] ; //σημεία αποθηκευσης εγκιβωτισμου

// Operations
public:
	void ObjectToInventor ( SoSeparator *root ) ;
	void InventorToObject ( SoSeparator *root ) ;
	void SaveProperties() ;

	void GetBoxPoints(float Ax,float Ay,float Az,float Bx,float By,float Bz,
					  float fangle,float rotaxisX,float rotaxisY,float rotaxisZ,
					  float *Cx,float *Cy,float *Cz) ;
	void RotateBox(int rp,float a) ;
	void GetBox() ;
	int  EditProperties ( CDocument *d, SoSeparator *root ) ;

   float GetGlobalObjDirection(SbVec3f point,SbVec3f normal) ;
	void AddNewObject(SbVec3f p_point, SbVec3f p_normal) ;

	float GetBatteryLength() ;
	float GetBatteryLeftDistance() ;
	float GetBatteryRightDistance() ;
	float SetBatteryLeftDistance(float val) ;
	float SetBatteryRightDistance(float val) ;

	void MoveObjectTo(float d1,float d2) ;
	void MoveBattery() ;
    void RotateObjectTo(float ang) ;
	void RotateBattery() ;
	void ProjectObjectTo(float projection) ;
	void ProjectBattery() ;

	void AttachObject() ;

	void DelRebuildButtery() ;
	void ExtDelRebuildButtery() ;
	void DelObject(int aanum,int mode);

	void ReplaceObject() ;
	void UnGroupObjects();

	void CopyObject(int aanumber) ;
	void PasteObject() ;

	bool IsAttachedObject(int objno) ;
	void DeleteObject(int aanumber) ;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// GExternalProp dialog

class GExternalProp : public CDialog
{
// Construction
public:
	GExternalProp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GExternalProp)
	enum { IDD = SYNTH_GEXTERNAL_PROP };
	CString	m_code;
	CString	m_descr;
	int		m_topoth;
	float	m_xdist;
	float	m_yangle;
	float	m_ydist;
	float   m_leftdist;
	float   m_rightdist;
	float   m_x1dist;
	float	m_objLen;
	float	m_batLen;
	float	m_outlook;
	int		m_rotpoint;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GExternalProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GExternalProp)
         // NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEXTERNAL_H__326C9C24_8F50_11D2_81BC_F1E9D6807A24__INCLUDED_)
