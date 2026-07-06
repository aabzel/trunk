#ifndef ADT_INIT_H
#define ADT_INIT_H

#include <stdbool.h>


#ifdef HAS_HASH_TABLE
#include "hash_table.h"
#define HASH_TABLE_INIT {.init_function=hash_table_mcal_init, .name="HashTable",},
#else
#define HASH_TABLE_INIT
#endif

#ifdef HAS_HASH_TABLE_S8
#include "hash_table_s8.h"
#define HASH_TABLE_S8_INIT {.init_function=hash_table_s8_mcal_init, .name="HashTableS8",},
#else
#define HASH_TABLE_S8_INIT
#endif

#ifdef HAS_HISTOGRAM
#include "histogram.h"
#define HISTOGRAM_INIT {.init_function=histogram_mcal_init, .name="histogram",},
#else
#define HISTOGRAM_INIT
#endif

#ifdef HAS_BIT_FIFO
#include "bit_fifo_mcal.h"
#define BIT_FIFO_INIT {.init_function=bit_fifo_mcal_init, .name="BitFifo",},
#else
#define BIT_FIFO_INIT
#endif


#ifdef HAS_MAX_HEAP
#include "max_heap.h"
#define MAX_HEAP_INIT {.init_function=max_heap_mcal_init, .name="MaxHaep",},
#else
#define MAX_HEAP_INIT
#endif

#ifdef HAS_MIN_HEAP
#include "min_heap.h"
#define MIN_HEAP_INIT {.init_function=min_heap_mcal_init, .name="MinHaep",},
#else
#define MIN_HEAP_INIT
#endif



#define ADT_INIT            \
    HASH_TABLE_S8_INIT      \
    BIT_FIFO_INIT           \
    HASH_TABLE_INIT         \
    HISTOGRAM_INIT          \
    MAX_HEAP_INIT           \
    MIN_HEAP_INIT

#endif /*ADT_INIT_H*/
