#include "light_navigator_config.h"

#include "data_utils.h"
#include "light_navigator_types.h"

const LightNavigatorConfig_t LightNavigatorConfig[] = {
    {
        .num = 1,
        .rtc_num = 1,
        .trigger_num = 1,
        .light_sensor_num = 1,
        .valid = true,
        .filename = "LiRaw.csv",
        .day_light_filename = "DayLig.txt",
        .coordinate_filename = "Coordi.txt",
    },
    {
        .num = 2,
        .rtc_num = 1,
        .trigger_num = 2,
        .light_sensor_num = 2,
        .valid = true,
        .filename = "LiRaw2.csv",
        .day_light_filename = "DayLig2.txt",
        .coordinate_filename = "Coordi2.txt",
    },
};

LightNavigatorHandle_t LightNavigatorInstance[] = {
    {
        .num = 1,
        .valid = true,
        .init = false,
    },
    {
        .num = 2,
        .valid = true,
        .init = false,
    },
};

COMPONENT_GET_CNT(LedMono, light_navigator)

