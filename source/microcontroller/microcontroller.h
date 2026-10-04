#ifndef MICROCONTROLLER_H
#define MICROCONTROLLER_H

#ifndef HAS_MICROCONTROLLER
#error  "+HAS_MICROCONTROLLER"
#endif

#include "std_includes.h"
#include "microcontroller_types.h"

#include "microcontroller_diag.h"

#ifdef HAS_FC7300F8MDT
#include "fc7300f8mdt.h"
#endif

#ifdef HAS_AT32F413RC
#include "at32f413rc.h"
#endif

#ifdef HAS_AT32F435ZM
#include "at32f435zm.h"
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

#ifdef HAS_YTM32B1ME05G0MLQ
#include "ytm32b1me05g0mlq.h"
#endif

#ifdef HAS_STM32F401RE
#include "stm32f401re.h"
#endif

#ifdef HAS_STM32F407VG
#include "stm32f4xx.h"
#include "stm32f407vg.h"
#endif

#ifdef HAS_STM32F407VE
#include "stm32f407xx.h"
#include "stm32f407ve.h"
#endif

#ifdef HAS_STM32F446RE
#include "stm32f446re.h"
#endif

#ifdef HAS_STM32F407ZG
#include "stm32f407zg.h"
#endif

#ifdef HAS_STM32F415RG
#include "stm32f415rg.h"
#endif

#ifdef HAS_STM32F413ZG
#include "stm32f413zg.h"
#endif


#ifdef HAS_STM32F746NG
#include "stm32f746ng.h"
#endif


bool microcontroller_init(void);
bool microcontroller_custom_init(void);
McuPhyAddress_t mcu_phy_assress_classify(const uint32_t phy_address);
bool is_mem_addr(uint32_t addr);
bool mcu_is_text_addr(const uint32_t address);

#endif /* MICROCONTROLLER_H */
