
#ifndef STM32F411CE_H
#define STM32F411CE_H

#include <stm32f411xe.h>

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif
#include "macro_utils.h"
#include "stm32f411ce_const.h"

/*MBR does not need GPIO*/
#if defined(HAS_GPIO) && defined(HAS_PINS)
extern const PinData_t PinConfig[];
uint16_t pin_get_cnt(void);
#endif

#endif /* STM32F411CE_H */
