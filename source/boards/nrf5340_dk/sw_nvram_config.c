#include "sw_nvram_config.h"

#include <stddef.h>

#include "data_utils.h"
#include "mx25r6435f_const.h"

const NvRamConfig_t NvRamConfig[]={
    {
     .num=1,
     .name="SPI-Flash",
     .page={ {.page_start=MX25R6435F_SECTOR_SIZE,  .size=MX25R6435F_SECTOR_SIZE, .prefix=0, .num=0,},
             {.page_start=MX25R6435F_SECTOR_SIZE*2,.size=MX25R6435F_SECTOR_SIZE, .prefix=0, .num=1,}
     },
    .nor_flash_num=3,
    .valid=true,
    },
};

NvRamItem_t NvRamItem[]={
    {.num = 1,
     .init=false,
     .entry_cnt=0,
     .valid=true,
    },
};

uint32_t sw_nvram_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(NvRamConfig);
    uint32_t cnt_ints = ARRAY_SIZE(NvRamItem);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
