#include "scheduler_diag.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "common_diag.h"

#include "log.h"
#include "num_to_str.h"
#include "scheduler_mcal.h"
#include "str_utils.h"
#include "super_cycle.h"
#include "table_utils.h"
#include "time_mcal.h"
#include "writer.h"
#ifdef HAS_FLOAT_UTILS
#include "float_utils.h"
#endif
#ifdef HAS_LIMITER_DIAG
#include "limiter_diag.h"
#endif

const char* TaskNumToName(const uint8_t num, const uint32_t task_num) {
    const char* name = "?";
    SchedulerHandle_t* Node = SchedulerGetNode(num);
    if(Node) {
        if(task_num < Node->task_array_cnt) {
            name = Node->TaskArray[task_num].name;
        }
    }
    return name;
}

const char* SchedulerNodeToStr(const SchedulerHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sN:%u", text, Node->num);
        snprintf(text, sizeof(text), "%sCnt:%u", text, Node->task_array_cnt);
        snprintf(text, sizeof(text), "%sTaskArr:0x%p", text, Node->TaskArray);
    }
    return text;
}

const char* SchedulerTaskToStr(const SchedulerTaskHandle_t* const Task) {
    strcpy(text, "");
    if(Task) {
        snprintf(text, sizeof(text), "%sName:[%s]", text, Task->name);
        snprintf(text, sizeof(text), "%sEn:%u", text, Task->on);
        snprintf(text, sizeof(text), "%sPer:%llu us", text, Task->period_us);
#ifdef HAS_LIMITER_DIAG
        snprintf(text, sizeof(text), "%sLim:%s", text, LimiterToStr(&(Task->limiter)));
#endif
    }
    return text;
}

bool scheduler_diag_run(const uint8_t num, char* key_word1, char* key_word2) {
    bool res = false;
    uint64_t up_time_us = time_get_us();

    uint32_t up_time_ms = time_get_ms32();
    int32_t cnt = 0;
    uint64_t all_scheduler_us = 0;
    all_scheduler_us = scheduler_all_run_time_us(num);
    // super_cycle_diag();

    LOG_INFO(SCHEDULER, "UpTime %u us", up_time_us);

    uint64_t total_run_time_us = super_cycle_run_time_us(num);
    uint32_t t_cnt = scheduler_get_task_cnt(num);
    LOG_INFO(SCHEDULER, "LoopTotalRunTime %llu us" CRLF, total_run_time_us);
    LOG_INFO(SCHEDULER, "scheduler cnt %u", t_cnt);
    LOG_INFO(SCHEDULER, "total run time  %u us", total_run_time_us);
    LOG_INFO(SCHEDULER, "up_time  %u ms", up_time_ms);

    static const table_col_t cols[] = {
        {4, "Num"},     {4, "id"},    {17, "SchedulerName"}, {5, "On"},    {8, "Calls"},
        {8, "Calls/s"}, {11, "Rmin"}, {11, "Rcur"},          {11, "Rmax"}, {9, "CPU[%]"},
    };
    float cpu_use = 0.0;
    (void)cpu_use;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    char lgLine[150] = {0};
    int32_t t = 0;
    for(t = 0; t < t_cnt; t++) {
        SchedulerTaskHandle_t* Task = SchedulerNunToTaskNode(num, t);
        Limiter_t* Limiter = &(Task->limiter);
        cpu_use = (((float)Limiter->run_time_total_us) * 100.0) / ((float)all_scheduler_us);
        strcpy(lgLine, TSEP);
        snprintf(lgLine, sizeof(lgLine), "%s %2u " T_SEP, lgLine, t);
        snprintf(lgLine, sizeof(lgLine), "%s %15s " T_SEP, lgLine, Task->name);
        snprintf(lgLine, sizeof(lgLine), "%s %3s " T_SEP, lgLine, OnOffToStr(Limiter->on_off));
        snprintf(lgLine, sizeof(lgLine), "%s %6u " T_SEP, lgLine, (uint32_t)Limiter->call_cnt);
        if(up_time_ms) {
            snprintf(lgLine, sizeof(lgLine), "%s %6u " T_SEP, lgLine,
                     (uint32_t)((Limiter->call_cnt * 1000) / up_time_ms));
        }
        if(0 != Limiter->call_cnt) {
            snprintf(lgLine, sizeof(lgLine), "%s %9s " T_SEP, lgLine, UsecToStr(Limiter->duration_us.min));
            snprintf(lgLine, sizeof(lgLine), "%s %9s " T_SEP, lgLine, UsecToStr(Limiter->duration_us.cur));
            snprintf(lgLine, sizeof(lgLine), "%s %9s " T_SEP, lgLine, UsecToStr(Limiter->duration_us.max));
        }
#ifdef HAS_FLOAT_UTILS
        snprintf(lgLine, sizeof(lgLine), "%s %7s " T_SEP, lgLine, FloatToStr(cpu_use, 3));
#endif
        if(is_contain(lgLine, key_word1, key_word2)) {
            cli_printf(TSEP " %2u ", cnt);
            cli_printf("%s" CRLF, lgLine);
            // cli_printf(CRLF);
            cnt++;
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    LOG_INFO(SCHEDULER, "Rmax-MaxSchedulerContinuousRunTime");

    return res;
}

bool scheduler_diag(const uint8_t num, char* key_word1, char* key_word2) {
    bool res = false;

    uint32_t up_time_ms = time_get_ms32();
    int32_t t = 0;
    int32_t cnt = 0;
    uint64_t all_scheduler_us = 0;
    all_scheduler_us = scheduler_all_run_time_us(num);

    LOG_INFO(SCHEDULER, "up_time:%u ms", up_time_ms);
    super_cycle_diag();

    // uint64_t total_run_time_us = super_cycle_run_time_us();
    // LOG_INFO(SCHEDULER, "TotalRunTime:%f s", usec_to_sec(total_run_time_us));

    uint32_t t_cnt = scheduler_get_task_cnt(num);
    LOG_INFO(SCHEDULER, "scheduler cnt %u", t_cnt);

    static const table_col_t cols[] = {
        {4, "Num"},     {4, "id"},   {17, "SchedulerName"}, {5, "On"},     {8, "Calls"},
        {8, "Calls/s"}, {9, "Idle"}, {8, "Idle/s"},         {9, "CPU[%]"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    char lgLine[150] = {0};
    for(t = 0; t < t_cnt; t++) {
        SchedulerTaskHandle_t* Task = SchedulerNunToTaskNode(num, t);
        if(Task) {
            Limiter_t* Limiter = &(Task->limiter);
            if(Limiter) {
                if(Limiter->function) {
                    float cpu_use = 0.0;
                    cpu_use = (((float)Limiter->run_time_total_us) * 100.0) / ((float)all_scheduler_us);
                    strcpy(lgLine, TSEP);
                    snprintf(lgLine, sizeof(lgLine), "%s %2u " T_SEP, lgLine, t);
                    snprintf(lgLine, sizeof(lgLine), "%s %15s " T_SEP, lgLine, Task->name);
                    snprintf(lgLine, sizeof(lgLine), "%s %3s " T_SEP, lgLine, OnOffToStr(Limiter->on_off));
                    snprintf(lgLine, sizeof(lgLine), "%s %6u " T_SEP, lgLine, (uint32_t)Limiter->call_cnt);
                    if(up_time_ms) {
                        snprintf(lgLine, sizeof(lgLine), "%s %6u " T_SEP, lgLine,
                                 (uint32_t)((Limiter->call_cnt * 1000) / up_time_ms));
                    }
                    snprintf(lgLine, sizeof(lgLine), "%s %7u " T_SEP, lgLine, (uint32_t)Limiter->idle_cnt);
                    if(up_time_ms) {
                        snprintf(lgLine, sizeof(lgLine), "%s %6u " T_SEP, lgLine,
                                 (uint32_t)((Limiter->idle_cnt * 1000) / up_time_ms));
                    }
#ifdef HAS_FLOAT_UTILS
                    snprintf(lgLine, sizeof(lgLine), "%s %7s " T_SEP, lgLine, FloatToStr(cpu_use, 3));
#endif

                    res = is_contain(lgLine, key_word1, key_word2);
                    if(res) {
                        cli_printf(TSEP " %2u ", cnt);
                        cli_printf("%s" CRLF, lgLine);
                        cnt++;
                        res = true;
                    }
                }
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool scheduler_diag_period(const uint8_t num, char* key_word1, char* key_word2) {
    bool res = false;
    uint32_t t_cnt = scheduler_get_task_cnt(num);
    super_cycle_diag();
    int32_t t = 0;
    uint64_t total_run_time_us = super_cycle_run_time_us(num);
    LOG_INFO(SCHEDULER, "SchedulerCnt %u,UpTime:%f s" CRLF, t_cnt, USEC_2_SEC(total_run_time_us));
    uint64_t all_scheduler_us = 0;
    all_scheduler_us = scheduler_all_run_time_us(num);
    float all_percentages = 0.0;

    static const table_col_t cols[] = {{4, "id"},      {17, "SchedulerName"}, {5, "On"},    {8, "Calls"},
                                       {8, "Calls/s"}, {9, "CPU[%]"},         {11, "Tmin"}, {11, "Tcur"},
                                       {11, "Tmax"},   {11, "Tavg"},          {11, "Tset"}};
    float cpu_use = 0.0;
    (void)cpu_use;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    char lgLine[150];
    for(t = 0; t < t_cnt; t++) {
        SchedulerTaskHandle_t* Task = SchedulerNunToTaskNode(num, t);
        if(Task) {
            Limiter_t* Limiter = &(Task->limiter);
            if(Limiter) {

                cpu_use = (((float)Limiter->run_time_total_us) * 100.0) / ((float)all_scheduler_us);
                all_percentages += cpu_use;
                strcpy(lgLine, TSEP);
                snprintf(lgLine, sizeof(lgLine), "%s %2u " T_SEP, lgLine, t);
                snprintf(lgLine, sizeof(lgLine), "%s %15s " T_SEP, lgLine, Task->name);
                snprintf(lgLine, sizeof(lgLine), "%s %3s " T_SEP, lgLine, OnOffToStr(Limiter->on_off));
                snprintf(lgLine, sizeof(lgLine), "%s %6s " T_SEP, lgLine, uint32ToStr(Limiter->call_cnt));
                if(total_run_time_us) {
                    uint32_t call_per_s = (uint32_t)(((float)Limiter->call_cnt) / USEC_2_SEC(total_run_time_us));
                    snprintf(lgLine, sizeof(lgLine), "%s %6u " T_SEP, lgLine, call_per_s);
                }
                snprintf(lgLine, sizeof(lgLine), "%s %7.3f " T_SEP, lgLine, cpu_use);

                snprintf(lgLine, sizeof(lgLine), "%s %9s " T_SEP, lgLine, UsecToStr(Limiter->start_period_us.min));
                snprintf(lgLine, sizeof(lgLine), "%s %9s " T_SEP, lgLine, UsecToStr(Limiter->start_period_us.cur));
                snprintf(lgLine, sizeof(lgLine), "%s %9s " T_SEP, lgLine, UsecToStr(Limiter->start_period_us.max));
                uint32_t avr_per_us = 0;
                if(0 != Limiter->call_cnt) {
                    avr_per_us = total_run_time_us / Limiter->call_cnt;
                }
                snprintf(lgLine, sizeof(lgLine), "%s %9s " T_SEP, lgLine, UsecToStr(avr_per_us));
                snprintf(lgLine, sizeof(lgLine), "%s %9s " T_SEP, lgLine, UsecToStr(Task->period_us));

                if(is_contain(lgLine, key_word1, key_word2)) {
                    cli_printf("%s" CRLF, lgLine);
                    res = true;
                }
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
#ifdef HAS_FLOAT_UTILS
    res = is_float_equal_absolute(100.0, all_percentages, 2.0);
    if(false == res) {
        LOG_ERROR(SCHEDULER, "ExeError %f %%", all_percentages);
    }
#endif
    uint64_t scheduler_time_us = total_run_time_us - all_scheduler_us;

    LOG_INFO(SCHEDULER, "TotalSupLpRunTime: %llu us", total_run_time_us);
    LOG_INFO(SCHEDULER, "AllSchedulersDuration:%llu us, %f %%", all_scheduler_us, all_percentages);
    LOG_INFO(SCHEDULER, "SchedulerDuration: %llu us", scheduler_time_us);

    cpu_use = (((float)scheduler_time_us) * 100.0) / ((float)total_run_time_us);
    LOG_INFO(SCHEDULER, "SchedulerOverhead: %7.3f %%", cpu_use);

    LOG_INFO(SCHEDULER, "Tmin - MinimumSchedulerExecutionPeriod");
    LOG_INFO(SCHEDULER, "Tavg - AverageSchedulerExecutionPeriod");
    LOG_INFO(SCHEDULER, "Tmax - MaximumSchedulerExecutionPeriod");

    return res;
}
