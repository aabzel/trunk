
#ifndef FONT_CONST_H
#define FONT_CONST_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FONT_12 = 12,
    FONT_16 = 16,
    FONT_24 = 24,

    FONT_UNDEF = 0,
} Font_t;

typedef enum {
    PIXEL_OFF = 0,
    PIXEL_ON = 1,

    PIXEL_UNDEF = 2,
} Pixel_t;

#ifdef __cplusplus
}
#endif

#endif
