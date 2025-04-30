#include "delta_sigma_config.h"

#include "data_utils.h"

const DeltaSigmaConfig_t DeltaSigmaConfig[] = {
    {
      .num = 1,
      .valid = true,
      .target = 1500,
      .min = 0,
      .Pad = {.port=PORT_D, .pin=14,},
      .max = 3300,
      .comparator_middle = 1650,
      .sample_frequency_hz = 48000,
    },
};

DeltaSigmaHandle_t DeltaSigmaInstance[]={
    {.num=1, .valid=true,},
};

uint32_t delta_sigma_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DeltaSigmaInstance);
    cnt2 = ARRAY_SIZE(DeltaSigmaConfig);
    if(cnt1==cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
