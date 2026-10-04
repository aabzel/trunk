#include "dwt_config.h"

#include "data_utils.h"
#include "microcontroller_const.h"

const DwtConfig_t DwtConfig[] = {
    {
        .num = DWT_NUM_CORE0,
        .valid = true,
        .counter_freq = 168000000,
        .DWTx = DWT  ,
        .name = "DWT"  ,
    },
};

DwtHandle_t DwtInstance[] = {
    {
        .num = DWT_NUM_CORE0,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Dwt, dwt)
