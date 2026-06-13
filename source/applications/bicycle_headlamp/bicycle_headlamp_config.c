#include "bicycle_headlamp_config.h"

#include "data_utils.h"

const BicycleHeadLampConfig_t BicycleHeadLampConfig[] = {
    {
        .ir_samsung_num = 1,
        .smooth_lamp_num = 1,
        .num = 1,
        .mult = 0.02,
        .limit_up = 100.0,
        .limit_down= 0.0,
        .valid = true,
        .name = "BICYCLE_HEADLAMP1",
    },
};


BicycleHeadLampHandle_t BicycleHeadLampInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(BicycleHeadLamp, bicycle_headlamp)


