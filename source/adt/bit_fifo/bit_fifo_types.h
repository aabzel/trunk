#ifndef BIT_FIFO_TYPES_H
#define BIT_FIFO_TYPES_H

#include "std_includes.h"
#include "bit_fifo_const.h"



#define BIT_FIFO_COMMON_VARIABLES                      \
    char* name;                                        \
    uint8_t* buffer;     /*pointer to user-provided byte buffer (non-const because we write into it)*/                              \
    uint32_t size;  /*total bits the buffer can hold (buffer_bytes * 8)*/                          \
    uint8_t num;                                       \
    bool valid;

typedef struct {
    BIT_FIFO_COMMON_VARIABLES
}BitFifoConfig_t;


typedef struct {
    BIT_FIFO_COMMON_VARIABLES
    uint32_t capacity_bits;  /*total bits the buffer can hold (buffer_bytes * 8)*/                          \
    bool     init;             // indicates whether the FIFO has been initialized
    uint32_t write_bit;        // absolute write position (global bit counter)
    uint32_t read_bit;         // absolute read position (global bit counter)
    uint32_t overflow_cnt;     // number of bits lost due to overwriting
} BitFifoHandle_t;





#endif /* BIT_FIFO_TYPES_H */
