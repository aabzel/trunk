#include "gpio_diag.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bit_utils.h"
#include "gpio_drv.h"

const char* get_gpio_mode(uint8_t pin) {
    char* name = "_";

    return name;
}

const char* get_gpio_alter_fun(uint8_t dio_pin) {
    const char* name = "?";

    return name;
}

const char* get_gpio_pull_mode(uint8_t dio_pin) {
    char* pull_name = "?";

    return pull_name;
}

const char* get_gpio_type(uint8_t dio_pin) {
    const char* iomode_name = "?";
    return iomode_name;
}

const char* get_gpio_edge(uint8_t dio_pin) {
    const char* edge_name = "?";

    return edge_name;
}

const char* gpio_dir2str(DioDir_t gpio_dir) {
    const char* name = "?";

    return name;
}
