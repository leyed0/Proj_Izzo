// ReadFreqDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "I87000.h"
#include "I7000.h"

int main(int argc, char* argv[])
{
	int ret,wRtn ;
	short port;
	unsigned long w7000[32];
	float f7000[32];
	long baudrate;
	char szSend[32],szReceive[32];
	port =1;
	baudrate = 115200;

  printf("Get DLL Version %04X\n",Get_Dll_Version());

  ret=Open_Com(port,baudrate,8,0,0);
  if (ret)
  {
	  printf("Open Comport error code %d\n",ret);
	  exit(0);
  }

 

  while(1)
  {
	
	w7000[0] = (short) port ; // COM Port
	w7000[1] = 0x1;//(Word) StrToInt( "0x" + Address->Text ); // Module Address
	w7000[2] = 0x87082 ; // Module ID
	w7000[3] = 0 ;
	w7000[4] = 200; // TimeOut = 0.1 second
	w7000[5] = 0; // Channel No.
	w7000[6] = 1; // string debug
	//w7000[7] = 0;


	ret = ReadFreq(w7000 , f7000, szSend , szReceive);
	if ( ret != 0 )
	{
		
		Close_Com (port);
	}
	else
		printf("Freq = %ld\r",w7000[9]);

  }




	return 0;
}
