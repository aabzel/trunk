#include "test_ili9341.h"

#include "unit_test_check.h"
#include "ili9341_mcal.h"
#include "fonts_english.h"
#include "fonts_russian.h"

bool test_ili9341_read_unique_id(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    Ili9341Id_t ID = {0};
    res = ili9341_read_id(1, &ID.dword);
    ASSERT_TRUE(res);
    LOG_WARNING(TEST, "ID:%s", Ili9341IdToStr(&ID));

    uint8_t man_id1 = 0;
    res = ili9341_read_man_id1(1, &man_id1);
    ASSERT_TRUE(res);
    LOG_WARNING(TEST, "ManID1:0x%02x", man_id1);

    uint8_t driver_version = 0;
    res = ili9341_read_driver_version_id2(1, &driver_version);
    ASSERT_TRUE(res);
    LOG_WARNING(TEST, "driverVersion:0x%02x", driver_version);

    return res;
}

bool test_ili9341_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_EQ(2, sizeof(Ili9341Pixel_t) );
    ASSERT_EQ(4, sizeof(Ili9341Id_t) );
    return res;
}

#define REC_START_X 2
#define REC_WIDTH 235
#define REC_HEIGHT 30
bool test_ili9341_draw_rec_all(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE( ili9341_draw_rec(1, ili9341_mix_color( 30, 30, 30), REC_START_X, 7* REC_HEIGHT, REC_WIDTH, REC_HEIGHT));
    ASSERT_TRUE( ili9341_draw_rec(1, ili9341_mix_color( 30, 0, 0),   REC_START_X, 1,             REC_WIDTH, REC_HEIGHT));
    ASSERT_TRUE( ili9341_draw_rec(1, ili9341_mix_color( 30, 30, 0),  REC_START_X, 5* REC_HEIGHT, REC_WIDTH, REC_HEIGHT));
    ASSERT_TRUE( ili9341_draw_rec(1, ili9341_mix_color( 0, 30, 0),   REC_START_X, 1* REC_HEIGHT, REC_WIDTH, REC_HEIGHT));
    ASSERT_TRUE( ili9341_draw_rec(1, ili9341_mix_color( 0, 0, 30),   REC_START_X, 2* REC_HEIGHT, REC_WIDTH, REC_HEIGHT));
    ASSERT_TRUE( ili9341_draw_rec(1, ili9341_mix_color( 0, 30, 30),  REC_START_X, 6* REC_HEIGHT, REC_WIDTH, REC_HEIGHT));
    ASSERT_TRUE( ili9341_draw_rec(1, ili9341_mix_color( 0, 0, 0),    REC_START_X, 3* REC_HEIGHT, REC_WIDTH, REC_HEIGHT));
    ASSERT_TRUE( ili9341_draw_rec(1, ili9341_mix_color( 30, 0, 30),  REC_START_X, 4* REC_HEIGHT, REC_WIDTH, REC_HEIGHT));
    return res;
}

bool test_ili9341_draw_rec_green(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE( ili9341_draw_rec(1, ili9341_mix_color( 0, 30, 0),   1, 1, 100, 100));
    return res;
}

bool test_ili9341_pixel_one(const uint8_t num,
                            const uint16_t color,
                            uint16_t start_x,
                            uint16_t start_y ) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;

    res = ili9341_draw_pixel( num, start_x, start_y, color);
    ASSERT_TRUE(res);
    uint16_t read_color = 0;

    res = ili9341_read_pixel( num, start_x, start_y, &read_color);
    ASSERT_TRUE(res);

    LOG_INFO(TEST, "Read:0x%04x,Set:0x%04x", read_color,color);
    ASSERT_EQ(color, read_color);
    return res;
}

bool test_ili9341_pixel_00(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE( test_ili9341_pixel_one(1, ili9341_mix_color( 30, 0, 0),   1, 1));
    ASSERT_TRUE( test_ili9341_pixel_one(1, ili9341_mix_color( 0, 30, 0),   1, 1));
    ASSERT_TRUE( test_ili9341_pixel_one(1, ili9341_mix_color( 0, 0, 30),   1, 1));
    return res;
}

bool test_ili9341_draw_rec_red(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    res = ili9341_column_address_set(1, 20, 40);
    ASSERT_TRUE(res);

    res = ili9341_page_address_set(1, 80, 100);
    ASSERT_TRUE(res);

    uint16_t data[400] = {0};
    uint32_t cnt = ARRAY_SIZE(data);
    res = ili9341_pix_array_color_set(COLOR_RED,30,data,cnt);
    res = ili9341_memory_write(1, data, cnt);
    ASSERT_TRUE(res);

    return res;
}

bool test_ili9341_draw_char(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE( ili9341_write_char(1, 3, 3, 'a', Font_16x26, 0xFFFF, 0x0000) );
    ASSERT_TRUE( ili9341_write_char(1, 19, 50, 'b', Font_16x26, 0xFFFF, 0x0000) );
    ASSERT_TRUE( ili9341_write_char(1, 35, 100, 'c', Font_16x26, 0xFFFF, 0x0000) );
    return res;
}

bool test_ili9341_write_string(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE( ili9341_write_string(1,0, 0,"Hello, world!",Font_7x10, 0xFFFF, 0x0000));
    ASSERT_TRUE( ili9341_write_string(1,0, 10,"qwertyuiop[]",Font_7x10, 0xFFFF, 0x0000));
    ASSERT_TRUE( ili9341_write_string(1,0, 20,"asdfghjkl;'",Font_7x10, 0xFFFF, 0x0000));
    ASSERT_TRUE( ili9341_write_string(1,0, 30,"zxcvbnm,./",Font_7x10, 0xFFFF, 0x0000));
    return res;
}

bool test_ili9341_rus_chars(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    char* RusText= "Привет, Мир!"; // 12 = 3 + 9*2
    LOG_INFO(TEST, "Len:%u",  strlen(RusText)); // 21
    LOG_INFO(TEST, "[%s]", RusText);
    ASSERT_TRUE( ili9341_write_string(1,0, 0, RusText, FontRus_7x10, 0xFFFF, 0x0000));
    //uint16_t letter = 'Р№'; /*error: multi-character character constant [-Werror=multichar]*/
    return res;
}

bool test_ili9341_print_font(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE(  ili9341_write_font(1, 0, 0, 0, FontRus_7x10, 0xFFFF, 0)  );
    ASSERT_TRUE(  ili9341_write_font(1, 10, 0, 1, FontRus_7x10, 0xFFFF, 0)  );
    ASSERT_TRUE(  ili9341_write_font(1, 20, 0, 6, FontRus_7x10, 0xFFFF, 0)  );
    //uint16_t letter = 'Р№'; /*error: multi-character character constant [-Werror=multichar]*/

    uint8_t i = 0 ;
    uint8_t cnt = 65 ;
    uint16_t y =0;
    uint16_t x = 0;
    for(i=0;i<cnt;i++) {
        if(310<x){
            x = 0;
            y += 10;
        }

        ASSERT_TRUE(  ili9341_write_font(1, x, y, i, FontRus_7x10, 0xFFFF, 0)  );
        x+= 7;
    }
    return res;
}

bool test_ili9341_write_utf8_string(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
     ili9341_write_utf8_string(1,0, 0,"Привет, Мир!",FontRus_7x10, 0xFFFF, 0x0000);
     ili9341_write_utf8_string(1,0, 11,"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ",FontRus_7x10, 0xFFFF, 0x0000);
     ili9341_write_utf8_string(1,0, 22,"абвгдеёжзийклмнопрстуфхцчшщъыьэюя",FontRus_7x10, 0xFFFF, 0x0000);
    return res;
}


