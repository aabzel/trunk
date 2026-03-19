#include "nvs_mcal.h"

#include <stddef.h>

#include "std_includes.h"
#include "bit_utils.h"
#include "data_utils.h"
#include "flash_mcal.h"
#include "log.h"
#include "nvs_config.h"
#include "nvs_const.h"

#ifdef HAS_NVS_DIAG
#include "nvs_diag.h"
#endif

bool nvs_erase_page(uint8_t num,uint32_t flash_addr) {
    bool res = false;
    return res;
}
