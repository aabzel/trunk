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
#include "timer_diag.h"
#include "writer_config.h"

const char* PwmPolarityToStr(const PwmPolarity_t polarity) {
    const char* name = "?";
    switch(polarity) {
    case PWM_POLARITY_LOW:
        name = "Norm";
        break;
    case PWM_POLARITY_HIGH:
        name = "Inve";
        break;
    default:
        break;
    }
    return name;
}

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
        snprintf(text, sizeof(text), "%sOut:%s", text, TimChanToStr(Config->TimChan));
        snprintf(text, sizeof(text), "%sPhaseCtrl:%s", text, TimChanToStr(Config->PhaseComparator));
        snprintf(text, sizeof(text), "%sPHA:%f s,", text, Config->phase_s);
        snprintf(text, sizeof(text), "%sDuty:%f %%,", text, Config->duty);
        snprintf(text, sizeof(text), "%sFreq:%f Hz,", text, Config->frequency_hz);
        snprintf(text, sizeof(text), "%sName:%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sComHan:%p,", text, Config->ComparatorHandler);
        snprintf(text, sizeof(text), "%sPerDoneHan:%p,", text, Config->PeriodDoneHandler);
        snprintf(text, sizeof(text), "%s%s,", text, GpioPadToStr(Config->Pad));
        snprintf(text, sizeof(text), "%sPola:%s,", text, PwmPolarityToStr(Config->polarity));
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
    static const table_col_t cols[] = {{4, "No"},   {10, "TimCh"}, {10, "Freq,Hz"},  {10, "Period,s"}, {7, "Duty"},
                                       {6, "Pola"}, {6, "Pad"},    {10, "MasTimCh"}, {8, "PhaseUs"},   {10, "name"}};

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint16_t num = 0;
    for(num = 0; num <= 10; num++) {
        const PwmConfig_t* Config = PwmGetConfig(num);
        if(Config) {
            PwmHandle_t* Node = PwmGetNode(num);
            if(Node) {
                float duty_cycle = 0.0f;
                float frequency_hz = 0.0f;
                float period_s = 0.0f;
                char temp_str[120] = {0};
                Pad_t Pad = {0};
                uint32_t phase_us = 0;
                res = pwm_duty_get(num, &duty_cycle);
                res = pwm_frequency_get(num, &frequency_hz);
                res = pwm_period_get(num, &period_s);
                res = pwm_pad_get(num, &Pad);
                PwmPolarity_t polarity = PWM_POLARITY_UNDEF;
                res = pwm_polarity_get(num, &polarity);
                res = pwm_phase_get(num, &phase_us);

                strcpy(temp_str, TSEP);
                snprintf(temp_str, sizeof(temp_str), "%s %02u " TSEP, temp_str, num);
                snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, TimChanToStr(Node->TimChan));
                snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, DoubleToStr(frequency_hz));
                snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, DoubleToStr(period_s));
                snprintf(temp_str, sizeof(temp_str), "%s %5.2f " TSEP, temp_str, duty_cycle);
                snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, PwmPolarityToStr(polarity));
                snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, GpioPadToStr(Pad));
                snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, TimChanToStr(Node->PhaseComparator));
                snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, phase_us);
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
