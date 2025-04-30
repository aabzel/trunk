
#ifndef UART_ISR_H
#define UART_ISR_H

#include <zephyr/drivers/uart.h>

#ifndef HAS_ZEPHYR
#error "+ HAS_ZEPHYR"
#endif

#ifndef HAS_FIFO
#error "+ HAS_FIFO"
#endif

#ifndef HAS_UART
#error "+ HAS_UART"
#endif

#ifndef HAS_UART_ISR
#error "+ HAS_UART_ISR"
#endif

void uart2_callback(const struct device* dev, void* user_data);

#endif /* UART_ISR_H */
