#include "gd5f1gq5_config.h"

#include "data_utils.h"

const Gd5f1gq5Config_t Gd5f1gq5Config[] = {
    {
        .num = 1,
        .spi_num = 3,
        .chip_select = {.port=PORT_A, .pin=15,},
        .valid = true,
        .name = "GD5F1GQ5UEYIGR",
    },

};

Gd5f1gq5Handle_t Gd5f1gq5Instance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Gd5f1gq5, gd5f1gq5)

