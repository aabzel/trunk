#ifndef NRF_USART_DRV_H
#define NRF_USART_DRV_H

//#include "sys_config.h"
#include "uart_mcal.h"
#include "uart_config.h"
#include "uart_custom_types.h"



#define UART6_BAUD_RATE CLI_UART_BAUD_RATE /*CLI   */

#ifndef HAS_UART_INTERRUPT
#warning "+HAS_UART_INTERRUPT"
#endif /*HAS_UART_INTERRUPT*/

#ifndef HAS_UART
#endif

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

#ifndef HAS_FIFO
#error "+HAS_FIFO"
#endif

#ifndef HAS_FIFO_CHAR
#error "+HAS_FIFO_CHAR"
#endif

bool uart0_rx_timeout(void);
bool uart1_rx_timeout(void);
bool uart2_rx_timeout(void);
bool uart3_rx_timeout(void);
bool print_banner(uint8_t uart_num);
bool uart_poll(uint8_t uart_num, uint8_t* out_array, uint16_t size, uint16_t* read_cnt);
bool uart_poll_read(uint8_t uart_num);

#endif /* NRF_USART_DRV_H  */
