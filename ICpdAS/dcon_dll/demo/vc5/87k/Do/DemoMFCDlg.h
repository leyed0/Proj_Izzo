// DemoMFCDlg.h : header file
//

#if !defined(AFX_DEMOMFCDLG_H__20784902_08E9_400A_B970_747F54F69E59__INCLUDED_)
#define AFX_DEMOMFCDLG_H__20784902_08E9_400A_B970_747F54F69E59__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDemoMFCDlg dialog

class CDemoMFCDlg : public CDialog
{
// Construction
public:
	CDemoMFCDlg(CWnd* pParent = NULL);	// standard constructor
    WORD CDemoMFCDlg::GetDlgItemHex(int nID);
    void CDemoMFCDlg::SetDlgItemHex(int nID, WORD nHex);

// Dialog Data
	//{{AFX_DATA(CDemoMFCDlg)
	enum { IDD = IDD_DEMOMFC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoMFCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoMFCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCancelMode();
	afx_msg void OnActive();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOMFCDLG_H__20784902_08E9_400A_B970_747F54F69E59__INCLUDED_)
