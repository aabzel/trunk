#include "writer_swd.h"

#include <stdbool.h>
#include <string.h>

#ifndef HAS_SWD
#error "Add HAS_SWD"
#endif

#ifdef HAS_FIFO
#include "fifo_char.h"
#endif

#include "sys_config.h"
#ifdef HAS_LOG
#include "log_config.h"
#endif
#include "swd_drv.h"
#include "writer_generic.h"

#define MAX_SWD_BLOCK 100U

bool swd_writer_transmit(struct generic_writer_s* writer) {
    bool res = false;
    static char data[300] = ""; /*TODO Determine min size*/
    if(writer) {
        res = fifo_pull_array(&writer->fifo, data, sizeof(data), (uint16_t*)&writer->in_transmit);
        if(false == res) {
            writer->fifo.err_cnt++;
        }
        if(0 < writer->in_transmit) {
            writer->tx_cnt += writer->in_transmit;
            if(MAX_SWD_BLOCK < writer->in_transmit) {
                writer->in_transmit = MAX_SWD_BLOCK;
            }
            if(writer->enable) {
                res = swd_write((uint8_t*)data, writer->in_transmit); /*Error here*/
            }
        }
    }
    return res;
}

static char swd_o_data[SWD_TX_ARRAY_SIZE] = {0};
generic_writer_t swd_o = {
    .stream = {
          .f_putch = writer_putc,
          .f_putstr = writer_puts
         },
    .in_transmit = 0,
    .lost_char_count = 0,
    .tx_cnt = 0,
    .error_count = 0,
#ifdef HAS_FIFO
    .fifo = {.fifoState = {.size = sizeof(swd_o_data), .start = 0, .end = 0, .count = 0, .errors = 0},
             .array = swd_o_data,
             .initDone = true},
#endif
    .f_transmit = swd_writer_transmit,
    .enable = true,
    .busy = false,
};

bool swd_writer_init(void) {
    bool res = true;
    memset(swd_o_data, 0, sizeof(swd_o_data));
    return res;
}
