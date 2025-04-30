#include "distance_config.h"

#include "common_const.h"
#include "data_utils.h"
#include "distance_const.h"
#include "gpio_const.h"
#include "log.h"

const DistanceConfig_t DistanceConfig[] = {
    {
        .num = 1,
        .debug_led_num = 1,
        .decawave_num = 1,
        .valid = true,
    },
};

volatile DistanceHandle_t DistanceInstance[] = {
    {
        .num = 1,
        .valid = true,
        .state = DISTANCE_STATE_UNKNOWN,
        .input = DISTANCE_INPUT_NONE,
        .new_dist_time_stamp_ms = 0,
        .distance_m = 0.0,
    },
};

uint32_t distance_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DistanceInstance);
    cnt2 = ARRAY_SIZE(DistanceConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    } else {
        // LOG_ERROR(DISTANCE,"ConfigErr");
    }
    return cnt;
}
