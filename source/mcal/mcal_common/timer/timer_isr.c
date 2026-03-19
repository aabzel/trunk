#include "timer_isr.h"

#ifdef HAS_DELTA_SIGMA
#include "delta_sigma.h"
#endif

bool TimerISR(TimerHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->int_cnt++;
        Node->int_done = true;
        res = true;
    }
    return res;
}

bool TimerPeriodElapsedCallback(TimerHandle_t* const Node) {
    bool res = false;
    if(Node) {
#ifdef HAS_DELTA_SIGMA
        if(4 == Node->num) {
            res = delta_sigma_isr_proc_one(1);
        }
#endif
        res = true;
    }
    return res;
}
