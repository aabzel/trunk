#include "mpu_config.h"

#include "data_utils.h"
#include "macro_utils.h"
#include "cortex_m7_const.h"

const MpuRegionConfig_t MpuRegions[] = {
};

const MpuConfig_t MpuConfig[] = {
};

MpuHandle_t MpuInstance[] = {
};

uint32_t mpu_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(MpuConfig);
    cnt2 = ARRAY_SIZE(MpuInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
