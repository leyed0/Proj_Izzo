
// The following functions are designed MFC only

#include <windows.h>
#include "I7000.h"

char  gcPort;         //COM Port
long  gdwBaudRate;    //Baud Rate
WORD  gwCheckSum;
char  gcDataBit, gcParity, gcStopBit;

char  gszSend[80];    //Debug string 
char  gszReceive[80]; 

WORD  gw7000[11];     //data buffer for 7K series function
float gf7000[11];
DWORD gdwBuf[11];     //data buffer for 8K/87K series function
float gfBuf[11];


//*************************************
void IFillWordArray04(WORD *wArray, WORD wVal0, WORD wVal1, WORD wVal2, WORD wVal3, WORD wVal4)
{
	wArray[0]=wVal0;
	wArray[1]=wVal1;
	wArray[2]=wVal2;
	wArray[3]=wVal3;
	wArray[4]=wVal4;
}

//*************************************
void IFillWordArray59(WORD *wArray, WORD wVal5, WORD wVal6, WORD wVal7, WORD wVal8, WORD wVal9)
{
	wArray[5]=wVal5;
	wArray[6]=wVal6;
	wArray[7]=wVal7;
	wArray[8]=wVal8;
	wArray[9]=wVal9;
}

//*************************************
void IFillFloatArray04(float *fArray, float fVal0, float fVal1, float fVal2, float fVal3, float fVal4)
{
	fArray[0]=fVal0;
	fArray[1]=fVal1;
	fArray[2]=fVal2;
	fArray[3]=fVal3;
	fArray[4]=fVal4;
}

//*************************************
void IFillFloatArray59(float *fArray, float fVal5, float fVal6, float fVal7, float fVal8, float fVal9)
{
	fArray[5]=fVal5;
	fArray[6]=fVal6;
	fArray[7]=fVal7;
	fArray[8]=fVal8;
	fArray[9]=fVal9;
}

//*************************************
WORD IOpenCom(char cComPort, DWORD dwBaudRate)
{
	return Open_Com( cComPort, dwBaudRate, 8, 0 , 0 );
}


//*************************************
void ISetCOMString(CComboBox *cb, int iStart, int iEnd)
{
   int i;
   char szStr[10];

   cb->ResetContent();
   for (i=iStart;i<=iEnd;i++) {
	   sprintf(szStr, "COM%d", i);
       cb->AddString( szStr );
   }
   cb->SetCurSel(0);
}

//*************************************
void ISetBaudRateString(CComboBox *cb)
{
     cb->ResetContent();
     cb->AddString("115200");
     cb->AddString("57600");
     cb->AddString("38400");
     cb->AddString("19200");
     cb->AddString("9600");
     cb->AddString("4800");
     cb->AddString("2400");
     cb->AddString("1200");
     cb->SetCurSel( 0 );
}

//*************************************
CString IGetErrorString(WORD wErrCode)
{
    CString ErrString;
    
    switch (wErrCode) {
	case  0: ErrString = "No Error" ;                  break;
	case  1: ErrString = "Function Error";             break;
	case  2: ErrString = "Port Error";                 break;
	case  3: ErrString = "Baud Rate Error";            break;
	case  4: ErrString = "Data Error";                 break;
	case  5: ErrString = "Stop Error";                 break;
	case  6: ErrString = "Parity Error";               break;
	case  7: ErrString = "CheckSum Error";             break;
	case  8: ErrString = "Not Open";                   break;
	case  9: ErrString = "Send Thread Create Error";   break;
	case 10: ErrString = "Send Command Error";         break;
	case 11: ErrString = "Read Com Port Status Error"; break;
	case 12: ErrString = "Result String Check Error";  break;
	case 13: ErrString = "Command Error";              break;
	//case 14: ErrString = ""; break;
	case 15: ErrString = "Time Out";                   break;
	//case 16: ErrString = ""; break;
	case 17: ErrString = "Module Id Error";            break;
	case 18: ErrString = "AD Channel Error";           break;
	case 19: ErrString = "Under Input Range";          break;
	case 20: ErrString = "Exceed Input Range";         break;
	case 21: ErrString = "Invalidate Counter No";      break;
	case 22: ErrString = "Invalidate Counter Value";   break;
	case 23: ErrString = "Invalidate Gate Mode";       break;
        default :
                 ErrString = "Unknown Error";              break;
    }
    return ErrString ;
}

