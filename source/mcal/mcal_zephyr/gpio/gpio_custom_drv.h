#ifndef GPIO_ZEPHYR_DRV_H
#define GPIO_ZEPHYR_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "gpio_bsp.h"
#include "gpio_types.h"
#include "gpio_custom_const.h"
#include "gpio_custom_types.h"

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

#ifndef HAS_ZEPHYR
#error "+HAS_ZEPHYR"
#endif

GpioDir_t gpio_get_dir(uint8_t pad_num);
GpioPullMode_t gpio_get_pull(uint8_t pad_num);
bool gpio_init(void);
bool gpio_set_pull(uint8_t pad_num, GpioPullMode_t pull_code);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_ZEPHYR_DRV_H  */
