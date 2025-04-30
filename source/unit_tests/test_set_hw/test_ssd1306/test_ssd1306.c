#include "test_ssd1306.h"

#include <string.h>

#include "log.h"
#include "none_blocking_pause.h"
#include "ssd1306_drv.h"
#include "str_utils.h"
#include "unit_test_check.h"

bool test_ssd1306_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(SSD1306, LOG_LEVEL_DEBUG);
    bool res = true;

    EXPECT_EQ(1, sizeof(ControlByte_t));
    EXPECT_EQ(1, sizeof(Ssd1306Command_t));
    EXPECT_EQ(2, sizeof(FontFrame_t));

    set_log_level(SSD1306, LOG_LEVEL_INFO);
    return res;
}

bool test_ssd1306_hash_tables(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(SSD1306, LOG_LEVEL_DEBUG);
    set_log_level(SSD1306, LOG_LEVEL_INFO);

    return res;
}

bool test_ssd1306_connected(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(SSD1306, LOG_LEVEL_DEBUG);
    set_log_level(I2C, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(ssd1306_is_connected(1));

    set_log_level(SSD1306, LOG_LEVEL_INFO);
    set_log_level(I2C, LOG_LEVEL_INFO);
    return res;
}

bool test_ssd1306_screen(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(SSD1306, LOG_LEVEL_DEBUG);
    set_log_level(I2C, LOG_LEVEL_DEBUG);

    Ssd1306Handle_t* Node = Ssd1306GetNode(1);
    ASSERT_NE(0, Node);
    memset(Node->FrameBuffer, 0, 1024);

    memset(&Node->FrameBuffer[0 * SSD1306_PAGE_SIZE], 0x55, SSD1306_PAGE_SIZE);
    memset(&Node->FrameBuffer[1 * SSD1306_PAGE_SIZE], 0, SSD1306_PAGE_SIZE);
    memset(&Node->FrameBuffer[2 * SSD1306_PAGE_SIZE], 0x81, SSD1306_PAGE_SIZE);
    memset(&Node->FrameBuffer[3 * SSD1306_PAGE_SIZE], 0, SSD1306_PAGE_SIZE);
    memset(&Node->FrameBuffer[4 * SSD1306_PAGE_SIZE], 0xc3, SSD1306_PAGE_SIZE);
    memset(&Node->FrameBuffer[5 * SSD1306_PAGE_SIZE], 0, SSD1306_PAGE_SIZE);
    memset(&Node->FrameBuffer[6 * SSD1306_PAGE_SIZE], 0xe7, SSD1306_PAGE_SIZE);
    memset(&Node->FrameBuffer[7 * SSD1306_PAGE_SIZE], 0, SSD1306_PAGE_SIZE);

    ASSERT_TRUE(ssd1306_set_memory_addressing_mode(1, SSD1306_MEM_ADDR_MODE_HORIZONTAL));

    ASSERT_TRUE(ssd1306_write_data(1, Node->FrameBuffer, 1024));

    set_log_level(SSD1306, LOG_LEVEL_INFO);
    set_log_level(I2C, LOG_LEVEL_INFO);
    return res;
}

bool test_ssd1306_dot(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(SSD1306, LOG_LEVEL_DEBUG);
    set_log_level(I2C, LOG_LEVEL_DEBUG);

    uint32_t i = 0;
    ASSERT_TRUE(ssd1306_sram_clean(1));
    for(i = 0; i < 63; i++) {
        ASSERT_TRUE(ssd1306_write_dot(1, i, i, true));
    }

    ASSERT_TRUE(ssd1306_update(1));

    set_log_level(SSD1306, LOG_LEVEL_INFO);
    set_log_level(I2C, LOG_LEVEL_INFO);
    return res;
}

bool test_ssd1306_char(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(SSD1306, LOG_LEVEL_DEBUG);
    set_log_level(I2C, LOG_LEVEL_DEBUG);

    ASSERT_TRUE(ssd1306_sram_clean(1));

    ASSERT_TRUE(ssd1306_write_char(1, 0, 0, 'a', FONT_12));
    ASSERT_TRUE(ssd1306_write_char(1, 12, 0, 'b', FONT_12));
    ASSERT_TRUE(ssd1306_write_char(1, 24, 0, 'c', FONT_12));

    ASSERT_TRUE(ssd1306_update(1));

    set_log_level(SSD1306, LOG_LEVEL_INFO);
    set_log_level(I2C, LOG_LEVEL_INFO);
    return res;
}

bool test_ssd1306_text(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(SSD1306, LOG_LEVEL_DEBUG);
    set_log_level(I2C, LOG_LEVEL_DEBUG);
    bool res = true;

    ASSERT_TRUE(ssd1306_write_string(1, 0, 0, STRING_COMMA_LENGTH("Hello World!"), FONT_12));
    ASSERT_TRUE(ssd1306_write_string(1, 0, 12, STRING_COMMA_LENGTH("Second Line"), FONT_12));
    ASSERT_TRUE(ssd1306_write_string(1, 0, 2 * 12, STRING_COMMA_LENGTH("third Line"), FONT_12));

    set_log_level(SSD1306, LOG_LEVEL_INFO);
    set_log_level(I2C, LOG_LEVEL_INFO);
    return res;
}
