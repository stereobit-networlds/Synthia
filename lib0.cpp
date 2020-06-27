// lib0.cpp : implementation file
//

#include "stdafx.h"
#include "..\Synth\SYNTH.h"
#include "lib0.h"

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoText2.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLib0

CLib0::CLib0()
{
}

CLib0::~CLib0()
{
}

/*========================== getvar =============================*/

void CLib0::getvar(	char *dd, char *mm,	
					char *vname1, char *vname2, char *value ) 
{
	char *i_vname, vname[100] ;
	int mlen = strlen(mm), dlen = strlen(dd) ;
	int i, row = 0, row1 = 0 ;

	// make the "vname"
	vname[0] = NULL ;
	strcat(vname,vname1) ;
	if (vname2 != NULL ) strcat(vname,vname2) ;

	// find in "mt" the "vname"
	if ((i_vname = strstr(mm,vname))==NULL)
	{
		value[0] = NULL ;
		return ;
	}

	// find the number of "\n" before the "i_vname"
	i = 0 ;
	do
	{
		if (mm[i] == '\r') row++ ;		// an other row is found
		if (mm + i == i_vname) break ;  // string termination
		if (mm[i] == NULL) break ;
		i++ ;
	} while (i < mlen) ;

	// vname is not found
	if (mm[i] == NULL)
	{
		value[0] = NULL ;
		return ;
	}

	// find the corresponding row in the "dd" string
	i = 0 ;
	do
	{
		if (dd[i] == '\r') row1++ ;		// an other row is found
		if (row == row1) break ;		// search termination 
		i++ ;
	} while (i < dlen) ;
	
	// line is not found
	if (dd[i] == NULL)
	{
		value[0] = NULL ;
		return ;
	}

	// copy the "dd[i+1]" to "value"
	for ( int j = 0 ; ; j++ )
	{
		if (row != 0)	value[j] = dd[i+2+j] ;
		else			value[j] = dd[i+j] ;

		if ((value[j] == NULL) || (value[j] == '\r')) break ;
	}
	if (value[j] == '\r') value[j] = NULL ;	// null terminate the result
}

/*======================= strtofloat ======================*/

float CLib0::strtofloat ( char *value ) 
{
	if (*value == NULL) return 0 ;
	float fl ;
	sscanf(value,"%f",&fl) ;
	return fl ;
}

/*======================== strtoint =====================*/

int CLib0::strtoint ( char *value ) 
{
	if (*value == NULL) return 0 ;
	int i ;
	sscanf(value,"%d",&i) ;
	return i ;
}

/*======================== floattostr ======================*/

CString CLib0::floattostr ( float fl )
{
	CString buf ;
	char buf1[50] ;

	sprintf(buf1,"%f",fl) ;
	buf = buf1 ;

	return buf ;
}

/*======================== inttostr ======================*/

CString CLib0::inttostr ( int i )
{
	CString buf ;
	char buf1[50] ;

	sprintf(buf1,"%d",i) ;
	buf = buf1 ;

	return buf ;
}

//======================= CStringToChar =====================

void CLib0::CStringToChar ( CString cstr, char *chr )
{
	for ( int i = 0 ; i < cstr.GetLength() ; i++)
		chr[i] = cstr.operator[](i) ;
	chr[i] = NULL ;
}

void CLib0::setSoSFFloatProp ( SoSeparator *sep, SbName pname, float val ) 
{
	SoText2 *txt ;
	SoField *f ;

	f = SoDB::createGlobalField(pname,SoSFFloat::getClassTypeId()) ;
	((SoSFFloat *)f)->setValue(val) ;
	txt = new SoText2 ;
	txt->string.connectFrom(SoDB::getGlobalField(pname)) ;	
	sep->addChild(txt) ;
}

float CLib0::getSoSFFloatProp ( SbName pname ) 
{
	float val = 0 ;
	SoSFFloat *f = (SoSFFloat *)(SoDB::getGlobalField(pname)) ;
	if (f) val = f->getValue() ;
	return val ;
}

void	CLib0::setSoSFStringProp ( SoSeparator *sep, SbName pname, CString val ) 
{
	SoText2 *txt ;
	SoField *f ;

	f = SoDB::createGlobalField(pname,SoSFString::getClassTypeId()) ;
	((SoSFString *)f)->setValue(val) ;
	txt = new SoText2 ;
	txt->string.connectFrom(SoDB::getGlobalField(pname)) ;	
	sep->addChild(txt) ;
}

CString	CLib0::getSoSFStringProp ( SbName pname ) 
{
	CString val = "" ;
	SoSFString *f = (SoSFString *)(SoDB::getGlobalField(pname)) ;
	if (f) val = f->getValue().getString() ;
	return val ;
}

void CLib0::setSoSFIntProp ( SoSeparator *sep, SbName pname, int val ) 
{
	SoText2 *txt ;
	SoField *f ;

	f = SoDB::createGlobalField(pname,SoSFInt32::getClassTypeId()) ;
	((SoSFInt32 *)f)->setValue(val) ;
	txt = new SoText2 ;
	txt->string.connectFrom(SoDB::getGlobalField(pname)) ;	
	sep->addChild(txt) ;
}

int CLib0::getSoSFIntProp ( SbName pname ) 
{
	int val = 0 ;
	SoSFInt32 *f = (SoSFInt32 *)(SoDB::getGlobalField(pname)) ;
	if (f) val = f->getValue() ;
	return val ;
}



/////////////////////////////////////////////////////////////////////////////
// CLib0 message handlers
