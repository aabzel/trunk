#include "mx25l6433f_config.h"

#include "data_utils.h"

const Mx25l6433fConfig_t Mx25l6433fConfig[] = {
    {
        .num = 1,
        .valid = true,
        .spi_num = 1,
        .chip_select = {.port=PORT_B, .pin=0,},
        .write_protection = {.port=PORT_P, .pin=0,},
        .reset = {.port=PORT_P, .pin=0,},
        .name = "MX25L6433F1",
    },
};
Mx25l6433fHandle_t Mx25l6433fInstance[] = {
    { .num = 1, .valid = true, },
};

COMPONENT_GET_CNT(Mx25l6433f, mx25l6433f)


