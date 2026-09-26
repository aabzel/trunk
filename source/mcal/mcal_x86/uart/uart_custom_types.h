#ifndef USART_CUSTOM_TYPES_H
#define USART_CUSTOM_TYPES_H

#include "x86x.h"
#include "clock_const.h"
#include "uart_custom_const.h"
#include "microcontroller_drv.h"
#include "module_fcuart_regs.h"
#include "module_driver_fcuart.h"

#define UART_CUSTOM_VARIABLES                                                                                               \
    FCUART_HandleType Handle;                                                                                               \
    FCUART_TxRxInterrupt_CallBackType   RxCallBack;          /* receive interrupt callback function address */              \
    FCUART_TxRxInterrupt_CallBackType   TxEmptyCallBack;     /* transfer empty interrupt callback function address */       \
    FCUART_TxRxInterrupt_CallBackType   TxCompleteCallBack;  /* transfer complete interrupt callback function address */    \
    FCUART_ErrorInterrupt_CallBackType   ErrorCallBack;  /*  error interrupt callback function address*/    \
    FCUART_DataType RxMsg; \
    FCUART_DataType TxMsg; \
    FCUART_Type* UARTx;


typedef struct{
    UART_CUSTOM_VARIABLES
    ClockBus_t clock_bus;
    FCUART_InstanceType instance_type;
    uint32_t clock_type;
    PCC_ClkSrcType clk_src_type;
    uint8_t num;
    IRQn_Type irq_n;
    bool valid;
#ifdef HAS_DMA
#endif//HAS_DMA
}UartInfo_t;

#endif /* USART_CUSTOM_TYPES_H  */
