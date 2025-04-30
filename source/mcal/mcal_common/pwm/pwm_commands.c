#include "pwm_commands.h"

#include "convert.h"
#include "log.h"
#include "pwm_drv.h"

bool pwm_enable_command(int32_t argc, char* argv[]) { return false; }

bool pwm_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = pwm_init();
    return res;
}

bool pwm_diag_command(int32_t argc, char* argv[]) { return false; }

bool pwm_phase_set_command(int32_t argc, char* argv[]) { return false; }

bool pwm_duty_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t channel = PWM_CHANNEL_UNDEF;
    double duty_cycle = 0.0;
    if(3 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErr Num %s", argv[0]);
        }

        res = try_str2uint8(argv[1], &channel);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErr Index %s", argv[1]);
        }

        res = try_str2double(argv[2], &duty_cycle);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErr Duty %s", argv[2]);
        }
    }

    if(res) {
        res = pwm_duty_set(num, (PwmChannel_t)channel, duty_cycle);
        if(res) {
            LOG_INFO(PWM, "SetDutyOk T:%u C:%u D:%6.2f", num, channel, duty_cycle);
        } else {
            LOG_ERROR(PWM, "SetDutyErr T:%u C:%u D:%6.2f", num, channel, duty_cycle);
        }
    } else {
        LOG_ERROR(PWM, "Usage: psd TimNum Ch Duty");
    }
    return res;
}

bool pwm_period_set_command(int32_t argc, char* argv[]) { return false; }
