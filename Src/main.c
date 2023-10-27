/**
 * @file main.c
 * @author Parth Kharade (you@domain.com)
 * @brief 	Short program to illustrate functioning of inbuilt API in the Atmel AT89c51 microcontroller
 * @version 0.1
 * @date 2023-10-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "stdio.h"
#include "stdint.h"
#include "at89c51ed2.h"
#include "stdlib.h"
#include "serial.h"
#define CODE_LOC 0x3B00
#define PGM_MTP 0xFFF0
__sfr __at (0xA2) AUXR1 ;
void main(){
/************************HEADER START*******************************/
__code unsigned char __at (CODE_LOC) signature[4] = {0xA5,0xE5,0xE0,0xA5};                

__code unsigned char __at (CODE_LOC+4) id[4] = {35,255,0,0};

__code unsigned char __at (CODE_LOC+8) reserved1[4] = {0,0,0,0};

__code unsigned char __at (CODE_LOC+12) reserved2[4] = {0,0,0,0};

__code unsigned char __at (CODE_LOC+16) reserved3[4] = {0,0,0,0};

__code unsigned char __at (CODE_LOC+20) reserved4[4] = {0,0,0,0};

__code unsigned char __at (CODE_LOC+24) reserved5[4] = {0,0,0,0};

__code unsigned char __at (CODE_LOC+28) reserved6[4] = {255,255,255,255};

__code unsigned char __at (CODE_LOC+32) pname[] = "ISP-CALLS";

/************************HEADER END********************************/
	
	printf_tiny("\r\n Enter H to see a list of all available commands.");
	while(1){
		printf_tiny("\r\n >> ");
		char comm = getchar();
		putchar(comm);
		switch (comm)
		{
		case 'H':
			printf_tiny("\r\n ------------------------------------");
			printf_tiny("\r\n |            Help Menu             |");
			printf_tiny("\r\n |----------------------------------|");
			printf_tiny("\r\n |   H.  | Help Menu                |");
			printf_tiny("\r\n |----------------------------------|");
			printf_tiny("\r\n |   A.  | Read SBV                 |");
			printf_tiny("\r\n |----------------------------------|");
			printf_tiny("\r\n |   B.  | Read BSB                 |");
			printf_tiny("\r\n |----------------------------------|");
			printf_tiny("\r\n |   C.  | Read HSB                 |");
			printf_tiny("\r\n |----------------------------------|");
			printf_tiny("\r\n |   D.  | Read BOOT_ID1            |");	
			printf_tiny("\r\n |----------------------------------|");
			printf_tiny("\r\n |   E.  | Read BOOT_ID2            |");
			printf_tiny("\r\n |----------------------------------|");
			printf_tiny("\r\n |   F.  | Read Boot_V              |");
			printf_tiny("\r\n |----------------------------------|");
			printf_tiny("\r\n |   G.  | Prog Data Mem (0x6000)   |");														
			printf_tiny("\r\n ------------------------------------");
			break;
		case 'A':{
			AUXR1|=0x20;
			__asm
				mov r1, #0x07
				mov dpl,#0x02
				mov dph,#0x00
				lcall #PGM_MTP			
			__endasm;
			AUXR1&=0xDF;
			uint16_t SBV = ACC;
			printf_tiny("\r\n Value of SBV is : %x",SBV);
			break;
		}
		case 'B':{
			AUXR1|=0x20;
			__asm
				mov r1, #0x07
				mov dpl,#0x01
				mov dph,#0x00
				lcall #PGM_MTP			
			__endasm;
			AUXR1&=0xDF;
			uint16_t BSB = ACC;
			printf_tiny("\r\n Value of BSB is : %x",BSB);
			break;
		}
		case 'C':{
			AUXR1|=0x20;
			__asm
				mov r1, #0x0B
				lcall #PGM_MTP			
			__endasm;
			AUXR1&=0xDF;
			uint16_t HSB = ACC;
			printf_tiny("\r\n Value of HSB is : %x",HSB);
			break;
		}
		case 'D':{
			AUXR1|=0x20;
			__asm
				mov r1, #0x0E
				mov dpl,#0x00
				lcall #PGM_MTP			
			__endasm;
			AUXR1&=0xDF;
			uint16_t BID1 = ACC;
			printf_tiny("\r\n Value of Boot ID 1 is is : %x",BID1);
			break;
		}
		case 'E':{
			AUXR1|=0x20;
			__asm
				mov r1, #0x0E
				mov dpl,#0x01
				lcall #PGM_MTP			
			__endasm;
			AUXR1&=0xDF;
			uint16_t BID2 = ACC;
			printf_tiny("\r\n Value of Boot ID 2 is is : %x",BID2);
			break;
		}
		case 'F':{
			AUXR1|=0x20;
			__asm
				mov r1, #0x0F
				lcall #PGM_MTP			
			__endasm;
			AUXR1&=0xDF;
			uint16_t BV = ACC;
			printf_tiny("\r\n Value of Boot Version is : %x",BV);
			break;
		}
		case 'G':{
			printf_tiny("Enter the value to be written to 0x6000 :");
			uint16_t data_byte = 0;
			scan_num(&data_byte);
			ACC = (uint8_t)(data_byte&0xFF);
			AUXR1|=0x20;
			__asm
				mov r1, #0x02
				mov dpl, #0x00
				mov dph, #0x60
				lcall #PGM_MTP				
			__endasm;
			AUXR1&=0xDF;
			uint16_t RES = ACC;
			if(RES == 0)
				printf_tiny("\r\n Byte programmed successfully");
			else
				printf_tiny("\r\n Porgramming unsuccessful");
			break;
		}
		default:
			break;
		}
	}
}