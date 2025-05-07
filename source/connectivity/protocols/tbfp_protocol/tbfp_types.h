#ifndef TBFP_TYPES_H
#define TBFP_TYPES_H

/*TBFP Trivial Binary Frame Protocol*/
#ifdef __cplusplus
extern "C" {
#endif


#include <time.h>

#include "std_includes.h"
#include "data_utils.h"
#include "fifo_char.h"
#include "tbfp_protocol_parser.h"
#include "tbfp_re_tx_ack_fsm_types.h"
#include "tbfp_const.h"
#include "system.h"

#ifdef HAS_GNSS
#include "gnss_types.h"
#endif

#ifdef HAS_PROTOCOL
#include "protocol_types.h"
#endif


typedef union {
    uint8_t byte;
    struct {
        uint8_t lifetime :4; /*bit 0-3*/
        uint8_t response:1;  /*bit 4 this bit says that this is a response packet*/
        uint8_t reserved:1;  /*bit 5*/
        uint8_t crc_check_need:1;  /*bit 6*/
        uint8_t ack_need:1;  /*bit 7*/
    };
}TbfpFrameFlags_t;

#ifdef HAS_TBFP_DIAG

#define TBFP_DIAG_VARIABLES                          \
    uint32_t preamble_cnt;                           \
    uint16_t max_len; /*TODO combine to struct*/     \
    uint16_t min_len;                                \
    bool debug;
#else
#define TBFP_DIAG_VARIABLES
#endif /*HAS_TBFP_DIAG*/

/*(see specification
   https://docs.google.com/spreadsheets/d/1VAT3Ak7AzcufgvuRHrRVoVfC3nxugFGJR5pyzxL4W7Q/edit#gid=0
  ) */
typedef union {
    uint8_t buff[7];
    struct {
        uint8_t preamble;
        TbfpFrameFlags_t flags; /* For ack, mesh feature (lifetime)*/
        uint16_t snum; /* serial number of the frame. For flow controll.*/
        uint16_t len; /* Payload Len */
        TbfpPayloadId_t payload_id;
        uint8_t payload[0]; /* just for pointer*/
	}__attribute__((packed));
} __attribute__((packed)) TbfpHeader_t;

typedef struct  {
    uint8_t id;
    uint64_t mac;
    time_t time_stamp;
#ifdef HAS_GNSS
    GnssCoordinate_t coordinate;
    double height_m;
#endif
} __attribute__((packed)) TbfPingFrame_t;


#define TBFP_RX_VARIABLES   \
    U32Value_t rx_rate;     \
    uint32_t rx_byte;       \
    uint32_t rx_cnt;        \
    uint32_t rx_byte_prev;  \
    uint32_t rx_pkt_cnt;    \
    bool rx_done;           \
    bool rx_pong;           \
    bool rx_ping;

#define TBFP_TX_VARIABLES                  \
    uint32_t tx_size;  \
    uint32_t tx_byte;  \
    uint32_t tx_byte_prev;  \
    uint32_t tx_pkt_cnt;  \
    U32Value_t tx_rate;  \
    uint32_t err_tx_cnt;  \
    uint32_t err_tx_cnt_prev;

#define TBFP_COMMON_RX_VARIABLES         \
    uint8_t* fix_frame;                  \
    uint8_t* rx_frame;                   \
    uint8_t* RxArray;                    \
    uint32_t rx_array_size;

#define TBFP_COMMON_TX_VARIABLES         \
    uint32_t tx_array_size;              \
    uint8_t* TxFrame;


#define TBFP_COMMON_VARIABLES            \
    TBFP_COMMON_RX_VARIABLES             \
    TBFP_COMMON_TX_VARIABLES             \
    bool valid;                          \
    bool crc_check_need;                 \
    bool heartbeat;                      \
    Interfaces_t inter_face;             \
    uint8_t preamble_val;                \
    uint8_t uart_num;                    \
	uint32_t num;




#define TBFP_CRC_VARIABLES            \
    uint32_t read_crc8;               \
    uint32_t len_err_cnt;             \
    uint32_t crc_err_cnt;             \
    uint32_t crc_err_cnt_prev;

typedef struct  {
    TBFP_COMMON_VARIABLES
}TbfpConfig_t;


typedef struct  {
    TBFP_COMMON_VARIABLES
    TBFP_RX_VARIABLES
    TBFP_TX_VARIABLES
    TBFP_CRC_VARIABLES
    TBFP_DIAG_VARIABLES
    TBFP_PARSER_VARIABLES
    TBFP_RE_TX_FSM_VARIABLES
    //uint32_t err_cnt; // in FSM too
    uint32_t err_send_cnt;
    uint32_t lack_frame_in_data;
//  TbfpParser_t parser;
    uint16_t tx_sn;
    uint16_t payload_size;
    uint32_t rx_time_stamp_ms;
    uint32_t rx_time_stamp_iteration;
    uint32_t iteration;
#ifdef HAS_TBFP_FLOW_CONTROL
    FlowCrtl_t Flow; // RxFlow
#endif /*HAS_TBFP_FLOW_CONTROL*/
    bool proc_done; /*Flag to proc outside of that software component*/
} TbfpHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* TBFP_TYPES_H */
