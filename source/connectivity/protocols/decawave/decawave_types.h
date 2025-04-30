#ifndef DECAWAVE_TYPES_H
#define DECAWAVE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "crc16_ccitt.h"
#include "data_types.h"
#include "decawave_constants.h"
#include "protocol_types.h"
#include "sys_constants.h"
#include "uwb_if_types.h"


typedef union {
    uint8_t buff[10];
    struct {
        uint8_t preamble;
        DwcaMess_t message;
        uint16_t sequence_number;
        uint16_t destination_addr;
        uint16_t source_addr;
        uint16_t payload_size;
    } __attribute__((__packed__));
} DecaWaveHeader_t;

typedef union {
    uint8_t buff[9];
    struct {
        /*order of variable matters*/
        double distance_real_m;
        uint8_t valid;
    } __attribute__((__packed__));
} PollPayload_t;

#define DECA_WARE_COMMAN_VARIABLE                                    \
    uint32_t num;                                                    \
    uint8_t debug_led_num;                                           \
    uint8_t distance_num;                                            \
    Interfaces_t interface;                                          \
    uint32_t fir_filter_num;                                         \
    uint8_t preamble_val;                                            \
    bool valid;                                                      \
    uint64_t timer_clock; /*????*/

typedef struct {
    double t_delay_s;
    double t_loop_s;
    uint64_t t_loop;
    uint64_t t_delay;
} TwrTimings_t;

typedef struct {
    uint64_t tof;
    DoubleValue_t distance_m;
    double tof_s;
    double distance_real_m;
    double ant_delay_m;
    uint32_t update_time_stamp_ms;
    bool valid;
} PhaseTimings_t;

typedef struct {
    DECA_WARE_COMMAN_VARIABLE
    uint32_t rx_pkt_cnt;
    uint32_t tx_pkt_cnt;
    uint32_t rx_byte;
    uint32_t tx_byte;
    uint32_t rx_byte_prev;
    uint32_t tx_byte_prev;
    uint32_t len_err_cnt;
    uint32_t crc_err_cnt;
    uint32_t crc_ok_cnt;
    uint32_t crc_err_cnt_prev;
    uint32_t err_cnt;
    uint32_t calc_dist_cnt;
    U32Value_t tx_rate;
    U32Value_t rx_rate;
    uint32_t preamble_cnt;
    uint32_t spin_cnt;
    UwbRole_t role;
    uint16_t max_len;
    uint16_t min_len;
    uint16_t tx_sequence_number;
    uint16_t prev_rx_sequence_number;
    bool debug;
    uint16_t addr; /*My Addr*/
    uint16_t tag_addr;
    uint8_t tx_frame[DECAWAVE_MAX_FRAME];

    /*Group Flow Control*/
    FlowCrtl_t Flow;

    // uint32_t tx_frame_len;
    uint32_t tx_size;
    uint8_t rx_payload[DECAWAVE_MAX_PAYLOAD];
    DecaWaveHeader_t rx_header;
    DecaWaveHeader_t tx_header;
    Crc16_t crc16;
    // bool valid_distance;
    // double distance_real_m;
    TwrTimings_t initiator;
    TwrTimings_t responder;
    DoubleValue_t avarage_distance_m;
    PhaseTimings_t phase1;
    PhaseTimings_t phase2;
    PhaseTimings_t final;
    double distance_filtered_real_m;

} DecaWaveHandle_t;

typedef struct {
    DECA_WARE_COMMAN_VARIABLE
    double ant_delay_m;
    double phase1_ant_delay_m;
    double phase2_ant_delay_m;
    uint16_t addr_def;
} DecaWaveConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* DECAWAVE_TYPES_H */
