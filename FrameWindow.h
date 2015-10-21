#ifndef _FRAMEWINDOW_
#define _FRAMEWINDOW_

#include "dcomm.h"
#include <stdio.h>
#include "crc16.h"

//Bentuk data | SOH=1 byte | FRAME NUMBER = 1 byte | STX = 1 byte | DATA =  | ETX = 1 byte | CHECKSUM = 2 byte |
class FrameWindow{
private:
	char FrameNumber; // id of frame
	char* data; //data in the frame
	int length; // length of frame
	bool checksum;// boolean code for checksum
public:
	FrameWindow(char numFrame,char* adata){
		checksum = true;
		FrameNumber = numFrame;

		//Encapsulate SOH, STX, and ETX
		char x= SOH + '0';
		char y= STX +'0';
		char z= ETX + '0';
		data[0]= x;
		data[1]= numFrame;
		data[2]= y;

		//counting the length of data and encapsulate to frame
		int i=0;
		while( adata[i] != '\0'){
			data[3+i] = adata[i];
			++i;
		}
		int datalength = i;

		data[4+i] = z;

		//Create crc code
		unsigned short crccode= calc_crc16(data);
		char o= (crccode & 0xFF00) >> 8; // get the MSB from crc code
		char p= crccode & 0xFF; // get the LSB from crc code

		data[i+5]= o;
		data[i+6]= p;
		length = i+6;
	}
	
};
#endif
