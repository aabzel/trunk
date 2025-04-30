#include "sw_nvram_config.h"

#include <stddef.h>

#include "data_utils.h"

#include "sw_nor_flash_config.h"
#define SECTOR_SIZE (0x1000 * 2)

const NvRamConfig_t NvRamConfig[] = {
    {
        .num = 1,
        .nor_flash_num = 1,
        .name = "inRAM",
        .valid = true,
        .page = {{
                     .page_start = 0,
                     .size = SECTOR_SIZE,
                     .num = 0,
                     .prefix = 0,
                 },
                 {
                     .page_start = SECTOR_SIZE,
                     .size = SECTOR_SIZE,
                     .num = 1,
                     .prefix = 0,
                 }},
    },
    {
        .num = 2,
        .nor_flash_num = 2,
        .name = "Set",
        .valid = true,
        .page = {{
                     .num = 0,
                     .page_start = 0,
                     .size = SECTOR_SIZE,
                     .prefix = 0,
                 },
                 {
                     .num = 1,
                     .page_start = SECTOR_SIZE,
                     .size = SECTOR_SIZE,
                     .prefix = 0,
                 }},
    },
};

NvRamItem_t NvRamItem[] = {
    {
        .num = 1,
        .init = false,
        .valid = true,
    },
    {
        .num = 2,
        .init = false,
        .valid = true,
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
