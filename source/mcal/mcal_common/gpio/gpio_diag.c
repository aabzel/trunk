#include "gpio_diag.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bit_utils.h"
#include "data_utils.h"
#include "gpio_mcal.h"
#include "log.h"
#include "str_utils.h"
#ifdef HAS_EXT_INT
#include "ext_int_const.h"
#include "ext_int_diag.h"
#endif
#include "table_utils.h"
#include "writer_config.h"

#include "shared_array.h"

const char* GpioAltFun2Str(uint8_t code) {
    snprintf(text, sizeof(text), "AF%u", code);
    return text;
}

const char* GpioFunToStr(GpioPinFunction_t function) {
    const char* name = "?";
    switch((uint8_t)function) {
    case GPIO_FUN_ANALOG:
        name = "Analog";
        break;
    case GPIO_FUN_MULTIPLEXED:
        name = "Mux";
        break;
    case GPIO_FUN_OUT:
        name = "Out";
        break;
    case GPIO_FUN_INPUT:
        name = "Input";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* GpioDir2Str(GpioDir_t code) {
    const char* name = "?";
    switch((uint8_t)code) {
    case GPIO_DIR_IN:
        name = "In";
        break;
    case GPIO_DIR_OUT:
        name = "Out";
        break;
    case GPIO_DIR_OUT_PUSH_PULL:
        name = "OutPp";
        break;
    case GPIO_DIR_OUT_OPEN_DRAIN:
        name = "OutOd";
        break;
    case GPIO_DIR_INOUT:
        name = "Io";
        break;
    case GPIO_DIR_NONE:
        name = "-";
        break;
    case GPIO_DIR_INOUT_OPEN_DRAIN:
        name = "InOd";
        break;
    case GPIO_DIR_UNDEF:
        name = "?";
        break;
    }
    return name;
}

const char* GpioMode2Str(GpioApiMode_t mode) {
    const char* name = "?";
    switch((uint8_t)mode) {
    case GPIO_API_MODE_GPIO:
        name = "GPIO";
        break;
    case GPIO_API_MODE_ALT1:
        name = "ALT1";
        break;
    case GPIO_API_MODE_ALT2:
        name = "ALT2";
        break;
    case GPIO_API_MODE_HW_PWM:
        name = "HwPwm";
        break;
    case GPIO_API_MODE_INPUT:
        name = "In";
        break;
    case GPIO_API_MODE_OUTPUT:
        name = "Out";
        break;
    case GPIO_API_MODE_ANALOG:
        name = "Analog";
        break;
    case GPIO_API_MODE_I2C:
        name = "I2C";
        break;

    case GPIO_DIR_UNDEF:
        name = "?";
        break;
    }
    return name;
}

const char* GpioPad2Str(uint8_t pad) {

    Pad_t Pad;
    Pad.byte = pad;
    if(gpio_is_valid_pad(pad)) {
#ifdef HAS_GPIO_DIAG
        snprintf(text, sizeof(text), "P%s%u", GpioPort2Str(Pad.port), Pad.pin);
#else
        snprintf(text, sizeof(text), "P%u.%u", Pad.port, Pad.pin);
#endif
    } else {
        snprintf(text, sizeof(text), "--");
    }
    return text;
}

const char* GpioPadToStr(Pad_t Pad) {

    if(gpio_is_valid_pad(Pad.byte)) {
#ifdef HAS_GPIO_DIAG
        snprintf(text, sizeof(text), "P%s%u", GpioPort2Str(Pad.port), Pad.pin);
#else
        snprintf(text, sizeof(text), "P%u.%u", Pad.port, Pad.pin);
#endif
    } else {
        snprintf(text, sizeof(text), "--");
    }
    return text;
}

const char* GpioOutType2Str(uint8_t code) {
    char* name = "?";

    return name;
}

const char* GpioSpeed2Str(uint8_t code) {
    char* name = "?";
    return name;
}

const char* GpioLevel2Str(GpioLogicLevel_t code) {
    char* name = "?";
    switch((uint8_t)code) {
    case GPIO_LVL_HI:
        name = "H";
        break;
    case GPIO_LVL_LOW:
        name = "L";
        break;
    }
    return name;
}

const char* GpioPull2Str(GpioPullMode_t code) {
    const char* name = "?";
    switch((uint8_t)code) {
    case GPIO__PULL_DOWN:
        name = "Down";
        break;
    case GPIO__PULL_UP:
        name = "Up";
        break;
    case GPIO__PULL_AIR:
        name = "Air";
        break;
    case GPIO__PULL_BOTH:
        name = "UpDown";
        break;
    }
    return name;
}

const char* GpioPad2WireName(uint8_t pad) {
    const char* pin_name = "?";
    uint8_t i = 0;
    for(i = 0; i < gpio_get_cnt(); i++) {
        if(((uint8_t)GpioConfig[i].pad.byte) == pad) {
            pin_name = GpioConfig[i].name;
            break;
        }
    }
    return pin_name;
}

#ifdef HAS_EXT_INT_DIAG
const char* GpioEdgeToStr(PinIntEdge_t code) {
    const char* name = "?";
    name = ExtIntEdgeToStr(code);
    return name;
}
#endif

const char* GpioConfToStr(const GpioConfig_t* Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%s%s,", text, GpioPad2Str(Config->pad.byte));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sDir:%s,", text, GpioDir2Str(Config->dir));
        snprintf(text, sizeof(text), "%sMode:%s,", text, GpioMode2Str(Config->mode));
        snprintf(text, sizeof(text), "%sMux:%u,", text, Config->mux);
        snprintf(text, sizeof(text), "%sLL:%s,", text, GpioLevel2Str(Config->logic_level));
        snprintf(text, sizeof(text), "%sPull:%s,", text, GpioPull2Str(Config->pull));
        snprintf(text, sizeof(text), "%sPin:%u,", text, Config->mcu_pin);
        snprintf(text, sizeof(text), "%sLD:%u,", text, Config->load_detect);
    }
    return text;
}

bool GpioConfigDiag(const GpioConfig_t* const Config) {
    bool res = false;
    LOG_WARNING(GPIO, "%s", GpioConfToStr(Config));
    return res;
}

bool gpio_diag(char* key_word1, char* key_word2) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"},        {7, "pad"},  {7, "level"}, {6, "dir"}, {6, "pull"},
#ifdef HAS_GPIO_NRFX
                                       {6, "mux"},
#endif
#ifdef HAS_BOARD_INFO_DIAG
                                       {12, "connect1"},
#endif
                                       {12, "connect2"}, {15, "name"}};
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
    uint8_t i = 0;
    char log_line[150];
    uint16_t gpio_cnt = gpio_get_cnt();
    for(i = 0; i < gpio_cnt; i++) {
        if(PORT_UNDEF != GpioConfig[i].pad.port) {
            GpioDir_t dirr = gpio_dir_get(GpioConfig[i].pad.byte);
            GpioPullMode_t pull = gpio_pull_get(GpioConfig[i].pad.byte);
#ifdef HAS_GPIO_NRFX
            nrf_gpio_pin_mcusel_t mcu_sel = nrf_gpio_pin_mcu_select_get(GpioConfig[i].pad.byte);
#endif
            strcpy(log_line, TSEP);
            logic_level = GPIO_LVL_UNDEF;
            gpio_get_state(GpioConfig[i].pad.byte, &logic_level);
            snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line, GpioPad2Str(GpioConfig[i].pad.byte));
            snprintf(log_line, sizeof(log_line), "%s   %s   " TSEP, log_line, GpioLevel2Str(logic_level));
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, GpioDir2Str(dirr));
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, GpioPull2Str(pull));
#ifdef HAS_GPIO_NRFX
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, McuSel2Str(mcu_sel));
#endif
#ifdef HAS_BOARD_INFO_DIAG
            snprintf(log_line, sizeof(log_line), "%s %10s " TSEP, log_line, Pad2ConnectorPin(GpioConfig[i].pad));
#endif /*HAS_BOARD_INFO_DIAG*/
            snprintf(log_line, sizeof(log_line), "%s %10s " TSEP, log_line, GpioGetCon2(GpioConfig[i].pad.byte));
            snprintf(log_line, sizeof(log_line), "%s %13s " TSEP, log_line, GpioPad2WireName(GpioConfig[i].pad.byte));
            if(is_contain(log_line, key_word1, key_word2)) {
                cli_printf(TSEP " %3u ", num);
                cli_printf("%s" CRLF, log_line);
                // cli_printf(CRLF);
                num++;
                res = true;
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
