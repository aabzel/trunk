#ifndef UART_CUSTOM_ISR_H
#define UART_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* uart_handle) ;
void HAL_UART_TxCpltCallback(UART_HandleTypeDef* uart_handle);

#ifdef __cplusplus
}
#endif


#endif /* UART_CUSTOM_ISR_H */


