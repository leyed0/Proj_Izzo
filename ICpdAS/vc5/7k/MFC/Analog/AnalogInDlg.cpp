// AnalogInDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AnalogIn.h"
#include "AnalogInDlg.h"
#include "uart.h"
#include "i7000.h"
CAnalogInDlg   dlg;
int      m_Baudrate;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CAnalogInDlg dialog


CAnalogInDlg::CAnalogInDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnalogInDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnalogInDlg)
	m_strBaudrate = _T("");
	m_nComPort = 0;
	m_nModuleAddress = 0;
	m_strModuleType = _T("");
	m_strChecksum = _T("");
	//}}AFX_DATA_INIT
}


void CAnalogInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnalogInDlg)
	DDX_CBString(pDX, IDC_BAUDRATE, m_strBaudrate);
	DDX_Text(pDX, IDC_COMPORT, m_nComPort);
	DDX_Text(pDX, IDC_MODULEADDRESS, m_nModuleAddress);
	DDX_CBString(pDX, IDC_MODULETYPE, m_strModuleType);
	DDX_CBString(pDX, IDC_CHECKSUM, m_strChecksum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnalogInDlg, CDialog)
	//{{AFX_MSG_MAP(CAnalogInDlg)
	ON_BN_CLICKED(IDC_ANALOGINPUT, OnAnaloginput)
	ON_BN_CLICKED(IDC_OPENFIRSTLY, OnOpenfirstly)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnalogInDlg message handlers

void CAnalogInDlg::OnAnaloginput() 
{
	// TODO: Add your control notification handler code here
	CString   m_Temp;
	WORD      wModuleType;
	char      *stopstring;
	WORD      w7000[10],wRetValue;
	float     f7000[10];
	char      szSendTo7000[80],szReceiveFrom7000[80];
	char      szTemp[80];
  
	//  get the module type 
    GetDlgItemText(IDC_MODULETYPE,dlg.m_strModuleType);
	wModuleType=(WORD)strtoul(dlg.m_strModuleType,&stopstring,16);
    TRACE("Module Type: %04x\n",wModuleType);

	//  get the module address
	GetDlgItemText(IDC_MODULEADDRESS,m_Temp);
	dlg.m_nModuleAddress=atoi(m_Temp);

	w7000[0]=dlg.m_nComPort;        // COM Port to open  0/1/2.../255
	w7000[1]=dlg.m_nModuleAddress;  // module address
    w7000[2]=wModuleType;           // module Type ex. 0x7012   
	w7000[3]= 0;                    // checksum 0:disable 1:enable
	w7000[4]=100;                   // timeout interval 100 means 0.1 second
	w7000[5]=0;                     // Input Channel No.
	w7000[6]=0;  // no debug info in szSendTo7000 and szReceiveFrom7000
	wRetValue=AnalogIn(w7000,f7000,szSendTo7000,szReceiveFrom7000);
	if( wRetValue>NoError )
	{
       Beep(100,100);
	   sprintf(szTemp,"Error Code: %d",wRetValue);
       AfxMessageBox(szTemp,MB_OK);	
	   return;
	}
    sprintf(szTemp,"%6.3f",f7000[0]);
	SetDlgItemText(IDC_ANALOGINPUTVALUE,szTemp);
	TRACE("The Analog Input = %5.3f\n",f7000[0]);
}


void CAnalogInDlg::OnOpenfirstly() 
{
	// TODO: Add your control notification handler code here
    CString  m_Temp;
	WORD     wRetValue;


    Beep(100,100);
	GetDlgItemText(IDC_COMPORT,m_Temp);
	dlg.m_nComPort=atoi(m_Temp);

	GetDlgItemText(IDC_MODULEADDRESS,m_Temp);
	dlg.m_nModuleAddress=atoi(m_Temp);

 	GetDlgItemText(IDC_BAUDRATE,dlg.m_strBaudrate);
    m_Baudrate=atoi(dlg.m_strBaudrate); 

 	GetDlgItemText(IDC_MODULETYPE,dlg.m_strModuleType);

 	GetDlgItemText(IDC_CHECKSUM,dlg.m_strChecksum);
	if( !strcmp(dlg.m_strChecksum,"Disable") )
	{
		TRACE("Openfirstly  Disable\n");
	}
	else
	{
		TRACE("Openfirstly  Enable\n");
	}

	wRetValue=Open_Com(dlg.m_nComPort,m_Baudrate,8,0,0);

	TRACE("Openfirstly  COMPort=%d\n",dlg.m_nComPort);
	TRACE("Openfirstly  Baudrate=%ld\n",m_Baudrate);
	TRACE("Openfirstly  Checsum=%s\n",dlg.m_strChecksum);
	TRACE("Openfirstly  ModuleType=%s\n",dlg.m_strModuleType);
	TRACE("Openfirstly  ModuleAddr=%d\n",dlg.m_nModuleAddress);
}

void CAnalogInDlg::OnOK() 
{
	// TODO: Add extra validation here
	Close_Com(dlg.m_nComPort);
	CDialog::OnOK();
}
