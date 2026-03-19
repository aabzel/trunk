#include "timer_diag.h"

#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "debugger.h"
#include "float_diag.h"
#include "gpio_diag.h"
#include "clock_diag.h"
#include "log.h"
#include "microcontroller_const.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "timer_mcal.h"
#include "writer_config.h"

const char* BusClockToStr(uint32_t bus_clock) {
    const char* name = "?";
    return name;
}

const char* TimerDirToStr(const TimerDir_t code) {
    char* name = "?";
    switch(code) {
    case TIMER_CNT_DIR_UP:
        name = "Up";
        break;
    case TIMER_CNT_DIR_DOWN:
        name = "Down";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

bool timer_diag_interrupt(void){
    bool res = false;
    uint32_t ok = 0;
    static const table_col_t cols[] = {
        {5, "Num"},
        {5, "En"},
        {10, "cnt"},
        {10, "period"},
        {12, "UpTimeS"},
        {8, "Comp"},
        {8, "Int"},
        {8, "pulse_fin"},

    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint8_t num = 0;
    for(num = 0; num <= TIMER_MAX_NUM; num++) {
        res = timer_is_valid(num);
        if(res) {
            TimerHandle_t* Node = TimerGetNode(num);
            if(Node) {
                bool status = timer_get_status(num);
                uint32_t cnt = timer_counter_get(num);
                uint32_t period = timer_period_get(num);
                float up_time_s = timer_get_s(num);

                cli_printf(TSEP);
                cli_printf(" %02u  " TSEP, num);
                cli_printf(" %3s " TSEP, OnOffToStr(status));
                cli_printf(" %8u " TSEP, cnt);
                cli_printf(" %8u " TSEP, period);
                cli_printf(" %8.1f " TSEP, up_time_s);
                cli_printf(" %6u " TSEP, Node->comparator_cnt);
                cli_printf(" %6u " TSEP, Node->int_cnt);
                cli_printf(" %6u " TSEP, Node->pulse_fin_cnt);
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


bool timer_diag(void) {
    bool res = false;
    uint32_t ok = 0;
    static const table_col_t cols[] = {
        {5, "Num"},
        {12, "cnt"},
        {5, "En"},
        {8, "busName"},
        {10, "busFreq"},
        {5, "bit"},      
        {12, "period"},  
        {7, "psc"},
        {6, "dir"},
        {9, "fill"},
        {9, "period,s"},
        {9, "UpTimeS"},
        {8, "Int"}, 
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t num = 0;
    for(num = 0; num <= TIMER_MAX_NUM; num++) {
        res = timer_is_valid(num);
        if(res) {
            TimerHandle_t* Node = TimerGetNode(num);
            if(Node) {
                char temp[120]={0};
                memset(temp,0,sizeof(temp));
                strcpy(temp, TSEP);
              
                uint8_t  bitness = timer_bitness_get(num);
                bool status = timer_get_status(num);
                uint32_t  counter = timer_counter_get(num);
                uint32_t prescaler = timer_prescaler_get(num);
                uint32_t period = timer_period_get(num);
                float fill = (float)100 * counter / period;
                TimerDir_t dir = timer_dir_get(num);
                float period_real_s = timer_period_get_s(num);
                float up_time_s = timer_get_s(num);
                ClockBus_t clock_bus_name=timer_clock_bus_name_get(num);

                snprintf(temp, sizeof(temp),"%s %02u  " TSEP,temp, num);
                snprintf(temp, sizeof(temp),"%s %10u " TSEP,temp, counter);
                snprintf(temp, sizeof(temp),"%s %3s " TSEP,temp, OnOffToStr(status));
                snprintf(temp, sizeof(temp),"%s %6s " TSEP,temp, ClockBusToStr(clock_bus_name));
                snprintf(temp, sizeof(temp),"%s %8u " TSEP,temp, timer_bus_clock_get(num));
                snprintf(temp, sizeof(temp),"%s %02u  " TSEP,temp, bitness);
                snprintf(temp, sizeof(temp),"%s %10u " TSEP,temp, period);
                snprintf(temp, sizeof(temp),"%s %5u " TSEP,temp, prescaler);
                snprintf(temp, sizeof(temp),"%s %4s " TSEP,temp, TimerDirToStr(dir));
                snprintf(temp, sizeof(temp),"%s %7s " TSEP,temp, FloatToStr( fill,3));
                snprintf(temp, sizeof(temp),"%s %7s " TSEP,temp, FloatToStr(period_real_s,2));
                snprintf(temp, sizeof(temp),"%s %7s " TSEP,temp, FloatToStr(up_time_s,1));
                snprintf(temp, sizeof(temp),"%s %6u " TSEP,temp, Node->int_cnt);
                cli_printf("%s"CRLF, temp);
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
        {5, "Num"},    {12, "BusClk"},   {12, "PSC"},    {12, "CNT"},    {6, "AuRel"},
        {9, "tickUs"}, {12, "PeriodMs"}, {13, "freqHz"}, {12, "Period"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t num = 0;
    uint32_t ok = 0;
    // float period_max = 0.0f;
    // float t_psc = 0.0;
    // float tick_s = 0.0;

    for(num = 0; num <= TIMER_MAX_NUM; num++) {
        res = true;
        float fck = 0.0;
        fck = (float)timer_bus_clock_get(num);
        if(0.0 < fck) {
            char temp[120] = "";
            strncpy(temp, "", sizeof(temp));
            
            float frequency_hz = 0.0;
            uint32_t prescaler = 0;
            uint32_t period = 0;
            period = timer_period_get(num);
            //  tick_s = timer_get_tick_s(num);

            uint32_t period_ms = timer_period_get_ms(num);
            uint32_t tick_us = timer_get_tick_us(num);
            TimerHandle_t* Node = TimerGetNode(num);
            strncpy(temp, Node->name, sizeof(temp));
            snprintf(temp,sizeof(temp),"%s",TSEP);

            prescaler = timer_prescaler_get(num);
            res = timer_frequency_get(num, &frequency_hz);
            uint32_t counter = timer_counter_get(num);

            snprintf(temp,sizeof(temp),"%s %02u  " TSEP,temp, num);
            snprintf(temp,sizeof(temp),"%s %10.0f " TSEP,temp, fck);
            snprintf(temp,sizeof(temp),"%s %10u " TSEP,temp, prescaler);
            snprintf(temp,sizeof(temp),"%s %10u " TSEP,temp, counter);
            snprintf(temp,sizeof(temp),"%s %4s " TSEP,temp, OnOffToStr(timer_get_auto_reload(num)));
            snprintf(temp,sizeof(temp),"%s %7u " TSEP,temp, tick_us);

            snprintf(temp,sizeof(temp),"%s %10u " TSEP,temp, period_ms);
            snprintf(temp,sizeof(temp),"%s %11.2f " TSEP,temp, frequency_hz);
            snprintf(temp,sizeof(temp),"%s %10u " TSEP,temp, period);

            cli_printf("%s" CRLF,temp);
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
    static char temp[150] = "?";
    if(Config) {
        strcpy(temp, "");
        snprintf(temp, sizeof(temp), "%sTIM%u,", temp, Config->num);
        snprintf(temp, sizeof(temp), "%sPeriod:%f s,", temp, Config->period_s);
        snprintf(temp, sizeof(temp), "%sCntTime:%u ns,", temp, Config->cnt_period_ns);
        snprintf(temp, sizeof(temp), "%sEn:%u,", temp, Config->on_off);
        snprintf(temp, sizeof(temp), "%sIntEn:%u,", temp, Config->interrupt_on);
        snprintf(temp, sizeof(temp), "%sDir:%s,", temp, TimerDirToStr(Config->dir));
    }
    return temp;
}

bool timer_diag_compare_complimentary(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"}, {12, "Period"}, {12, "PSC"}, {12, "CCR1"}, {12, "CCR2"}, {12, "CCR3"}, {12, "CCR4"},
    };

    uint8_t num = 0;
    // float period_max = 0.0f;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    char temp[20] = "";
    for(num = 0; num <= TIMER_MAX_NUM; num++) {
        res = true;
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
            strncpy(temp, "", sizeof(temp));
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

    char temp[200] = "";
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
                strncpy(temp, "", sizeof(temp));
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

    char temp[200] = "";
    uint8_t num = 0;
    for(num = 0; num <= TIMER_MAX_NUM; num++) {
        res = false;
        int32_t channel = 0;
        for(channel = 1; channel <= 4; channel++) {
            strcpy(temp, TSEP);
            uint32_t channel_value = 0;
            float duty = 0.0;
            float frequency_hz = 0.0;
            res = timer_frequency_get(num, &frequency_hz);
            if(res) {
                res = timer_duty_get(num, channel, &duty);
                channel_value = timer_cc_val_get(num, (TimerCapComChannel_t)channel);
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, cnt);
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, num);
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, channel);
                snprintf(temp, sizeof(temp), "%s %6s " TSEP, temp, DoubleToStr(frequency_hz));
                snprintf(temp, sizeof(temp), "%s %8u " TSEP, temp, channel_value);
                snprintf(temp, sizeof(temp), "%s %5.2f " TSEP, temp, duty);

                Pad_t Pad = {0};
                res = timer_out_channel_pad_get(num, channel, &Pad);
                if(res) {
                    snprintf(temp, sizeof(temp), "%s %4s " TSEP, temp, GpioPadToStr(Pad));
                }
                cli_printf("%s" CRLF, temp);
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

bool timer_raw_reg_diag(uint8_t i) {
    bool res = false;
    TimerInfo_t* Info = TimerGetInfo(i);
    if(Info) {
        uint32_t cnt = time_register_cnt();
        res = debug_raw_reg_diag(TIMER, Info->TIMx, TimerRegs, cnt);
    }
    return res;
}
