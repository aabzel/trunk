#include "pwm_custom_commands.h"

#include "pwm_mcal.h"
#include "log.h"
#include "convert.h"

bool pwm_phase_deg_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 3;
    float phase_deg = 0.0f;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(PWM, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &phase_deg);
        log_res(PWM, res, "PhaseDeg");
    }

    if(res) {
        res = pwm_phase_deg(num, phase_deg);
        if(res) {
            LOG_INFO(PWM, "SetPhaseSwOk,PWM%u,Pha:%f deg", num, phase_deg);
        } else {
            LOG_ERROR(PWM, "SetPhaseSwErr,PWM%u,Pha:%f deg", num, phase_deg);
        }
    } else {
        LOG_ERROR(PWM, "Usage: ppasd PwmNum PhaseDeg");
    }
    return res;
}

bool pwm_phase_hw_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 3;
    int32_t phase_us = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(PWM, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], &phase_us);
        log_res(PWM, res, "PhaseUs");
    }

    if(res) {
        res = pwm_phase_set_hw(num, phase_us);
        if(res) {
            LOG_INFO(PWM, "SetPhaseSwOk,PWM%u,Pha:%d us", num, phase_us);
        } else {
            LOG_ERROR(PWM, "SetPhaseSwErr,PWM%u,Pha:%d us", num, phase_us);
        }
    } else {
        LOG_ERROR(PWM, "Usage: pphah PwmNum PhaseUs");
    }
    return res;
}


bool pwm_phase_sw_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 3;
    int32_t phase_us = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(PWM, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], &phase_us);
        log_res(PWM, res, "PhaseUs");
    }

    if(res) {
        res = pwm_phase_set_sw(num, phase_us);
        if(res) {
            LOG_INFO(PWM, "SetPhaseSwOk,PWM%u,Pha:%d us", num, phase_us);
        } else {
            LOG_ERROR(PWM, "SetPhaseSwErr,PWM%u,Pha:%d us", num, phase_us);
        }
    } else {
        LOG_ERROR(PWM, "Usage: ppas PwmNum PhaseUs");
    }
    return res;
}
