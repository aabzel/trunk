#include "nvs_drv.h"

#include <stddef.h>
#include <stdint.h>

#include "bit_utils.h"
#include "data_utils.h"
#include "flash_mcal.h"
#include "log.h"
#include "nvs_config.h"
#include "nvs_const.h"

#ifdef HAS_NVS_DIAG
#include "nvs_diag.h"
#endif

bool nvs_erase_page(uint32_t flash_addr) {
    bool res = false;
    return res;
}
