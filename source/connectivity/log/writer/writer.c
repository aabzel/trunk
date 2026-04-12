#include "writer.h"

#include <string.h>

#include "code_generator.h"
#include "fifo_char.h"

#ifdef HAS_UART
#include "writer_uart.h"
#endif

#ifdef HAS_MULTICORE
#include "microcontroller.h"
#include "multicore_mcal.h"
#endif

COMPONENT_GET_NODE(Writer, writer)
COMPONENT_GET_CONFIG(Writer, writer)

static bool WriterIsValidConfig(const WriterConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->inter_face.word) { res = false; }
        ifn(Config->TxArray) { res = false; }
        ifn(0 < Config->tx_array_size) { res = false; }
        ifn(Config->f_putch) { res = false; }
        ifn(Config->f_transmit) { res = false; }
        ifn(Config->f_putstr) { res = false; }
        // ifn(Config->name) { }
    }
    return res;
}

WriterHandle_t* WriterGetNodeByInterface(const InterfaceType_t interface_if) {
    WriterHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = writer_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(interface_if.word == WriterInstance[i].inter_face.word) {
            if(WriterInstance[i].valid) {
                Node = &WriterInstance[i];
                break;
            }
        }
    }
    return Node;
}

void string_putc(void* const string_stream, const char ch) {
    string_stream_t* s = (string_stream_t*)string_stream;
    if(s->pos < (s->size - 1)) {
        s->data[s->pos] = ch;
        s->pos++;
        s->data[s->pos] = '\0';
    } else {
        s->overflow = true;
    }
}

void string_puts(void* string_stream, const char* str, int32_t len) {
    int i;
    if(len < 0) {
        len = strlen(str);
    }
    for(i = 0; i < len; i++) {
        string_putc(string_stream, str[i]);
    }
}

static bool writer_init_common(const WriterConfig_t* const Config, WriterHandle_t* const Node) {
    bool res = false;
    if(Config) {
        Node->num = Config->num;
        Node->inter_face = Config->inter_face;
        Node->valid = Config->valid;
        Node->TxArray = Config->TxArray;
        Node->tx_array_size = Config->tx_array_size;
        Node->name = Config->name;
        Node->f_putch = Config->f_putch;
        Node->f_putstr = Config->f_putstr;
        Node->f_transmit = Config->f_transmit;

        Node->stream.f_putch = Config->f_putch;
        Node->stream.f_putstr = Config->f_putstr;
        res = true;
    }
    return res;
}

static bool writer_proc_one(uint8_t num) {
    bool res = false;
    WriterHandle_t* Node = WriterGetNode(num);
    if(Node) {
        res = true;
    }
    return res;
}

static bool writer_init_custom(void) {
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

WriterHandle_t* writer_set_default(void) {
    WriterHandle_t* Node = NULL;
#ifdef HAS_UART
    Node = &dbg_o;
#endif
    return Node;
}

InterfaceType_t writer_interface_get(void) {
    InterfaceType_t interf = {0};
    if(curWriterPtr) {
        interf = curWriterPtr->inter_face;
    }
    return interf;
}

bool writer_interface_set(const InterfaceType_t interface_if) {
    bool res = false;
    curWriterPtr = WriterGetNodeByInterface(interface_if);
    if(curWriterPtr) {
        res = true;
    }
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

#ifdef HAS_PC
    curWriterPtr = &std_out_o;
    res = true;
#endif

    return res;
}

#if 0

/*ostream_t stream*/
void writer_putc(void* stream_ptr, char ch) {
	if(stream_ptr){
	    ostream_t* Stream = (ostream_t*)stream_ptr;
	    if(Stream->f_putch){
            Stream->f_putch(stream_ptr,ch);
	    }
	}
}
#endif

#if 0
void writer_puts(void* stream_ptr, const char* str, int32_t len) {
    if(1 == len) {
        writer_putc(stream_ptr, *str);
    } else {
    	ostream_t* stream = (ostream_t*)stream_ptr;
    	stream->f_putstr(stream_ptr,str,len);
#if 0
    bool res = false;
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
#endif
    }
}
#endif

bool oputs(ostream_t* const ostream, const char* const str) {
    bool res = false;
    if(ostream) {
        if(str) {
            if(ostream->f_putstr) {
                size_t len = strlen(str);
                ostream->f_putstr(ostream, str, len);
                res = true;
            }
        }
    }
    return res;
}

void oputs_len(ostream_t* const ostream, const char* const str, int32_t len) {
    if(ostream) {
        if(str) {
            if(ostream->f_putstr) {
                ostream->f_putstr(ostream, str, len);
            }
        }
    }
}

void oputc(ostream_t* const ostream, char c) {
    if(ostream) {
        if(ostream->f_putch) {
            ostream->f_putch(ostream, c);
        }
    }
}

WriterHandle_t* writer_get(void) {
    WriterHandle_t* Node = curWriterPtr;
#ifdef HAS_MULTICORE
    int8_t core_num = 0;
    core_num = multicore_get_core_num();
    Node = core_to_writer(core_num);
#endif
    return Node;
}

void writer_error_callback(WriterHandle_t* stream) { stream->error_count++; }

bool writer_clean(const WriterHandle_t* stream) { return fifo_clean((FifoChar_t*)&stream->fifo); }

bool writer_half_clean(const WriterHandle_t* stream) {
    bool res = false;
    if(fifo_get_count((FifoChar_t*)&stream->fifo) < (fifo_get_size((FifoChar_t*)&stream->fifo) / 2)) {
        res = true;
    }
    return res;
}

static bool writer_init_one(uint8_t num) {
    bool res = false;
    const WriterConfig_t* Config = WriterGetConfig(num);
    if(Config) {
#ifdef HAS_WRITER_DIAG
        LOG_WARNING(SYS, "%s", WriterConfigToStr(Config));
#endif
        res = WriterIsValidConfig(Config);
        if(res) {
            WriterHandle_t* Node = WriterGetNode(num);
            if(Node) {
                res = writer_init_common(Config, Node);
                res = fifo_init(&(Node->fifo), Config->TxArray, Config->tx_array_size);
                Node->init = true;
                Node->enable = true;
                Node->busy = false;
            }
        }
    }
    return res;
}

COMPONENT_PROC_PATTERT(WRITER, WRITER, writer)
COMPONENT_INIT_PATTERT(WRITER, WRITER, writer)
