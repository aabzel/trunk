#ifndef ILI9341_MCAL_H
#define ILI9341_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ili9341_config.h"
#include "ili9341_types.h"
#include "led_general_const.h"
#include "fonts_english.h"

#ifdef HAS_ILI9341_DIAG
#include "ili9341_diag.h"
#endif

/* API */
Ili9341Handle_t* Ili9341GetNode(uint8_t num);
const Ili9341Config_t* Ili9341GetConfig(uint8_t num);
bool Ili9341IsValidConfig(const Ili9341Config_t* const Config);

#ifdef HAS_ILI9341_CUSTOM
const Ili9341Info_t* Ili9341GetInfo(uint8_t num);
#endif

bool ili9341_mcal_init(void);
bool ili9341_init_custom(void);
bool ili9341_init_one(uint8_t num);

bool ili9341_proc_one(uint8_t num);
bool ili9341_proc(void);

/*setters*/

bool ili9341_write_utf8_string(uint8_t num ,
                               uint16_t xi, uint16_t yi,
                               const char* const str,
                               FontDef font,
                               uint16_t color,
                               uint16_t bgcolor);

bool ili9341_write_font(uint8_t num ,
                        uint16_t x,
                        uint16_t y,
                        uint16_t offset,
                        FontDef font,
                        uint16_t color,
                        uint16_t bgcolor) ;
bool ili9341_writer_set(const uint8_t num);
bool ili9341_writer_transmit(void* base);
void ili9341_1_putc(void* stream_ptr, char ch);
void ili9341_1_puts(void* stream_ptr, const char* str, int32_t len);
bool ili9341_write_cmd_param(const uint8_t num,
                             const Ili9341Cmd_t command,
                             const uint8_t * const param,
                             const uint32_t cnt);
bool ili9341_write_string(uint8_t num ,
                          uint16_t x, uint16_t y,
                          const char* str,
                          FontDef font,
                          uint16_t color,
                          uint16_t bgcolor);
bool ili9341_write_utf8_char(uint8_t num ,
                             uint16_t x,
                             uint16_t y,
                             char* start,
                             FontDef font,
                             uint16_t color,
                             uint16_t bgcolor);
bool ili9341_write_char(uint8_t num , uint16_t x, uint16_t y, char ch,
                        FontDef font, uint16_t color, uint16_t bgcolor);
bool ili9341_draw_horizontal_line(const uint8_t num, uint16_t x, uint16_t y, uint16_t width, uint16_t colour);
bool ili9341_draw_vertical_line(const uint8_t num, uint16_t x, uint16_t y, uint16_t height, uint16_t colour);

bool ili9341_fill_screen(const uint8_t num, uint16_t colour);
bool ili9341_pix_array_color_set( const Color_t color, const uint8_t intensity,
                                  uint16_t *const data, const uint32_t cnt);
bool ili9341_memory_write(const uint8_t num,  const uint16_t * const word, uint32_t cnt);
bool ili9341_column_address_set(const uint8_t num,
                                const uint16_t start_column,
                                const uint16_t end_column);
bool ili9341_page_address_set(const uint8_t num,
                                const uint16_t start_page,
                                const uint16_t end_page);
bool ili9341_sleep_out(const uint8_t num);
bool ili9341_software_reset(uint8_t num);
bool ili9341_set_orientation(uint8_t num, ScreenOrientation_t orientation);
bool ili9341_display_on(const uint8_t num);
bool ili9341_normal_mode_on(const uint8_t num);
bool ili9341_draw_pixel(uint8_t num, uint16_t x,uint16_t y,uint16_t colour);
bool ili9341_draw_rec(const uint8_t num,
                      const uint16_t color,
                      uint16_t start_x,
                      uint16_t start_y,
                      uint16_t width,
                      uint16_t height ) ;

/*getters*/
uint16_t ili9341_mix_color( const uint16_t red, const uint16_t green, const uint16_t blue);

Ili9341Pixel_t ili9341_pix_color_set( const Color_t color, const uint8_t intensity);
bool ili9341_raw_reg_diag(uint8_t num);
bool ili9341_is_valid_num(const uint8_t num);
bool ili9341_read_id(const uint8_t num, uint32_t * const id);
bool ili9341_read_pixel(uint8_t num, uint16_t start_x, uint16_t start_y, uint16_t * const colour);
bool ili9341_read_man_id1(const uint8_t num, uint8_t * const pId1);
bool ili9341_read_driver_version_id2(const uint8_t num, uint8_t * const pId2) ;
bool ili9341_read_memory(const uint8_t num, uint16_t * const words, const uint32_t cnt);

#ifdef __cplusplus
}
#endif

#endif /* ILI9341_MCAL_H */
