#ifndef TEST_DW1000_GPIO_H
#define TEST_DW1000_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"
#include "dw1000_gpio_types.h"

#ifndef HAS_DW1000
#error "+HAS_DW1000"
#endif

#ifndef HAS_TEST_DW1000
#error "+HAS_TEST_DW1000"
#endif

bool test_dw1000_gpio_pins(void);
bool test_dw1000_gpio_init(void);
bool test_dw1000_gpio_pin(Dw1000GpioNum_t pad_num);
bool test_dw1000_gpio_types(void);
bool test_dw1000_gpio_set(void);
bool test_dw1000_gpio_set_dir(void);
bool test_dw1000_gpio_read_0v(void);
bool test_dw1000_gpio_read_3v(void);
bool test_dw1000_gpio_set_multiple(void);
bool test_dw1000_gpio_cross(void);
bool test_dw1000_gpio_hash_maps(void);

#define TEST_SUIT_DW1000_GPIO                                    \
    {"dw1000_gpio_init", test_dw1000_gpio_init},                \
    {"dw1000_gpio_types", test_dw1000_gpio_types},              \
    {"dw1000_gpio_read_0v", test_dw1000_gpio_read_0v},          \
    {"dw1000_gpio_read_3v", test_dw1000_gpio_read_3v},          \
    {"dw1000_gpio_set_dir", test_dw1000_gpio_set_dir},          \
    {"dw1000_gpio_set_multiple", test_dw1000_gpio_set_multiple},          \
    {"dw1000_gpio_cross", test_dw1000_gpio_cross},          \
    {"dw1000_gpio_pins", test_dw1000_gpio_pins},          \
    {"dw1000_gpio_hash_maps", test_dw1000_gpio_hash_maps},          \
    {"dw1000_gpio_set", test_dw1000_gpio_set},

#ifdef __cplusplus
}
#endif

#endif /* TEST_DW1000_GPIO_H */
