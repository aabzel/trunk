#include "nvs_config.h"

#include "macro_utils.h"
#include "nvs_types.h"
#include "flash_dep.h"
#include "sys_config.h"

const NvsConfig_t NvsConfig = {
    .start = 0x000fc000,
    .size = (4*(ON_CHIP_NOR_FLASH_PAGE_SIZE)),
    .end = (NVS_START+NVS_SIZE),
};

NvsItem_t NvsItem = {0};
