#ifndef TBFP_CONFIG_H
#define TBFP_CONFIG_H

#include "std_includes.h"
#include "tbfp_types.h"

typedef enum {
    TBFP_NUM_CAN0 = 1,
    TBFP_NUM_CAN1 = 2,
    TBFP_NUM_LOOPBACK = 3,
    TBFP_NUM_BLACK_HOLE = 4,
    TBFP_NUM_UNDEF = 0,
} TbfpLegalNums_t;

extern const TbfpConfig_t TbfpConfig[];
extern TbfpHandle_t TbfpInstance[];

uint32_t tbfp_get_cnt(void);

#endif /* TBFP_CONFIG_H */
