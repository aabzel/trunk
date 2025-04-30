#include "decawave_proto_config.h"

#include "data_utils.h"
#include "common_const.h"
#include "decawave_constants.h"
#include "sys_constants.h"

const DecaWaveConfig_t DecaWaveConfig[] = {
    {
     .num = 1,
     .preamble_val = 0x41,
     .addr_def = 0x0A,
     .interface = IF_BLACK_HOLE,
     .valid = true,
     .timer_clock = 64000000000,
     .ant_delay_m = 154.199,/*Move ant_delay_m to DW1000 conf*/
    },
};

DecaWaveHandle_t DecaWaveInstance[] = {
    {.num=1, .valid = true,},
};

uint32_t decawave_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DecaWaveInstance);
    cnt2 = ARRAY_SIZE(DecaWaveConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
