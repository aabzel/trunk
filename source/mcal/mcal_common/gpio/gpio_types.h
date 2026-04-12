#ifndef GPIO_MCAL_TYPES_H
#define GPIO_MCAL_TYPES_H

#include "std_includes.h"
#include "microcontroller_types.h"
#include "gpio_const.h"

#ifdef HAS_EXT_INT
#include "ext_int_const.h"
#endif

#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_types.h"
#else

typedef union {
    uint8_t byte;
    struct {
        uint8_t pin  : 4; /**/
        uint8_t port : 4; /* */
    };
}Pad_t;

#endif /*HAS_GPIO_CUSTOM*/

typedef struct {
    GpioLogicLevel_t Set;
    GpioLogicLevel_t Real;
} GpioLogicLevelState_t;



typedef struct {
    uint16_t gpio_pin;
    uint32_t int_cnt;
} PinInt_t;

typedef struct {
    uint32_t mux; /*STM32-4byte, AT32-1byte*/
    Pad_t Pad;
    uint16_t mcu_pin;
#ifdef HAS_TI
    uint8_t config_number;
#endif
#ifdef HAS_LOG
    char* name;
    char* function;
    char* connector1;
    char* connector2;
    bool testable;
#endif
    GpioDir_t dir;
    GpioSpeed_t speed;
    GpioPullMode_t pull;
    GpioApiMode_t mode;
    GpioDriveSelect_t drive_select;
    GpioLogicLevel_t logic_level;
#ifdef HAS_EXT_INT
    PinIntEdge_t edge;
#endif
} GpioConfig_t;


#endif /* GPIO_MCAL_TYPES_H  */
