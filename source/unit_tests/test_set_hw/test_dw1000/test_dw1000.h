#ifndef TEST_DW1000_H
#define TEST_DW1000_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifdef HAS_TEST_DW1000_GPIO
#include "test_dw1000_gpio.h"
#else
#define TEST_SUIT_DW1000_GPIO
#endif

#ifndef HAS_DW1000
#error "+HAS_DW1000"
#endif

#ifndef HAS_TEST_DW1000
#error "+HAS_TEST_DW1000"
#endif

bool test_dw1000_connected(void);
bool test_dw1000_types(void);
bool test_dw1000_tx(void);
bool test_dw1000_rx_ant_delay(void);
bool test_dw1000_tx_ant_delay(void);
bool test_dw1000_hash_tables(void) ;

#ifdef HAS_DW1000_OTP

bool test_dw1000_otp_read(void);
bool test_dw1000_otp_write(void);

#define TEST_SUIT_DW1000_OTP                          \
    {"dw1000_otp_read", test_dw1000_otp_read},        \
    {"dw1000_otp_write", test_dw1000_otp_write},
#else
#define TEST_SUIT_DW1000_OTP
#endif

#define TEST_SUIT_DW1000                               \
    {"dw1000_types", test_dw1000_types},              \
    {"dw1000_hash_tables", test_dw1000_hash_tables},  \
    {"dw1000_connect", test_dw1000_connected},        \
    {"dw1000_tx", test_dw1000_tx},                    \
    {"dw1000_rx_ant_delay", test_dw1000_rx_ant_delay},              \
    {"dw1000_tx_ant_delay", test_dw1000_tx_ant_delay},              \
    TEST_SUIT_DW1000_GPIO                                    \
    TEST_SUIT_DW1000_OTP

#ifdef __cplusplus
}
#endif

#endif /* TEST_DW1000_H */
