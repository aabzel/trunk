#include "test_spi_interrupt.h"
#include "test_spi.h"

#include <string.h>

#include "debug_info.h"
#include "gpio_mcal.h"
#include "spi_interrupt.h"
#include "spi_mcal.h"
#include "sys_config.h"
#include "unit_test_check.h"

bool test_spi_write_interrupt(uint8_t num) {
    LOG_INFO(TEST, "%s():SPI%u", __FUNCTION__, num);
    uint8_t txArray[TEST_SPI_SIZE] = {0};
    bool res = true;
    SpiHandle_t* Node = SpiGetNode(num);
    EXPECT_NE(NULL, Node);
    Node->tx_done = false;
    memset(txArray, TEST_SPI_TX_PATTERN, sizeof(txArray));
    ASSERT_TRUE(spi_write_interrupt(num, txArray, sizeof(txArray)));
    ASSERT_TRUE(Node->tx_done);
    return res;
}

bool test_spi_write_read_interrupt(uint8_t num) {
    LOG_INFO(TEST, "%s(): SPI%u", __FUNCTION__, num);
    uint8_t txArray[TEST_SPI_SIZE] = {0};
    uint8_t rxArray[TEST_SPI_SIZE] = {0};
    bool res = true;
    SpiHandle_t* Node = SpiGetNode(num);
    EXPECT_NE(NULL, Node);

    memset(txArray, TEST_SPI_TX_PATTERN, sizeof(txArray));
    memset(rxArray, 0xFF, sizeof(rxArray));
    ASSERT_TRUE(spi_write_read_interrupt(num, txArray, rxArray, TEST_SPI_SIZE));
    ASSERT_TRUE(Node->tx_done);
    ASSERT_TRUE(Node->rx_done);
    print_hex(rxArray, TEST_SPI_SIZE);
    return res;
}

bool test_spi_read_interrupt(uint8_t num) {
    LOG_INFO(TEST, "%s():SPI%u", __FUNCTION__, num);
    uint8_t rxArray[TEST_SPI_SIZE] = {0};
    bool res = true;
    SpiHandle_t* Node = SpiGetNode(num);
    EXPECT_NE(NULL, Node);
    Node->rx_done = false ;
    memset(rxArray, 0xFF, sizeof(rxArray));
    ASSERT_TRUE(spi_read_interrupt(num, rxArray, sizeof(rxArray)));
    ASSERT_TRUE(Node->rx_done);
    print_hex(rxArray, TEST_SPI_SIZE);
    return res;
}

//---------------------------------

#ifdef HAS_SPI1
bool test_spi1_write_interrupt(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_write_interrupt(1));
    return true;
}

bool test_spi1_write_read_interrupt(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_write_read_interrupt(1));
    return true;
}

bool test_spi1_read_interrupt(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_read_interrupt(1));
    return true;
}
#endif


#ifdef HAS_SPI2

bool test_spi2_write_interrupt(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_write_interrupt(2));
    return true;
}

bool test_spi2_write_read_interrupt(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_write_read_interrupt(2));
    return true;
}

bool test_spi2_read_interrupt(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_read_interrupt(2));
    return true;
}
#endif


#ifdef HAS_SPI3
bool test_spi3_write_interrupt(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_write_interrupt(3));
    return true;
}

bool test_spi3_write_read_interrupt(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_write_read_interrupt(3));
    return true;
}

bool test_spi3_read_interrupt(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_read_interrupt(3));
    return true;
}
#endif



