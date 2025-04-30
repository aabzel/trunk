#include "iso_tp_config.h"

#include "data_utils.h"

const IsoTpConfig_t IsoTpConfig[] = {
    {
    .num = 1,
    .valid= true,
    .my_id= 0x1C,
    .block_size= 3,
    .separation_time_ms= 10,
    .interface = IF_ISO_TP2,
    },

    {
    .num = 2,
    .valid= true,
    .my_id= 0x18,
    .block_size= 3,
    .separation_time_ms= 10,
    .interface = IF_ISO_TP1,
    }
};

IsoTpHandle_t IsoTpInstance[]={
    {.num=1, .valid=true, },
    {.num=2, .valid=true, }
};

uint32_t iso_tp_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(IsoTpInstance);
    cnt2 = ARRAY_SIZE(IsoTpConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
