#ifndef STM32F407ZG_H
#define STM32F407ZG_H

#include <stm32f407xx.h>

#include "stm32f407zg_const.h"

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif


/*MBR does not need GPIO*/
#if defined(HAS_GPIO) && defined(HAS_PINS)
extern const PinData_t PinConfig[];
uint16_t pin_get_cnt(void);
#endif

#endif /* STM32F407ZG_H */
