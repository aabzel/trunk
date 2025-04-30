
#ifndef FONTS_H
#define FONTS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "font_types.h"

#ifdef HAS_FONT_12_X_6
extern const uint8_t gsc_ascii_1206[95][12];
#endif

#ifdef HAS_FONT_16_X_8
extern const uint8_t gsc_ascii_1608[95][16];
#endif

#ifdef HAS_FONT_24_X_12
extern const uint8_t gsc_ascii_2412[95][36];
#endif

extern const FontInfo_t FontInfo[];

int8_t Font2ByteInRow(Font_t font);
const FontInfo_t* Font2FontInfo(Font_t font);
Pixel_t FontPixelGet(int16_t x, int16_t y, char letter, Font_t font);
uint8_t Font2Size(Font_t font);
FontFrame_t Font2FontDimension(Font_t font);

#ifdef __cplusplus
}
#endif

#endif
