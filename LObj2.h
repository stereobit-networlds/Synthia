#if !defined(AFX_LOBJ2_H__B1008AA4_8DB7_11D2_81BC_A5113812E41F__INCLUDED_)
#define AFX_LOBJ2_H__B1008AA4_8DB7_11D2_81BC_A5113812E41F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LObj2.h : header file
//

#include <Inventor/nodes/SoSeparator.h>

class LObj2 : public CObject
{
// Construction
public:
	LObj2();

// Attributes
public:

	int		eidos ;  // tetrapleyro, pentapleyro, exapleyro

    float	height0 ;
    int		pano_kal, kato_kal ; // 1=������� ����,���� ������, 0=���
    int     pleyres ;
    float   len[10], angle[10] ;
    int		toix[9] ;  // 1=������� ������, 0=���

    int		anal_count ; // the number of sides that have been analysed
    int		anal_sides[3] ; // ����� ������� ����� ��������
    int		zcount[3] ;    // ������ �����
    float	zheight[3][6] ;  // ��� �����
    int		zccount[3][6] ;  // ������ ������ ��� ����
    float	zcwidth[3][6][3] ;  // ����� ������
    int		zcobjcount[3][6][3] ;  // ������ ��������� ��� �����
    float	objheight[3][6][3][6] ;
    float	objdepth[3][6][3][6] ;
    int		objtype[3][6][3][6] ;

    int		curv_count ; // the number of sides that have curvature
    int		curv_sides[3] ; // ����� ����� �� �������� �������
    int		curv_type[3] ; // ����� ��� �������� �������  (0=������)
    float	curv_angle[3] ; // ������ ��� ����������� �����

// Operations
public:

	void TableToObject ( char *dd, char *mm ) ;
	void CreateObject ( BOOL add, SoGroup *root, COleVariant eid_id[10],
						CDaoRecordset *dt, CDaoRecordset *mt ) ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LObj2)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~LObj2();

};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOBJ2_H__B1008AA4_8DB7_11D2_81BC_A5113812E41F__INCLUDED_)
