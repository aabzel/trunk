#include "super_cycle.h"

#include "common_functions.h"
#ifdef HAS_MISCELLANEOUS
#include "data_utils.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifdef HAS_FREE_RTOS
#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"
#endif

#ifdef HAS_ZEPHYR_RTOS
#include <zephyr/kernel.h>
#endif /*HAS_ZEPHYR_RTOS*/

#ifndef MIN
#define MIN(n, m) (((n) < (m)) ? (n) : (m))
#endif

#ifndef MAX
#define MAX(n, m) (((n) < (m)) ? (m) : (n))
#endif

bool super_cycle_iteration(void) {
    bool res = false;
    if(SuperCycle.init) {
        res = true;
        SuperCycle.run = true;
        SuperCycle.spin_cnt++;
        if(SuperCycle.prev_start_time_us < SuperCycle.start_time_us) {
            SuperCycle.error++;
        }

#ifdef HAS_TIME
        SuperCycle.start_time_us = time_get_us();
#else  /*HAS_TIME*/
        SuperCycle.start_time_us++;
#endif /*HAS_TIME*/

#ifdef HAS_MISCELLANEOUS
        uint32_t duration_us = (uint32_t)(SuperCycle.start_time_us - SuperCycle.prev_start_time_us);
        DATA_UPDATE(SuperCycle.duration_us, duration_us);
#endif

        super_cycle_proc(SuperCycle.start_time_us);

#ifdef HAS_FREE_RTOS
        vTaskDelay(SuperCycle.iteration_sleep_ms);
#endif /*HAS_FREE_RTOS*/

#ifdef HAS_ZEPHYR_RTOS
        k_msleep(SuperCycle.iteration_sleep_ms); /*Works*/
                                                 // k_sleep(K_NO_WAIT); /*Cli hang on No Sound*/
                                                 // k_yield(); /*Cli hang on, No Sound*/
#endif
        SuperCycle.prev_start_time_us = SuperCycle.start_time_us;
    }

    return res;
}

#define SUPER_CYCLE_DEFAUIT_ITERATION_MS 3
bool super_cycle_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_WARNING(SUPER_CYCLE, "Init");
#endif
    SuperCycle.start_time_us = 0;
    SuperCycle.run = false;
    SuperCycle.error = 0;
    SuperCycle.iteration_sleep_ms = SUPER_CYCLE_DEFAUIT_ITERATION_MS;
    SuperCycle.init = true;

#ifdef HAS_DATA_UTILS_EXT
    data_u32_init(&SuperCycle.duration_us);
#endif

#ifdef HAS_DATA_UTILS_EXT
    data_u32_init(&SuperCycle.duration_us);
    SuperCycle.spin_cnt = 0;
    SuperCycle.prev_start_time_us = 0;
#endif /*HAS_DEBUG*/

#ifdef HAS_TIME
    SuperCycle.init_end_time_us = 0;
    // SuperCycle.init_end_time_us = time_get_us(); // That call spoils upTime counter in SCR1.
    SuperCycle.init_end_time_ms = ((uint32_t)SuperCycle.init_end_time_us) / 1000UL;
#endif /*HAS_TIME*/
#ifdef HAS_LOG
    // LOG_DEBUG(SUPER_CYCLE, "InitEndTime:%llu us", SuperCycle.init_end_time_us);
#endif
    return res;
}

//_Noreturn
void super_cycle_start(void) {
#ifdef HAS_LOG
    LOG_INFO(SUPER_CYCLE, "Start");
#endif
    super_cycle_init();

    for(;;) {
        super_cycle_iteration();
    }
}

bool super_cycle_check_continuity(SuperCycle_t* const Node, uint64_t new_val) {
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

uint64_t super_cycle_get_init_time_us(void) { return SuperCycle.start_time_us; }

uint64_t super_cycle_run_time_us(void) {
    uint64_t run_time_us = 0;
#ifdef HAS_TIME
    uint64_t up_time_us = time_get_us();
    run_time_us = up_time_us - SuperCycle.init_end_time_us;
#endif

#ifdef HAS_LOG
    // LOG_DEBUG(SUPER_CYCLE, "UpTime: %llu us", up_time_us);
#endif
    return run_time_us;
}

uint32_t super_cycle_run_time_ms(void) {
    uint32_t run_time_ms = 0;
#ifdef HAS_TIME
    uint64_t up_time_ms = time_get_ms32();
    run_time_ms = up_time_ms - SuperCycle.init_end_time_ms;
#endif

#ifdef HAS_LOG
    LOG_DEBUG(SUPER_CYCLE, "UpTime: %u ms", up_time_ms);
#endif
    return run_time_ms;
}
