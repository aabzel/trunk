#ifndef SRC_UART_WRITER_H
#define SRC_UART_WRITER_H

#include "writer_types.h"

#define DBG_TX_ARRAY_SIZE (200U) // 60+

#ifndef HAS_UART
#error "Add HAS_UART"
#endif

//#define DBG_UART_STREAM (&dbg_o.s)

bool uart_writer_init(void);
bool uart_writer_transmit(void* base);


void uart1_putc(void* stream_ptr, char ch);
void uart1_puts(void* stream_ptr, const char* str, int32_t len);

void uart2_putc(void* stream_ptr, char ch);
void uart2_puts(void* stream_ptr, const char* str, int32_t len);

void uart3_putc(void* stream_ptr, char ch);
void uart3_puts(void* stream_ptr, const char* str, int32_t len);

void uart5_putc(void* stream_ptr, char ch);
void uart5_puts(void* stream_ptr, const char* str, int32_t len);

void uart6_putc(void* stream_ptr, char ch);
void uart6_puts(void* stream_ptr, const char* str, int32_t len);


#endif /* SRC_UART_WRITER_H */
