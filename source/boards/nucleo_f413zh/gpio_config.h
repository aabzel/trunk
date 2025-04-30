#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#include <stdint.h>

#include "gpio_types.h"
//#include "sys_config.h"

extern GpioConfig_t GpioConfig[];
uint32_t gpio_get_cnt(void);

#endif /* GPIO_CONFIG_H  */
