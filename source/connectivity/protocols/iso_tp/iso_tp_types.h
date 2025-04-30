#ifndef ISO_TP_TYPES_H
#define ISO_TP_TYPES_H

/*ISO_TP Unified Diagnostic Services */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>

#include "data_utils.h"
#include "iso_tp_const.h"
#include "system.h"

typedef union {
    uint8_t byte;
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
       uint16_t data_len :12; /*bit 0-11*/
       uint16_t frame_id:4;  /*bit 12-15*/
    };
}IsoTpFirstFrameHeader_t;


typedef union {
    uint8_t buff[3];
    struct {
        struct {
            uint8_t flow_status :4; /*bit 0-3*/
            uint8_t frame_id:4;  /*bit 4-7*/
        }__attribute__((packed));
        uint8_t block_size;
        uint8_t min_sep_time;
    }__attribute__((packed));
} __attribute__((packed)) IsoTpFlowControlHeader_t;


typedef union {
    uint8_t byte;
    struct {
       uint8_t sn :4; /*bit 0-3*/
       uint8_t frame_id:4;  /*bit 4-7*/
    };
}IsoTpConsecutiveFrameHeader_t;

typedef union{
    IsoTpFlowControlHeader_t FlowControlHeader;
    IsoTpConsecutiveFrameHeader_t ConsecutiveFrameHeader;
    uint8_t data[8];
    uint64_t qword;
}IsoTpFrame_t;

#define ISO_TP_COMMON_VARIABLES       \
    bool valid;                       \
	uint16_t my_id;                   \
	uint8_t block_size;               \
    uint8_t separation_time_ms;       \
    uint32_t num;                     \
    uint32_t uds_num;                 \
    Interfaces_t interface;

#define ISO_TP_RECEIVER_VARIABLES \
	IsoTpFrame_t RxFrame;   \
    uint8_t rx_prev_sn;          \
	uint8_t RxData[ISO_TP_MTU];  \
	bool unproc_frame;  \
	int32_t rx_rest_byte; \
	size_t rx_byte_cnt; \
    size_t rx_block_cnt; \
	size_t expected_size; \
	uint16_t rx_id;

#define ISO_TP_SENDER_VARIABLES  \
	IsoTpFrame_t TxFrame;        \
	uint8_t sn;           \
	uint32_t tx_period_ms;   \
	uint32_t tx_next_time_ms;   \
	size_t tx_done_bytes;      \
	uint8_t TxData[ISO_TP_MTU];   \
	volatile int32_t tx_rest_byte; \
	uint8_t blocks_to_send; \
	size_t tx_size;

//uint16_t target_id;

typedef struct {
    ISO_TP_COMMON_VARIABLES

	ISO_TP_RECEIVER_VARIABLES

	ISO_TP_SENDER_VARIABLES
	//uint8_t block_cnt;

    IsoTpState_t state;
    IsoTpRole_t role;
} IsoTpHandle_t;

typedef struct {
    ISO_TP_COMMON_VARIABLES
}IsoTpConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* ISO_TP_TYPES_H */
