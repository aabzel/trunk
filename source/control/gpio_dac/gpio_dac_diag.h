#ifndef GPIO_DAC_DIAG_H
#define GPIO_DAC_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "gpio_dac_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_GPIO_DAC
#error "+HAS_GPIO_DAC"
#endif

#ifndef HAS_GPIO_DAC_DIAG
#error "+HAS_GPIO_DAC_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool gpio_dac_diag(void);
bool gpio_dac_diag_one(uint8_t num);
const char* GpioDacConfigToStr(const GpioDacConfig_t* const Config);
const char* GpioDacNodeToStr(const GpioDacHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_DAC_DIAG_H  */
