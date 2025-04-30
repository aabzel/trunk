#ifndef DISPLAY_DRV_H
#define DISPLAY_DRV_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "display_config.h"
#include "display_const.h"
#include "display_dep.h"
#include "fonts.h"
#include "display_types.h"

bool display_init(void);
bool display_write_string(uint8_t num, int16_t x_start, int16_t y_start, char* const str, size_t len, Font_t font) ;
bool display_proc(void);
bool display_write_char(uint8_t num, int16_t x, int16_t y, char str, Font_t font);
bool display_init_one(uint8_t num);
bool display_sram_clean(uint8_t num);
const DisplayConfig_t* DisplayGetConfNode(uint8_t id_num);
DisplayHandle_t* DisplayGetNode(uint8_t id_num);

#endif /* DISPLAY_DRV_H */
