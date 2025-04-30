#include "timer_diag.h"

#include <stdio.h>
#include <string.h>

#include "clock_diag.h"
#include "common_diag.h"
#include "gpio_diag.h"
#include "log.h"
#include "num_to_str.h"
#include "sys_config.h"
#include "table_utils.h"
#include "timer_mcal.h"
#include "writer_config.h"

#if 0
const char* BusClock2Str(uint32_t bus_clock) {
    const char* name = "?";
    return name;
}
#endif

const char* TimerDirToStr(TimerDir_t code) {
    char* name = "?";
    switch((uint32_t)code) {
    case CNT_DIR_UP:
        name = "Up";
        break;
    case CNT_DIR_DOWN:
        name = "Down";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

bool timer_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"}, {5, "bit"},  {10, "period"},   {5, "En"},         {7, "psc"}, {10, "cnt"},     {6, "dir"},
        {6, "bus"}, {8, "fill"}, {11, "period,s"}, {11, "period,ms"}, {8, "Int"}, {12, "UpTimeS"},

    };
    bool status = 0;
    uint32_t cnt = 0;
    uint32_t ok = 0;
    uint8_t num = 0;
    uint32_t prescaler = 0;
    uint8_t bitness = 0;
    uint32_t period = 0;
    double period_real_s = 0.0f;
    // float period_max = 0.0f;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    double fill = 0.0;
    for(num = 0; num <= TIMER_MAX_NUM; num++) {
        res = timer_is_valid(num);
        if(res) {
            TimerHandle_t* Node = TimerGetNode(num);
            if(Node) {
                cli_printf(TSEP);
                bitness = timer_bitness_get(num);
                status = timer_get_status(num);
                cnt = timer_counter_get(num);
                prescaler = timer_prescaler_get(num);
                period = timer_period_get(num);
                fill = (double)100 * cnt / period;
                TimerDir_t dir = timer_dir_get(num);
                period_real_s = timer_period_get_s(num);
                double up_time_s = timer_get_s(num);

                cli_printf(" %02u  " TSEP, num);
                cli_printf(" %02u  " TSEP, bitness);
                cli_printf(" %8u " TSEP, period);
                cli_printf(" %3s " TSEP, OnOffToStr(status));
                cli_printf(" %5u " TSEP, prescaler);
                cli_printf(" %8u " TSEP, cnt);
                cli_printf(" %04s " TSEP, TimerDirToStr(dir));
                cli_printf(" %04s " TSEP, ClockBusToStr(timer_bus_clock_get(num)));
                cli_printf(" %6.2f " TSEP, fill);
                cli_printf("  %7.2f  " TSEP, period_real_s);
                cli_printf("  %7.2f  " TSEP, 1000.0 * period_real_s);
                cli_printf(" %6u " TSEP, Node->overflow);
                cli_printf("  %7.2f  " TSEP, up_time_s);

                cli_printf(CRLF);
                ok++;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    if(ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool timer_diag_ll(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"},   {12, "BusClk"}, {12, "PSC"},      {12, "CNT"},    {9, "tickUs"},
        {6, "AuRel"}, {10, "Int"},    {12, "PeriodMs"}, {13, "freqHz"}, {12, "Period"},
    };

    uint8_t num = 0;
    uint32_t ok = 0;
    // float period_max = 0.0f;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    double fck = 0.0;
    // double t_psc = 0.0;
    // double tick_s = 0.0;
    double frequency_hz = 0.0;
    uint32_t period = 0;
    uint32_t prescaler = 0;

    char name[20] = "";
    for(num = 0; num <= TIMER_MAX_NUM; num++) {
        res = true;
        fck = (double)timer_bus_clock_get(num);
        if(0.0 < fck) {
            strncpy(name, "", sizeof(name));
            period = timer_period_get(num);
            //  tick_s = timer_get_tick_s(num);

            uint32_t period_ms = timer_period_get_ms(num);
            uint32_t tick_us = timer_get_tick_us(num);
            TimerHandle_t* Node = TimerGetNode(num);
            const TimerConfig_t* Config = TimerGetConfig(num);
            if(Config) {
                strncpy(name, Config->name, sizeof(name));
            }
            cli_printf(TSEP);

            prescaler = timer_prescaler_get(num);
            res = timer_frequency_get(num, &frequency_hz);
            uint32_t counter = timer_counter_get(num);

            cli_printf(" %02u  " TSEP, num);
            cli_printf(" %10.0f " TSEP, fck);
            cli_printf(" %10u " TSEP, prescaler);
            cli_printf(" %10u " TSEP, counter);
            cli_printf(" %7u " TSEP, tick_us);
            cli_printf(" %4s " TSEP, OnOffToStr(timer_get_auto_reload(num)));
            if(Node) {
                cli_printf(" %8u " TSEP, Node->overflow);
            } else {
                cli_printf(" %8u " TSEP, 0);
            }

            cli_printf(" %10u " TSEP, period_ms);
            cli_printf(" %11.2f " TSEP, frequency_hz);
            cli_printf(" %10u " TSEP, period);

            cli_printf(CRLF);
            ok++;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    if(ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

const char* TimerConfigToStr(const TimerConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        double period = TimerConfigToPeriodSec(Config);
        snprintf(text, sizeof(text), "%sCntTime:%u ns,", text, Config->cnt_period_ns);
        snprintf(text, sizeof(text), "%sEn:%u,", text, Config->on_off);
        snprintf(text, sizeof(text), "%sIntEn:%u,", text, Config->interrupt_on);
        snprintf(text, sizeof(text), "%sPeriod:%s s,", text, DoubleToStr(period));
        snprintf(text, sizeof(text), "%sDirr:%u,", text, Config->dir);
    }
    return text;
}

bool timer_diag_compare_complimentary(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"}, {12, "Period"}, {12, "PSC"}, {12, "CCR1"}, {12, "CCR2"}, {12, "CCR3"}, {12, "CCR4"},
    };

    uint8_t num = 0;
    // float period_max = 0.0f;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    char name[20] = "";
    for(num = 0; num <= TIMER_MAX_NUM; num++) {
        res = true;
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
            strncpy(name, "", sizeof(name));
            cli_printf(TSEP);
            cli_printf(" %02u  " TSEP, num);

            uint32_t period = timer_period_get(num);
            cli_printf(" %10u " TSEP, period);

            uint32_t prescaler = timer_prescaler_get(num);
            cli_printf(" %10u " TSEP, prescaler);

            int32_t channel = 0;
            uint32_t channel_value = 0;
            for(channel = 1; channel <= 5; channel++) {
                channel_value = timer_ccc_val_get(num, (TimerCapComChannel_t)channel);
                cli_printf(" %10u " TSEP, channel_value);
            }

            cli_printf(CRLF);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool timer_diag_compare(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"}, {12, "Period"}, {12, "PSC"}, {12, "CCR1"}, {12, "CCR2"}, {12, "CCR3"}, {12, "CCR4"},
    };

    uint8_t num = 0;
    // float period_max = 0.0f;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    char name[200] = "";
    for(num = 0; num <= TIMER_MAX_NUM; num++) {
        res = true;
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
            cli_printf(TSEP);
            cli_printf(" %02u  " TSEP, num);

            uint32_t period = timer_period_get(num);
            cli_printf(" %10u " TSEP, period);

            uint32_t prescaler = timer_prescaler_get(num);
            cli_printf(" %10u " TSEP, prescaler);

            int32_t channel = 0;
            uint32_t channel_value = 0;
            for(channel = 1; channel <= 4; channel++) {
                strncpy(name, "", sizeof(name));
                channel_value = timer_cc_val_get(num, (TimerCapComChannel_t)channel);
                cli_printf(" %10u " TSEP, channel_value);
            }

            cli_printf(CRLF);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool timer_channel_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"}, {5, "Tim"}, {5, "Cha"}, {8, "Freq"}, {10, "compare"}, {7, "Duty"}, {6, "Pad"},
    };

    uint8_t cnt = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    char name[200] = "";
    uint8_t num = 0;
    for(num = 0; num <= TIMER_MAX_NUM; num++) {
        res = false;
        int32_t channel = 0;
        for(channel = 1; channel <= 4; channel++) {
            strcpy(name, TSEP);
            uint32_t channel_value = 0;
            double duty = 0.0;
            double frequency_hz = 0.0;
            res = timer_frequency_get(num, &frequency_hz);
            if(res) {
                res = timer_duty_get(num, channel, &duty);
                channel_value = timer_cc_val_get(num, (TimerCapComChannel_t)channel);
                snprintf(name, sizeof(name), "%s %3u " TSEP, name, cnt);
                snprintf(name, sizeof(name), "%s %3u " TSEP, name, num);
                snprintf(name, sizeof(name), "%s %3u " TSEP, name, channel);
                snprintf(name, sizeof(name), "%s %6s " TSEP, name, DoubleToStr(frequency_hz));
                snprintf(name, sizeof(name), "%s %8u " TSEP, name, channel_value);
                snprintf(name, sizeof(name), "%s %5.2f " TSEP, name, duty);

                Pad_t Pad = {0};
                res = timer_out_channel_pad_get(num, channel, &Pad);
                if(res) {
                    snprintf(name, sizeof(name), "%s %4s " TSEP, name, GpioPadToStr(Pad));
                }
                cli_printf("%s" CRLF, name);
                cnt++;
                res = true;
            }
        }
        if(res) {
            table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        }
    }
    return res;
}
