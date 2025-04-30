
#ifndef STM32F413ZH_H
#define STM32F413ZH_H

#include <stm32f413xx.h>

#include "macro_utils.h"
#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

#include "stm32f413zh_const.h"

/*MBR does not need GPIO*/
#if defined(HAS_GPIO) && defined(HAS_PINS)
extern const PinData_t PinConfig[];
uint16_t pin_get_cnt(void);
#endif

#endif /* STM32F413ZH_H */
