#include "gpio_mapper_config.h"

#include "data_utils.h"

static const Pad_t gpioArray[] = {
    {.port=PORT_B, .pin=0,},
    {.port=PORT_B, .pin=1,},
    {.port=PORT_B, .pin=2,},
    {.port=PORT_B, .pin=3,},
    {.port=PORT_B, .pin=4,},
    {.port=PORT_B, .pin=5,},
    {.port=PORT_B, .pin=8,},
    {.port=PORT_B, .pin=9,},
    {.port=PORT_B, .pin=14,},
};

static const Pad_t gpioArray2[] = {
    {.port=PORT_C, .pin=0,},
    {.port=PORT_C, .pin=1,},
    {.port=PORT_C, .pin=2,},
    {.port=PORT_C, .pin=3,},
    {.port=PORT_C, .pin=4,},
    {.port=PORT_C, .pin=5,},
    {.port=PORT_C, .pin=13,},
    {.port=PORT_C, .pin=14,},
    {.port=PORT_C, .pin=15,},
};

const GpioMapperConfig_t GpioMapperConfig[] = {
    {
        .num = GPIO_MAP_INIT_LEN,
        .valid = true,
        .value = 6,
        .gpioArray = gpioArray,
        .bitness = ARRAY_SIZE(gpioArray),
        .name = "DEBUG",
    },
    {
        .num = GPIO_MAP_ERR_CODE,
        .valid = true,
        .value = 0,
        .gpioArray = gpioArray2,
        .bitness = ARRAY_SIZE(gpioArray2),
        .name = "ErrCode",
    },
};

GpioMapperHandle_t GpioMapperInstance[] = {
    { .num = GPIO_MAP_INIT_LEN, .valid = true, },
    { .num = GPIO_MAP_ERR_CODE, .valid = true, },
};

COMPONENT_GET_CNT(GpioMapper, gpio_mapper)


