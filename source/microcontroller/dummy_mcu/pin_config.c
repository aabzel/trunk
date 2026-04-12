#include "pin_config.h"

#include "gpio_types.h"

const PinData_t PinConfig[] = {
};

uint32_t pin_get_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(PinConfig);
    return cnt;
}

