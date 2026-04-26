#ifndef GPIO_DAC_MCAL_H
#define GPIO_DAC_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "gpio_dac_config.h"
#include "gpio_dac_types.h"
#ifdef HAS_GPIO_DAC_DIAG
#include "gpio_dac_diag.h"
#endif

/* API */
GpioDacHandle_t* GpioDacGetNode(uint8_t num);
const GpioDacConfig_t* GpioDacGetConfig(uint8_t num);
bool GpioDacIsValidConfig(const GpioDacConfig_t* const Config);


bool gpio_dac_mcal_init(void);
bool gpio_dac_init_one(uint8_t num);

bool gpio_dac_proc_one(uint8_t num);
bool gpio_dac_proc(void);

/*setters*/
bool gpio_dac_write(uint8_t num, uint8_t * data, const uint32_t size);

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* GPIO_DAC_MCAL_H */
