#ifndef ISO_TP_TYPES_H
#define ISO_TP_TYPES_H


#include <stddef.h>
#include <time.h>

#include "std_includes.h"
#include "data_utils.h"
#include "iso_tp_const.h"
#include "interfaces_types.h"
#include "system.h"

#ifdef HAS_ISO_TP_CUSTOM
#include "iso_tp_custom_types.h"
#else
#define ISO_TP_CONFIG_CUSTOM_VARIABLES
#define ISO_TP_CUSTOM_VARIABLES
#endif

/*Table 26 Normal fixed addressing, N_TAtype = #5 and 7*/
typedef union {
    uint32_t dword;
    struct {
        uint32_t source_address : 8;  /* (SA) bit 0-7 The SA field shall contain the source address, N_SA*/
        uint32_t target_address : 8;  /* (PS) bit 15-8 N_TA The PDU-specific field shall contain the target address (destination address), */
        uint32_t protocol_format : 8; /* (PF) bit 23-16 Protocol data unit format */
        uint32_t data_page : 1;       /* (DP) bit 24 zero */
        uint32_t reserved : 1;        /* bit 25 zero */
        uint32_t priority : 3;         /* bit 28-26   The priority is user defined with a default value of six  (110 binary)*/
        uint32_t reserved2 : 3;        /* bit 31-29   The priority is user defined with a default value of six  (110 binary)*/
    };
    struct {
        uint32_t extended : 29; /* bit 28-0*/
        uint32_t res :3;       /* bit 31-29*/
    };
} IsoTpNormalFixedAddress_t;

/*Table A.3 ? Mixed addressing, physical addressed messages*/
typedef union {
    uint32_t dword;
    struct {
        uint32_t source_address :8; /*bit 0-7 N_SA*/
        uint32_t target_address :8; /*bit 15-8 N_TA*/
        uint32_t const206val :8; /*bit 23 ? 16 magic value 206 */
        uint32_t zero :2; /*bit 25-24 zero */
        uint32_t six:3; /*bit 28-26     110 binary*/
    };
    struct {
        uint32_t extended :29; /*bit 28-0*/
        uint32_t res :3; /*bit 31-29*/
    };
} IsoTpFixedAddress_t;

/*Table 32 ? Mixed addressing with 11 bit CAN identifier, N_TAtype = #1 and 3*/
typedef union {
    uint32_t dword;
    struct {
        uint32_t address_information :11; /*bit 10-0 N_AI*/
        uint32_t res1:21; /*bit 31-11   */
    };
    struct {
        uint32_t standart :11; /*bit 10-0*/
        uint32_t res2 :21; /*bit 31-11*/
    };
} IsoTpMixedAddress_t;

typedef union {
    uint8_t buff[1];
    struct {
       uint8_t reserved : 4;  /* bit 0-3*/
       uint8_t frame_id : 4;  /* bit 4-7: Valid values: 0 1 2 3*/
    };
}IsoTpFrameHeader_t;

typedef union {
    uint8_t buff[1];
    struct {
       uint8_t data_len :4; /*bit 0-3*/
       uint8_t frame_id:4;  /*bit 4-7*/
   };
}IsoTpSingleFrameHeader_t;

/*Little endian cpu*/
typedef union {
    uint8_t buff[2];
    uint16_t word;
    struct {
       uint16_t data_len: 12;  /* bit 11-0   */
       uint16_t frame_id: 4;   /* bit 15-12  must be constant ISO_TP_FRAME_CODE_FIRST_FRAME */
    };
}IsoTpFirstFrameHeader_t;


typedef union {
    uint8_t buff[3];
    struct {
        struct {
            uint8_t flow_status :4; /* bit 0-3 must be values from IsoTpFlowControlFlag_t */
            uint8_t frame_id:4;     /* bit 4-7 must be  ISO_TP_FRAME_CODE_FLOW_CONTOL*/
        }__attribute__((packed));
        uint8_t block_size;
        uint8_t min_sep_time;
    }__attribute__((packed));
} __attribute__((packed)) IsoTpFlowControlHeader_t;



typedef union {
    uint8_t buff[1];
    struct {
       uint8_t sn :4; /*bit 0-3*/
       uint8_t frame_id:4;  /*bit 4-7 must be ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME=2*/
    };
}IsoTpConsecutiveFrameHeader_t;

typedef union{
    IsoTpSingleFrameHeader_t SingleFrameHeader;
    IsoTpFlowControlHeader_t FlowControlHeader;
    IsoTpConsecutiveFrameHeader_t ConsecutiveFrameHeader;
    uint8_t data[8];
    uint64_t qword;
}IsoTpFrame_t;


#ifdef HAS_IQUEUE
#define ISO_TP_IQUEUE uint8_t iqueue_num;
#else
#define ISO_TP_IQUEUE
#endif

#define ISO_TP_COMMON_VARIABLES       \
    ISO_TP_CONFIG_CUSTOM_VARIABLES    \
    ISO_TP_IQUEUE                     \
    uint8_t* TxFiFoMem;               \
    uint32_t tx_fifo_size;            \
    bool valid;                       \
    uint8_t block_size;               \
    float separation_time_s;          \
    char* name;                       \
    IsoTpAddressing_t addressing;     \
    uint32_t my_id;                   \
    uint32_t num;                     \
    uint32_t uds_num;                 \
    uint32_t cli_num;                 \
    InterfaceType_t interface_if;

#define ISO_TP_RECEIVER_VARIABLES   \
    uint16_t expected_size;         \
    uint16_t rx_msg_size;           \
    uint32_t subscription_id;       \
    uint32_t rx_id;                 \
    IsoTpFrame_t RxFrame;           \
    uint8_t rx_prev_sn;             \
    uint8_t rx_sn;                  \
    uint8_t RxData[ISO_TP_MTU];     \
    bool unproc_frame;              \
    bool rx_done;                   \
    int32_t rx_rest_byte;           \
    uint32_t rx_byte_cnt;           \
    uint32_t rx_block_cnt;

#define ISO_TP_SENDER_VARIABLES    \
    bool tx_done;                  \
    FifoChar_t TxFifo;             \
    IsoTpFrame_t TxFrame;          \
    uint8_t sn;                    \
    uint8_t tx_sn;                 \
    uint8_t target_id;             \
    uint32_t reply_address_id;     \
    uint32_t tx_period_ms;         \
    uint32_t tx_next_time_ms;      \
    uint32_t tx_done_bytes;        \
    uint8_t TxData[ISO_TP_MTU];    \
    volatile int32_t tx_rest_byte; \
    uint8_t blocks_to_send;        \
    uint32_t tx_size;


typedef struct {
    ISO_TP_COMMON_VARIABLES
    ISO_TP_CUSTOM_VARIABLES
    ISO_TP_RECEIVER_VARIABLES
    ISO_TP_SENDER_VARIABLES
    bool in_progress; /* data is being transmitted or received */
    bool init;
    bool error_done;
    uint32_t error_cnt;
    //uint8_t block_cnt;
    uint32_t spin;
    IsoTpNormalFixedAddress_t RxAddress;
    IsoTpState_t state;
    IsoTpRole_t role;
} IsoTpHandle_t;

typedef struct {
    ISO_TP_COMMON_VARIABLES
}IsoTpConfig_t;

#endif /* ISO_TP_TYPES_H */
