#include "task_commands.h"

#include <inttypes.h>

#ifdef HAS_CLOCK
#include "clock.h" //TODO DEL
#endif

#ifdef HAS_STRING
#include "convert.h"
#endif /*HAS_STRING*/

#include "common_diag.h"
#include "data_utils.h"
#include "log.h"

#ifdef HAS_SYSTICK
#include "systick_mcal.h"
#endif
#include "task_diag.h"
#include "task_info.h"

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifndef HAS_TASK_DIAG
#error "+HAS_TASK_DIAG"
#endif

bool task_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool task_state = true;
    uint16_t task_id = 0;
    if(1 <= argc) {
        res = try_str2uint16(argv[0], &task_id);
        if(false == res) {
            LOG_ERROR(SCHEDULER, "Unable to extract task_id %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &task_state);
        if(false == res) {
            LOG_ERROR(SCHEDULER, "Unable to extract task_state %s", argv[1]);
        }
    }

    if(res) {
        uint16_t cnt = task_get_cnt();
        if(task_id < cnt) {
            TaskInstance[task_id].limiter.on_off = task_state;
            LOG_INFO(SCHEDULER, "task %s %s", TaskInstance[task_id].name, (true == task_state) ? "on" : "off");
        }
    } else {
        LOG_ERROR(SCHEDULER, "Usage tc Num Status");
    }
    return res;
}

bool task_diag_command(int32_t argc, char* argv[]) {
    (void)(argc);
    (void)(argv);
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
        res = task_diag(keyWord1, keyWord2);
    }
    return res;
}

bool task_init_command(int32_t argc, char* argv[]) {
    (void)(argc);
    (void)(argv);
    bool res = false;
    res = task_init();
    return res;
}

bool task_diag_run_command(int32_t argc, char* argv[]) {
    (void)(argc);
    (void)(argv);
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
        res = task_diag_run(keyWord1, keyWord2);
    }
    return res;
}

bool task_diag_period_command(int32_t argc, char* argv[]) {
    (void)(argc);
    (void)(argv);
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
        res = task_diag_period(keyWord1, keyWord2);
    }
    return res;
}
