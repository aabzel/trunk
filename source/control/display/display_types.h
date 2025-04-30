#ifndef DISPLAY_TYPES_H
#define DISPLAY_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#ifdef HAS_PC
#include <stdio.h>
#endif

#include "display_const.h"

#define DISPLAY_CONNON_VARIABLES                \
    uint8_t num;                                                  \
    bool valid;                                                   \
    uint16_t page_cnt;                                               \
    uint16_t width;                                               \
    uint16_t height;                                              \
    double pixel_size;

typedef struct {
    DISPLAY_CONNON_VARIABLES
    char name[DISPLAY_NAME_SIZE];
}DisplayConfig_t;

typedef struct {
    DISPLAY_CONNON_VARIABLES
    bool init;
    char name[DISPLAY_NAME_SIZE];
    uint32_t err_cnt;
    uint32_t frame_buffer_size;
    uint8_t* FrameBuffer;
#ifdef HAS_PC
    FILE* file_ptr;
#endif
    uint32_t pix_cnt;
}DisplayHandle_t;


#endif /* DISPLAY_TYPES_H */
