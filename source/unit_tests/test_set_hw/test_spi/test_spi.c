#include "test_spi.h"

#include <string.h>

#include "debug_info.h"
#include "gpio_mcal.h"
#include "spi_drv.h"
#include "spi_config.h"
#include "sys_config.h"
#include "unit_test_check.h"

static bool test_spi_read_num(uint8_t num) {
    LOG_INFO(TEST, "%s(): SPI %u", __FUNCTION__,num);
    uint8_t array[2];
    bool res = true;
    SpiHandle_t* Node = SpiGetNode(num);
    EXPECT_NE(NULL, Node);
    uint32_t init_int_cnt = Node->it_cnt;
    memset(array,0xFF,sizeof(array));
    ASSERT_TRUE(spi_api_read(num, array, sizeof(array)));
    print_hex(array, sizeof(array));
    EXPECT_GR(init_int_cnt, Node->it_cnt);
    return res;
}

static bool test_spi_write_num(uint8_t num) {
    LOG_INFO(TEST, "%s(): SPI %u", __FUNCTION__,num);
    uint8_t array[2];
    bool res = true;
    SpiHandle_t* Node = SpiGetNode(num);
    EXPECT_NE(NULL, Node);
    uint32_t init_int_cnt = Node->it_cnt;
    memset(array,0xFF,sizeof(array));
    ASSERT_TRUE(spi_api_write(num, array, sizeof(array)));
    EXPECT_GR(init_int_cnt, Node->it_cnt);
    return res;
}

static bool test_spi_write_null_num(uint8_t num) {
    LOG_INFO(TEST, "%s(): SPI %u", __FUNCTION__,num);
    bool res = true;
    uint8_t array[2];
    ASSERT_FALSE(spi_api_write(num, array, 0));
    ASSERT_FALSE(spi_api_write(num, NULL, 0));
    return res;
}

#ifdef HAS_SPI0
bool test_spi0_write(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE( test_spi_write_num(0));
    return true;
}
#endif

#ifdef HAS_SPI1
bool test_spi1_write(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_write_num(1));
    ASSERT_TRUE(test_spi_write_null_num(1));
    return true;
}
#endif

#ifdef HAS_SPI2
bool test_spi2_write(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE( test_spi_write_num(2));
    ASSERT_TRUE( test_spi_write_null_num(2));
    return true;
}
#endif

#ifdef HAS_SPI3
bool test_spi3_write(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE( test_spi_write_num(3));
    ASSERT_TRUE( test_spi_write_null_num(3));
    return true;
}
#endif

#ifdef HAS_SPI4
bool test_spi4_write(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE( test_spi_write_num(4));
    ASSERT_TRUE(test_spi_write_null_num(4));
    return true;
}
#endif

#ifdef HAS_SPI_WAIT_WRITE
bool test_spi_wait_write(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t array[2];
    gpio_set_state(DIO_SX1262_SS, 1);
#ifdef HAS_CAN
    gpio_set_state(DIO_CAN_SS, 1);
#endif
    memset(array,0xFF,sizeof(array));
    ASSERT_TRUE( spi_wait_write(SPI0_INX, array, sizeof(array)));
    ASSERT_TRUE( spi_wait_tx_done(SPI0_INX));
    return true;
}
#endif


#ifdef HAS_SPI0
bool test_spi0_read(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
#ifdef DIO_SX1262_SS
    gpio_set_state(DIO_SX1262_SS, 1);
#endif
#ifdef HAS_CAN
    gpio_set_state(DIO_CAN_SS, 1);
#endif
    ASSERT_TRUE(test_spi_read_num(0));
    return true;
}
#endif

#ifdef HAS_SPI1
bool test_spi1_read(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_read_num(1));
    return true;
}
#endif

#ifdef HAS_SPI2
bool test_spi2_read(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_read_num(2));
    return true;
}
#endif

#ifdef HAS_SPI3
bool test_spi3_read(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_read_num(3));
    return true;
}
#endif

#ifdef HAS_SPI4
bool test_spi4_read(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_spi_read_num(4));
    return true;
}
#endif
