
#ifndef MICROCONTROLLER_DRV_H
#define MICROCONTROLLER_DRV_H

#include "std_includes.h"
#include "microcontroller_const.h"

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

#ifndef HAS_MICROCONTROLLER
#error  "+HAS_MICROCONTROLLER"
#endif

#ifdef HAS_AT32F413RC
#include "at32f413rc.h"
#endif

#ifdef HAS_AT32F435ZM
#include "at32f435zm.h"
#endif

#ifdef HAS_YTM32B1ME05G0MLQ
#include "ytm32b1me05g0mlq.h"
#endif

#ifdef HAS_STM32F407VG
#include "stm32f407vg.h"
#endif


#ifdef HAS_PINS
bool mcu_get_prev_pin(PinData_t cur_pin, PinData_t* const prev_pin);
bool mcu_get_next_pin(PinData_t cur_pin, PinData_t* const next_pin);
bool mcu_get_up_pin(PinData_t cur_pin, PinData_t* const up_pin);
bool mcu_get_down_pin(PinData_t cur_pin, PinData_t* const down_pin);
bool mcu_get_right_pin(PinData_t cur_pin, PinData_t* const right_pin);
bool mcu_get_left_pin(PinData_t cur_pin, PinData_t* const left_pin);
#endif

McuPhyAddress_t mcu_phy_assress_classify(const uint32_t phy_address);
bool mcu_is_text_addr(const uint32_t address);

#endif /* MICROCONTROLLER_DRV_H */
