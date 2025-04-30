#include "nvs_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "bit_utils.h"
#include "data_utils.h"
#include "flash_mcal.h"
#include "log.h"
#include "nrfx_nvmc.h"
#include "nvs_config.h"
#include "nvs_custom_const.h"

#ifdef HAS_DIAG
#include "hal_nrfx_diag.h"
#endif

#ifdef HAS_NVS_DIAG
#include "nvs_diag.h"
#endif

#ifdef HAS_NVS_WRITE
bool nvs_erase_page(uint32_t flash_addr) {
    bool res = false;
    LOG_WARNING(NVS, "ErasePage Addr: 0x%x ", flash_addr);
    res = is_flash_addr(flash_addr);
    if(res) {
        nrfx_err_t ret;
        // ret = nrfx_nvmc_page_partial_erase_init(flash_addr, NVMC_ERASE_DURATION_MS);
        ret = nrfx_nvmc_page_erase(flash_addr);
        if(NRFX_SUCCESS == ret) {
            res = true;
        } else {
            res = false;
            LOG_ERROR(NVS, "EraseError %u %s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}
#endif
