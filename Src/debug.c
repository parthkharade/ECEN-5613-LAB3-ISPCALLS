/**
 * @file debug.c
 * @author Parth Kharade (you@domain.com)
 * @brief Implements ta virutal debug port
 * @version 0.1
 * @date 2023-10-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "debug.h"
#include "8051.h"
void mark_location(uint8_t val){

	ACC = val;
	__asm
		mov dpl,#0xa0
		mov dph,#0xa0
		movx @dptr,a
	__endasm;

}
