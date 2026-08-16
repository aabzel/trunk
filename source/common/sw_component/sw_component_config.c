#include "sw_component_config.h"

#include "data_utils.h"

const SwComponentConfig_t SwComponentConfig[] = {
    {
        .num = 1,
        .valid = true,
        .name = "SW_COMPONENT1",
    },

    {
        .num = 2,
        .valid = true,
        .name = "SW_COMPONENT2",
    },
};

SwComponentHandle_t SwComponentInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },

};

COMPONENT_GET_CNT(SwComponent, sw_component)


