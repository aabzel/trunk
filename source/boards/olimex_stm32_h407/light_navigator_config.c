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

uint32_t light_navigator_get_cnt(void) {
    uint8_t cnt = 0;
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(LightNavigatorConfig);
    cnt2 = ARRAY_SIZE(LightNavigatorInstance);

    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
