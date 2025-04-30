#include "histogram_config.h"

#include "data_utils.h"
#include "common_const.h"
#include "histogram_const.h"

static uint32_t HistogramData[1023*16]={0};

const HistogramConfig_t HistogramConfig[] = {
    {
      .num=1,
      .valid = true,
      .size = ARRAY_SIZE(HistogramData),
      .frequency = HistogramData,
      .min_val = 0,
      .max_val=1023*16,
      .resolution=1,
    },
};

HistogramHandle_t HistogramInstance[]={
    {.num=1, .valid=true,},
};

uint32_t histogram_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(HistogramInstance);
    cnt2 = ARRAY_SIZE(HistogramConfig);
    if(cnt1==cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
