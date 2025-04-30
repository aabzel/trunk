#include "timer_drv.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "timer_custom_drv.h"
#include "bit_utils.h"
#include "core_driver.h"

#ifdef HAS_CLOCK
#include "clock.h"
#endif

#include "float_utils.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_SOFTWARE_TIMER
#include "software_timer_isr.h"
#endif /*HAS_SOFTWARE_TIMER*/

#ifdef HAS_SYSTICK
#include "systick_general.h"
#endif

#include "clock_custom_const.h"
#include "at32f435_437.h"
//#include "timer_bsp.h"
#include "sys_config.h"
#include "timer_config.h"
#include "timer_types.h"
#include "time_mcal.h"
#include "timer_utils.h"
#include "timer_stm32_types.h"

uint8_t timer_get_width(uint32_t timer_base) {
    uint8_t width = 0;
    return width;
}

const static TimIntance_t TimLut[] = {
#ifdef TIM1
    {
        .clock_bus = BUS_APB2,
        .num = 1,
        .instance = TIM1,
    },
#endif /**/

#ifdef TIM2
    {
        .clock_bus = BUS_APB1,
        .num = 2,
        .instance = TIM2,
    },
#endif /**/

#ifdef TIM3
    {
        .clock_bus = BUS_APB1,
        .num = 3,
        .instance = TIM3,
    },
#endif /**/

#ifdef TIM4
    {
        .clock_bus = BUS_APB1,
        .num = 4,
        .instance = TIM4,
    },
#endif /**/

#ifdef TIM5
    {
        .clock_bus = BUS_APB1,
        .num = 5,
        .instance = TIM5,
    },
#endif /**/

#ifdef TIM6
    {
        .clock_bus = BUS_APB1,
        .num = 6,
        .instance = TIM6,
    },
#endif /**/

#ifdef TIM7
    {
        .clock_bus = BUS_APB1,
        .num = 7,
        .instance = TIM7,
    },
#endif /**/

#ifdef TIM8
    {
        .clock_bus = BUS_APB2,
        .num = 8,
        .instance = TIM8,
    },
#endif /**/

#ifdef TIM9
    {
        .clock_bus = BUS_APB2,
        .num = 9,
        .instance = TIM9,
    },
#endif /**/

#ifdef TIM10
    {
        .clock_bus = BUS_APB2,
        .num = 10,
        .instance = TIM10,
    },
#endif /**/

#ifdef TIM11
    {
        .clock_bus = BUS_APB2,
        .num = 11,
        .instance = TIM11,
    },
#endif /**/

#ifdef TIM12
    {
        .clock_bus = BUS_APB1,
        .num = 12,
        .instance = TIM12,
    },
#endif /**/

#ifdef TIM13
    {
        .clock_bus = BUS_APB1,
        .num = 13,
        .instance = TIM13,
    },
#endif /**/

#ifdef TIM14
    {
        .clock_bus = BUS_APB1,
        .num = 14,
        .instance = TIM14,
    },
#endif /**/

};

TIM_TypeDef* timer_get_ptr(uint8_t num) {
    TIM_TypeDef* instance = NULL;
    uint16_t i = 0;
    for(i = 0; i < ARRAY_SIZE(TimLut); i++) {
        if(num == TimLut[i].num) {
            instance = TimLut[i].instance;
            break;
        }
    }
    return instance;
}

uint32_t timer_get_period(uint8_t timer_num) {
    uint32_t timer_period32 = 0;
    TIM_TypeDef* TIMx = timer_get_ptr(timer_num);
    if(TIMx) {
        timer_period32 = TIMx->ARR;
    }
    return timer_period32;
}

uint32_t timer_get_cc_val( uint8_t  timer_num,   CapComChannel_t chaneel  ){
	return 0;
}

bool timer_set_cc_val( uint8_t timer_num, CapComChannel_t channel,
		uint32_t cc_value, bool int_on){
	return false;
}


bool timer_set_status( uint8_t timer_num,   bool on_off){
	return 0;
}

uint8_t timer_get_bitness(  uint8_t timer_num){
	return 0;
}

double timer_get_tick_s(uint8_t  timer_num){
	return 0.0;
}

double timer_get_freq(uint8_t timer_num) {
    double frequency_hz = 0.0;
    TIM_TypeDef* TIMx = timer_get_ptr(timer_num);
    if(TIMx) {
        uint32_t bus_clock = timer_get_bus_clock(timer_num);
        frequency_hz = ((double)bus_clock) / (((double)TIMx->ARR + 1) * ((double)TIMx->PSC + 1));
    }
    return frequency_hz;
}

uint32_t timer_get_bus_clock(uint8_t num) {
    uint32_t clock_hz = 0;
    uint16_t i = 0;
    for(i = 0; i < ARRAY_SIZE(TimLut); i++) {
        if(num == TimLut[i].num) {
            uint32_t pclk = 0;
            switch(TimLut[i].clock_bus) {
            case BUS_APB1:
                pclk = HAL_RCC_GetPCLK1Freq();
                break;
            case BUS_APB2:
                pclk = HAL_RCC_GetPCLK2Freq();
                break;
            default:
                break;
            }

            clock_hz = 2 * pclk;
            break;
        }
    }
    return clock_hz;
}

bool timer_get_status(uint8_t timer_num) {
    bool res = true;
    uint8_t status = 0xFF;
    uint32_t timer_cr1 = 0;
    TIM_TypeDef* TIMx = timer_get_ptr(timer_num);
    if(TIMx) {
        res = true;
        timer_cr1 = TIMx->CR1;
    } else {
        res = false;
    }

    if(res) {
        status = MASK_1BIT & timer_cr1;
    }
    return status;
}

uint32_t timer_get_prescaler(uint8_t timer_num) {
    bool res = true;
    uint32_t timer_prescaler = 0xFF;
    uint32_t timer_prescaler32 = 0;

    TIM_TypeDef* TIMx = timer_get_ptr(timer_num);
    if(TIMx) {
        res = true;
        timer_prescaler32 = TIMx->PSC;
    } else {
        res = false;
    }

    if(res) {
        timer_prescaler = MASK_16BIT & timer_prescaler32;
    }
    return timer_prescaler;
}

bool timer_get_auto_reload(uint8_t timer_num) {
    bool res = false;

    TIM_TypeDef* TIMx = timer_get_ptr(timer_num);
    if(TIMx) {
        if(CHECK_BIT_NUM(TIMx->CR1, 7)) {
            res = true;
        } else {
            res = false;
        }
    }

    return res;
}

uint32_t timer_get_counter(uint8_t timer_num, CapComChannel_t channel) {
    uint32_t timer_cnt32 = 0;
    TIM_TypeDef* TIMx = timer_get_ptr(timer_num);
    if(NULL != TIMx) {
        timer_cnt32 = TIMx->CNT;
    }

    return timer_cnt32;
}

uint64_t timer_get_period_us(uint8_t timer_num) {
    uint64_t real_period_us = 0;
    uint32_t prescaler = 0;
    uint32_t reload = 0;
    TimerItem_t* TimNode = NULL;
    TimNode = TimerGetNode(timer_num);
    if(TimNode) {
        double fck = (double)timer_get_bus_clock(timer_num);
        double tf = 1.0 / fck;
        prescaler = TimNode->timer_h.Instance->PSC;
        reload = TimNode->timer_h.Instance->ARR;
        double t_psc = tf * ((double)prescaler);

        real_period_us = (uint64_t)(t_psc * ((double)reload)) * 1000000.0;
    }
    return real_period_us;
}

double timer_get_period_s(uint8_t timer_num) {
    double real_period_s = 0;
    uint32_t prescaler = 0;
    uint32_t reload = 0;
    TimerItem_t* TimNode = NULL;
    TimNode = TimerGetNode(timer_num);
    if(TimNode) {
        double fck = (double)timer_get_bus_clock(timer_num);
        double tf = 1.0 / fck;
        prescaler = TimNode->timer_h.Instance->PSC;
        reload = TimNode->timer_h.Instance->ARR;
        double t_psc = tf * ((double)prescaler);

        real_period_s = (t_psc * ((double)reload));
    }
    return real_period_s;
}

uint64_t timer_get_us(void) {
    uint64_t up_time_us = 0, int_cnt = 0, cnt_us = 0;
    uint64_t period_us = MSEC_2_USEC(TIMER_US_PERIOD_MS);
    TimerItem_t* Node = NULL;
#ifdef TIMER_US_TICK_NUM
    Node = TimerGetNode(TIMER_US_TICK_NUM);
#endif /*TIMER_US_TICK_NUM*/
    if(Node) {
        int_cnt = Node->int_cnt;
        cnt_us = __HAL_TIM_GET_COUNTER(&(Node->timer_h));
        up_time_us = cnt_us + int_cnt * period_us;
    }
    return up_time_us;
}

uint32_t timer_get_ms(void) {
    uint32_t up_time_ms = 0;
    //uint32_t int_cnt = 0, cnt_ms = 0;
    TimerItem_t* Node = NULL;
#ifdef TIMER_MS_TICK_NUM
    Node = TimerGetNode(TIMER_MS_TICK_NUM);
#endif /*TIM2*/

    if(Node) {
        //cnt_ms = __HAL_TIM_GET_COUNTER(&(Node->timer_h))/2;
        //int_cnt = Node->int_cnt;
        //up_time_ms = cnt_ms + TIMER_MS_PERIOD_MS * (int_cnt/2);

        up_time_ms =  Node->int_cnt;
    }

    return up_time_ms;
}

TimDir_t timer_get_dir(uint8_t timer_num) {
    TimDir_t dir = CNT_DIR_UNDEF;
    TIM_TypeDef* TIMx = timer_get_ptr(timer_num);
    if(TIMx) {
        uint32_t timer_cr1 = 0;
        timer_cr1 = TIMx->CR1;
        if(BIT_4 == (BIT_4 & timer_cr1)) {
            dir = CNT_DIR_DOWN;
        } else {
            dir = CNT_DIR_UP;
        }
    }
    return dir;
}

bool timer_init_item(uint8_t timer_num) {
    bool res = false;
#ifdef HAS_LOG
    LOG_INFO(TIMER, "%u Init", timer_num);
#endif
    const TimerConfig_t* TimerConfigNode = NULL;
    TimerConfigNode = TimerGetConfigNode(timer_num);
    if(TimerConfigNode) {
        uint32_t out_load = 0;

        uint32_t prescaler = 0;

        uint32_t bus_clock_hz = 0;
        bus_clock_hz = timer_get_bus_clock(timer_num);
        prescaler = timer_calc_prescaler((uint32_t)bus_clock_hz,
        		TimerConfigNode->cnt_period_us,
				PRESCALER_MAX);
        res = timer_calc_registers(TimerConfigNode->period_ms, TimerConfigNode->period_us, TimerConfigNode->period_ns,
                                 bus_clock_hz, prescaler, &out_load, 0xFFFFFFFF);
        if(res) {
            TimerItem_t* node = NULL;
            node = TimerGetNode(timer_num);
            // HAL_TIM_IRQHandler(&node->timer_h);

            TIM_MasterConfigTypeDef sMasterConfig = {0};
            TIM_ClockConfigTypeDef sClockSourceConfig = {0};
            TIM_TypeDef* TimerInstanceNode = timer_get_ptr(timer_num);
            if(TimerInstanceNode && node) {
                node->int_cnt = 0;
                node->timer_h.Instance = TimerInstanceNode;
                node->timer_h.Init.Prescaler = prescaler;
                node->timer_h.Init.CounterMode = TIM_COUNTERMODE_UP;
                node->timer_h.Init.Period = out_load;
                node->timer_h.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
                node->timer_h.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
                if(HAL_OK == HAL_TIM_Base_Init(&node->timer_h)) {
                    res = true;
                    LOG_INFO(TIMER, "%u InitOk", timer_num);
                }

                sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
                if(HAL_TIM_ConfigClockSource(&node->timer_h, &sClockSourceConfig) != HAL_OK) {
                    res = false;
                    LOG_ERROR(TIMER, "%u SetClkSrcErr", timer_num);
                }

                sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
                sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
                if(HAL_TIMEx_MasterConfigSynchronization(&node->timer_h, &sMasterConfig) != HAL_OK) {
                    res = false;
                    LOG_ERROR(TIMER, "%u SetSyncErr", timer_num);
                }

                HAL_StatusTypeDef ret;
                /* prevent timer interrupt at timer start */
                node->timer_h.Instance->EGR |= TIM_EGR_UG;
                __NOP();
                __NOP();
                __NOP();
                node->timer_h.Instance->SR = 0; //&= ~TIM_FLAG_UPDATE;
                ret = HAL_TIM_Base_Start_IT(&node->timer_h);
                if(HAL_OK == ret) {
                    res = true;
                    node->int_cnt = 0;
                    LOG_INFO(TIMER, "%u StartOk", timer_num);
                } else {
                    res = false;
                    LOG_ERROR(TIMER, "%u StartErr", timer_num);
                }
            } else {
                res = false;
            }
        } else {
#ifdef HAS_LOG
            LOG_ERROR(TIMER, "CalcPscLdErr");
#endif
        }
    }

    return res;
}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* timer_baseHandle) {
#ifdef HAS_TIMER1
    if(TIM1 == timer_baseHandle->Instance) {
        __HAL_RCC_TIM1_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 10, 10);
        HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);

        HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 10, 10);
        HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

        HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 10, 10);
        HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);

        HAL_NVIC_SetPriority(TIM1_CC_IRQn, 10, 10);
        HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);
    }
#endif

#ifdef HAS_TIMER2
    if(timer_baseHandle->Instance == TIM2) {
        __HAL_RCC_TIM2_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM2_IRQn, 10, 10);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
#endif

#ifdef HAS_TIMER3
    if(timer_baseHandle->Instance == TIM3) {
        __HAL_RCC_TIM3_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM3_IRQn, 10, 10);
        HAL_NVIC_EnableIRQ(TIM3_IRQn);
    }
#endif

#ifdef HAS_TIMER4
    if(timer_baseHandle->Instance == TIM4) {
        __HAL_RCC_TIM4_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM4_IRQn, 10, 10);
        HAL_NVIC_EnableIRQ(TIM4_IRQn);
    }
#endif

#ifdef HAS_TIMER5
    if(TIM5 == timer_baseHandle->Instance) {
        __HAL_RCC_TIM5_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM5_IRQn, 1, 1);
        HAL_NVIC_EnableIRQ(TIM5_IRQn);
    }
#endif

#ifdef HAS_TIMER9
    if(timer_baseHandle->Instance == TIM9) {
        __HAL_RCC_TIM9_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 10, 10);
        HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
    }
#endif

#ifdef HAS_TIMER10
    if(timer_baseHandle->Instance == TIM10) {
        __HAL_RCC_TIM10_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 10, 10);
        HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
    }
#endif

#ifdef HAS_TIMER11
    if(timer_baseHandle->Instance == TIM11) {
        __HAL_RCC_TIM11_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 10, 10);
        HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
    }
#endif
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* timer_baseHandle) {
#ifdef TIM1
    if(timer_baseHandle->Instance == TIM1) {
        __HAL_RCC_TIM1_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(TIM1_CC_IRQn);
    }
#endif

#ifdef HAS_TIMER2
    if(timer_baseHandle->Instance == TIM2) {
        __HAL_RCC_TIM2_CLK_DISABLE();

        HAL_NVIC_DisableIRQ(TIM2_IRQn);
    }
#endif

#ifdef HAS_TIMER3
    if(timer_baseHandle->Instance == TIM3) {
        __HAL_RCC_TIM3_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(TIM3_IRQn);
    }
#endif

#ifdef HAS_TIMER4
    if(timer_baseHandle->Instance == TIM4) {
        __HAL_RCC_TIM4_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(TIM4_IRQn);
    }
#endif

#ifdef HAS_TIMER5
    if(timer_baseHandle->Instance == TIM5) {
        __HAL_RCC_TIM5_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(TIM5_IRQn);
    }
#endif

#ifdef HAS_TIMER9
    if(timer_baseHandle->Instance == TIM9) {
        __HAL_RCC_TIM9_CLK_DISABLE();
    }
#endif

#ifdef HAS_TIMER10
    if(timer_baseHandle->Instance == TIM10) {
        __HAL_RCC_TIM10_CLK_DISABLE();
    }
#endif

#ifdef HAS_TIMER11
    if(timer_baseHandle->Instance == TIM11) {
        __HAL_RCC_TIM11_CLK_DISABLE();
    }
#endif
}

int8_t TimInstance2Num(TIM_TypeDef* Instance) {
    int8_t timer_num = -1;
#ifdef TIM1
    if(TIM1 == Instance) {
        timer_num = 1;
    }
#endif /**/

#ifdef TIM2
    if(TIM2 == Instance) {
        timer_num = 2;
    }
#endif /**/

#ifdef TIM3
    if(TIM3 == Instance) {
        timer_num = 3;
    }
#endif /**/

#ifdef TIM4
    if(TIM4 == Instance) {
        timer_num = 4;
    }
#endif /**/

#ifdef TIM5
    if(TIM5 == Instance) {
        timer_num = 5;
    }
#endif /**/

#ifdef TIM6
    if(TIM6 == Instance) {
        timer_num = 6;
    }
#endif /**/

#ifdef TIM7
    if(TIM7 == Instance) {
        timer_num = 7;
    }
#endif /**/

#ifdef TIM8
    if(TIM8 == Instance) {
        timer_num = 8;
    }
#endif /**/

#ifdef TIM9
    if(TIM9 == Instance) {
        timer_num = 9;
    }
#endif /**/

#ifdef TIM10
    if(TIM10 == Instance) {
        timer_num = 10;
    }
#endif /**/

#ifdef TIM11
    if(TIM11 == Instance) {
        timer_num = 11;
    }
#endif /**/

    return timer_num;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t timer_num = TimInstance2Num(htim->Instance);
        TimerItem_t* TimerNode = TimerGetNode(timer_num);
        if(TimerNode) {
            TimerNode->int_cnt++;
            if(TIMER_STACK_NUM == timer_num) {
                sampling_timer_interrupt_handler();
            }
            if(TIMER_MS_TICK_NUM == timer_num) {
                HAL_IncTick();
#ifdef HAS_SOFTWARE_TIMER
                sw_timer_proc();
#endif /*HAS_SOFTWARE_TIMER*/

#if defined(HAS_SYSTICK) && defined(HAS_SYSTICK_INT)
                //SysTickIntHandler();
#endif /**/
            }
        }
    }
}

void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t timer_num = TimInstance2Num(htim->Instance);
        TimerItem_t* TimerNode = TimerGetNode(timer_num);
        if(TimerNode) {
        }
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t timer_num = TimInstance2Num(htim->Instance);
        TimerItem_t* TimerNode = TimerGetNode(timer_num);
        if(TimerNode) {
            TimerNode->ic_cap_cnt++;
        }
    }
}

void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t timer_num = TimInstance2Num(htim->Instance);
        TimerItem_t* TimerNode = TimerGetNode(timer_num);
        if(TimerNode) {
        }
    }
}

void HAL_TIM_TriggerCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t timer_num = TimInstance2Num(htim->Instance);
        TimerItem_t* TimerNode = TimerGetNode(timer_num);
        if(TimerNode) {
        }
    }
}

void HAL_TIM_TriggerHalfCpltCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t timer_num = TimInstance2Num(htim->Instance);
        TimerItem_t* TimerNode = TimerGetNode(timer_num);
        if(TimerNode) {
        }
    }
}

void HAL_TIM_ErrorCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t timer_num = TimInstance2Num(htim->Instance);
        TimerItem_t* TimerNode = TimerGetNode(timer_num);
        if(TimerNode) {
            TimerNode->error_cnt++;
        }
    }
}
