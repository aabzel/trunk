#include "nvs_drv.h"

#include "log.h"

#ifdef HAS_NVS_DIAG
#include "nvs_diag.h"
#endif

#ifdef HAS_NVS_WRITE
bool nvs_erase_page(uint32_t flash_addr) {
    bool res = false;
    LOG_WARNING(NVS, "ErasePage Addr: 0x%x ", flash_addr);

    return res;
}
#endif
