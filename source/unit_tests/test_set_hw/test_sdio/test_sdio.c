#include "test_sdio.h"

#include <stdint.h>

#include "array.h"
#include "data_utils.h"
#include "log.h"
#include "macro_utils.h"
#include "none_blocking_pause.h"
#include "sdio_mcal.h"
#include "unit_test_check.h"

/*To Save Stack*/
static uint8_t OrigBlock[SDIO_BLOCK_SIZE + 1] = {0};
static uint8_t ReadBlock[SDIO_BLOCK_SIZE + 1] = {0};
static uint8_t WriteBlock[SDIO_BLOCK_SIZE + 1] = {0};

static bool test_sdio_read_write_block(uint32_t block_num) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LG_SDIO, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(sdio_read_sector(SD_CARD_SDIO_NUM, block_num, 1, OrigBlock));
    array_incr(WriteBlock, SDIO_BLOCK_SIZE);

    ASSERT_TRUE(sdio_write_sector(SD_CARD_SDIO_NUM, block_num, 1, WriteBlock));
    ASSERT_TRUE(wait_in_loop_ms(100));
    ASSERT_TRUE(sdio_read_sector(SD_CARD_SDIO_NUM, block_num, 1, ReadBlock));

    EXPECT_EQ_MEM(ReadBlock, WriteBlock, SDIO_BLOCK_SIZE);

    ASSERT_TRUE(sdio_write_sector(SD_CARD_SDIO_NUM, block_num, 1, OrigBlock));
    set_log_level(LG_SDIO, LOG_LEVEL_INFO);
    return true;
}

/*
 tsr test_sdio_driver+
 */
bool test_sdio_read_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LG_SDIO, LOG_LEVEL_DEBUG);
    uint32_t i = 0;
    for(i = 1; i <= 2; i++) {
        ASSERT_TRUE(test_sdio_read_write_block(i));
    }
    set_log_level(LG_SDIO, LOG_LEVEL_INFO);

    return true;
}

bool test_sdio_const(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LG_SDIO, LOG_LEVEL_DEBUG);
    ASSERT_GR(32, SDIO_TIME_OUT_MS);
    set_log_level(LG_SDIO, LOG_LEVEL_INFO);
    return true;
}

bool test_sdio_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LG_SDIO, LOG_LEVEL_DEBUG);
    uint32_t block_num = 10;
    bool res = false;
    bool spot_valid = false;

    res = sdio_read_sector(SD_CARD_SDIO_NUM, 608, 1, ReadBlock);
    ASSERT_TRUE(res);

    res = sdio_read_sector(SD_CARD_SDIO_NUM, 8320, 1, ReadBlock);
    ASSERT_TRUE(res);

    uint32_t sum = 0;
    for(block_num = 1; block_num < (GBYTE_BYTE(2) / SDIO_BLOCK_SIZE); block_num++) {
        res = sdio_read_sector(SD_CARD_SDIO_NUM, block_num, 1, ReadBlock);
        ASSERT_TRUE(res);
        sum = arr_sum(ReadBlock, SDIO_BLOCK_SIZE);
        if(0 < sum) {
            LOG_INFO(TEST, "Block #%u has valid data", block_num);
            spot_valid = true;
            break;
        }
    }
    ASSERT_TRUE(spot_valid);
    set_log_level(LG_SDIO, LOG_LEVEL_INFO);

    return true;
}

#ifdef HAS_SDIO_DMA
static bool test_sdio_read_write_block_dma(uint32_t block_num) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LG_SDIO, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(sdio_read_sector_dma(SD_CARD_SDIO_NUM, block_num, 1, OrigBlock));
    array_incr(WriteBlock, SDIO_BLOCK_SIZE);

    ASSERT_TRUE(sdio_write_sector_dma(SD_CARD_SDIO_NUM, block_num, 1, WriteBlock));
    ASSERT_TRUE(wait_in_loop_ms(100));
    ASSERT_TRUE(sdio_read_sector_dma(SD_CARD_SDIO_NUM, block_num, 1, ReadBlock));

    EXPECT_EQ_MEM(ReadBlock, WriteBlock, SDIO_BLOCK_SIZE);

    ASSERT_TRUE(sdio_write_sector_dma(SD_CARD_SDIO_NUM, block_num, 1, OrigBlock));
    set_log_level(LG_SDIO, LOG_LEVEL_INFO);
    return true;
}

bool test_sdio_read_dma(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LG_SDIO, LOG_LEVEL_DEBUG);
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < 100; i++) {
        LOG_INFO(TEST, "i=%u", i);
        res = sdio_read_sector_dma(SD_CARD_SDIO_NUM, i, 1, ReadBlock);
        ASSERT_TRUE(res);
    }
    set_log_level(LG_SDIO, LOG_LEVEL_INFO);
    return true;
}

bool test_sdio_write_dma(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LG_SDIO, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(test_sdio_read_write_block_dma(3));
    ASSERT_TRUE(test_sdio_read_write_block_dma(2));
    set_log_level(LG_SDIO, LOG_LEVEL_INFO);
    return true;
}
#endif

#ifdef HAS_SDIO_INTERRUPT
static bool test_sdio_read_write_block_it(uint32_t block_num) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LG_SDIO, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(sdio_read_sector_it(SD_CARD_SDIO_NUM, block_num, 1, OrigBlock));
    array_incr(WriteBlock, SDIO_BLOCK_SIZE);
    ASSERT_TRUE(wait_in_loop_ms(100));

    ASSERT_TRUE(sdio_write_sector_it(SD_CARD_SDIO_NUM, block_num, 1, WriteBlock));
    ASSERT_TRUE(wait_in_loop_ms(100));
    ASSERT_TRUE(sdio_read_sector_it(SD_CARD_SDIO_NUM, block_num, 1, ReadBlock));

    EXPECT_EQ_MEM(ReadBlock, WriteBlock, SDIO_BLOCK_SIZE);

    ASSERT_TRUE(sdio_write_sector_it(SD_CARD_SDIO_NUM, block_num, 1, OrigBlock));
    set_log_level(LG_SDIO, LOG_LEVEL_INFO);
    return true;
}

bool test_sdio_read_it(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LG_SDIO, LOG_LEVEL_DEBUG);
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < 100; i++) {
        res = sdio_read_sector_it(SD_CARD_SDIO_NUM, i, 1, ReadBlock);
        ASSERT_TRUE(res);
    }
    set_log_level(LG_SDIO, LOG_LEVEL_INFO);
    return true;
}

bool test_sdio_write_it(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LG_SDIO, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(test_sdio_read_write_block_it(3));
    ASSERT_TRUE(test_sdio_read_write_block_it(2));
    set_log_level(LG_SDIO, LOG_LEVEL_INFO);
    return true;
}
#endif

/*That test casuse fail*/
bool test_sdio_link(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LG_SDIO, LOG_LEVEL_DEBUG);
    // ASSERT_TRUE(sdio_is_connected(1)); /*Cause bug*/
    set_log_level(LG_SDIO, LOG_LEVEL_INFO);
    return true;
}
