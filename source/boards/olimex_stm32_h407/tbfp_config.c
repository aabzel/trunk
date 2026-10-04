#include "tbfp_config.h"

#include "data_utils.h"
#include "gpio_const.h"
#include "common_const.h"
#include "tbfp_const.h"

const TbfpConfig_t TbfpConfig[]={
    {.num=1, .interface=IF_FAT_FS, .preamble_val = 0x12, .valid = true,},
    {.num=2, .interface=IF_LOOPBACK, .preamble_val = 0xA5, .valid = true,},
    {.num=3, .interface=IF_BLACK_HOLE, .preamble_val = 0xB0, .valid = true,},
};

TbfpProtocol_t TbfpInstance[]={
    {.num=1, .valid = true,},
    {.num=2, .valid = true,},
    {.num=3, .valid = true,},
};


COMPONENT_GET_CNT(Tbfp, tbfp)

