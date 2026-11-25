#ifndef CAN_CUSTOM_TYPE_H
#define CAN_CUSTOM_TYPE_H

#include "fc7300x.h"
#include "can_custom_const.h"
#include "clock_const.h"
#include "flexcan_driver.h"
#include "microcontroller_types.h"


#define CAN_CUSTOM_TX_VARIABLES         \
    flexcan_msgbuff_t TxMsg;             \
    flexcan_data_info_t txMbStdInfo;


#define CAN_CUSTOM_RX_VARIABLES         \
    flexcan_msgbuff_t RxMsg;            \
    flexcan_data_info_t rxMbStdInfo;

#define CAN_CUSTOM_VARIABLES         \
    CAN_CUSTOM_RX_VARIABLES          \
    CAN_CUSTOM_TX_VARIABLES          \
    CAN_Type* CANx;                  \
    flexcan_state_t handle;

typedef struct {
    CAN_Type* CANx;
    uint32_t clock_type;
    ClockBus_t clock_bus;
    uint8_t num;
    bool valid;
    uint32_t clock_hz;
    IRQn_Type irq_n_error;
    IRQn_Type irq_n_wake_up;
    IRQn_Type irq_n_ored;
    IRQn_Type irq_n_ored_0_15_mb;
    IRQn_Type irq_n_ored_16_31_mb;
    IRQn_Type irq_n_ored_32_47_mb;
    IRQn_Type irq_n_ored_48_63_mb;
}CanInfo_t;


/*
 18.3.3.2 CAN CTRL1 Register
 */
typedef union {
    uint32_t qword;
    struct {
        uint32_t PROPSEG:3; /*  2-0   */
        uint32_t LOM:1; /*  3  Listen Only Mode */
        uint32_t LBUF:1; /*  4  Lowest Buffer Transmitted First –Defines the ordering mechanism for message buffer transmission */
        uint32_t TSYN:1; /*  5   */
        uint32_t BOFFREC:1; /* 6  Bus Off Recovery–Defines how the FlexCAN recovers from Bus Off state  */
        uint32_t SMP:1; /*  7  CAN bit Sampling –Defines the sampling mode of CAN bits at the Rx input */
        uint32_t res:2; /*  9 -8   */
        uint32_t RWRNMSK:1; /*  10   */
        uint32_t TWRNMSK:1; /* 11    */
        uint32_t LPB:1; /*12   Loop Back Mode –Configures the FlexCAN to operate in Loop-Back mode  */
        uint32_t CLKSRC:1; /*  13  CAN engine clock source –Selects the clock source to the PE submodule to be either the peripheral clock or the oscillator clock */
        uint32_t ERRMSK:1; /* 14  Error Interrupt Mask –Provides a mask for the Error interru  */
        uint32_t BOFFMSK:1; /* 15    */
        uint32_t PSEG2:3; /* 18 - 16  Phase Segment 2 –Defines the length of phase segment 2  */
        uint32_t PSEG1:3; /* 21 - 19 Phase Segment 1 –Defines the length of phase segment 1 in the bit time   */
        uint32_t RJW:2; /* 23 - 22  Resync Jump Width –Defines the maximum number of time quanta that a bit time can be changed by one re-synchronization  */
        uint32_t PRESDIV:8; /* 31 - 24  Prescaler Division Factor –Defines the ratio between the PE clock frequency and the serial clock (Sclock) frequency  */
    };
}CanRegCTRL1_t;


/* CAN CBT Register      */
typedef union {
    uint32_t qword;
    struct {
        uint32_t EPSEG2:5; /*    */
        uint32_t EPSEG1:5; /*    */
        uint32_t EPROPSEG:6; /*    */
        uint32_t ERJW:5; /*    */
        uint32_t EPRESDIV:10; /*    */
        uint32_t BTF:1; /*    */
    };
}CanRegCBT_t;


/* CAN FDCBT Register */
typedef union {
    uint32_t qword;
    struct {
        uint32_t FPSEG2:3; /* Fast Phase Segment 2 */
        uint32_t RES1:2; /*    */
        uint32_t FPSEG1:3; /* Fast Phase Segment 1 */
        uint32_t RES2:2; /*    */
        uint32_t FPROPSEG:5; /* Fast Propagation Segment */
        uint32_t RES3:1; /*    */
        uint32_t FRJW:3; /* Fast Resync Jump Width   */
        uint32_t RES4:1; /*    */
        uint32_t FPRESDIV:10; /*Fast    */
        uint32_t RES5:2; /*    */
    };
}CanRegFDCBT_t;



typedef union{
    uint32_t qword;
    struct{
        uint32_t WAKINT:1;
        uint32_t ERRINT:1;
        uint32_t BOFFINT:1;
        uint32_t RX:1;
        uint32_t FLTCONF:2;
        uint32_t TX:1;
        uint32_t IDLE:1;
        uint32_t RXWRN:1;
        uint32_t TXWRN:1;
        uint32_t STFERR:1;
        uint32_t FRMERR:1;
        uint32_t CRCERR:1;
        uint32_t ACKERR:1;
        uint32_t BIT0ERR:1;
        uint32_t BIT1ERR:1;
        uint32_t RWRNINT:1;
        uint32_t TWRNINT:1;
        uint32_t SYNCH:1;
        uint32_t BOFFDOENINT:1;
        uint32_t ERRINT_FAST :1;
        uint32_t ERROVR :1;
        uint32_t res1:4;
        uint32_t STFERR_FAST  :1;
        uint32_t FRMERR_FAST   :1;
        uint32_t CRCERR_FAST    :1;
        uint32_t res2    :1;
        uint32_t BIT0ERR_FAST    :1;
        uint32_t BIT1ERR_FAST    :1;
    };
}CanRegEsr_t;


/*  Table 18.12: CAN ECR  */
typedef union {
    uint32_t qword;
    struct {
        uint32_t TXERRCNT:8; /*  Transmit Error Counter  */
        uint32_t RXERRCNT:8; /*  Receive Error Counter     */
        uint32_t TXERRCNT_FAST:8; /* Transmit Error Counter for Fast Bits */
        uint32_t RXERRCNT_FAST:8; /* Receive  Error Counter for Fast Bits*/
    };
}CanRegECR_t;

/* 18.3.3.42 CAN WMB_WMBn_CS Register */
typedef union {
    uint32_t qword;
    struct {
        uint32_t res1:16; /*    */
        uint32_t DLC:4; /* Length of Data in Bytes  */
        uint32_t RTR:1; /* Remote Transmission Request Bit     */
        uint32_t IDE:1; /*ID Extended Bit Identifies whether the frame format is standard or extended. */
        uint32_t SRR:1; /* Substitute Remote Request Can be received either recessive or dominant.*/
        uint32_t res2:9; /*    */
    };
}CanRegWMB_CS_t;



/*  18.3.3.50 CAN FDCTRL Register  */
typedef union {
    uint32_t qword;
    struct {
        uint32_t TDCVAL:6; /*  transceiver Delay Compensation Value*/
        uint32_t res1:2; /*  xxxxxxx*/
        uint32_t TDCOFF:5; /*  Transceiver Delay Compensation Offset*/
        uint32_t res2:1; /*  xxxxxxx*/
        uint32_t TDCFAIL:1; /*  Transceiver Delay Compensation Fail*/
        uint32_t TDCEN:1; /*  Transceiver Delay Compensation Enable*/
        uint32_t MBDSR0:2; /*  Message Buffer Data Size for Region 0*/
        uint32_t res3:13; /*  xxxxxxx*/
        uint32_t FDRATE:1; /*  bit rate switch enable*/
    };
}CanRegCAN_FDCTRL_t;


typedef struct {
    uint8_t buff[16];
}CanMbPayload8_t;

typedef struct {
    uint8_t buff[24];
}CanMbPayload16_t;

typedef struct {
    uint8_t buff[40];
}CanMbPayload32_t;

typedef union {
    uint8_t buff[72];
    uint32_t qword[18];
}CanMbPayload64_t;


/*
 Figure 18.2: message buffer structure example with 64 bytes payload
 */
typedef union {
    uint8_t buf[72];
    uint32_t qword[18];
    struct {
        struct {
           uint32_t TIME_STAMP: 16;
           uint32_t DLC: 4;
           uint32_t RTR: 1;
           uint32_t IDE: 1;
           uint32_t SRR: 1;
           uint32_t RES1: 1;
           uint32_t CODE: 4;
           uint32_t RES2: 1;
           uint32_t ESI: 1;
           uint32_t BRS: 1;
           uint32_t EDL: 1;
        };
        struct{
            uint32_t ID_EXTENDED: 29;
            uint32_t PRIO: 3;
        };
        uint8_t data[64];
    };
}CanMessageBufferLayOut_t;


typedef union {
    uint8_t buff[2048];
    CanMbPayload8_t MbPayload8[128];
    CanMbPayload16_t MbPayload16[84];
    CanMbPayload32_t MbPayload32[48];
    CanMbPayload64_t MbPayload64[28];
}CanMessageBuffer_t;



#endif /* CAN_CUSTOM_TYPE_H  */
