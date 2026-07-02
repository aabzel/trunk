#include "gpio_diag.h"

#include <stddef.h>

#include "bit_utils.h"
#include "data_utils.h"
#include "diag_inc.h"
#include "gpio_mcal.h"
#include "log.h"
#include "shared_array.h"
#include "std_includes.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_EXT_INT
#include "ext_int_const.h"
#include "ext_int_diag.h"
#endif

#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

const char* GpioDriveSelectToStr(const GpioDriveSelect_t drive_select) {
    char* name = "?";
    switch(drive_select) {
    case GPIO_DRIVE_SELECT_2MA:
        name = "2mA";
        break;
    case GPIO_DRIVE_SELECT_4MA:
        name = "4mA";
        break;
    case GPIO_DRIVE_SELECT_8MA:
        name = "8mA";
        break;
    default:
        break;
    }
    return name;
}

const char* GpioSpeedToStr(const GpioSpeed_t speed) {
    char* name = "?";
    switch(speed) {
    case GPIO_SPEED_LOW_SPEED:
        name = "Slow";
        break;
    case GPIO_SPEED_MEDIUM_SPEED:
        name = "Medium";
        break;
    case GPIO_SPEED_FAST_SPEED:
        name = "Fast";
        break;
    case GPIO_SPEED_HIGH_SPEED:
        name = "High";
        break;
    default:
        break;
    }
    return name;
}

static char lText[40] = {0};

const char* GpioGetCon2(Pad_t pad) {
    const char* name = "-";
#ifdef HAS_PINS
    uint32_t cnt = gpio_get_cnt();
    uint8_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(pad.byte == GpioConfig[i].Pad.byte) {
            name = GpioConfig[i].connector2;
            break;
        }
    }
#endif
    return name;
}

const char* GpioGetCon1(Pad_t Pad) {
    const char* name = "?";
#ifdef HAS_PINS
    uint32_t cnt = gpio_get_cnt();
    uint8_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(Pad.byte == GpioConfig[i].Pad.byte) {
            name = GpioConfig[i].connector1;
            break;
        }
    }
#endif
    return name;
}

const char* GpioPullToStr(GpioPullMode_t code) {
    const char* name = "?";
    switch(code) {
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
    default:
        break;
    }
    return name;
}

const char* GpioAltFunToStr(uint8_t alt_foo) {
    snprintf(lText, sizeof(lText), "AF%u", alt_foo);
    return lText;
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

const char* GpioDirToStr(GpioDir_t code) {
    const char* name = "?";
    switch(code) {
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
    default:
        break;
    }
    return name;
}

const char* GpioModeToStr(GpioApiMode_t mode) {
    const char* name = "?";
    switch(mode) {
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
    default:
        break;
    }
    return name;
}

const char* GpioPortToStr(const GpioPort_t port) {
    const char* name = "?";
    switch(port) {
    case GPIO_PORT_A:
        name = "A";
        break;
    case GPIO_PORT_B:
        name = "B";
        break;
    case GPIO_PORT_C:
        name = "C";
        break;
    case GPIO_PORT_D:
        name = "D";
        break;
    case GPIO_PORT_E:
        name = "E";
        break;
    case GPIO_PORT_F:
        name = "F";
        break;
    case GPIO_PORT_G:
        name = "G";
        break;
    case GPIO_PORT_H:
        name = "H";
        break;
    case GPIO_PORT_I:
        name = "I";
        break;
    case GPIO_PORT_J:
        name = "J";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* GpioPadToStr(Pad_t Pad) {
    strcpy(lText, "");
    if(gpio_is_valid_pad(Pad)) {
#ifdef HAS_GPIO_DIAG
        snprintf(lText, sizeof(lText), "P%s%u", GpioPortToStr(Pad.port), Pad.pin);
#else
        snprintf(lText, sizeof(lText), "P%u.%u", Pad.port, Pad.pin);
#endif
    } else {
        snprintf(lText, sizeof(lText), "--");
    }
    return lText;
}

const char* GpioOutTypeToStr(Pad_t Pad) {
    char* name = "?";

    return name;
}

const char* GpioLevelToStr(GpioLogicLevel_t code) {
    char* name = "?";
    switch(code) {
    case GPIO_LVL_HI:
        name = "H";
        break;
    case GPIO_LVL_LOW:
        name = "L";
        break;
    default:
        break;
    }
    return name;
}

const char* GpioPad2WireName(const Pad_t Pad) {
    const char* pin_name = "?";
    uint8_t i = 0;
    for(i = 0; i < gpio_get_cnt(); i++) {
        if((GpioConfig[i].Pad.byte) == Pad.byte) {
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

bool gpio_diag(char* key_word1, char* key_word2) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"},        {7, "pad"}, {7, "level"}, {6, "dir"}, {6, "pull"},
#ifdef HAS_GPIO_NRFX
                                       {6, "mux"},
#endif
#ifdef HAS_BOARD_INFO_DIAG
                                       {12, "connect1"},
#endif
                                       {15, "name"}};
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
    uint8_t i = 0;
    char temp[150];
    uint16_t gpio_cnt = gpio_get_cnt();
    for(i = 0; i < gpio_cnt; i++) {
        if(GPIO_PORT_UNDEF != GpioConfig[i].Pad.port) {
            GpioDir_t dir = gpio_dir_get(GpioConfig[i].Pad);
            GpioPullMode_t pull = gpio_pull_get(GpioConfig[i].Pad);
#ifdef HAS_GPIO_NRFX
            nrf_gpio_pin_mcusel_t mcu_sel = nrf_gpio_pin_mcu_select_get(GpioConfig[i].Pad);
#endif
            strcpy(temp, TSEP);
            logic_level = GPIO_LVL_UNDEF;
            gpio_get_state(GpioConfig[i].Pad, &logic_level);
            snprintf(temp, sizeof(temp), "%s %5s " TSEP, temp, GpioPadToStr(GpioConfig[i].Pad));
            snprintf(temp, sizeof(temp), "%s   %s   " TSEP, temp, GpioLevelToStr(logic_level));
            snprintf(temp, sizeof(temp), "%s %4s " TSEP, temp, GpioDirToStr(dir));
            snprintf(temp, sizeof(temp), "%s %4s " TSEP, temp, GpioPullToStr(pull));
#ifdef HAS_GPIO_NRFX
            snprintf(temp, sizeof(temp), "%s %4s " TSEP, temp, McuSelToStr(mcu_sel));
#endif

#ifdef HAS_BOARD_INFO_DIAG
            snprintf(temp, sizeof(temp), "%s %10s " TSEP, temp, Pad2ConnectorPin(GpioConfig[i].Pad));
#endif

            snprintf(temp, sizeof(temp), "%s %13s " TSEP, temp, GpioPad2WireName(GpioConfig[i].Pad));
            if(is_contain(temp, key_word1, key_word2)) {
                cli_printf(TSEP " %3u ", num);
                cli_printf("%s" CRLF, temp);
                // cli_printf(CRLF);
                num++;
                res = true;
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool diag_gpio(char* key_word1, char* key_word2) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"},        {7, "pad"},  {8, "mode"}, {7, "level"}, {8, "Fun"},
                                       {6, "dir"},       {6, "pull"}, {5, "MuxS"}, {5, "MuxG"},
#ifdef HAS_BOARD_INFO_DIAG
                                       {12, "connect1"},
#endif
                                       {15, "name"}};
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i = 0;
    uint16_t gpio_cnt = gpio_get_cnt();
    for(i = 0; i < gpio_cnt; i++) {
        if(GPIO_PORT_UNDEF != GpioConfig[i].Pad.port) {
            GpioDir_t dir = gpio_dir_get(GpioConfig[i].Pad);
            GpioPullMode_t pull = gpio_pull_get(GpioConfig[i].Pad);
            GpioPinFunction_t function = GPIO_FUN_UNDEF;
            res = gpio_pin_fun_get(GpioConfig[i].Pad, &function);
            GpioApiMode_t mode = gpio_mode_get(GpioConfig[i].Pad);

            uint8_t pin_mux = 0;

            res = gpio_pin_mux_get(GpioConfig[i].Pad, &pin_mux);
#ifdef HAS_GPIO_NRFX
            nrf_gpio_pin_mcusel_t mcu_sel = nrf_gpio_pin_mcu_select_get(GpioConfig[i].Pad);
#endif
            char temp[150];
            strcpy(temp, TSEP);
            GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
            gpio_get_state(GpioConfig[i].Pad, &logic_level);
            snprintf(temp, sizeof(temp), "%s %5s " TSEP, temp, GpioPadToStr(GpioConfig[i].Pad));
            snprintf(temp, sizeof(temp), "%s %6s " TSEP, temp, GpioModeToStr(mode));
            snprintf(temp, sizeof(temp), "%s   %s   " TSEP, temp, GpioLevelToStr(logic_level));
            snprintf(temp, sizeof(temp), "%s %6s " TSEP, temp, GpioFunToStr(function));
            snprintf(temp, sizeof(temp), "%s %4s " TSEP, temp, GpioDirToStr(dir));
            snprintf(temp, sizeof(temp), "%s %4s " TSEP, temp, GpioPullToStr(pull));
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, GpioConfig[i].mux);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, pin_mux);
#ifdef HAS_GPIO_NRFX
            snprintf(temp, sizeof(temp), "%s %4s " TSEP, temp, McuSelToStr(mcu_sel));
#endif
#ifdef HAS_BOARD_INFO_DIAG
            snprintf(temp, sizeof(temp), "%s %10s " TSEP, temp, Pad2ConnectorPin(GpioConfig[i].Pad));
#endif
            snprintf(temp, sizeof(temp), "%s %13s " TSEP, temp, GpioPad2WireName(GpioConfig[i].Pad));
            if(is_contain(temp, key_word1, key_word2)) {
                cli_printf(TSEP " %3u ", num);
                cli_printf("%s" CRLF, temp);
                // cli_printf(CRLF);
                num++;
                res = true;
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    if(num) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool gpio_raw_reg_diag(const GpioPort_t port) {
    bool res = false;
#ifdef HAS_GPIO_CUSTOM
    const GpioPortInfo_t* Info = GpioGetPortInfo(port);
    if(Info) {
        LOG_INFO(GPIO, "GPIO%u,Base:0x%p", port, Info->GPIOx);
        uint32_t reg_cnt = gpio_reg_cnt();
        res = debug_raw_reg_diag(GPIO, (uint32_t)Info->GPIOx, GpioReg, reg_cnt);
#ifdef HAS_GPIO_PORT
        uint32_t port_cnt = port_reg_cnt();
        res = debug_raw_reg_diag(GPIO, (uint32_t)Info->PORTx, PortReg, port_cnt);
#endif
    }

#endif
    return res;
}

const char* GpioConfigToStr(const GpioConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%s%s,", text, GpioPadToStr(Config->Pad));
        snprintf(text, sizeof(text), "%sDrvSel:%s,", text, GpioDriveSelectToStr(Config->drive_select));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sDir:%s,", text, GpioDirToStr(Config->dir));
        snprintf(text, sizeof(text), "%sMode:%s,", text, GpioModeToStr(Config->mode));
        snprintf(text, sizeof(text), "%sMux:%u,", text, Config->mux);
        snprintf(text, sizeof(text), "%sLL:%s,", text, GpioLevelToStr(Config->logic_level));
        snprintf(text, sizeof(text), "%sPull:%s,", text, GpioPullToStr(Config->pull));
        snprintf(text, sizeof(text), "%sSpeed:%s,", text, GpioSpeedToStr(Config->speed));
        snprintf(text, sizeof(text), "%sPin:%u,", text, Config->mcu_pin);
    }
    return text;
}

bool GpioConfigDiag(const GpioConfig_t* const Config) {
    bool res = false;
    LOG_WARNING(GPIO, "%s", GpioConfigToStr(Config));
    return res;
}

const char* GpioPadsToStr(const Pad_t* const pPad, const uint32_t cnt) {
    static char loText[250] = "";
    strcpy(loText, "");
    if(pPad) {
        if(cnt) {
            uint32_t b = 0;
            for (b = 0; b < cnt; b++) {
                snprintf(loText, sizeof(loText), "%s%s,", loText, GpioPadToStr(pPad[b]));
            }
        }
    }
    return loText;
}

