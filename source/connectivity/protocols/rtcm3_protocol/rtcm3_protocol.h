#ifndef RTCM3_PROTOCOL_H
#define RTCM3_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "data_utils.h"
#include "protocol_common.h"
#include "system.h"

#define RTCM3_PREAMBLE 0xD3
#define RTCM3_HEADER_SIZE 3U
#define RTCM3_CRC24_SIZE 3U
#define RTCM3_OVERHEAD (RTCM3_CRC24_SIZE + RTCM3_HEADER_SIZE)
#define RTCM3_RX_MAX_PAYLOAD_SIZE (1030U)
#define RTCM3_RX_MAX_FRAME_SIZE (RTCM3_RX_MAX_PAYLOAD_SIZE + RTCM3_OVERHEAD)
#define RTCM_IF_CNT 4 /*LoRa RS232 UART1*/

#define RTCM3_INX_PREAMBLE 0
#define RTCM3_INX_LEN 1
#define RTCM3_INX_PAYLOAD 3

/*TODO: replase with RxState_t*/
#if 0
typedef enum  {
    RTCM3_WAIT_PREAMBLE = 0U,
    RTCM3_WAIT_LEN = 1U,
    RTCM3_WAIT_PAYLOAD = 2U,
    RTCM3_WAIT_CRC = 3U,
    RTCM3_RX_DONE = 4U
} Rtcm3ProtState_t;
#endif
typedef struct  {
    uint16_t len : 10; /*Big or Little endian*/
    uint16_t res : 6;
} Rtcm3LenBit_t;

typedef union  {
    uint16_t len16;
    uint8_t len8[2];
    Rtcm3LenBit_t field;
} __attribute__((__packed__)) Rtcm3Len_t;

typedef struct  {
    uint8_t preamble;
    Rtcm3Len_t ex_len;
} __attribute__((__packed__)) Rtcm3Header_t;

typedef struct  {
    uint32_t rx_pkt_cnt;
    uint32_t err_tx_cnt;
    uint32_t err_tx_cnt_prev;
    uint32_t rx_rx_pkt_cnt;
    uint32_t lost_pkt_cnt[IF_CNT];
    uint32_t uart_lost_pkt_cnt;
    uint32_t crc_err_cnt;
    uint32_t crc_err_cnt_prev;
    uint32_t load_len;
    uint32_t err_cnt;
#ifdef HAS_DEBUG
    uint32_t diff_rx_pkt_cnt;
    uint32_t prev_rx_pkt_cnt;
    uint32_t preamble_cnt;
    uint16_t max_len;
    uint16_t min_len;
#endif
    U32Value_t tx_rate;
    U32Value_t rx_rate;
    uint32_t rx_byte;
    uint32_t rx_byte_prev;
    uint32_t tx_byte;
    uint32_t tx_byte_prev;
    Rtcm3Len_t exp_len;
    uint32_t read_crc;
    uint16_t ack_cnt;
    RxState_t rx_state;
    uint32_t jumbo_frame_cnt;
    uint8_t rx_frame[RTCM3_RX_MAX_FRAME_SIZE];
    uint8_t fix_frame[RTCM3_RX_MAX_FRAME_SIZE];
    Interfaces_t interface;
    bool forwarding[IF_CNT]; // TODO make bit field
} Rtcm3Protocol_t;

extern Rtcm3Protocol_t Rtcm3Protocol[IF_CNT];

bool rtcm3_check(void);
bool rtcm3_calc_byte_rate(void);
bool rtcm3_generate_frame(uint8_t* arr, uint32_t size);
bool rtcm3_reset_rx(Rtcm3Protocol_t* instance, RxState_t rx_state);
bool rtcm3_protocol_init(Rtcm3Protocol_t* instance, Interfaces_t interface, bool lora_fwd);
bool rtcm3_proc_byte(Rtcm3Protocol_t* instance, uint8_t rx_byte);
bool is_rtcm3_frame(uint8_t* arr, uint16_t len);
bool rtcm3_proc_array(uint8_t* const payload, uint32_t size, Interfaces_t interface);

#ifdef __cplusplus
}
#endif

#endif /* RTCM3_PROTOCOL_H */
