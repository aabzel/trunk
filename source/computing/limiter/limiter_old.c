#include "limiter.h"

#include <stdlib.h>

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


static uint64_t limiter_get_time_us(void) {
    static uint64_t up_time_us = 0;
#ifdef HAS_TIME
    up_time_us = time_get_us();
#else  /*HAS_TIME*/
    up_time_us++;
#endif /*HAS_TIME*/
    return up_time_us;
}


static bool limiter_task_frame(Limiter_t* const Node) {
    bool res = false;
    if(Node) {
        uint64_t start_us = 0;
        uint64_t stop_us = 0;
        uint64_t duration_us = 0;
        uint64_t period_us = 0;

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
#endif /*HAS_FLASH*/
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
            data_u64_update(&Node->duration_us, duration_us);

            Node->run_time_total_us += duration_us;
        } else {
            duration_us = 0; /*(0x1000000U + stop) - start;*/
            res = false;
        }
    }
    return res;
}

bool limiter(Limiter_t* const Node, uint32_t period_us, uint64_t up_time_us) {
    bool res = false;
    if(Node->on_off) {
        // uint64_t diff_us = up_time_us - Node->start_time_prev_us;
        // if(0 == diff_us) {
        //    res = false;
        //}

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
    }
    return res;
}

// bool foo(void) { return true; }

bool limiter_init(Limiter_t* const Node, uint64_t period_us) {
    bool res = false;
#ifdef HAS_TIME_DIAG
    //LOG_WARNING(LIMITER, "Init: Period:%s", UsecToStr(period_us));
#endif
    if(Node) {
        if(false == Node->init) {
            Node->call_cnt = 0;
            res = data_u64_init(&Node->duration_us);
            res = data_u64_init(&Node->start_period_us);
            Node->run_time_total_us = 0;
            Node->start_time_next_us = 0;
            Node->start_time_prev_us = 0; /*Zero important*/
            Node->on_off = true;
            Node->init = true;
            Node->phase_us = rand() % period_us;
            res = true;
            // Node->function = foo;
        }
    }
    return res;
}
