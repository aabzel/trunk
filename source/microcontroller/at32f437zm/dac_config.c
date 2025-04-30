#include "dac_config.h"


#include "data_utils.h"

/*constant compile-time known settings in Flash*/
const DacConfig_t DacConfig[] = {
    {        .num = 1,        .name = "DAC1",        .valid = true,    },
    {        .num = 2,        .name = "DAC2",        .valid = true,    },
};

DacHandle_t DacInstance[] = {
    {        .num = 1,        .valid = true,    },
    {        .num = 2,        .valid = true,    },
};

uint32_t dac_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(DacConfig);
    uint32_t cnt_ints = ARRAY_SIZE(DacInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
