#include "dwm3000_config.h"

#include "data_utils.h"
#include "gpio_types.h"
#include "common_const.h"
#include "dwm3000_const.h"

const Dwm3000Config_t Dwm3000Config={
    .num=DWM3000_MAIN,
    .spi_num=DWM3000_SPI_NUM,
    .chip_select={.port=1, .pin=12,},
    .wakeup={.port=1, .pin=13,},
    .gpio5={.port=1, .pin=8,},
    .gpio6={.port=1, .pin=9,},
    .valid = true,

};

Dwm3000Handle_t Dwm3000Instance={
    .num=DWM3000_MAIN,   .valid = true,
};


