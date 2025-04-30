#ifndef USART_ZEPHYR_TYPES_H
#define USART_ZEPHYR_TYPES_H

#include <stdint.h>

#include "uart_nrf_const.h"
#include "nrfx_uarte.h"

#ifdef HAS_UART_ISR
typedef void (*uart_isr_callback_t)(const struct device* dev, void* user_data);
#endif

#define FLASH_CUSTOM_TYPES \
    struct device *dev;



typedef struct {
	bool valid;
	uint8_t num;
	struct device *dev;
#ifdef HAS_UART_ISR
	uart_isr_callback_t uart_isr_callback;
#endif
}UartZephyrInto_t;


#endif /* USART_ZEPHYR_TYPES_H  */
