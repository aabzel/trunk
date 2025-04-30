#include "software_timer_isr.h"

#include <stddef.h>

#include "flash_mcal.h"
#include "software_timer.h"

/*Called from ISR SysTick or any hardware timer with stable Msec period*/
static bool sw_timer_run_callback(SoftwareTimer_t* instance) {
    bool res = false;
    if(instance) {
        res = is_flash_addr((uint32_t)instance->handler);
        if(res) {
            res = instance->handler();
            instance->handler_cnt++;
            instance->isr = true;
        } else {
            instance->err_cnt++;
        }
    }
    return res;
}

/*Called from ISR*/
static bool sw_timer_proc_up(SoftwareTimer_t* instance) {
    bool res = false;
    if(instance) {
        if(instance->cnt < instance->period_ms) {
            instance->cnt++;
            res = true;
        } else if(instance->cnt == instance->period_ms) {
            instance->cnt = 0;
            res = sw_timer_run_callback(instance);
            switch((uint8_t)instance->mode) {
            case SW_TIMER_MODE_CONTINUOUS:
                instance->on_off = true;
                break;
            case SW_TIMER_MODE_SINGLE:
                instance->on_off = false;
                break;
            }
            res = true;
        } else {
            res = false;
            instance->err_cnt++;
            instance->cnt = 0;
        }
    }
    return res;
}

/*Called from ISR*/
static bool sw_timer_proc_down(SoftwareTimer_t* instance) {
    bool res = false;
    if(instance) {
        if(0 == instance->cnt) {
            res = sw_timer_run_callback(instance);
            switch((uint8_t)instance->mode) {
            case SW_TIMER_MODE_CONTINUOUS:
                instance->cnt = instance->period_ms;
                instance->on_off = true;
                break;
            case SW_TIMER_MODE_SINGLE:
                instance->on_off = false;
                instance->cnt = 0;
                break;
            }
        } else {
            instance->cnt--;
        }
    }
    return res;
}

/*Called from ISR SysTick or any hardware timer with stable Msec period*/
bool sw_timer_proc(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = 0;
    cnt = software_timer_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(SoftwareTimerInstance[i].valid) {
            if(SoftwareTimerInstance[i].on_off) {
                switch((uint8_t)SoftwareTimerInstance[i].dir) {
                case SW_TIMER_CNT_DIR_UP:
                    res = sw_timer_proc_up(&SoftwareTimerInstance[i]);
                    break;
                case SW_TIMER_CNT_DIR_DOWN:
                    res = sw_timer_proc_down(&SoftwareTimerInstance[i]);
                    break;
                }
            }
        }
    }
    return res;
}
