
#ifndef FONT_TYPES_H
#define FONT_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "font_const.h"

typedef struct {
    uint8_t dx;
    uint8_t dy;
} FontFrame_t;

typedef struct {
    Font_t font;
    FontFrame_t dimension;
    uint8_t size;
    int8_t byte_in_row;
    char* name;
} FontInfo_t;

#ifdef __cplusplus
}
#endif

#endif
