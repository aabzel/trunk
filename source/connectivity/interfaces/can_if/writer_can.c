#include "writer_can.h"

#include <stdbool.h>

#include "fifo_char.h"
#include "sys_config.h"
#include "can_drv.h"
#ifndef HAS_CAN
#error "CAN HW is not determined"
#endif

#define MAX_CAN_BLOCK 100U

static char dbg_o_data[CAN_TX_ARRAY_SIZE];
generic_writer_t can_o = {
    .s = {writer_putc, writer_puts},
    .in_transmit = 0,
    .lost_char_count = 0,
    .total_char_count = 0,
    .error_count = 0,
    .fifo = {.fifoState = {.size = sizeof(dbg_o_data), .start = 0, .end = 0, .count = 0, .errors = 0},
             .array = dbg_o_data,
             .initDone = true},
    .f_transmit = can_writer_transmit,
    .enable = true,
};

bool can_writer_transmit(struct generic_writer_s* writer) {
    bool res = false;
    char data[300] = ""; /*TODO Determine min size*/
    res = fifo_pull_array(&writer->fifo, data, sizeof(data), (uint16_t*)&writer->in_transmit);
    if(false == res) {
        writer->fifo.err_cnt++;
    }
    if(0 < writer->in_transmit) {
        writer->total_char_count += writer->in_transmit;
        if(MAX_CAN_BLOCK < writer->in_transmit) {
            writer->in_transmit = MAX_CAN_BLOCK;
        }
        if(writer->enable) {
            res = can_send((uint8_t*)data, writer->in_transmit); /*Error here*/
        }
    }
    return res;
}
