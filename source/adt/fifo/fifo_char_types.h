#ifndef FIFO_CHAR_TYPES_H
#define FIFO_CHAR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "std_includes.h"
#include "fifo_index.h"
#include "fifo_char_dep.h"

#define ESCAPE_CHAR ((uint8_t)0x1B)
#define ESCAPE_SQ_BR_OP_CHAR ((uint8_t)0x5B)

typedef struct {
    uint32_t err_cnt;
    bool init_done;
    fifo_index_info_t fifoState; // not volatile!
    uint8_t* array;
} FifoChar_t;


#ifdef __cplusplus
}
#endif

#endif /* FIFO_CHAR_TYPES_H */
