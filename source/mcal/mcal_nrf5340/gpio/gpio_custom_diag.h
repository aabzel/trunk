#ifndef GPIO_NRF_DIAG_H
#define GPIO_NRF_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "nrf_gpio.h"
#include "gpio_custom_const.h"

const char* McuSel2Str(nrf_gpio_pin_mcusel_t mcusel);
const char* PinCoreSel2Str(GpioPinMcuSel_t core_sel);
const char* GpioPort2Str(uint8_t port);

#endif /* GPIO_NRF_DIAG_H  */
