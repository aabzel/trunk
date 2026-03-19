#ifndef CAN_STM32_CUSTOM_CONST_H
#define CAN_STM32_CUSTOM_CONST_H

#define CAN_STM32_DRV_VERSION (2)
#define CAN_WAIT_INIT_MODE_TIMEOUT_MS 1000

#define CAN2_FILTER_NUM_FIRST (14u)

/*see Bits 6:4 LEC[2:0]: Last error code
 This field is set by hardware and holds a code which indicates the error condition of the last
 error detected on the CAN bus. If a message has been transferred (reception or
 transmission) without error, this field is cleared to 0.
 The LEC[2:0] bits can be set to value 0b111 by software. They are updated by hardware to
 indicate the current communication status
 */
typedef enum {
    CAN_LEC_OK = 0, /*000: No Error*/
    CAN_LEC_STUFF_ERROR = 1,/*001: Stuff Error*/
    CAN_LEC_FORM_ERROR = 2,/*010: Form Error*/
    CAN_LEC_ACKNOWLEDGMENT_ERROR = 3,/*011: Acknowledgment Error*/
    CAN_LEC_BIT_RECESSIVE_ERROR = 4,/*100: Bit recessive Error*/
    CAN_LEC_BIT_DOMINANT_ERROR = 5,/*101: Bit dominant Error*/
    CAN_LEC_CRC_ERROR = 6,/*110: CRC Error*/
    CAN_LEC_RESET = 7,/*111: Set by software*/
    CAN_LEC_UNDEF = 8/**/
} CanLastErrorCode_t;

/*Bits 27:0 FFAx: Filter FIFO assignment for filter x
 * CAN filter FIFO assignment register (CAN_FFA1R)*/
typedef enum {
    CAN_FILTER_FIFO_0 = 0 , /*0: Filter assigned to FIFO 0*/
    CAN_FILTER_FIFO_1 = 1 , /*1: Filter assigned to FIFO 1*/
    CAN_FILTER_FIFO_UNDEF =2 , /**/
} CanFFAxCode_t;

/*Bit 0 INRQ: Initialization request*/
typedef enum {
    CAN_INRQ_NORMAL = 0,//The software clears this bit to switch the hardware into normal mode.
    CAN_INRQ_INITIALIZATION = 1,//Software sets this bit to request the CAN hardware to enter initialization mode.
}CanMCR_INRQ_t;


/* FSCx: Filter scale configuration*/
typedef enum {
    CAN_FILTER_SCALE_16_BIT = 0 , /*0: Dual 16-bit scale configuration*/
    CAN_FILTER_SCALE_32_BIT = 1 , /*1: Single 32-bit scale configuration */
    CAN_FILTER_SCALE_UNDEF =2 , /**/
} CanFilterScale_t;

/* CAN filter mode register (CAN_FM1R)*/
typedef enum {
    CAN_FILTER_MODE_ID_MASK = 0 , /*0: Two 32-bit registers of filter bank x are in Identifier Mask mode.*/
    CAN_FILTER_MODE_LIST = 1 ,    /*1: Two 32-bit registers of filter bank x are in Identifier List mode. */
    CAN_FILTER_MODE_UNDEF = 2 , /**/
} CanFilterMode_t;

/*Bit 0 INAK: Initialization acknowledge*/
typedef enum {
    CAN_MSR_INAK_INITIALIZATION = 1, /*This bit is set by hardware and indicates to the software that the CAN hardware is now in
initialization mode. This bit acknowledges the initialization request from the software (set
INRQ bit in CAN_MCR register).*/

    CAN_MSR_INAK_INITIALIZATION_LEFT = 0, /*This bit is cleared by hardware when the CAN hardware has left the initialization mode (to
be synchronized on the CAN bus). To be synchronized the hardware has to monitor a
sequence of 11 consecutive recessive bits on the CAN RX signal.*/
} CanMsrInak_t;

/* Mode is controlled in CAN_MCR register */
typedef enum {
    CAN_STM_MODE_NORMAL = 1,
    CAN_STM_MODE_SLEEP = 8, /* Sleep mode is entered as soon as the current CAN activity (transmission or reception of a CAN
frame) has been completed.*/
    CAN_STM_MODE_FREEZE = 6,
    CAN_STM_MODE_STANDBY = 2,/*As a safeguard against programming errors, the configuration of the Bit Timing register
(CAN_BTR) is only possible while the device is in Standby mode.*/
    CAN_STM_MODE_SILENT = 3,/*In Silent mode, the bxCAN is able to receive valid data frames and valid remote frames, but
    it sends only recessive bits on the CAN bus and it cannot start a transmission. */
    CAN_STM_MODE_LOOPBACK = 4,
    CAN_STM_MODE_LOOPBACK_SILENT = 7,
    /*Therefore the CAN_BTR register can be modified by
software only while the CAN hardware is in initialization mode.*/
    CAN_STM_MODE_INITIALIZATION =5,/*Therefore the CAN_BTR register can be modified by
software only while the CAN hardware is in initialization mode.*/
    CAN_STM_MODE_UNDEF =0,
}CanStmMode_t;

typedef enum {
    CAN_IDE_STD=0,
    CAN_IDE_EXT=1,
    CAN_IDE_UNDEF=2,
}CanIdeBit_t;

#endif /* CAN_STM32_CUSTOM_CONST_H  */
