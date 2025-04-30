#ifndef USART_CUSTOM_TYPES_H
#define USART_CUSTOM_TYPES_H

#include "uart_custom_const.h"
#include "sys_config.h"

#define UART_CUSTOM_VARIABLES     \
    UART_HandleTypeDef uart_h;

typedef struct {
	bool valid;
    uint8_t num;
    USART_TypeDef* USARTx;
    uint32_t clock_hz;
    IRQn_Type irq_n;
}UartInfo_t;

typedef union {
    uint32_t reg_val;
    struct{
        uint32_t sbk:1;     /*Send break*/
        uint32_t rwu:1;     /*Receiver wakeup*/
        uint32_t re:1;      /*Receiver enable*/
        uint32_t te:1;      /*Transmitter enable*/
        uint32_t idleie:1;  /*IDLE interrupt enable*/
        uint32_t rxneie:1;  /*RXNE interrupt enable*/
        uint32_t tcie:1;    /*Transmission complete interrupt enable*/
        uint32_t txeie:1;   /*TXE interrupt enable*/
        uint32_t peie:1;    /*PE interrupt enable*/
        uint32_t pce:1;     /*Parity control enable*/
        uint32_t wake:1;    /*Wake up method*/
        uint32_t m:1;       /*Word length*/
        uint32_t ue:1;      /*USART enable*/
        uint32_t res:1;     /**/
        uint32_t over8:1;   /*Over sampling mode*/
        uint32_t res2:16;   /**/
    };
}UartRegCtrl1_t;


typedef union {
    uint32_t reg_val;
    struct{
        uint32_t fraction:4;
        uint32_t mantissa:12;
        uint32_t res:16;
    };
}UartRegBaud_t;

#endif /* USART_CUSTOM_TYPES_H  */
