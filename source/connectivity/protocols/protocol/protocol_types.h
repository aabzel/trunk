#ifndef PROTOCOL_TYPES_H
#define PROTOCOL_TYPES_H

#include <stdint.h>

#include "protocol_const.h"

typedef struct {
    uint16_t prev_s_num; /*Prev Rx SN*/
    uint16_t cur_sn; /*RxSn*/
    uint32_t cur; /*Current flow*/
    uint32_t prev_flow; /*previous current flow*/
    uint32_t maximum_continuous; /*maximum continuous flow*/
    uint32_t order_err;
    uint32_t err_cnt;
    uint32_t ok_cnt;
    uint32_t lost_rx_frames;
    uint32_t total_lost_rx_frames;
    uint32_t torn_cnt;
    uint32_t torn_cnt_prev;
    uint32_t duplicate_cnt;
    bool torn; /*Torn Flow*/
}FlowCrtl_t;

// Packets/Bytes
typedef struct {
    uint32_t tx;
    uint32_t rx;
}TrafficDir_t;

typedef struct {
    uint32_t addr;
    uint8_t size;
}Addr32Mask_t;


#endif /* PROTOCOL_TYPES_H */
