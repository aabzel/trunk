#include "gpio_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bit_utils.h"
#include "data_utils.h"
#include "gpio_config.h"
#include "gpio_custom_const.h"

#ifdef HAS_LOG
#include "log.h"
#endif /*HAS_LOG*/

#ifdef HAS_GPIO_DIAG
#include "gpio_diag.h"
#endif /*HAS_GPIO_DIAG*/

#include "nrf_gpio.h"

bool gpio_clock_init(void) {
    LOG_WARNING(GPIO, "ClockInit");
    return false;
}

bool gpio_set_logic_level(uint8_t pad_num, GpioLogicLevel_t logic_level) {
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "SetState Pad: %s=%s LogicLev: %u", GpioPad2Str(pad_num), GpioPad2WireName(pad_num), logic_level);
#endif
    bool res = false;
    res = gpio_is_valid_pad(pad_num);
    if(res) {
        nrf_gpio_pin_write((uint32_t)pad_num, (uint32_t)logic_level);
    } else {
#ifdef HAS_GPIO_DIAG
        LOG_ERROR(GPIO, "InvalidGpioPad %s", GpioPad2Str(pad_num));
#endif
    }
    return res;
}

static nrf_gpio_pin_pull_t GpioPull2NrfPull(GpioPullMode_t gpio_pull) {
    nrf_gpio_pin_pull_t nrf_pull_cfg = NRF_GPIO_PIN_NOPULL;
    switch((uint8_t)gpio_pull) {
    case GPIO__PULL_DOWN:
        nrf_pull_cfg = NRF_GPIO_PIN_PULLDOWN;
        break;
    case GPIO__PULL_UP:
        nrf_pull_cfg = NRF_GPIO_PIN_PULLUP;
        break;
    case GPIO__PULL_AIR:
        nrf_pull_cfg = NRF_GPIO_PIN_NOPULL;
        break;
    case GPIO__PULL_UNDEF:
        nrf_pull_cfg = NRF_GPIO_PIN_NOPULL;
        break;
    case GPIO__PULL_BOTH:
        nrf_pull_cfg = NRF_GPIO_PIN_NOPULL;
        break;
    }
    return nrf_pull_cfg;
}

bool gpio_set_pull(uint8_t pad_num, GpioPullMode_t pull_code) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "SetPull Pad: %s Pull: %u=%s", GpioPad2Str(pad_num), pull_code, GpioPull2Str(pull_code));
#endif
    nrf_gpio_pin_pull_t nrf_pull = GpioPull2NrfPull(pull_code);

    nrf_gpio_pin_dir_t gpio_pin_dir = nrf_gpio_pin_dir_get((uint32_t)pad_num);
    nrf_gpio_pin_input_t pin_input = nrf_gpio_pin_input_get((uint32_t)pad_num);
    nrf_gpio_pin_sense_t pin_sense = nrf_gpio_pin_sense_get((uint32_t)pad_num);
    nrf_gpio_cfg(pad_num, gpio_pin_dir, pin_input, nrf_pull, NRF_GPIO_PIN_S0S1, pin_sense);

    res = true;
    return res;
}

/*TODO rename to gpio_get_logic_level*/
bool gpio_get_state(uint8_t pad_num, GpioLogicLevel_t* const logic_level) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "%s Get", GpioPad2Str(pad_num));
#endif
    if(logic_level) {
        *logic_level = GPIO_LVL_UNDEF;
        uint32_t pin_val = 0;
        uint32_t pin_out_val = 0;
        GpioDir_t dir = gpio_get_dir(pad_num);
        switch((uint8_t)dir) {
        case GPIO_DIR_INOUT:
        case GPIO_DIR_INOUT_OD:
        case GPIO_DIR_IN:
            pin_val = nrf_gpio_pin_read((uint32_t)pad_num);
            *logic_level = (GpioLogicLevel_t)pin_val;
            res = true;
            break;
        case GPIO_DIR_OUT_PUSH_PULL:
        case GPIO_DIR_OUT_OPEN_DRAIN:
        case GPIO_DIR_OUT:
            pin_out_val = nrf_gpio_pin_out_read((uint32_t)pad_num);
            *logic_level = (GpioLogicLevel_t)pin_out_val;
            res = true;
            break;
        }
#ifdef HAS_GPIO_DIAG
        LOG_DEBUG(GPIO, "%s Get %u", GpioPad2Str(pad_num), *logic_level);
#endif
#if 0
        if(pin_val != pin_out_val) {
            *logic_level = (GpioLogicLevel_t) pin_out_val;
        } else {
            *logic_level = (GpioLogicLevel_t) pin_val;
        }
        res = true;
#endif
    }
    return res;
}

#if 0
bool gpio_is_valid_pad(uint8_t pad_num) {
    bool res = false;
    Pad_t Pad;
    Pad.byte = pad_num;
    if(Pad.port <= GPIO_PORT_MAX) {
        if(Pad.pin <= GPIO_PIN_MAX) {
            res = true;
        }
    }
    return res;
}
#endif

static GpioPullMode_t NrfPull2Pull(nrf_gpio_pin_pull_t pull) {
    GpioPullMode_t PullMode = GPIO__PULL_UNDEF;
    switch(pull) {
    case NRF_GPIO_PIN_NOPULL:
        PullMode = GPIO__PULL_AIR;
        break;
    case NRF_GPIO_PIN_PULLDOWN:
        PullMode = GPIO__PULL_DOWN;
        break;
    case NRF_GPIO_PIN_PULLUP:
        PullMode = GPIO__PULL_UP;
        break;
    }
    return PullMode;
}

bool gpio_set_pin_mcu(Pad_t Pad, GpioPinMcuSel_t mcu_sel) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Pad: %s SetCore %s", GpioPad2Str(Pad.byte), PinCoreSel2Str(mcu_sel));
#endif
    nrf_gpio_pin_mcusel_t mcusel = NRF_GPIO_PIN_MCUSEL_APP;
    switch((uint8_t)mcu_sel) {
    case NRF_GPIO_PIN_MUX_APP:
        mcusel = NRF_GPIO_PIN_MCUSEL_APP;
        res = true;
        break;
    case NRF_GPIO_PIN_MUX_NET:
        mcusel = NRF_GPIO_PIN_MCUSEL_NETWORK;
        res = true;
        break;
    case NRF_GPIO_PIN_MUX_TRACE:
        mcusel = NRF_GPIO_PIN_MCUSEL_TND;
        res = true;
        break;
    }
    if(res) {
        nrf_gpio_pin_mcu_select(Pad.byte, mcusel);
    }
    return res;
}

bool gpio_init_custom(void) {
    bool res = true;
    return res;
}

bool gpio_nrfx_toggle(uint8_t pad_num) {
    /*It can be called from I2S! (No Logs)*/
    bool res = true;
    res = gpio_is_valid_pad(pad_num);
    if(res) {
#ifdef HAS_GPIO_DIAG
        LOG_PARN(GPIO, "Toggle %s", GpioPad2Str(pad_num));
#endif
        nrf_gpio_pin_toggle((uint32_t)pad_num);
    }
    return res;
}

GpioPullMode_t gpio_get_pull(uint8_t pad_num) {
    GpioPullMode_t PullMode = GPIO__PULL_UNDEF;
    nrf_gpio_pin_pull_t pull = nrf_gpio_pin_pull_get((uint32_t)pad_num);
    PullMode = NrfPull2Pull(pull);
    return PullMode;
}

static GpioDir_t NrfDir2Dir(nrf_gpio_pin_dir_t gpio_pin_dir) {
    GpioDir_t dir = GPIO_DIR_UNDEF;
    switch(gpio_pin_dir) {
    case NRF_GPIO_PIN_DIR_INPUT:
        dir = GPIO_DIR_IN;
        break;
    case NRF_GPIO_PIN_DIR_OUTPUT:
        dir = GPIO_DIR_OUT;
        break;
    }
    return dir;
}

GpioDir_t gpio_get_dir(uint8_t pad_num) {
    GpioDir_t dir = GPIO_DIR_UNDEF;
    nrf_gpio_pin_dir_t gpio_pin_dir = NRF_GPIO_PIN_DIR_INPUT;
    gpio_pin_dir = nrf_gpio_pin_dir_get((uint32_t)pad_num);
    dir = NrfDir2Dir(gpio_pin_dir);
    return dir;
}

nrf_gpio_pin_mcusel_t nrf_gpio_pin_mcu_select_get(uint32_t pin_number) {
    nrf_gpio_pin_mcusel_t mcu = NRF_GPIO_PIN_MCUSEL_APP;
    uint32_t mcusel = 0;
    NRF_GPIO_Type* reg = nrf_gpio_pin_port_decode(&pin_number);
    uint32_t cnf = reg->PIN_CNF[pin_number];
    mcusel = 0x7UL & (cnf >> GPIO_PIN_CNF_MCUSEL_Pos);
    mcu = (nrf_gpio_pin_mcusel_t)mcusel;
    return mcu;
}

bool gpio_set_dir(uint8_t pad_num, GpioDir_t dir) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_WARNING(GPIO, "SetDir %s Dir:%s", GpioPad2Str(pad_num), GpioDir2Str(dir));
#endif
    if(dir) {
        switch((uint32_t)dir) {
        case GPIO_DIR_INOUT:
        case GPIO_DIR_INOUT_OD:
        case GPIO_DIR_IN:
            nrf_gpio_pin_dir_set((uint32_t)pad_num, NRF_GPIO_PIN_DIR_INPUT);
            res = true;
            break;
        case GPIO_DIR_OUT_PUSH_PULL:
        case GPIO_DIR_OUT_OPEN_DRAIN:
        case GPIO_DIR_OUT:
            nrf_gpio_pin_dir_set((uint32_t)pad_num, NRF_GPIO_PIN_DIR_OUTPUT);
            res = true;
            break;
        }
    }
    return res;
}

bool gpio_init_one(const GpioConfig_t* Config) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_WARNING(GPIO, "Init %s %s %s %s", GpioPad2Str(Config->pad.byte), GpioLevel2Str(Config->logic_level),
                GpioDir2Str(Config->dir), Config->name);
#endif
    res = gpio_is_pin_single(Config->pad.byte);
    if(res) {
        if(Config) {
            res = gpio_set_pull(Config->pad.byte, Config->gpio_pull);

            switch(Config->dir) {
            case GPIO_DIR_INOUT:
            case GPIO_DIR_OUT_PUSH_PULL:
            case GPIO_DIR_OUT: {
                nrf_gpio_pin_pull_t pull_config = GpioPull2NrfPull(Config->gpio_pull);
                nrf_gpio_cfg_input((uint32_t)Config->pad.byte, pull_config);
                nrf_gpio_cfg_output(Config->pad.byte);
                gpio_set_logic_level(Config->pad.byte, Config->logic_level);
                res = true;
            } break;
            case GPIO_DIR_IN: {
                res = gpio_set_pull(Config->pad.byte, Config->gpio_pull);
            } break;
            default:
#ifdef HAS_GPIO_DIAG
                LOG_WARNING(GPIO, "UndefDir %s Dir:%s", GpioPad2Str(Config->pad.byte), GpioDir2Str(Config->dir));
#endif
                res = true;
                break;
            }

            if(GPIO_CORE_MUX_UNDEF != Config->mcu_sel) {
                gpio_set_pin_mcu(Config->pad, Config->mcu_sel);
            }
            //
        }
    } else {
#ifdef HAS_GPIO_DIAG
        LOG_ERROR(GPIO, "ReDefine Pad:%s", GpioPad2Str(Config->pad.byte));
#endif /*HAS_GPIO_DIAG*/
    }
    return res;
}
