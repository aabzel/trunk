#ifndef FC7300_CAN_REGISTERS_TYPE_H
#define FC7300_CAN_REGISTERS_TYPE_H

#include "std_includes.h"

typedef union {
    uint32_t bitwise;
    struct {
        uint32_t :1;
        uint32_t ERRINT :1;
        uint32_t BOFFINT :1;
        uint32_t RX :1;
        uint32_t FLTCONF :2;
        uint32_t TX :1;
        uint32_t IDLE :1;
        uint32_t RXWRN :1;
        uint32_t TXWRN :1;
        uint32_t STFERR :1;
        uint32_t FRMERR :1;
        uint32_t CRCERR :1;
        uint32_t ACKERR :1;
        uint32_t BIT0ERR :1;
        uint32_t BIT1ERR :1;
        uint32_t RWRNINT :1;
        uint32_t TWRNINT :1;
        uint32_t SYNCH :1;
        uint32_t BOFFDONEINT :1;
        uint32_t ERRINT_FAST :1;
        uint32_t ERROVR :1;
        uint32_t :4;
        uint32_t STFERR_FAST :1;
        uint32_t FRMERR_FAST :1;
        uint32_t CRCERR_FAST :1;
        uint32_t :1;
        uint32_t BIT0ERR_FAST :1;
        uint32_t BIT1ERR_FAST :1;
    };
} CAN_ESR1_TypeDef;

/*
  58.8.1 FLEXCAN_MCR (Module Configuration Register)
 */
typedef union {
    uint32_t dword;
    struct {
        uint32_t MAXMB:7; /*6-0 Number Of The Last Message Buffer */
        uint32_t RES1:1; /*7  */
        uint32_t IDAM:2; /*9-8  ID Acceptance Mode*/
        uint32_t RES2:1; /*10  */
        uint32_t FDEN:1; /*11  CAN FD Operation Enable*/
        uint32_t AEN:1; /* 12 Abort Enable*/
        uint32_t LPRIO_EN:1; /*13  Local Priority Enable*/
        uint32_t PNET_EN:1; /*14  Pretended Networking Enable*/
        uint32_t DMA:1; /*15  DMA Enable*/
        uint32_t IRMQ:1; /*16 Individual Rx Masking And Queue Enable */
        uint32_t SRXDIS:1; /*17  Self Reception Disable*/
        uint32_t RES3:2; /*19-18  */
        uint32_t LPMACK:1; /*20 Low-Power Mode Acknowledge */
        uint32_t WRNEN:1; /*21 Warning Interrupt Enable */
        uint32_t RES4:1; /*22  */
        uint32_t SUPV:1; /*23 Supervisor Mode */
        uint32_t FRZACK:1; /*24 Freeze Mode Acknowledge */
        uint32_t SOFT_RST:1; /*25 Soft Reset */
        uint32_t RES5:1; /*26  */
        uint32_t NOTRDY:1; /*27 FLEXCAN Not Ready */
        uint32_t HALT:1; /*28 Halt FLEXCAN */
        uint32_t RFEN:1; /*29 Legacy Rx FIFO Enable  */
        uint32_t FRZ:1; /*30 Freeze Enable */
        uint32_t MDIS:1; /* bit:31 Module Disable */
    };
}CanRegMCR_t;

typedef union {
    uint32_t dword;
    struct {
        uint32_t PROPSEG  : 3;  /* 2-0 Propagation Segment    */
        uint32_t LOM      : 1;  /* 3 Listen-Only Mode   */
        uint32_t LBUF     : 1;  /* 4 Lowest Buffer Transmitted First   */
        uint32_t TSYN     : 1;  /* 5 Timer Sync   */
        uint32_t BOFFREC  : 1;  /* 6 Bus Off Recovery   */
        uint32_t SMP      : 1;  /* 7 CAN Bit Sampling   */
        uint32_t RES      : 2;  /* 9-8 CAN   */
        uint32_t RWRNMSK  : 1;  /* 10 Rx Warning Interrupt Mask   */
        uint32_t TWRNMSK  : 1;  /* 11 Tx Warning Interrupt Mask   */
        uint32_t LPB      : 1;  /* 12 Loop Back Mode   */
        uint32_t CLKSRC   : 1;  /* 13 CAN Engine Clock Source   */
        uint32_t ERRMSK   : 1;  /* 14 Error Interrupt Mask   */
        uint32_t BOFFMSK  : 1;  /* 15 Bus Off Interrupt Mask   */
        uint32_t PSEG2    : 3;  /* 18-16 Phase Segment 2   */
        uint32_t PSEG1    : 3;  /* 21-19 Phase Segment 1   */
        uint32_t RJW      : 2;  /* 23-22 Resync Jump Width   */
        uint32_t PRESDIV  : 8;  /* 31-24 Prescaler Division Factor   */
    };
} CanRegCTRL1_t;


/*
58.8.11 FLEXCAN_CTRL2 (Control 2 Register)/
 */
typedef union {
    uint32_t dword; /** Full 32-bit register access */
    struct {
        uint32_t RES1: 11;  /** Bits 10:0   Reserved bits*/
        uint32_t EDFLTDIS: 1;  /** Bit 11 Edge Filter Disable*/
        uint32_t ISO_CAN_FD_EN: 1; /** Bit 12 ISO CAN FD Enable*/
        uint32_t BTE    : 1;  /** Bit 13 Bit Timing Expansion enable*/
        uint32_t PREXCEN     : 1;  /** Bit 14 Protocol Exception Enable*/
        uint32_t RES2     : 1;  /** Bit 15 */
        uint32_t EACE   : 1;  /** Bit 16 Entire Frame Arbitration Field Comparison Enable For Rx Mailboxes*/
        uint32_t RRS    : 1;  /** Bit 17 Remote Request Storing*/
        uint32_t MRP    : 1;  /** Bit 18 Mailboxes Reception Priority*/
        uint32_t TASD   : 5;  /** Bits 23:19 Tx Arbitration Start Delay*/
        uint32_t RFFN   : 4;  /** Bits 27:24 Number Of Rx FIFO Filters */
        uint32_t WRMFRZ   : 1;  /** Bit 28 Write-Access To Memory In Freeze Mode*/
        uint32_t ECRWRE   : 1;  /** Bit 29 Error-correction Configuration Register Write Enable*/
        uint32_t BOFF_DONE_MSK   : 1;  /** Bit 30 Bus Off Done Interrupt Mask*/
        uint32_t ERRM   : 1;  /** Bit 31  Error Interrupt Mask for errors detected in the data phase of fast CAN FD frames*/
    } ;
} CanRegCTRL2_t;



/*
58.8.3 FLEXCAN_TIMER (Free Running Timer Register)
  */
typedef union  {
    uint32_t dword; /* Full 32-bit register access */
    struct {
        uint32_t TIMER   : 16;  /*Timer Value  Contains the free-running counter value.*/
        uint32_t RES      :16;  /*res */
    } ;
} CanRegTIMER_t;


/*
  58.8.16 FLEXCAN_CBT (CAN Bit Timing Register)
  */
typedef union  {
    uint32_t dword; /* Full 32-bit register access */
    struct {
        uint32_t EPSEG2   : 5;  /*4-0 Extended Phase Segment 2 */
        uint32_t EPSEG1   : 5;  /*9-5 Extended Phase Segment 1 */
        uint32_t EPROPSEG : 6;  /*15-10 Extended Propagation Segment */
        uint32_t ERJW     : 5;  /*20-16 Extended Resync Jump Width */
        uint32_t EPRESDIV : 10; /*30-21 Extended Prescaler Division Factor*/
        uint32_t BTF      : 1;  /*31 Bit Timing Format Enable */
    } ;
} CanRegCBT_t;

/*  58.8.41 FLEXCAN_EPRS (Enhanced CAN Bit Timing Prescalers Register  */
typedef union  {
    uint32_t dword; /* Full 32-bit register access */
    struct {
        uint32_t ENPRESDIV   : 10;  /* 9-0   */
        uint32_t RES1   : 6;        /* 15-10   */
        uint32_t EDPRESDIV   : 10;  /*  25-16 */
        uint32_t RES2   : 6;        /* 31-26   */
    } ;
} CanRegEPRS_t;



/*
58.8.10 FLEXCAN_IFLAG1 (Interrupt Flags 1 Register)
  */
typedef union  {
    uint32_t dword;  /* Full 32-bit register access */
    struct {
        uint32_t BUF0I     : 1;  /* bit:0 , Buffer MB0 Interrupt*/
        uint32_t BUF1I     : 1;  /* bit:1 , */
        uint32_t BUF2I     : 1;  /* bit:2 , */
        uint32_t BUF3I     : 1;  /* bit:3 , */
        uint32_t BUF4I     : 1;  /* bit:4 , */
        uint32_t BUF5I     : 1;  /* bit:5 , */
        uint32_t BUF6I     : 1;  /* bit:6 , */
        uint32_t BUF7I     : 1;  /* bit:7 , */
        uint32_t BUF8I     : 1;  /* bit:8 ,  Buffer MBi Interrupt */
        uint32_t BUF9I     : 1;  /* bit:9 ,  Buffer MBi Interrupt */
        uint32_t BUF10I    : 1;  /* bit:20 ,  Buffer MBi Interrupt */
        uint32_t BUF11I    : 1;  /* bit:21 ,  Buffer MBi Interrupt */
        uint32_t BUF12I    : 1;  /* bit:22 ,  Buffer MBi Interrupt */
        uint32_t BUF13I    : 1;  /* bit:23 ,  Buffer MBi Interrupt */
        uint32_t BUF14I    : 1;  /* bit:24 ,  Buffer MBi Interrupt */
        uint32_t BUF15I    : 1;  /* bit:25 ,  Buffer MBi Interrupt */
        uint32_t BUF16I    : 1;  /* bit:26 ,  Buffer MBi Interrupt */
        uint32_t BUF17I    : 1;  /* bit:27 ,  Buffer MBi Interrupt */
        uint32_t BUF18I    : 1;  /* bit:28 ,  Buffer MBi Interrupt */
        uint32_t BUF19I    : 1;  /* bit:29 ,  Buffer MBi Interrupt */
        uint32_t BUF20I    : 1;  /* bit:20 ,  Buffer MBi Interrupt */
        uint32_t BUF21I    : 1;  /* bit:21 ,  Buffer MBi Interrupt */
        uint32_t BUF22I    : 1;  /* bit:22 ,  Buffer MBi Interrupt */
        uint32_t BUF23I    : 1;  /* bit:23 ,  Buffer MBi Interrupt */
        uint32_t BUF24I    : 1;  /* bit:24 ,  Buffer MBi Interrupt */
        uint32_t BUF25I    : 1;  /* bit:25 ,  Buffer MBi Interrupt */
        uint32_t BUF26I    : 1;  /* bit:26 ,  Buffer MBi Interrupt */
        uint32_t BUF27I    : 1;  /* bit:27 ,  Buffer MBi Interrupt */
        uint32_t BUF28I    : 1;  /* bit:28 ,  Buffer MBi Interrupt */
        uint32_t BUF29I    : 1;  /* bit:29 ,  Buffer MBi Interrupt */
        uint32_t BUF30I    : 1;  /* bit:30 ,  Buffer MBi Interrupt */
        uint32_t BUF31I    : 1;  /* bit:31 ,  Buffer MBi Interrupt */
    } ;
} CanRegIFLAG1_t;


/*
58.8.9 FLEXCAN_IMASK1 (Interrupt Masks 1 Register)
  */
typedef union  {
    uint32_t dword;  /* Full 32-bit register access */
    struct {
        uint32_t BUF0I     : 1;  /* bit:0 , Buffer MB0 Interrupt*/
        uint32_t BUF1I     : 1;  /* bit:1 , */
        uint32_t BUF2I     : 1;  /* bit:2 , */
        uint32_t BUF3I     : 1;  /* bit:3 , */
        uint32_t BUF4I     : 1;  /* bit:4 , */
        uint32_t BUF5I     : 1;  /* bit:5 , */
        uint32_t BUF6I     : 1;  /* bit:6 , */
        uint32_t BUF7I     : 1;  /* bit:7 , */
        uint32_t BUF8I     : 1;  /* bit:8 ,  Buffer MBi Interrupt */
        uint32_t BUF9I     : 1;  /* bit:9 ,  Buffer MBi Interrupt */
        uint32_t BUF10I    : 1;  /* bit:10 ,  Buffer MBi Interrupt */
        uint32_t BUF11I    : 1;  /* bit:11 ,  Buffer MBi Interrupt */
        uint32_t BUF12I    : 1;  /* bit:12 ,  Buffer MBi Interrupt */
        uint32_t BUF13I    : 1;  /* bit:13 ,  Buffer MBi Interrupt */
        uint32_t BUF14I    : 1;  /* bit:14 ,  Buffer MBi Interrupt */
        uint32_t BUF15I    : 1;  /* bit:15 ,  Buffer MBi Interrupt */
        uint32_t BUF16I    : 1;  /* bit:16 ,  Buffer MBi Interrupt */
        uint32_t BUF17I    : 1;  /* bit:17 ,  Buffer MBi Interrupt */
        uint32_t BUF18I    : 1;  /* bit:18 ,  Buffer MBi Interrupt */
        uint32_t BUF19I    : 1;  /* bit:19 ,  Buffer MBi Interrupt */
        uint32_t BUF20I    : 1;  /* bit:20 ,  Buffer MBi Interrupt */
        uint32_t BUF21I    : 1;  /* bit:21 ,  Buffer MBi Interrupt */
        uint32_t BUF22I    : 1;  /* bit:22 ,  Buffer MBi Interrupt */
        uint32_t BUF23I    : 1;  /* bit:23 ,  Buffer MBi Interrupt */
        uint32_t BUF24I    : 1;  /* bit:24 ,  Buffer MBi Interrupt */
        uint32_t BUF25I    : 1;  /* bit:25 ,  Buffer MBi Interrupt */
        uint32_t BUF26I    : 1;  /* bit:26 ,  Buffer MBi Interrupt */
        uint32_t BUF27I    : 1;  /* bit:27 ,  Buffer MBi Interrupt */
        uint32_t BUF28I    : 1;  /* bit:28 ,  Buffer MBi Interrupt */
        uint32_t BUF29I    : 1;  /* bit:29 ,  Buffer MBi Interrupt */
        uint32_t BUF30I    : 1;  /* bit:30 ,  Buffer MBi Interrupt */
        uint32_t BUF31I    : 1;  /* bit:31 ,  Buffer MBi Interrupt */
    } ;
} CanRegIMASK1_t;


/*
  58.8.45 FLEXCAN_FDCTRL (CAN FD Control Register)
  */
typedef union {
    uint32_t dword; ///< Full 32-bit register access
    struct {
        uint32_t TDCVAL  : 6;   /* bit: 5-0  Transceiver Delay Compensation Value */
        uint32_t RES1: 2;   /* bit: 3-10 */
        uint32_t TDCOFF  : 5;   /* bit: 12-8 Transceiver Delay Compensation Offset        */
        uint32_t RES2: 1;   /* bit: 11-14 */
        uint32_t TDCFAIL    : 1;   /* bit: 14 Transceiver Delay Compensation Fail */
        uint32_t TDCEN    : 1;   /* bit 15 Transceiver Delay Compensation Enable*/
        uint32_t MBDSR0  : 2;   /* bit: 17-16 Message Buffer Data Size for Region 0 */
        uint32_t RES3: 13;   /* bit:  */
        uint32_t FDRATE    : 1;   /* bit 31 Bit Rate Switch Enable*/
    } ;
} CanRegFDCTRL_t;



/*
 58.8.42 FLEXCAN_ENCBT (Enhanced Nominal CAN Bit Timing Register)
 */
typedef union {
    uint32_t dword; /* Full register access */
    struct    {
        uint32_t NTSEG1 : 8;  /* [7:0] Nominal Time Segment 1 */
        uint32_t RES1: 4;     /* [11:8]  */
        uint32_t NTSEG2 : 7;  /* [18:12] Nominal Time Segment 2 */
        uint32_t RES2   : 3;  /* [21:19]  */
        uint32_t NRJW   : 7;  /* [28:22] Nominal Resynchronization Jump Width */
        uint32_t RES3   : 3;  /* [31:29]  */
    } ;
} CanRegENCBT_t;



/*
  8.8.7 FLEXCAN_ECR (Error Counter Register)
 */
typedef union{
    uint32_t dword;  /* Full register access */
    struct    {
        uint8_t TXERRCNT      ; /* bit  7-0 Transmit Error Counter*/
        uint8_t RXERRCNT      ; /* bit  15-8  Receive Error Counter*/
        uint8_t TXERRCNT_FAST ; /* bit  23-16 Transmit Error Counter for fast bits  */
        uint8_t RXERRCNT_FAST ; /* bit  31-24 Receive Error Counter for fast bits*/
    };
} CanRegECR_t;


/*
  Union for FLEXCAN_ESR1 register (Error and Status 1 Register)
  Little-endian layout, lowest bits at the top.
 */
typedef union {
    uint32_t dword; /* Full register access */
    struct    {
        uint32_t RES1 : 1;       /* bit:0   */
        uint32_t ERRINT    : 1;  /* bit:1 Error Interrupt */
        uint32_t BOFFINT   : 1;  /* bit:2 Bus Off Interrupt  */
        uint32_t RX        : 1;  /* bit:3 This bit indicates if FLEXCAN is receiving a message.   */
        uint32_t FLTCONF   : 2;  /* bit:5-4 Fault Confinement State  */
        uint32_t TX        : 1;  /* bit:6 FLEXCAN In Transmission  */
        uint32_t IDLE      : 1;  /* bit:7 This bit indicates when FLEXCAN bus is in IDLE state.  */
        uint32_t RXWRN     : 1;  /* bit:8 Rx Error Warning           */
        uint32_t TXWRN     : 1;  /* bit:9 TX Error Warning  */
        uint32_t STFERR    : 1;  /* bit:10 Stuffing Error  */
        uint32_t FRMERR    : 1;  /* bit:11  Form Error */
        uint32_t CRCERR    : 1;  /* bit:12  Cyclic Redundancy Check Error         */
        uint32_t ACKERR    : 1;  /* bit:13  Acknowledge Error */
        uint32_t BIT0ERR   : 1;  /* bit:14  Bit0 Error */
        uint32_t BIT1ERR   : 1;  /* bit:15  Bit1 Error */
        uint32_t RWRNINT   : 1;  /* bit:16 Rx Warning Interrupt Flag  */
        uint32_t TWRNINT   : 1;  /* bit:17 Tx Warning Interrupt Flag  */
        uint32_t SYNCH     : 1;  /* bit:18 FLEXCAN Synchronization Status  */
        uint32_t BOFFDONEINT : 1; /*  Bus Off Done Interrupt */
        uint32_t ERRINT_FAST : 1; /*  Error interrupt for errors detected in Data Phase of CAN FD frames with  BRS bit set */
        uint32_t ERROVR : 1; /*Error Overrun   */
        uint32_t RES2   : 4; /*   */
        uint32_t STFERR_FAST : 1; /*  Stuffing Error in the Data Phase of CAN FD frames  */
        uint32_t FRMERR_FAST : 1; /* Form Error in the Data Phase of CAN FD frames with the BRS bit set  */
        uint32_t CRCERR_FAST : 1; /* Cyclic Redundancy Check Error in the CRC field of CAN FD frames with the BRS bit set  */
        uint32_t RES3 : 1; /*   */
        uint32_t BIT0ERR_FAST : 1; /* Bit0 Error in the Data Phase of CAN FD frames with the BRS bit set  */
        uint32_t BIT1ERR_FAST : 1; /* Bit1 Error in the Data Phase of CAN FD frames with the BRS bit set  */
    } ;
} CanRegESR1_t;

/*
58.8.48 FLEXCAN_ERFCR (Enhanced Rx FIFO Control Register)
 */
typedef union {
    uint32_t dword;
    struct {
        uint32_t ERFWM :5;  /* bits 4-0  Enhanced Rx FIFO Watermark */
        uint32_t RES1 :3;   /* bits 7-5  reserved*/
        uint32_t NFE :6;    /* bits 13-8 Number of Enhanced Rx FIFO Filter Elements*/
        uint32_t RES2 :2;   /* bits 15-14 reserved*/
        uint32_t NEXIF :7;  /* bits 22-16 Number of Extended ID Filter Elements */
        uint32_t RES3 :3;   /* bits 25-23 reserved*/
        uint32_t DMALW :5;  /* bits 30-26  DMA Last Word */
        uint32_t ERFEN :1;  /* bit  31 Enhanced Rx FIFO enable */
    };
} CanRegERFCR_t;

/*
58.8.50 FLEXCAN_ERFSR (Enhanced Rx FIFO Status Register) Offset: C14h
 */
typedef union{
    uint32_t dword; // Raw register access
    struct {
        uint32_t ERFEL      : 6; /*5-0 Enhanced Rx FIFO Elements*/
        uint32_t RES1 : 10;      /*15-7*/
        uint32_t ERFF       : 1; /*16 Enhanced Rx FIFO full*/
        uint32_t ERFE       : 1; /*17 Enhanced Rx FIFO empty*/
        uint32_t RES2  : 9;      /*26-28*/
        uint32_t ERFCLR    : 1; /*27 Enhanced Rx FIFO Clear*/
        uint32_t ERFDA     : 1; /*28 Enhanced Rx FIFO Data Available*/
        uint32_t ERFWMI    : 1; /*29 Enhanced Rx FIFO Watermark Indication*/
        uint32_t ERFOVF    : 1; /*30 Enhanced Rx FIFO Overflow*/
        uint32_t ERFUFW    : 1; /*31 Enhanced Rx FIFO Underflow*/
    } ;
} CanRegERFSR_t;

/*58.8.44 FLEXCAN_ETDC (Enhanced Transceiver Delay Compensation Register)*/
typedef union{
    uint32_t dword; // Raw register access
    struct {
        uint32_t ETDCVAL     : 8; /*7-0 Enhanced Transceiver Delay Compensation Value*/
        uint32_t RES1        : 7;        /*14-8 res*/
        uint32_t ETDCFAIL    : 1; /*15 Transceiver Delay Compensation Fail*/
        uint32_t RES2        : 7; /*29-23 Res*/
        uint32_t ETDCOFF     : 7; /*22-16 Enhanced Transceiver Delay Compensation Offset*/
        uint32_t TDMDIS      : 1; /*30 Transceiver Delay Measurement Disable */
        uint32_t ETDCEN      : 1; /*31 Transceiver Delay Compensation Enable*/
    } ;
} CanRegETDC_t;

/*
 58.8.12 FLEXCAN_ESR2 (Error and Status 2 Register)
 */
typedef union {
    uint32_t dword; /* Full register access */
    struct    {
        uint32_t RES1 : 13;       /* 12-0   */
        uint32_t IMB : 1;       /* 13  Inactive Mailbox */
        uint32_t VPS : 1;       /* 14  Valid Priority Status */
        uint32_t RES2: 1;       /* 15   */
        uint32_t LPTM : 7;       /* 22-16   Lowest Priority Tx Mailbox */
        uint32_t RES3: 9;       /* 31-23   */
    } ;
} CanRegESR2_t;


#endif /* FC7300_CAN_REGISTERS_TYPE_H  */
