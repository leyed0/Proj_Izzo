// DemoMFC.h : main header file for the DEMOMFC application
//

#if !defined(AFX_DEMOMFC_H__472C164C_F863_4C4F_BB07_B704F1F60321__INCLUDED_)
#define AFX_DEMOMFC_H__472C164C_F863_4C4F_BB07_B704F1F60321__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemoMFCApp:
// See DemoMFC.cpp for the implementation of this class
//

class CDemoMFCApp : public CWinApp
{
public:
	CDemoMFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoMFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemoMFCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOMFC_H__472C164C_F863_4C4F_BB07_B704F1F60321__INCLUDED_)
