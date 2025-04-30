#include "gpio_drv.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bit_utils.h"
#include "board_layout.h"
#include "data_utils.h"
#include "driver/gpio.h"
#include "gpio_common.h"
#include "none_blocking_pause.h"

static gpio_mode_t GpioDir2Mode(DioDir_t dir) {
    gpio_mode_t gpio_mode = GPIO_MODE_INPUT;
    switch(dir) {
    case GPIO_DIR_IN:
        gpio_mode = GPIO_MODE_INPUT;
        break;
    case GPIO_DIR_OUT:
        gpio_mode = GPIO_MODE_OUTPUT;
        break;
    case GPIO_DIR_OUT_OD:
        gpio_mode = GPIO_MODE_OUTPUT_OD;
        break;
    case GPIO_DIR_INOUT_OD:
        gpio_mode = GPIO_MODE_INPUT_OUTPUT_OD;
        break;
    case GPIO_DIR_INOUT:
        gpio_mode = GPIO_MODE_INPUT_OUTPUT;
        break;
    case GPIO_DIR_NONE:
        gpio_mode = GPIO_MODE_DISABLE;
        break;
    case GPIO_DIR_UNDEF:
        gpio_mode = GPIO_MODE_INPUT;
        break;
    default:
        break;
    }
    return gpio_mode;
}

static gpio_pullup_t is_gpio_pull_up_mode(PullMode_t pull_mode) {
    gpio_pullup_t is_pull_up = GPIO_PULLUP_DISABLE;
    switch(pull_mode) {
    case PULL_UP_DOWN:
        is_pull_up = GPIO_PULLUP_ENABLE;
        break;
    case PULL_DOWN:
        is_pull_up = GPIO_PULLUP_DISABLE;
        break;
    case PULL_UP:
        is_pull_up = GPIO_PULLUP_ENABLE;
        break;
    case PULL_AIR:
        is_pull_up = GPIO_PULLUP_DISABLE;
        break;
    case PULL_UNDEF:
        is_pull_up = GPIO_PULLUP_DISABLE;
        break;
    default:
        is_pull_up = GPIO_PULLUP_DISABLE;
        break;
    }
    return is_pull_up;
}

static gpio_pulldown_t is_gpio_pull_down_mode(PullMode_t pull_mode) {
    gpio_pulldown_t is_pull_down = GPIO_PULLDOWN_DISABLE;
    switch(pull_mode) {
    case PULL_UP_DOWN:
        is_pull_down = GPIO_PULLDOWN_ENABLE;
        break;
    case PULL_DOWN:
        is_pull_down = GPIO_PULLDOWN_ENABLE;
        break;
    case PULL_UP:
        is_pull_down = GPIO_PULLDOWN_DISABLE;
        break;
    case PULL_AIR:
        is_pull_down = GPIO_PULLDOWN_DISABLE;
        break;
    case PULL_UNDEF:
        is_pull_down = GPIO_PULLDOWN_DISABLE;
        break;
    default:
        is_pull_down = GPIO_PULLDOWN_DISABLE;
        break;
    }
    return is_pull_down;
}
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html
bool gpio_init(void) {
    bool out_res = true;
    uint8_t p = 0;
    esp_err_t ret = ESP_OK;
    uint32_t cnt = pin_get_cnt();
    uint32_t init_cnt = 0;
    for(p = 0; p < cnt; p++) {
        if((PIN_NO_INIT != PinTable[p].level) && (0 <= PinTable[p].dio) && (39 != PinTable[p].dio)) {
            init_cnt++;
            printf("\n\rDio %d", PinTable[p].dio);
            if(1 == init_cnt) {
                // p=cnt*2;
            }
            gpio_config_t ioConf = {};
            ioConf.intr_type = GPIO_INTR_DISABLE;
            ioConf.mode = GpioDir2Mode(PinTable[p].dir);
            ioConf.pin_bit_mask = 1ULL << (PinTable[p].dio);
            ioConf.pull_down_en = is_gpio_pull_down_mode(PinTable[p].pull_mode);
            ioConf.pull_up_en = is_gpio_pull_up_mode(PinTable[p].pull_mode);
            gpio_reset_pin(PinTable[p].dio);
            ret = gpio_config(&ioConf); // hang on
            // gpio_iomux_in(PinTable[p].dio, uint32_t signal_idx);
            if(ESP_OK == ret) {

                ret = gpio_intr_disable(PinTable[p].dio);
                gpio_set_direction(PinTable[p].dio, GpioDir2Mode(PinTable[p].dir));
                if((0 == PinTable[p].level) || (1 == PinTable[p].level)) {
                    gpio_set_level(PinTable[p].dio, (uint32_t)PinTable[p].level);
                }
            } else {
                printf("\n\rDio %d Error", PinTable[p].dio);
                out_res = false;
            }
        }
    }
    return out_res;
}

bool gpio_get_state(int8_t dio_number, uint8_t* logic_level) {
    bool res = false;
    if(logic_level) {
        if(0 < dio_number) {
            int value = gpio_get_level(dio_number);
            (*logic_level) = (uint8_t)value;
            res = true;
        }
    }
    return res;
}

uint8_t gpio_read(int8_t dio_number) {
    uint8_t logic_level = 0x55;
    bool res = gpio_get_state(dio_number, &logic_level);
    if(false == res) {
        logic_level = 0xEE;
    }
    return logic_level;
}

bool gpio_set_state(int8_t dio_number, uint8_t logic_level) {
    gpio_set_level(dio_number, (uint32_t)logic_level);
    return true;
}

bool is_edge_irq_en(int8_t gpio_num) {
    bool res = false;
    return res;
}

PullMode_t gpio_get_pull_mode(int8_t gpio_num) {
    PullMode_t pull_mode = PULL_UNDEF;
    return pull_mode;
}

bool gpio_set_pin_pull_mode(int8_t gpio_num, PullMode_t pull_mode) {
    bool res = false;
    esp_err_t ret = ESP_ERR_INVALID_ARG;
    gpio_num_t gpio_n = (gpio_num_t)gpio_num;
    if(PULL_UP == pull_mode) {
        ret = gpio_pullup_en(gpio_n);
    } else if(PULL_AIR == pull_mode) {
        ret = gpio_pullup_dis(gpio_n);
        if(ESP_OK == ret) {
            ret = gpio_pulldown_dis(gpio_n);
        }
    } else if(PULL_DOWN == pull_mode) {
        ret = gpio_pulldown_en(gpio_n);
    } else if(PULL_UP_DOWN == pull_mode) {
        ret = gpio_pullup_en(gpio_n);
        if(ESP_OK == ret) {
            ret = gpio_pulldown_en(gpio_n);
        }
    } else {
        res = false;
    }
    if(ESP_OK == ret) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

static gpio_pull_mode_t GpioPull2Esp32Pull(PullMode_t pull_mode) {
    gpio_pull_mode_t esp32_pull = GPIO_FLOATING;
    switch(pull_mode) {
    case PULL_UP_DOWN:
        esp32_pull = GPIO_PULLUP_PULLDOWN;
        break;
    case PULL_DOWN:
        esp32_pull = GPIO_PULLDOWN_ONLY;
        break;
    case PULL_UP:
        esp32_pull = GPIO_PULLUP_ONLY;
        break;
    case PULL_AIR:
        esp32_pull = GPIO_FLOATING;
        break;
    case PULL_UNDEF:
        esp32_pull = GPIO_FLOATING;
        break;
    default:
        esp32_pull = GPIO_FLOATING;
        break;
    }
    return esp32_pull;
}

bool gpio_set_pull(int8_t gpio_num, PullMode_t pull_mode) {
    bool res = false;
    gpio_pull_mode_t esp32_pull = GpioPull2Esp32Pull(pull_mode);
    esp_err_t ret = gpio_set_pull_mode((gpio_num_t)gpio_num, esp32_pull);
    if(ESP_OK == ret) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool gpio_get_in_mode(int8_t gpio_num) {
    bool res = false;
    return res;
}

bool gpio_set_in_mode(int8_t gpio_num, bool is_in_mode) {
    bool res = false;

    return res;
}

uint8_t get_aux_num(int8_t io_pin) {
    uint8_t aux_pin = 0;

    return aux_pin;
}

bool gpio_toggle(int8_t dio_number) {
    bool res = false;
    static int cur_state = 0;
    esp_err_t stat = ESP_OK;
    switch(cur_state) {
    case 0:
        stat = gpio_set_level((gpio_num_t)dio_number, (uint32_t)1);
        cur_state = 1;
        break;
    case 1:
        stat = gpio_set_level((gpio_num_t)dio_number, (uint32_t)0);
        cur_state = 0;
        break;
    }
    if(ESP_OK == stat) {
        res = true;
    }
    return res;
}

uint32_t gpio_get_alter_fun(int8_t gpio_num) { return 0; }

DioDir_t gpio_get_dir(int8_t gpio_num) {
    DioDir_t dir = GPIO_DIR_UNDEF;
    // TODO
    return dir;
}

bool gpio_set_dir(int8_t gpio_num, DioDir_t des_dir) {
    bool res = false;
    gpio_mode_t gpio_mode = GpioDir2Mode(des_dir);
    esp_err_t ret;
    ret = gpio_set_direction((gpio_num_t)gpio_num, gpio_mode);
    if(ESP_OK == ret) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
