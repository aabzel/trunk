#include "sd_card_config.h"

#include "gpio_types.h"
#include "spi_types.h"

const SdCardConfig_t SdCardConfig = {
    .spi_num = 1,
    .block_len = 512,
    .chip_sel={.port=PORT_A, .pin=4,},
    //.sclk={.port=PORT_A, .pin=5},
    //.miso={.port=PORT_A, .pin=6},
    //.mosi={.port=PORT_A, .pin=7},
};

SdCardHandle_t SdCardInstance={
    .chip_enable_cnt=0,
};
