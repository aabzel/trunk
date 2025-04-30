#include "gpio_mcal.h"

#include <stddef.h>

#include "compiler_const.h"
#include "std_includes.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_CLOCK
#include "clock.h"
#endif

#ifdef HAS_CLI
#include "convert.h"
#endif

#ifdef HAS_TIME

#include "time_mcal.h"
#endif

#ifdef HAS_GPIO_DIAG
#include "gpio_diag.h"
#endif

#ifdef HAS_TIME
#include "none_blocking_pause.h"
#endif /*HAS_SUPER_CYCLE*/

#include "board_config.h"
//#include "data_utils.h"

#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#include "gpio_config.h"
#include "microcontroller.h"
#include "sys_config.h"

#ifdef HAS_CLI
bool parse_pad(char* argv[], Pad_t* pad) {
    bool res = false;
    uint8_t port = 0;
    uint8_t cnt = 0;
    uint8_t pin = 0;
    res = try_str2uint8(argv[0], &port);
    if(false == res) {
        LOG_ERROR(GPIO, "ParseErr PortNum %s", argv[0]);
    } else {
        cnt++;
        LOG_INFO(GPIO, "ParsePortOk %u", port);
        pad->port = port;
    }

    res = try_str2uint8(argv[1], &pin);
    if(false == res) {
        LOG_ERROR(GPIO, "ParseErr PinNum %s 0..%u", argv[1], GPIO_PIN_MAX);
    } else {
        cnt++;
        LOG_INFO(GPIO, "ParsePinOk %u", pin);
        if(pin <= GPIO_PIN_MAX) {
            LOG_INFO(GPIO, "PinValOk %u", pin);
            pad->pin = pin;
        } else {
            res = false;
            LOG_ERROR(GPIO, "PinValErr %u Max %u", pin, GPIO_PIN_MAX);
        }
    }
    if((2 == cnt) && res) {
#ifdef HAS_GPIO_DIAG
        LOG_INFO(GPIO, "SpotPad %s", GpioPadToStr(*pad));
#endif
        res = true;
    } else {
        LOG_ERROR(GPIO, "PadParseErr");
        res = false;
    }
    return res;
}
#endif /*HAS_CLI*/

#ifdef HAS_GPIO_EXT
uint8_t get_mcu_pin(uint8_t pad) {
    uint8_t mcu_pin = 0;
#ifdef HAS_PINS
    uint8_t i = 0;
    for(i = 0; i < pin_get_cnt(); i++) {
        if(((uint8_t)PinConfig[i].pad.byte) == pad) {
            mcu_pin = PinConfig[i].mcu_pin;
            break;
        }
    }
#endif
    return mcu_pin;
}
#endif

#ifdef HAS_LOG
const char* GpioGetCon1(uint8_t pad) {
    const char* name = "?";
#ifdef HAS_PINS
    uint32_t cnt = gpio_get_cnt();
    uint8_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(pad == GpioConfig[i].pad.byte) {
            name = GpioConfig[i].connector1;
            break;
        }
    }
#endif
    return name;
}
#endif

#ifdef HAS_LOG
const char* GpioGetCon2(uint8_t pad) {
    const char* name = "-";
#ifdef HAS_PINS
    uint32_t cnt = gpio_get_cnt();
    uint8_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(pad == GpioConfig[i].pad.byte) {
            name = GpioConfig[i].connector2;
            break;
        }
    }
#endif
    return name;
}
#endif

#if 0
Port_t PortLetter2PortNum(char port) {
    Port_t port_num = PORT_UNDEF;
    switch(port) {
    case '0': port_num = 0;break;
    case '1': port_num = 1;break;
    case '2': port_num = 2;break;
    }
    return port_num;
}
#endif

#ifdef HAS_GPIO_EXT
uint8_t gpio_port_pin2pad(Port_t port, uint8_t pin) {
    Pad_t pad = {0};
    pad.port = port;
    pad.pin = pin;
    return pad.byte;
}

uint8_t gpio_padval_2pin(uint8_t pad_val) {
    Pad_t Pad = {.byte = pad_val};
    return Pad.pin;
}

uint8_t gpio_padval_2port(uint8_t pad_val) {
    Pad_t Pad = {.byte = pad_val};
    return Pad.port;
}
#endif

#ifdef HAS_GPIO_EXT
bool gpio_set_state_verify(uint8_t pad_num, GpioLogicLevel_t logic_level) {
    bool res;
    Pad_t Pad = {.byte = pad_num};
    GpioLogicLevel_t logic_level_effective = GPIO_LVL_UNDEF;
    res = gpio_logic_level_set(Pad, logic_level);
#ifdef HAS_TIME
    time_delay_ms(600);
#endif
    res = gpio_get_state(pad_num, &logic_level_effective);
    if(logic_level_effective == logic_level) {
        res = true;
    } else {
#ifdef HAS_GPIO_DIAG
        LOG_ERROR(GPIO, "SetErr Pad: %s Des:%u Real:%u", GpioPad2Str(pad_num), logic_level, logic_level_effective);
#endif
        res = false;
    }
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
uint8_t pad_assign(uint8_t pad_num, char* wire_name) {
    bool res = false;
    uint8_t pad = 0;
    res = gpio_is_valid_pad(pad_num);
    if(res) {
#ifdef HAS_GPIO_DIAG
        LOG_INFO(GPIO, "Wire %s Pad %s=%s", wire_name, GpioPad2Str(pad_num), GpioPad2WireName(pad_num));
#endif
        pad = pad_num;
    } else {
        res = false;
#ifdef HAS_GPIO_DIAG
        LOG_ERROR(GPIO, "Wire %s Pad %s=%s Err", wire_name, GpioPad2Str(pad_num), GpioPad2WireName(pad_num));
#endif
    }
    return pad;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_ bool gpio_pin_mux_set(Port_t port, uint8_t pin, uint8_t mux) {
    bool res = false;
    return res;
}

_WEAK_FUN_ bool gpio_pin_fun_get(Pad_t Pad, GpioPinFunction_t* const function) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_ bool gpio_clock_init(void) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_
bool gpio_logic_level_set(Pad_t Pad, GpioLogicLevel_t logic_level) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_ bool gpio_is_valid_pad(uint8_t pad_num) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_
bool gpio_get_state(uint8_t pad_num, GpioLogicLevel_t* const logic_level) {
    bool res = false;
    /*Determine in Sep file*/
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_ bool gpio_init_one(const GpioConfig_t* const pinInstance) {
    bool res = false;
    /*Determine in Sep file*/
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_
bool gpio_proc(void) {
    bool res = false;
    /*Determine in Sep file*/
    return res;
}
#endif

bool gpio_mcal_init(void) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_WARNING(GPIO, "Init");
#endif

#ifdef HAS_GPIO_CUSTOM_INIT
    res = gpio_init_custom();
#endif

#ifdef HAS_PINS
    gpio_clock_init();

    uint32_t i = 0;
    uint32_t cnt_ok = 0;
    uint32_t pin_cnt = gpio_get_cnt();
    for(i = 0; i < pin_cnt; i++) {
        res = gpio_init_one(&GpioConfig[i]);
        if(res) {
            cnt_ok++;
        } else {
#ifdef HAS_GPIO_DIAG
            LOG_ERROR(GPIO, "Init %s Err", GpioPad2Str(GpioConfig[i].pad.byte));
#endif
        }
    }

    if(pin_cnt == cnt_ok) {
        res = true;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(GPIO, "Partial %u/%u", cnt_ok, pin_cnt);
#endif
    }
#endif /*HAS_PINS*/

    return res;
}

#ifdef HAS_GPIO_EXT
const GpioConfig_t* gpio_get_config(Pad_t pad) {
    const GpioConfig_t* ConfNode = NULL;
    uint32_t cnt = gpio_get_cnt();
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(pad.byte == GpioConfig[i].pad.byte) {
            ConfNode = &GpioConfig[i];
            break;
        }
    }
    return ConfNode;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_ bool gpio_pull_set(Pad_t Pad, GpioPullMode_t pull_code) {
    /*This function must be implemented in in platform specific code*/
    return false;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_ GpioApiMode_t gpio_mode_get(uint8_t pad_num) { return GPIO_API_MODE_UNDEF; }

_WEAK_FUN_ GpioPullMode_t gpio_pull_get(uint8_t pad_num) {
    /*This function must be implemented in in platform specific code*/
    return GPIO__PULL_UNDEF;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_ bool gpio_dir_set(uint8_t pad_num, GpioDir_t dir) {
    /*This function must be implemented in in platform specific code*/
    return false;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_ GpioDir_t gpio_dir_get(uint8_t pad_num) {
    /*This function must be implemented in in platform specific code*/
    return GPIO_DIR_UNDEF;
}
#endif

#ifdef HAS_GPIO_EXT
GpioLogicLevel_t gpio_opposite_level_get(GpioLogicLevel_t origin_ll) {
    GpioLogicLevel_t out_ll = GPIO_LVL_UNDEF;
    switch((uint8_t)origin_ll) {
    case GPIO_LVL_LOW:
        out_ll = GPIO_LVL_HI;
        break;
    case GPIO_LVL_HI:
        out_ll = GPIO_LVL_LOW;
        break;
    default:
        break;
    }
    return out_ll;
}
#endif

#ifdef HAS_GPIO_EXT
bool GpioProcReadLow(GpioLogicLevel_t active) {
    bool on_off = false;
    switch((uint8_t)active) {
    case GPIO_LVL_HI:
        on_off = false;
        break;
    case GPIO_LVL_LOW:
        on_off = true;
        break;
    }
    return on_off;
}
#endif

#ifdef HAS_GPIO_EXT
bool GpioProcReadHi(GpioLogicLevel_t active) {
    bool on_off = false;
    switch((uint8_t)active) {
    case GPIO_LVL_HI:
        on_off = true;
        break;
    case GPIO_LVL_LOW:
        on_off = false;
        break;
    }
    return on_off;
}
#endif

#ifdef HAS_GPIO_EXT
/*can be called from ISR*/
_WEAK_FUN_
bool gpio_toggle(const Pad_t pad) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    // LOG_DEBUG(GPIO, "Toggle P%s%u", GpioPort2Str(pad.port), pad.pin);
#endif
    GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
    res = gpio_get_state(pad.byte, &logic_level);
    if(res) {
        GpioLogicLevel_t new_ll = gpio_opposite_level_get(logic_level);
        res = gpio_logic_level_set(pad, new_ll);
    }

    return res;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_ bool gpio_pin_mux_get(uint8_t port, uint8_t pin, uint8_t* mux) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
bool gpio_is_valid_pull(GpioPullMode_t pull) {
    bool res = false;
    switch((uint8_t)pull) {
    case GPIO__PULL_DOWN:
    case GPIO__PULL_UP:
    case GPIO__PULL_AIR:
    case GPIO__PULL_BOTH:
        res = true;
        break;
    }
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
bool gpio_is_valid_mode(GpioApiMode_t mode) {
    bool res = false;
    switch(mode) {
    case GPIO_API_MODE_INPUT_EXINT:
    case GPIO_API_MODE_I2C:
    case GPIO_API_MODE_ALT1:
    case GPIO_API_MODE_HW_PWM:
    case GPIO_API_MODE_INPUT:
    case GPIO_API_MODE_ALT2:
    case GPIO_API_MODE_ANALOG:
    case GPIO_API_MODE_OUTPUT:
    case GPIO_API_MODE_GPIO:
        res = true;
        break;
    default:
        res = true;
        break;
    }
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
bool gpio_is_pin_single(uint8_t byte) {
    bool res = false;
    uint32_t i = 0, pin_cnt = 0;
    uint32_t pin_real_cnt = 0;
    pin_cnt = gpio_get_cnt();
    for(i = 0; i < pin_cnt; i++) {
        if(byte == GpioConfig[i].pad.byte) {
            pin_real_cnt++;
        }
    }
    if(1 == pin_real_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif
