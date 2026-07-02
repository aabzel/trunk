#include "led_mono_drv.h"

#include <stddef.h>
#include <string.h>

#include "code_generator.h"
#include "compiler_const.h"
#include "gpio_mcal.h"
#include "led_mono_pwm.h"
#include "std_includes.h"
#include "sys_config.h"

#ifdef HAS_PWM
#include "pwm_mcal.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_LED_MONO_DIAG
#include "led_mono_diag.h"
#endif

#ifdef HAS_GPIO_DIAG
#include "gpio_diag.h"
#endif

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_LED_DIAG
#include "led_diag.h"
#endif

#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif

#ifdef HAS_TEST_LED_MONO
#include "test_led_mono.h"
#endif

#ifdef HAS_TIME
#include "none_blocking_pause.h"
#endif

#ifdef HAS_HEALTH_MONITOR
#include "health_monitor.h"
#endif /**/

#ifndef HAS_LED
#error "Add HAS_LED"
#endif

COMPONENT_GET_NODE(LedMono, led_mono)
COMPONENT_GET_CONFIG(LedMono, led_mono)

static LedMonoHandle_t* LedMonoGetNodeByGroup(const uint32_t group, const uint32_t num) {
    LedMonoHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = led_mono_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == LedMonoInstance[i].num) {
            if(group == LedMonoInstance[i].group) {
                if(LedMonoInstance[i].valid) {
                    Node = &LedMonoInstance[i];
                    break;
                }
            }
        }
    }
    return Node;
}

static GpioLogicLevel_t LedLogicLevelZero2Voltage(GpioLogicLevel_t active) {
    GpioLogicLevel_t voltage = GPIO_LVL_UNDEF;
    switch(active) {
    case GPIO_LVL_LOW:
        voltage = GPIO_LVL_HI;
        break;
    case GPIO_LVL_HI:
        voltage = GPIO_LVL_LOW;
        break;
    default:
        break;
    }
    return voltage;
}

uint8_t LedMonoPadToNum(const Pad_t Pad) {
    uint8_t num = 0;
    LedMonoHandle_t* Node = LedPad2Node(Pad);
    if(Node) {
        num = Node->num;
    }
    return num;
}

static GpioLogicLevel_t LedLogicLevelHi2Voltage(GpioLogicLevel_t active) {
    GpioLogicLevel_t voltage = active;
    return voltage;
}

static GpioLogicLevel_t LedLogicLevel2Voltage(uint8_t val, GpioLogicLevel_t active) {
    GpioLogicLevel_t voltage = GPIO_LVL_UNDEF;
    switch(val) {
    case GPIO_LVL_LOW:
        voltage = LedLogicLevelZero2Voltage(active);
        break;
    case GPIO_LVL_HI:
        voltage = LedLogicLevelHi2Voltage(active);
        break;
    default:
        break;
    }
    return voltage;
}

bool led_mono_is_valid_num(uint8_t num) {
    bool res = false;
    LedMonoHandle_t* Node=LedMonoGetNode(num);
    if(Node) {
        res = true;
    }
    return res;
}

#ifdef HAS_LED_EXT
static GpioLogicLevel_t VoltageLow2LogicLevel(GpioLogicLevel_t active) {
    GpioLogicLevel_t LogicLevel = GPIO_LVL_UNDEF;
    switch(active) {
    case GPIO_LVL_LOW:
        LogicLevel = GPIO_LVL_HI;
        break;
    case GPIO_LVL_HI:
        LogicLevel = GPIO_LVL_LOW;
        break;
    default:
        break;
    }
    return LogicLevel;
}
#endif

#ifdef HAS_LED_EXT
static GpioLogicLevel_t VoltageHi2LogicLevel(GpioLogicLevel_t active) {
    GpioLogicLevel_t LogicLevel = GPIO_LVL_UNDEF;
    switch(active) {
    case GPIO_LVL_LOW:
        LogicLevel = GPIO_LVL_LOW;
        break;
    case GPIO_LVL_HI:
        LogicLevel = GPIO_LVL_HI;
        break;
    default:
        break;
    }
    return LogicLevel;
}
#endif

#ifdef HAS_LED_EXT
static GpioLogicLevel_t Voltage2LedLogicLevel(uint8_t voltage, GpioLogicLevel_t active) {
    GpioLogicLevel_t level = GPIO_LVL_UNDEF;
    switch(voltage) {
    case GPIO_LVL_LOW:
        level = VoltageLow2LogicLevel(active);
        break;
    case GPIO_LVL_HI:
        level = VoltageHi2LogicLevel(active);
        break;
    default:
        break;
    }
    return level;
}
#endif

#ifdef HAS_LED_EXT
LedMonoHandle_t* LedPad2Node(Pad_t Pad) {
    LedMonoHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = led_mono_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(Pad.byte == LedMonoInstance[i].pad.byte) {
            if(LedMonoInstance[i].valid) {
                Node = &LedMonoInstance[i];
                break;
            }
        }
    }
    return Node;
}
#endif

static bool led_set_state_ll(LedMonoHandle_t* const Node, const GpioLogicLevel_t des_logic_level) {
    bool res = false;
    if(Node) {
        res = false;
#ifdef HAS_LOG
        LOG_DEBUG(LED_MONO, "LED_%u,Set,Val:%u", Node->num, des_logic_level);
#endif
        switch(Node->led_phy) {
        case LED_PHY_GPIO: {
            GpioLogicLevel_t voltage = LedLogicLevel2Voltage(des_logic_level, Node->active);
            res = gpio_logic_level_set(Node->pad, voltage);
        } break;

        case LED_PHY_PWM: {
#ifdef HAS_PWM
            float pwm_duty = led_logic_level_to_duty(Node, des_logic_level);
            res = pwm_duty_set(Node->pwm_num, pwm_duty);
#endif
        } break;

        case LED_PHY_PDM: {
        } break;

        case LED_PHY_RELAY: {
        } break;

        default:
            res = false;
            break;
        }

        Node->prev = des_logic_level;
    }
    return res;
}

#ifdef HAS_LED_EXT
static GpioLogicLevel_t led_get_state_ll(LedMonoHandle_t* Node) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(LED_MONO, "%u GetLL", Node->num);
#endif
    GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
    if(Node) {
        GpioLogicLevel_t voltage_level = GPIO_LVL_UNDEF;
        res = gpio_get_state(Node->pad, &voltage_level);
        if(res) {
            logic_level = Voltage2LedLogicLevel(voltage_level, Node->active);
#ifdef HAS_GPIO_DIAG
            LOG_DEBUG(LED_MONO, "%u GetLL Vol:%s Lev:%s", Node->num, GpioLevelToStr(voltage_level),
                      GpioLevelToStr(logic_level));
#endif
        }
    }
    return logic_level;
}
#endif

#ifdef HAS_LED_EXT
bool led_set_state(Pad_t Pad, GpioLogicLevel_t des_logic_level) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(LED_MONO, "Set:%s,Val:%u", GpioPadToStr(Pad), des_logic_level);
#endif
    LedMonoHandle_t* Node = NULL;
    Node = LedPad2Node(Pad);
    if(Node) {
        res = led_set_state_ll(Node, des_logic_level);
    }
    return res;
}
#endif

#ifndef HAS_MATH
static uint8_t led_calc_pwm_sample_num(int32_t time_us, uint32_t period_ms, float duty) {
    uint8_t val = 0;
    if(100.0f < duty) {
        duty = 100.0f;
    }

    if(duty < 0.0f) {
        duty = 0.0f;
    }

    int32_t time_saw = time_us % period_ms;
    int32_t treshold = (int32_t)((((float)period_ms) * duty) / 100.0f);
    if(treshold < time_saw) {
        val = 0;
    } else {
        val = 1;
    }

    return val;
}
#endif

bool led_mono_on(LedMonoHandle_t* const Node) {
    bool res = false;
    if(Node) {
        res = true;
        res = led_set_state_ll(Node, GPIO_LVL_HI); // Error
        Node->mode = LED_MCAL_MODE_ON;
        Node->prev = GPIO_LVL_UNDEF; // Error
    } else {
#ifdef HAS_LOG
        LOG_ERROR(LED_MONO, "LED%u OnNodeErr", Node->num);
#endif
    }
    return res;
}

bool led_mono_off(LedMonoHandle_t* const Node) {
    bool res = false;
    if(Node) {
        res = true;
        Node->prev = GPIO_LVL_UNDEF;                // hang-up error in optimization
        Node->mode = LED_MCAL_MODE_OFF;             // hang-up error in optimization
        res = led_set_state_ll(Node, GPIO_LVL_LOW); // hang-up error in optimization
    } else {
#ifdef HAS_LOG
        LOG_ERROR(LED_MONO, "OffNodeErr");
#endif
    }
    return res;
}

bool led_mono_toggle(const uint8_t num) {
    bool res = false;
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        res = gpio_toggle(Node->pad);
    }
    return res;
}

bool led_mono_ctrl(const uint8_t num, const bool on_off) {
    bool res = false;
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        if(on_off) {
            res = led_mono_on(Node);
        } else {
            res = led_mono_off(Node);
        }
    }
    return res;
}

#if 0
bool led_mono_hw_pwm(uint8_t num, float frequency_hz, float duty_cycle) {
    bool res = false;
#ifdef HAS_PWM
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        int8_t pwm_num = pwm_gpio_pad_to_pwm_num(Node->pad);
        if(0 <= pwm_num) {
            res = pwm_freq_duty_set((uint8_t)pwm_num, frequency_hz, duty_cycle);
        }
    }
#endif
    return res;
}
#endif

bool led_mono_frequency_set(const uint8_t num, const float frequency_hz) {
    bool res = true;
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        Node->period_ms = freq2period_ms(frequency_hz);
        res = true;
    }
    return res;
}

bool led_mono_sw_pwm(uint8_t num, float freq_hz, float duty) {
    bool res = true;
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        Node->prev = GPIO_LVL_UNDEF;
        Node->duty = duty;
        Node->mode = LED_MCAL_MODE_PWM;
        if(0.0 < freq_hz) {
#ifdef HAS_MATH
            Node->period_ms = freq2period_ms(freq_hz);
#else
            Node->period_ms = 1000;
#endif
        } else {
#ifdef HAS_LOG
            LOG_INFO(LED_MONO, "FreqErr %f Hz", freq_hz);
#endif
        }
        Node->phase_ms = 0;
    }
    return res;
}

bool led_mono_set(uint8_t num, GpioLogicLevel_t level) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(LED_MONO, "LED_%u Set %s", num, GpioLevelToStr(level));
#endif
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        res = led_set_state_ll(Node, level);
    } else {
#ifdef HAS_LOG
        LOG_ERROR(LED_MONO, "LED_%u SetNodeErr", num);
#endif
    }
    return res;
}

#ifdef HAS_LED_EXT
GpioLogicLevel_t led_mono_get(uint8_t num) {
#ifdef HAS_LOG
    LOG_DEBUG(LED_MONO, "%u Get", num);
#endif
    GpioLogicLevel_t level = GPIO_LVL_UNDEF;
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        level = led_get_state_ll(Node);
#ifdef HAS_GPIO_DIAG
        LOG_DEBUG(LED_MONO, "LED_%u Set %s", num, GpioLevelToStr(level));
#endif
    } else {
#ifdef HAS_LOG
        LOG_ERROR(LED_MONO, "%u GetNodeErr", num);
#endif
    }
    return level;
}
#endif

bool led_mono_duration_set(const uint8_t num, const uint32_t duration_ms) {
    bool res = false;
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        if(0xFFFFFFFF == duration_ms) {
            Node->off_time_stamp = 0xFFFFFFFF;
        } else {
            Node->off_time_stamp = time_get_ms32() + duration_ms;
        }
        res = true;
    }
    return res;
}

#ifdef HAS_LED_EXT
static bool led_mono_blink_ll(LedMonoHandle_t* Node, uint32_t duration_ms) {
    bool res = false;
    if(Node && (0 < duration_ms)) {
        Node->prev = GPIO_LVL_UNDEF;
#ifdef HAS_TIME
        Node->on_time_ms = time_get_ms32();
#endif
        Node->duration_ms = duration_ms;
        Node->prev_mode = Node->mode;
        Node->mode = LED_MCAL_MODE_BLINK;
        res = led_set_state_ll(Node, GPIO_LVL_HI);
    }
    return res;
}
#endif

#ifdef HAS_LED_EXT
bool led_mono_blink(uint8_t num, uint32_t duration_ms) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(LED_MONO, "LED_%u Blink %u ms", num, duration_ms);
#endif
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        res = led_mono_blink_ll(Node, duration_ms);
    } else {
#ifdef HAS_LOG
        LOG_DEBUG(LED_MONO, "%u Blink,NodeErr", num);
#endif
    }
    return res;
}
#endif

bool led_mono_mode_set(uint8_t num, LedMode_t mode) {
    bool res = false;
#ifdef HAS_LED_DIAG
    LOG_INFO(LED_MONO, "LED%u,SetMode:%u=%s", num, mode, LedModeToStr(mode));
#endif
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        Node->mode = mode;
        res = true;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(LED_MONO, "LED%u,NodeErr", num);
#endif
    }
    return res;
}

bool led_mono_init_custom(void) {
    bool res = true;
#ifdef HAS_LOG
    uint32_t cnt = led_mono_get_cnt();
    LOG_INFO(LED_MONO, "LEDcnt:%u", cnt);
#endif
    return res;
}

static bool led_mono_init_common(const LedMonoConfig_t* const Config, LedMonoHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->active = Config->active;
            Node->color = Config->color;
            Node->group = Config->group;
            Node->prev = GPIO_LVL_UNDEF;
            Node->duty = Config->duty;
            Node->led_phy = Config->led_phy;
#ifdef HAS_PWM
            Node->pwm_num = Config->pwm_num;
            Node->pwm_frequency_hz = Config->pwm_frequency_hz;
            Node->pwm_duty_on = Config->pwm_duty_on;
            Node->pwm_duty_off = Config->pwm_duty_off;
#endif
            Node->period_ms = Config->period_ms;
            Node->phase_ms = Config->phase_ms;
            Node->on_time_ms = Config->on_time_ms;
            Node->duration_ms = Config->duration_ms;
            Node->num = Config->num;
            Node->mode = Config->mode;
            Node->name = Config->name;
            Node->pad = Config->pad;
            res = true;
        }
    }
    return res;
}

static bool led_mono_init_gpio(LedMonoHandle_t* const Node) {
    bool res = false;
    if(Node) {
        res = gpio_dir_set(Node->pad, GPIO_DIR_OUT);
        res = gpio_mode_set(Node->pad, GPIO_API_MODE_GPIO);
        res = gpio_pull_set(Node->pad, GPIO__PULL_AIR);
    }
    return res;
}

static bool led_mono_init_node(LedMonoHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->off_time_stamp = 0xFFFFFFFF;
        res = true;
#ifdef HAS_PWM
        if(LED_PHY_PWM == Node->led_phy) {
            res = pwm_frequency_set(Node->pwm_num, Node->pwm_frequency_hz);
        }
#endif
    }
    return res;
}

static bool LedMonoIsValidConfig(const LedMonoConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = gpio_is_valid_pad(Config->pad);
        ifn(res) {
#ifdef HAS_LOG
            LOG_ERROR(LED_MONO, "Gpio,Err:%u", Config->num);
#endif
        }

#ifdef HAS_PWM
        res = pwm_is_valid_duty_cycle(Config->duty);
        ifn(res) {
#ifdef HAS_LOG
            LOG_ERROR(LED_MONO, "Duty,Err:%u", Config->num);
#endif
        }

        res = LedMonoIsValidConfigPwm(Config);
#endif

        ifn(0 < Config->period_ms) {
#ifdef HAS_LOG
            LOG_ERROR(LED_MONO, "period,Err:%u", Config->num);
#endif
        }

        ifn(Config->name) {
#ifdef HAS_LOG
            LOG_ERROR(LED_MONO, "name,Err:%u", Config->num);
#endif
        }

        ifn(Config->led_phy) {
#ifdef HAS_LOG
            LOG_ERROR(LED_MONO, "ledPhy,Err:%u", Config->num);
#endif
        }

        ifn(Config->mode) {
#ifdef HAS_LOG
            LOG_ERROR(LED_MONO, "mode,Err:%u", Config->num);
#endif
        }
    }
    return res;
}

bool led_mono_init_one(uint32_t num) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(LED_MONO, "LED_MONO_%u,TryInit", num);
#endif
    const LedMonoConfig_t* Config = LedMonoGetConfig(num);
    if(Config) {
        res = LedMonoIsValidConfig(Config);
        if(res) {
#ifdef HAS_LED_MONO_DIAG
            LOG_WARNING(LED_MONO, "Cfg:%s", LedMonoConfigToStr(Config));
#endif
            LedMonoHandle_t* Node = LedMonoGetNode(num);
            if(Node) {
                led_mono_init_common(Config, Node);
                led_mono_init_node(Node);
                led_mono_init_gpio(Node);
                /*TODO Init GPIO for LED*/
#ifdef HAS_TEST_LED_MONO
                res = led_mono_on(Node);
#endif

#ifdef HAS_LOG
                log_level_get_set(LED_MONO, LOG_LEVEL_INFO);
#endif
            } else {
#ifdef HAS_LOG
                LOG_ERROR(LED_MONO, "NodeErr:%u", num);
#endif
            }
            Node->init = true;
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_ERROR(LED_MONO, "CfgErr:%u", num);
#endif
        }
    }

    return res;
}

_WEAK_FUN_ bool led_mono_fix(void) { return true; }

static bool led_mono_proc_one_ll(LedMonoHandle_t* const Node) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(LED_MONO, "Proc:%u", Node->num);
#endif
    if(Node) {
#ifdef HAS_LOG
        log_level_t ll = log_level_get(LED_MONO);
        if(LOG_LEVEL_PARANOID == ll) {
#ifdef HAS_LED_MONO_DIAG
            LedMonoDiag(Node);
#endif
        }
#endif

        uint64_t time_us = 0;
#ifdef HAS_TIME
        time_us = time_get_us();
        Node->cur_time_ms = (uint32_t)(time_us / 1000);
#else
        Node->cur_time_ms++;
        time_us = Node->cur_time_ms;
#endif /*HAS_TIME*/
        uint8_t val = 0;
        switch(Node->mode) {
        case LED_MCAL_MODE_ON: {
            val = 1;
            res = true;
            // Node->prev = GPIO_LVL_UNDEF;
        } break;
        case LED_MCAL_MODE_OFF: {
            val = 0;
            // Node->prev = GPIO_LVL_UNDEF;
            res = true;
        } break;
#ifdef HAS_LED_EXT
        case LED_MCAL_MODE_BLINK: {
            uint32_t cur_duration_ms = 0;
            cur_duration_ms = Node->cur_time_ms - Node->on_time_ms;
            if(Node->duration_ms < cur_duration_ms) {
                res = true;
                val = 0;
                const LedMonoConfig_t* Config = LedMonoGetConfig(Node->num);
                if(Config) {
                    Node->mode = Config->mode;
                }
            } else {
                val = 1;
            }
        } break;
#endif
        case LED_MCAL_MODE_PWM: {
#ifdef HAS_MATH
            val = calc_pwm_sample_num(time_us, Node->period_ms, Node->duty, Node->phase_ms);
#else
            val = led_calc_pwm_sample_num((int32_t)time_us, Node->period_ms, Node->duty);
#endif
            res = true;
        } break;
        default: {
            res = false;
        } break;
        }

        if(res) {
            if(Node->prev != val) {
#ifdef HAS_GPIO_DIAG
                LOG_NOTICE(LED_MONO, "%s NewVal: %u", GpioPadToStr(Node->pad), val);
#endif
                res = led_set_state_ll(Node, (GpioLogicLevel_t)val);
            }
        } else {
        }
        Node->prev = val;

        if(Node->off_time_stamp < Node->cur_time_ms) {
            Node->mode = LED_MCAL_MODE_OFF;
        }
    }
    return res;
}

static bool led_mono_proc_group_one(uint32_t group, uint32_t num) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(LED_MONO, "Proc:Gr:%u,N:%u", group, num);
#endif
    LedMonoHandle_t* Node = LedMonoGetNodeByGroup(group, num);
    if(Node) {
        res = led_mono_proc_one_ll(Node);
    }
    return res;
}

bool led_mono_proc_one(uint32_t num) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(LED_MONO, "Proc:%u", num);
#endif
    led_mono_fix();
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        res = led_mono_proc_one_ll(Node);
    }
    return res;
}

bool led_mono_proc_group(uint32_t group) {
    bool res = true;
    uint32_t ok = 0;
    uint32_t cnt = led_mono_get_cnt();
    uint32_t num = 0;
    for(num = 0; num <= cnt; num++) {
        res = led_mono_proc_group_one(group, num);
        if(res) {
            ok++;
        }
    }
    if(ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

COMPONENT_INIT_PATTERT(LED_MONO, LED_MONO, led_mono)
COMPONENT_PROC_PATTERT(LED_MONO, LED_MONO, led_mono)
