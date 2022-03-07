#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "I7000.h"

void	READ_CMD(char *);
WORD	ASCII_TO_HEX(char);
char	HEX_TO_ASCII(WORD wHex);
void	TEST_CMD(HWND, int, int, int, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char	cPort=2; /* COM-2 */
WORD	wAddr=1; /* module address=1 */
char	szSend[80], szReceive[80];
int	iLine;

/* -------------------------------------------------------------------- */

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
		    PSTR szCmdLine, int iCmdShow)
     {
     static char szAppName[] = "Demo1";
     HWND	 hwnd ;
     MSG	 msg ;
     WNDCLASSEX  wndclass ;

     wndclass.cbSize	    = sizeof(wndclass);
     wndclass.style	    = CS_HREDRAW|CS_VREDRAW;
     wndclass.lpfnWndProc   = WndProc;
     wndclass.cbClsExtra    = 0;
     wndclass.cbWndExtra    = 0;
     wndclass.hInstance     = hInstance;
     wndclass.hIcon	    = LoadIcon(NULL, IDI_APPLICATION);
     wndclass.hCursor	    = LoadCursor(NULL, IDC_ARROW);
     wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
     wndclass.lpszMenuName  = NULL;
     wndclass.lpszClassName = szAppName;
     wndclass.hIconSm	    = LoadIcon(NULL, IDI_APPLICATION);

     RegisterClassEx(&wndclass) ;
     hwnd=CreateWindow(szAppName,"cPort=[0]  wAddr=[2][3]  szSend=[5..]",
			  WS_OVERLAPPEDWINDOW,
			  CW_USEDEFAULT, CW_USEDEFAULT,
			  CW_USEDEFAULT, CW_USEDEFAULT,
			  NULL, NULL, hInstance, NULL) ;
     ShowWindow(hwnd,SW_SHOWMAXIMIZED);
     UpdateWindow(hwnd);

     while (GetMessage(&msg, NULL, 0, 0))
	  {
	  TranslateMessage(&msg);
	  DispatchMessage(&msg);
	  }
     return msg.wParam;
     }

/* -------------------------------------------------------------------- */

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
static int  cxChar, cyChar, cxClient, cyClient, cxBuffer, cyBuffer,
	    xCaret, yCaret;
static char cBuf[80];
HDC	    hdc;
TEXTMETRIC  tm;
PAINTSTRUCT ps;
int	    i;

switch (iMsg)
  {
  case WM_CREATE :		       // window initial
       hdc=GetDC(hwnd);
       SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
       GetTextMetrics(hdc, &tm);
       cxChar=tm.tmAveCharWidth;
       cyChar=tm.tmHeight;
       ReleaseDC(hwnd, hdc);
       szSend[0]=0;	/* initial command */
       return 0;
  case WM_SIZE :
       cxClient=LOWORD(lParam); 	// window size in pixels
       cyClient=HIWORD(lParam);
       cxBuffer=max(1,cxClient/cxChar); // window size in characters
       cyBuffer=max(1,cyClient/cyChar);
       return 0;
  case WM_SETFOCUS :
       CreateCaret(hwnd, NULL, cxChar, cyChar);
       SetCaretPos(xCaret * cxChar, yCaret * cyChar);
       ShowCaret(hwnd);
       return 0;
  case WM_KILLFOCUS :
       HideCaret(hwnd);
       DestroyCaret();
       return 0;
  case WM_CHAR :			// user press KEYBOARD
       for (i = 0 ; i < (int) LOWORD(lParam) ; i++)
       {
       switch (wParam)
	 {
	 case '\b' :                    // backspace pressed
	   if (xCaret > 0)
	   {
	   xCaret-- ;
	   cBuf[xCaret]=' ';
	   HideCaret(hwnd);
	   hdc=GetDC(hwnd);
	   SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
	   TextOut(hdc, xCaret * cxChar, yCaret * cyChar,cBuf+xCaret,1);
	   ShowCaret(hwnd);
	   ReleaseDC(hwnd, hdc);
	   }
	   break ;
	 case '\r' :                    // carriage return  pressed
	   cBuf[xCaret]=0;
	   if (xCaret!=0) {xCaret=0; yCaret++;}
	   READ_CMD(cBuf);
	   TEST_CMD(hwnd,xCaret, cxChar, yCaret,cyChar);
	   xCaret=0; yCaret+=iLine;
	   if (yCaret >= cyBuffer) InvalidateRect(hwnd, NULL, TRUE);
	   break ;
	 case '\x1B' :                  // escape pressed
	   InvalidateRect (hwnd, NULL, TRUE) ;
	   xCaret=yCaret=0;
	   break ;
	 default :			// other KEY pressed
	   cBuf[xCaret]=(char) wParam;
	   HideCaret(hwnd);
	   hdc=GetDC (hwnd);
	   SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
	   TextOut(hdc,xCaret*cxChar,yCaret*cyChar,cBuf+xCaret,1);
	   ShowCaret(hwnd);
	   ReleaseDC(hwnd, hdc);
	   xCaret++;
	   break ;
	 }
       }
       SetCaretPos(xCaret*cxChar, yCaret*cyChar);
       return 0;
  case WM_PAINT :			// clr and show HELP
       InvalidateRect(hwnd, NULL, TRUE);
       hdc=BeginPaint(hwnd, &ps);
       SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));

       sprintf(cBuf,"NOW --> cPort=%d, wAddr=%d, szSend=[%s]",cPort,wAddr,szSend);
       TextOut(hdc,0,0,cBuf,strlen(cBuf));
       xCaret = 0 ; yCaret=1;
       SetCaretPos(0,yCaret*cyChar);

       EndPaint(hwnd, &ps);
       return 0;
  case WM_DESTROY :
       PostQuitMessage(0);
       return 0 ;
  }
return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

/* -------------------------------------------------------------------- */
/* [0]=cPort, [2][3]=wAddr, [5...]=szSend[]				*/

void READ_CMD(char szCmd[])
{
WORD wT1,wT2;

if (szCmd[0]==0) return;	// only press [Enter]

cPort=(char)ASCII_TO_HEX(szCmd[0]);

wT1=ASCII_TO_HEX(szCmd[2]);
wT2=ASCII_TO_HEX(szCmd[3]);
wAddr=wT1*16+wT2;

wT1=5; wT2=0;
for (;;)
    {
    if (szCmd[wT1]==0) break;
    szSend[wT2++]=szCmd[wT1++];
    }
szSend[wT2]=0;
}

/* -------------------------------------------------------------------- */

WORD ASCII_TO_HEX(char cChar)
{
if (cChar<='9') return(cChar-'0');
else if (cChar<='F') return(cChar-'A'+10);
else return(cChar-'a'+10);
}

/* -------------------------------------------------------------------- */

char  HEX_TO_ASCII(WORD wHex)
{
if (wHex<=9) return(wHex+'0');
else return(wHex-10+'A');
}

/* -------------------------------------------------------------------- */

WORD w7000[10];
float f7000[10];

void TEST_CMD(HWND hwnd, int x, int dx, int y, int dy)
{
char cBuf[80],cShow[80],cResult[80];
HDC hdc;
WORD wRet,i,j,wT;
char cData=8, cStop=0, cParity=0;
DWORD dwBaudRate=9600L;
WORD wCheckSum=1;	/* check-sum enable */
WORD wTimeOut=100;	/* default time-out constant=100 */

iLine=0;
hdc=GetDC(hwnd);
HideCaret(hwnd);
SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));

sprintf(cShow,"------- cPort=%d wAddr=%d szSend=[%s] ---------------------",cPort,wAddr,szSend);
TextOut(hdc,x*dx,(y+iLine)*dy,cShow,strlen(cShow)); iLine++;

wRet=Open_Com(cPort,dwBaudRate,cData,cParity,cStop);
if (wRet!=NoError)
   {
   sprintf(cShow,"0. Open Error, return code=%d",wRet);
   TextOut(hdc,x*dx,(y+iLine)*dy,cShow,strlen(cShow)); iLine++;
   goto ret_label;
   }

// ------------------- multi-task driver demo ------------------------
i=wAddr/16;
j=wAddr-i*16;
cBuf[0]='$';
cBuf[1]=HEX_TO_ASCII(i);
cBuf[2]=HEX_TO_ASCII(j);
cBuf[3]='M';
cBuf[4]=0;
wRet = Send_Cmd(cPort,cBuf,1000,wCheckSum); /* time-out = 1000 ms = 1 sec */
   if (wRet!=NoError)
   {
       sprintf(cShow,"1. Send_Cmd error, return code=%d",wRet);
       TextOut(hdc,x*dx,(y+iLine)*dy,cShow,strlen(cShow)); iLine++;
       goto ret_label;
   }

    cResult[0]=0;
    wRet=Receive_Cmd(cPort, cResult, 1000, &wT);

sprintf(cShow,"1. wRet=%x, Send=%s, receive=%s, wT=%d",wRet,cBuf,cResult,wT);
TextOut(hdc,x*dx,(y+iLine)*dy,cShow,strlen(cShow)); iLine++;

// ------------------- Non-multi-task driver demo ------------------------

cBuf[4]=0;
wRet = Send_Receive_Cmd(cPort,cBuf,cResult,wTimeOut,wCheckSum,&wT);
sprintf(cShow,"2. wRet=%d, Send=%s, receive=%s, wT=%d",wRet,cBuf,cResult,wT);
TextOut(hdc,x*dx,(y+iLine)*dy,cShow,strlen(cShow)); iLine++;

cBuf[3]='2';
cBuf[4]=0;
wRet = Send_Receive_Cmd(cPort,cBuf,cResult,wTimeOut,wCheckSum,&wT);
sprintf(cShow,"3. wRet=%d, Send=%s, receive=%s, wT=%d",wRet,cBuf,cResult,wT);
TextOut(hdc,x*dx,(y+iLine)*dy,cShow,strlen(cShow)); iLine++;

cBuf[3]='F';
cBuf[4]=0;
wRet = Send_Receive_Cmd(cPort,cBuf,cResult,wTimeOut,wCheckSum,&wT);
sprintf(cShow,"4. wRet=%d, Send=%s, receive=%s, wT=%d",wRet,cBuf,cResult,wT);
TextOut(hdc,x*dx,(y+iLine)*dy,cShow,strlen(cShow)); iLine++;

wRet = Send_Receive_Cmd(cPort,szSend,cResult,wTimeOut,wCheckSum,&wT);
sprintf(cShow,"5. wRet=%d, Send=%s, receive=%s, wT=%d",wRet,szSend,cResult,wT);
TextOut(hdc,x*dx,(y+iLine)*dy,cShow,strlen(cShow)); iLine++;

ret_label:
wRet=Close_Com(cPort);
if (wRet!=NoError)
   {
   sprintf(cShow,"5. Close Error, return code=%d",wRet);
   TextOut(hdc,x*dx,(y+iLine)*dy,cShow,strlen(cShow)); iLine++;
   }

sprintf(cShow,"------- key-in new cPort,wAddr,szSend if need ----------");
TextOut(hdc,x*dx,(y+iLine)*dy,cShow,strlen(cShow)); iLine++;

ShowCaret(hwnd);
ReleaseDC (hwnd,hdc);
}