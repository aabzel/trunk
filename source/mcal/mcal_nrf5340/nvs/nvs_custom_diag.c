#include "nvs_custom_diag.h"

#include <stdbool.h>

#include "log.h"
#include "nrfx_nvmc.h"
#include "nvs_config.h"
#include "nvs_dep.h"
#include "sys_config.h"

bool nvs_custom_diag(void) {
    bool res = true;

    uint32_t flash_size = nrfx_nvmc_flash_size_get();
    LOG_INFO(NVS, "FlashSize %u Byte", flash_size);

    uint32_t page_size = nrfx_nvmc_flash_page_size_get();
    LOG_INFO(NVS, "PageSize %u Byte", page_size);
    if(ON_CHIP_NOR_FLASH_PAGE_SIZE != page_size) {
        LOG_ERROR(NVS, "PageSize %u %u Byte", page_size, ON_CHIP_NOR_FLASH_PAGE_SIZE);
    }
    // uint32_t page_count = nrfx_nvmc_flash_page_count_get();
    LOG_INFO(NVS, "PageCount %u", NvsConfig.size / page_size);
    /*TODO: Calc CRC for entite NVS*/
    return res;
}
