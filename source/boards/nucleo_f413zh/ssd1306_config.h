#ifndef SSD1306_CONFIG_H
#define SSD1306_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "ssd1306_types.h"

extern const Ssd1306Config_t Ssd1306Config[];
extern Ssd1306Handle_t Ssd1306Instance[];

uint32_t ssd1306_get_cnt(void);

#endif /* SSD1306_CONFIG_H */
