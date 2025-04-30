#ifndef USART_DRV_H
#define USART_DRV_H

#include <stdbool.h>
#include <stdint.h>
#include "sys_config.h"
#include "uart_common.h"
#include "driver/uart.h"

#define UART_PERIOD_US 1
#define UART_RX_ARRAY_SIZE 500U
#define UART_RX_FIFO_ARRAY_SIZE 100U
#define UART_TX_ARRAY_SIZE 600U


typedef struct xUartCfg_t{
    int tx_io_num;
    int rx_io_num;
}UartCfg_t;

extern UartCfg_t UartCfg[2];

bool uart_init(void);
bool usart_set_baudrate(uint8_t uart_num, uint16_t baudrate);
bool uart_read(uint8_t uart_num, uint8_t* out_array, uint16_t array_len);
bool uart_send(uint8_t uart_num, uint8_t* array, uint16_t array_len, bool is_wait);
uint32_t uart_get_baud_rate(uint8_t uart_num, uint16_t* mantissa, uint16_t* fraction, uint8_t* over_sampling);

bool proc_uart(uint8_t uart_index);
bool proc_uarts(void);
uint32_t uart_get_baud_rate(uint8_t uart_num, uint16_t* mantissa,
                            uint16_t* fraction, uint8_t* over_sampling) ;

#endif /* USART_DRV_H  */
