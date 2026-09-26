#ifndef GPIO_X86_CONST_H
#define GPIO_X86_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

//[0   31] 5 bit for pin number 2^5=32
#define GPIO_PIN_COUNT 31
#define GPIO_PIN_UNDEF 32

#if 0
//[0 4] 3 bit for port number 2^3=8
typedef enum {
    PORT_A = 0,
    PORT_B = 1,
    PORT_C = 2,
    PORT_D = 3,
    PORT_E = 4,

    PORT_UNDEF = 5,
} Port_t;
#endif

typedef enum {
    X86_PULL_AIR = 0,
    X86_PULL_UP = 1,
    X86_PULL_DOWN= 2,

    X86_PULL_UNDEF = 3,
} GpioFc7300xPull_t;


typedef enum {
    SPEED_LOW_SPEED = 0,
    SPEED_MEDIUM_SPEED = 1,
    SPEED_FAST_SPEED = 2,
    SPEED_HIGH_SPEED = 3,
    SPEED_UNDEF = 4,
} GpioFc7300xSpeed_t;

typedef enum {
    OUT_TYPE_PUSH_PULL = 0,
    OUT_TYPE_OPEN_DRAIN = 1,
    OUT_TYPE_UNDEF = 2,
} GpioOutType_t;


typedef enum {
    GPIO_OUT_DATA_TYPE_PULL_DOWN = 0, //0: Pull-down
    GPIO_OUT_DATA_TYPE_PULL_UP = 1,   //1: Pull-up
    GPIO_OUT_DATA_TYPE_UNDEF = 2,
} GpioFc7300xOutputData_t;

//6.3.1 GPIO configuration register (GPIOx_CFGR) (x=A..H)
typedef enum {
    GP_X86_MODE_INPUT = 0,            /*Input mode (reset state)*/
    GP_X86_MODE_GNRL_PURPOSE_OUT = 1, /*General-purpose output mode*/
    GP_X86_MODE_ALT_FUN = 2,          /*Multiplexed function mode*/
    GP_X86_MODE_ANALOG = 3,           /*Analog mode*/

    GP_X86_MODE_UNDEF = 4,
} GpioFc7300xMode_t;

//see 6.3.1 GPIO configuration register low (GPIOx_CFGLR) (x=A..F)
typedef enum {
	GPIO_X86_MODE_ANALOG = 0,             /*00: Analog mode*/
    GPIO_X86_MODE_FLOATING_INPUT = 1,     /*01: Floating input (after reset)*/
    GPIO_X86_MODE_PULL_UP_DOWN_INPUT = 2, /*10: Pull-up/pull-down input*/
    GPIO_X86_MODE_RESERVED = 3,           /*11: Reserved(Open-drain)*/
    GPIO_X86_MODE_UNDEF = 4,
} GpioFc7300x_IOFCy_t;


//see 6.3.1 GPIO configuration register low (GPIOx_CFGLR) (x=A..F)
typedef enum {
	GPIO_X86_OUT_PUSH_PULL = 0,       //00: General-purpose push-pull output
    GPIO_X86_OUT_OPEN_DRAIN = 1,      //01: General-purpose open-drain output
    GPIO_X86_OUT_ALT_PUSH_PULL = 2,   //10: Alternate function push-pull output
    GPIO_X86_OUT_ALT_OPEN_DRAIN = 3,  //11: Alternate function open-drain output
    GPIO_X86_OUT_UNDEF = 4,
} GpioFc7300xOutIOFCy_t;


//GPIOx mode configuration (y=0~7)
typedef enum {
    GPIO_X86_IOM_Y_INPUT = 0,                //00: Input mode (reset state)
    GPIO_X86_IOM_Y_OUT_LARGE_SOURCING = 1,   //01: Output mode, large  sourcing/sinking strength
    GPIO_X86_IOM_Y_OUT_NORMAL_SOURCING2 = 2, //10: Output mode, normal sourcing/sinking strength
    GPIO_X86_IOM_Y_OUT_NORMAL_SOURCING3 = 3, //11: Output mode, normal sourcing/sinking strength
    GPIO_X86_IOM_Y_UNDEF = 4,
} GpioFc7300x_IOMCy_t;




#ifdef __cplusplus
}
#endif

#endif /* GPIO_X86_CONST_H  */
