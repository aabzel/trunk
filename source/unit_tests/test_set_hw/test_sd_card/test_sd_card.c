#include "test_sd_card.h"

#include <stdint.h>

#include "array.h"
#include "byte_utils.h"
#include "data_utils.h"
#include "debug_info.h"
#include "gpio_drv.h"
#include "log.h"
#include "sd_card_diag.h"
#include "sd_card_drv.h"
#include "spi_drv.h"
#include "unit_test_check.h"

static uint8_t read_block[BLOCK_SIZE_BYTE + 1];
static uint8_t write_array[BLOCK_SIZE_BYTE + 1];

bool test_sd_card_init(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(SD_CARD, LOG_LEVEL_DEBUG);
    set_log_level(SPI, LOG_LEVEL_DEBUG);
    bool res = true;
    EXPECT_TRUE(sd_card_init());
    set_log_level(SD_CARD, LOG_LEVEL_INFO);
    set_log_level(SPI, LOG_LEVEL_INFO);
    return res;
}

bool test_sd_card_read(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(SD_CARD, LOG_LEVEL_DEBUG);
    set_log_level(SPI, LOG_LEVEL_DEBUG);
    bool res = true;
    memset(read_block, 0, BLOCK_SIZE_BYTE);
    ASSERT_TRUE(sd_read_sector(10, read_block));
    print_hex_buf(read_block, BLOCK_SIZE_BYTE);
    set_log_level(SD_CARD, LOG_LEVEL_INFO);
    set_log_level(SPI, LOG_LEVEL_INFO);
    return res;
}

/*
 tsr test_sd_card_write_read+
 */
bool test_sd_card_write_read(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    set_log_level(SD_CARD, LOG_LEVEL_DEBUG);
    set_log_level(SPI, LOG_LEVEL_DEBUG);

    uint32_t block_num = 16;
    bool res = true;
    array_incr(write_array, BLOCK_SIZE_BYTE);

    ASSERT_TRUE(sd_write_sector(block_num, write_array));

    memset(read_block, 0, BLOCK_SIZE_BYTE);
    ASSERT_TRUE(sd_read_sector(block_num, read_block));

    ASSERT_EQ_MEM(write_array, read_block, BLOCK_SIZE_BYTE);

    set_log_level(SD_CARD, LOG_LEVEL_INFO);
    set_log_level(SPI, LOG_LEVEL_INFO);

    return res;
}

bool test_sd_card_write(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    set_log_level(SD_CARD, LOG_LEVEL_DEBUG);
    set_log_level(SPI, LOG_LEVEL_DEBUG);

    uint32_t block_num = 17;
    bool res = true;
    array_incr(write_array, BLOCK_SIZE_BYTE);
    ASSERT_TRUE(sd_write_sector(block_num, write_array));

    set_log_level(SD_CARD, LOG_LEVEL_INFO);
    set_log_level(SPI, LOG_LEVEL_INFO);
    return res;
}

bool test_sd_card_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_EQ(4, sizeof(Cmd8Arg_t));
    ASSERT_EQ(1, sizeof(R1_t));
    ASSERT_EQ(2, sizeof(R2_t));
    ASSERT_EQ(1, sizeof(DataResponseToken_t));
    ASSERT_EQ(4, sizeof(OCR_t));
    ASSERT_EQ(4, sizeof(ACmd41Arg_t));
    ASSERT_EQ(4, sizeof(R7Data_t));
    ASSERT_EQ(5, sizeof(R3_t));
    ASSERT_EQ(5, sizeof(R7_t));
    ASSERT_EQ(6, sizeof(SdFramePlane_t));
    ASSERT_EQ(6, sizeof(SdFrame_t));
    ASSERT_EQ(16, sizeof(CID_t));
    ASSERT_EQ(16, sizeof(CSD_t));

    ASSERT_STREQ("April 2001", Mdt2Str(0x14));
    return res;
}

const uint8_t exp_frame[6] = {0x52, 0x87, 0x65, 0x43, 0x21, 0xAB};
bool test_sd_card_frame(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    SdFrame_t spiFrame;
    memset(spiFrame.buff, 0, 6);

    spiFrame.one2 = 1;
    spiFrame.zero = 0;
    spiFrame.one1 = 1;
    spiFrame.index = 0x12;
    spiFrame.crc7 = 0x55;
    spiFrame.args = 0x87654321;
    print_hex_buf(exp_frame, 6);
    print_hex_buf(spiFrame.buff, 6);

    ASSERT_TRUE(reverse_byte_order_array(spiFrame.buff, 6));

    ASSERT_TRUE(res);
    return res;
}

bool test_sd_card_gpio(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(GPIO, LOG_LEVEL_DEBUG);
    const SpiConfig_t* SpiConfig = SpiGetConfig(SdCardConfig.spi_num);
    ASSERT_NE(NULL, SpiConfig);
    // EXPECT_EQ(GPIO__PULL_UP, gpio_get_pull(SdCardConfig.chip_sel.byte));
    EXPECT_EQ(GPIO__PULL_AIR, gpio_get_pull(SpiConfig->PadSck.byte));
    EXPECT_EQ(GPIO__PULL_UP, gpio_get_pull(SpiConfig->PadMiso.byte));
    EXPECT_EQ(GPIO__PULL_UP, gpio_get_pull(SpiConfig->PadMosi.byte));

    set_log_level(GPIO, LOG_LEVEL_INFO);
    return res;
}
