#ifndef GPIO_MCAL_TYPES_H
#define GPIO_MCAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

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
    Pad_t pad;
    uint16_t mcu_pin; /*up to pin 400*/
    char* name;
    bool valid;
} PinData_t;

typedef struct {
    uint16_t gpio_pin;
    uint32_t int_cnt;
} PinInt_t;

typedef struct {
    uint32_t mux; /*STM32-4byte, AT32-1byte*/
    Pad_t pad;
    uint8_t mcu_pin;
    uint8_t config_number;
#ifdef HAS_LOG
    char* name;
    char* function;
    char* connector1;
    char* connector2;
    bool load_detect;
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

#ifdef __cplusplus
}
#endif

#endif /* GPIO_MCAL_TYPES_H  */
