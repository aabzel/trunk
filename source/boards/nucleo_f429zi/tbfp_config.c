#include "tbfp_config.h"

#include "data_utils.h"
#include "gpio_const.h"
#include "common_const.h"
#include "tbfp_const.h"

const TbfpConfig_t TbfpConfig[]={
    {.num=1, .interface=IF_UWB, .preamble_val = 0x12, .valid = true,},
    {.num=2, .interface=IF_LOOPBACK, .preamble_val = 0xA5, .valid = true,},
    {.num=3, .interface=IF_BLACK_HOLE, .preamble_val = 0xB0, .valid = true,},
};

TbfpProtocol_t TbfpInstance[]={
    {.num=1, .valid = true,},
    {.num=2, .valid = true,},
    {.num=3, .valid = true,},
};

uint32_t tbfp_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(TbfpInstance);
    cnt2 = ARRAY_SIZE(TbfpConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
