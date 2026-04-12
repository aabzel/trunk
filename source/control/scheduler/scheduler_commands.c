#include "scheduler_commands.h"

#include <inttypes.h>

#ifdef HAS_STRING
#include "convert.h"
#endif

#include "common_diag.h"
#include "data_utils.h"
#include "log.h"
#include "scheduler_mcal.h"

#ifndef HAS_SCHEDULER_DIAG
#error "+HAS_SCHEDULER_DIAG"
#endif

bool scheduler_task_period_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint16_t task_num = 0;
    uint32_t task_period_us = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(SCHEDULER, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint16(argv[1], &task_num);
        log_res(SCHEDULER, res, "Task");
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &task_period_us);
        log_res(SCHEDULER, res, "PeriodUs");
    }

    if(res) {
        uint32_t task_period_get = 0;
        res = scheduler_task_period_get(num, task_num, &task_period_get);
        if(res) {
            LOG_INFO(SCHEDULER, "SCHEDULER%u,Task:%s,GetPeriodUs:%u", num, TaskNumToName(num, task_num),
                     task_period_get);
        }
        if(3 <= argc) {
            LOG_INFO(SCHEDULER, "SCHEDULER%u,Task:%s,SetPeriodUs:%u", num, TaskNumToName(num, task_num),
                     task_period_us);
            res = scheduler_task_period_set(num, task_num, task_period_us);
        }

    } else {
        LOG_ERROR(SCHEDULER, "Usage tp Num id PerionUs");
    }
    return res;
}

bool scheduler_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool scheduler_state = true;
    uint16_t task_num = 0;

    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(SCHEDULER, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint16(argv[1], &task_num);
        log_res(SCHEDULER, res, "Task");
    }

    if(3 <= argc) {
        res = try_str2bool(argv[2], &scheduler_state);
        log_res(SCHEDULER, res, "En");
    }

    if(res) {
        SchedulerTaskHandle_t* Task = SchedulerNunToTaskNode(num, task_num);
        if(Task) {
            Task->limiter.on_off = scheduler_state;
            LOG_INFO(SCHEDULER, "%s", SchedulerTaskToStr(Task));
        }

    } else {
        LOG_ERROR(SCHEDULER, "Usage tc Num id Status");
    }
    return res;
}

bool scheduler_diag_command(int32_t argc, char* argv[]) {
    (void)(argc);
    (void)(argv);
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    uint8_t num = 1;

    if(0 <= argc) {
        num = 1;
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(SCHEDULER, res, "Num");
    }

    if(2 <= argc) {
        strncpy(keyWord1, argv[1], sizeof(keyWord1));
        res = true;
    }

    if(3 <= argc) {
        strncpy(keyWord2, argv[2], sizeof(keyWord2));
        res = true;
    }

    if(res) {
        res = scheduler_diag(num, keyWord1, keyWord2);
        log_res(SCHEDULER, res, "Diag");
    } else {
        LOG_ERROR(SCHEDULER, "Usage tdi Num Status");
    }
    return res;
}

bool scheduler_init_command(int32_t argc, char* argv[]) {
    (void)(argc);
    (void)(argv);
    bool res = false;
    res = scheduler_mcal_init();
    log_res(SCHEDULER, res, "Init");
    return res;
}

bool scheduler_diag_run_command(int32_t argc, char* argv[]) {
    (void)(argc);
    (void)(argv);
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";

    uint8_t num = 1;
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(SCHEDULER, res, "Num");
    }

    if(2 <= argc) {
        strncpy(keyWord1, argv[1], sizeof(keyWord1));
        res = true;
    }

    if(3 <= argc) {
        strncpy(keyWord2, argv[2], sizeof(keyWord2));
        res = true;
    }

    if(res) {
        res = scheduler_diag_run(num, keyWord1, keyWord2);
        log_res(SCHEDULER, res, "DRun");
    } else {
        LOG_ERROR(SCHEDULER, "Usage tdr Num Key");
    }
    return res;
}

bool scheduler_diag_period_command(int32_t argc, char* argv[]) {
    (void)(argc);
    (void)(argv);
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";

    uint8_t num = 1;
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(SCHEDULER, res, "Num");
    }

    if(2 <= argc) {
        strncpy(keyWord1, argv[1], sizeof(keyWord1));
        res = true;
    }

    if(3 <= argc) {
        strncpy(keyWord2, argv[2], sizeof(keyWord2));
        res = true;
    }

    if(res) {
        res = scheduler_diag_period(num, keyWord1, keyWord2);
        log_res(SCHEDULER, res, "Period");
    } else {
        LOG_ERROR(SCHEDULER, "Usage sdp Num KeyWord");
    }
    return res;
}
