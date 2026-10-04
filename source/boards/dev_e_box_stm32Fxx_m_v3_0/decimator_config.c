#include "decimator_config.h"

#include "data_utils.h"

const DecimatorConfig_t DecimatorConfig[] = {
    {
        .num = 1,
        .name = "4fs",
        .valid = true,
        .samples_per_bit = 40,
    },
};

DecimatorHandle_t DecimatorInstance[] = {
     {.num = 1, .valid = true,},
};

COMPONENT_GET_CNT(Decimator, decimator)
