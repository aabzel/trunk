#ifndef STRING_WRITER_H
#define STRING_WRITER_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>

#include "ostream.h"


typedef struct {
    ostream_t s;
    char* data;
    const uint16_t size;
    uint16_t pos;
    bool overflow;
} string_stream_t;

#define STRING_STREAM(str)                                                                                             \
    { {string_putc, string_puts}, (str), sizeof(str), 0, false }

void string_putc(void* _s, char ch);
void string_puts(void* _s, const char* str, int32_t len);

#ifdef __cplusplus
}
#endif

#endif /* STRING_WRITER_H */
