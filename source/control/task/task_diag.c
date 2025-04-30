#include "task_diag.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "float_utils.h"
#include "log.h"
#include "num_to_str.h"
#include "str_utils.h"
#include "super_cycle.h"
#include "super_cycle_config.h"
#include "super_cycle_diag.h"
#include "table_utils.h"
#include "task_config.h"
#include "task_info.h"
#include "time_mcal.h"
#include "writer_config.h"
#include "writer_generic.h"

bool task_diag_run(char* key_word1, char* key_word2) {
    bool res = false;
    uint64_t up_time_us = time_get_us();
    uint64_t total_time_ms = 0;
    uint32_t up_time_ms = time_get_ms32();
    int32_t id = 0;
    int32_t num = 0;
    uint64_t all_task_us = 0;
    all_task_us = task_all_run_time_us();
    super_cycle_diag();

    LOG_INFO(SCHEDULER, "UpTime %u us" CRLF, up_time_us);

    uint64_t total_run_time_us = super_cycle_run_time_us();
    LOG_INFO(SCHEDULER, "LoopTotalRunTime %llu us" CRLF, total_run_time_us);

    uint16_t t_cnt = task_get_cnt();

    LOG_INFO(SCHEDULER, "task cnt %u" CRLF, t_cnt);
    LOG_INFO(SCHEDULER, "total run time  %u us" CRLF, total_run_time_us);
    LOG_INFO(SCHEDULER, "up_time  %u ms" CRLF, up_time_ms);
    cli_printf("total_time %u ms" CRLF, total_time_ms);
    static const table_col_t cols[] = {
        {4, "Num"},     {4, "id"},    {17, "TaskName"}, {5, "On"},    {8, "Calls"},
        {8, "Calls/s"}, {11, "Rmin"}, {11, "Rcur"},     {11, "Rmax"}, {9, "CPU[%]"},

    };
    float cpu_use = 0.0;
    (void)cpu_use;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    char log_line[150] = {0};
    for(id = 0; id < t_cnt; id++) {
        TaskConfig_t* TaskNode = &TaskInstance[id];
        Limiter_t* LimiterNode = &(TaskNode->limiter);
        cpu_use = (((float)LimiterNode->run_time_total_us) * 100.0) / ((float)all_task_us);
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %2u " T_SEP, log_line, id);
        snprintf(log_line, sizeof(log_line), "%s %15s " T_SEP, log_line, TaskNode->name);
        snprintf(log_line, sizeof(log_line), "%s %3s " T_SEP, log_line, OnOff2Str(LimiterNode->on_off));
        snprintf(log_line, sizeof(log_line), "%s %6u " T_SEP, log_line, (uint32_t)LimiterNode->call_cnt);
        if(up_time_ms) {
            snprintf(log_line, sizeof(log_line), "%s %6u " T_SEP, log_line,
                     (uint32_t)((LimiterNode->call_cnt * 1000) / up_time_ms));
        }
        if(0 != LimiterNode->call_cnt) {
            snprintf(log_line, sizeof(log_line), "%s %9s " T_SEP, log_line, UsecToStr(LimiterNode->duration_us.min));
            snprintf(log_line, sizeof(log_line), "%s %9s " T_SEP, log_line, UsecToStr(LimiterNode->duration_us.cur));
            snprintf(log_line, sizeof(log_line), "%s %9s " T_SEP, log_line, UsecToStr(LimiterNode->duration_us.max));
        }
        snprintf(log_line, sizeof(log_line), "%s %7s " T_SEP, log_line, FloatToStr(cpu_use, 3));
        if(is_contain(log_line, key_word1, key_word2)) {
            cli_printf(TSEP " %2u ", num);
            cli_printf("%s" CRLF, log_line);
            // cli_printf(CRLF);
            num++;
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    LOG_INFO(SCHEDULER, "Rmax-MaxTaskContinuousRunTime");

    return res;
}

bool task_diag(char* key_word1, char* key_word2) {
    bool res = false;

    uint32_t up_time_ms = time_get_ms32();
    int32_t id = 0;
    int32_t num = 0;
    uint64_t all_task_us = 0;
    all_task_us = task_all_run_time_us();

    LOG_INFO(SCHEDULER, "up_time:%u ms", up_time_ms);
    super_cycle_diag();

    // uint64_t total_run_time_us = super_cycle_run_time_us();
    // LOG_INFO(SCHEDULER, "TotalRunTime:%f s", usec_to_sec(total_run_time_us));

    uint16_t t_cnt = task_get_cnt();
    LOG_INFO(SCHEDULER, "task cnt %u", t_cnt);

    static const table_col_t cols[] = {
        {4, "Num"},     {4, "id"},   {17, "TaskName"}, {5, "On"},     {8, "Calls"},
        {8, "Calls/s"}, {9, "Idle"}, {8, "Idle/s"},    {9, "CPU[%]"},
    };
    float cpu_use = 0.0;
    (void)cpu_use;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    char log_line[150] = {0};
    for(id = 0; id < t_cnt; id++) {
        TaskConfig_t* TaskNode = &TaskInstance[id];
        if(TaskNode) {
            Limiter_t* LimiterNode = &(TaskNode->limiter);
            if(LimiterNode) {

                cpu_use = (((float)LimiterNode->run_time_total_us) * 100.0) / ((float)all_task_us);
                strcpy(log_line, TSEP);
                snprintf(log_line, sizeof(log_line), "%s %2u " T_SEP, log_line, id);
                snprintf(log_line, sizeof(log_line), "%s %15s " T_SEP, log_line, TaskNode->name);
                snprintf(log_line, sizeof(log_line), "%s %3s " T_SEP, log_line, OnOff2Str(LimiterNode->on_off));
                snprintf(log_line, sizeof(log_line), "%s %6u " T_SEP, log_line, (uint32_t)LimiterNode->call_cnt);
                if(up_time_ms) {
                    snprintf(log_line, sizeof(log_line), "%s %6u " T_SEP, log_line,
                             (uint32_t)((LimiterNode->call_cnt * 1000) / up_time_ms));
                }
                snprintf(log_line, sizeof(log_line), "%s %7u " T_SEP, log_line, (uint32_t)LimiterNode->idle_cnt);
                if(up_time_ms) {
                    snprintf(log_line, sizeof(log_line), "%s %6u " T_SEP, log_line,
                             (uint32_t)((LimiterNode->idle_cnt * 1000) / up_time_ms));
                }

                snprintf(log_line, sizeof(log_line), "%s %7s " T_SEP, log_line, FloatToStr(cpu_use, 3));

                if(is_contain(log_line, key_word1, key_word2)) {
                    cli_printf(TSEP " %2u ", num);
                    cli_printf("%s" CRLF, log_line);
                    num++;
                    res = true;
                }
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool task_diag_period(char* key_word1, char* key_word2) {
    bool res = false;
    uint16_t t_cnt = task_get_cnt();
    super_cycle_diag();
    int32_t id = 0;
    uint64_t total_run_time_us = super_cycle_run_time_us();
    LOG_INFO(SCHEDULER, "TaskCnt %u,UpTime:%f s" CRLF, t_cnt, USEC_2_SEC(total_run_time_us));
    uint64_t all_task_us = 0;
    all_task_us = task_all_run_time_us();
    float all_percentages = 0.0;

    static const table_col_t cols[] = {{4, "id"},      {17, "TaskName"}, {5, "On"},    {8, "Calls"},
                                       {8, "Calls/s"}, {9, "CPU[%]"},    {11, "Tmin"}, {11, "Tcur"},
                                       {11, "Tmax"},   {11, "Tavg"},     {11, "Tset"}};
    float cpu_use = 0.0;
    (void)cpu_use;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    char log_line[150];
    for(id = 0; id < t_cnt; id++) {
        TaskConfig_t* TaskNode = &TaskInstance[id];
        if(TaskNode) {
            Limiter_t* LimiterNode = &(TaskNode->limiter);
            if(LimiterNode) {

                cpu_use = (((float)LimiterNode->run_time_total_us) * 100.0) / ((float)all_task_us);
                all_percentages += cpu_use;
                strcpy(log_line, TSEP);
                snprintf(log_line, sizeof(log_line), "%s %2u " T_SEP, log_line, id);
                snprintf(log_line, sizeof(log_line), "%s %15s " T_SEP, log_line, TaskNode->name);
                snprintf(log_line, sizeof(log_line), "%s %3s " T_SEP, log_line, OnOff2Str(LimiterNode->on_off));
                snprintf(log_line, sizeof(log_line), "%s %6s " T_SEP, log_line, uint32ToStr(LimiterNode->call_cnt));
                if(total_run_time_us) {
                    uint32_t call_per_s = (uint32_t)(((float)LimiterNode->call_cnt) / USEC_2_SEC(total_run_time_us));
                    snprintf(log_line, sizeof(log_line), "%s %6u " T_SEP, log_line, call_per_s);
                }
                snprintf(log_line, sizeof(log_line), "%s %7.3f " T_SEP, log_line, cpu_use);

                snprintf(log_line, sizeof(log_line), "%s %9s " T_SEP, log_line,
                         UsecToStr(LimiterNode->start_period_us.min));
                snprintf(log_line, sizeof(log_line), "%s %9s " T_SEP, log_line,
                         UsecToStr(LimiterNode->start_period_us.cur));
                snprintf(log_line, sizeof(log_line), "%s %9s " T_SEP, log_line,
                         UsecToStr(LimiterNode->start_period_us.max));
                uint32_t avr_per_us = 0;
                if(0 != LimiterNode->call_cnt) {
                    avr_per_us = total_run_time_us / LimiterNode->call_cnt;
                }
                snprintf(log_line, sizeof(log_line), "%s %9s " T_SEP, log_line, UsecToStr(avr_per_us));
                snprintf(log_line, sizeof(log_line), "%s %9s " T_SEP, log_line, UsecToStr(TaskNode->period_us));

                if(is_contain(log_line, key_word1, key_word2)) {
                    cli_printf("%s" CRLF, log_line);
                    res = true;
                }
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    res = is_float_equal_absolute(100.0, all_percentages, 2.0);
    if(false == res) {
        LOG_ERROR(SCHEDULER, "ExeError %f %%", all_percentages);
    }
    uint64_t scheduler_time_us = total_run_time_us - all_task_us;

    LOG_INFO(SCHEDULER, "TotalSupLpRunTime: %llu us", total_run_time_us);
    LOG_INFO(SCHEDULER, " AllTasksDuration: %llu us, %f %%", all_task_us, all_percentages);
    LOG_INFO(SCHEDULER, "SchedulerDuration: %llu us", scheduler_time_us);

    cpu_use = (((float)scheduler_time_us) * 100.0) / ((float)total_run_time_us);
    LOG_INFO(SCHEDULER, "SchedulerOverhead: %7.3f %%", cpu_use);

    LOG_INFO(SCHEDULER, "Tmin - MinimumTaskExecutionPeriod");
    LOG_INFO(SCHEDULER, "Tavg - AverageTaskExecutionPeriod");
    LOG_INFO(SCHEDULER, "Tmax - MaximumTaskExecutionPeriod");

    return res;
}

const char* TaskNode2Str(const TaskConfig_t* const Node) {
    strcpy(text, "");
    snprintf(text, sizeof(text), "%sName:[%s]", text, Node->name);
    snprintf(text, sizeof(text), "%sFoo:%p", text, Node->limiter.function);
#ifndef HAS_MIK32
    snprintf(text, sizeof(text), "%sPer:%llu us", text, Node->period_us);
    snprintf(text, sizeof(text), "%sPha:%llu us", text, Node->limiter.phase_us);
#endif
    return text;
}
