#ifndef USART_NRF53_TYPES_H
#define USART_NRF53_TYPES_H

#include <stdint.h>

#include "uart_custom_const.h"
#include "nrfx_uarte.h"

#define UART_CUSTOM_VARIABLES      \
    uint8_t rx_dma_buf[5];    \
    nrfx_uarte_t uart__h;     \
    nrfx_uarte_config_t config; /*TODO Move to stack memory*/

    //NRF_UARTE_Type *uart_h;




typedef struct  {
	bool valid;
    uint8_t uart_num;
    nrfx_uarte_event_handler_t  event_handler;
} UartEventHandler_t;

typedef struct  {
	bool valid;
    uint32_t baudrate;
    nrf_uarte_baudrate_t  nrf_uarte_baudrate;
} NrfUartBaudRateInfo_t;

typedef struct  {
    uint8_t num;
    bool valid;
    uint8_t uart_int_id;
    nrfx_uarte_event_handler_t  event_handler;
    NRF_UARTE_Type* uart_ptr;
    uint32_t clock_hz;
} UartInfo_t;


#endif /* USART_NRF53_TYPES_H  */
