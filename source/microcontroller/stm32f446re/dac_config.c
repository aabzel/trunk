#include "dac_config.h"

#include "data_utils.h"

const DacConfig_t SECTION_CFG_DATA DacConfig[] = {
    {
        .num = 1,
        .name = "DAC1",
        .valid = true,
        .irq_priority = 3,
        .interrupt_on = true,
    },
};

DacHandle_t DacInstance[] = {
    {        .num = 1,        .valid = true,    },
};

COMPONENT_GET_CNT(Dac, dac)

