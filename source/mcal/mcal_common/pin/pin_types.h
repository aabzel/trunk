#ifndef PIN_MCAL_TYPES_H
#define PIN_MCAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "microcontroller_types.h"
#include "gpio_types.h"
#include "pin_types.h"
#ifdef HAS_EXT_INT
#include "ext_int_const.h"
#endif

#ifdef HAS_PIN_CUSTOM
#include "pin_custom_types.h"
#else
#endif /*HAS_PIN_CUSTOM*/


typedef struct {
    Pad_t pad;
    uint16_t mcu_pin; /*up to pin 400*/
    char* name;
    bool valid;
} PinData_t;



typedef struct {
    Pad_t pad;
    uint8_t mcu_pin;
#ifdef HAS_LOG
    char* name;
#endif
} PinConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* PIN_MCAL_TYPES_H  */
