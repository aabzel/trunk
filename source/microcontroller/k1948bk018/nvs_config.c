#include "nvs_config.h"

// TODO add multiple instances of NVS for reservation (e.g.RAID 5)

const NvsConfig_t NvsConfig = {
    .start = NVS_START,
    .size = NVS_SIZE,
};

NvsItem_t NvsItem = {0};
