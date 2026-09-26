#include "nvs_drv.h"

#include <stddef.h>
#include <stdint.h>

#include "bit_utils.h"
#include "data_utils.h"
#include "log.h"

#ifdef HAS_NVS_DIAG
#include "nvs_diag.h"
#endif

#ifdef HAS_NVS_WRITE
bool nvs_erase_page(uint32_t flash_addr) {
    bool res = false;
    return res;
}
#endif
