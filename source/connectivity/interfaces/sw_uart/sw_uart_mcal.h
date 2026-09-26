#ifndef SW_UART_MCAL_H
#define SW_UART_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sw_uart_config.h"
#include "sw_uart_types.h"
#include "sw_uart_isr.h"

#ifdef HAS_SW_UART_DIAG
#include "sw_uart_diag.h"
#endif

/* API */
SwUartHandle_t* SwUartGetNode(uint8_t num);
const SwUartConfig_t* SwUartGetConfig(uint8_t num);
bool SwUartIsValidConfig(const SwUartConfig_t* const Config);

#ifdef HAS_SW_UART_CUSTOM
const SwUartInfo_t* SwUartGetInfo(uint8_t num);
#endif

bool sw_uart_mcal_init(void);
bool sw_uart_init_custom(void);
bool sw_uart_init_one(uint8_t num);
bool sw_uart_init_common(const SwUartConfig_t* const Config,
                              SwUartHandle_t* const Node);

bool sw_uart_proc_one(uint8_t num);
bool sw_uart_proc(void);

/*setters*/
bool sw_uart_tx_next(uint8_t num);
bool sw_uart_writer_transmit(void* base);
void sw_uart_puts(void* stream_ptr, const char* str, int32_t len);
void sw_uart_putc(void* stream_ptr, char ch);
bool sw_uart_proc_bit(SwUartHandle_t* Node, uint8_t sample);
bool sw_uart_baudrate_set(uint8_t num, const uint32_t baudrate);
bool sw_uart_mcal_send(uint8_t num, const uint8_t* const data, uint32_t size);
bool sw_uart_last_rx_set(const uint8_t num, const uint8_t data);

/*getters*/
uint8_t sw_uart_last_rx_get(const uint8_t num);
bool sw_uart_baudrate_get(uint8_t num, uint32_t* const baudrate);
bool sw_uart_check(void);


#ifdef __cplusplus
}
#endif

#endif /* SW_UART_MCAL_H */
