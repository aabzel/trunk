#ifndef SSD1306_DRV_H
#define SSD1306_DRV_H

#include <stddef.h>

#include "std_includes.h"
#include "ssd1306_config.h"
#include "ssd1306_types.h"
#ifdef HAS_SSD1306_DIAG
#include "ssd1306_diag.h"
#endif

#ifdef HAS_FONT
#include "fonts.h"
#endif

//API
const Ssd1306Config_t* Ssd1306GetConfig(uint8_t id_num);
Ssd1306Handle_t* Ssd1306GetNode(uint8_t id_num);
bool ssd1306_mcal_init(void);
bool ssd1306_init_custom(void);
bool ssd1306_init_one(uint8_t num);
bool ssd1306_proc_one(uint8_t num);
bool ssd1306_proc(void);

bool is_valid_pixel(int16_t x, int16_t y);

#ifdef HAS_FONT
bool ssd1306_write_char(uint8_t num, int16_t x, int16_t y, char str, Font_t font);
bool ssd1306_write_string(uint8_t num, int16_t x, int16_t y, char* str, size_t len, Font_t font);
#endif
bool ssd1306_write_dot(uint8_t num, int16_t x, int16_t y, bool on_off);
bool ssd1306_check(void);
bool ssd1306_clock(bool on_off);
bool ssd1306_write_cmd(uint8_t num, Ssd1306Command_t cmd);
bool ssd1306_write_data(uint8_t num, uint8_t* array, uint32_t size);
bool ssd1306_sram_clean(uint8_t num);
bool ssd1306_update(uint8_t num);
bool ssd1306_write_data_ll(Ssd1306Handle_t* const Node, Ssd1306Command_t cmd);
bool ssd1306_write_cmd_ll(Ssd1306Handle_t* Node, Ssd1306Command_t cmd);
bool ssd1306_is_connected(uint8_t num);
bool ssd1306_write_cmd2_ll(Ssd1306Handle_t* Node, Ssd1306Command_t cmd1, Ssd1306Command_t cmd2);
bool ssd1306_set_display_start_line(uint8_t num, uint8_t start_line);
bool ssd1306_set_display_offset(uint8_t num, uint8_t offset);
bool ssd1306_set_memory_addressing_mode(uint8_t num, Ssd1306MemoryAddressingMode_t memory_addressing_mode);
bool ssd1306_set_contrast(uint8_t num, uint8_t contrast);
bool ssd1306_set_multiplex_ratio(uint8_t num, uint8_t multiplex_ratio);
bool ssd1306_set_page_start_addr(uint8_t num, Ssd1306Page_t page);
//bool ssd1306_set_display_clock_ll(Ssd1306Handle_t* Node);
bool ssd1306_read_reg(uint8_t reg_addr, uint8_t* reg_val);
bool ssd1306_reset(void);
bool ssd1306_write_lazy_reg(uint8_t reg_addr, uint8_t reg_val);
bool ssd1306_write_reg(uint8_t reg_addr, uint8_t reg_val);
bool ssd1306_write_frame(uint8_t num, Ssd1306Command_t cmd, uint8_t data);
uint32_t ssd1306_reg_cnt(void);
uint8_t ssd1306_get_chip_addr(uint8_t id_num);

#endif /* SSD1306_DRV_H */
