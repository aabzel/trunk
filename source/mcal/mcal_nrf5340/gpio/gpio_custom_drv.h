#ifndef GPIO_NRFX_DRV_H
#define GPIO_NRFX_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "gpio_custom_const.h"
#include "gpio_custom_types.h"
#include "nrf_gpio.h"

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

#ifndef HAS_NRFX
#warning "+HAS_NRFX"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

nrf_gpio_pin_mcusel_t nrf_gpio_pin_mcu_select_get(uint32_t pin_number);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_NRFX_DRV_H  */
