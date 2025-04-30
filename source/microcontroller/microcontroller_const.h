#ifndef MICROCONTROLLER_CONST_H
#define MICROCONTROLLER_CONST_H


typedef enum{
    MCU_PHY_ADDR_UNDEF = 0,
    MCU_PHY_ADDR_SRAM = 1,
    MCU_PHY_ADDR_EEPROM = 2,
    MCU_PHY_ADDR_SPIFI = 3,
    MCU_PHY_ADDR_PERIPHERY = 4,
    MCU_PHY_ADDR_FLASH = 5,

    MCU_PHY_ADDR_UNUSED = 6,
}McuPhyAddress_t;

#ifdef HAS_K1948BK018
#include "k1948bk018_const.h"
#include "mcu32_memory_map.h"
#endif

#ifdef HAS_AT32F413RC
#include "at32f413rc_const.h"
#include "at32f413.h"
#endif

#ifdef HAS_AT32F435ZM
#include "at32f435zm_const.h"
#ifdef HAS_EHAL
#include "at32f435zm_ehal.h"
#endif
#endif

#ifdef HAS_AT32F437ZM
#include "at32f437zm_const.h"
#ifdef HAS_EHAL
#include "at32f437zm_ehal.h"
#endif
#endif

#ifdef HAS_STM32F407X
#include <stm32f407xx.h>
#endif

#ifdef HAS_STM32F407ZG
#include "stm32f407zg_const.h"
#endif

#ifdef HAS_STM32F407VG
#include "stm32f407vg_const.h"
#endif

#ifdef HAS_YTM32B1ME05G0MLQ
#include "ytm32b1me05g0mlq_const.h"
#endif

#endif /* MICROCONTROLLER_CONST_H */
