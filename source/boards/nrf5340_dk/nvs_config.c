#include "nvs_config.h"

#include "macro_utils.h"
#include "nvs_types.h"
#include "sys_config.h"

const NvsConfig_t NvsConfig = {
    .start= NVS_START,
    .size = NVS_SIZE,
    .end = NVS_END,
};

NvsItem_t NvsItem = {0};
