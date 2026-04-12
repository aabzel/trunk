#include "timer_mcal.h"

#include <stddef.h>
#include <string.h>

#include "bit_utils.h"
#include "clock_custom_const.h"
#include "code_generator.h"
#include "data_utils.h"
#include "float_utils.h"
#include "hal_diag.h"
#include "hal_mcal.h"
#include "log.h"
#include "std_includes.h"
#include "stm32f4xx_hal.h"
#include "sys_config.h"
#include "timer_custom.h"
#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_CLOCK
#include "clock_mcal.h"
#endif

#ifdef HAS_SOFTWARE_TIMER
#include "software_timer_isr.h"
#endif /**/

#ifdef HAS_SYSTICK
#include "systick_mcal.h"
#endif

uint32_t TimerChannelToHalChannel(TimerCapComChannel_t channel) {
    uint32_t hal_channel = 0;
    switch(channel) {
    case 1:
        hal_channel = TIM_CHANNEL_1;
        break;
    case 2:
        hal_channel = TIM_CHANNEL_2;
        break;
    case 3:
        hal_channel = TIM_CHANNEL_3;
        break;
    case 4:
        hal_channel = TIM_CHANNEL_4;
        break;
    default:
        break;
    }
    return hal_channel;
}

#if 0
uint8_t timer_get_width(uint32_t timer_base) {
    uint8_t width = 0;
    return width;
}
#endif

static const int32_t Timer1IRQs[] = {TIM1_CC_IRQn, TIM1_TRG_COM_TIM11_IRQn, TIM1_UP_TIM10_IRQn, TIM1_BRK_TIM9_IRQn};

static const TimerInfo_t TimerInfo[] = {
#ifdef TIM1
    {
        .bitness = 16,
        .valid = true,
        .clock_bus = CLOCK_BUS_APB2,
        .num = 1,
        .TIMx = TIM1,
        .irq_n = Timer1IRQs,
        .irq_cnt = ARRAY_SIZE(Timer1IRQs),
        .Comparators =
            {
                .compare1 = 1,
                .compare2 = 1,
                .compare3 = 1,
                .compare4 = 1,
            },
    },
#endif

#ifdef TIM2
    {
        .bitness = 32,
        .valid = true,
        .clock_bus = CLOCK_BUS_APB1,
        .num = 2,
        .TIMx = TIM2,
        .Comparators =
            {
                .compare1 = 1,
                .compare2 = 1,
                .compare3 = 1,
                .compare4 = 1,
            },
    },
#endif

#ifdef TIM3
    {
        .bitness = 16,
        .valid = true,
        .clock_bus = CLOCK_BUS_APB1,
        .num = 3,
        .TIMx = TIM3,
        .Comparators =
            {
                .compare1 = 1,
                .compare2 = 1,
                .compare3 = 1,
                .compare4 = 1,
            },
    },
#endif

#ifdef TIM4
    {
        .valid = true,
        .bitness = 16,
        .clock_bus = CLOCK_BUS_APB1,
        .num = 4,
        .TIMx = TIM4,
        .Comparators =
            {
                .compare1 = 1,
                .compare2 = 1,
                .compare3 = 1,
                .compare4 = 1,
            },
    },
#endif

#ifdef TIM5
    {
        .valid = true,
        .clock_bus = CLOCK_BUS_APB1,
        .num = 5,
        .bitness = 32,
        .TIMx = TIM5,
        .Comparators =
            {
                .compare1 = 1,
                .compare2 = 1,
                .compare3 = 1,
                .compare4 = 1,
            },
    },
#endif

#ifdef TIM6
    {
        .bitness = 16,
        .valid = true,
        .clock_bus = CLOCK_BUS_APB1,
        .num = 6,
        .TIMx = TIM6,
        .Comparators =
            {
                .compare1 = 0,
                .compare2 = 0,
                .compare3 = 0,
                .compare4 = 0,
            },
    },
#endif

#ifdef TIM7
    {
        .bitness = 16,
        .valid = true,
        .clock_bus = CLOCK_BUS_APB1,
        .num = 7,
        .TIMx = TIM7,
        .Comparators =
            {
                .compare1 = 0,
                .compare2 = 0,
                .compare3 = 0,
                .compare4 = 0,
            },
    },
#endif

#ifdef TIM8
    {
        .bitness = 16,
        .valid = true,
        .clock_bus = CLOCK_BUS_APB2,
        .num = 8,
        .TIMx = TIM8,
        .Comparators =
            {
                .compare1 = 1,
                .compare2 = 1,
                .compare3 = 1,
                .compare4 = 1,
            },
        /*1 2 3 4   */
    },
#endif

#ifdef TIM9
    {
        .bitness = 16,
        .valid = true,
        .clock_bus = CLOCK_BUS_APB2,
        .num = 9,
        .TIMx = TIM9,
        .Comparators =
            {
                .compare1 = 1,
                .compare2 = 1,
            },
        /*1 2*/
    },
#endif

#ifdef TIM10
    {
        .bitness = 16,
        .valid = true,
        .clock_bus = CLOCK_BUS_APB2,
        .num = 10,
        .TIMx = TIM10,
        .Comparators =
            {
                .compare1 = 1,
                .compare2 = 1,
            },
    },
#endif

#ifdef TIM11
    {
        .bitness = 16,
        .valid = true,
        .clock_bus = CLOCK_BUS_APB2,
        .num = 11,
        .TIMx = TIM11,
        .Comparators =
            {
                .compare1 = 1,
                .compare2 = 1,
            },
    },
#endif

#ifdef TIM12
    {
        .bitness = 16,
        .valid = true,
        .clock_bus = CLOCK_BUS_APB1,
        .num = 12,
        .TIMx = TIM12,
        .Comparators =
            {
                .compare1 = 1,
                .compare2 = 1,
            },
    },
#endif

#ifdef TIM13
    {
        .bitness = 16,
        .valid = true,
        .clock_bus = CLOCK_BUS_APB1,
        .num = 13,
        .TIMx = TIM13,
        .Comparators =
            {
                .compare1 = 1,
                .compare2 = 1,
            },
    },
#endif

#ifdef TIM14
    {
        .bitness = 16,
        .valid = true,
        .clock_bus = CLOCK_BUS_APB1,
        .num = 14,
        .TIMx = TIM14,
        .Comparators =
            {
                .compare1 = 1,
                .compare2 = 1,
            },
    },
#endif
};

static const TimerChannelInfo_t TimerChannelInfo[] = {
    {
        .timer_num = 9,
        .out_channel = 1,
        .Pad =
            {
                .port = PORT_E,
                .pin = 5,
            },
        .valid = true,
    },
    {
        .timer_num = 9,
        .out_channel = 2,
        .Pad =
            {
                .port = PORT_E,
                .pin = 6,
            },
        .valid = true,
    },
    {
        .timer_num = 10,
        .out_channel = 2,
        .Pad =
            {
                .port = PORT_F,
                .pin = 6,
            },
        .valid = true,
    },
    {
        .timer_num = 11,
        .out_channel = 1,
        .Pad =
            {
                .port = PORT_F,
                .pin = 7,
            },
        .valid = true,
    },
    {
        .timer_num = 13,
        .out_channel = 1,
        .Pad =
            {
                .port = PORT_F,
                .pin = 8,
            },
        .valid = true,
    },
};

TimerChannelInfo_t* TimerChannelGetNode(const uint8_t timer_num, const uint8_t channel) {
    uint32_t i = 0;
    TimerChannelInfo_t* ChannelInfo = NULL;
    uint32_t cnt = ARRAY_SIZE(TimerChannelInfo);
    for(i = 0; i < cnt; i++) {
        if(TimerChannelInfo[i].valid) {
            if(timer_num == TimerChannelInfo[i].timer_num) {
                if(channel == TimerChannelInfo[i].out_channel) {
                    ChannelInfo = &TimerChannelInfo[i];
                    break;
                }
            }
        }
    }
    return ChannelInfo;
}

uint32_t timer_mcu_cnt_get(void) {
    uint32_t cnt = ARRAY_SIZE(TimerInfo);
    return cnt;
}

TimerInfo_t* TimerGetInfo(const uint8_t num) {
    TimerInfo_t* Info = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(TimerInfo);
    for(i = 0; i < cnt; i++) {
        if(num == TimerInfo[i].num) {
            if(TimerInfo[i].valid) {
                Info = &TimerInfo[i];
                break;
            }
        }
    }
    return Info;
}
int8_t TimInstance2Num(const TIM_TypeDef* const TIMERx) {
    int8_t num = -1;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(TimerInfo);
    for(i = 0; i < cnt; i++) {
        if(TIMERx == TimerInfo[i].TIMx) {
            num = (int8_t)TimerInfo[i].num;
            break;
        }
    }
    return num;
}

TIM_TypeDef* timer_get_ptr(const uint8_t num) {
    TIM_TypeDef* TIMx = NULL;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        TIMx = Info->TIMx;
    }
    return TIMx;
}

uint8_t timer_bitness_get(uint8_t num) {
    uint8_t bitness = 0;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        bitness = Info->bitness;
    }
    return bitness;
}

uint32_t timer_period_get(uint8_t num) {
    uint32_t timer_period32 = 0;
    TIM_TypeDef* TIMx = timer_get_ptr(num);
    if(TIMx) {
        timer_period32 = TIMx->ARR;
    }
    return timer_period32;
}

#if 0
uint32_t timer_get_cc_val( uint8_t  num,   TimerCapComChannel_t chaneel  ){
	return 0;
}

bool timer_set_cc_val( uint8_t num, TimerCapComChannel_t channel,
		uint32_t cc_value, bool int_on){
	return false;
}


bool timer_set_status( uint8_t num,   bool on_off){
	return 0;
}

uint8_t timer_get_bitness(  uint8_t num){
	return 0;
}
double timer_get_tick_s(uint8_t  num){
	return 0.0;
}
#endif

ClockBus_t timer_clock_bus_name_get(const uint8_t num) {
    ClockBus_t clock_bus_name = CLOCK_BUS_UNDEF;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        clock_bus_name = Info->clock_bus;
    }
    return clock_bus_name;
}

int32_t timer_bus_clock_get(uint8_t num) {
    int32_t clock_hz = -1;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        uint32_t pclk = 0;
        switch(Info->clock_bus) {
        case CLOCK_BUS_APB1:
            pclk = HAL_RCC_GetPCLK1Freq();
            break;
        case CLOCK_BUS_APB2:
            pclk = HAL_RCC_GetPCLK2Freq();
            break;
        default:
            LOG_ERROR(TIMER, "NoBusClock");
            break;
        }
        clock_hz = 2 * pclk;
    }
    return clock_hz;
}

#if 0
bool timer_frequency_get(uint8_t num, double * const frequency){
//double timer_frequency_get(uint8_t num) {
    bool res = false ;
    double frequency_hz = 0.0;
    TIM_TypeDef* TIMx = timer_get_ptr(num);
    if(TIMx) {
        int32_t bus_clock = timer_bus_clock_get(num);
        frequency_hz = ((double)bus_clock) / (((double)TIMx->ARR + 1) * ((double)TIMx->PSC + 1));
        *frequency=frequency_hz;
        res = true;
    }
    return res;
}
#endif

bool timer_get_status(uint8_t num) {
    bool res = true;
    uint8_t status = 0xFF;
    uint32_t timer_cr1 = 0;
    TIM_TypeDef* TIMx = timer_get_ptr(num);
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

static bool timer_channel_out_pwm_is_work_ll(const TimerRegCCMR_t* const pRegChan) {
    bool res = false;
    if(TIM_CC1S_OUTPUT_COMPARE == pRegChan->CCxS) {
        switch(pRegChan->OCxM) {
        case TIM_OC1_MODE_PWM1:
            res = true;
            break;
        case TIM_OC1_MODE_PWM2:
            res = true;
            break;
        case TIM_OC1_MODE_FROZEN:
            res = false;
            break;
        case TIM_OC1_MODE_ACTIVE_ON_MATCH:
            res = false;
            break;
        case TIM_OC1_MODE_INACTIVE_ON_MATCH:
            res = false;
            break;
        case TIM_OC1_MODE_TOGGLE_ON_MATCH:
            res = false;
            break;
        case TIM_OC1_MODE_FORCE_INACTIVE:
            res = false;
            break;
        case TIM_OC1_MODE_FORCE_ACTIVE:
            res = false;
            break;
        default:
            res = false;
            break;
        }
    }
    return res;
}

bool timer_channel_is_work(const uint8_t num, const TimerCapComChannel_t channel) {
    bool res = false;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        TimerRegCR1_t CR1;
        CR1.dword = Info->TIMx->CR1;

        TimerRegCCMR1_t CCMR1;
        CCMR1.dword = Info->TIMx->CCMR1;

        TimerRegCCMR2_t CCMR2;
        CCMR2.dword = Info->TIMx->CCMR2;

        TimerRegCCER_t CCER;
        CCER.dword = Info->TIMx->CCER;

        if(TIMER_CEN_COUNTER_ENABLED == CR1.CEN) {
            switch(channel) {
            case TIMER_CC_CHAN_1: {
                res = timer_channel_out_pwm_is_work_ll(&CCMR1.CH1);
                res = CCER.CC1E && res;
            } break;

            case TIMER_CC_CHAN_2: {
                res = timer_channel_out_pwm_is_work_ll(&CCMR1.CH2);
                res = CCER.CC2E && res;
            } break;

            case TIMER_CC_CHAN_3: {
                res = timer_channel_out_pwm_is_work_ll(&CCMR2.CH3);
                res = CCER.CC3E && res;
            } break;

            case TIMER_CC_CHAN_4: {
                res = timer_channel_out_pwm_is_work_ll(&CCMR2.CH4);
                res = CCER.CC4E && res;
            } break;
            default: {
                res = false;
            } break;
            }
        }
    }
    return res;
}

uint32_t timer_prescaler_get(uint8_t num) {
    bool res = true;
    uint32_t timer_prescaler = 0xFF;
    uint32_t timer_prescaler32 = 0;

    TIM_TypeDef* TIMx = timer_get_ptr(num);
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

uint32_t timer_get_auto_reload(uint8_t num) {
    uint32_t auto_reload = 0;
    TIM_TypeDef* TIMx = timer_get_ptr(num);
    if(TIMx) {
        auto_reload = TIMx->ARR;
    }

    return auto_reload;
}

uint32_t timer_counter_to_us(uint8_t num, uint32_t counter) {
    uint32_t up_time_us = counter;
    return up_time_us;
}

uint32_t timer_counter_get(uint8_t num) {
    uint32_t timer_cnt32 = 0;
    TIM_TypeDef* TIMx = timer_get_ptr(num);
    if(TIMx) {
        timer_cnt32 = TIMx->CNT;
    }

    return timer_cnt32;
}

bool timer_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret = HAL_ERROR;
        if(on_off) {
            ret = HAL_TIM_Base_Start_IT(&Node->Handle);
            // ret = HAL_TIM_Base_Start(&Node->Handle);
            // HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
        } else {
            ret = HAL_TIM_Base_Stop_IT(&Node->Handle);
            // ret = HAL_TIM_Base_Stop(&Node->Handle);
        }
        res = HAL_retToRes(ret);
    }
    return res;
}

bool timer_channel_ctrl(uint8_t num, TimerCapComChannel_t channel, bool on_off) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        res = timer_is_valid_channel(num, channel);
        if(res) {
            res = false;

#ifdef HAS_HAL_TIM_PWM
            uint32_t hal_channel = TimerChannelToHalChannel(channel);
            HAL_StatusTypeDef ret = HAL_ERROR;
            if(on_off) {
                res = HAL_TIM_CHANNEL_STATE_READY == TIM_CHANNEL_STATE_GET(&Node->Handle, hal_channel);
                if(res) {
                    ret = HAL_TIM_PWM_Start_IT(&Node->Handle, hal_channel);
                } else {
#ifdef HAS_HAL_DIAG
                    LOG_ERROR(TIMER, "TIM%u,NotReady", num);
#endif
                    res = true;
                }
            } else {
                ret = HAL_TIM_PWM_Stop_IT(&Node->Handle, hal_channel);
            }
            res = HAL_retToRes(ret);

            if(!res) {
#ifdef HAS_HAL_DIAG
                LOG_ERROR(TIMER, "%u=%s", ret, HalStatusToStr(ret));
#endif
            }
#endif /*HAS_HAL_TIM_PWM*/
        }
    }
    return res;
}

bool timer_period_set_ll(TimerHandle_t* const Node, const uint32_t period) {
    bool res = false;
    if(Node) {
        /*auto-reload register*/
        Node->Handle.Instance->ARR = period;
        res = true;
    }
    return res;
}

bool timer_period_set(uint8_t num, uint32_t period) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        res = timer_period_set_ll(Node, period);
    }
    return res;
}

#if 0
uint64_t timer_period_get_us(uint8_t num) {
    uint64_t real_period_us = 0;
    uint32_t prescaler = 0;
    uint32_t reload = 0;
    TimerHandle_t* Node = NULL;
    Node = TimerGetNode(num);
    if(Node) {
        double fck = (double)timer_bus_clock_get(num);
        double tf = 1.0 / fck;
        prescaler = Node->Handle.Instance->PSC;
        reload = Node->Handle.Instance->ARR;
        double t_psc = tf * ((double)prescaler);

        real_period_us = (uint64_t)(t_psc * ((double)reload)) * 1000000.0;
    }
    return real_period_us;
}

double timer_period_get_s(uint8_t num) {
    double real_period_s = 0;
    uint32_t prescaler = 0;
    uint32_t reload = 0;
    TimerHandle_t* Node = NULL;
    Node = TimerGetNode(num);
    if(Node) {
        double fck = (double)timer_bus_clock_get(num);
        double tf = 1.0 / fck;
        prescaler = Node->Handle.Instance->PSC;
        reload = Node->Handle.Instance->ARR;
        double t_psc = tf * ((double)prescaler);

        real_period_s = (t_psc * ((double)reload));
    }
    return real_period_s;
}

uint64_t timer_get_us(uint8_t num) {
    uint64_t up_time_us = 0, int_cnt = 0, cnt_us = 0;
    uint64_t period_us = MSEC_2_USEC(TIMER_US_PERIOD_MS);
    TimerHandle_t* Node = NULL;
    Node = TimerGetNode(num);
    if(Node) {
        int_cnt = Node->int_cnt;
        cnt_us = __HAL_TIM_GET_COUNTER(&(Node->Handle));
        up_time_us = cnt_us + int_cnt * period_us;
    }
    return up_time_us;
}

uint32_t timer_get_ms(uint8_t num) {
    uint32_t up_time_ms = 0;
    //uint32_t int_cnt = 0, cnt_ms = 0;
    TimerHandle_t* Node = NULL;
#ifdef TIMER_MS_TICK_NUM
    Node = TimerGetNode(num);
#endif /*TIM2*/

    if(Node) {
        //cnt_ms = __HAL_TIM_GET_COUNTER(&(Node->Handle))/2;
        //int_cnt = Node->int_cnt;
        //up_time_ms = cnt_ms + TIMER_MS_PERIOD_MS * (int_cnt/2);

        up_time_ms =  Node->int_cnt;
    }

    return up_time_ms;
}

#endif
TimerDir_t timer_dir_get(uint8_t num) {
    TimerDir_t dir = TIMER_CNT_DIR_UNDEF;
    TIM_TypeDef* TIMx = timer_get_ptr(num);
    if(TIMx) {
        uint32_t timer_cr1 = 0;
        timer_cr1 = TIMx->CR1;
        if(BIT_4 == (BIT_4 & timer_cr1)) {
            dir = TIMER_CNT_DIR_DOWN;
        } else {
            dir = TIMER_CNT_DIR_UP;
        }
    }
    return dir;
}

bool timer_out_channel_pad_get(uint8_t num, TimerCapComChannel_t channel, Pad_t* const Pad) {
    bool res = false;
    TimerChannelInfo_t* Channel = TimerChannelGetNode(num, channel);
    if(Channel) {
        *Pad = Channel->Pad;
        res = true;
    }
    return res;
}

bool timer_is_valid_channel(const uint8_t num, const uint8_t channel) {
    bool res = false;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        uint8_t comparator_mask = (1U << channel);
        if(comparator_mask == (comparator_mask & Info->Comparators.byte)) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

bool timer_counter_set(uint8_t num, uint32_t value) {
    bool res = false;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        Info->TIMx->CNT = value;
        res = true;
    }
    return res;
}

bool timer_compare_set(uint8_t num, TimerCapComChannel_t channel, uint32_t compare_value) {
    bool res = false;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        res = timer_is_valid_channel(num, channel);
        if(res) {
            switch(channel) {
            case TIMER_CC_CHAN_1: {
                Info->TIMx->CCR1 = compare_value;
                res = true;
            } break;
            case TIMER_CC_CHAN_2: {
                Info->TIMx->CCR2 = compare_value;
                res = true;
            } break;
            case TIMER_CC_CHAN_3: {
                Info->TIMx->CCR3 = compare_value;
                res = true;
            } break;
            case TIMER_CC_CHAN_4: {
                Info->TIMx->CCR4 = compare_value;
                res = true;
            } break;
            default:
                res = false;
                break;
            }
        }
    }
    return res;
}

uint32_t timer_cc_val_get(const uint8_t num, const TimerCapComChannel_t channel) {
    uint32_t cap_com_val = 0;
    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        if(Info->TIMx) {
            switch(channel) {
            case TIMER_CC_CHAN_1: {
                cap_com_val = Info->TIMx->CCR1;
            } break;
            case TIMER_CC_CHAN_2: {
                cap_com_val = Info->TIMx->CCR2;
            } break;
            case TIMER_CC_CHAN_3: {
                cap_com_val = Info->TIMx->CCR3;
            } break;
            case TIMER_CC_CHAN_4: {
                cap_com_val = Info->TIMx->CCR4;
            } break;
            default:
                cap_com_val = 0;
                break;
            }
        }
    }
    return cap_com_val;
}

uint32_t timer_ccc_val_get(uint8_t num, TimerCapComChannel_t channel) {
    uint32_t ccc_val = timer_cc_val_get(num, channel);
    return ccc_val;
}

static bool timer_config_to_init(uint32_t prescaler, uint32_t out_load, TIM_Base_InitTypeDef* const Init) {
    bool res = false;
    if(Init) {
        if(out_load) {
            Init->RepetitionCounter = 0;
            Init->Prescaler = prescaler;
            Init->CounterMode = TIM_COUNTERMODE_UP;
            Init->Period = out_load;
            Init->ClockDivision = TIM_CLOCKDIVISION_DIV1;
            Init->AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
            res = true;
        }
    }
    return res;
}

static bool timer_init_interrupts_ll(TimerInfo_t* Info) {
    bool res = false;
    if(Info->irq_cnt) {
        if(Info->irq_n) {
            uint32_t i = 0;
            for(i = 0; i < Info->irq_cnt; i++) {
                HAL_NVIC_SetPriority(Info->irq_n[i], 15, 15);
                HAL_NVIC_EnableIRQ(Info->irq_n[i]);
            }
            res = true;
        }
    }
    return res;
}

static bool timer_errata_fix(TimerHandle_t* const Node) {
    bool res = false;
    /* prevent timer interrupt at timer start */
    Node->Handle.Instance->EGR |= TIM_EGR_UG;
    __NOP();
    __NOP();
    __NOP();
    Node->Handle.Instance->SR = 0; //&= ~TIM_FLAG_UPDATE;

    return res;
}

bool timer_init_custom(void) {
    bool res = false;
    LOG_INFO(TIMER, "MaxTIMnum:%u", TIMER_MAX_NUM);
    return res;
}

bool timer_is_valid(uint8_t num) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        const TimerConfig_t* Config = TimerGetConfig(num);
        if(Config) {
            res = true;
        }
    }

    TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        res = IS_TIM_MASTER_INSTANCE(Info->TIMx);
    }

    return res;
}

bool timer_init_one(uint8_t num) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(TIMER, "%u Init", num);
#endif
    TimerHandle_t* Node = TimerGetNode(num);
    const TimerConfig_t* Config = TimerGetConfig(num);
    TimerInfo_t* Info = TimerGetInfo(num);

    if(Info) {
#ifdef HAS_TIMER_DIAG
        LOG_WARNING(TIMER, "%s", TimerInfoToStr(Info));
#endif
        if(Config) {
#ifdef HAS_TIMER_DIAG
            LOG_WARNING(TIMER, "%s", TimerConfigToStr(Config));
#endif
            res = TimerIsValidConfig(Config);
            if(res) {
                if(Node) {
                    Node->TIMx = Info->TIMx;
                    res = true;
                }
            }
        }
    }

    if(res) {
        uint32_t out_load = 0;

        uint32_t prescaler = 0;

        uint32_t bus_clock_hz = 0;
        bus_clock_hz = timer_bus_clock_get(num);
        prescaler = timer_calc_prescaler((uint32_t)bus_clock_hz, Config->cnt_period_ns, TIMER_PRESCALER_MAX) - 1;
        res = timer_calc_registers(Config->period_s, bus_clock_hz, prescaler, &out_load, 0xFFFFFFFF);
        if(res) {
            // HAL_TIM_IRQHandler(&Node->Handle);

            TIM_MasterConfigTypeDef sMasterConfig = {0};
            TIM_ClockConfigTypeDef sClockSourceConfig = {0};

            if(Info->TIMx) {
                if(Config->interrupt_on) {
                    res = timer_init_interrupts_ll(Info);
                }

                Node->int_cnt = 0;
                Node->Handle.Instance = Info->TIMx;
                res = timer_config_to_init(prescaler, out_load, &Node->Handle.Init);
                res = timer_base_clock_ctrl(num, true);

                if(HAL_OK == HAL_TIM_Base_Init(&Node->Handle)) {
                    res = true;
#ifdef HAS_LOG
                    LOG_DEBUG(TIMER, "%uInitOk", num);
#endif
                }

                sClockSourceConfig.ClockFilter = 0;
                sClockSourceConfig.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
                sClockSourceConfig.ClockPolarity = TIM_CLOCKPOLARITY_RISING;
                sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
                if(HAL_TIM_ConfigClockSource(&Node->Handle, &sClockSourceConfig) != HAL_OK) {
                    res = false;
#ifdef HAS_LOG
                    LOG_ERROR(TIMER, "%u SetClkSrcErr", num);
#endif
                }

                sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
                sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
                if(HAL_TIMEx_MasterConfigSynchronization(&Node->Handle, &sMasterConfig) != HAL_OK) {
                    res = false;
#ifdef HAS_LOG
                    LOG_ERROR(TIMER, "%u SetSyncErr", num);
#endif
                }

                res = timer_errata_fix(Node);

                res = timer_ctrl(num, Config->on_off);
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

static bool timer_base_clock_on(const uint8_t num) {
    bool res = false;
    switch(num) {
    case 1: {
        __HAL_RCC_TIM1_CLK_DISABLE();
        res = true;
    } break;
    case 2: {
        __HAL_RCC_TIM2_CLK_DISABLE();
        res = true;
    } break;
    case 3: {
        __HAL_RCC_TIM3_CLK_DISABLE();
        res = true;
    } break;
    case 4: {
        __HAL_RCC_TIM4_CLK_DISABLE();
        res = true;
    } break;
    case 5: {
        __HAL_RCC_TIM5_CLK_DISABLE();
        res = true;
    } break;
    case 6: {
        __HAL_RCC_TIM6_CLK_DISABLE();
        res = true;
    } break;
    case 7: {
        __HAL_RCC_TIM7_CLK_DISABLE();
        res = true;
    } break;
    case 8: {
        __HAL_RCC_TIM8_CLK_DISABLE();
        res = true;
    } break;
    case 9: {
        __HAL_RCC_TIM9_CLK_DISABLE();
        res = true;
    } break;
    case 0: {
        __HAL_RCC_TIM10_CLK_DISABLE();
        res = true;
    } break;
    case 11: {
        __HAL_RCC_TIM11_CLK_DISABLE();
        res = true;
    } break;
    case 12: {
        __HAL_RCC_TIM12_CLK_DISABLE();
        res = true;
    } break;
    case 13: {
        __HAL_RCC_TIM13_CLK_DISABLE();
        res = true;
    } break;
    case 14: {
        __HAL_RCC_TIM14_CLK_DISABLE();
        res = true;
    } break;
    default:
        res = false;
        break;
    }

    return res;
}

static bool timer_base_clock_off(const uint8_t num) {
    bool res = false;
    switch(num) {
    case 1: {
        __HAL_RCC_TIM1_CLK_ENABLE();
        res = true;
    } break;
    case 2: {
        __HAL_RCC_TIM2_CLK_ENABLE();
        res = true;
    } break;
    case 3: {
        __HAL_RCC_TIM3_CLK_ENABLE();
        res = true;
    } break;
    case 4: {
        __HAL_RCC_TIM4_CLK_ENABLE();
        res = true;
    } break;
    case 5: {
        __HAL_RCC_TIM5_CLK_ENABLE();
        res = true;
    } break;
    case 6: {
        __HAL_RCC_TIM6_CLK_ENABLE();
        res = true;
    } break;
    case 7: {
        __HAL_RCC_TIM7_CLK_ENABLE();
        res = true;
    } break;
    case 8: {
        __HAL_RCC_TIM8_CLK_ENABLE();
        res = true;
    } break;
    case 9: {
        __HAL_RCC_TIM9_CLK_ENABLE();
        res = true;
    } break;
    case 10: {
        __HAL_RCC_TIM10_CLK_ENABLE();
        res = true;
    } break;
    case 11: {
        __HAL_RCC_TIM11_CLK_ENABLE();
        res = true;
    } break;
    case 12: {
        __HAL_RCC_TIM12_CLK_ENABLE();
        res = true;
    } break;
    case 13: {
        __HAL_RCC_TIM13_CLK_ENABLE();
        res = true;
    } break;
    case 14: {
        __HAL_RCC_TIM14_CLK_ENABLE();
        res = true;
    } break;
    default:
        break;
    }

    return res;
}

bool timer_base_clock_ctrl(const uint8_t num, const bool on_off) {
    bool res = false;
    if(on_off) {
        res = timer_base_clock_on(num);
    } else {
        res = timer_base_clock_off(num);
    }
    return res;
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* pHandle) {
#ifdef HAS_TIMER1
    if(TIM1 == pHandle->Instance) {
        __HAL_RCC_TIM1_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 10, 10);
        // HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);

        HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 10, 10);
        // HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

        HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 10, 10);
        // HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);

        HAL_NVIC_SetPriority(TIM1_CC_IRQn, 10, 10);
        // HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);
    }
#endif

#ifdef HAS_TIMER2
    if(pHandle->Instance == TIM2) {
        __HAL_RCC_TIM2_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM2_IRQn, 10, 10);
        //  HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
#endif

#ifdef HAS_TIMER3
    if(pHandle->Instance == TIM3) {
        __HAL_RCC_TIM3_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM3_IRQn, 10, 10);
        //  HAL_NVIC_EnableIRQ(TIM3_IRQn);
    }
#endif

#ifdef HAS_TIMER4
    if(pHandle->Instance == TIM4) {
        __HAL_RCC_TIM4_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
        //  HAL_NVIC_EnableIRQ(TIM4_IRQn);
    }
#endif

#ifdef HAS_TIMER5
    if(TIM5 == pHandle->Instance) {
        __HAL_RCC_TIM5_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM5_IRQn, 1, 1);
        //  HAL_NVIC_EnableIRQ(TIM5_IRQn);
    }
#endif

#ifdef HAS_TIMER6
    if(TIM6 == pHandle->Instance) {
        __HAL_RCC_TIM6_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 1, 1);
        //  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
    }
#endif

#ifdef HAS_TIMER7
    if(TIM7 == pHandle->Instance) {
        __HAL_RCC_TIM7_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM7_IRQn, 1, 1);
        // HAL_NVIC_EnableIRQ(TIM7_IRQn);
    }
#endif

#ifdef HAS_TIMER8
    if(TIM8 == pHandle->Instance) {
        __HAL_RCC_TIM8_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 1, 1);
        //  HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);

        HAL_NVIC_SetPriority(TIM8_TRG_COM_TIM14_IRQn, 1, 1);
        //  HAL_NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn);

        HAL_NVIC_SetPriority(TIM8_CC_IRQn, 1, 1);
        //  HAL_NVIC_EnableIRQ(TIM8_CC_IRQn);

        HAL_NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, 1, 1);
        //  HAL_NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);
    }
#endif

#ifdef HAS_TIMER9
    if(pHandle->Instance == TIM9) {
        __HAL_RCC_TIM9_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 10, 10);
        //   HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
    }
#endif

#ifdef HAS_TIMER10
    if(pHandle->Instance == TIM10) {
        __HAL_RCC_TIM10_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 10, 10);
        //   HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
    }
#endif

#ifdef HAS_TIMER11
    if(pHandle->Instance == TIM11) {
        __HAL_RCC_TIM11_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 10, 10);
        //  HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
    }
#endif
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* pHandle) {
#ifdef TIM1
    if(pHandle->Instance == TIM1) {
        __HAL_RCC_TIM1_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(TIM1_CC_IRQn);
    }
#endif

#ifdef HAS_TIMER2
    if(pHandle->Instance == TIM2) {
        __HAL_RCC_TIM2_CLK_DISABLE();

        HAL_NVIC_DisableIRQ(TIM2_IRQn);
    }
#endif

#ifdef HAS_TIMER3
    if(pHandle->Instance == TIM3) {
        __HAL_RCC_TIM3_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(TIM3_IRQn);
    }
#endif

#ifdef HAS_TIMER4
    if(pHandle->Instance == TIM4) {
        __HAL_RCC_TIM4_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(TIM4_IRQn);
    }
#endif

#ifdef HAS_TIMER5
    if(pHandle->Instance == TIM5) {
        __HAL_RCC_TIM5_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(TIM5_IRQn);
    }
#endif

#ifdef HAS_TIMER9
    if(pHandle->Instance == TIM9) {
        __HAL_RCC_TIM9_CLK_DISABLE();
    }
#endif

#ifdef HAS_TIMER10
    if(pHandle->Instance == TIM10) {
        __HAL_RCC_TIM10_CLK_DISABLE();
    }
#endif

#ifdef HAS_TIMER11
    if(pHandle->Instance == TIM11) {
        __HAL_RCC_TIM11_CLK_DISABLE();
    }
#endif
}
