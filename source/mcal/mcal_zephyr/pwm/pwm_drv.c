#include "pwm_drv.h"

#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/zephyr.h>

#include "clock_utils.h"
#include "data_utils.h"
#include "hal_nrfx_diag.h"
#include "log.h"
#include "pwm_custom_types.h"
#include "pwm_dep.h"
#include "pwm_diag.h"
#include "pwm_types.h"
#include "time_mcal.h"

/*
 * https://docs.zephyrproject.org/apidoc/latest/group__device__model.html
 * https://docs.zephyrproject.org/apidoc/latest/group__pwm__interface.html
 * */

const static PwmStaticInfo_t PwmStaticInfo[] = {
#ifdef HAS_PWM0
    {
        .num = 0,
        .valid = true,
        .dev = DEVICE_DT_GET(DT_NODELABEL(pwm0)),
    },
#endif /*HAS_PWM0*/

#ifdef HAS_PWM1
    {
        .num = 1,
        .dev = DEVICE_DT_GET(DT_NODELABEL(pwm1)),
        .valid = true,
    },
#endif /*HAS_PWM1*/

#ifdef HAS_PWM2
    {
        .num = 2,
        .dev = DEVICE_DT_GET(DT_NODELABEL(pwm2)),
        .valid = true,
    },
#endif /*HAS_PWM2*/

#ifdef HAS_PWM3
    {
        .num = 3,
        .dev = DEVICE_DT_GET(DT_NODELABEL(pwm3)),
        .valid = true,
    },
#endif /*HAS_PWM3*/
};

PwmStaticInfo_t* PwmGetStaticNode(uint8_t num) {
    PwmStaticInfo_t* Node = NULL;
    uint8_t i = 0;
    uint8_t cnt = ARRAY_SIZE(PwmStaticInfo);
    LOG_DEBUG(PWM, "Total: %u Need %u", cnt, num);
    for(i = 0; i < cnt; i++) {
        if(num == PwmStaticInfo[i].num) {
            LOG_DEBUG(PWM, "spotNum %u", num);
            if(PwmStaticInfo[i].valid) {
                LOG_DEBUG(PWM, "spotValid %u", num);
                Node = (PwmStaticInfo_t*)&PwmStaticInfo[i];
                break;
            }
        }
    }
    return Node;
}

bool pwm_start(uint8_t num) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
    }

    return res;
}

bool pwm_phase_set(uint8_t num, uint32_t phase_us) {
    bool res = true;
#warning TODO
    return res;
}

bool pwm_duty_set(uint8_t num, PwmChannel_t channel, double duty) {
    bool res = false;
    LOG_DEBUG(PWM, "Set PWM%u, Ch:%u, Duty %6.2f", num, channel, duty);
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        PwmStaticInfo_t* Info = PwmGetStaticNode(num);
        if(Info) {
            if(Info->dev) {
                int ret = 0;
                double period_s = 1.0 / Node->frequency_hz;
                uint32_t period_ns = SEC_2_NSEC(period_s);
                uint32_t pulse_ns = ((duty) * ((double)period_ns)) / 100.0;
                ret = pwm_set(Info->dev, (uint32_t)channel, period_ns, pulse_ns, 0);
                if(0 == ret) {
                    res = true;
                    Node->duty = duty;
                    LOG_DEBUG(PWM, "PWM%u DutySetOk", num);
                } else {
                    LOG_ERROR(PWM, "PWM%u SetErr", num);
                }
            } else {
                LOG_ERROR(PWM, "PWM%u DevErr", num);
            }
        } else {
            LOG_ERROR(PWM, "PWM%u InfoErr", num);
        }
    } else {
        LOG_ERROR(PWM, "PWM%u NodeErr", num);
    }

    return res;
}

bool pwm_init_one(uint8_t num) {
    bool res = false;
    LOG_INFO(PWM, "Init %u", num);
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        LOG_INFO(PWM, "SpotNode %u", num);
        PwmStaticInfo_t* Info = PwmGetStaticNode(num);
        if(Info) {
            LOG_INFO(PWM, "SpotNode %u", num);
            if(Info->dev) {
                res = device_is_ready(Info->dev);
                if(res) {
                    LOG_INFO(PWM, "SpotDev %u", num);
                    Node->init_done = true;
                    res = true;
                } else {
                    LOG_ERROR(PWM, "DeviceIsNotReady");
                    res = false;
                }
            }
        }
    }
    return res;
}

bool pwm_stop(uint8_t num) {
    bool res = false;
    LOG_INFO(PWM, "PWM%u Stop", num);
    res = pwm_duty_set(num, 0, 0.0);
    return res;
}

bool pwm_frequency_set(uint8_t num, PwmChannel_t channel, double frequency_hz) {
    bool res = true;
    res = false;
    LOG_DEBUG(PWM, "Set PWM%u, Ch:%u, Freq %6.2f", num, channel, frequency_hz);
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        PwmStaticInfo_t* Info = PwmGetStaticNode(num);
        if(Info) {
            if(Info->dev) {
                int ret = 0;
                double period_s = 1.0 / frequency_hz;
                uint32_t period_ns = SEC_2_NSEC(period_s);
                uint32_t pulse_ns = ((Node->duty) * ((double)period_ns)) / 100.0;
                ret = pwm_set(Info->dev, (uint32_t)channel, period_ns, pulse_ns, 0);
                if(0 == ret) {
                    Node->frequency_hz = frequency_hz;
                    LOG_DEBUG(PWM, "FreqSetOk", num);
                    res = true;
                } else {
                    LOG_ERROR(PWM, "SetErr", num);
                }
            } else {
                LOG_ERROR(PWM, "DevErr", num);
            }
        } else {
            LOG_ERROR(PWM, "InfoErr", num);
        }
    } else {
        LOG_ERROR(PWM, "NodeErr", num);
    }

    return res;
}
