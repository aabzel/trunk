#ifndef USART_CUSTOM_POLLING_H
#define USART_CUSTOM_POLLING_H

#include "uart_mcal.h"

bool uart_wait_send_ll(UartHandle_t* Node, const uint8_t* const data, uint32_t size);
bool uart_send_wait_ll(UartHandle_t* const Node, const uint8_t* const data, uint32_t size);
bool uart_send_ll(uint8_t num, uint8_t* data, uint16_t size);

#endif /* USART_CUSTOM_POLLING_H  */
