#ifndef IQUEUE_CONFIG_H
#define IQUEUE_CONFIG_H

#include "std_includes.h"
#include "iqueue_types.h"

typedef enum {
    IQUEUE_NUN_U8_5 = 1,
    IQUEUE_NUN_S16_6 = 2,
    IQUEUE_NUN_CAN1 = 3,
    IQUEUE_NUN_CAN2 = 4,
    IQUEUE_NUN_UNDEF = 0,
}iQueueLegalIndxe_t;

extern const iQueueConfig_t iQueueConfig[];
extern iQueueHandle_t iQueueInstance[];

uint32_t iqueue_get_cnt(void);

#endif /* IQUEUE_CONFIG_H */
