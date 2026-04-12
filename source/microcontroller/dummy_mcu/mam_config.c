#include "mam_config.h"

#include "data_utils.h"


static const MamMemoryAccessConfig_t MamRegions[] = {
};


const MamConfig_t MamConfig[] = {
};

MamHandle_t MamInstance[] = {
};

uint32_t mam_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(MamConfig);
    cnt2 = ARRAY_SIZE(MamInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
