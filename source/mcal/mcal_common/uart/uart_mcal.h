#ifndef UART_MCAL_H
#define UART_MCAL_H

#include "sys_constants.h"
#include "uart_isr.h"
#include "uart_types.h"
#include "uart_config.h"

#ifdef HAS_UART_DIAG
#include "uart_diag.h"
#endif

#ifdef HAS_UART_CUSTOM
#include "uart_custom_drv.h"
#endif

#ifdef HAS_INTERFACES
#include "interfaces_types.h"
#endif


/*API*/
UartHandle_t* UartGetNode(uint8_t num);
const UartConfig_t* UartGetConfig(uint8_t num);

#ifdef HAS_UART_CUSTOM
const UartInfo_t* UartGetInfo(uint8_t num);
#endif

bool uart_init_common(const UartConfig_t *const Config, UartHandle_t *const Node) ;
bool uart_init_one(uint8_t num);
bool uart_init_custom(void);

bool uart_is_allowed(uint8_t num);
bool uart_is_init(uint8_t num);
bool uart_mcal_init(void);
bool uart_banner_init(void);
bool UartIsValidConfig(const UartConfig_t* const Config);

bool uart_proc(void) ;
bool uart_proc_one(uint8_t num);
bool uart_heartbeat_proc_one(uint8_t num);
bool uart_heartbeat_proc(void);
InterfaceType_t UartNumToInterface(uint8_t num);
uint8_t UartInterfaceToNum(const InterfaceType_t Interface);
bool uart_wait_fifo_space_ll(UartHandle_t* Node, uint32_t size);

/*setters*/
#ifdef HAS_DMA
bool uart_dma_send_wait_ll(UartHandle_t* const Node, const uint8_t* const data, uint32_t size);
bool uart_dma_send_wait(uint8_t num, const uint8_t* const data, uint32_t len);
bool uart_dma_send(const uint8_t num, const uint8_t* const data, const uint32_t size);
#endif
bool uart_veryfy_one(uint8_t num);
bool uart_set_baudrate(uint8_t num, uint32_t baudrate); //TODO uart_baudrate_set
bool uart_wait_send(uint8_t num, const uint8_t* const data, uint32_t len);
bool uart_send_wait(uint8_t num, const uint8_t* const data, uint32_t len);
bool print_banner(uint8_t num);
bool uart_flush(uint8_t num);
bool uart_tx_next(const uint8_t num);
bool uart_tx_next_ll( UartHandle_t* Node );
bool uart_send_banner(uint8_t num, char* pattern);
bool uart_mcal_send(const uint8_t num, const uint8_t* const data, uint32_t len);
bool uart_send_ll( UartHandle_t* Node, uint8_t* data, uint16_t array_len, bool is_wait);
bool uart_send_wait_ll(UartHandle_t* const Node,  const uint8_t* const data, uint32_t len);
bool uart_wait_send_ll(UartHandle_t* Node, const uint8_t* const data, uint32_t len);
bool uart_writer(const uint8_t num);

/*getters*/
uint32_t uart_get_cfg_baudrate(uint8_t num);
uint32_t uart_baud_rate_get_ll(uint8_t num, uint16_t* mantissa, uint16_t* fraction, uint8_t* over_sampling);
uint32_t UartGetBaseClock(const uint8_t num);
bool uart_get_baud_rate(uint8_t num, uint32_t* const baudrate) ;
bool uart_calc_byte_rate(void);
bool uart_wait_tx_done(UartHandle_t* const Node);
bool uart_check(void);

/*ISR code*/
//bool UartRxProcIsr(uint8_t num, uint8_t rx_byte);
//bool UartTxProcIsr(uint8_t num);
bool uart_read(uint8_t num, uint8_t* out_array, uint16_t array_len);
bool uart_wait_tx_done_ll(UartHandle_t* Node);
uint32_t uart_calc_transfer_time_ms(uint32_t baudrate, uint32_t bytes);
uint32_t uart_calc_transfer_time_us(uint32_t baudrate, uint32_t bytes);

#endif /* UART_MCAL_H  */
