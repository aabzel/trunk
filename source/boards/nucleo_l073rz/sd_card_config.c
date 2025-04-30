#include "sd_card_config.h"

#include "gpio_types.h"
#include "spi_types.h"

const SdCardConfig_t SdCardConfig = {
    .spi_num = 2,
    .block_len = 512,
    .valid = true,
    .chip_sel = {.port=PORT_B, .pin=4,},
    .sclk = {.port=PORT_B, .pin=10},/*Just For Diag*/
    .mosi = {.port=PORT_B, .pin=15},/*Just For Diag*/
    .miso = {.port=PORT_B, .pin=14},/*Just For Diag*/
};

SdCardHandle_t SdCardInstance = {
    .spi_num = 2,
    .valid= true,
};

