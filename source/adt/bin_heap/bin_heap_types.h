#ifndef BIN_HEAP_TYPES_H
#define BIN_HEAP_TYPES_H

#include "std_includes.h"

#define BIN_HEAP_CONNON_VARIABLES                      \
    int32_t* array;                                    \
    uint32_t capacity;                                 \
    char* name;                                        \
    uint8_t num;                                       \
    bool valid;

typedef struct {
    BIN_HEAP_CONNON_VARIABLES
}BinHeapConfig_t;

typedef struct {
    BIN_HEAP_CONNON_VARIABLES
    bool init;
    uint32_t size;
}BinHeapHandle_t;



#endif /* BIN_HEAP_TYPES_H */
