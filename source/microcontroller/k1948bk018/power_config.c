#include "power_config.h"

#include "data_utils.h"


/*constant compile-time known settings in Flash*/
const PowerConfig_t PowerConfig[] = {
    {
        .num = 1,
        .mode = POWER_MODE_ACTIVE,
        .name = "Active",
        .valid = true,
    },
};

PowerHandle_t PowerInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t power_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(PowerConfig);
    uint32_t cnt_ints = ARRAY_SIZE(PowerInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
