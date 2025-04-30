#include "writer_stdout.h"

#include <stdbool.h>
#include <stdio.h>

#include "fifo_char.h"
#include "writer_generic.h"

#define MAX_STDOUT_BLOCK 800U

static char std_out_o_data[STDOUT_TX_ARRAY_SIZE];
generic_writer_t std_out_o = {
    .stream = {writer_putc, writer_puts},
    .in_transmit = 0,
    .lost_char_count = 0,
    .tx_cnt = 0,
    .error_count = 0,
    .fifo = {.fifoState = {.size = sizeof(std_out_o_data), .start = 0, .end = 0, .count = 0, .errors = 0},
             .array = std_out_o_data,
             .initDone = true},
    .f_transmit = stdout_writer_transmit,
    .enable = true,
};

bool stdout_writer_transmit(struct generic_writer_s* writer) {
    bool res = false;
    char data[3000] = ""; /*TODO Determine min size*/
    res = fifo_pull_array(&writer->fifo, data, sizeof(data), (uint16_t*)&writer->in_transmit);
    if(false == res) {
        writer->fifo.err_cnt++;
    }
    if(0 < writer->in_transmit) {
        writer->tx_cnt += writer->in_transmit;
        // if(MAX_STDOUT_BLOCK < writer->in_transmit) {
        //   writer->in_transmit = MAX_STDOUT_BLOCK;
        // }
        if(writer->enable) {
            uint32_t i = 0;
            for(i = 0; i < writer->in_transmit; i++) {
                printf("%c", data[i]);
            }
        }
    }
    return res;
}
