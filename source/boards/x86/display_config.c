#include "display_config.h"

#include "data_utils.h"

#include "display_const.h"

const DisplayConfig_t DisplayConfig[] = {
    {
        .num = 1,
        .width = 128,
        .height = 64,
        .page_cnt = 8,
        .pixel_size = 0.25,
        .name="Display",
        .valid = true,
    },
};

DisplayHandle_t DisplayInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t display_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DisplayInstance);
    cnt2 = ARRAY_SIZE(DisplayConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
