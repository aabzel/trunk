#include "none_blocking_pause.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#include "time_mcal.h"
#ifdef HAS_CLOCK
#include "clock.h"
#endif

#ifdef HAS_SUPER_CYCLE
#include "super_cycle.h"
#endif /*HAS_SUPER_CYCLE*/

#ifdef HAS_TASKS
#include "task_info.h"
#endif

#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif

#ifdef HAS_TIMER
#include "timer_utils.h"
#endif

#ifdef HAS_FREE_RTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

/* 49 days max*/
/*none blocking wait for self test and polling*/
bool wait_in_loop_ms(uint32_t wait_pause_ms) {
    bool res = false;
    if(wait_pause_ms) {
#ifdef HAS_LOG
        LOG_DEBUG(TIME, "Pause %u ms", wait_pause_ms);
#endif

#ifdef HAS_FREE_RTOS
        vTaskDelay(wait_pause_ms / portTICK_RATE_MS);
        res = true;
#endif

        uint32_t start_ms = 0U;
        uint32_t curr_ms = 0U;
        start_ms = time_get_ms32();
        bool loop = true;

        while(loop) {
#ifdef HAS_SUPER_CYCLE
            super_cycle_iteration();
#endif
            curr_ms = time_get_ms32();
            if(wait_pause_ms < (curr_ms - start_ms)) {
                res = true;
                loop = false;
                break;
            }
        }
    } else {
        res = true;
    }
    return res;
}

bool wait_ms(uint32_t wait_pause_ms) {
    bool res = false;
    if(0 < wait_pause_ms) {

        uint32_t start_ms = 0U;
        uint32_t curr_ms = 0U;
        uint32_t cnt = 0;
        start_ms = time_get_ms32();
        bool loop = true;
        int32_t diff_ms = 0;

        while(loop) {
            curr_ms = time_get_ms32();
            diff_ms = curr_ms - start_ms;
            if(wait_pause_ms < diff_ms) {
                res = true;
                loop = false;
                break;
            }
            cnt++;
            if((2500 * wait_pause_ms) < cnt) {
                res = false;
                loop = false;
                break;
            }
        }
    } else {
        res = true;
    }
    return res;
}

/*none blocking wait for self test and poling*/
bool wait_us(uint64_t wait_pause_us) {
    uint64_t start_us = 0U;
    uint64_t curr_us = 0U;
    uint64_t diff_us = 0U;
    bool res = false;
    start_us = time_get_us();
    bool loop = true;
    while(loop) {
        curr_us = time_get_us();
        diff_us = curr_us - start_us;
        if(wait_pause_us < diff_us) {
            res = true;
            loop = false;
            break;
        }
    }
    return res;
}
