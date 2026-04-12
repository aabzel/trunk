#include "writer_uart.h"

#include <string.h>

#ifndef HAS_UART
#error "Add HAS_UART"
#endif

#include "fifo_char.h"
#include "std_includes.h"
#include "sys_config.h"
#include "uart_mcal.h"
#include "writer.h"
#ifdef HAS_LOG
#include "log.h"
#endif

/*ostream_t stream*/
void uart1_putc(void* stream_ptr, char ch) { uart_mcal_send(1, (uint8_t*)&ch, 1); }
void uart2_putc(void* stream_ptr, char ch) { uart_mcal_send(2, (uint8_t*)&ch, 1); }
void uart3_putc(void* stream_ptr, char ch) { uart_mcal_send(3, (uint8_t*)&ch, 1); }
void uart5_putc(void* stream_ptr, char ch) { uart_mcal_send(5, (uint8_t*)&ch, 1); }
void uart6_putc(void* stream_ptr, char ch) { uart_mcal_send(6, (uint8_t*)&ch, 1); }

void uart1_puts(void* stream_ptr, const char* str, int32_t len) {
    if(str) {
        if(len) {
            uart_mcal_send(1, (uint8_t*)str, len);
        }
    }
}

void uart2_puts(void* stream_ptr, const char* str, int32_t len) {
    if(str) {
        if(len) {
            uart_mcal_send(2, (uint8_t*)str, len);
        }
    }
}

void uart3_puts(void* stream_ptr, const char* str, int32_t len) {
    if(str) {
        if(len) {
            uart_mcal_send(3, (uint8_t*)str, len);
        }
    }
}

void uart5_puts(void* stream_ptr, const char* str, int32_t len) {
    if(str) {
        if(len) {
            uart_mcal_send(5, (uint8_t*)str, len);
        }
    }
}

void uart6_puts(void* stream_ptr, const char* str, int32_t len) {
    if(str) {
        if(len) {
            uart_mcal_send(6, (uint8_t*)str, len);
        }
    }
}

// bool uart_writer_transmit(struct sWriterHandle_t* Node) {
bool uart_writer_transmit(void* base) {
    bool res = false;
    WriterHandle_t* Node = (WriterHandle_t*)base;
    if(Node) {
        strcpy((char*)Node->data, "");
        uint32_t out_len = 0;
        Node->in_transmit = 0;
        res = fifo_pull_array(&Node->fifo, Node->data, 200, &out_len);
        if(false == res) {
            Node->fifo.err_cnt++;
        } else {
            Node->in_transmit = out_len;
        }
        if(0 < Node->in_transmit) {
            Node->tx_cnt += Node->in_transmit;
            if(Node->enable) {
                uint8_t uart_num = UartInterfaceToNum(Node->inter_face);
                res = uart_mcal_send(uart_num, (uint8_t*)Node->data, Node->in_transmit);
            }
            Node->in_transmit = 0;
        }
    }
    return res;
}

bool uart_writer_init(void) {
    bool res = true;
    // memset(DbgOutData, 0, sizeof(DbgOutData));
    return res;
}
