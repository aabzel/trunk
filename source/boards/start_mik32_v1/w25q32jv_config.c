#include "w25q32jv_config.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#include "w25q32jv_types.h"

const W25q32jvConfig_t W25q32jvConfig[] = {
    {
        .num = 1,
        .spi_num = 0xFF,
        .spifi_num = 0,
        .valid = true,
#ifdef HAS_GPIO
        .chip_select = { .port = 2, .pin = 1,},
        .reset = { .port = 2, .pin = 5,},
        .write_protection = { .port = 2, .pin = 4,},
#endif
    },
};

W25q32jvHandle_t W25q32jvInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t w25q32jv_get_cnt(void) {
    return 1;
}
