#ifndef TEST_GPIO_H
#define TEST_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "sys_config.h"
#include "test_hw_dep_check.h"
#include "gpio_types.h"

#ifndef HAS_GPIO
#error "It is needed HAS_GPIO option for that component"
#endif

bool test_gpio_pull_mode(Pad_t Pad, GpioPullMode_t des_pull) ;

bool test_gpio_pin(Pad_t Pad);
bool test_gpio_write(void);
bool test_gpio_types(void);
bool test_gpio_pull(void);
bool test_gpio_const(void);

#define TEST_SUIT_GPIO                    \
    {"gpio_const", test_gpio_const},      \
    {"gpio_pull", test_gpio_pull},        \
    {"gpio_write", test_gpio_write},      \
    {"gpio_types", test_gpio_types},

#ifdef __cplusplus
}
#endif

#endif /* TEST_GPIO_H */
