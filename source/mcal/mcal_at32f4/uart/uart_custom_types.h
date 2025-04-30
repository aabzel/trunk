#ifndef USART_CUSTOM_TYPES_H
#define USART_CUSTOM_TYPES_H

#include "artery_at32f4xx.h"
#include "clock_const.h"
#include "uart_custom_const.h"

#define UART_CUSTOM_VARIABLES \
    usart_type* UARTx;

typedef struct{
    ClockBus_t clock_bus;
    crm_periph_clock_type clock_type;
    uint8_t num;
    IRQn_Type irq_n;
    usart_type* UARTx;
    bool valid;
#ifdef HAS_DMA
#ifdef HAS_AT32F43X
    dmamux_requst_id_sel_type dma_tx_mux;
    dmamux_requst_id_sel_type dma_rx_mux;
#endif //HAS_AT32F43X
#endif//HAS_DMA
   // uint32_t clock_hz; /*TODO Delete*/
}UartInfo_t;

#endif /* USART_CUSTOM_TYPES_H  */
