#include "mbr_config.h"

#include "k1948bk018_const.h"


const MbrConfig_t MbrConfig = {
    .boot_start_address = EXT_ROM_START,
};

MbrHandle_t MbrInstance = {
    .boot_start_address = EXT_ROM_START,
};
