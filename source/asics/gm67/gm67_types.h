#ifndef GM67_TYPES_H
#define GM67_TYPES_H

#include "std_includes.h"
#include "gm67_const.h"
#include "fifo_char.h"

#define GM67_COMMON_VARIABLES            \
    uint8_t num;                         \
    uint8_t uart_num;                    \
    uint8_t* RxArray;                    \
    uint32_t rx_array_size;              \
    bool valid;

typedef struct {
    GM67_COMMON_VARIABLES
    char* name;
} Gm67Config_t;

typedef struct {
    GM67_COMMON_VARIABLES
    uint32_t rx_cnt;
    uint32_t i;
    uint32_t rx_frame_cnt;
    FifoChar_t RxFifo;
    uint32_t rx_time_ms;
    bool new_frame;
    bool unptoc_frame;
    uint8_t DataCur[GM_IN_BUFF_SIZE];
    uint32_t rx_size;
    uint8_t DataFixed[GM_IN_BUFF_SIZE];
} Gm67Handle_t;

#endif /* GM67_TYPES_H */
