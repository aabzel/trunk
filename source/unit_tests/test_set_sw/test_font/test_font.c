#include "test_font.h"

#include "font_diag.h"
#include "fonts.h"
#include "unit_test_check.h"

bool test_font_hash(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(2, Font2ByteInRow(FONT_12));
    EXPECT_EQ(2, Font2ByteInRow(FONT_16));
    EXPECT_EQ(3, Font2ByteInRow(FONT_24));

    EXPECT_EQ(12, Font2Size(FONT_12));
    EXPECT_EQ(16, Font2Size(FONT_16));
    EXPECT_EQ(36, Font2Size(FONT_24));
    return res;
}

bool test_font_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(2, sizeof(FontFrame_t));
    EXPECT_EQ(1, sizeof(Font_t));
    EXPECT_EQ(1, sizeof(Pixel_t));
    return res;
}

#ifdef HAS_FONT_24_X_12

bool test_font_24(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    char letter = ' ';
    while('~' != letter) {
        EXPECT_TRUE(font_diag_char(letter, FONT_24));
        letter++;
    }
    return res;
}

bool test_font_raw_24(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    char letter = ' ';
    while('~' != letter) {
        EXPECT_TRUE(font_diag_char_raw(letter, FONT_24));
        letter++;
    }
    return res;
}
#endif

#ifdef HAS_FONT_16_X_8
bool test_font_16(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(FONT, LOG_LEVEL_DEBUG);
    bool res = true;
    char letter = ' ';
    while('~' != letter) {
        EXPECT_TRUE(font_diag_char(letter, FONT_16));
        letter++;
    }

    set_log_level(FONT, LOG_LEVEL_INFO);
    return res;
}

bool test_font_raw_16(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(FONT, LOG_LEVEL_DEBUG);
    bool res = true;
    char letter = ' ';
    while('~' != letter) {
        EXPECT_TRUE(font_diag_char_raw(letter, FONT_16));
        letter++;
    }

    set_log_level(FONT, LOG_LEVEL_INFO);
    return res;
}
#endif

#ifdef HAS_FONT_12_X_6
bool test_font_12(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;

    char letter = ' ';
    while('~' != letter) {
        EXPECT_TRUE(font_diag_char(letter, FONT_12));
        letter++;
    }

    return res;
}

bool test_font_raw_12(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;

    char letter = ' ';
    while('~' != letter) {
        EXPECT_TRUE(font_diag_char_raw(letter, FONT_12));
        letter++;
    }

    return res;
}
#endif

/*
https://www.exploringbinary.com/twos-complement-converter/
*/
