#include "test_sw_uart.h"

#include <stdint.h>

#include "array.h"
#include "data_utils.h"
#include "log.h"
#include "macro_utils.h"
#include "none_blocking_pause.h"
#include "sw_uart_mcal.h"
#include "uart_mcal.h"
#include "unit_test_check.h"

bool test_sw_uart_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_EQ(4, sizeof(SwUartFrameRx_t));
    ASSERT_EQ(4, sizeof(SwUartFrameTx_t));
    return res;
}

bool test_sw_uart_tx_array5(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t data[5]={1,2,3,4,5};
    res = sw_uart_mcal_send(SW_UART_TEST_NUM, data, sizeof(data));
    ASSERT_TRUE(res);
    return res;
}

bool test_sw_uart_rx_00(void){
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE( test_sw_uart_rx_one(0x00));
    return res;

}

bool test_sw_uart_rx_termocode(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    res = test_sw_uart_rx_one(0x00);
    ASSERT_TRUE(res);

    res = test_sw_uart_rx_one(0x01);
    ASSERT_TRUE(res);

    res = test_sw_uart_rx_one(0x03);
    ASSERT_TRUE(res);

    res = test_sw_uart_rx_one(0x07);
    ASSERT_TRUE(res);

    res = test_sw_uart_rx_one(0x0f);
    ASSERT_TRUE(res);

    res = test_sw_uart_rx_one(0x1f);
    ASSERT_TRUE(res);

    res = test_sw_uart_rx_one(0x3f);
    ASSERT_TRUE(res);

    res = test_sw_uart_rx_one(0x7f);
    ASSERT_TRUE(res);

    res = test_sw_uart_rx_one(0xff);
    ASSERT_TRUE(res);
    return res;
}

bool test_sw_uart_rx_one(uint8_t data) {
    LOG_INFO(TEST, "%s()Data:0x%x", __FUNCTION__,data);
    bool res = true;

    res = sw_uart_last_rx_set(1, 0x00);

    res = uart_mcal_send(2, &data, 1);
    ASSERT_TRUE(res);

    res = wait_in_loop_ms(300);
    ASSERT_TRUE(res);

    uint8_t last_rx = sw_uart_last_rx_get(1);
    ASSERT_EQ(data, last_rx);

    return res;
}

bool test_sw_uart_rx_ff(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;

    res=test_sw_uart_rx_one(0xff);
    ASSERT_TRUE(res);
    return res;
}

bool test_sw_uart_rx_55(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    res=test_sw_uart_rx_one(0x55);
    ASSERT_TRUE(res);

    return res;
}

bool test_sw_uart_tx_one(uint8_t test_byte, uint8_t tx_uart_num, uint8_t rx_uart_num,uint32_t time_out_ms) {
    LOG_INFO(TEST, "%s(),TestByte:0x%x,txSwUART%u,->txUART%u", __FUNCTION__, test_byte, tx_uart_num, rx_uart_num);
    bool res = true;

    res = uart_last_rx_reset(rx_uart_num);
    ASSERT_TRUE(res);

    uint8_t data = test_byte;
    res = sw_uart_mcal_send(tx_uart_num, &data, 1);
    ASSERT_TRUE(res);

    res = wait_ms(time_out_ms);
    ASSERT_TRUE(res);

    uint8_t last_rx = uart_last_rx_get(rx_uart_num);
    ASSERT_EQ(test_byte, last_rx);
    return res;
}

bool test_sw_uart_tx(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;

    res = test_sw_uart_tx_one(0x55,   SW_UART_TEST_NUM, 2,200);
    ASSERT_TRUE(res);

    res = test_sw_uart_tx_one(0xaa,   SW_UART_TEST_NUM, 2,200);
    ASSERT_TRUE(res);

    res = test_sw_uart_tx_one(0x00,   SW_UART_TEST_NUM, 2,200);
    ASSERT_TRUE(res);

    res = test_sw_uart_tx_one(0xFF,   SW_UART_TEST_NUM, 2,200);
    ASSERT_TRUE(res);
    return res;
}

bool test_sw_uart_tx_all( const  uint8_t num , const uint32_t time_out_ms) {
    LOG_INFO(TEST, "%s()N:%u,TO:%u ms", __FUNCTION__, num,time_out_ms);
    bool res = true;
    uint32_t b = 0;
    for(b=0x0; b<=0xFF; b++) {
        res = test_sw_uart_tx_one((uint8_t) b, num, 2, time_out_ms);
        ASSERT_TRUE(res);
    }
    return res;
}
