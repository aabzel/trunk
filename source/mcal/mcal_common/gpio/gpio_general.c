#include "gpio_mcal.h"

#include <stddef.h>

#include "board_config.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "microcontroller.h"
#include "std_includes.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_CLOCK
#include "clock_mcal.h"
#endif

#ifdef HAS_CLI
#include "convert.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_TIME
#include "none_blocking_pause.h"
#endif

#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

uint32_t GpioPinNumToPinMask(uint8_t pin_num) {
    uint32_t pin_mask = 0;
    if(pin_num < 31) {
        pin_mask |= (1 << pin_num);
    }
    return pin_mask;
}

#ifdef HAS_CLI
bool parse_pad(char* argv[], Pad_t* pad) {
    bool res = false;
    uint8_t cnt = 0;
    uint8_t pin = 0;
    uint8_t port = 0;
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

#if 0
GpioPort_t PortLetter2PortNum(char port) {
    GpioPort_t port_num = PORT_UNDEF;
    switch(port) {
    case '0': port_num = 0;break;
    case '1': port_num = 1;break;
    case '2': port_num = 2;break;
    }
    return port_num;
}
#endif

#ifdef HAS_GPIO_EXT
uint8_t gpio_port_pin2pad(GpioPort_t port, uint8_t pin) {
    Pad_t pad = {0};
    pad.port = port;
    pad.pin = pin;
    return pad.byte;
}

uint8_t gpio_padval_2pin(Pad_t Pad) { return Pad.pin; }

uint8_t gpio_padval_2port(Pad_t Pad) { return Pad.port; }
#endif

#ifdef HAS_GPIO_EXT
bool gpio_set_state_verify(Pad_t Pad, GpioLogicLevel_t logic_level) {
    bool res;
    GpioLogicLevel_t logic_level_effective = GPIO_LVL_UNDEF;
    res = gpio_logic_level_set(Pad, logic_level);
#ifdef HAS_TIME_EXT
    time_delay_ms(600);
#endif
    res = gpio_get_state(Pad, &logic_level_effective);
    if(logic_level_effective == logic_level) {
        res = true;
    } else {
#ifdef HAS_GPIO_DIAG
        LOG_ERROR(GPIO, "SetErr Pad: %s Des:%u Real:%u", GpioPadToStr(Pad), logic_level, logic_level_effective);
#endif
        res = false;
    }
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
uint8_t pad_assign(Pad_t Pad, char* wire_name) {
    bool res = false;
    uint8_t pad = 0;
    res = gpio_is_valid_pad(Pad);
    if(res) {
#ifdef HAS_GPIO_DIAG
        LOG_INFO(GPIO, "Wire %s Pad %s=%s", wire_name, GpioPadToStr(Pad), GpioPad2WireName(Pad));
#endif
        pad = Pad.byte;
    } else {
        res = false;
#ifdef HAS_GPIO_DIAG
        LOG_ERROR(GPIO, "Wire %s Pad %s=%s Err", wire_name, GpioPadToStr(Pad), GpioPad2WireName(Pad));
#endif
    }
    return pad;
}
#endif

_WEAK_FUN_
bool gpio_mode_set(const Pad_t Pad, const GpioApiMode_t mode) {
    bool res = false;
    return res;
}

#ifdef HAS_GPIO_EXT
_WEAK_FUN_ bool gpio_pin_mux_set(GpioPort_t port, uint8_t pin, uint8_t mux) {
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
_WEAK_FUN_ bool gpio_is_valid_pad(Pad_t Pad) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_
bool gpio_get_state(Pad_t pad, GpioLogicLevel_t* const logic_level) {
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
            LOG_ERROR(GPIO, "Init %s Err", GpioPadToStr(GpioConfig[i].Pad));
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
        if(pad.byte == GpioConfig[i].Pad.byte) {
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
_WEAK_FUN_ GpioApiMode_t gpio_mode_get(Pad_t Pad) { return GPIO_API_MODE_UNDEF; }

_WEAK_FUN_ GpioPullMode_t gpio_pull_get(Pad_t Pad) {
    /*This function must be implemented in in platform specific code*/
    return GPIO__PULL_UNDEF;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_ bool gpio_dir_set(Pad_t Pad, GpioDir_t dir) {
    /*This function must be implemented in in platform specific code*/
    return false;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_ GpioDir_t gpio_dir_get(Pad_t Pad) {
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
    default:
        break;
    }
    return on_off;
}
#endif

#ifdef HAS_GPIO_EXT
bool GpioProcReadHi(GpioLogicLevel_t active) {
    bool on_off = false;
    switch(active) {
    case GPIO_LVL_HI:
        on_off = true;
        break;
    case GPIO_LVL_LOW:
        on_off = false;
        break;
    default:
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
    // LOG_DEBUG(GPIO, "Toggle P%s%u", GpioPortToStr(pad.port), pad.pin);
#endif
    GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
    res = gpio_get_state(pad, &logic_level);
    if(res) {
        GpioLogicLevel_t new_ll = gpio_opposite_level_get(logic_level);
        res = gpio_logic_level_set(pad, new_ll);
    }

    return res;
}
#endif

#ifdef HAS_GPIO_EXT
_WEAK_FUN_ bool gpio_pin_mux_get(const Pad_t Pad, uint8_t* mux) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
bool gpio_is_valid_pull(GpioPullMode_t pull) {
    bool res = false;
    switch(pull) {
    case GPIO__PULL_DOWN:
    case GPIO__PULL_UP:
    case GPIO__PULL_AIR:
    case GPIO__PULL_BOTH:
        res = true;
        break;
    default:
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
bool gpio_is_pin_single(const Pad_t Pad) {
    bool res = false;
    uint32_t i = 0, pin_cnt = 0;
    uint32_t pin_real_cnt = 0;
    pin_cnt = gpio_get_cnt();
    for(i = 0; i < pin_cnt; i++) {
        if(Pad.byte == GpioConfig[i].Pad.byte) {
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

bool GpioIsValidConfig(const GpioConfig_t* const Config) {
    bool res = false;
    bool out_res = true;
    (void) res;
    if(Config) {
        res = true;
#ifdef HAS_GPIO_EXT
        res = gpio_is_pin_single(Config->Pad);
        if(!res) {
            out_res = false;
#ifdef HAS_GPIO_DIAG
            LOG_ERROR(GPIO, "ReDefine,%s", GpioPadToStr(Config->Pad));
#endif
        }
#endif

#ifdef HAS_GPIO_EXT
        res = gpio_is_valid_pad(Config->Pad);
        if(!res) {
            out_res = false;
#ifdef HAS_GPIO_DIAG
            LOG_ERROR(GPIO, "%s,Pad,Err", GpioPadToStr(Config->Pad));
#endif
        }
#endif

        ifn(Config->dir) {
            out_res = false;
#ifdef HAS_GPIO_DIAG
            LOG_ERROR(GPIO, "%s,Dir,Error", GpioPadToStr(Config->Pad));
#endif
        }

        ifn(Config->speed) {
            // res = false;
#ifdef HAS_GPIO_DIAG
            LOG_WARNING(GPIO, "%s,speed,Error", GpioPadToStr(Config->Pad));
#endif
        }

#ifdef HAS_GPIO_EXT
        res = gpio_is_valid_pull(Config->pull);
        if(!res) {
            out_res = false;
#ifdef HAS_GPIO_DIAG
            LOG_ERROR(GPIO, "%s,pull,Error", GpioPadToStr(Config->Pad));
#endif
        }
#endif

#ifdef HAS_GPIO_EXT
        res = gpio_is_valid_mode(Config->mode);
        if(!res) {
            out_res = false;
#ifdef HAS_GPIO_DIAG
            LOG_ERROR(GPIO, "%s,mode,Error", GpioPadToStr(Config->Pad));
#endif
        }
#endif

        if(Config->drive_select) {
            // res = false;
#ifdef HAS_GPIO_DIAG
            LOG_WARNING(GPIO, "%s,drive_select,Error", GpioPadToStr(Config->Pad));
#endif
        }
    }

    return out_res;
}
