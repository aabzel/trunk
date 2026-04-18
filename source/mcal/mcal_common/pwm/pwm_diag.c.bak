#include "pwm_diag.h"

#include <stdio.h>
#include <string.h>

#include "gpio_diag.h"
#include "log.h"
#include "microcontroller_const.h"
#include "num_to_str.h"
#include "pwm_mcal.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

const char* PwmSignalToStr(const PwmSignalBinary_t* const PwmSignal) {
    if(PwmSignal) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sDuty:%f %%,", text, PwmSignal->duty);
        snprintf(text, sizeof(text), "%sFreq:%f Hz,", text, PwmSignal->frequency_hz);
        snprintf(text, sizeof(text), "%sPhase:%f s,", text, PwmSignal->phase_s);
    }
    return text;
}

const char* PwmConfigToStr(const PwmConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sEn:%u,", text, Config->on);
        snprintf(text, sizeof(text), "%sPHA:%u us,", text, Config->phase_us);
        snprintf(text, sizeof(text), "%sDuty:%f %%,", text, Config->duty);
        snprintf(text, sizeof(text), "%sFreq:%f Hz,", text, Config->frequency_hz);
        snprintf(text, sizeof(text), "%sName:%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sTIM%u_", text, Config->timer_num);
        snprintf(text, sizeof(text), "%sCH%u,", text, Config->timer_channel);
        snprintf(text, sizeof(text), "%sComHan:0x%p,", text, Config->ComparatorHandler);
        snprintf(text, sizeof(text), "%sPulseDoneHan:0x%p,", text, Config->PulseDoneHandler);
        snprintf(text, sizeof(text), "%s%s,", text, GpioPadToStr(Config->Pad));
        snprintf(text, sizeof(text), "%sEn:%u,", text, Config->on);
    }
    return text;
}

const char* SignalToStr(const PwmSignal_t* const Signal) {
    if(Signal) {
        snprintf(text, sizeof(text), "PER:%u,PULSE:%u", Signal->period, Signal->pulse_diration);
    }
    return text;
}

bool PwmDiagConfig(const PwmConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(PWM, "%s", PwmConfigToStr(Config));
        res = true;
    }
    return res;
}

bool pwm_diag(char* key_word1, char* key_word2) {
    bool res = false;
    uint16_t cnt = 0;
    uint32_t pwm_cnt = pwm_get_cnt();
    LOG_INFO(PWM, "Cnt:%u", pwm_cnt);
    static const table_col_t cols[] = {{4, "No"},   {5, "Tim"}, {7, "CH"},   {10, "Freq"},
                                       {8, "Duty"}, {6, "Pad"}, {10, "name"}};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint16_t num = 0;
    for(num = 0; num <= 10; num++) {
        const PwmConfig_t* Config = PwmGetConfig(num);
        if(Config) {

            PwmHandle_t* Node = PwmGetNode(num);
            if(Node) {
                float duty_cycle = 0.0;
                char temp_str[120];
                Pad_t Pad = {0};
                float frequency_hz = 0.0;
                res = pwm_duty_get(num, &duty_cycle);
                res = pwm_frequency_get(num, &frequency_hz);
                res = pwm_pad_get(num, &Pad);
                strcpy(temp_str, TSEP);
                snprintf(temp_str, sizeof(temp_str), "%s %02u " TSEP, temp_str, num);
                snprintf(temp_str, sizeof(temp_str), "%s T%02u " TSEP, temp_str, Node->timer_num);
                snprintf(temp_str, sizeof(temp_str), "%s CH_%02u " TSEP, temp_str, Node->timer_channel);
                snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, DoubleToStr(frequency_hz));
                snprintf(temp_str, sizeof(temp_str), "%s D%5.2f " TSEP, temp_str, duty_cycle);
                snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, GpioPadToStr(Pad));
                snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, Config->name);
                res = is_contain(temp_str, key_word1, key_word2);
                if(res) {
                    cli_printf("%s" CRLF, temp_str);
                    cnt++;
                }
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
