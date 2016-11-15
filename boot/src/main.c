#include "boot_dev.h"

// Debug stop register
#define EXR1K_DSR_RSTE				0x00000001  // [0] Reset exception 
#define EXR1K_DSR_BUSEE				0x00000002  // [1] Bus error exception 
#define EXR1K_DSR_DPFE				0x00000004  // [2] Data Page Fault exception 
#define EXR1K_DSR_IPFE				0x00000008  // [3] Insn Page Fault exception 
#define EXR1K_DSR_TTE				0x00000010  // [4] Tick Timer exception 
#define EXR1K_DSR_AE				0x00000020  // [5] Alignment exception 
#define EXR1K_DSR_IIE				0x00000040  // [6] Illegal Instruction exception 
#define EXR1K_DSR_IE				0x00000080  // [7] Interrupt exception 
#define EXR1K_DSR_DME				0x00000100  // [8] DTLB miss exception 
#define EXR1K_DSR_IME				0x00000200  // [9] ITLB miss exception 
#define EXR1K_DSR_RE				0x00000400  // [10] Range exception 
#define EXR1K_DSR_SCE				0x00000800  // [11] System call exception 
#define EXR1K_DSR_FPE     			0x00001000  // [12] Floating Point Exception 
#define EXR1K_DSR_TE				0x00002000  // [13] Trap exception
#define	EXR1K_DSR_TET				0x00004000	// [14] Ticktimer Exception Trace Enable: If SR[TEE],ESR[TEE] disable incorrectly, stall CPU
#define	EXR1K_DSR_IET				0x00008000	// [15] Interrupt Exception Trace Enable: If SR[IEE],ESR[TEE] disable incorrectly, stall CPU
#define	EXR1K_DSR_MET				0x00010000	// [16] Multiple Exception Trace

#define EXR1K_SPRRID_W 				11
#define EXR1K_SPRGID_DU				( 6<< EXR1K_SPRRID_W)
#define EXR1K_DSR					(EXR1K_SPRGID_DU + 20)

#define	EXR1K_SPRGID_TB				(14<< EXR1K_SPRRID_W)

#define EXR1K_HTBCR 					(EXR1K_SPRGID_TB + 0x700)			// TB: Control register

// TB control register
#define EXR1K_HTBCR_EN	  		0x00000001  // [0] Enable
#define	EXR1K_HTBCR_NE				0x00000002	// [1] NOP enable 
#define	EXR1K_HTBCR_TE				0x00000004	// [2] Timestamp enable

// Process control
#define TRAP	asm("l.trap 0");												// $CMT-ygkim-151007: stop. DO NOT use in XSR bcz CPU will be halted!!
#define BREAK	{ enable_jtag_ctrl_exception(); asm("l.trap 0");	}			// $CMT-ygkim-150824: stop and transfer control to JTAG. DO NOT use in XSR!!

#define sys_call(v) asm volatile("l.sys\t%0": : "n"(v));
	
// exception stops the core and turn over control to JTAG
#define _NOINS
_NOINS void enable_jtag_ctrl_exception(void)
{
  	mtspr(EXR1K_DSR,	 EXR1K_DSR_RSTE	 	// [0] Reset exception                
					//	|EXR1K_DSR_BUSEE	// [1] Bus error exception            
						|EXR1K_DSR_DPFE		// [2] Data Page Fault exception      
						|EXR1K_DSR_IPFE		// [3] Insn Page Fault exception      
					//	|EXR1K_DSR_TTE		// [4] Tick Timer exception           	// Used @CPU
						|EXR1K_DSR_AE		// [5] Alignment exception            
						|EXR1K_DSR_IIE		// [6] Illegal Instruction exception  
					//	|EXR1K_DSR_IE		// [7] Interrupt exception            	// Used @CPU
						|EXR1K_DSR_DME		// [8] DTLB miss exception            
						|EXR1K_DSR_IME		// [9] ITLB miss exception            
					//	|EXR1K_DSR_RE		// [10] Range exception               
					//	|EXR1K_DSR_SCE		// [11] System call exception         	// Used @CPU
						|EXR1K_DSR_FPE   	// [12] Floating Point Exception      
					//	|EXR1K_DSR_TE	  	// [13] Trap exception  				
					);	  	

	//TRACE("DSR: %x \r\n",mfspr(EXR1K_DSR));
}

_NOINS void disable_jtag_ctrl_exception(void)
{
	mtspr(EXR1K_DSR,0);
}

void syscall_A(void)
{
	UINT *epcr = (UINT *) mfspr(SPR_EPCR_BASE);
	epcr--;
	
	switch((*epcr) & 0x0000FFFF){		// System Call Instruction Value
		case 0x01	:	printf("Syscall : 0x01\n"); break;
		case 0x02	:	printf("Syscall : 0x02\n"); break;
		case 0x03	:	printf("Syscall : 0x03\n"); break;
		case 0x04	:	printf("Syscall : 0x04\n"); break;
		default		:	printf("Syscall : anything else\n"); break;
	}
}

void trapcall_A(void)
{
	UINT *epcr = (UINT *) mfspr(SPR_EPCR_BASE);
	
	mtspr(SPR_EPCR_BASE, ++epcr);
}

int A[] = {0, 1, 2, 3, 4, 5, 6, 7};
int B[] = {10, 11, 12, 13, 14, 15, 16, 17};

int proc(int *a, int *b){
	TRAP
	int sum = 0;
	int i;
	for(i=0; i<8; i++){
		int val_a = *a;
		int val_b = *b;
		sum += val_a * val_b;
		a++; b++;
	}
	return sum;
}

int main(void)
{
	
	mtspr(EXR1K_HTBCR,	 EXR1K_HTBCR_EN 	// HTB enable
						|EXR1K_HTBCR_NE							// NOP enable
						|EXR1K_HTBCR_TE	);					// Timestamp enable: Enable Free running counter
	enable_jtag_ctrl_exception();
	Uart_Init();
	
	printf("\nCPU START\n");

	printf("Scalar Product Sum = %d\n", proc(A, B));
	
	return 0;
}