#ifndef TEST_UART_H
#define TEST_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_UART
#error "It is needed HAS_UART option for that component"
#endif

#include "test_hw_dep_check.h"

bool test_uart_loopback(uint8_t num);
bool test_uart_time(void);

#ifdef HAS_UART0

bool test_uart0_read(void);
bool test_uart0_write(void);
bool test_uart0_write_string(void);

#define TEST_SUIT_UART0                                                                                                \
    {"uart0_write", test_uart0_write}, {"uart0_write_string", test_uart0_write_string}, {"uart0_read", test_uart0_read},
#else
#define TEST_SUIT_UART0
#endif

#ifdef HAS_UART1
bool test_uart1_read(void);
bool test_uart1_write(void);
bool test_uart1_wait_write(void);
bool test_uart1_loopback(void);

#define TEST_SUIT_UART1 {"uart1_write", test_uart1_write}, \
	        {"uart1_wait_write", test_uart1_wait_write},   \
	        {"uart1_loopback", test_uart1_loopback},   \
			{"uart1_read", test_uart1_read},
#else
#define TEST_SUIT_UART1
#endif

#ifdef HAS_UART3
bool test_uart3_read(void);
bool test_uart3_write(void);
bool test_uart3_write_new_line(void);
bool test_uart3_wait_write(void);

#define TEST_SUIT_UART3                                                                                                \
    {"uart3_write", test_uart3_write}, {"uart3_wait_write", test_uart3_wait_write},                                    \
        {"uart3_CRLF", test_uart3_write_new_line}, {"uart3_read", test_uart3_read},
#else
#define TEST_SUIT_UART3
#endif

#define TEST_SUIT_UART {"uart_time", test_uart_time}, TEST_SUIT_UART0 TEST_SUIT_UART1 TEST_SUIT_UART3

#ifdef __cplusplus
}
#endif

#endif /* TEST_UART_H */
