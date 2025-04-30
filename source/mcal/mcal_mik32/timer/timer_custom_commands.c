#include "timer_commands.h"

#include <inttypes.h>

#include "clock.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "sys_config.h"
#include "time_mcal.h"
#include "timer_mcal.h"
#include "writer_config.h"

#if 0

static bool diag_page_timer_compare(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"}, {10, "name"}, {12, "ARR"}, {12, "PSC"}, {12, "CCR1"}, {12, "CCR2"}, {12, "CCR3"}, {12, "CCR4"},
    };

    uint8_t timer_num = 0;
    // float period_max = 0.0f;
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));

    char name[20] = "";
    for(timer_num = 1; timer_num <= TIMER_COUNT; timer_num++) {
        res = true;

        TIM_TypeDef* TIMx = timer_get_ptr(timer_num);
        strncpy(name, "", sizeof(name));

        const TimerConfig_t* TimerConfNode = TimerGetConfigNode(timer_num);
        if(TimerConfNode) {
            strncpy(name, TimerConfNode->name, sizeof(name));
        }
        cli_printf(TSEP);

        cli_printf(" %02u  " TSEP, timer_num);
        cli_printf(" %8s " TSEP, name);
        cli_printf(" %10u " TSEP, TIMx->ARR);
        cli_printf(" %10u " TSEP, TIMx->PSC);
        cli_printf(" %10u " TSEP, TIMx->CCR1);
        cli_printf(" %10u " TSEP, TIMx->CCR2);
        cli_printf(" %10u " TSEP, TIMx->CCR3);
        cli_printf(" %10u " TSEP, TIMx->CCR4);
        cli_printf(CRLF);
    }
    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    return res;
}

static bool diag_page_timer_ll(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"},  {12, "BusClk"},   {10, "name"},   {6, "AuRel"}, {8, "tickUs"},
        {10, "Int"}, {12, "PeriodMs"}, {13, "freqHz"}, {12, "ARR"},  {12, "PSC"},
    };

    uint8_t timer_num = 0;
    // float period_max = 0.0f;
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    double fck = 0.0;
    double t_psc = 0.0;
    double tf = 0.0;
    double frequency = 0;
    uint32_t period = 0;
    uint16_t prescaler = 0;
    char name[20] = "";
    for(timer_num = 1; timer_num <= TIMER_COUNT; timer_num++) {
        res = true;

        TIM_TypeDef* TIMx = timer_get_ptr(timer_num);
        strncpy(name, "", sizeof(name));
        period = timer_get_period32(timer_num);
        TimerHandle_t* TimerNode = TimerGetNode(timer_num);
        const TimerConfig_t* TimerConfNode = TimerGetConfigNode(timer_num);
        if(TimerConfNode) {
            strncpy(name, TimerConfNode->name, sizeof(name));
        }
        cli_printf(TSEP);

        prescaler = timer_get_prescaler(timer_num);
        fck = (double)timer_get_bus_clock(timer_num);
        tf = 1.0 / fck;
        t_psc = tf * ((double)prescaler);
        frequency = timer_get_freq(timer_num);

        cli_printf(" %02u  " TSEP, timer_num);
        cli_printf(" %10.0f " TSEP, fck);
        cli_printf(" %8s " TSEP, name);
        cli_printf(" %4s " TSEP, OnOff2Str(timer_get_auto_reload(timer_num)));
        cli_printf(" %5u  " TSEP, SEC_2_USEC(t_psc));
        if(TimerNode) {
            cli_printf(" %8u " TSEP, TimerNode->int_cnt);
        } else {
            cli_printf(" %8u " TSEP, 0);
        }

        uint32_t period_ms = SEC_2_MSEC(t_psc * ((double)period));
        cli_printf(" %10u " TSEP, period_ms);
        cli_printf(" %10.2f " TSEP, frequency);

        cli_printf(" %10u " TSEP, TIMx->ARR);
        cli_printf(" %10u " TSEP, TIMx->PSC);
        cli_printf(CRLF);
    }
    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    return res;
}

static bool diag_page_tim(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"}, {5, "En"},  {7, "psc"},  {12, "period"},
        {6, "dir"}, {6, "bus"}, {8, "fill"}, {11, "period,s"},

    };
    uint8_t status = 0;
    uint32_t cnt = 0;
    uint8_t timer_num = 0;
    uint16_t prescaler = 0;
    uint32_t period = 0;
    double period_real_s = 0.0f;
    // float period_max = 0.0f;
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));

    double fill = 0.0;
    for(timer_num = 1; timer_num <= TIMER_COUNT; timer_num++) {
        res = true;
        cli_printf(TSEP);
        status = timer_get_status(timer_num);

        prescaler = timer_get_prescaler(timer_num);
        period = timer_get_period32(timer_num);

        fill = (double)100 * cnt / period;

        cli_printf(" %02u  " TSEP, timer_num);
        cli_printf(" %3s " TSEP, OnOff2Str(status));
        cli_printf(" %5u " TSEP, prescaler);
        cli_printf(" 0x%08x " TSEP, period);
        TimDir_t dir = timer_get_dir(timer_num);
        cli_printf(" %04s " TSEP, TimDir2Str(dir));
        cli_printf(" %04s " TSEP, BusClock2Str(timer_get_bus_clock(timer_num)));
        cli_printf(" %6.2f " TSEP, fill);
        period_real_s = timer_get_period_s(timer_num);
        cli_printf("  %7.2f  " TSEP, period_real_s);

        cli_printf(CRLF);
    }
    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    return res;
}

bool timer_diag_compare_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = diag_page_timer_compare();
    } else {
        LOG_ERROR(TIMER, "Usage: tdc");
    }

    return res;
}

bool timer_diag_ll_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = diag_page_timer_ll();
    } else {
        LOG_ERROR(TIMER, "Usage: tdl");
    }

    return res;
}

bool timer_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = diag_page_tim();
    } else {
        LOG_ERROR(TIMER, "Usage: td");
    }

    return res;
}

bool timer_set_prescaler_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t timer_base_id = 0;
    uint8_t timer_inst = 0;
    uint8_t prescaler = 0;
    if(3 == argc) {
        res = true;
        if(res) {
            res = try_str2uint8(argv[0], &timer_base_id);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract timer_base_id %s", argv[0]);
            }
        }

        if(res) {
            res = try_str2uint8(argv[1], &timer_inst);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract timer_inst %s", argv[1]);
            }
            if(4 <= timer_inst) {
                res = false;
            }
        }

        if(res) {
            res = try_str2uint8(argv[2], &prescaler);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract prescaler %s", argv[2]);
            }
        }
    } else {
        LOG_ERROR(TIMER, "Usage: tsp base inst prescaler");
    }

    if(res) {
    }

    return res;
}

bool timer_set_laod_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t timer_base_id = 0;
    uint8_t timer_inst = 0;
    uint32_t load = 0;
    if(3 == argc) {
        res = true;
        if(res) {
            res = try_str2uint8(argv[0], &timer_base_id);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract timer_base_id %s", argv[0]);
            }
        }

        if(res) {
            res = try_str2uint8(argv[1], &timer_inst);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract timer_inst %s", argv[1]);
            }
            if(4 <= timer_inst) {
                res = false;
            }
        }

        if(res) {
            res = try_str2uint32(argv[2], &load);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract load %s", argv[2]);
            }
        }
    } else {
        LOG_ERROR(TIMER, "Usage: tsl base inst load");
    }

    if(res) {
    }

    return res;
}

bool timer_set_period_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t timer_index = 0;
    uint32_t pesiod_ms = 1000;
    if(2 == argc) {
        res = true;
        if(res) {
            res = try_str2uint8(argv[0], &timer_index);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract index %s", argv[0]);
            }
            if(timer_get_cnt() <= timer_index) {
                res = false;
            }
        }

        if(res) {
            res = try_str2uint32(argv[1], &pesiod_ms);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract pesiod_ms %s", argv[1]);
            }
        }
    } else {
        LOG_ERROR(TIMER, "Usage: tspr timer_index pesiod_ms");
        res = false;
    }
    if(res) {
        uint32_t prescaler = 0;
        uint32_t load = 0;
        res = timer_calc_registers(pesiod_ms, 0, 0, SYS_FREQ, prescaler, &load, 0xFFFFFFFF);
        if(res) {
        }
    }
    return res;
}
#endif
