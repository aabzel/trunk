#ifndef REC_PLAY_TYPES_H
#define REC_PLAY_TYPES_H

#include "std_includes.h"
#include "rec_play_const.h"

#define REC_PLAY_COMMON_VARIABLES                  \
    char* name;                                    \
    uint8_t wm8731_num;                            \
    uint8_t play_num;                              \
    uint8_t rec_num;                               \
    uint8_t num;                                   \
    bool valid;

typedef struct {
    REC_PLAY_COMMON_VARIABLES
}RecPlayConfig_t;

typedef struct {
    REC_PLAY_COMMON_VARIABLES
    RecPlayState_t state;
    char file_name[150];
    bool init;
    uint32_t spin;
}RecPlayHandle_t;


#endif /* REC_PLAY_TYPES_H */
