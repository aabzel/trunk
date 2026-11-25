#include "multicore_config.h"

#include "data_utils.h"

const MultiCoreConfig_t MultiCoreConfig[] = {
    { .num = 1, .valid = true, },
    { .num = 2, .valid =true, },
    { .num = 3, .valid = true, }
};

MultiCoreHandle_t MultiCoreInstance[] = {
    { .num = 1, .valid = true, },
    { .num = 2, .valid = true, },
    { .num = 3, .valid = true, }
};

uint32_t multicore_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(MultiCoreInstance);
    cnt2 = ARRAY_SIZE(MultiCoreConfig);
    if (cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
