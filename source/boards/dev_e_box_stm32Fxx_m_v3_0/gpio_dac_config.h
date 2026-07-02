#ifndef GPIO_DAC_CONFIG_H
#define GPIO_DAC_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "gpio_dac_types.h"
#include "gpio_dac_dep.h"

extern const GpioDacConfig_t GpioDacConfig[];
extern GpioDacHandle_t GpioDacInstance[];

uint32_t gpio_dac_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* GPIO_DAC_CONFIG_H */
