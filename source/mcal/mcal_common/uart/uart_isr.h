#ifndef UART_GENERAL_ISR_H
#define UART_GENERAL_ISR_H

#include "std_includes.h"

#ifdef HAS_UART_CUSTOM
#include "uart_custom_isr.h"
#endif

#include "uart_types.h"

bool UartRxProcIsrLL(UartHandle_t* Node, uint8_t rx_byte);
bool UartTxProcIsrLL(UartHandle_t* const Node) ;
bool UartRxProcIsr(uint8_t num, uint8_t rx_byte);
bool UartTxProcIsr(uint8_t num);

#endif /* UART_GENERAL_ISR_H */
