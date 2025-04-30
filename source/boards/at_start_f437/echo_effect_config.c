#include "echo_effect_config.h"

#include "data_utils.h"

#define SAMPLE_CNT 24000
static int16_t SampleArray[SAMPLE_CNT];

const EchoEffectConfig_t EchoEffectConfig[] = {
    {
      .num = 1,
      .inArray = SampleArray,
      .capacity = ARRAY_SIZE(SampleArray),
      .valid = true,
      .name = "I2sEcho",
      .scale = 0.4,
    },
};

EchoEffectHandle_t EchoEffectInstance[] = {
    {.num=1, .valid=true,},
};

uint32_t echo_effect_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(EchoEffectInstance);
    cnt2 = ARRAY_SIZE(EchoEffectConfig);
    if(cnt1==cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
