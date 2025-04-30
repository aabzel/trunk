#ifndef GPIO_STM32_CONST_H
#define GPIO_STM32_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define GPIO_PIN_COUNT 15

typedef enum {
    PORT_A = 0,
    PORT_B = 1,
    PORT_C = 2,
    PORT_D = 3,
    PORT_E = 4,
    PORT_F = 5,
    PORT_G = 6,
    PORT_H = 7,

    PORT_UNDEF = 8,
} Port_t;

/*see 7.4.4 GPIO port pull-up/pull-down register (GPIOx_PUPDR)*/
typedef enum {
    STM32_PULL_AIR = GPIO_NOPULL,
    STM32_PULL_UP = GPIO_PULLUP,
    STM32_PULL_DOWN = GPIO_PULLDOWN,
    STM32_PULL_RESERVED = 3,

    STM32_PULL_UNDEF = 4,
} GpioStm32Pull_t;

typedef enum {
    SPEED_LOW_SPEED = 0,
    SPEED_MEDIUM_SPEED = 1,
    SPEED_FAST_SPEED = 2,
    SPEED_HIGH_SPEED = 3,
    SPEED_UNDEF = 4,
} GpioStm32Speed_t;

typedef enum {
    OUT_TYPE_PUSH_PULL = 0,
    OUT_TYPE_OPEN_DRAIN = 1,
    OUT_TYPE_UNDEF = 2,
} OutType_t;

typedef enum {
    GP_STM32_MODE_INPUT = 0,
    GP_STM32_MODE_GNRL_PURPOSE_OUT = 1,
    GP_STM32_MODE_ALT_FUN = 2,
    GP_STM32_MODE_ANALOG = 3,
    GP_STM32_MODE_UNDEF = 4,
} GpioStm32Mode_t;

#ifdef __cplusplus
}
#endif

#endif /* GPIO_STM32_CONST_H  */
