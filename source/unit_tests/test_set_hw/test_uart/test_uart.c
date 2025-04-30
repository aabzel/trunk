#include "test_uart.h"

#include <stdio.h>
#include <string.h>

#include "sys_config.h"
#include "uart_mcal.h"
#include "unit_test_check.h"
#include "none_blocking_pause.h"

bool test_uart_loopback(uint8_t num) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint16_t i = 0;
    UartHandle_t* Node = UartGetNode(num);
    ASSERT_NE(0, Node);
    uint32_t duration_us = uart_calc_transfer_time_us(9600,  5);
    LOG_INFO(TEST, "RxTimeOut:%u us", duration_us);
    for(i=0; i < 256; i++) {
        uint8_t send_byte = (uint8_t)i;
        ASSERT_TRUE(uart_mcal_send(num, &send_byte, 1));
        ASSERT_TRUE(wait_us((uint64_t) duration_us));
        ASSERT_EQ(send_byte, Node->rx_byte);
    }

    return true;
}

static bool test_uart_wait_write(uint8_t num) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(UART, LOG_LEVEL_DEBUG);
    bool res = true;
    uint8_t array[10] = {0};
    EXPECT_TRUE(uart_wait_send(num, (uint8_t*)array, sizeof(array)));
    EXPECT_TRUE(uart_wait_send(num, (uint8_t*)array, sizeof(array)));
    EXPECT_TRUE(uart_wait_send(num, (uint8_t*)array, sizeof(array)));
    EXPECT_TRUE(uart_wait_send(num, (uint8_t*)array, sizeof(array)));
    set_log_level(UART, LOG_LEVEL_INFO);
    return res;
}


bool test_uart_time(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint32_t time_us = uart_calc_transfer_time_us(460800, 10);
    ASSERT_EQ(260, time_us);

    uint32_t time_ms = uart_calc_transfer_time_ms(460800, 100);
    ASSERT_EQ(2, time_ms);
    return res;
}

#ifdef HAS_UART0

bool test_uart0_loopback(void){
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_TRUE( test_uart_loopback(0))
    return true;
}


bool test_uart0_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t array[2] = {0};
    UartHandle_t* UartNode = UartGetNode(0);
    ASSERT_NE(NULL, UartNode);
#ifdef HAS_UART_INTERRUPT
    uint32_t init_tx_cnt = UartNode->cnt.byte_tx;
#endif
    memset(array, 0xFF, sizeof(array));
    ASSERT_TRUE(uart_mcal_send(0, array, sizeof(array)));
#ifdef HAS_UART_INTERRUPT
    ASSERT_GR(init_tx_cnt, UartNode->cnt.byte_tx);
#endif
    return res;
}
bool test_uart0_write_string(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    char temp_str[200] = "";
    uint32_t i = 0;
    memset(temp_str, 0x0, sizeof(temp_str));
    for(i = 0; i < 96; i++) {
        temp_str[i] = '*';
    }

    cli_printf("%1u", 2);
    cli_printf("%s" CRLF, temp_str);

    return res;
}

bool test_uart0_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t byte = 0xFF;
    ASSERT_TRUE(uart_read(0, &byte, 1));
    return res;
}
#endif /*HAS_UART0*/

#ifdef HAS_UART1

bool test_uart1_loopback(void){
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_TRUE( test_uart_loopback(1))
    return true;
}

bool test_uart1_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t array[2] = {0};
    UartHandle_t* UartNode = UartGetNode(1);
    ASSERT_NE(NULL, UartNode);
    uint32_t init_tx_cnt = UartNode->cnt.byte_tx;
    memset(array, 0xFF, sizeof(array));
    ASSERT_TRUE(uart_mcal_send(1, array, sizeof(array)));
    ASSERT_GR(init_tx_cnt, UartNode->cnt.byte_tx);
    return res;
}
bool test_uart1_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t byte = 0xFF;
    EXPECT_FALSE(uart_read(1, &byte, 1));
    return res;
}

bool test_uart1_wait_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    EXPECT_TRUE(test_uart_wait_write(1));
    return res;
}

#endif

#ifdef HAS_UART3

bool test_uart3_loopback(void){
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_TRUE( test_uart_loopback(3))
    return true;
}


bool test_uart3_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    char array[10] = "87654321";
    bool res = true;
    UartHandle_t* UartNode = UartGetNode(3);
    ASSERT_NE(NULL, UartNode);
    uint32_t init_tx_cnt = UartNode->cnt.byte_tx;
    ASSERT_TRUE(uart_mcal_send(3, (uint8_t*)array, strlen(array) + 1));
    ASSERT_GR(init_tx_cnt, UartNode->cnt.byte_tx);
    return res;
}

//static const char g_array[10] = "87654321";
bool test_uart3_wait_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    EXPECT_TRUE(test_uart_wait_write(3));
    return res;
}

bool test_uart3_write_new_line(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    static char array[80] = "";
    bool res = true;
    snprintf(array, sizeof(array), "NewLine->" CRLF "<-NewLineDone" CRLF);
    ASSERT_TRUE(uart_mcal_send(3, (uint8_t*)array, strlen(array)));
    return res;
}

bool test_uart3_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t byte = 0xFF;
    EXPECT_FALSE(uart_read(3, &byte, 1));
    return res;
}
#endif /*HAS_UART3*/
