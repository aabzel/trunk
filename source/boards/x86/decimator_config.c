#include "decimator_config.h"

#include "data_utils.h"

const DecimatorConfig_t DecimatorConfig[] = {
   {.num=1, .valid=true, .samples_per_bit = 441, },
};

DecimatorHandle_t DecimatorInstance[] = {
     {.num=1, .valid=true,},
};

uint32_t decimator_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DecimatorInstance);
    cnt2 = ARRAY_SIZE(DecimatorConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
