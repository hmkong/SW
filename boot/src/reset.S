#include "spr_defs.h"
#define EXCEPTION_STACK_SIZE (256)

#define	ENTRY(symbol)					 \
	.global	symbol						;\
symbol:																			// $CMT-ygkim-150730: to define label
#define	WORD_ENTRY(symbol)				 \
	ENTRY(symbol)						;\
	.word	_##symbol															// $CMT-ygkim-150730: to define word label


		.extern XsrBusErr
        .extern XsrDpFault
        .extern XsrIpFault
        .extern xsr_tick
        .extern XsrAlign
        .extern XsrIllInsn
        .extern XsrInt
        .extern XsrDtlbMiss
        .extern XsrItlbMiss
        .extern XsrFloatPoint

				.extern	_enable_icache
				.extern	_enable_dcache

        .extern syscall_A
        .extern syscall_B
        .extern syscall_C
        .extern syscall_D
        .extern trapcall_A
        .extern XsrBreak
        .extern XsrTrap

		.extern	_ResetSectInit
		.extern	_DataSectInit
		.extern	_BssSectInit

        .extern cache_init

		.global _save_gpr
        .global _rest_gpr

//#############################################################################
		.section .reset, "ax"
//#############################################################################
// Code memory information for boot loader
	.org	0x000

// LMA information
		WORD_ENTRY(_lma_size		)
		WORD_ENTRY(_lma_start		)		// reserved
		WORD_ENTRY(_reset_lma_s		)
		WORD_ENTRY(_reset_lma_e		)
		WORD_ENTRY(_text_lma_s		)
		WORD_ENTRY(_text_lma_e		)
		WORD_ENTRY(_ispm_text_lma_s	)
		WORD_ENTRY(_ispm_text_lma_e	)
		WORD_ENTRY(_ispm_data_lma_s	)
		WORD_ENTRY(_ispm_data_lma_e	)
		WORD_ENTRY(_rodata_lma_s	)
		WORD_ENTRY(_rodata_lma_e	)
		WORD_ENTRY(_data_lma_s		)
		WORD_ENTRY(_data_lma_e		)

// VMA information
		WORD_ENTRY(_reset_s     	)
		WORD_ENTRY(_reset_e     	)
		WORD_ENTRY(_text_s      	)
		WORD_ENTRY(_text_e      	)
		WORD_ENTRY(_ispm_text_s 	)
		WORD_ENTRY(_ispm_text_e 	)
		WORD_ENTRY(_ispm_data_s 	)
		WORD_ENTRY(_ispm_data_e 	)
		WORD_ENTRY(_rodata_s      	)
		WORD_ENTRY(_rodata_e      	)
		WORD_ENTRY(_data_s      	)
		WORD_ENTRY(_data_e      	)
		WORD_ENTRY(_bss_s       	)
		WORD_ENTRY(_bss_e       	)
		WORD_ENTRY(_stack_s       	)
		WORD_ENTRY(_stack_e       	)

//-----------------------------------------------------------------------------
		.org	0x100
_reset:
        l.nop
	// Init ISR
//		l.andi	r0,r0, 0
//        l.nop
//        l.nop
//		l.andi	r1,r0, 0	// EXR1K_ISR_RDWE									// $CMT-ygkim-151109: added RDWE(default) for RF
//       l.nop
//        l.nop
//		l.mtspr r0,r1, EXR1K_ISR
//        l.nop
//        l.nop

        l.andi	r0,r0,0x0
        l.andi	r1,r0,0x0
		l.andi	r2,r0,0x0
		l.andi	r3,r0,0x0
		l.andi	r4,r0,0x0
		l.andi	r5,r0,0x0
		l.andi	r6,r0,0x0
		l.andi	r7,r0,0x0
		l.andi	r8,r0,0x0
		l.andi	r9,r0,0x0
		l.andi	r10,r0,0x0
		l.andi	r11,r0,0x0
		l.andi	r12,r0,0x0
		l.andi	r13,r0,0x0
		l.andi	r14,r0,0x0
		l.andi	r15,r0,0x0
		l.andi	r16,r0,0x0
		l.andi	r17,r0,0x0
		l.andi	r18,r0,0x0
		l.andi	r19,r0,0x0
		l.andi	r20,r0,0x0
		l.andi	r21,r0,0x0
		l.andi	r22,r0,0x0
		l.andi	r23,r0,0x0
		l.andi	r24,r0,0x0
		l.andi	r25,r0,0x0
		l.andi	r26,r0,0x0
		l.andi	r27,r0,0x0
		l.andi	r28,r0,0x0
		l.andi	r29,r0,0x0
		l.andi	r30,r0,0x0
		l.andi	r31,r0,0x0

		l.movhi	r3,hi(_init_hw)					// Jump to "_init_hw"
		l.ori	r3,r3,lo(_init_hw)				//		"
		l.jr	r3								//		"
		l.nop									//		"


//#############################################################################
// Exception handler
//-----------------------------------------------------------------------------
// Macro
#define PROLOG                          ;\
    l.addi  r1,r1,-EXCEPTION_STACK_SIZE ;\
    l.sw    0x04(r1),r3                 ;\
    l.sw    0x1c(r1),r9                 ;\
                                        ;\
    l.movhi r3,hi(_save_gpr)            ;\
    l.ori   r3,r3,lo(_save_gpr)         ;\
    l.jalr  r3                          ;\
    l.nop                               ;\
    l.movhi r3,hi(__except_stack)       ;\
    l.ori   r3,r3,lo(__except_stack)    ;\
    l.sw    0x00(r3),r1                 ;\
    l.addi  r3,r3,-4                    ;\
    l.addi  r1,r3,0                     ;\

#define ISR_PROLOG                      ;\
    l.addi  r1,r1,-EXCEPTION_STACK_SIZE ;\
    l.sw    0x04(r1),r3                 ;\
    l.sw    0x1c(r1),r9                 ;\
                                        ;\
    l.movhi r3,hi(_save_gpr)            ;\
    l.ori   r3,r3,lo(_save_gpr)         ;\
    l.jalr  r3                          ;\
    l.nop                               ;\
    l.movhi r3,hi(__isr_stack)          ;\
    l.ori   r3,r3,lo(__isr_stack)       ;\
    l.sw    0x00(r3),r1                 ;\
    l.addi  r3,r3,-4                    ;\
    l.addi  r1,r3,0                     ;\


#define CALL(func)                      ;\
    l.movhi r3,hi(func)                 ;\
    l.ori   r3,r3,lo(func)              ;\
    l.jalr  r3                          ;\
    l.nop                               ;

#define EPILOG                          ;\
    l.movhi r3,hi(__except_stack)       ;\
    l.ori   r3,r3,lo(__except_stack)    ;\
    l.lwz   r1,0x0(r3)                  ;\
                                        ;\
    l.movhi r3,hi(_rest_gpr)            ;\
    l.ori   r3,r3,lo(_rest_gpr)         ;\
    l.jalr  r3                          ;\
    l.nop                               ;\
                                        ;\
    l.lwz   r3,0x04(r1)                 ;\
    l.lwz   r9,0x1c(r1)                 ;\
    l.addi  r1,r1,EXCEPTION_STACK_SIZE  ;\
    l.rfe                               ;\
    l.nop                               ;

#define ISR_EPILOG                      ;\
    l.movhi r3,hi(__isr_stack)          ;\
    l.ori   r3,r3,lo(__isr_stack)       ;\
    l.lwz   r1,0x0(r3)                  ;\
                                        ;\
    l.movhi r3,hi(_rest_gpr)            ;\
    l.ori   r3,r3,lo(_rest_gpr)         ;\
    l.jalr  r3                          ;\
    l.nop                               ;\
                                        ;\
    l.lwz   r3,0x04(r1)                 ;\
    l.lwz   r9,0x1c(r1)                 ;\
    l.addi  r1,r1,EXCEPTION_STACK_SIZE  ;\
    l.rfe                               ;\
    l.nop                               ;

//-----------------------------------------------------------------------------
        .org 0x200
_buserr_vector:
    PROLOG
    CALL(XsrBusErr)
    EPILOG

//-----------------------------------------------------------------------------
        .org 0x300
_dpfault_vector:
    PROLOG
    CALL(XsrDpFault)
    EPILOG

//-----------------------------------------------------------------------------
        .org 0x400
_ipfault_vector:
    PROLOG
    CALL(XsrIpFault)
    EPILOG

//-----------------------------------------------------------------------------
        .org 0x500
_lpint_vector:
    PROLOG
    CALL(xsr_tick)
    EPILOG

//-----------------------------------------------------------------------------
        .org 0x600
_align_vector:
    PROLOG
    CALL(XsrAlign)
    EPILOG

//-----------------------------------------------------------------------------
        .org 0x700
_illinsn_vector:
    PROLOG
    CALL(XsrIllInsn)
    EPILOG

//-----------------------------------------------------------------------------
        .org 0x800
_hpint_vector:
    ISR_PROLOG
    CALL(XsrInt)
    ISR_EPILOG

//-----------------------------------------------------------------------------
        .org 0x900
_dtlbmiss_vector:
    PROLOG
    CALL(XsrDtlbMiss)
    EPILOG


//-----------------------------------------------------------------------------
        .org 0xa00
_itlbmiss_vector:
    PROLOG
    //CALL(boot_itlb_miss_handler)
    EPILOG

//-----------------------------------------------------------------------------
        .org 0xb00
_float_vector:
    PROLOG
    CALL(XsrFloatPoint)
    EPILOG

//-----------------------------------------------------------------------------
        .org 0xc00
_syscall_vector:
//	l.trap	0
    PROLOG
    CALL(syscall_A)
    EPILOG

//-----------------------------------------------------------------------------
        .org 0xd00
_break_vector:
    PROLOG
    CALL(XsrBreak)
    EPILOG

//-----------------------------------------------------------------------------
        .org 0xe00
_trap_vector:
		PROLOG
//		CALL(XsrTrap)
		CALL(trapcall_A)
		EPILOG

//-----------------------------------------------------------------------------
_save_gpr:
    l.sw    0x00(r1),r2
    l.sw    0x08(r1),r4
    l.sw    0x0c(r1),r5
    l.sw    0x10(r1),r6
    l.sw    0x14(r1),r7
    l.sw    0x18(r1),r8
    l.sw    0x20(r1),r10
    l.sw    0x24(r1),r11
    l.sw    0x28(r1),r12
    l.sw    0x2c(r1),r13
    l.sw    0x30(r1),r14
    l.sw    0x34(r1),r15
    l.sw    0x38(r1),r16
    l.sw    0x3c(r1),r17
    l.sw    0x40(r1),r18
    l.sw    0x44(r1),r19
    l.sw    0x48(r1),r20
    l.sw    0x4c(r1),r21
    l.sw    0x50(r1),r22
    l.sw    0x54(r1),r23
    l.sw    0x58(r1),r24
    l.sw    0x5c(r1),r25
    l.sw    0x60(r1),r26
    l.sw    0x64(r1),r27
    l.sw    0x68(r1),r28
    l.sw    0x6c(r1),r29
    l.sw    0x70(r1),r30
    l.sw    0x74(r1),r31
    l.jr    r9
    l.nop

_rest_gpr:
    l.lwz   r31,0x74(r1)
    l.lwz   r30,0x70(r1)
    l.lwz   r29,0x6C(r1)
    l.lwz   r28,0x68(r1)
    l.lwz   r27,0x64(r1)
    l.lwz   r26,0x60(r1)
    l.lwz   r25,0x5C(r1)
    l.lwz   r24,0x58(r1)
    l.lwz   r23,0x54(r1)
    l.lwz   r22,0x50(r1)
    l.lwz   r21,0x4C(r1)
    l.lwz   r20,0x48(r1)
    l.lwz   r19,0x44(r1)
    l.lwz   r18,0x40(r1)
    l.lwz   r17,0x3C(r1)
    l.lwz   r16,0x38(r1)
    l.lwz   r15,0x34(r1)
    l.lwz   r14,0x30(r1)
    l.lwz   r13,0x2C(r1)
    l.lwz   r12,0x28(r1)
    l.lwz   r11,0x24(r1)
    l.lwz   r10,0x20(r1)
    l.lwz   r8 ,0x18(r1)
    l.lwz   r7 ,0x14(r1)
    l.lwz   r6 ,0x10(r1)
    l.lwz   r5 ,0x0C(r1)
    l.lwz   r4 ,0x08(r1)
    l.lwz   r2 ,0x00(r1)
    l.jr    r9
    l.nop



//#############################################################################
		.section .text
//#############################################################################
_init_hw:

//-----------------------------------------------------------------------------
// Stack pointer(R1)
	l.movhi	r1,hi(__stack)
	l.ori	r1,r1,lo(__stack)

//-----------------------------------------------------------------------------
// SR
    l.addi  r10,r0,(SPR_SR_SM|SPR_SR_EPH)
    l.mtspr r0,r10, SPR_SR
    l.nop
    l.nop

// Init cache
		CALL(_enable_icache)
		CALL(_enable_dcache)

//-----------------------------------------------------------------------------
// Ram init
//	CALL(_ResetSectInit)		// .reset section initilize
//	CALL(_DataSectInit)			// .data section initilize
	CALL(_BssSectInit)			// .bss section initilize

//-----------------------------------------------------------------------------
// PIC mask
/*_pic_init:
    l.movhi r3,(0x0000)
    l.ori   r3,r3,(0x0000)
    l.mtspr r0,r3,SPR_PICMR*/

//-----------------------------------------------------------------------------
// Jump to "_main"
	l.movhi	r2,hi(main)
	l.ori	r2,r2,lo(main)
	l.jr    r2
	l.addi	r2,r0,0

//******************************************************************************
// Code Dummy: Only for EXR1K
//------------------------------------------------------------------------------
		.section .reset_dummy, "ax"
_reset_dummy_code:
		FILL_NOPS_1CACHE_LINE

		.section .text_dummy, "ax"
_text_dummy_code:
		FILL_NOPS_1CACHE_LINE