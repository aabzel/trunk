#ifndef MICROCONTROLLER_H
#define MICROCONTROLLER_H

#ifndef HAS_MICROCONTROLLER
#error  "+HAS_MICROCONTROLLER"
#endif

#include "std_includes.h"
#include "microcontroller_types.h"

#ifdef HAS_FC7300F8MDT
#include "fc7300f8mdt.h"
#endif

#ifdef HAS_DUMMY_MCU
#include "dummy_mcu.h"
#endif

#ifdef HAS_K1948BK018
#include "k1948bk018.h"
#endif

#ifdef HAS_NRF5340
#include "nrf5340.h"
#endif

#ifdef HAS_STM32F401RE
#include "stm32f401re.h"
#endif

#ifdef HAS_STM32F407VG
#include "stm32f407vg.h"
#endif

#ifdef HAS_STM32F407VE
#include "stm32f407ve.h"
#endif

#ifdef HAS_STM32F407ZG
#include "stm32f407zg.h"
#endif

#ifdef HAS_STM32F415RG
#include "stm32f415rg.h"
#endif


bool microcontroller_init(void);

#endif /* MICROCONTROLLER_H */
