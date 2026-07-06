#include "test_i2s_dma.h"

#include "i2s_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "data_utils.h"
#include "unit_test_check.h"

static uint16_t rxArray[100] = { 0 };
static uint16_t txArray[100] = { 0 };


bool test_i2s_dma_read( I2sHandle_t *Node) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_NE(NULL, Node);
    Node->rx_done = false;
    Node->rx_half = false;
    memset(rxArray, 0x55, sizeof(rxArray));
    EXPECT_TRUE(i2s_dma_read(Node->num, (uint16_t* )rxArray, ARRAY_SIZE(rxArray))      );
    EXPECT_TRUE(wait_in_loop_ms(100));
    EXPECT_TRUE(i2s_dma_stop(Node->num));
    return res;
}

bool test_i2s_dma_write( I2sHandle_t *Node) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_NE(NULL, Node);
    Node->tx_done = false;
    Node->tx_half = false;
    memset(txArray, 0x55, sizeof(txArray));

    ASSERT_TRUE(i2s_dma_write(Node->num, (uint16_t* )txArray, ARRAY_SIZE(txArray))      );
    ASSERT_TRUE(wait_in_loop_ms(100));
    ASSERT_TRUE(i2s_dma_stop(Node->num));
    return res;
}

bool test_i2s_dma_half_write(uint8_t num){
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    bool res = true;
    I2sHandle_t *Node = I2sGetNode(num);
    ASSERT_TRUE( test_i2s_dma_write( Node));
    ASSERT_TRUE( Node->tx_half);
    return res;
}

bool test_i2s_dma_half_read(uint8_t num){
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    bool res = true;
    I2sHandle_t *Node = I2sGetNode(num);
    ASSERT_TRUE( test_i2s_dma_read( Node));
    ASSERT_TRUE( Node->rx_half);
    return res;
}

bool test_i2s_dma_done_write(uint8_t num){
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    bool res = true;
    I2sHandle_t *Node = I2sGetNode(num);
    ASSERT_TRUE( test_i2s_dma_write( Node));
    ASSERT_TRUE( Node->tx_done);
    return res;
}

bool test_i2s_dma_done_read(uint8_t num) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    bool res = true;
    I2sHandle_t *Node = I2sGetNode(num);
    ASSERT_TRUE( test_i2s_dma_read( Node));
    ASSERT_TRUE( Node->rx_done);
    return res;
}

#ifdef HAS_I2S2
bool test_i2s2_dma_done_write(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_dma_done_write(2));
    return true;
}

bool test_i2s2_dma_half_write(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_dma_half_write(2));
    return true;
}

bool test_i2s2_dma_done_read(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_dma_done_read(2));
    return true;
}

bool test_i2s2_dma_half_read(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_dma_half_read(2));
    return true;
}

#endif /*HAS_I2S2*/
