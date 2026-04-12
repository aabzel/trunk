#include "writer_stdout.h"

#include <stdio.h>
#include <string.h>

#include "array_diag.h"
#include "fifo_char.h"
#include "log.h"
#include "std_includes.h"

#define MAX_STDOUT_BLOCK 800U

static uint8_t std_out_o_data[STDOUT_TX_ARRAY_SIZE] = {0};

WriterHandle_t std_out_o = {
    .stream = {stdout_putc, stdout_puts},
    .in_transmit = 0,
    .lost_char_count = 0,
    .tx_cnt = 0,
    .error_count = 0,
    .fifo = {.fifoState = {.size = sizeof(std_out_o_data), .start = 0, .end = 0, .count = 0, .errors = 0},
             .array = std_out_o_data,
             .init_done = true},
    .f_transmit = stdout_writer_transmit,
    .enable = true,
};

/*ostream_t stream*/
void stdout_putc(void* stream_ptr, char ch) { printf("%c", ch); }

void stdout_puts(void* stream_ptr, const char* str, int32_t len) {
    if(str) {
        if(len) {
            uint32_t i = 0;
            for(i = 0; i < len; i++) {
                printf("%c", str[i]);
            }
        }
    }
}

// bool stdout_writer_transmit(struct sWriterHandle_t* Node) {
bool stdout_writer_transmit(void* base) {
    bool res = false;
    WriterHandle_t* Node = (WriterHandle_t*)base;
    if(Node) {
        strcpy((char*)Node->data, "");
        res = fifo_pull_array(&Node->fifo, Node->data, 200, &Node->in_transmit);
        if(false == res) {
            Node->fifo.err_cnt++;
        }
        if(0 < Node->in_transmit) {
            Node->tx_cnt += Node->in_transmit;
            if(Node->enable) {
                stdout_puts(NULL, (char*)Node->data, Node->in_transmit);
                res = true;
            }
        }
    }
    return res;
}

bool stdio_send(const uint8_t* const array, const uint32_t size) {
    bool res = false;
#ifdef HAS_ARRAY_DIAG
    cli_printf("%s", ArrayToStr(array, size));
    res = true;
#endif
    return res;
}

#if 0

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
#endif
