#ifndef CAN_YTM_CUSTOM_CONST_H
#define CAN_YTM_CUSTOM_CONST_H

#define TX_MAILBOX (0UL)
#define RX_MAILBOX (1UL)



/*
Message Buffer Data Size for Region 0
–Selects the data size.
MBDSR0 For region R0 of message buffers allocated in RAM:
MBDSR0 can be written in Freeze mode only.
 */
typedef enum{
    CAN_MESG_BUFF_DATA_SIZE_8_BYTE = 0, /*Selects 8 bytes per message buffer*/
    CAN_MESG_BUFF_DATA_SIZE_16_BYTE = 1, /* Selects 16 bytes per message buffer*/
    CAN_MESG_BUFF_DATA_SIZE_32_BYTE = 2, /*Selects 32 bytes per message buffer*/
    CAN_MESG_BUFF_DATA_SIZE_64_BYTE = 3, /*Selects 64 bytes per message buffer*/
    CAN_MESG_BUFF_DATA_SIZE_UNDEF = 4, /**/
}CanMessageBufferDataSize_t;


typedef enum {
    CAN_DLC_0 = 0,
    CAN_DLC_1 = 1,
    CAN_DLC_2 = 2,
    CAN_DLC_3 = 3,
    CAN_DLC_4 = 4,
    CAN_DLC_5 = 5,
    CAN_DLC_6 = 6,
    CAN_DLC_7 = 7,
    CAN_DLC_8 = 8,
    CAN_DLC_12 = 9,
    CAN_DLC_16 = 10,
    CAN_DLC_20 = 11,
    CAN_DLC_24 = 12,
    CAN_DLC_32 = 13,
    CAN_DLC_48 = 14,
    CAN_DLC_64 = 15,
    CAN_DLC_UNDEF = 16
}CanDlc_t;



typedef enum {
    CAN_CODE_INACTIVE = 0, /* */
    CAN_CODE_INACTIVE_2 = 8, /* */
    CAN_CODE_EMPTY = 4, /*  */
    CAN_CODE_FULL = 2, /* */
    CAN_CODE_OVERRUN = 6, /* */
    CAN_CODE_RANSWER = 0xA, /* */
    CAN_CODE_BUSY = 1, /* */
    CAN_CODE_ABORT = 9, /* */
    CAN_CODE_DATA = 12, /* */
    CAN_CODE_TANSWER = 14, /* */
    // CAN_CODE_REMOTE = 12, /* */

    CAN_CODE_UNDEF = 17, /**/
}CanCode_t;


#endif /* CAN_YTM_CUSTOM_CONST_H  */
