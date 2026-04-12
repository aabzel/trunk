#include "super_cycle.h"

#include "common_functions.h"
#include "compiler_const.h"

#ifdef HAS_MISCELLANEOUS
#include "data_utils.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_MULTICORE
#include "multicore_mcal.h"
#endif

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifdef HAS_RTOS
#include "rtos_mcal.h"
#endif

#ifndef MIN
#define MIN(n, m) (((n) < (m)) ? (n) : (m))
#endif

#ifndef MAX
#define MAX(n, m) (((n) < (m)) ? (m) : (n))
#endif

#include "code_generator.h"

COMPONENT_GET_NODE(SuperCycle, super_cycle)
COMPONENT_GET_CONFIG(SuperCycle, super_cycle)

static bool SuperCycleIsValidConfig(const SuperCycleConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(0 < Config->max_duration_us) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(SUPER_CYCLE, "NoMaxDiaration");
#endif
            res = false;
        }
    }

    return res;
}

bool super_cycle_proc_one(uint8_t num) {
    bool res = false;
    SuperCycleHandle_t* Node = SuperCycleGetNode(num);
    if(Node) {
        if(Node->init) {
            res = true;
            Node->run = true;
            Node->spin_cnt++;
            if(Node->prev_start_time_us < Node->start_time_us) {
                Node->error++;
            }

#ifdef HAS_TIME
            Node->start_time_us = time_get_us();
#else
            Node->start_time_us++;
#endif

#ifdef HAS_MISCELLANEOUS
            uint32_t duration_us = (uint32_t)(Node->start_time_us - Node->prev_start_time_us);
            DATA_UPDATE(Node->duration_us, duration_us);
#endif

            super_cycle_proc_ll(Node);

#ifdef HAS_FREE_RTOS
            vTaskDelay(Node->iteration_sleep_ms);
#endif /*HAS_FREE_RTOS*/

#ifdef HAS_ZEPHYR_RTOS
            k_msleep(Node->iteration_sleep_ms); /*Works*/
                                                // k_sleep(K_NO_WAIT); /*Cli hang on No Sound*/
                                                // k_yield(); /*Cli hang on, No Sound*/
#endif
            Node->prev_start_time_us = Node->start_time_us;
        }
    }

    return res;
}

uint8_t super_cycle_core_to_num(void) {
    uint8_t num = 1;
#ifdef HAS_MULTICORE
    int8_t core_num = multicore_get_core_num();
    num = ((uint8_t)core_num) + 1;
#endif
    return num;
}

bool super_cycle_check_continuity(SuperCycleHandle_t* const Node, uint64_t new_val) {
    bool res = false;
    if(Node) {
        if(Node->prev_start_time_us <= new_val) {
            res = true;
        } else if(new_val == Node->prev_start_time_us) {
#ifdef HAS_LOG
            // LOG_WARNING(SUPER_CYCLE, "StallErr: Cur %llu US", new_val);
#endif
            res = false;
        } else {
            res = false;
#ifdef HAS_STREAM
            uint64_t diff_val = Node->prev_start_time_us - new_val;
            (void)diff_val;
            // LOG_ERROR(SUPER_CYCLE, "UpTimeError: Cur %llu US Prev %llu US Diff %llu US", new_val,
            //          Node->prev_start_time_us, diff_val);
#endif /*HAS_STREAM*/
            Node->error++;
        }
        Node->prev_start_time_us = new_val;
    }
    return res;
}

#if 0
uint64_t super_cycle_get_init_time_us(uint8_t num) {
    uint64_t start_time_us = 0;
    SuperCycleHandle_t* Node = SuperCycleGetNode(num);
    if(Node) {
        start_time_us = Node->start_time_us;
    }
    return start_time_us;
}
#endif

uint64_t super_cycle_run_time_us(uint8_t num) {
    uint64_t run_time_us = 0;
    SuperCycleHandle_t* Node = SuperCycleGetNode(num);
    if(Node) {
#ifdef HAS_TIME
        uint64_t up_time_us = time_get_us();
        run_time_us = up_time_us - Node->init_end_time_us;
#endif

#ifdef HAS_LOG
        // LOG_DEBUG(SUPER_CYCLE, "UpTime: %llu us", up_time_us);
#endif
    }
    return run_time_us;
}

static bool super_cycle_init_custom(void) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(SUPER_CYCLE, "InitCustom");
#endif
    return res;
}

bool super_cycle_init_one(uint8_t num) {
    bool res = false;
    const SuperCycleConfig_t* Config = SuperCycleGetConfig(num);
    if(Config) {
        res = SuperCycleIsValidConfig(Config);
        if(res) {
            SuperCycleHandle_t* Node = SuperCycleGetNode(num);
            if(Node) {
#ifdef HAS_LOG
                LOG_WARNING(SUPER_CYCLE, "Init:%u", num);
#endif
                Node->scheduler_num = Config->scheduler_num;
                Node->start_time_us = 0;
                Node->iteration_sleep_ms = SUPER_CYCLE_DEFAUIT_ITERATION_MS;
                Node->error = 0;
                Node->valid = true;
                Node->run = false;
                Node->init = true;

#ifdef HAS_DATA_UTILS_EXT
                data_u32_init(&Node->duration_us);
#endif

#ifdef HAS_DATA_UTILS_EXT
                data_u32_init(&Node->duration_us);
                Node->spin_cnt = 0;
                Node->prev_start_time_us = 0;
#endif /**/

#ifdef HAS_TIME
                Node->init_end_time_us = 0;
                // Node->init_end_time_us = time_get_us(); // That call spoils upTime counter in SCR1.
                Node->init_end_time_ms = ((uint32_t)Node->init_end_time_us) / 1000UL;
#endif /*HAS_TIME*/

#ifdef HAS_LOG
                // LOG_DEBUG(SUPER_CYCLE, "InitEndTime:%llu us", Node->init_end_time_us);
#endif
                res = true;
            }
        }
    }
    return res;
}

_WEAK_FUN_ bool super_cycle_proc_max_perf(void) {
    bool res = true;
    return res;
}

void super_cycle_start_one(uint8_t num) {
#ifdef HAS_LOG
    LOG_INFO(SUPER_CYCLE, "Start");
#endif
    super_cycle_init_one(num);

    for(;;) {
#ifdef HAS_SUPER_CYCLE_MAX_PERF
        super_cycle_proc_max_perf();
#else
        super_cycle_proc_max_perf();
        super_cycle_proc_one(num);
#endif
    }
}

COMPONENT_INIT_PATTERT(SUPER_CYCLE, SUPER_CYCLE, super_cycle)
COMPONENT_PROC_PATTERT(SUPER_CYCLE, SUPER_CYCLE, super_cycle)
