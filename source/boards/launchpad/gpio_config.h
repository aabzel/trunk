#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#include <stdint.h>

#include "gpio_types.h"

#define GPIO_COUNT 2

extern const GpioConfig_t GpioConfig[];

void gpioButtonFxn1(uint_least8_t index);
uint32_t gpio_get_cnt(void);
uint16_t pin_config_get_cnt(void);

extern GPIO_CallbackFxn gpioCallbackFunctions[GPIO_COUNT];
extern PIN_Config BoardGpioInitTableLUT[] ;
extern GPIO_PinConfig gpioPinConfigs[GPIO_COUNT] ;

#endif /* GPIO_CONFIG_H  */
