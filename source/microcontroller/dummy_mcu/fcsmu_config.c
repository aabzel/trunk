#include "fcsmu_config.h"

#include "data_utils.h"

const FcsmuConfig_t FcsmuConfig[] = {
};

FcsmuHandle_t FcsmuInstance[] = {
};

uint32_t fcsmu_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(FcsmuInstance);
    cnt2 = ARRAY_SIZE(FcsmuConfig);
    if (cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
