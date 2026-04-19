#include "pwm_phase_demo_commands.h"

#include "convert.h"
#include "log.h"
#include "pwm_phase_demo_mcal.h"


bool pwm_phase_demo_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(PWM_PHASE_DEMO, res, "Num");
    }

    if(res) {
        res = pwm_phase_demo_diag_one(num);
        log_info_res(PWM_PHASE_DEMO, res, "Diag");

        res = pwm_phase_demo_diag();
        log_info_res(PWM_PHASE_DEMO, res, "Diag");
    } else {
        LOG_ERROR(PWM_PHASE_DEMO, "Usage: fdat");
    }

    return res;
}

bool pwm_phase_demo_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(PWM_PHASE_DEMO, res, "Num");
    }

    if(0 == argc) {
        res = pwm_phase_demo_mcal_init();
        log_info_res(PWM_PHASE_DEMO, res, "Init");
    }
    return res;
}
