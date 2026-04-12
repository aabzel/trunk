#include "dwt_config.h"

#include "data_utils.h"
#include "microcontroller_const.h"

const DwtConfig_t DwtConfig[] = {
    {
        .num = 1,
        .valid = true,
        .counter_freq = 168000000,
        .DWTx = DWT  ,
        .name = "DWT"  ,
    },
};

DwtHandle_t DwtInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Dwt, dwt)
