/* **************************************************************************
 File Name	: 	dev.h
 Description:	EN672A - Device Driver
 Designer	:	YoungKyu, Jang
 Modifier	:	16. 5. 30
 Copyright Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
//#ifndef __DEV_H__
//#define __DEV_H__

#include "spr_defs.h"


/*
 INDEX	:
		 1. TYPE DEF
		 2. Memory Size & Base Address Definition
		 3. IRQ Number Def
		 4. SYSTEM
		 5. UTIL
		 6. ADC
		 7. CPU
		 8. DDR
		 9. DMA
		10. GPIO
		11. ISR
		12. SERIAL FLASH (ISP)
		13. TIMER
		14. ETHERNET (IP Only)
		15. H.264 (IP Only)
		16. SDIO (IP Only)
		17. I2C
		18. AUD
		19. SPI
		20. UART
		21. UTIL
		23. USB
*/


//*************************************************************************************************
// 1. TYPE DEF
//-------------------------------------------------------------------------------------------------
#define	_regs_					typedef	union{ULONG a; struct{	// Register union start
#define	_rege_					}b;}							// Register union end
#define	_am(uon,base,addr)		((volatile uon*)(UINT*)(base+(addr)))->a		// All macro
#define	_bm(uon,base,addr,mne)	((volatile uon*)(UINT*)(base+(addr)))->b.mne	// Bit macro

//-------------------------------------------------------------------------------------------------
// Type definition

typedef int						INT;		// 16 bit or 32 bit according to system
typedef unsigned int			UINT;		//	"
typedef unsigned int			uint;		//	"
typedef char					CHAR;		// 8 bit
typedef unsigned char			UCHAR;		//	"
typedef unsigned char			BYTE;		//	"
typedef unsigned char			BOOL;		//	"
typedef unsigned char			INT8U;		//	"
typedef signed	 char			INT8S;		//	"
typedef signed   char			int8;		//	"
typedef unsigned char			uint8;		//	"
typedef unsigned char			u_int8;		//	"
typedef volatile uint8			vuint8;		//	"
typedef short					SHORT;		// 16 bit
typedef unsigned short			USHORT;		//	"
typedef unsigned short			WORD;		//	"
typedef unsigned short			WCHAR;		//	"
typedef unsigned short			INT16U;		//	"
typedef signed	 short			INT16S;		//	"
typedef signed   short			int16;		//	"
typedef unsigned short			uint16;		//	"
typedef unsigned short	    	u_int16;	//	"
typedef volatile uint16			vuint16;	//	"
typedef long					LONG;		// 32 bit
typedef unsigned long			ULONG;		//	"
typedef unsigned long			DWORD;		//	"
typedef unsigned long			INT32U;		//	"
typedef signed   long			INT32S;		//	"
typedef signed   long			int32;		//	"
typedef unsigned long			u32;		//	"
typedef unsigned long			uint32;		//	"
typedef unsigned long			u_int32;	//	"
typedef volatile uint32			vuint32;	//	"
typedef	long long				LLONG;		// 64 bit
typedef	unsigned long long		ULLONG;		//	"
typedef unsigned long long		INT64U;		//	"
typedef signed	 long long		INT64S;		//	"
typedef signed   long long		int64;		//	"
typedef unsigned long long		uint64;		//	"

typedef unsigned int 			float32;
typedef unsigned long long 		float64;
//*************************************************************************************************
// 2. Memory Size & Base Address Definition
//-------------------------------------------------------------------------------------------------
// Mem size
#define DDR_SIZE				(64*1024*1024)
#define RAM0_SIZE				(     32*1024)	//	32kB (Local)


// Base address
#define DDR_BASE				0x08000000	//	OK
#define DDR_BK0_BASE			0x08000000	//	OK
#define DDR_BK1_BASE			0x09000000	//	OK
#define DDR_BK2_BASE			0x0a000000	//	OK
#define DDR_BK3_BASE			0x0b000000	//	OK
#define RAM_BASE				0x04000000	//	OK


// Reg address
#define	DMA_REG_BASE			0xf1000000	//	CPU  OK
#define UART_REG_BASE			0xf8000000	//	CPU  OK
#define GPIO_REG_BASE			0xf8300000	//	CPU  OK
#define DDR_REG_BASE			0xf9300000	//	CPU  OK


#define TRUE					1
#define FALSE					0

#define CLK_VALUE (27.00 * (7.4))	// 199.8MHz

#define BUS_CLK					(CLK_VALUE * 1000000)
#define UART0BAUD			(115200)


//-------------------------------------------------------------------------------------------------
// Macro
#define MAX_INT_HANDLERS	21		// Number of interrupt handlers

struct tIhnd {						// Handler entry
	void 	(*handler)(void *);
	void	*arg;
};


#define DIt(ID)	const UINT nSPR_SR_##ID = mfspr(SPR_SR);		/* Don't Use Groble Variable !!!*/\
				mtspr(SPR_SR, nSPR_SR_##ID & ~(SPR_SR_IEE | SPR_SR_TEE))

#define EIt(ID)	mtspr(SPR_SR, nSPR_SR_##ID)


#define DI()	DIt()

#define EI()	EIt()

//*************************************************************************************************
// 5. UTIL
//-------------------------------------------------------------------------------------------------
// LMA information
extern const UINT _lma_size;
extern const UINT _lma_start;
extern const UINT _reset_lma_s;
extern const UINT _reset_lma_e;
extern const UINT _text_lma_s;
extern const UINT _text_lma_e;
extern const UINT _ispm_text_lma_s;
extern const UINT _ispm_text_lma_e;
extern const UINT _data_lma_s;
extern const UINT _data_lma_e;

// VMA information
extern const UINT _reset_s;
extern const UINT _reset_e;
extern const UINT _text_s;
extern const UINT _text_e;
extern const UINT _ispm_text_s;
extern const UINT _ispm_text_e;
extern const UINT _data_s;
extern const UINT _data_e;
extern const UINT _bss_s;
extern const UINT _bss_e;
extern const UINT _stack;

extern void _DataSectInit(void);
extern void _BssSectInit(void);
extern void _ResetSectInit(void);
extern void mtspr(UINT anSpr, UINT anVal);
extern UINT mfspr(UINT anSpr);
extern void WaitXus(UINT anUs);
extern void WaitXms(UINT anMs);
extern void MemCpy(BYTE * dst, BYTE * src, UINT len);
extern void call(UINT addr);
extern void PrintHex(BYTE * Dat, UINT Len);
//*************************************************************************************************
// 8. DDR
//-------------------------------------------------------------------------------------------------
_regs_	UINT REF_EN			: 1;
		UINT ZQCS_EN		: 1;
		UINT ZQCS_LMT		: 18;
		UINT REF_LMT		: 12;	_rege_  _DDR_LEF;

_regs_	UINT MR_REQ			: 1;
		UINT _res			: 9;
		UINT MR_CTL			: 2;
		UINT MR_CMD			: 20;	_rege_  _DDR_CTL0;

_regs_	UINT _res0			: 4;
		UINT T_MR			: 4;
		UINT _res1			: 12;
		UINT DCK_INV		: 1;
		UINT RD_LTC			: 3;
		UINT RD_EDGE		: 1;
		UINT WR_DQLTC		: 3;
		UINT WR_DQSLTC		: 3;
		UINT _res2			: 1;	_rege_  _DDR_CTL1;

_regs_	UINT _res			: 4;
		UINT T_RP			: 4;
		UINT T_WR			: 4;
		UINT T_WTR			: 4;
		UINT T_RTP			: 4;
		UINT T_RTW			: 4;
		UINT T_RCD			: 4;
		UINT T_RRD			: 4;	_rege_  _DDR_TIM0;

_regs_	UINT _res0			: 2;
		UINT T_ZQCS			: 6;
		UINT T_FAW			: 6;
		UINT T_RFC			: 6;
		UINT T_RC			: 6;
		UINT T_RAS			: 6;	_rege_  _DDR_TIM1;

_regs_	UINT DLY7			: 4;
		UINT DLY6			: 4;
		UINT DLY5			: 4;
		UINT DLY4			: 4;
		UINT DLY3			: 4;
		UINT DLY2			: 4;
		UINT DLY1			: 4;
		UINT DLY0			: 4;	_rege_  _DDR_DLYCTL;

#define	DDR_REF_EN		_bm(_DDR_LEF		, DDR_REG_BASE, 0x00, REF_EN		)	//	RW
#define	DDR_ZQCS_EN		_bm(_DDR_LEF		, DDR_REG_BASE, 0x00, ZQCS_EN		)	//	RW
#define	DDR_ZQCS_LMT	_bm(_DDR_LEF		, DDR_REG_BASE, 0x00, ZQCS_LMT		)	//	RW
#define	DDR_REF_LMT		_bm(_DDR_LEF		, DDR_REG_BASE, 0x00, REF_LMT		)	//	RW
#define	DDR_MR_REQ		_bm(_DDR_CTL0		, DDR_REG_BASE, 0x04, MR_REQ		)	//	RW
#define	DDR_MR_CTL		_bm(_DDR_CTL0		, DDR_REG_BASE, 0x04, MR_CTL		)	//	RW
#define	DDR_MR_CMD		_bm(_DDR_CTL0		, DDR_REG_BASE, 0x04, MR_CMD		)	//	RW
#define	DDR_MR			_am(_DDR_CTL0		, DDR_REG_BASE, 0x04				)	//	RW
#define DDR_T_MR		_bm(_DDR_CTL1		, DDR_REG_BASE, 0x08, T_MR			)	//	RW
#define	DDR_DCK_INV		_bm(_DDR_CTL1		, DDR_REG_BASE, 0x08, DCK_INV		)	//	RW
#define	DDR_RD_LTC		_bm(_DDR_CTL1		, DDR_REG_BASE, 0x08, RD_LTC		)	//	RW
#define	DDR_RD_EDGE		_bm(_DDR_CTL1		, DDR_REG_BASE, 0x08, RD_EDGE		)	//	RW
#define	DDR_WR_DQLTC	_bm(_DDR_CTL1		, DDR_REG_BASE, 0x08, WR_DQLTC		)	//	RW
#define	DDR_WR_DQSLTC	_bm(_DDR_CTL1		, DDR_REG_BASE, 0x08, WR_DQSLTC		)	//	RW
#define DDR_T_RP		_bm(_DDR_TIM0		, DDR_REG_BASE, 0x0c, T_RP	        )	//	RW
#define DDR_T_WR		_bm(_DDR_TIM0		, DDR_REG_BASE, 0x0c, T_WR	        )	//	RW
#define DDR_T_WTR		_bm(_DDR_TIM0		, DDR_REG_BASE, 0x0c, T_WTR			)	//	RW
#define DDR_T_RTP		_bm(_DDR_TIM0		, DDR_REG_BASE, 0x0c, T_RTP			)	//	RW
#define DDR_T_RTW		_bm(_DDR_TIM0		, DDR_REG_BASE, 0x0c, T_RTW			)	//	RW
#define DDR_T_RCD		_bm(_DDR_TIM0		, DDR_REG_BASE, 0x0c, T_RCD			)	//	RW
#define DDR_T_RRD		_bm(_DDR_TIM0		, DDR_REG_BASE, 0x0c, T_RRD			)	//	RW
#define DDR_T_ZQCS		_bm(_DDR_TIM1		, DDR_REG_BASE, 0x10, T_ZQCS		)	//	RW
#define DDR_T_FAW		_bm(_DDR_TIM1		, DDR_REG_BASE, 0x10, T_FAW			)	//	RW
#define DDR_T_RFC		_bm(_DDR_TIM1		, DDR_REG_BASE, 0x10, T_RFC			)	//	RW
#define DDR_T_RC		_bm(_DDR_TIM1		, DDR_REG_BASE, 0x10, T_RC			)	//	RW
#define DDR_T_RAS		_bm(_DDR_TIM1		, DDR_REG_BASE, 0x10, T_RAS			)	//	RW
#define DDR_DLY_DQSIN3	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x14, DLY7			)	//	RW 
#define DDR_DLY_DQSIN2	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x14, DLY6			)	//	RW
#define DDR_DLY_DQSIN1	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x14, DLY5			)	//	RW
#define DDR_DLY_DQSIN0	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x14, DLY4			)	//	RW
#define DDR_DLY_CAOUT9	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x14, DLY1			)	//	RW
#define DDR_DLY_CAOUT8	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x14, DLY0			)	//	RW
#define DDR_DLY_CAOUT7	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x18, DLY7			)	//	RW
#define DDR_DLY_CAOUT6	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x18, DLY6			)	//	RW
#define DDR_DLY_CAOUT5	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x18, DLY5			)	//	RW
#define DDR_DLY_CAOUT4	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x18, DLY4			)	//	RW
#define DDR_DLY_CAOUT3	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x18, DLY3			)	//	RW
#define DDR_DLY_CAOUT2	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x18, DLY2			)	//	RW
#define DDR_DLY_CAOUT1	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x18, DLY1			)	//	RW
#define DDR_DLY_CAOUT0	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x18, DLY0			)	//	RW
#define DDR_DLY_DQOUT31	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x1c, DLY7			)	//	RW
#define DDR_DLY_DQOUT30	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x1c, DLY6			)	//	RW
#define DDR_DLY_DQOUT29	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x1c, DLY5			)	//	RW
#define DDR_DLY_DQOUT28	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x1c, DLY4			)	//	RW
#define DDR_DLY_DQOUT27	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x1c, DLY3			)	//	RW
#define DDR_DLY_DQOUT26	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x1c, DLY2			)	//	RW
#define DDR_DLY_DQOUT25	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x1c, DLY1			)	//	RW
#define DDR_DLY_DQOUT24	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x1c, DLY0			)	//	RW
#define DDR_DLY_DQOUT23	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x20, DLY7			)	//	RW
#define DDR_DLY_DQOUT22	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x20, DLY6			)	//	RW
#define DDR_DLY_DQOUT21	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x20, DLY5			)	//	RW
#define DDR_DLY_DQOUT20	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x20, DLY4			)	//	RW
#define DDR_DLY_DQOUT19	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x20, DLY3			)	//	RW
#define DDR_DLY_DQOUT18	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x20, DLY2			)	//	RW
#define DDR_DLY_DQOUT17	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x20, DLY1			)	//	RW
#define DDR_DLY_DQOUT16	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x20, DLY0			)	//	RW
#define DDR_DLY_DQOUT15	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x24, DLY7			)	//	RW
#define DDR_DLY_DQOUT14	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x24, DLY6			)	//	RW
#define DDR_DLY_DQOUT13	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x24, DLY5			)	//	RW
#define DDR_DLY_DQOUT12	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x24, DLY4			)	//	RW
#define DDR_DLY_DQOUT11	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x24, DLY3			)	//	RW
#define DDR_DLY_DQOUT10	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x24, DLY2			)	//	RW
#define DDR_DLY_DQOUT09	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x24, DLY1			)	//	RW
#define DDR_DLY_DQOUT08	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x24, DLY0			)	//	RW
#define DDR_DLY_DQOUT07	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x28, DLY7			)	//	RW
#define DDR_DLY_DQOUT06	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x28, DLY6			)	//	RW
#define DDR_DLY_DQOUT05	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x28, DLY5			)	//	RW
#define DDR_DLY_DQOUT04	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x28, DLY4			)	//	RW
#define DDR_DLY_DQOUT03	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x28, DLY3			)	//	RW
#define DDR_DLY_DQOUT02	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x28, DLY2			)	//	RW
#define DDR_DLY_DQOUT01	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x28, DLY1			)	//	RW
#define DDR_DLY_DQOUT00	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x28, DLY0			)	//	RW
#define DDR_DLY_CSOUT	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x2c, DLY7			)	//	RW
#define DDR_DLY_DMOUT3	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x2c, DLY3			)	//	RW
#define DDR_DLY_DMOUT2	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x2c, DLY2			)	//	RW
#define DDR_DLY_DMOUT1	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x2c, DLY1			)	//	RW
#define DDR_DLY_DMOUT0	_bm(_DDR_DLYCTL		, DDR_REG_BASE, 0x2c, DLY0			)	//	RW

extern void DdrInit(void);
extern BOOL DdrChk(void);
extern BOOL DdrCmdCal(void);
extern BOOL DdrRdLtc(void);
extern BOOL DdrDqsOutDly(void);
extern BOOL DdrTest(void);
extern void DdrParamInsert(void);
extern void DdrParamBypass(void);
extern void DdrDqsInTest(void);  
extern void DdrClkOutTest(void);  
extern void DdrDqsOutTest(void);  
//*************************************************************************************************
// 9. DMA
//-------------------------------------------------------------------------------------------------
_regs_  UINT _res0			: 16;
		UINT VALUE			: 8;
		UINT _res1			: 1;
		UINT CHKSUM_CLR		: 1;
		UINT MODE			: 2;
		UINT IRQ			: 1;
		UINT IRQ_EN			: 1;
		UINT IRQ_CLR		: 1;
		UINT GO				: 1;    _rege_  _DMA_CONT;

_regs_								_rege_	_DMA_INT;
_regs_	UINT _res0			: 16;
		UINT CHKSUM			: 16;	_rege_	_DMA_CHKSUM;

#define DMA_VALUE		_bm(_DMA_CONT		, DMA_REG_BASE, 0x0000, VALUE		)	//RW
#define DMA_CHKSUM_CLR	_bm(_DMA_CONT		, DMA_REG_BASE, 0x0000, CHKSUM_CLR	)	//RW
#define DMA_MODE		_bm(_DMA_CONT		, DMA_REG_BASE, 0x0000, MODE		)	//RW
#define DMA_IRQ			_bm(_DMA_CONT		, DMA_REG_BASE, 0x0000, IRQ			)
#define DMA_IRQ_EN		_bm(_DMA_CONT		, DMA_REG_BASE, 0x0000, IRQ_EN		)	//RW
#define DMA_IRQ_CLR		_bm(_DMA_CONT		, DMA_REG_BASE, 0x0000, IRQ_CLR		)	//RW
#define DMA_GO			_bm(_DMA_CONT		, DMA_REG_BASE, 0x0000, GO			)	//RW
#define DMA_SRC			_am(_DMA_INT		, DMA_REG_BASE, 0x0004				)	//RW
#define DMA_DST			_am(_DMA_INT		, DMA_REG_BASE, 0x0008				)	//RW
#define DMA_LEN			_am(_DMA_INT		, DMA_REG_BASE, 0x000c				)	//RW
#define DMA_CHKSUM		_bm(_DMA_CHKSUM		, DMA_REG_BASE, 0x0010, CHKSUM		)	//RO
extern void DmaMemCpy(BYTE * dst, BYTE * src, UINT len);
extern void DmaMemSet(BYTE * dst, BYTE Value, UINT len);
extern WORD DmaChkSum(BYTE * src, UINT len);
//*************************************************************************************************
// 10. GPIO
//-------------------------------------------------------------------------------------------------
_regs_					_rege_  _GPIO;
#define	GPIO_I			_am(_GPIO , GPIO_REG_BASE, 0x00) 			//
#define	GPIO_O			_am(_GPIO , GPIO_REG_BASE, 0x04) 			//
#define	GPIO_OEN		_am(_GPIO , GPIO_REG_BASE, 0x08) 			//
#define	GPIO_EDGE_DIR	_am(_GPIO , GPIO_REG_BASE, 0x0c) 			//
#define	GPIO_IRQ_EN		_am(_GPIO , GPIO_REG_BASE, 0x10) 			//
#define	GPIO_IRQ_CLR	_am(_GPIO , GPIO_REG_BASE, 0x14) 			//
#define	GPIO_IRQ		_am(_GPIO , GPIO_REG_BASE, 0x18) 			//
#define	GPIO_PU_EN		_am(_GPIO , GPIO_REG_BASE, 0x1c) 			//
#define	GPIO_MUX		_am(_GPIO , GPIO_REG_BASE, 0x20) 			//

extern void GpioInit(void);
extern void GpioEi(BYTE abSel);
extern void GpioDi(BYTE abSel);
extern void GpioRiseEdge(BYTE abSel);
extern void GpioFallEdge(BYTE abSel);
extern void GpioOutDir(BYTE abSel);
extern void GpioInDir(BYTE abSel);
extern void GpioSetHi(BYTE abSel);
extern void GpioSetLo(BYTE abSel);
extern void GpioFuncPin(BYTE abSel);
extern void GpioFuncPinOff(BYTE abSel);
extern BYTE GpioGetPin(BYTE abSel);

//*************************************************************************************************
// 11. ISR
//-------------------------------------------------------------------------------------------------
extern int IntInit(void);
extern int IntAdd(UINT anVec, void (* handler)(void *), void *arg);
extern int IrqDisable(UINT anVec);
extern int IrqEnable(UINT anVec);
extern void XsrInt(void);
extern void XsrBusErr(void);
extern void XsrAlign(void);
extern void XsrIllInsn(void);
extern void XsrFloatPoint(void);
extern void XsrSyscall(void);
extern void XsrBreak(void);
extern void XsrTrap(void);
extern void XsrDpFault(void);
extern void XsrIpFault(void);
extern void XsrDtlbMiss(void);
extern void XsrItlbMiss(void);
extern void xsr_tick(void);


//*************************************************************************************************
// 20. UART
//-------------------------------------------------------------------------------------------------
_regs_	UINT CLKDIV		: 12;
		UINT _res		: 6;
		UINT TX_TYPE	: 1;
		UINT STOP_BIT	: 1;
		UINT PARITY_EN	: 1;
		UINT PARITY_TYPE: 1;
		UINT TX_IRQ		: 1;
		UINT TX_IRQ_EN	: 1;
		UINT TX_IRQ_CLR	: 1;
		UINT TX_EMPTY	: 1;
		UINT TX_FULL	: 1;
		UINT RX_IRQ		: 1;
		UINT RX_IRQ_EN	: 1;
		UINT RX_IRQ_CLR	: 1;
		UINT RX_EMPTY	: 1;
		UINT RX_FULL	: 1; _rege_  _UART_CONT;

_regs_	UINT _res		:16;
		UINT TX_DAT		: 8;
		UINT RX_DAT		: 8; _rege_  _UART_DAT;

//---------------------------------------- UART CH0 ----------------------------------------
#define	UART_CLKDIV			_bm(_UART_CONT, UART_REG_BASE, 0x00, CLKDIV			)	//	RW
#define UART_TX_TYPE		_bm(_UART_CONT, UART_REG_BASE, 0x00, TX_TYPE		)	//	RW
#define UART_STOP_BIT		_bm(_UART_CONT, UART_REG_BASE, 0x00, STOP_BIT		)	//	RW
#define UART_PARITY_EN		_bm(_UART_CONT, UART_REG_BASE, 0x00, PARITY_EN		)	//	RW
#define UART_PARITY_TYPE 	_bm(_UART_CONT, UART_REG_BASE, 0x00, PARITY_TYPE	)	//	RW
#define	UART_TX_IRQ			_bm(_UART_CONT, UART_REG_BASE, 0x00, TX_IRQ			)	//	RO
#define	UART_TX_IRQ_EN		_bm(_UART_CONT, UART_REG_BASE, 0x00, TX_IRQ_EN		)	//	RW
#define	UART_TX_IRQ_CLR		_bm(_UART_CONT, UART_REG_BASE, 0x00, TX_IRQ_CLR		)	//	WO
#define	UART_TX_EMPTY		_bm(_UART_CONT, UART_REG_BASE, 0x00, TX_EMPTY		)	//	RO
#define	UART_TX_FULL		_bm(_UART_CONT, UART_REG_BASE, 0x00, TX_FULL		)	//	RO
#define	UART_RX_IRQ			_bm(_UART_CONT, UART_REG_BASE, 0x00, RX_IRQ			)	//	RO
#define	UART_RX_IRQ_EN		_bm(_UART_CONT, UART_REG_BASE, 0x00, RX_IRQ_EN		)	//	RW
#define	UART_RX_IRQ_CLR		_bm(_UART_CONT, UART_REG_BASE, 0x00, RX_IRQ_CLR		)	//	WO
#define	UART_RX_EMPTY		_bm(_UART_CONT, UART_REG_BASE, 0x00, RX_EMPTY		)	//	RO
#define UART_RX_FULL		_bm(_UART_CONT, UART_REG_BASE, 0x00, RX_FULL		)	//	RO
#define	UART_TX_DAT			_bm(_UART_DAT , UART_REG_BASE, 0x04, TX_DAT			)	//	WO
#define	UART_RX_DAT			_bm(_UART_DAT , UART_REG_BASE, 0x04, RX_DAT			)	//	WO

extern void Uart_Init(void);
extern void Uart_Tx(char dat);
extern void Uart_Rx(char *dat);
extern void Uart_Str(const char *text);
extern void Uart_Strn(const char *text, int len);
extern void Uart_Num(char num);
extern void Uart_Hex(int data);
extern void Uart_Byte(BYTE data);
extern void Uart_Dec(unsigned char data);
extern void Uart_Printf(char * text, int dat);



extern int printf(const char *format, ...);
extern char* strcpy_(char * pDest,const char * pSrc);
extern UINT  strlen_(const char* apbStr);
extern char* strrev(char* str);
extern char* itoa(int value, char* str, int base, int* len);
extern int uitoan(uint value, char* str, int base, int width, char fill_val);
