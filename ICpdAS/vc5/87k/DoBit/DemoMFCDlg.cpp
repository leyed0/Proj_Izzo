// DemoMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DemoMFC.h"
#include "DemoMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "I7000.h"
#include "I7000u.cpp"
#include "I87000.h"

WORD  wRtn;
WORD  wTtlChannel;
DWORD wMaxValue;


/////////////////////////////////////////////////////////////////////////////
// CDemoMFCDlg dialog

CDemoMFCDlg::CDemoMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoMFCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoMFCDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoMFCDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoMFCDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoMFCDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_Active, OnActive)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_Exit, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoMFCDlg message handlers

BOOL CDemoMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Initialize setting for GUI
	((CComboBox*)GetDlgItem(IDC_ModuleID))->SetCurSel(0);   // Module ID

	CComboBox *pcb;
	pcb = (CComboBox*)GetDlgItem(IDC_Com);                  
	ISetCOMString( pcb, 1, 255 );                           // COM port Strings

    ((CComboBox*)GetDlgItem(IDC_BaudRate))->SetCurSel(4);   // Baud Rate
    ((CComboBox*)GetDlgItem(IDC_Checksum))->SetCurSel(0);	// Checksum
    ((CComboBox*)GetDlgItem(IDC_OutputMode))->SetCurSel(1);	// Output Mode
    ((CComboBox*)GetDlgItem(IDC_ChannelMode))->SetCurSel(1);// Channel Mode

	SetDlgItemText( IDC_Address, TEXT("1") );   // Module Address
	SetDlgItemText( IDC_Do,      TEXT("1") );   // Digital Output Value
	SetDlgItemText( IDC_Rb,      TEXT("1") );   // Read Back Value
	SetDlgItemText( IDC_Channel, TEXT("0") );   // Channel Number


	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoMFCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoMFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemoMFCDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

     gdwBuf[8] = GetDlgItemHex( IDC_Do ) & 1; // digital data to output
	 // Change the output value dependents on Output Mode
     switch ( ((CComboBox*)GetDlgItem(IDC_OutputMode))->GetCurSel() )
     {
     case 1:  // Inverted
        gdwBuf[8] = 1 - gdwBuf[8];
        break;
     }
     SetDlgItemHex( IDC_Do, (WORD)gdwBuf[8] );

     // Channel Number (Bit)
     gdwBuf[7] = GetDlgItemInt( IDC_Channel ) & 0xF;
     switch ( ((CComboBox*)GetDlgItem(IDC_ChannelMode))->GetCurSel() )
     {
     case 1:  // Increment
        gdwBuf[7] = gdwBuf[7] + 1;
        if (gdwBuf[7] >= (DWORD)wTtlChannel)
            gdwBuf[7] = 0;
        break;
     case 2:  // Decrement
        if (gdwBuf[7] == 0)
            gdwBuf[7] = wTtlChannel;
        gdwBuf[7] = gdwBuf[7] - 1;
        break;
     }
     SetDlgItemInt( IDC_Channel, gdwBuf[7], FALSE );

	 // Calling the digital output function for 87K series 
     wRtn = DigitalBitOut_87K(gdwBuf, gfBuf, gszSend, gszReceive);
     if (wRtn != 0)
     {
         OnActive( );
		 char szErr[80];
		 sprintf( szErr, "DigitalBitOut_87K() Error!! Error Code: %d", wRtn );
         AfxMessageBox( szErr );
		 return;
     }

     gdwBuf[5] = 0;
	 // Calling the digital output read-back function for 87K series
     wRtn = DigitalOutReadBack_87K(gdwBuf, gfBuf, gszSend, gszReceive);
     if (wRtn != 0)
     {
          SetDlgItemText( IDC_Rb, TEXT("Error") );
     }
     else
          SetDlgItemHex( IDC_Rb, (WORD) (gdwBuf[5] >> gdwBuf[7]) & 1);
	
	CDialog::OnTimer(nIDEvent);
}

void CDemoMFCDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	// TODO: Add your message handler code here
}

void CDemoMFCDlg::OnActive() 
{
	// TODO: Add your control notification handler code here

	char btnTitle[10];
	// Stop by User
	GetDlgItemText(IDC_Active, btnTitle, 9);
	if ( btnTitle[0] == 'S' ) {
		SetDlgItemText( IDC_Active, "Active" );
		KillTimer(1);         // Stop Timer
		Sleep( 500 );
		Close_Com( gcPort );  // Close COM port
		GetDlgItem( IDC_Exit )->EnableWindow( TRUE );
		return;
	}

	// Get the COM port
    gcPort = (char)(((CComboBox*)GetDlgItem(IDC_Com))->GetCurSel() + 1);
	// Get the Baud Rate
	gdwBaudRate = GetDlgItemInt( IDC_BaudRate, NULL, FALSE );
    wRtn = IOpenCom(gcPort, gdwBaudRate);  // Open COM port
    if (wRtn != NoError)
    {
         AfxMessageBox( "COM port open error!!" );
         return;
    }

    gdwBuf[0] = gcPort;                           // COM Port
    gdwBuf[1] = GetDlgItemInt(IDC_Address);       // Module Address
    gdwBuf[2] = GetDlgItemHex( IDC_ModuleID );    // Module ID
    gdwBuf[3] = ((CComboBox*)GetDlgItem(IDC_Checksum))->GetCurSel();  // CheckSum Disable or Enable
    gdwBuf[4] = 100;                              // TimeOut = 0.1 second
    //gdwBuf[5] = 0;                              // 16-bit digital data to output
    gdwBuf[6] = 1;                                // string debug

     // Total Channels & Max Output value
     switch ( gdwBuf[2] )
     {
     case 0x87063:
          wTtlChannel = 4;
          wMaxValue   = 0xF;
          break;
     case 0x87054: case 0x87055: case 0x87064:
     case 0x87065: case 0x87066: case 0x87068:
          wTtlChannel = 8;
          wMaxValue   = 0xFF;
          break;
     case 0x87057:
     default:
          wTtlChannel = 16;
          wMaxValue   = 0xFFFF;
          break;
     }

	
	SetTimer(1, 500, NULL);   // Start the timer
	SetDlgItemText( IDC_Active, "Stop" );
	GetDlgItem( IDC_Exit )->EnableWindow( FALSE );
}

void CDemoMFCDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
	
}

WORD CDemoMFCDlg::GetDlgItemHex(int nID)
{
	static const int nLength = 20;
	char szStr[nLength], * stopstring;
	
	GetDlgItemText(nID, szStr, 19);
	return (WORD) strtoul( szStr, &stopstring, 16 );
}


void CDemoMFCDlg::SetDlgItemHex(int nID, WORD nHex)
{
	static const int nLength = 20;
	char string[nLength];

	_ltoa( nHex, string, 16 );
	SetDlgItemText(nID, string);
}

