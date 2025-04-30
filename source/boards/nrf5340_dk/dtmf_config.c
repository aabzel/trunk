#include "dtmf_config.h"

#include "data_utils.h"
#include "dtmf_const.h"


const DtmfConfig_t DtmfConfig[] = {
    {
        .num = 1,
        .dac_num = 1,
        .i2s_num = 0,
        .valid = true,
        .name = "DTMF0",
    },
};

DtmfHandle_t DtmfInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t dtmf_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DtmfInstance);
    cnt2 = ARRAY_SIZE(DtmfConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
