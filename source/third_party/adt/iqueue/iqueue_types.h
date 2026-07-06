#ifndef IQUEUE_TYPES_H
#define IQUEUE_TYPES_H

#include "std_includes.h"
#include "interfaces_types.h"
#include "iqueue_const.h"
#include "lib_iqueue.h"
#include "storage_const.h"

//StorageType_t type;

#define IQUEUE_COMMON_VARIABLES                  \
    void* storage;                               \
    InterfaceType_t Interface;                   \
    uint32_t element_cnt;                        \
    uint32_t element_size;                       \
    iqueue_t * pHandle;                          \
    char* name;                                  \
    uint8_t num;                                 \
    bool valid;

typedef struct {
    IQUEUE_COMMON_VARIABLES
}iQueueConfig_t;

typedef struct {
    IQUEUE_COMMON_VARIABLES
    bool init;
    uint32_t spin;
}iQueueHandle_t;


#endif /* IQUEUE_TYPES_H */
