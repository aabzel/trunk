#include "w25q16bv_config.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#include "w25q16bv_types.h"

const W25q16bvConfig_t W25q16bvConfig[] = {
    {
        .num = 1,
        .spi_num = 1,
        .valid = true,
#ifdef HAS_GPIO
        .chip_select = { .port = PORT_A, .pin = 15,},
        .reset = { .port = PORT_UNDEF, .pin = 0,},
        .write_protection = { .port = PORT_UNDEF, .pin = 0,},
#endif
    },
};

W25q16bvHandle_t W25q16bvInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t w25q16bv_get_cnt(void) {
    return 1;
}
