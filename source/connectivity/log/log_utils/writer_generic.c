#include "writer_generic.h"

#include <stdbool.h>
#include <string.h>

#include "fifo_char.h"
#include "writer_config.h"

#ifndef HAS_STREAM
#error "+HAS_STREAM"
#endif

bool writer_init(void) {
    bool res = false;
    curWriterPtr = NULL;

#ifdef HAS_HID
    // curWriterPtr=&usb_hid_o;
    res = true;
#endif

#ifdef HAS_SWD
    curWriterPtr = &swd_o;
    res = true;
#endif

#ifdef HAS_X86_64
    curWriterPtr = &std_out_o;
    res = true;
#endif

#ifdef HAS_UART
    curWriterPtr = &dbg_o;
    res = true;
#endif
    return res;
}

bool writer_default(void) {
    bool res = false;
    curWriterPtr = NULL;

#ifdef HAS_SWD
    curWriterPtr = &swd_o;
    res = true;
#endif

#ifdef HAS_UART
    curWriterPtr = &dbg_o;
    res = true;
#endif

    return res;
}

void writer_putc(void* stream_ptr, char ch) {
    generic_writer_t* stream = (generic_writer_t*)stream_ptr;
    if(false == stream->busy) {
        stream->busy = true;
        bool res = fifo_push(&stream->fifo, ch);
        if(false == res) {
            stream->lost_char_count++;
        } else {
            stream->f_transmit(stream);
        }
        stream->busy = false;
    }
}

void writer_puts(void* stream_ptr, const char* str, int32_t len) {
    bool res = false;
    if(1 == len) {
        writer_putc(stream_ptr, *str);
    } else {
        generic_writer_t* stream = (generic_writer_t*)stream_ptr;
        if(false == stream->busy) {
            stream->busy = true;
            if(len < 0) {
                len = strlen(str);
            }

            res = fifo_push_array((FifoChar_t*)&stream->fifo, (char*)str, (FifoIndex_t)len);
            if(false == res) {
                stream->fifo.err_cnt++;
            }

            FifoIndex_t size = fifo_get_count(&stream->fifo);
            if(0 < size) {
                stream->f_transmit(stream); /*Error*/
            }

            stream->busy = false;
        }
    }
}

void writer_error_callback(generic_writer_t* stream) { stream->error_count++; }

bool writer_clean(const generic_writer_t* stream) { return fifo_clean((FifoChar_t*)&stream->fifo); }

bool writer_half_clean(const generic_writer_t* stream) {
    bool res = false;
    if(fifo_get_count((FifoChar_t*)&stream->fifo) < (fifo_get_size((FifoChar_t*)&stream->fifo) / 2)) {
        res = true;
    }
    return res;
}
