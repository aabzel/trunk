#include "lockstep_config.h"

#include "data_utils.h"

const LockStepConfig_t LockStepConfig[] = {
};

LockStepHandle_t LockStepInstance[] = {
};

uint32_t lockstep_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(LockStepInstance);
    cnt2 = ARRAY_SIZE(LockStepConfig);
    if (cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
