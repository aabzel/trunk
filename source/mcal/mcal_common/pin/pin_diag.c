#include "pin_diag.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bit_utils.h"
#include "data_utils.h"
#include "pin_mcal.h"
#include "log.h"
#include "str_utils.h"
#ifdef HAS_EXT_INT
#include "ext_int_const.h"
#include "ext_int_diag.h"
#endif
#include "table_utils.h"
#include "writer_config.h"

#include "shared_array.h"

const char* PinAltFunToStr(uint8_t code) {
    snprintf(text, sizeof(text), "AF%u", code);
    return text;
}

const char* PinFunToStr(PinPinFunction_t function) {
    const char* name = "?";
    switch((uint8_t)function) {
    case PIN_FUN_ANALOG:
        name = "Analog";
        break;
    case PIN_FUN_MULTIPLEXED:
        name = "Mux";
        break;
    case PIN_FUN_OUT:
        name = "Out";
        break;
    case PIN_FUN_INPUT:
        name = "Input";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* PinDirToStr(PinDir_t code) {
    const char* name = "?";
    switch((uint8_t)code) {
    case PIN_DIR_IN:
        name = "In";
        break;
    case PIN_DIR_OUT:
        name = "Out";
        break;
    case PIN_DIR_OUT_PUSH_PULL:
        name = "OutPp";
        break;
    case PIN_DIR_OUT_OPEN_DRAIN:
        name = "OutOd";
        break;
    case PIN_DIR_INOUT:
        name = "Io";
        break;
    case PIN_DIR_NONE:
        name = "-";
        break;
    case PIN_DIR_INOUT_OPEN_DRAIN:
        name = "InOd";
        break;
    case PIN_DIR_UNDEF:
        name = "?";
        break;
    }
    return name;
}

const char* PinModeToStr(PinApiMode_t mode) {
    const char* name = "?";
    switch((uint8_t)mode) {
    case PIN_API_MODE_PIN:
        name = "PIN";
        break;
    case PIN_API_MODE_ALT1:
        name = "ALT1";
        break;
    case PIN_API_MODE_ALT2:
        name = "ALT2";
        break;
    case PIN_API_MODE_HW_PWM:
        name = "HwPwm";
        break;
    case PIN_API_MODE_INPUT:
        name = "In";
        break;
    case PIN_API_MODE_OUTPUT:
        name = "Out";
        break;
    case PIN_API_MODE_ANALOG:
        name = "Analog";
        break;
    case PIN_API_MODE_I2C:
        name = "I2C";
        break;

    case PIN_DIR_UNDEF:
        name = "?";
        break;
    }
    return name;
}

const char* PinPadToStr(uint8_t pad) {

    Pad_t Pad;
    Pad.byte = pad;
    if(pin_is_valid_pad(pad)) {
#ifdef HAS_PIN_DIAG
        snprintf(text, sizeof(text), "P%s%u", PinPortToStr(Pad.port), Pad.pin);
#else
        snprintf(text, sizeof(text), "P%u.%u", Pad.port, Pad.pin);
#endif
    } else {
        snprintf(text, sizeof(text), "--");
    }
    return text;
}

const char* PinPadToStr(Pad_t Pad) {

    if(pin_is_valid_pad(Pad.byte)) {
#ifdef HAS_PIN_DIAG
        snprintf(text, sizeof(text), "P%s%u", PinPortToStr(Pad.port), Pad.pin);
#else
        snprintf(text, sizeof(text), "P%u.%u", Pad.port, Pad.pin);
#endif
    } else {
        snprintf(text, sizeof(text), "--");
    }
    return text;
}

const char* PinOutTypeToStr(uint8_t code) {
    char* name = "?";

    return name;
}

const char* PinSpeedToStr(uint8_t code) {
    char* name = "?";
    return name;
}

const char* PinLevelToStr(PinLogicLevel_t code) {
    char* name = "?";
    switch((uint8_t)code) {
    case PIN_LVL_HI:
        name = "H";
        break;
    case PIN_LVL_LOW:
        name = "L";
        break;
    }
    return name;
}

const char* PinPullToStr(PinPullMode_t code) {
    const char* name = "?";
    switch((uint8_t)code) {
    case PIN__PULL_DOWN:
        name = "Down";
        break;
    case PIN__PULL_UP:
        name = "Up";
        break;
    case PIN__PULL_AIR:
        name = "Air";
        break;
    case PIN__PULL_BOTH:
        name = "UpDown";
        break;
    }
    return name;
}

const char* PinPad2WireName(uint8_t pad) {
    const char* pin_name = "?";
    uint8_t i = 0;
    for(i = 0; i < pin_get_cnt(); i++) {
        if(((uint8_t)PinConfig[i].pad.byte) == pad) {
            pin_name = PinConfig[i].name;
            break;
        }
    }
    return pin_name;
}

#ifdef HAS_EXT_INT_DIAG
const char* PinEdgeToStr(PinIntEdge_t code) {
    const char* name = "?";
    name = ExtIntEdgeToStr(code);
    return name;
}
#endif

const char* PinConfToStr(const PinConfig_t* Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%s%s,", text, PinPadToStr(Config->pad.byte));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sDir:%s,", text, PinDirToStr(Config->dir));
        snprintf(text, sizeof(text), "%sMode:%s,", text, PinModeToStr(Config->mode));
        snprintf(text, sizeof(text), "%sMux:%u,", text, Config->mux);
        snprintf(text, sizeof(text), "%sLL:%s,", text, PinLevelToStr(Config->logic_level));
        snprintf(text, sizeof(text), "%sPull:%s,", text, PinPullToStr(Config->pull));
        snprintf(text, sizeof(text), "%sPin:%u,", text, Config->mcu_pin);
        snprintf(text, sizeof(text), "%sLD:%u,", text, Config->load_detect);
    }
    return text;
}

bool PinConfigDiag(const PinConfig_t* const Config) {
    bool res = false;
    LOG_WARNING(PIN, "%s", PinConfToStr(Config));
    return res;
}

bool pin_diag(char* key_word1, char* key_word2) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"},        {7, "pad"},  {7, "level"}, {6, "dir"}, {6, "pull"},
#ifdef HAS_PIN_NRFX
                                       {6, "mux"},
#endif
#ifdef HAS_BOARD_INFO_DIAG
                                       {12, "connect1"},
#endif
                                       {12, "connect2"}, {15, "name"}};
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    PinLogicLevel_t logic_level = PIN_LVL_UNDEF;
    uint8_t i = 0;
    char log_line[150];
    uint16_t pin_cnt = pin_get_cnt();
    for(i = 0; i < pin_cnt; i++) {
        if(PORT_UNDEF != PinConfig[i].pad.port) {
            PinDir_t dirr = pin_dir_get(PinConfig[i].pad.byte);
            PinPullMode_t pull = pin_pull_get(PinConfig[i].pad.byte);
#ifdef HAS_PIN_NRFX
            nrf_pin_pin_mcusel_t mcu_sel = nrf_pin_pin_mcu_select_get(PinConfig[i].pad.byte);
#endif
            strcpy(log_line, TSEP);
            logic_level = PIN_LVL_UNDEF;
            pin_get_state(PinConfig[i].pad.byte, &logic_level);
            snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line, PinPadToStr(PinConfig[i].pad.byte));
            snprintf(log_line, sizeof(log_line), "%s   %s   " TSEP, log_line, PinLevelToStr(logic_level));
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, PinDirToStr(dirr));
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, PinPullToStr(pull));
#ifdef HAS_PIN_NRFX
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, McuSelToStr(mcu_sel));
#endif
#ifdef HAS_BOARD_INFO_DIAG
            snprintf(log_line, sizeof(log_line), "%s %10s " TSEP, log_line, Pad2ConnectorPin(PinConfig[i].pad));
#endif /*HAS_BOARD_INFO_DIAG*/
            snprintf(log_line, sizeof(log_line), "%s %10s " TSEP, log_line, PinGetCon2(PinConfig[i].pad.byte));
            snprintf(log_line, sizeof(log_line), "%s %13s " TSEP, log_line, PinPad2WireName(PinConfig[i].pad.byte));
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
