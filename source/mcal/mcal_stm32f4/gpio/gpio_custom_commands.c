#include "gpio_custom_commands.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
#include "gpio_custom_drv.h"
#include "gpio_diag.h"
#include "gpio_custom_diag.h"
#include "log_utils.h"
#include "log.h"
#include "log_constants.h"
#include "str_utils.h"
#include "sys_config.h"
#include "table_utils.h"
#include "writer_config.h"

static bool diag_gpio_interrupt(char* key_word1, char* key_word2) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"}, {5, "gpioPin"}, {5, "mask"}, {5, "pend"}, {6, "edge"}, {6, "ItCn"}};
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t pin = 0;
    char log_line[120];
    for(pin = 0; pin <= 15; pin++) {
        //#define __HAL_GPIO_EXTI_GET_IT(__EXTI_LINE__) (EXTI->PR & (__EXTI_LINE__))
#ifdef HAS_PIN_INT
        PinInt_t* PinIntNode = PinIntGetNode(pin);
        PinIntEdge_t edge = pin_get_edge(pin);
#endif
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %2u  " TSEP, log_line, pin);
        snprintf(log_line, sizeof(log_line), "%s %3s " TSEP, log_line, OnOff2Str(pin_get_int(pin)));
        snprintf(log_line, sizeof(log_line), "%s %3s " TSEP, log_line, OnOff2Str(pin_get_int_pend(pin)));
#ifdef HAS_PIN_INT
        snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, GpioEdge2Str(edge));
        if(PinIntNode) {
            snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, (unsigned int)PinIntNode->int_cnt);
        }
#endif
        if(is_contain(log_line, key_word1, key_word2)) {
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, log_line);
            num++;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool gpio_interrupt_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }
    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        LOG_ERROR(GPIO, "Usage: gl keyWord");
    }
    if(res) {
        res = diag_gpio_interrupt(keyWord1, keyWord2);
    }
    return res;
}

bool sw_interrupt_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t pin_num = 0;
    uint32_t mask = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &pin_num);
        if(res) {
            mask |= (1 << pin_num);
        }
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &pin_num);
        if(res) {
            mask |= (1 << pin_num);
        }
    }
    if(res) {
        res = generate_sw_int(mask);
    }
    return res;
}

bool ext_int_mask_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t pin_num = 0;
    uint32_t mask = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &pin_num);
        if(res) {
            mask |= (1 << pin_num);
        }
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &pin_num);
        if(res) {
            mask |= (1 << pin_num);
        }
    }
    if(res) {
        res = ext_int_set_mask(mask);
    }
    return res;
}

bool ext_int_mask_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t pin_num = 0;
    uint32_t mask = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &pin_num);
        if(res) {
            mask |= (1 << pin_num);
        }
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &pin_num);
        if(res) {
            mask |= (1 << pin_num);
        }
    }
    if(res) {
        res = ext_int_reset_mask(mask);
    }
    return res;
}



