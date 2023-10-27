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
