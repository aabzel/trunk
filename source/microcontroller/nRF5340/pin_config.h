
#ifndef MCU_PIN_CONFIG_H
#define MCU_PIN_CONFIG_H

#include "gpio_types.h"

#ifdef HAS_MBR
#error "MBR does not need GPIO"
#endif

extern const PinData_t PinConfig[];
uint16_t pin_get_cnt(void);

#endif /* MCU_PIN_CONFIG_H */
