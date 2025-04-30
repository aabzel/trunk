#ifndef WRITER_GENERIC_H
#define WRITER_GENERIC_H

#include "std_includes.h"

#ifdef HAS_FIFO
#include "fifo_char.h"
#include "fifo_index.h"
#endif /*HAS_FIFO*/

#ifdef HAS_STREAM
#include "oprintf.h"
#endif

struct generic_writer_s;

#ifndef HAS_STREAM
#error "+HAS_STREAM"
#endif

bool writer_default(void);
bool writer_init(void);

typedef struct generic_writer_s {
    ostream_t stream;
    uint16_t in_transmit; // tx_cnt_byte
    int64_t lost_char_count;
    int64_t tx_cnt;
    int64_t error_count;
#ifdef HAS_FIFO
    FifoChar_t fifo;
#endif
    bool (*f_transmit)(struct generic_writer_s* writer);
    volatile void* instance;
    bool enable;
    bool busy;
    char data[300] ; /*TODO Determine min size*/
} generic_writer_t;

void writer_tx_callback(generic_writer_t* s);
void writer_error_callback(generic_writer_t* s);
void writer_putc(void* _s, char ch);
void writer_puts(void* _s, const char* s, int32_t len);
bool writer_clean(const generic_writer_t* s);
bool writer_half_clean(const generic_writer_t* s);

#endif /* WRITER_GENERIC_H */
