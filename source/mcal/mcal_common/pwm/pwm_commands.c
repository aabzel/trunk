#include "pwm_commands.h"

#include "common_diag.h"
#include "convert.h"
#include "log.h"
#include "pwm_diag.h"
#include "pwm_mcal.h"

bool pwm_signal_parse(int32_t argc, char* argv[], uint32_t start, PwmSignalBinary_t* const Node) {
    bool res = false;

    if(start <= argc) {
        res = try_str2float(argv[start], &Node->frequency_hz);
        log_info_res(PWM, res, "FrequencyHz");
    }

    if((start + 1) <= argc) {
        res = try_str2float(argv[start + 1], &Node->duty);
        log_info_res(PWM, res, "duty");
    }

    if((start + 2) <= argc) {
        res = try_str2float(argv[start + 2], &Node->phase_s);
        log_info_res(PWM, res, "phase_s");
    }
    return res;
}

bool pwm_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = pwm_mcal_init();
    return res;
}

bool pwm_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }
    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(res) {
        res = pwm_diag(keyWord1, keyWord2);
    } else {
        LOG_ERROR(PWM, "Usage: pwd keyWord");
    }

    return res;
}

/*
pu Num Duty
pdu 1 10
pdu 2 20
pdu 2 21
pdu 2 25
pdu 2 30
pdu 2 40
pdu 2 90
 */
bool pwm_duty_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    float duty_cycle = 0.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(PWM, res, "Num");
    }

    if(2 <= argc) {

        res = try_str2float(argv[1], &duty_cycle);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErr Duty %s", argv[1]);
        }
    }

    if(res) {
        switch(argc) {
        case 1: {
            res = pwm_duty_get(num, &duty_cycle);
            if(res) {
                LOG_INFO(PWM, "Get,DutyOk PWM%u,Duty:%6.2f%%", num, duty_cycle);
            } else {
                LOG_ERROR(PWM, "Get,DutyErr PWM%u", num);
            }
        } break;
        case 2: {
            res = pwm_duty_set(num, duty_cycle);
            if(res) {
                LOG_INFO(PWM, "Set,DutyOk,PWM%u,Duty:%6.2f %%", num, duty_cycle);
            } else {
                LOG_ERROR(PWM, "Set,DutyErr,PWM%u", num);
            }
        } break;
        default: {
            res = false;
        } break;
        }
    } else {
        LOG_ERROR(PWM, "Usage: pdu Num Duty");
    }
    return res;
}

bool pwm_period_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t pwm_index = 0;
    uint32_t pesiod_ms = 1000;
    if(2 == argc) {
        res = true;

        res = try_str2uint8(argv[0], &pwm_index);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErrindex %s", argv[0]);
        }

        if(res) {
            res = try_str2uint32(argv[1], &pesiod_ms);
            if(false == res) {
                LOG_ERROR(PWM, "ParseErrpesiod_ms %s", argv[1]);
            }
        }
    }

    if(res) {
        res = false;
    } else {
        LOG_ERROR(PWM, "Usage: psp TimNum pesiod_us");
    }
    return res;
}

bool pwm_enable_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    bool on = 0;
    if(2 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(PWM, res, "Num");

        res = try_str2bool(argv[1], &on);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErrOn %s", argv[1]);
        }
    }

    if(res) {
        LOG_INFO(PWM, "PWM%u %s", num, OnOffToStr(on));
        res = pwm_ctrl(num, on);
        if(res) {
            LOG_INFO(PWM, "Ok");
        } else {
            LOG_ERROR(PWM, "ERR");
        }
    } else {
        LOG_ERROR(PWM, "Usage: pe PwmNum En");
    }
    return res;
}

bool pwm_frequency_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    float frequency_hz = 0.0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(PWM, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &frequency_hz);
        log_res(PWM, res, "Freq");
    }

    if(res) {
        switch(argc) {
        case 1: {
            res = pwm_frequency_get(num, &frequency_hz);
            if(res) {
                LOG_INFO(PWM, "PWM%u,Get,Freq:%f Hz", num, frequency_hz);
            }
        } break;
        case 2: {
            LOG_INFO(PWM, "PWM%u Freq:%f Hz", num, frequency_hz);
            res = pwm_frequency_set(num, frequency_hz);
            if(res) {
                LOG_INFO(PWM, "FreqSetOk");
            } else {
                LOG_ERROR(PWM, "FreqSetErr");
            }
        } break;
        default: {
            res = false;
        } break;
        }
    } else {
        LOG_ERROR(PWM, "Usage: pf PwmNum FrequencyHz");
    }
    return res;
}

/*
 pwm_phase 3 0
 */
bool pwm_phase_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t phase = 0;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(PWM, res, "Num");

        res = try_str2uint32(argv[1], &phase);
        log_res(PWM, res, "Phase");
    }
    if(res) {
        res = pwm_phase_set(num, phase);
        if(res) {
            LOG_INFO(PWM, "SetPhaseOk T:%u P:%u", num, phase);
        } else {
            LOG_ERROR(PWM, "SetPhaseErr T:%u P:%u", num, phase);
        }
    } else {
        LOG_ERROR(PWM, "Usage: psd TimNum Phase");
    }
    return res;
}

bool pwm_polarity_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t polarity = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(PWM, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &polarity);
        log_res(PWM, res, "polarity");
    }

    if(res) {
        res = pwm_polarity_set(num, polarity);
        log_res(PWM, res, "SetPolarity");
    } else {
        LOG_ERROR(PWM, "Usage: po Num Polarity");
    }
    return res;
}
