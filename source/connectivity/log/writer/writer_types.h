#ifndef WRITER_TYPES_H
#define WRITER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "interfaces_types.h"
#include "writer_const.h"
#include "fifo_char.h"

typedef void (*PutCharFoo)(void* f_data, char ch);
typedef void (*PutStringFoo)(void* f_data, const char* s, int32_t len);
typedef bool (*fTransmit)(void * base);

#define WRITER_STREAM_VARIABLE                                          \
    void (*f_putch)(void* f_data, char ch);                             \
    void (*f_putstr)(void* f_data, const char* s, int32_t len);


typedef struct {
    WRITER_STREAM_VARIABLE
} ostream_t;

typedef struct {
    ostream_t s;
    char* data;
    const uint16_t size;
    uint16_t pos;
    bool overflow;
} string_stream_t;


#define WRITER_GENERIC_VARIABLE                                \
    volatile void* instance;                                   \
    ostream_t stream;                                          \
    uint32_t in_transmit; /* tx_cnt_byte*/                     \
    int64_t lost_char_count;                                   \
    int64_t tx_cnt;                                            \
    int64_t error_count;                                       \
    FifoChar_t fifo;                                           \
    bool enable;                                               \
    bool busy;                                                 \
    uint8_t data[300] ; /*TODO Determine min size*/

#define WRITER_COMMON_VARIABLE         \
    WRITER_STREAM_VARIABLE             \
    uint8_t num;                       \
    InterfaceType_t inter_face;        \
    bool (*f_transmit)(void * Node);   \
    uint8_t* TxArray;                  \
    char* name;                        \
    uint32_t tx_array_size;            \
    bool valid;


typedef struct {
    WRITER_COMMON_VARIABLE
}WriterConfig_t;


typedef struct sWriterHandle_t {
    WRITER_COMMON_VARIABLE
    WRITER_GENERIC_VARIABLE
    bool init;
}WriterHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* WRITER_TYPES_H */
