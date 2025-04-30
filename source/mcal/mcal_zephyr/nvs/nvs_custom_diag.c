#include "nvs_custom_diag.h"

#include <stdbool.h>

#include "log.h"
#include "nrfx_nvmc.h"
#include "nvs_config.h"
#include "nvs_dep.h"
#include "sys_config.h"

bool nvs_custom_diag(void) {
    bool res = true;
    LOG_INFO(NVS, "Diag");

}
