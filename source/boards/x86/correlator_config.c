#include "correlator_config.h"

#include "data_utils.h"
#include "correlator_const.h"

const CorrelatorConfig_t CorrelatorConfig[] = {
   {.num=1, .valid=true,  },
};

CorrelatorHandle_t CorrelatorInstance[]={
     {.num=1, .valid=true,},
};

uint32_t correlator_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(CorrelatorInstance);
    cnt2 = ARRAY_SIZE(CorrelatorConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
