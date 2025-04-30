#include "nvs_diag.h"

#include <stdbool.h>

#include "flash_mcal.h"
#include "log.h"
#include "nvs_config.h"
#include "nvs_custom_diag.h"

bool nvs_diag(void) {
    bool res = true;
    LOG_INFO(NVS, "StartAddr: 0x%08x", NvsConfig.start);
    LOG_INFO(NVS, "TotalSize: %u Byte", NvsConfig.size);
    // LOG_INFO(NVS,"TotalSize: %u Pages", NVS_SIZE/NOR_FLASH_PAGE_SIZE);
    // LOG_INFO(NVS,"PageSize: %u byte", NOR_FLASH_PAGE_SIZE);

    res = is_flash_addr(NvsConfig.start);
    if(res) {
        res = nvs_custom_diag();
    } else {
        LOG_ERROR(NVS, "WrongStartAddr: 0x%08x", NvsConfig.start);
    }

    /*TODO: Calc CRC for entite NVS*/
    return res;
}
