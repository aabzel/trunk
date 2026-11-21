#ifndef ILI9341_CONFIG_H
#define ILI9341_CONFIG_H

#include "std_includes.h"
#include "ili9341_types.h"

extern const Ili9341Config_t Ili9341Config[];
extern Ili9341Handle_t Ili9341Instance[];

uint32_t ili9341_get_cnt(void);

#endif /* ILI9341_CONFIG_H */
