#ifndef TEST_ILI9341_H
#define TEST_ILI9341_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"
#include "ili9341_mcal.h"

#ifndef HAS_TEST_ILI9341
#error "+HAS_ILI9341_TESTS"
#endif

bool test_ili9341_pixel_one(const uint8_t num, const uint16_t color, uint16_t start_x, uint16_t start_y );

bool test_ili9341_write_utf8_string(void);
bool test_ili9341_rus_chars(void);
bool test_ili9341_write_string(void);
bool test_ili9341_draw_char(void);
bool test_ili9341_types(void);
bool test_ili9341_pixel_00(void);
bool test_ili9341_draw_rec_all(void);
bool test_ili9341_draw_rec_red(void);
bool test_ili9341_read_unique_id(void) ;
bool test_ili9341_draw_rec_green(void) ;
bool test_ili9341_print_font(void) ;

#define TEST_SUIT_ILI9341                                               \
        {"ili9341_types", test_ili9341_types},                          \
        {"ili9341_rus_chars", test_ili9341_rus_chars},                  \
        {"ili9341_pixel_00", test_ili9341_pixel_00},                  \
        {"ili9341_draw_char", test_ili9341_draw_char},                  \
        {"ili9341_draw_rec_red", test_ili9341_draw_rec_red},            \
        {"ili9341_draw_rec_green", test_ili9341_draw_rec_green},        \
        {"ili9341_draw_rec_all", test_ili9341_draw_rec_all},            \
        {"ili9341_write_string", test_ili9341_write_string},            \
        {"ili9341_write_utf8_string", test_ili9341_write_utf8_string},  \
        {"ili9341_print_font", test_ili9341_print_font},                \
        {"ili9341_read_unique_id", test_ili9341_read_unique_id},

#ifdef __cplusplus
}
#endif

#endif /* TEST_ILI9341_H */
