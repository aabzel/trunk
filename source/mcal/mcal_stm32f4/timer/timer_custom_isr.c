#include "timer_mcal.h"

#include "core_driver.h"
#include "timer_custom_drv.h"
#ifdef HAS_SOFTWARE_TIMER
#include "software_timer_isr.h"
#endif

void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t num = TimInstance2Num(htim->Instance);
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
            // Node->overflow++;
        }
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t num = TimInstance2Num(htim->Instance);
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
            Node->ic_cap_cnt++;
        }
    }
}

void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t num = TimInstance2Num(htim->Instance);
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
        }
    }
}

void HAL_TIM_TriggerCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t num = TimInstance2Num(htim->Instance);
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
        }
    }
}

void HAL_TIM_TriggerHalfCpltCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t num = TimInstance2Num(htim->Instance);
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
        }
    }
}

void HAL_TIM_ErrorCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t num = TimInstance2Num(htim->Instance);
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
            Node->error_cnt++;
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t num = TimInstance2Num(htim->Instance);
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
            Node->int_cnt++;
            Node->overflow++;
            if(TIMER_STACK_NUM == num) {
                sampling_timer_interrupt_handler();
            }
            if(TIMER_MS_TICK_NUM == num) {
                HAL_IncTick();
#ifdef HAS_SOFTWARE_TIMER
                sw_timer_proc();
#endif /*HAS_SOFTWARE_TIMER*/

#if defined(HAS_SYSTICK) && defined(HAS_SYSTICK_INT)
                // SysTickIntHandler();
#endif /**/
            }
        }
    }
}
