#include "test_spi_dma.h"
#include "test_spi.h"

#include <string.h>

#include "debug_info.h"
#include "gpio_mcal.h"
#include "array.h"
#include "spi_dma.h"
#include "spi_mcal.h"
#include "sys_config.h"
#include "unit_test_check.h"

bool test_spi_dma_read(uint8_t num) {
    LOG_INFO(TEST, "%s():SPI%u", __FUNCTION__, num);
    uint8_t rxArray[2] = {0};
    bool res = true;
    SpiHandle_t* Node = SpiGetNode(num);
    EXPECT_NE(NULL, Node);

    memset(rxArray, 0xFF, sizeof(rxArray));
    ASSERT_TRUE(spi_dma_read(num, rxArray, sizeof(rxArray)));
    ASSERT_TRUE(Node->rx_done);
    print_hex(rxArray, TEST_SPI_SIZE);
    return res;
}

bool test_spi_dma_write(uint8_t num) {
    LOG_INFO(TEST, "%s():SPI%u", __FUNCTION__, num);
    uint8_t txArray[TEST_SPI_SIZE] = {0};
    bool res = true;
    SpiHandle_t* Node = SpiGetNode(num);
    EXPECT_NE(NULL, Node);

    memset(txArray, TEST_SPI_TX_PATTERN, sizeof(txArray));
    ASSERT_TRUE(spi_dma_write(num, txArray, sizeof(txArray)));
    ASSERT_TRUE(Node->tx_done);
    return res;
}

bool test_spi_dma_write_read(uint8_t num) {
    LOG_INFO(TEST, "%s(): SPI%u", __FUNCTION__, num);
    uint8_t txArray[TEST_SPI_SIZE] = {0};
    uint8_t rxArray[TEST_SPI_SIZE] = {0};
    bool res = true;
    SpiHandle_t* Node = SpiGetNode(num);
    EXPECT_NE(NULL, Node);

    memset(txArray, TEST_SPI_TX_PATTERN, sizeof(txArray));
    memset(rxArray, 0xFF, sizeof(rxArray));
    ASSERT_TRUE(spi_dma_write_read(num, txArray, rxArray, TEST_SPI_SIZE));
    ASSERT_TRUE(Node->txrx_done);
    ASSERT_TRUE(Node->tx_done);
    ASSERT_TRUE(Node->rx_done);
    print_hex(rxArray, TEST_SPI_SIZE);
    return res;
}

#define TEST_ARR_SIZE 5
bool test_spi_dma_loopback_num(uint8_t num) {
    LOG_INFO(TEST, "%s(): SPI%u", __FUNCTION__, num);
    uint8_t tx_array[TEST_ARR_SIZE] = {0};
    uint8_t rx_array[TEST_ARR_SIZE] = {0};
    bool res = true;
    SpiHandle_t* Node = SpiGetNode(num);
    ASSERT_NE(NULL, Node);

    memset(rx_array, 0, sizeof(rx_array));
    ASSERT_TRUE( array_incr(tx_array, sizeof(tx_array), 1));
    ASSERT_TRUE(spi_dma_write_read(num, tx_array, rx_array, TEST_ARR_SIZE));
    ASSERT_TRUE(Node->txrx_done);
    ASSERT_TRUE(Node->tx_done);
    ASSERT_TRUE(Node->rx_done);
    ASSERT_EQ_MEM(rx_array, tx_array, TEST_ARR_SIZE)
    return res;
}

#ifdef HAS_SPI1
bool test_spi1_write_dma(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_dma_write(1));
    return true;
}

bool test_spi1_write_read_dma(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_dma_write_read(1));
    return true;
}

bool test_spi1_read_dma(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_dma_read(1));
    return true;
}
#endif

#ifdef HAS_SPI2
bool test_spi2_write_dma(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_dma_write(2));
    return true;
}

bool test_spi2_write_read_dma(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_dma_write_read(2));
    return true;
}

bool test_spi2_read_dma(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_dma_read(2));
    return true;
}
//  tr spi2_dma_loopback
bool test_spi2_dma_loopback(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_dma_loopback_num(2));
    return true;
}


#endif


#ifdef HAS_SPI3
bool test_spi3_write_dma(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_dma_write(3));
    return true;
}

bool test_spi3_write_read_dma(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_dma_write_read(3));
    return true;
}

bool test_spi3_read_dma(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_dma_read(3));
    return true;
}
#endif


