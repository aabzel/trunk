#ifndef TEST_SW_UART_H
#define TEST_SW_UART_H

#include "std_inc.h"

#define SW_UART_TEST_NUM 1

bool test_sw_uart_rx_one(uint8_t data);
bool test_sw_uart_tx_all(const  uint8_t num , const uint32_t time_out_ms);
bool test_sw_uart_tx_one(uint8_t tx_data, uint8_t tx_uart_num, uint8_t rx_uart_num, uint32_t time_out_ms);

bool test_sw_uart_rx_termocode(void);
bool test_sw_uart_tx(void);
bool test_sw_uart_types(void);
bool test_sw_uart_tx_array5(void);
bool test_sw_uart_rx_00(void);
bool test_sw_uart_rx_55(void);
bool test_sw_uart_tx_55(void);
bool test_sw_uart_rx_ff(void);

#define TEST_SUIT_SW_UART                           \
    {"sw_uart_types", test_sw_uart_types},          \
    {"sw_uart_rx_termocode", test_sw_uart_rx_termocode},          \
    {"sw_uart_rx_00", test_sw_uart_rx_00},          \
    {"sw_uart_rx_ff", test_sw_uart_rx_ff},          \
    {"sw_uart_rx_55", test_sw_uart_rx_55},          \
    {"sw_uart_tx", test_sw_uart_tx},                \
    {"sw_uart_tx_array5", test_sw_uart_tx_array5},
    

#endif /* TEST_SW_UART_H */
