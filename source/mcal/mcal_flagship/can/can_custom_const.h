#ifndef CAN_CONST_CONST_H
#define CAN_CONST_CONST_H

#define CAN_FC7300_DRV_VERSION (3)

#define CAN_WAIT_FREEZE_TIMEOUT_MS 3000

/* Module Disable, bit 31 */
typedef enum {
    CAN_MCR_MDIS_ENABLE = 0, /* 0b - Enable the FLEXCAN module */
    CAN_MCR_MDIS_DISABLE = 1, /* 1b - Disable the FLEXCAN module. */
    CAN_MCR_MDIS_UNDEF = 2,
} CanMCR_MDIS_t;

/* Halt FLEXCAN bit 29*/
typedef enum {
    CAN_MCR_HALT_NO_FREEZE_MODE_REQUEST = 0, /* 0b - No Freeze mode request*/
    CAN_MCR_HALT_ENTERS_FREEZE_MODE = 1, /* 1b - Enters Freeze mode if the FRZ bit is asserted.   */
    CAN_MCR_HALT_UNDEF = 2,
} CanMCR_HALT_t;

/* Self Reception Disable, bit 17*/
typedef enum {
    CAN_MCR_SRXDIS_SELF_RECEPTION_ON = 0, /* 0b - Self-reception enabled  */
    CAN_MCR_SRXDIS_SELF_RECEPTION_OFF = 1, /* 1b - Self-reception disabled.  */
    CAN_MCR_SRXDIS_UNDEF = 2,
} CanMCR_SRXDIS_t;

/* Freeze Enable, bit 30*/
typedef enum {
    CAN_MCR_FRZ_FLEE_FREEZE_MODE = 0, /* 0b -  Not enabled to enter Freeze mode  */
    CAN_MCR_FRZ_ENTER_FREEZE_MODE = 1, /* 1b - Enabled to enter Freeze mode  */
    CAN_MCR_FRZ_UNDEF = 2,
} CanMCR_FRZ_t;

/* Transceiver Delay Compensation, bit 15 */
typedef enum {
    FDCTRL_TDCEN_DISABLE = 0, /* 0b - TDC is disabled*/
    FDCTRL_TDCEN_ENABLED = 1, /* 1b - TDC is enabled      */
    FDCTRL_TDCEN_UNDEF = 2, /* */
} CanFDCTRL_TDCEN_t;

/* Transceiver Delay Compensation Enable, bit 31 */
typedef enum {
    ETDC_ETDCEN_TDC_DISABLE = 0, /* 0b - TDC is disabled*/
    ETDC_ETDCEN_TDC_ENABLED = 1, /* 1b - TDC is enabled      */
    ETDC_ETDCEN_UNDEF = 2, /* */
} CanETDC_ETDCEN_t;

/* CAN Engine Clock Source (bit 13)*/
typedef enum {
    CAN_CTRL1_CLKSRC_OSCILLATOR = 0, /* The CAN engine clock source is the oscillator clock */
    CAN_CTRL1_CLKSRC_PERIPHERAL = 1, /* The CAN engine clock source is the peripheral clock.    */
    CAN_CTRL1_CLKSRC_UNDEF = 2,
} Can_CTRL1_CLKSRC_t;



/*  Bit Rate Switch*/
typedef enum {
    CAN_BRS_NO = 0, /* bit rate is not switched*/
    CAN_BRS_YES = 1, /* bit rate is switched*/
    CAN_BRS_UNDEF = 2, /* */
} CanBRSCode_t;

/* Error State Indicator*/
typedef enum {
    CAN_ESI_PASSIVE = 0, /* transmitting node is error passive*/
    CAN_ESI_ACTIVE = 1, /* transmitting node is error active */
    CAN_ESI_UNDEF = 2, /* */
} CanESICode_t;

/* Extended Data Length*/
typedef enum {
    CAN_EDL_CLASSIC = 0, /**/
    CAN_EDL_FD = 1, /**/
    CAN_EDL_UNDEF = 2, /* */
} CanEDLCode_t;

/* SRR — Substitute Remote Request*/
typedef enum {
    CAN_SRR_DOMINANT_NO_VALID = 0, /*0 = Dominant is not a valid value for transmission in extended format frames*/
    CAN_SRR_RECESSIVE_COMPULSORY = 1, /*1 = Recessive value is compulsory for transmission in extended format frames*/
    CAN_SRR_UNDEF = 2, /* */
} CanSRRCode_t;

/* IDE — ID Extended Bit*/
typedef enum {
    CAN_IDE_STANDARD = 0, /* 0= Frame format is standard*/
    CAN_IDE_EXTENDED = 1, /* 1 = Frame format is extended*/
    CAN_IDE_UNDEF = 2, /* */
} CanIDECode_t;

/* RTR — Remote frame flag */
typedef enum {
    CAN_RTR_REMOTE_REJECTED = 0,/* 0 = Remote frames are rejected, and data frames can be accepted*/
    CAN_RTR_REMOTE_ACCEPTED = 1,/* 1 = Remote frames can be accepted, and data frames are rejected*/
    CAN_RTR_REMOTE_UNDEF = 2, /**/
} CanFrameRTR_t;

/* RTR — Remote Transmission Request */
typedef enum {
    CAN_RTR_TX = 0, /* 0= e current MB has a data frame to be transmitted. In Rx MB it may be considered in matching processes*/
    CAN_RTR_REM_REQ = 1, /* 1 =current MB may have a remote request frame to be transmitted if MB is Tx. If the MB is Rx then incoming
     remote request frames may be stored*/
    CAN_RTR_UNDEF = 2, /* */
} CanRTRCode_t;

typedef enum {
    CAN_MODE_NORMAL = 1, /* */
    CAN_MODE_Freeze = 8, /* */
    CAN_MODE_LOOP_BACK = 4, /*  */
    CAN_MODE_LISTEN_ONLY = 2, /* */
    CAN_MODE_CAN_FD_ACTIVE = 6, /* */
    CAN_MODE_DISABLE = 0xA, /* */
    CAN_MODE_STOP = 0xA, /* */
    CAN_MODE_PRETENDED_NETWORK = 0xA, /* */

    CAN_MODE_UNDEF = 0, /**/
} CanFc7300Mode_t;



typedef enum {
    FLEXCAN_BAUD_20K = 20000U, /* FLEXCAN_BAUD_20K  normal bit 20Kbps  */
    FLEXCAN_BAUD_50K = 50000U, /* FLEXCAN_BAUD_50K  normal bit 50Kbps  */
    FLEXCAN_BAUD_100K = 100000U, /* FLEXCAN_BAUD_100K normal bit 100Kbps */
    FLEXCAN_BAUD_125K = 125000U, /* FLEXCAN_BAUD_100K normal bit 125Kbps */
    FLEXCAN_BAUD_250K = 250000U, /* FLEXCAN_BAUD_250K normal bit 250Kbps */
    FLEXCAN_BAUD_500K = 500000U, /* FLEXCAN_BAUD_500K normal bit 500Kbps */
    FLEXCAN_BAUD_800K = 800000U, /* FLEXCAN_BAUD_500K normal bit 800Kbps */
    FLEXCAN_BAUD_1M = 1000000U,/* FLEXCAN_BAUD_1M   normal bit 1Mbps   */
    FLEXCAN_BAUD_2M = 2000000U,/* FLEXCAN_BAUD_2M   normal bit 2Mbps   */
    FLEXCAN_BAUD_3M = 3000000U,/* FLEXCAN_BAUD_3M   normal bit 3Mbps   */
    FLEXCAN_BAUD_4M = 4000000U,/* FLEXCAN_BAUD_4M   normal bit 4Mbps   */
    FLEXCAN_BAUD_5M = 5000000U,/* FLEXCAN_BAUD_5M   normal bit 5Mbps   */
    FLEXCAN_BAUD_6M = 6000000U,/* FLEXCAN_BAUD_6M   normal bit 6Mbps   */
    FLEXCAN_BAUD_8M = 8000000U /* FLEXCAN_BAUD_8M   normal bit 8Mbps   */
} CAN_BaudType;

typedef enum {
    FLEXCAN_BAUDCLK_HZ_8M = 8000000U, /* FLEXCAN_BAUDCLK_HZ_8M   8MHz clock source   */
    FLEXCAN_BAUDCLK_HZ_12M = 12000000U, /* FLEXCAN_BAUDCLK_HZ_12M  12MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_16M = 16000000U, /* FLEXCAN_BAUDCLK_HZ_16M  16MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_24M = 24000000U, /* FLEXCAN_BAUDCLK_HZ_24M  24MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_48M = 48000000U, /* FLEXCAN_BAUDCLK_HZ_48M  48MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_96M = 96000000U, /* FLEXCAN_BAUDCLK_HZ_96M  96MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_120M = 120000000U,/* FLEXCAN_BAUDCLK_HZ_120M 120MHz clock source */
    FLEXCAN_BAUDCLK_HZ_150M = 150000000U /* FLEXCAN_BAUDCLK_HZ_150M 150MHz clock source */
} CAN_BaudClkType;

typedef enum {
    CAN_RET_OK = 0, /* Ok */
    CAN_RET_ERR = 1, /* Errror */
    CAN_RET_UNDEF = 2, /* undef */
} CAN_ErrorCode_t;

#endif /* CAN_CONST_CONST_H */
