/******************************************************************************
//	Copyright(c) Eyenix Co.,Ltd. 2003-
//
//	File Name:		mem.ld
//	Description:	
//	Author:			YoungKyu Jang
//					Young-Geun Kim (ygkim@{eyenix.com;rcv.kaist.ac.kr}) Eyenix Co.,Ltd.
//
//	Note:	
//
//	Ver Date		Author		Changes
//	--- ----		------		-------
//	0.1	140924		ykjang		first designed
//	0.1	150425		ygkim		revised
// -----------------------------------------------------------------------------*/
MEMORY
		{
			RAM     : ORIGIN = 0x04000000, LENGTH = (32*1024)					/* RAM0_SIZE */
			DDR     : ORIGIN = 0x08000000, LENGTH = (64*1024*1024)					/* DDR_SIZE */
		}

/* stack and heap size */
isr_stack_size 		= 1024;
except_stack_size 	= 1024;
stack_size 			= 1024;
heap_size			= 256;

/* stack area at the end of SRAM */
__isr_stack_s		= ORIGIN(RAM) + LENGTH(RAM);
__isr_stack_e 		= __isr_stack_s - isr_stack_size;

__except_stack_s	= __isr_stack_e;
__except_stack_e	= __except_stack_s - except_stack_size;

__stack_s			= __except_stack_e;
__stack_e			= __stack_s - stack_size;

__isr_stack			= __isr_stack_s - 4;
__except_stack		= __except_stack_s - 4;
__stack				= __stack_s - 4;


/*******************************************************************************
// Output sections
//----------------------------------------------------------------------------*/
SECTIONS
{
		.reset :
		{
			. = ALIGN(4);
			__reset_s = .;
			*(.reset)
			*(.reset_dummy)
			. = ALIGN(4);
			__reset_e = .;
		} > RAM

		__reset_lma_s = LOADADDR(.reset);
		__reset_lma_e = ( (LOADADDR(.reset) + SIZEOF(.reset) + 3) & ~ (4-1) );

    .rodata : AT ( (LOADADDR (.reset) + SIZEOF(.reset) + 31) & ~ (32-1))
    	{
    		. = ALIGN(32);
    		__rodata_s = .;
    		*(.rodata)				/* constants, strings */
    		*(.rodata.*)			/* constants, strings */
    		. = ALIGN(32);
    		__rodata_e = .;
    	} > RAM
    
    __rodata_lma_s = LOADADDR(.rodata);
		__rodata_lma_e = ( (LOADADDR(.rodata) + SIZEOF(.rodata) + 31) & ~ (32-1) );
    
		.text : AT ( (LOADADDR (.rodata) + SIZEOF(.rodata) + 3) & ~ (4 - 1))
		{
			. = ALIGN(4);
			__text_s = ALIGN(4);
			*(.text)
			*(.text_dummy)
			*(.rodata)
			*(.rodata.*)
			. = ALIGN(4);
			__text_e = ALIGN(4);
		} > RAM

		__text_lma_s = LOADADDR(.text);
		__text_lma_e = ( (LOADADDR(.text) + SIZEOF(.text) + 3) & ~ (4-1) );
	
		.ispm_text : AT ( (LOADADDR (.text) + SIZEOF(.text) + 31) & ~ (32-1))
		{
			. = ALIGN(32);
			__ispm_text_s = .;
			*(.ispmtext)
			*(.ispm_text_dummy)
			. = ALIGN(32);
			__ispm_text_e = .;
		} > RAM
	
		__ispm_text_lma_s = LOADADDR(.ispm_text);
		__ispm_text_lma_e = ( (LOADADDR(.ispm_text) + SIZEOF(.ispm_text) + 31) & ~ (32-1) );
	
		.ispm_data : AT ( (LOADADDR (.ispm_text) + SIZEOF(.ispm_text) + 31) & ~ (32-1))
		{
			. = ALIGN(32);
			__ispm_data_s = .;
			*(.ispmdata)
			. = ALIGN(32);
			__ispm_data_e = .;
		} > RAM
	
		__ispm_data_lma_s = LOADADDR(.ispm_data);
		__ispm_data_lma_e = ( (LOADADDR(.ispm_data) + SIZEOF(.ispm_data) + 31) & ~ (32-1) );

		.data : AT ( (LOADADDR(.ispm_data) + SIZEOF(.ispm_data) + 3) & ~ (4-1) )
		{
			. = ALIGN(4);
			__data_s = ALIGN(4);
			*(.data)
			*(.data.rel)
			*(.data.rel.local)
			*(.sdata)
			__data_e = ALIGN(4);
			. = ALIGN(4);
		} > RAM

		__data_lma_s = LOADADDR(.data);
		__data_lma_e = ( (LOADADDR(.data) + SIZEOF(.data) + 3) & ~ (4-1) );

		__lma_size = ( (LOADADDR(.data) + SIZEOF(.data) + 31) & ~ (32-1) ) - LOADADDR(.reset);
		__lma_start = 0;	/* reserved */

		.bss (NOLOAD) :
		{
			. = ALIGN(4);
			__bss_s = ALIGN(4);
			*(.bss) *(COMMON)
			__bss_e = ALIGN(4);
			. = ALIGN(4);
		} > RAM

}

