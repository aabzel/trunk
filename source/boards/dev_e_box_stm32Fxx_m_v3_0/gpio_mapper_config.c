#include "gpio_mapper_config.h"

#include "data_utils.h"


static const Pad_t DebugGpioArray[] = {
    {.port=PORT_B, .pin=2,},
    {.port=PORT_E, .pin=5,},
    {.port=PORT_E, .pin=6,},
    {.port=PORT_E, .pin=7,},
    {.port=PORT_E, .pin=8,},
    {.port=PORT_E, .pin=9,},
    {.port=PORT_E, .pin=10,},
    {.port=PORT_E, .pin=11,},
    {.port=PORT_E, .pin=13,},
};

static const Pad_t ErrorGpioArray2[] = {
    {.port=PORT_A, .pin=12,},
    {.port=PORT_C, .pin=2,},
    {.port=PORT_C, .pin=3,},
    {.port=PORT_C, .pin=13,},
    {.port=PORT_C, .pin=14,},
    {.port=PORT_C, .pin=15,},
    {.port=PORT_E, .pin=13,},
    {.port=PORT_E, .pin=14,},
    {.port=PORT_E, .pin=15,},
};

const GpioMapperConfig_t GpioMapperConfig[] = {
    {
        .num = GPIO_MAP_INIT_LEN,
        .valid = true,
        .value = 6,
        .gpioArray = DebugGpioArray,
        .bitness = ARRAY_SIZE(DebugGpioArray),
        .name = "DEBUG",
    },
    {
        .num = GPIO_MAP_ERR_CODE,
        .valid = true,
        .value = 0,
        .gpioArray = ErrorGpioArray2,
        .bitness = ARRAY_SIZE(ErrorGpioArray2),
        .name = "ErrCode",
    },
};

GpioMapperHandle_t GpioMapperInstance[] = {
    { .num = GPIO_MAP_INIT_LEN, .valid = true, },
    { .num = GPIO_MAP_ERR_CODE, .valid = true, },
};

COMPONENT_GET_CNT(GpioMapper, gpio_mapper)


