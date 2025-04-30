#include "writer_uart.h"

#include <stdbool.h>
#include <string.h>

#ifndef HAS_UART
#error "Add HAS_UART"
#endif

#include "fifo_char.h"
#include "sys_config.h"
#ifdef HAS_LOG
#include "log_config.h"
#endif
#include "uart_mcal.h"
#include "writer_generic.h"

//#define MAX_UART_BLOCK 100U
static char DbgOutData[DBG_TX_ARRAY_SIZE] = {0};

generic_writer_t dbg_o = {
    .stream = {.f_putch = writer_putc, .f_putstr = writer_puts},
    .in_transmit = 0,
    .lost_char_count = 0,
    .tx_cnt = 0,
    .error_count = 0,
    .fifo = {.fifoState = {.size = sizeof(DbgOutData), .start = 0, .end = 0, .count = 0, .errors = 0},
             .array = DbgOutData,
             .initDone = true},
    .f_transmit = uart_writer_transmit,
    .enable = true,
    .busy = false,
    .data = "",
};

bool uart_writer_transmit(generic_writer_t* writer) {
    bool res = false;
    if(writer) {
        strcpy(writer->data, "");
        res = fifo_pull_array(&writer->fifo, writer->data, 200, (uint16_t*)&writer->in_transmit);
        if(false == res) {
            writer->fifo.err_cnt++;
        }
        if(0 < writer->in_transmit) {
            writer->tx_cnt += writer->in_transmit;
            if(writer->enable) {
#warning TODO set CLI config
                res = uart_mcal_send(LOG_UART_NUM, (uint8_t*)writer->data, writer->in_transmit);
            }
        }
    }
    return res;
}

bool uart_writer_init(void) {
    bool res = true;
    memset(DbgOutData, 0, sizeof(DbgOutData));
    return res;
}
