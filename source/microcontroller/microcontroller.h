#ifndef MICROCONTROLLER_H
#define MICROCONTROLLER_H

#ifndef HAS_MICROCONTROLLER
#error  "+HAS_MICROCONTROLLER"
#endif

//#include "macro_utils.h"

#ifdef HAS_K1948BK018
#include "k1948bk018.h"
#endif

#ifdef HAS_NRF5340
#include "nrf5340.h"
#endif

#ifdef HAS_STM32F407ZG
#include "stm32f407zg.h"
#endif

#ifdef HAS_STM32F415RG
#include "stm32f415rg.h"
#endif


#include "std_includes.h"
#include "microcontroller_types.h"

#ifdef HAS_PINS

extern const PinData_t PinConfig[];

uint16_t pin_get_cnt(void);
#endif
bool mcu_init(void);

#endif /* MICROCONTROLLER_H */
