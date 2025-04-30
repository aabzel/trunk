#ifndef GPIO_DIAG_H
#define GPIO_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "gpio_drv.h"

const char* gpio_dir2str(DioDir_t gpio_dir);
const char* get_gpio_mode(uint8_t io_pin);
const char* get_gpio_type(uint8_t io_pin);
const char* get_gpio_alter_fun(uint8_t dio_pin);
const char* get_gpio_pull_mode(uint8_t dio_pin);
const char* get_gpio_edge(uint8_t dio_pin);

#endif /* GPIO_DIAG_H  */
