#ifndef CAN_MES_BUFFER_CONST_H
#define CAN_MES_BUFFER_CONST_H

/*
 field MBDSR0 17-16 in reg FLEXCAN_FDCTRL
 Message Buffer Data Size for Region 0
 MBDSR0 For region R0 of message buffers allocated in RAM:
 MBDSR0 can be written in Freeze mode only.
 */
typedef enum {
    CAN_MESG_BUFF_DATA_SIZE_8_BYTE = 0, /* Selects 8 bytes per message buffer*/
    CAN_MESG_BUFF_DATA_SIZE_16_BYTE = 1, /* Selects 16 bytes per message buffer*/
    CAN_MESG_BUFF_DATA_SIZE_32_BYTE = 2, /* Selects 32 bytes per message buffer*/
    CAN_MESG_BUFF_DATA_SIZE_64_BYTE = 3, /* Selects 64 bytes per message buffer*/
    CAN_MESG_BUFF_DATA_SIZE_UNDEF = 4, /* */
} CanMessageBufferDataSize_t;


/*Table 101. Message buffer code for Rx buffers*/
typedef enum {
    CAN_CODE_INACTIVE = 0, /* MB does not participate in the matching process*/
    CAN_CODE_EMPTY = 4, /*  When a frame is received successfully*/
    CAN_CODE_FULL = 2, /*The act of reading the C/S word followed by unlocking the MB (SRV) does not make the code return to
                         EMPTY. */
    CAN_CODE_OVERRUN = 6, /* */
    CAN_CODE_RANSWER = 0xA, /*A Remote Answer was configured to recognize a remote request frame received. */

    CAN_CODE_BUSY = 1, /*This code is ignored during the matching and arbitration process. */

    CAN_CODE_INACTIVE_2 = 8, /*MB does not participate in the arbitration process. */
    CAN_CODE_ABORT = 9, /*MB does not participate in the arbitration process. */
    CAN_CODE_DATA = 12, /*Transmit data frame unconditionally once.  */
    CAN_CODE_TANSWER = 14, /*This is an intermediate code that is automatically written to
    the MB by the CHI as a result of a match to a remote request frame. */
    // CAN_CODE_REMOTE = 12, /* */

    CAN_CODE_UNDEF = 17, /**/
}CanCode_t;




typedef enum {
    CAN_MESSAGE_BUFFER_0 = 0, /* message buffer index 0   */
    CAN_MESSAGE_BUFFER_1 = 1, /* message buffer index 1  */
    CAN_MESSAGE_BUFFER_2 = 2, /* message buffer index 2   */
    CAN_MESSAGE_BUFFER_3 = 3, /* message buffer index 3   */
    CAN_MESSAGE_BUFFER_4 = 4, /* message buffer index 4   */
    CAN_MESSAGE_BUFFER_5 = 5, /* message buffer index 5   */
    CAN_MESSAGE_BUFFER_6 = 6, /* message buffer index 6   */
    CAN_MESSAGE_BUFFER_7 = 7, /* message buffer index 7   */
    CAN_MESSAGE_BUFFER_8 = 8, /* message buffer index 8   */
    CAN_MESSAGE_BUFFER_9 = 9, /* message buffer index 9   */
    CAN_MESSAGE_BUFFER_10 = 10, /* message buffer index 10   */
    CAN_MESSAGE_BUFFER_11 = 11, /*    */
    CAN_MESSAGE_BUFFER_12 = 12, /*    */
    CAN_MESSAGE_BUFFER_13 = 13, /*    */
    CAN_MESSAGE_BUFFER_14 = 14, /*    */
    CAN_MESSAGE_BUFFER_15 = 15, /*    */
    CAN_MESSAGE_BUFFER_16 = 16, /*    */
    CAN_MESSAGE_BUFFER_17 = 17, /*    */
    CAN_MESSAGE_BUFFER_18 = 18, /*    */
    CAN_MESSAGE_BUFFER_19 = 19, /*    */
    CAN_MESSAGE_BUFFER_20 = 20, /*    */
    CAN_MESSAGE_BUFFER_21 = 21, /*    */
    CAN_MESSAGE_BUFFER_22 = 22, /*    */
    CAN_MESSAGE_BUFFER_23 = 23, /*    */
    CAN_MESSAGE_BUFFER_24 = 24, /*    */
    CAN_MESSAGE_BUFFER_25 = 25, /*    */
    CAN_MESSAGE_BUFFER_26 = 26, /*    */
    CAN_MESSAGE_BUFFER_27 = 27, /*    */
    CAN_MESSAGE_BUFFER_28 = 28, /*    */
    CAN_MESSAGE_BUFFER_29 = 29, /*    */
    CAN_MESSAGE_BUFFER_30 = 30, /*    */
    CAN_MESSAGE_BUFFER_31 = 31, /*    */
    CAN_MESSAGE_BUFFER_UNDEF = 16 /*    */
} CanMesgbuffIndex_t;




#endif /* CAN_MES_BUFFER_CONST_H */
