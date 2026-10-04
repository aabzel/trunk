#include "mbr_config.h"

#include "microcontroller_const.h"

const MbrConfig_t SECTION_CFG_DATA MbrConfig = {
    .boot_start_address = 0x080E0000,
    .led_num = 1,
};

MbrHandle_t MbrInstance = {
    .boot_start_address = 0x080E0000,
};
