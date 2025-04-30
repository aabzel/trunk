#include "nor_flash_config.h"

#ifdef HAS_SW_NOR_FLASH
#include "sw_nor_flash_config.h"
#include "sw_nor_flash_drv.h"
#endif

#include <stdbool.h>
#include <stddef.h>

#include "data_utils.h"
#include "sw_nor_flash_const.h"

static uint8_t SwNorFlashMem1[SW_NOR_FLASH_FLASH_SIZE];
static uint8_t SwNorFlashMem2[SW_NOR_FLASH_FLASH_SIZE];

const NorFlashConfig_t NorFlashConfig[] = {
#ifdef HAS_SW_NOR_FLASH
    {
        .num = 1,
        .name = "Sw-NOR-Flash",
        .option = NOR_FLASH_OPTION_SW,
        .start = 0,
        .size = SW_NOR_FLASH_FLASH_SIZE,
        .valid = true,
        .CustomInit = sw_nor_flash_init,
        .memory = SwNorFlashMem1, /*Ptr to array*/
    },
#endif

#ifdef HAS_SW_NOR_FLASH
    {
        .num = 2,
        .name = "Sw-NOR-Flash",
        .option = NOR_FLASH_OPTION_SW,
        .start = 0,
        .size = SW_NOR_FLASH_FLASH_SIZE,
        .valid = true,
        .CustomInit = sw_nor_flash_init,
        .memory = SwNorFlashMem2, /*Ptr to array*/
    },
#endif
};

NorFlashItem_t NorFlashItem[] = {
#ifdef HAS_SW_NOR_FLASH
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
#endif
};

uint32_t nor_flash_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(NorFlashItem);
    cnt2 = ARRAY_SIZE(NorFlashConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
