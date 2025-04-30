#ifndef USART_CUSTOM_ISR_H
#define USART_CUSTOM_ISR_H

#include "std_includes.h"
#include "microcontroller_const.h"
#include "microcontroller_types.h"

#define USART_ALL_INT (USART_CTSCF_INT | USART_ERR_INT | USART_BF_INT | USART_PERR_INT | USART_TDC_INT | USART_IDLE_INT)

bool UART_TxCpltCallback(usart_type* UARTx);
bool UART_RxCpltCallback(usart_type* UARTx);

bool UartIRQHandler(uint8_t num);

#endif /* USART_CUSTOM_ISR_H  */
