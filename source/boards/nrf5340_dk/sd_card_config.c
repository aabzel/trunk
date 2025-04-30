#include "sd_card_config.h"

#include "gpio_types.h"
#include "spi_types.h"

const SdCardConfig_t SdCardConfig = {
    .spi_num = 4,
    .chip_sel = {
            .port = 0,
            .pin = 26,
    },
    .valid = true,
    .block_len = 512,
};

SdCardHandle_t SdCardInstance = { 0 };
