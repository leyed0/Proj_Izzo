// AnalogIn.h : main header file for the ANALOGIN application
//

#if !defined(AFX_ANALOGIN_H__BA389F95_6B2D_11D3_BAE8_0080AD91800F__INCLUDED_)
#define AFX_ANALOGIN_H__BA389F95_6B2D_11D3_BAE8_0080AD91800F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAnalogInApp:
// See AnalogIn.cpp for the implementation of this class
//

class CAnalogInApp : public CWinApp
{
public:
	CAnalogInApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalogInApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAnalogInApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALOGIN_H__BA389F95_6B2D_11D3_BAE8_0080AD91800F__INCLUDED_)
