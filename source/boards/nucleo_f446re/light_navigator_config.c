#include "light_navigator_config.h"

#ifdef HAS_I2C
#include "i2c_drv.h"
#endif

#include "data_utils.h"
#include "light_navigator_types.h"

const LightNavigatorConfig_t LightNavigatorConfig[] = {
    {.num=1, .rtc_num=1, .trigger_num=1, .light_sensor_num=1, .valid=true,
	.filename="LiLog1.csv", .day_light_filename="DayLi1.txt",
	.coordinate_filename="Coord1.txt",},

    {.num=2, .rtc_num=1, .trigger_num=2, .light_sensor_num=2, .valid=true,
	.filename="LiLog2.csv", .day_light_filename="DayLi2.txt",
	.coordinate_filename="Coord2.txt",}
};

LightNavigatorItem_t LightNavigatorItem[]= {
    {.num=1, .valid=true, .init=false,},
    {.num=2, .valid=true, .init=false,}
};

COMPONENT_GET_CNT(LedMono, light_navigator)

