#ifndef CAN_MESSAGE_BUFFER_TYPES_H
#define CAN_MESSAGE_BUFFER_TYPES_H

#include "std_inc.h"
#include "can_message_buffer_const.h"

typedef union{
    uint32_t dword;
    struct{
        uint32_t RES3: 18;     /* 17-0   */
        uint32_t STANDARD: 11; /* 28-18   */
        uint32_t PRIO: 3;      /* 31-29   */
    };
    struct {
        uint32_t EXTENDED: 29; /*28-0   */
        uint32_t PRIO2: 3; /*31-29   */
    };
}CanMessageBufferId_t;


/*
Table 100. Message buffer structure example with 64 Bytes payload
 */
typedef union {
    uint8_t buf[72];
    uint32_t dword[18];
    struct {
        struct {
           uint32_t TIME_STAMP: 16; /* 15-0  */
           uint32_t DLC: 4; /*19-16   */
           uint32_t RTR: 1; /*20   */
           uint32_t IDE: 1; /*21   */
           uint32_t SRR: 1; /*22   */
           uint32_t RES1: 1; /*23   */
           uint32_t CODE: 4; /*27-24   */
           uint32_t RES2: 1; /*28   */
           uint32_t ESI: 1; /*29   */
           uint32_t BRS: 1; /*30   */
           uint32_t EDL: 1; /*31   */
        };
        CanMessageBufferId_t ID;
        uint8_t data[64]; /*   */
    };
}CanMessageBufferLayOut_t;


typedef struct {
    uint8_t buff[16];
    uint32_t dword[4];
}CanMbPayload8_t;

typedef struct {
    uint8_t buff[24];
    uint32_t dword[6];
}CanMbPayload16_t;

typedef struct {
    uint8_t buff[40];
    uint32_t dword[10];
}CanMbPayload32_t;

typedef union {
    uint8_t buff[72];
    uint32_t dword[18];
}CanMbPayload64_t;

typedef union {
    uint8_t buff[FLEXCAN_RAM_COUNT*4]; /*128*4=512 byte     */
    CanMbPayload8_t MbPayload8[32];  /* Table 104. 8-byte message buffer*/
    CanMbPayload16_t MbPayload16[21]; /* */
    CanMbPayload32_t MbPayload32[12]; /* */
    CanMbPayload64_t MbPayload64[7]; /* */
}CanMessageBuffer_t;

#endif /* CAN_MESSAGE_BUFFER_TYPES_H */
