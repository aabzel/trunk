#ifndef FC7300_CAN_REGISTERS_TYPE_H
#define FC7300_CAN_REGISTERS_TYPE_H

#include "std_includes.h"


/*
CAN master control register (CAN_MCR)
Address offset: 0x00
Reset value: 0x0001 0002
 */
typedef union  {
    volatile uint32_t dword;
    struct {
        volatile uint32_t INRQ : 1; /*Bit 0 INRQ: Initialization request*/
        volatile uint32_t SLEEP: 1;  /*Bit 1 SLEEP: Sleep mode request*/
        volatile uint32_t TXFP: 1;  /*Bit 2 TXFP: Transmit FIFO priority*/
        volatile uint32_t RFLM: 1;  /*Bit 3 RFLM: Receive FIFO locked mode*/
        volatile uint32_t NART: 1;  /*Bit 4 NART: No automatic retransmission*/
        volatile uint32_t AWUM: 1;  /*Bit 5 AWUM: Automatic wake-up mode*/
        volatile uint32_t ABOM: 1;  /*Bit 6 ABOM: Automatic bus-off management*/
        volatile uint32_t TTCM: 1;  /*Bit 7 TTCM: Time triggered communication mode*/
        volatile uint32_t RES1: 7;  /*Reserved*/
        volatile uint32_t RESET: 1;  /*Bit 15 RESET: bxCAN software master reset*/
        volatile uint32_t DBF: 1;  /*Bit 16 DBF: Debug freeze*/
        volatile uint32_t RES2: 15;  /*Bits 31:17 Reserved, must be kept at reset value.*/
    } ;
} CanReg_MCR_t;



/*
CAN bit timing register (CAN_BTR) offset: 0x1C Reset value: 0x0123 0000
This register can only be accessed by the software when the CAN hardware is in
initialization mode.
 */
typedef union  {
    uint32_t dword;
    struct {
        uint32_t BRP : 10; /*Bits 9:0 BRP[9:0]: Baud rate prescaler*/
        uint32_t RES1: 6;  /*Reserved*/
        uint32_t TS1 : 4;  /*Bits 19:16 TS1[3:0]: Time segment 1*/
        uint32_t TS2 : 3;  /*Bits 22:20 TS2[2:0]: Time segment 2*/
        uint32_t RES2 : 1; /*Reserved*/
        uint32_t SJW : 2;  /*Bits 25:24 SJW[1:0]: Resynchronization jump width*/
        uint32_t RES3 : 4; /*Reserved*/
        uint32_t LBKM : 1; /*Bit 30 LBKM: Loop back mode (debug)*/
        uint32_t SILM : 1; /*Bit 31 SILM: Silent mode (debug)*/
    } ;
} CanReg_BTR_t;



/*
Filter bank i register x (CAN_FiRx) (i=0..27, x=1, 2) Address offsets: 0x240..0x31C
There are 28 filter banks, i=0 .. 27. Each filter bank i is composed of two 32-bit registers,
CAN_FiR[2:1].
This register can only be modified when the FACTx bit of the CAN_FAxR register is cleared
or when the FINIT bit of the CAN_FMR register is set.
 */
typedef union  {
    uint32_t dword;
    uint32_t identifier;
    uint32_t mask;
} CanReg_FxR0_t;


/*
Filter bank i register x (CAN_FiRx) (i=0..27, x=1, 2)
Address offsets: 0x240..0x31C
Reset value: 0xXXXX XXXX
There are 28 filter banks, i=0 .. 27. Each filter bank i is composed of two 32-bit registers,
CAN_FiR[2:1].
This register can only be modified when the FACTx bit of the CAN_FAxR register is cleared
or when the FINIT bit of the CAN_FMR register is set.
 */
typedef union  {
    uint32_t dword;
    uint32_t identifier;
    uint32_t mask;
} CanReg_FxR1_t;




/*
CAN master status register (CAN_MSR) Address offset: 0x04 Reset value: 0x0000 0C02
 */
typedef union  {
    uint32_t dword;
    struct {
        uint32_t INAK : 1;  /*Initialization acknowledge*/
        uint32_t SLAK: 1;   /*Sleep acknowledge*/
        uint32_t ERRI : 1;  /*Error interrupt*/
        uint32_t WKUI : 1;  /*Wake-up interrupt*/
        uint32_t SLAKI : 1; /*Sleep acknowledge interrupt*/
        uint32_t RES1 : 3;  /**/
        uint32_t TXM : 1;   /*Transmit mode*/
        uint32_t RXM : 1;   /*Receive mode*/
        uint32_t SAMP : 1;  /*Last sample point*/
        uint32_t RX : 1;    /*CAN Rx signal*/
        uint32_t RES2: 20;  /**/
    } ;
} CanReg_MSR_t;



/*
CAN transmit status register (CAN_TSR)
Address offset: 0x08
Reset value: 0x1C00 0000
 */
typedef union  {
    uint32_t dword;
    struct {
        uint32_t RQCP0 : 1;  /* Bit 0 RQCP0: Request completed mailbox0*/
        uint32_t TXOK0 : 1;  /* Bit 1 TXOK0: Transmission OK of mailbox0*/
        uint32_t ALST0 : 1;  /* Bit 2 ALST0: Arbitration lost for mailbox0*/
        uint32_t TERR0 : 1;  /* Bit 3 TERR0: Transmission error of mailbox0*/
        uint32_t RES1 : 3;    /* Bits 6:4 Reserved, must be kept at reset value.*/
        uint32_t ABRQ0 : 1;  /* Bit 7 ABRQ0: Abort request for mailbox0*/
        uint32_t RQCP1 : 1;  /* Bit 8 RQCP1: Request completed mailbox1*/
        uint32_t TXOK1 : 1;  /* Bit 9 TXOK1: Transmission OK of mailbox1*/
        uint32_t ALST1 : 1;  /* Bit 10 ALST1: Arbitration lost for mailbox1*/
        uint32_t TERR1 : 1;  /* Bit 11 TERR1: Transmission error of mailbox1*/
        uint32_t RES2 : 3;    /* Bits 14:12 Reserved, must be kept at reset value.*/
        uint32_t ABRQ1 : 1;  /* Bit 15 ABRQ1: Abort request for mailbox 1*/
        uint32_t RQCP2 : 1;  /* Bit 16 RQCP2: Request completed mailbox2*/
        uint32_t TXOK2 : 1;  /* Bit 17 TXOK2: Transmission OK of mailbox 2*/
        uint32_t ALST2 : 1;  /* Bit 18 ALST2: Arbitration lost for mailbox 2*/
        uint32_t TERR2 : 1;  /* Bit 19 TERR2: Transmission error of mailbox 2*/
        uint32_t RES3: 3;     /* Bits 22:20 Reserved, must be kept at reset value.*/
        uint32_t ABRQ2: 1;   /* Bit 23 ABRQ2: Abort request for mailbox 2*/
        uint32_t CODE: 2;    /* Bits 25:24 CODE[1:0]: Mailbox code*/
        uint32_t TME0: 1;    /* Bit 26 TME0: Transmit mailbox 0 empty*/
        uint32_t TME1: 1;    /* Bit 27 TME1: Transmit mailbox 1 empty*/
        uint32_t TME2: 1;    /* Bit 28 TME2: Transmit mailbox 2 empty*/
        uint32_t LOW0: 1;    /* Bit 29 LOW0: Lowest priority flag for mailbox 0*/
        uint32_t LOW1: 1;    /* Bit 30 LOW1: Lowest priority flag for mailbox 1 */
        uint32_t LOW2: 1;    /* Bit 31 LOW2: Lowest priority flag for mailbox 2*/
    } ;
} CanReg_TSR_t;




/*
CAN error status register (CAN_ESR)
Address offset: 0x18
Reset value: 0x0000 0000
 */
typedef union  {
    uint32_t dword;
    struct {
        uint32_t EWGF : 1;  /* Error warning flag */
        uint32_t EPVF : 1;  /* Error passive flag */
        uint32_t BOFF : 1;  /* Bus-off flag */
        uint32_t RES1 : 1;  /*   */
        uint32_t LEC : 3;  /* Last error code */
        uint32_t RES2 : 9;  /*   */
        uint32_t TEC : 8;  /* Least significant byte of the 9-bit transmit error counter */
        uint32_t REC : 8;  /* Receive error counter */
    } ;
} CanReg_ESR_t;




/*
CAN interrupt enable register (CAN_IER)
Address offset: 0x14
Reset value: 0x0000 0000
 */
typedef union  {
    uint32_t dword;
    struct {
        uint32_t TMEIE : 1;  /* Transmit mailbox empty interrupt enable */
        uint32_t FMPIE0 : 1;  /*  FIFO message pending interrupt enable */
        uint32_t FFIE0 : 1;  /*  FIFO full interrupt enable */
        uint32_t FOVIE0 : 1;  /*  FIFO overrun interrupt enable */
        uint32_t FMPIE1 : 1;  /*  FIFO message pending interrupt enable */
        uint32_t FFIE1 : 1;  /*  FIFO full interrupt enable */
        uint32_t FOVIE1 : 1;  /* FIFO overrun interrupt enable */
        uint32_t RES1 : 1;  /* ddddddddddddddddddddd */
        uint32_t EWGIE : 1;  /* Error warning interrupt enable */
        uint32_t EPVIE : 1;  /* : Error passive interrupt enable */
        uint32_t BOFIE : 1;  /*  Bus-off interrupt enable */
        uint32_t LECIE : 1;  /* Last error code interrupt enable */
        uint32_t RES2 : 3;  /* ddddddddddddddddddddd */
        uint32_t ERRIE : 1;  /* Error interrupt enable */
        uint32_t WKUIE : 1;  /* Wake-up interrupt enable */
        uint32_t SLKIE : 1;  /* Sleep interrupt enable */
        uint32_t RES3 : 14;  /* ddddddddddddddddddddd */
    } ;
} CanReg_IER_t;



/*
CAN TX mailbox identifier register (CAN_TIxR) (x=0..2)
Address offsets: 0x180, 0x190, 0x1A0
Reset value: 0xXXXX XXXX (except bit 0, TXRQ = 0)
*/
typedef union  {
    uint32_t dword;
    struct {
        uint32_t TXRQ : 1;  /* Bit 0 Transmit mailbox request */
        uint32_t RTR: 1;  /* Bit 1 Remote transmission request */
        uint32_t IDE: 1;  /* Identifier extension */
        uint32_t EXID_17_0: 18;  /* EXID[17:0]: Extended identifier */
        uint32_t STID_EXT_28_18: 11;  /* STID[10:0]/EXID[28:18]: Standard identifier or extended identifier */
    } ;
} CanReg_TIxR_t;


/*
CAN mailbox data length control and time stamp register (CAN_TDTxR) (x=0..2)
All bits of this register are write protected when the mailbox is not in empty state.
Address offsets: 0x184, 0x194,
*/
typedef union  {
    uint32_t dword;
    struct {
        uint32_t DLC : 4;  /* Bits 3:0 DLC[3:0]: Data length code */
        uint32_t RES1 : 4;  /* Bits 7:4 */
        uint32_t TGT : 1;  /* Bit 8 Transmit global time */
        uint32_t RES2 : 7;  /*  Bits 15:9 Reserved */
        uint32_t TIME : 16;  /* Bits 31:16 TIME[15:0]: Message time stamp */
    } ;
} CanReg_TDTxR_t;



/*
CAN mailbox data low register (CAN_TDLxR) (x=0..2)
All bits of this register are write protected when the mailbox is not in empty state.
Address offsets: 0x188, 0x198, 0x1A8
Reset value: 0xXXXX XXXX
*/
typedef union  {
    uint32_t dword;
    struct {
        uint8_t DATA0 ;  /* Bits 7:0 DATA0[7:0]: Data byte 0 */
        uint8_t DATA1 ;  /* Bits 15:8 DATA1[7:0]: Data byte 1 */
        uint8_t DATA2 ;  /* Bits 23:16 DATA2[7:0]: Data byte 2 */
        uint8_t DATA3 ;  /* Bits 31:24 DATA3[7:0]: Data byte 3 */
    } ;
} CanReg_TDLxR_t;


/*
CAN mailbox data high register (CAN_TDHxR) (x=0..2)
All bits of this register are write protected when the mailbox is not in empty state.
Address offsets: 0x18C, 0x19C, 0x1AC
Reset value: 0xXXXX XXXX
*/
typedef union  {
    uint32_t dword;
    struct {
        uint8_t DATA4 ;  /* Bits 7:0 DATA4[7:0]: Data byte 4 */
        uint8_t DATA5 ;  /* Bits 15:8 DATA5[7:0]: Data byte 5 */
        uint8_t DATA6 ;  /* Bits 23:16 DATA6[7:0]: Data byte 6 */
        uint8_t DATA7 ;  /* Bits 31:24 DATA7[7:0]: Data byte 7 */
    } ;
} CanReg_TDHxR_t;


/*
CAN receive FIFO  register (CAN_RFxR)
CAN receive FIFO 0 register (CAN_RF0R)
CAN receive FIFO 1 register (CAN_RF1R)
*/
typedef union  {
    uint32_t dword;
    struct {
        uint32_t FMP  :2;  /* Bits 1:0 FMPx[1:0]: FIFO  message pending */
        uint32_t RES1  :1;  /* ssssss */
        uint32_t FULL  :1;  /* Bit 3 FULLx: FIFO  full */
        uint32_t FOVR  :1;  /* Bit 4 FOVRx: FIFO  overrun */
        uint32_t RFOM  :1;  /* Bit 5 RFOMx: Release FIFO  output mailbox */
        uint32_t RES2  :26;  /* Bits 31:6 Reserved, must be kept at reset value */
    } ;
} CanReg_RFxR_t;




/*
CAN filter activation register (CAN_FA1R)
Address offset: 0x21C
Reset value: 0x0000 0000
 */
typedef union  {
    uint32_t dword;
    struct {
        uint32_t FACT0 : 1; /*1: Filter x is active 0: Filter x is not active*/
        uint32_t FACT1 : 1; /**/
        uint32_t FACT2 : 1; /**/
        uint32_t FACT3 : 1; /**/
        uint32_t FACT4 : 1; /**/
        uint32_t FACT5 : 1; /**/
        uint32_t FACT6 : 1; /**/
        uint32_t FACT7 : 1; /**/
        uint32_t FACT8 : 1; /**/
        uint32_t FACT9 : 1; /**/
        uint32_t FACT10 :1; /**/
        uint32_t FACT11 :1; /**/
        uint32_t FACT12 :1; /**/
        uint32_t FACT13 :1; /**/
        uint32_t FACT14 :1; /**/
        uint32_t FACT15 :1; /**/
        uint32_t FACT16 :1; /**/
        uint32_t FACT17 :1; /**/
        uint32_t FACT18 :1; /**/
        uint32_t FACT19 :1; /**/
        uint32_t FACT20 :1; /**/
        uint32_t FACT21 :1; /**/
        uint32_t FACT22 :1; /**/
        uint32_t FACT23 :1; /**/
        uint32_t FACT24 :1; /**/
        uint32_t FACT25 :1; /**/
        uint32_t FACT26 :1; /**/
        uint32_t FACT27 :1; /*FFA27*/
        uint32_t RES: 4; /**/
    } ;
} CanReg_FA1R_t;


/*
 */
typedef union  {
    uint32_t dword;
    struct {
        uint32_t ZERO:1; /**/
        uint32_t RTR:1; /*0-need*/
        uint32_t IDE:1; /*1-Ext ID  0-StdID*/
        uint32_t RES1:29; /**/
    };
    struct {
        uint32_t RES2:3; /**/
        uint32_t EXT_ID:29; /**/
    };
    struct {
        uint32_t RES3:21; /**/
        uint32_t STD_ID:11; /**/
    };
} CanRegFilter32Bit_t;

#if 0
typedef union  {
    uint32_t dword;
    struct {
        uint32_t ZERO:1; /**/
        uint32_t RTR:1; /*0-need*/
        uint32_t IDE:1; /*1-Ext ID  0-StdID*/
        uint32_t EXT_ID:29; /**/
    };
} CanRegFilter32ExtBit_t;

typedef union  {
    uint32_t dword;
    struct {
        uint32_t ZERO:1; /**/
        uint32_t RTR:1; /*0-need*/
        uint32_t IDE:1; /*1-Ext ID  0-StdID*/
        uint32_t RES:18; /**/
        uint32_t STD_ID:11; /**/
    };
} CanRegFilter32StdBit_t;

#endif

/*Two 16-Bit Filters - Identifier Mask*/
typedef union  {
    uint16_t word;
    struct {
        uint16_t EXT_ID_15_17:3; /**/
        uint16_t IDE:1; /*1-Ext ID  0-StdID*/
        uint16_t RTR:1; /*0-need*/
        uint16_t STD:11; /**/
    };
} CanRegFilter16Bit_t;

typedef struct  {
    CanRegFilter16Bit_t FltID;
    CanRegFilter16Bit_t FltMask;
} CanRegFilter16DoubleIdMaskBit_t;

typedef struct  {
    CanRegFilter16Bit_t ID12;
    CanRegFilter16Bit_t ID34;
} CanRegFilter16QuadIdBit_t;





#endif /* FC7300_CAN_REGISTERS_TYPE_H  */
