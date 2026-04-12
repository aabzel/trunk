#ifndef SRC_STDOUT_WRITER_H
#define SRC_STDOUT_WRITER_H

#include "writer_types.h"

#define STDOUT_TX_ARRAY_SIZE 30000U

#ifndef HAS_X86_64
#error "This code only for the DeskTop"
#endif

extern WriterHandle_t std_out_o;
#define DBG_STDOUT_STREAM (&std_out_o.s)

bool stdio_send(const uint8_t* const array, const uint32_t size);
void stdout_putc(void* stream_ptr, char ch);
void stdout_puts(void* stream_ptr, const char* str, int32_t len);
bool stdout_writer_transmit(void* base);

#endif /* SRC_STDOUT_WRITER_H */
