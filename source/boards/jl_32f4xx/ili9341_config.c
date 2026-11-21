#include "ili9341_config.h"

#include "data_utils.h"
#include "ili9341_const.h"

const Ili9341Config_t Ili9341Config[] = {
    {
       .num = 1,
       .name = "Ili9341",
       .screen_orientation = SCREEN_ORIENTATION_HORIZONTAL,
       .spi_num = 1,
       .chip_select = { .port = PORT_A,  .pin = 3,},
       .LedPad = { .port = PORT_A,  .pin = 1,},
       .DcxPad = { .port = PORT_A,  .pin = 2,},
       .ResetPad = { .port = PORT_A,  .pin = 4,},
       .update_period_ms = 100,
       .valid = true,
    },
};

Ili9341Handle_t Ili9341Instance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Ili9341, ili9341)
