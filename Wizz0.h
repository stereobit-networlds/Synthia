#if !defined(AFX_WIZZ0_H__1BF688E1_8779_11D2_81BC_444553540000__INCLUDED_)
#define AFX_WIZZ0_H__1BF688E1_8779_11D2_81BC_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Wizz0.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizz0 dialog

class CWizz0 : public CDialog
{
// Construction
public:
	CWizz0(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CWizz0)
	enum { IDD = SYNTH_WIZZ0 };
	double	m_angle0;
	double	m_angle1;
	double	m_angle2;
	double	m_angle3;
	double	m_angle4;
	double	m_angle5;
	double	m_angle6;
	double	m_angle7;
	double	m_length0;
	double	m_length1;
	double	m_length2;
	double	m_length3;
	double	m_length4;
	double	m_length5;
	double	m_length6;
	double	m_length7;
	int		m_toix0;
	int		m_toix1;
	int		m_toix2;
	int		m_toix3;
	int		m_toix4;
	int		m_toix5;
	int		m_toix6;
	int		m_toix7;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizz0)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWizz0)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZZ0_H__1BF688E1_8779_11D2_81BC_444553540000__INCLUDED_)
