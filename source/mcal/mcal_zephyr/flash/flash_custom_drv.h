#ifndef USART_ZEPHYR_DRV_H
#define USART_ZEPHYR_DRV_H

#include "uart_bsp.h"
#include "uart_config.h"
#include "uart_zephyr_types.h"

#ifndef HAS_ZEPHYR
#error "+ HAS_ZEPHYR"
#endif

#ifndef HAS_FIFO
#error "+ HAS_FIFO"
#endif

#ifndef HAS_UART
#error "+ HAS_UART"
#endif

bool proc_uart(uint8_t uart_index);
bool proc_uarts(void);
bool uart_check(void);
bool uart_flush(uint8_t uart_num);
bool uart_init(void);
bool uart_read(uint8_t uart_num, uint8_t* out_array, uint16_t array_len);
bool uart_send_wait_ll(uint8_t uart_num, uint8_t* tx_buffer, uint16_t len);
bool uart_set_baudrate(uint8_t uart_num, uint32_t baudrate);
bool uart_wait_send_ll(uint8_t uart_num, uint8_t* tx_buffer, uint16_t len);
uint32_t uart_get_baud_rate(uint8_t uart_num, uint16_t* mantissa, uint16_t* fraction, uint8_t* over_sampling);
bool uart_poll(uint8_t uart_num, uint8_t* out_array, uint16_t size, uint16_t* read_cnt);
bool uart_poll_read(uint8_t uart_num);

#endif /* USART_ZEPHYR_DRV_H  */
