#ifndef PIN_CONFIG
#define PIN_CONFIG

#include <stdint.h>

#include "gpio_mcal.h"
#include "gpio_types.h"

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

#ifndef HAS_MCU
#error "+HAS_MCU"
#endif

extern const GpioConfig_t GpioConfig[];

uint32_t gpio_get_cnt(void);

#endif /* PIN_CONFIG  */
