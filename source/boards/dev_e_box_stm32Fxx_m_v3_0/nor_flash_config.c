#include "nor_flash_config.h"


#include <stdbool.h>
#include <stddef.h>

#include "data_utils.h"
#ifdef HAS_SW_NOR_FLASH
#include "sw_nor_flash.h"
#endif

#ifdef HAS_SW_NOR_FLASH
#include "sw_nor_flash_const.h"

static uint8_t SwNorFlashMem1[SW_NOR_FLASH_FLASH_SIZE]={0};
static uint8_t SwNorFlashMem2[SW_NOR_FLASH_FLASH_SIZE]={0};
#endif

const NorFlashConfig_t SECTION_CFG_DATA NorFlashConfig[] = {
#ifdef HAS_SW_NOR_FLASH
    {
        .num = 1,
        .name = "Sw-NOR-Flash",
        .option = NOR_FLASH_OPTION_SW,
        .start = 0,
        .size = SW_NOR_FLASH_FLASH_SIZE,
        .valid = true,
        .CustomInit = sw_nor_flash_init_one,
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
        .CustomInit = sw_nor_flash_init_one,
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

COMPONENT_GET_CNT(NorFlash, nor_flash)

