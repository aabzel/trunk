#ifndef UART_CUSTOM_TYPES_H
#define UART_CUSTOM_TYPES_H

#include "uart_custom_const.h"
#include "sys_config.h"
#include "periphery/uart.h"
#include "mik32_hal_usart.h"

#define UART_CUSTOM_VARIABLES      \
    USART_HandleTypeDef Handle;    \
    UART_TypeDef* UARTx;

typedef struct {
    bool valid;
    uint8_t num;
    UART_TypeDef* UARTx;
    uint32_t clock_hz;
    uint32_t interrupt_mask;
    IRQn_Type irq_n;
}UartInfo_t;

// see page 38
typedef union {
    uint32_t dword;
    struct{
        uint32_t UE:1;   /*    Ресет USART.      */
        uint32_t RES1:1;   /*    Зарезервировано      */
        uint32_t RE:1;   /*    Управление приемником      */
        uint32_t TE:1;   /*  Управление передатчиком        */
        uint32_t IDLEIE:1;   /* Управление прерыванием при отсутствии входных транзакций         */
        uint32_t RXNEIE:1;   /*  Управление прерыванием при успешном приеме дан-ных или перезаписи полу-ченных данных        */
        uint32_t TCIE:1;   /*   Управление прерыванием при успешной передаче дан-ных:       */
        uint32_t TXEIE:1;   /*          */
        uint32_t PEIE:1;   /*  Управление прерыванием при ошибке в принятом бите четности        */
        uint32_t PS:1;   /*  Выбор способа формирова-ния бита четности        */
        uint32_t PCE:1;   /* Контроль четности         */
        uint32_t RES2:1;   /*  Зарезервировано        */
        uint32_t M0:1;   /*   Совместно с битом 28 (M1) управляет длиной кадра       */
        uint32_t RES3:15;   /*   Зарезервировано       */
        uint32_t M1:1;   /*  Совместно с битом 12 (M0) управляет длиной кадра        */
        uint32_t RES4:3;   /*    Зарезервировано      */
    };
} __attribute__((__packed__)) Mik32UsartRegCONTROL1_t;

typedef union {
    uint32_t dword;
    struct{
        uint32_t R;
    };
} __attribute__((__packed__)) Mik32UsartRegCONTROL2_t;

typedef union {
    uint32_t dword;
    struct{
        uint32_t R;
    };
} __attribute__((__packed__)) Mik32UsartRegCONTROL3_t;


typedef union {
    uint32_t dword;
    struct{
        uint32_t R;
    };
} __attribute__((__packed__)) Mik32UsartRegDIVIDER_t;





typedef union {
    uint32_t dword;
    struct{
        uint32_t R;
    };
} __attribute__((__packed__)) Mik32UsartRegTXDATA_t;


typedef union {
    uint32_t dword;
    struct{
        uint32_t R;
    };
} __attribute__((__packed__)) Mik32UsartRegMODEM_t;



typedef struct {
    volatile Mik32UsartRegCONTROL1_t CONTROL1; /*offser 0x00   0*/
    volatile Mik32UsartRegCONTROL2_t CONTROL2; /*0x04   4*/
    volatile Mik32UsartRegCONTROL3_t CONTROL3; /*0x08   8*/
    volatile Mik32UsartRegDIVIDER_t DIVIDER;   /*0x0C   12  */
    volatile uint32_t reserved1[3];/*0x10 16*/
    volatile Mik32UsartRegFLAGS_t FLAGS;/*0x1C 28*/
    volatile uint32_t reserved3;/*0x20  32*/
    volatile Mik32UsartRegRXDATA_t RX_DATA;/*0x24  36*/
    volatile Mik32UsartRegTXDATA_t TX_DATA;/*0x28 40*/
    volatile Mik32UsartRegMODEM_t MODEM;/*0x2C 44*/
}  Mik32UsartRegs_t;

#endif /* UART_CUSTOM_TYPES_H  */
