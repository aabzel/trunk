#include "pwm_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "clock.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "pwm_config.h"
#include "pwm_const.h"
#include "pwm_drv.h"
#include "pwm_stm32_diag.h"
#include "str_utils.h"
#include "sys_config.h"
#include "table_utils.h"
#include "writer_config.h"

static bool pwm_diag_ll(char* key_word1, char* key_word2) {
    bool res = false;
    uint8_t tim_num = 0;
    double duty_cycle = 0.0;
    char temp_str[120];
    static const table_col_t cols[] = {{5, "No"}, {5, "Tim"}, {5, "Chan"}, {8, "Duty"}};
    uint16_t num = 0;
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    for(tim_num = 1; tim_num <= TIMER_COUNT; tim_num++) {
        uint8_t channel_num = 0;
        for(channel_num = TIM_CHANNEL1; channel_num <= TIM_CHANNEL4; channel_num++) {
            res = pwm_get_duty(tim_num, (TimChannel_t)channel_num, &duty_cycle);
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s T%02u " TSEP, temp_str, tim_num);
            snprintf(temp_str, sizeof(temp_str), "%s C%1u  " TSEP, temp_str, channel_num);
            snprintf(temp_str, sizeof(temp_str), "%s D%5.2f " TSEP, temp_str, duty_cycle);
            res = is_contain(temp_str, key_word1, key_word2);
            if(res) {
                cli_printf(TSEP " %3u ", num);
                cli_printf("%s" CRLF, temp_str);
                num++;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));

    return res;
}

bool pwm_diag_ll_command(int32_t argc, char* argv[]) {
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

    if(2 < argc) {
        LOG_ERROR(PWM, "Usage: pdl keyWord");
    }
    if(res) {
        res = pwm_diag_ll(keyWord1, keyWord2);
    }
    return res;
}

bool pwm_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
    } else {
        LOG_ERROR(PWM, "Usage: pwd");
    }

    return res;
}

bool pwm_set_period_command(int32_t argc, char* argv[]) {
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

bool pwm_set_duty_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t tim_num = 0;
    uint8_t channel = TIM_UNDEF;
    double duty_cycle = 0.0;
    if(3 == argc) {
        res = try_str2uint8(argv[0], &tim_num);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErrindex %s", argv[0]);
        }

        res = try_str2uint8(argv[1], &channel);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErrindex %s", argv[1]);
        }

        res = try_str2double(argv[2], &duty_cycle);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErrduty %s", argv[2]);
        }
    }

    if(res) {
        res = pwm_set_duty(tim_num, (TimChannel_t)channel, duty_cycle);
        if(res) {
            LOG_INFO(PWM, "SetDutyOk T:%u C:%u D:%f", tim_num, channel, duty_cycle);
        } else {
            LOG_ERROR(PWM, "SetDutyErr T:%u C:%u D:%f", tim_num, channel, duty_cycle);
        }
    } else {
        LOG_ERROR(PWM, "Usage: psd TimNum Ch Duty");
    }
    return res;
}

bool pwm_set_phase_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t tim_num = 0;
    uint32_t phase = 0;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &tim_num);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErr TimNum %s", argv[0]);
        }
        res = try_str2uint32(argv[1], &phase);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErr Phase %s", argv[1]);
        }
    }
    if(res) {
        res = pwm_set_phase(tim_num, phase);
        if(res) {
            LOG_INFO(PWM, "SetPhaseOk T:%u P:%u", tim_num, phase);
        } else {
            LOG_ERROR(PWM, "SetPhaseErr T:%u P:%u", tim_num, phase);
        }
    } else {
        LOG_ERROR(PWM, "Usage: psd TimNum Phase");
    }
    return res;
}

bool pwm_enable_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t timer_num = 0;
    uint8_t channel = 0;
    bool on = 0;
    if(3 == argc) {
        res = try_str2uint8(argv[0], &timer_num);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErr TimNum %s", argv[0]);
        }
        res = try_str2uint8(argv[1], &channel);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErrindex %s", argv[1]);
        }
        res = try_str2bool(argv[2], &on);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErrOn %s", argv[2]);
        }
    }

    if(res) {
        res = pwm_ctrl(timer_num, (TimChannel_t)channel, on);
        if(res) {
            LOG_INFO(PWM, "Ok");
        } else {
            LOG_ERROR(PWM, "ERR");
        }
    } else {
        LOG_ERROR(PWM, "Usage: pe TimNum Chan On");
    }
    return res;
}

bool oc_enable_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t timer_num = 0;
    uint8_t channel = 0;
    bool on = 0;
    if(3 == argc) {
        res = try_str2uint8(argv[0], &timer_num);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErr TimNum %s", argv[0]);
        }
        res = try_str2uint8(argv[1], &channel);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErrindex %s", argv[1]);
        }
        res = try_str2bool(argv[2], &on);
        if(false == res) {
            LOG_ERROR(PWM, "ParseErrOn %s", argv[2]);
        }
    }

    if(res) {
        res = oe_ctrl(timer_num, (TimChannel_t)channel, on);
        if(res) {
            LOG_INFO(PWM, "Ok");
        } else {
            LOG_ERROR(PWM, "ERR");
        }
    } else {
        LOG_ERROR(PWM, "Usage: oe TimNum Chan On");
    }
    return res;
}
