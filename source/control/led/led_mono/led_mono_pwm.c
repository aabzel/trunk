#include "led_mono_pwm.h"

#include "code_generator.h"
#include "std_includes.h"

#ifdef HAS_PWM
#include "pwm_mcal.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

float led_logic_level_to_duty(const LedMonoHandle_t* const Node, const GpioLogicLevel_t des_logic_level) {
    float pwm_duty = 0.0;
    switch (des_logic_level) {
    case GPIO_LVL_LOW: {
        pwm_duty = Node->pwm_duty_off;
    }
        break;

    case GPIO_LVL_HI: {
        pwm_duty = Node->pwm_duty_on;
    }
        break;
    default: {
        pwm_duty = 0.0;
    }
        break;
    }
    return pwm_duty;
}

bool led_mono_hw_pwm(uint8_t num, float frequency_hz, float duty_cycle) {
    bool res = false;
    LedMonoHandle_t *Node = LedMonoGetNode(num);
    if(Node) {
        int8_t pwm_num = pwm_gpio_pad_to_pwm_num(Node->pad);
        if(0 <= pwm_num) {
            res = pwm_freq_duty_set((uint8_t) pwm_num, frequency_hz, duty_cycle);
        }
    }
    return res;
}

bool led_mono_set_off_duty(const uint8_t num, const float off_duty) {
    bool res = false;
    LedMonoHandle_t *Node = LedMonoGetNode(num);
    if(Node) {
        res = pwm_is_valid_duty_cycle(off_duty);
        if(LED_PHY_PWM != Node->led_phy) {
            LOG_WARNING(LED, "LED%u,NotInPWMphy,PHY:%u", num, Node->led_phy);
        }
        if(res) {
            LOG_INFO(LED, "LED%u,SetOffDuty:%f->%f %%", num, Node->pwm_duty_off, off_duty);
            Node->pwm_duty_off = off_duty;
        }
    } else {
        res = false;
    }
    return res;
}

bool led_mono_set_on_duty(const uint8_t num, const float on_duty) {
    bool res = false;
    LedMonoHandle_t *Node = LedMonoGetNode(num);
    if(Node) {
        res = pwm_is_valid_duty_cycle(on_duty);
        if(LED_PHY_PWM != Node->led_phy) {
            LOG_WARNING(LED, "LED%u,NotInPWMphy,PHY:%u", num, Node->led_phy);
        }
        if(res) {
            LOG_INFO(LED, "LED%u,SetOnDuty:%f->%f %%", num, Node->pwm_duty_on, on_duty);
            Node->pwm_duty_on = on_duty;
        }
    } else {
        res = false;
    }
    return res;
}

bool LedMonoIsValidConfigPwm(const LedMonoConfig_t* const Config) {
    bool res = true;
    res = pwm_is_valid_duty_cycle(Config->pwm_duty_on);
    ifn(res) {
#ifdef HAS_LOG
        LOG_ERROR(LED_MONO, "DutyOn,Err:%u", Config->num);
#endif
    }

    res = pwm_is_valid_duty_cycle(Config->pwm_duty_off);
    ifn(res) {
#ifdef HAS_LOG
        LOG_ERROR(LED_MONO, "DutyOff,Err:%u", Config->num);
#endif
    }

    ifn(0 < Config->pwm_frequency_hz) {
#ifdef HAS_LOG
        LOG_ERROR(LED_MONO, "HwPwmFrequency,Err:%u", Config->num);
#endif
    }
    return res;
}
