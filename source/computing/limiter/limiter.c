#include "limiter.h"

#ifdef HAS_LIMITER_EXT
#include <stdlib.h> // for rand
#endif

#include "data_utils.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifndef MIN
#define MIN(n, m) (((n) < (m)) ? (n) : (m))
#endif

#ifndef MAX
#define MAX(n, m) (((n) < (m)) ? (m) : (n))
#endif

uint64_t limiter_get_time_us(void) {
    static uint64_t up_time_us = 0;
#ifdef HAS_TIME
    up_time_us = time_get_us();
#else
    up_time_us++;
#endif
    return up_time_us;
}

/*
 */
static bool limiter_task_frame(Limiter_t* const Node) {
    bool res = false;
    if(Node) {
#ifdef HAS_TIME
        uint64_t start_us = 0;
        uint64_t stop_us = 0;
        uint64_t duration_us = 0;
        uint64_t period_us = 0;
        (void)period_us;

        start_us = limiter_get_time_us();

        if(Node->start_time_prev_us < start_us) {
            period_us = start_us - Node->start_time_prev_us;
            res = true;
        } else {
            period_us = 0; /*(0x1000000U + start) - TASK_ITEM.start_time_prev; */
            res = false;
        }
        if(res) {
            DATA_UPDATE(Node->start_period_us, period_us);
            // data_u64_update(&Node->start_period_us, period_us);
        }

        // Node->start_time_prev_us = start_us;

        res = true;
#ifdef HAS_FLASH
        res = is_flash_addr((uint32_t)Node->function);
#endif
        if(res) {
            Node->call_cnt++;
            res = Node->function();
        } else {
            res = false;
        }

        stop_us = limiter_get_time_us();

        if(start_us < stop_us) {
            duration_us = stop_us - start_us;
            res = true;
#ifdef HAS_DATA_UTILS_EXT
            data_u64_update(&Node->duration_us, duration_us);
#endif

            Node->run_time_total_us += duration_us;
        } else {
            duration_us = 0; /*(0x1000000U + stop) - start;*/
            res = false;
        }
#else
        res = Node->function();
#endif
    }
    return res;
}

bool limiter(Limiter_t* const Node, uint32_t period_us, uint64_t up_time_us) {
    bool res = false;
    if(Node->on_off) {
#ifdef HAS_TIME
        if(Node->start_time_next_us < up_time_us) {
            Node->start_time_next_us = up_time_us + period_us;
            res = limiter_task_frame(Node);
            Node->start_time_prev_us = up_time_us;
        } else {
            Node->idle_cnt++;
        }

        if(up_time_us < Node->start_time_prev_us) {
            // LOG_DEBUG(LIMITER, "UpTimeOverflow %llu", up_time_us);
            Node->start_time_next_us = up_time_us + period_us;
        }
#else
        res = limiter_task_frame(Node);
#endif
    }
    return res;
}

// bool foo(void) { return true; }

bool limiter_init(Limiter_t* const Node, uint64_t period_us) {
    bool res = false;
#ifdef HAS_TIME_DIAG
    LOG_DEBUG(LIMITER, "Init:Period:%s", UsecToStr(period_us));
#endif
    if(Node) {
        if(false == Node->init) {
            Node->call_cnt = 0;
#ifdef HAS_DATA_UTILS_EXT
            res = data_u64_init(&Node->duration_us);
            res = data_u64_init(&Node->start_period_us);
#endif
            Node->run_time_total_us = 0;
            Node->start_time_next_us = 0;
            Node->start_time_prev_us = 0; /*Zero important*/
            Node->on_off = true;
            Node->init = true;
#ifdef HAS_LIMITER_EXT
            Node->phase_us = rand() % period_us;
#endif
            res = true;
            // Node->function = foo;
        }
    }
    return res;
}
