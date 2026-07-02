#ifndef I2S_CUSTOM_ISR_H
#define I2S_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32fx_hal.h"


void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef* hi2s);
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef* hi2s);

void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef* hi2s) ;
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef* hi2s);

void HAL_I2S_ErrorCallback(I2S_HandleTypeDef* hi2s);

void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef* hi2s);
void HAL_I2SEx_TxRxCpltCallback(I2S_HandleTypeDef* hi2s);


#ifdef __cplusplus
}
#endif



#endif
