#ifndef UART_MCAL_H
#define UART_MCAL_H

#include "uart_types.h"
#include "uart_config.h"
#include "sys_constants.h"
#include "uart_isr.h"
#ifdef HAS_UART_CUSTOM
#include "uart_custom_drv.h"
#endif

#ifdef HAS_INTERFACES
#include "interfaces_const.h"
#endif

#ifndef HAS_UART
#error "+ HAS_UART"
#endif

#ifndef HAS_FIFO
#error "+ HAS_FIFO"
#endif

extern uint32_t g_uart_rx_cnt;

UartHandle_t* UartGetNode(uint8_t num);

#ifdef HAS_UART_CUSTOM
UartInfo_t* UartGetInfo(uint8_t num) ;
#endif
const UartConfig_t* UartGetConfig(uint8_t num);

/*API*/
bool uart_init_general_one(const UartConfig_t *const Config, UartHandle_t *const Node) ;

bool uart_is_allowed(uint8_t num);
bool uart_is_init(uint8_t num);
bool uart_init_one(uint8_t num);
bool uart_init_custom(void);
bool uart_mcal_init(void);
bool uart_banner_init(void);
bool UartIsValidConfig(const UartConfig_t* const Config);
bool uart_proc(void) ;
bool uart_proc_one(uint8_t num);
Interfaces_t UartNumToInterface(uint8_t num);

/*setters*/
#ifdef HAS_DMA
bool uart_dma_send_wait_ll(UartHandle_t* const Node, const uint8_t* const data, size_t size);
bool uart_dma_send_wait(uint8_t num, const uint8_t* const data, size_t len);
#endif
bool uart_set_baudrate(uint8_t num, uint32_t baudrate); //TODO uart_baudrate_set
bool uart_wait_send(uint8_t num, const uint8_t* const data, size_t len);
bool uart_send_wait(uint8_t num, const uint8_t* const data, size_t len);
bool print_banner(uint8_t num);
bool uart_flush(uint8_t num);
bool uart_send_banner(uint8_t num, char* pattern);
bool uart_mcal_send(uint8_t num, const uint8_t* const data, uint16_t len);
bool uart_send_ll( uint8_t num, uint8_t* array, uint16_t array_len, bool is_wait) ;
bool uart_send_wait_ll(UartHandle_t* Node, const uint8_t* const  data, uint16_t len);
bool uart_wait_send_ll(UartHandle_t* Node, const uint8_t* const data, size_t len);

/*getters*/
uint32_t uart_get_cfg_baudrate(uint8_t num);
uint32_t uart_baud_rate_get_ll(uint8_t num, uint16_t* mantissa, uint16_t* fraction, uint8_t* over_sampling);
bool uart_get_baud_rate(uint8_t num, uint32_t* const baudrate) ;
bool uart_calc_byte_rate(void);
bool uart_check(void);

/*ISR code*/
//bool UartRxProcIsr(uint8_t num, uint8_t rx_byte);
//bool UartTxProcIsr(uint8_t num);
bool uart_read(uint8_t num, uint8_t* out_array, uint16_t array_len);
bool uart_wait_tx_done_ll(UartHandle_t* Node);
uint32_t uart_calc_transfer_time_ms(uint32_t baudrate, uint32_t bytes);
uint32_t uart_calc_transfer_time_us(uint32_t baudrate, uint32_t bytes);

#endif /* UART_MCAL_H  */
