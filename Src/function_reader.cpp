#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <inttypes.h>
using namespace std;

/* ... */
int main(){


// Open serial port
HANDLE serialHandle;

 serialHandle = CreateFileA("\\\\.\\COM4",              	  //port name
                      GENERIC_READ | GENERIC_WRITE,			 //Read/Write
                      0,                           			 // No Sharing
                      NULL,                        			 // No Security
                      OPEN_EXISTING,						// Open existing port only
                      0,           							 // Non Overlapped I/O
                      NULL);       							 // Null for Comm Devices

  if (serialHandle == INVALID_HANDLE_VALUE)
      printf("Error in opening serial port");
  else
      printf("opening serial port successful\n\n");

  //CloseHandle(hComm);//Closing the Serial Port

// Do some basic settings
DCB serialParams = { 0 };
serialParams.DCBlength = sizeof(serialParams);

GetCommState(serialHandle, &serialParams);
serialParams.BaudRate = 115200;
        serialParams.ByteSize = 8;
        serialParams.StopBits = ONESTOPBIT;
        serialParams.Parity = NOPARITY;
SetCommState(serialHandle, &serialParams);

// Set timeouts
COMMTIMEOUTS timeout = { 0 };
timeout.ReadIntervalTimeout = 50;
timeout.ReadTotalTimeoutConstant = 50;
timeout.ReadTotalTimeoutMultiplier = 50;
timeout.WriteTotalTimeoutConstant = 50;
timeout.WriteTotalTimeoutMultiplier = 10;

SetCommTimeouts(serialHandle, &timeout);
	
	 
	uint8_t buff[2];
	ReadFile(serialHandle, &buff, 2, NULL, NULL);
	uint8_t last = buff[0];
	bool done=true;
		
	while(1){
		ReadFile(serialHandle, &buff, 2, NULL, NULL);

		if(buff[0]!=last) {
			last=buff[0];
			done=0;
	}
	
		
		if(!done){
		
			if(last=='3'){
				system("Start https://jsos.pwr.edu.pl/");
				done=1;
			}	
			
			if(last=='4'){
				system("Start https://m.meteo.pl/");
				done=1;
			}
			
			if(last=='5'){
				system("Start https://open.spotify.com/track/6Uv0QLfMnAteF6KT0Fltbn?si=5b6ba4a78d15433f");
				done=1;
			}
		}
				
	}
		

CloseHandle(serialHandle);
 
return 0;
}
