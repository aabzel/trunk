#include "timer_custom_isr.h"

#include "timer_mcal.h"

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_PWM
#include "pwm_mcal.h"
#endif

#ifdef HAS_SOFTWARE_TIMER
#include "software_timer_isr.h"
#endif

bool TIMx_IRQHandler(uint8_t num) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        if(false == Node->isr_busy) {
            Node->isr_busy = true;
            TimerISR(Node);
            HAL_TIM_IRQHandler(&Node->Handle);
            res = true;
            Node->isr_busy = false;
        } else {
            Node->error_cnt++;
        }
    }
    return res;
}

/*---------------------*/

/*TODO mode to ISR code file*/
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* pHandle) {
    if(pHandle) {
        int8_t timer_num = TimInstance2Num(pHandle->Instance);
        TimerHandle_t* Timer = TimerGetNode(timer_num);
        if(Timer) {
            Timer->pulse_fin_cnt++;
#ifdef HAS_PWM
            PwmHandle_t* Pwm = PwmTimerNumToNode(timer_num);
            if(Pwm) {
                if(Pwm->ComparatorHandler) {
                    // Pwm->ComparatorHandler();
                }
            }
#endif
        }
    }
}

/*TODO mode to ISR code file*/

//--------------------------------------------------

void HAL_TIM_TriggerCallback(TIM_HandleTypeDef* pHandle) {
    if(pHandle) {
        int8_t num = TimInstance2Num(pHandle->Instance);
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
        }
    }
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef* pHandle) {
    if(pHandle) {
        int8_t timer_num = TimInstance2Num(pHandle->Instance);
        TimerHandle_t* Timer = TimerGetNode(timer_num);
        if(Timer) {
            Timer->delay_elapse_cnt++;
            Timer->comparator_cnt++;

            if(Timer->ComparatorHandler) {
                Timer->ComparatorHandler();
            }

#ifdef HAS_PWM
            PwmHandle_t* Pwm = PwmTimerNumToNode(timer_num);
            if(Pwm) {
                if(Pwm->ComparatorHandler) {
                    Pwm->ComparatorHandler();
                }
            }
#endif
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* pHandle) {
    if(pHandle) {
        int8_t num = TimInstance2Num(pHandle->Instance);
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
            if(Node->PeriodDoneHandler) {
                Node->PeriodDoneHandler();
            }
#ifdef HAS_PWM
            PwmHandle_t* Pwm = PwmTimerNumToNode(num);
            if(Pwm) {
                if(Pwm->PeriodDoneHandler) {
                    Pwm->PeriodDoneHandler();
                }
            }
#endif

#ifdef HAS_TIMER_STACK
            if(TIMER_STACK_NUM == num) {
                sampling_timer_interrupt_handler();
            }
#endif

#ifdef HAS_SOFTWARE_TIMER
            if(TIMER_TIME_STAMP_US == num) {
                // HAL_IncTick();
                sw_timer_proc();
            }
#endif
        }
    }
}

//------------------------------

void HAL_TIM_ErrorCallback(TIM_HandleTypeDef* pHandle) {
    if(pHandle) {
        int8_t num = TimInstance2Num(pHandle->Instance);
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
            Node->error_cnt++;
        }
    }
}

/*Half */
void HAL_TIM_TriggerHalfCpltCallback(TIM_HandleTypeDef* pHandle) {
    if(pHandle) {
        int8_t num = TimInstance2Num(pHandle->Instance);
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
        }
    }
}

void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef* pHandle) {
    if(pHandle) {
        int8_t num = TimInstance2Num(pHandle->Instance);
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
            // Node->overflow++;
        }
    }
}

void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef* pHandle) {
    if(pHandle) {
        int8_t timer_num = TimInstance2Num(pHandle->Instance);
        TimerHandle_t* Timer = TimerGetNode(timer_num);
        if(Timer) {
            Timer->pulse_fin_half_cnt++;
        }
    }
}

/* Input capture */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* pHandle) {
    if(pHandle) {
        int8_t num = TimInstance2Num(pHandle->Instance);
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
            Node->ic_cap_cnt++;
        }
    }
}

void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef* pHandle) {
    if(pHandle) {
        int8_t num = TimInstance2Num(pHandle->Instance);
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
        }
    }
}
