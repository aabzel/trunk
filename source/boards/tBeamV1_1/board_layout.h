#ifndef BOARD_LAYOUT_H
#define BOARD_LAYOUT_H

#include <stdint.h>

#include "sys_config.h"

#include "gpio_common.h"

#define PIN_NO_INIT 0x05

#define PIN_NAME_LEN 10
typedef struct xPin_t {
    int16_t dio;
    uint8_t mcu_pin;
    DioDir_t dir;
    char name[PIN_NAME_LEN];
    PullMode_t pull_mode;
    int8_t level;
} Pin_t;

extern const Pin_t PinTable[];

uint32_t pin_get_cnt(void);

#endif /* BOARD_LAYOUT_H  */
