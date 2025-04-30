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
        .filename = "LiLog.csv",
        .TrueCoordinate = { .phi = 55.864110, /* Latitude (degrees and minutes) */
                            .lambda = 37.426855, },/* Longitude (degrees and minutes) */
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

uint32_t light_navigator_light_to_lambda_get_cnt(void) {
    uint32_t cnt=light_navigator_get_cnt();
    return cnt;
}
