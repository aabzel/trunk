#ifndef DS_TWR_TYPES_H
#define DS_TWR_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "ds_twr_const.h"
#include "system_types.h"
#include "fifo_char.h"
#include "data_types.h"
#ifdef HAS_UWB
#include "uwb_if_types.h"
#endif

#ifndef HAS_DS_TWR
#error "+HAS_DS_TWR"
#endif

typedef struct {
    uint64_t t_delay ;
    uint64_t t_loop ;
    uint64_t tx_stamp;
    uint64_t rx_stamp;
} TimesResponder_t;

typedef union {
    uint8_t buff[16];
    struct {
        uint64_t t_delay;
        uint64_t t_loop;
    };
} ResponderTiming_t;

typedef struct {
    double t_delay_s;
    double t_loop_s;
    uint64_t t_loop ;
    uint64_t t_delay ;
    uint64_t tx_stamp;
    uint64_t rx_stamp;
} TimesInitiatior_t;

#define TWR_COMMON_VARIABLES    \
    Interfaces_t interface;     \
    uint8_t num;                \
    uint8_t decawave_num;       \
    uint64_t timer_clock;       \
    bool valid;                 \
    uint16_t known_nodes_cnt;
    //double ant_delay_m;

typedef struct {
    TWR_COMMON_VARIABLES
    uint16_t* known_nodes;
}DsTwrConfig_t;


#define UWB_MAX_IDS 4
typedef struct {
	TWR_COMMON_VARIABLES
    TimesInitiatior_t initiator;
    TimesResponder_t responder;
    uint32_t proc_cnt;
    uint32_t iter_cnt; /*number of start or rx poll */
    uint32_t spin_cnt;
    uint32_t err_cnt;
    DoubleValue_t offset_m;
    bool poll_arrived;
    bool respond_arrive;
    bool respond_sent;
    bool init;
    bool share_timing;
    bool continuous;
    bool resp_poll_send;
    DsTwrEvent_t event;
    uint64_t tx_stamp;
    uint64_t rx_stamp;
    uint32_t start_ms;
    uint16_t tag_id;
    DsTwrInput_t cur_input;
    DsTwrInput_t prev_input;
    DsTwrState_t state;
    DsTwrState_t prev_state;
    char InFifoHeap[5];
    char text[90]; /*Just for DiagStr*/
    FifoChar_t InputFifo;
    uint16_t cur_id_index;
#ifdef HAS_UWB
    UwbIdInfo_t IdInfo[UWB_MAX_IDS];
#endif
    uint64_t id;
} DsTwr_t;


#endif /* DS_TWR_TYPES_H */
