#include "led_mono_pwm_commands.h"

#include "convert.h"
#include "led_mono_pwm_mcal.h"
#include "log.h"

bool led_mono_pwm_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LED_MONO_PWM, res, "Num");
    }

    if(res) {

        res = led_mono_pwm_diag();
        log_info_res(LED_MONO_PWM, res, "Diag");
    } else {
        LOG_ERROR(LED_MONO_PWM, "Usage: fdat");
    }

    return res;
}

bool led_mono_pwm_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LED_MONO_PWM, res, "Num");
    }

    if(0 == argc) {
        res = led_mono_pwm_mcal_init();
        log_info_res(LED_MONO_PWM, res, "Init");
    }
    return res;
}
