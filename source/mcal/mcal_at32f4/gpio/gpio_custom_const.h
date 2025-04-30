#ifndef GPIO_AT32_CONST_H
#define GPIO_AT32_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

//#include "artery_at32f4xx.h"

#define GPIO_PIN_COUNT 15
#define GPIO_PIN_UNDEF 16

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

typedef enum {
    AT32_PULL_AIR = 0,
    AT32_PULL_UP = 1,
    AT32_PULL_DOWN= 2,

    AT32_PULL_UNDEF = 3,
} GpioAt32Pull_t;


typedef enum {
    SPEED_LOW_SPEED = 0,
    SPEED_MEDIUM_SPEED = 1,
    SPEED_FAST_SPEED = 2,
    SPEED_HIGH_SPEED = 3,
    SPEED_UNDEF = 4,
} GpioAt32Speed_t;

typedef enum {
    OUT_TYPE_PUSH_PULL = 0,
    OUT_TYPE_OPEN_DRAIN = 1,
    OUT_TYPE_UNDEF = 2,
} OutType_t;


typedef enum {
    GPIO_OUT_DATA_TYPE_PULL_DOWN = 0, //0: Pull-down
    GPIO_OUT_DATA_TYPE_PULL_UP = 1,   //1: Pull-up
    GPIO_OUT_DATA_TYPE_UNDEF = 2,
} GpioAt32F413OutputData_t;

//6.3.1 GPIO configuration register (GPIOx_CFGR) (x=A..H)
typedef enum {
    GP_AT32_MODE_INPUT = 0,            /*Input mode (reset state)*/
    GP_AT32_MODE_GNRL_PURPOSE_OUT = 1, /*General-purpose output mode*/
    GP_AT32_MODE_ALT_FUN = 2,          /*Multiplexed function mode*/
    GP_AT32_MODE_ANALOG = 3,           /*Analog mode*/

    GP_AT32_MODE_UNDEF = 4,
} GpioAt32Mode_t;

//see 6.3.1 GPIO configuration register low (GPIOx_CFGLR) (x=A..F)
typedef enum {
	GPIO_AT32F413_MODE_ANALOG = 0,             /*00: Analog mode*/
    GPIO_AT32F413_MODE_FLOATING_INPUT = 1,     /*01: Floating input (after reset)*/
    GPIO_AT32F413_MODE_PULL_UP_DOWN_INPUT = 2, /*10: Pull-up/pull-down input*/
    GPIO_AT32F413_MODE_RESERVED = 3,           /*11: Reserved(Open-drain)*/
    GPIO_AT32F413_MODE_UNDEF = 4,
} GpioAt32F413_IOFCy_t;


//see 6.3.1 GPIO configuration register low (GPIOx_CFGLR) (x=A..F)
typedef enum {
	GPIO_AT32F413_OUT_PUSH_PULL = 0,       //00: General-purpose push-pull output
    GPIO_AT32F413_OUT_OPEN_DRAIN = 1,      //01: General-purpose open-drain output
    GPIO_AT32F413_OUT_ALT_PUSH_PULL = 2,   //10: Alternate function push-pull output
    GPIO_AT32F413_OUT_ALT_OPEN_DRAIN = 3,  //11: Alternate function open-drain output
    GPIO_AT32F413_OUT_UNDEF = 4,
} GpioAt32F413OutIOFCy_t;


//GPIOx mode configuration (y=0~7)
typedef enum {
    GPIO_AT32F413_IOM_Y_INPUT = 0,                //00: Input mode (reset state)
    GPIO_AT32F413_IOM_Y_OUT_LARGE_SOURCING = 1,   //01: Output mode, large  sourcing/sinking strength
    GPIO_AT32F413_IOM_Y_OUT_NORMAL_SOURCING2 = 2, //10: Output mode, normal sourcing/sinking strength
    GPIO_AT32F413_IOM_Y_OUT_NORMAL_SOURCING3 = 3, //11: Output mode, normal sourcing/sinking strength
    GPIO_AT32F413_IOM_Y_UNDEF = 4,
} GpioAt32F413_IOMCy_t;




#ifdef __cplusplus
}
#endif

#endif /* GPIO_AT32_CONST_H  */
