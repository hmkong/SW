#include "exr1k_sprs.h"
#include "exr1k_asm.h"

ENTRY(proc)
	l.addi  r1,r1,-20			// dec stack
	l.sw    0(r1),r3			// save gprs
	l.sw    4(r1),r4
	l.sw    8(r1),r5
	l.sw    12(r1),r6
	l.sw	16(r1),r7
	l.andi	r5, r0, 0x00

loop_proc:
	l.add r6, r3, r5
	l.add r7, r4, r5 
	l.lwz r6, 0x0(r6)
	l.lwz r7, 0x0(r7)

	l.sfnei r5, 0x1C
	l.mac r6,r7
	l.bf loop_proc
	l.addi r5, r5, 0x04
	l.macrc r11

end_proc:
    l.lwz   r7,16(r1)		
    l.lwz   r6,12(r1)		
    l.lwz   r5,8(r1)		
    l.lwz   r4,4(r1)		
    l.lwz   r3,0(r1)			// restore gprs
    l.addi  r1,r1,20			// inc stack
    
    l.jr r9
    l.nop 0