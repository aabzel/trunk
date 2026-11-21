#ifndef FONTS_TYPES_H
#define FONTS_TYPES_H

#include <stdint.h>


typedef struct {
    uint16_t index;
    char* utf8;
} FontLettetInfo_t;



typedef struct {
    const uint8_t width;
    uint8_t height;
    const uint16_t *data;
} FontDef;

#endif // FONTS_TYPES_H
