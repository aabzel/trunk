#ifndef TIM_DRV_CUSTOM_ISR_H
#define TIM_DRV_CUSTOM_ISR_H

#include "std_includes.h"

bool TIMx_IRQHandler(uint8_t num);

//void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim);
//void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef* htim) ;
//void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef* htim);


#endif /* TIM_DRV_CUSTOM_ISR_H  */
