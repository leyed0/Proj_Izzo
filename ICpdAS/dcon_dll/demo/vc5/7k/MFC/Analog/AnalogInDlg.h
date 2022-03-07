#if !defined(AFX_ANALOGINDLG_H__BA389FA6_6B2D_11D3_BAE8_0080AD91800F__INCLUDED_)
#define AFX_ANALOGINDLG_H__BA389FA6_6B2D_11D3_BAE8_0080AD91800F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AnalogInDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnalogInDlg dialog

class CAnalogInDlg : public CDialog
{
// Construction
public:
	CAnalogInDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAnalogInDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_strBaudrate;
	int		m_nComPort;
	int		m_nModuleAddress;
	CString	m_strModuleType;
	CString	m_strChecksum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalogInDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAnalogInDlg)
	afx_msg void OnAnaloginput();
	afx_msg void OnOpenfirstly();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALOGINDLG_H__BA389FA6_6B2D_11D3_BAE8_0080AD91800F__INCLUDED_)
