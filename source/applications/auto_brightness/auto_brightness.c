#include "auto_brightness.h"

#include "auto_brightness_dep.h"
#include "code_generator.h"
#include "data_utils.h"
#include "led_mono_drv.h"
#include "schmitt_trigger.h"
#ifdef HAS_PWM
#include "pwm_drv.h"
#endif
#include "auto_brightness_diag.h"
#include "distance_drv.h"
#include "log.h"

COMPONENT_GET_NODE(AutoBrightness, auto_brightness)

COMPONENT_GET_CONFIG(AutoBrightness, auto_brightness)

double Dist2Duty(double dist_m) {
    double duty_cycle = 0.0;
    duty_cycle = -50.0 * dist_m + 100.0;
    LIMIT_VALUE(0.0, 100.0, duty_cycle);
    LOG_DEBUG(AUTO_BRIGHTNESS, "Dist %f m->Duty: %f %%", dist_m, duty_cycle);
    return duty_cycle;
}

bool auto_brightness_ff_led(AutoBrightnessHandle_t* Node) {
    bool res = false;
    if(Node) {
        LedHandle_t* LedNode = LedGetNode(Node->led_num);
        if(LedNode) {
            SchmittTriggerState_t state = schmitt_trigger_get_state(Node->schmitt_trigger_num);
            switch(state) {
            case SCHMITT_TRIGGER_STATE_UP: {
                res = led_mono_off(LedNode);
            } break;
            case SCHMITT_TRIGGER_STATE_DOWN: {
                res = led_mono_on(LedNode);
            } break;
            default:
                break;
            }
        }
    }
    return res;
}

bool auto_brightness_proc_one(uint8_t num) {
    bool res = false;
    AutoBrightnessHandle_t* Node = AutoBrightnessGetNode(num);
    if(Node) {
        LOG_DEBUG(AUTO_BRIGHTNESS, "SpotNode %s", AutoBrightnessNode2Str(Node));
        DistanceHandle_t* DistNode = DistanceGetNode(Node->dist_num);
        if(DistNode) {
            LOG_DEBUG(AUTO_BRIGHTNESS, "Dist: %6.2f m", DistNode->distance_m);
            Node->distance_m = DistNode->distance_m;
            Node->duty_cycle = Dist2Duty(DistNode->distance_m);

#ifdef HAS_PWM
            res = pwm_is_valid(Node->pwm_num);
            if(res) {
                res = true;
                res = pwm_duty_set(Node->pwm_num, Node->channel, Node->duty_cycle);
            } else {
                LOG_DEBUG(AUTO_BRIGHTNESS, "Undef PWM%u Err", Node->pwm_num);
            }
#endif

            if(Node->schmitt_trigger_num) {
                res = schmitt_trigger_proc_val(Node->schmitt_trigger_num, DistNode->distance_m);
                if(res) {
                    res = auto_brightness_ff_led(Node);
                    LOG_DEBUG(AUTO_BRIGHTNESS, "FF%u, Value:%f ProcOk", Node->schmitt_trigger_num,
                              DistNode->distance_m);
                } else {
                    LOG_ERROR(AUTO_BRIGHTNESS, "FF%u Err", Node->schmitt_trigger_num);
                }
            }
        }
    } else {
        LOG_PARN(AUTO_BRIGHTNESS, "NodeErr %u", num);
    }

    return res;
}

bool auto_brightness_init_one(uint8_t num) {
    bool res = true;
    const AutoBrightnessConfig_t* Config = AutoBrightnessGetConfig(num);
    if(Config) {
        AutoBrightnessDiagConfig(Config);
        AutoBrightnessHandle_t* Node = AutoBrightnessGetNode(num);
        if(Node) {
            Node->dist_num = Config->dist_num;
            Node->binary = Config->binary;
            Node->schmitt_trigger_num = Config->schmitt_trigger_num;
            Node->pwm_num = Config->pwm_num;
            Node->led_num = Config->led_num;
            Node->pwm_freq_hz = Config->pwm_freq_hz;
            Node->err_cnt = 0;
            Node->on = false;
            Node->valid = true;
#ifdef HAS_PWM
            Node->channel = Config->channel;
            res = pwm_frequency_set(Node->pwm_num, Node->channel, (double)Node->pwm_freq_hz);
            res = pwm_phase_set(Node->pwm_num, 0);
#endif
            // res = pwm_start(Node->pwm_num);
            res = true;
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(AUTO_BRIGHTNESS, AUTO_BRIGHTNESS, auto_brightness)

COMPONENT_PROC_PATTERT(AUTO_BRIGHTNESS, AUTO_BRIGHTNESS, auto_brightness)
