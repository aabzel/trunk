#ifndef UART_NRF_ISR_H
#define UART_NRF_ISR_H

#include <stdbool.h>

#include "nrfx_uarte.h"

#ifndef HAS_UART_INTERRUPT
#warning "+HAS_UART_INTERRUPT"
#endif /*HAS_UART_INTERRUPT*/

#ifndef HAS_UART
#error "+HAS_GPIO"
#endif

#ifndef HAS_UART_INTERRUPT
#error "+HAS_UART_INTERRUPT"
#endif

#ifndef HAS_UART_ISR
#error "+HAS_UART_ISR"
#endif

#ifdef NRFX_UARTE0_ENABLED
void nrfx_uart0_event_handler(nrfx_uarte_event_t const* p_event, void* p_context) ;
#endif

#ifdef NRFX_UARTE1_ENABLED
void nrfx_uart1_event_handler(nrfx_uarte_event_t const* p_event, void* p_context) ;
#endif

#ifdef NRFX_UARTE2_ENABLED
void nrfx_uart2_event_handler(nrfx_uarte_event_t const* p_event, void* p_context) ;
#endif

#ifdef NRFX_UARTE3_ENABLED
void nrfx_uart3_event_handler(nrfx_uarte_event_t const* p_event, void* p_context) ;
#endif


bool uart_interupts_enable(uint8_t uart_num) ;
nrfx_uarte_event_handler_t UartNum2EventHandler(uint8_t uart_num);

#endif /* UART_NRF_ISR_H  */
