#include "pll_sim_config.h"

#include "data_utils.h"

#define LO_FREQ_HZ 10.0
#define NICVISR_FREQ_HZ 8000.0
const PllSimConfig_t PllSimConfig[] = {
    {
      .num = 1,
      .valid = true,
      .lo_frequency_hz = LO_FREQ_HZ,
      .sample_frequency_hz = 2.0*NICVISR_FREQ_HZ,//1 000 000 ok
      .vco_p = 5.0, //10000 1000 180 deg->2000 Hz 180*vco_p = OutFreq
      .vco_i = 0.1, //
      .vco_d = 1.0, //
      .divider = 2,
      .fir_num  =1,
    },
};

PllSimHandle_t PllSimInstance[]={
    {.num=1, .valid=true,},
};

uint32_t pll_sim_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(PllSimInstance);
    cnt2 = ARRAY_SIZE(PllSimConfig);
    if(cnt1==cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
