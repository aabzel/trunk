#include "bootloader_config.h"

#include "flash_config.h"

const BootLoaderConfig_t BootLoaderConfig = {
    .app_start_address = APP_START_ADDRESS,
};

BootLoaderHandler_t BootLoaderInstance = {
    .app_start_address = APP_START_ADDRESS,
    .app_crc32 =
        {
            .calc = 0,
            .read = 0,
        },
    .app_len = 0,
};
