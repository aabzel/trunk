#include "pwm_drv.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "bit_utils.h"

#ifdef HAS_CLOCK
#include "clock.h"
#endif

#include "float_utils.h"

#ifdef HAS_LOG
#include "log.h"
#endif
//#include "cortex_m4_driver.h"
#include "data_utils.h"
#include "hal_diag.h"
#include "pwm_bsp.h"
#include "pwm_config.h"
#include "pwm_stm32_types.h"
#include "pwm_types.h"
#include "at32f435_437.h"
#include "sys_config.h"
#include "timer_bsp.h"
#include <timer_drv.h>

static const Channal2Code_t Channal2CodeLut[] = {
    {
        .channel = TIM_CHANNEL1,
        .code = TIM_CHANNEL_1,
    },
    {
        .channel = TIM_CHANNEL2,
        .code = TIM_CHANNEL_2,
    },
    {
        .channel = TIM_CHANNEL3,
        .code = TIM_CHANNEL_3,
    },
    {
        .channel = TIM_CHANNEL4,
        .code = TIM_CHANNEL_4,
    },
    {
        .channel = TIM_CHANNELALL,
        .code = TIM_CHANNEL_ALL,
    },
};

static bool is_valid_channel(TimChannel_t channel) {
    bool res = false;
    if(TIM_CHANNEL1 <= channel && (channel <= TIM_CHANNEL4)) {
        res = true;
    }
    return res;
}

static uint32_t Channel2Code(TimChannel_t channel) {
    uint32_t code = 0;
    bool res = is_valid_channel(channel);
    if(res) {
        uint8_t i = 0;
        for(i = 0; i < ARRAY_SIZE(Channal2CodeLut); i++) {
            if(Channal2CodeLut[i].channel == channel) {
                code = Channal2CodeLut[i].code;
                break;
            }
        }
    }
    return code;
}

bool tim_get_compare(uint8_t timer_num, TimChannel_t channel, uint32_t* out_compare) {
    uint32_t ccrx = 0;
    bool res = false;
    TIM_TypeDef* TIMx = tim_get_ptr(timer_num);
    if(TIMx) {
        res = is_valid_channel(channel);
        if(res) {
            switch((uint8_t)channel) {
            case TIM_CHANNEL1:
                ccrx = TIMx->CCR1;
                break;
            case TIM_CHANNEL2:
                ccrx = TIMx->CCR2;
                break;
            case TIM_CHANNEL3:
                ccrx = TIMx->CCR3;
                break;
            case TIM_CHANNEL4:
                ccrx = TIMx->CCR4;
                break;
            }
            if(out_compare) {
                res = true;
                (*out_compare) = ccrx;
            }
        }
    }
    return res;
}

bool tim_set_compare(uint8_t timer_num, TimChannel_t channel, uint32_t compare) {
    bool res = false;
    LOG_DEBUG(PWM, "SetCompare T:%u C:%u Compare:%u", timer_num, channel, compare);
    TIM_TypeDef* TIMx = tim_get_ptr(timer_num);
    if(TIMx) {
        res = is_valid_channel(channel);
        if(res) {
            switch((uint8_t)channel) {
            case TIM_CHANNEL1:
                TIMx->CCR1 = compare;
                break;
            case TIM_CHANNEL2:
                TIMx->CCR2 = compare;
                break;
            case TIM_CHANNEL3:
                TIMx->CCR3 = compare;
                break;
            case TIM_CHANNEL4:
                TIMx->CCR4 = compare;
                break;
            }
            res = true;
        }
    }
    return res;
}

bool pwm_get_duty(uint8_t timer_num, TimChannel_t channel, double* out_duty_cycle) {
    bool res = false;
    TIM_TypeDef* TIMx = tim_get_ptr(timer_num);
    if(TIMx) {
        uint32_t ccrx = 0;
        res = tim_get_compare(timer_num, channel, &ccrx);
        if(res) {
            res = false;
            double duty_cycle = 0.0;
            duty_cycle = 100.0 * ((double)(ccrx) / ((double)TIMx->ARR));
            if(out_duty_cycle) {
                (*out_duty_cycle) = duty_cycle;
                res = true;
            }
        }
    }
    return res;
}

static bool is_valid_duty_cycle(double duty_cycle) {
    bool res = false;
    if(0.0 <= duty_cycle && (duty_cycle <= 100.0)) {
        res = true;
    }
    return res;
}

bool pwm_set_duty(uint8_t timer_num, TimChannel_t channel, double duty_cycle) {
    bool res = false;
    TIM_TypeDef* TIMx = tim_get_ptr(timer_num);
    if(TIMx) {
        res = is_valid_duty_cycle(duty_cycle);
        if(res) {
            uint32_t compare = 0;
            compare = (uint32_t)(((double)TIMx->ARR) * duty_cycle / 100.0);
            LOG_DEBUG(PWM, "T:%u C:%u Compare:%u ARR:%u", timer_num, channel, compare, TIMx->ARR);
            res = is_valid_channel(channel);
            if(res) {
                res = tim_set_compare(timer_num, channel, compare);
            }
        }
    }
    return res;
}

bool pwm_set_phase(uint8_t timer_num, uint32_t phase) {
    bool res = false;
    return res;
}

bool pwm_init_ll(uint8_t ch_id) {
    bool res = false;
    LOG_INFO(PWM, "InitChannelId %u", ch_id);
    const PwmConfig_t* PwmConfigNode = NULL;
    PwmConfigNode = PwmGetCongigNode(ch_id);
    if(PwmConfigNode) {
        PwmHandle_t* PwmNode = PwmGetNode(ch_id);
        if(PwmNode) {
            TimerHandle_t* TimerNode = timer_get_node(PwmConfigNode->timer_num);
            if(TimerNode) {
                HAL_StatusTypeDef ret = HAL_ERROR;

                res = true;
                uint32_t channel_code = Channel2Code(PwmConfigNode->Channel);
                PwmNode->ConfigOC.OCMode = TIM_OCMODE_PWM1;
                PwmNode->ConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
                PwmNode->ConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
                PwmNode->ConfigOC.Pulse = 0;
                ret = HAL_TIM_PWM_ConfigChannel(&TimerNode->timer_h, &PwmNode->ConfigOC, channel_code);
                if(HAL_OK == ret) {
                    res = true;
                } else {
                    res = false;
                }
                res = pwm_set_duty(PwmConfigNode->timer_num, (TimChannel_t)PwmConfigNode->Channel,
                                   (double)PwmConfigNode->duty);
            }
        }
        if(res) {
            if(PwmConfigNode->on) {
                res = pwm_start(PwmConfigNode->timer_num, PwmConfigNode->Channel);
            }
        }
    }
    return res;
}

bool pwm_init(void) {
    bool res = false;
    LOG_INFO(PWM, "Init");
    uint8_t cnt = 0;
    uint8_t channel_id = 0;
    for(channel_id = 0; channel_id <= MAX_PWM_CH; channel_id++) {
        res = pwm_init_ll(channel_id);
        if(res) {
            cnt++;
        }
    }

    if(cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool tim_oc_start(uint8_t timer_num, TimChannel_t channel) {
    bool res = false;
    TimerHandle_t* TimerNode = timer_get_node(timer_num);
    if(TimerNode) {
        HAL_StatusTypeDef ret;
        uint32_t channel_code = Channel2Code(channel);
        ret = HAL_TIM_OC_Start_IT(&TimerNode->timer_h, channel_code);
        if(HAL_OK == ret) {
            LOG_INFO(TIM, "OcStartOk");
            res = true;
        } else {
            LOG_ERROR(TIM, "OcStartErr %s", HalStatus2Str(ret));
            res = false;
        }
    }
    return res;
}

bool tim_oc_stop(uint8_t timer_num, TimChannel_t channel) {
    bool res = false;
    TimerHandle_t* TimerNode = timer_get_node(timer_num);
    if(TimerNode) {
        HAL_StatusTypeDef ret;
        uint32_t channel_code = Channel2Code(channel);
        ret = HAL_TIM_OC_Stop_IT(&TimerNode->timer_h, channel_code);
        if(HAL_OK == ret) {
            LOG_INFO(TIM, "OcStopOk");
            res = true;
        } else {
            LOG_ERROR(TIM, "OcStopErr %s", HalStatus2Str(ret));
            res = false;
        }
    }
    return res;
}

bool pwm_start(uint8_t timer_num, TimChannel_t channel) {
    bool res = false;
    TimerHandle_t* TimerNode = timer_get_node(timer_num);
    if(TimerNode) {
        HAL_StatusTypeDef ret;
        uint32_t channel_code = Channel2Code(channel);
        ret = HAL_TIM_PWM_Start_IT(&TimerNode->timer_h, channel_code);
        if(HAL_OK == ret) {
            LOG_INFO(PWM, "StartOk");
            res = true;
        } else {
            LOG_ERROR(PWM, "StartErr %s", HalStatus2Str(ret));
            res = false;
        }
    }
    return res;
}

bool pwm_stop(uint8_t timer_num, TimChannel_t channel) {
    bool res = false;
    TimerHandle_t* TimerNode = timer_get_node(timer_num);
    if(TimerNode) {
        HAL_StatusTypeDef ret;
        uint32_t channel_code = Channel2Code(channel);
        ret = HAL_TIM_PWM_Stop_IT(&TimerNode->timer_h, channel_code);
        if(HAL_OK == ret) {
            LOG_INFO(PWM, "StopOk");
            res = true;
        } else {
            LOG_ERROR(PWM, "StopErr %s", HalStatus2Str(ret));
            res = false;
        }
    }
    return res;
}

bool pwm_ctrl(uint8_t timer_num, TimChannel_t channel, bool on) {
    bool res = false;
    if(on) {
        res = pwm_start(timer_num, (TimChannel_t)channel);
    } else {
        res = pwm_stop(timer_num, (TimChannel_t)channel);
    }
    return res;
}

bool oe_ctrl(uint8_t timer_num, TimChannel_t channel, bool on) {
    bool res = false;
    if(on) {
        res = tim_oc_start(timer_num, (TimChannel_t)channel);
    } else {
        res = tim_oc_stop(timer_num, (TimChannel_t)channel);
    }
    return res;
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim_pwmHandle) {}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim_pwmHandle) {}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t timer_num = TimInstance2Num(htim->Instance);
        TimerHandle_t* TimerNode = timer_get_node(timer_num);
        if(TimerNode) {
            TimerNode->pulse_fin_cnt++;
        }
    }
}

void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t timer_num = TimInstance2Num(htim->Instance);
        TimerHandle_t* TimerNode = timer_get_node(timer_num);
        if(TimerNode) {
            TimerNode->pulse_fin_half_cnt++;
        }
    }
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef* htim) {
    if(htim) {
        int8_t timer_num = TimInstance2Num(htim->Instance);
        TimerHandle_t* TimerNode = timer_get_node(timer_num);
        if(TimerNode) {
            TimerNode->delay_elapse_cnt++;
        }
    }
}
