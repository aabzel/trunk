#include "light_navigator_config.h"

#ifdef HAS_I2C
//#include "i2c_drv.h"
#endif

#include "data_utils.h"
#include "light_navigator_types.h"

const LightNavigatorConfig_t LightNavigatorConfig[] = {
    {
        .num = 1,
        .rtc_num = 1,
        .trigger_num = 1,
        .light_sensor_num = 1,
        .valid = true,
        .filename = "LiLog.csv",
        .day_light_filename = "DayLi.txt",
        .coordinate_filename = "Coord.txt",
    },
};

LightNavigatorHandle_t LightNavigatorInstance[] = {
    {
        .num = 1,
        .valid = true,
        .init = false,
    },
};

COMPONENT_GET_CNT(LedMono, light_navigator)
