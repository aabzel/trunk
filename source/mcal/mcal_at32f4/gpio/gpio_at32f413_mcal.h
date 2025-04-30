#ifndef GPIO_AT32F413_EXT_H
#define GPIO_AT32F413_EXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio_types.h"

GpioApiMode_t gpio_at32f413_mode_get(Pad_t Pad);
GpioDir_t gpio_at32f413_dir_get(Pad_t Pad);
GpioPullMode_t gpio_at32f413_pull_get(Pad_t Pad);
bool gpio_at32f413_pin_mux_get(Pad_t Pad, uint8_t* const mux);
bool gpio_at32f413_pin_fun_get(Pad_t Pad, GpioPinFunction_t* const function);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_AT32F413_EXT_H  */
