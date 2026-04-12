#ifndef SW_SD_CARD_TYPES_H
#define SW_SD_CARD_TYPES_H

#include "std_includes.h"
#include "sw_sd_card_const.h"

#define SW_SD_CARD_CONNON_VARIABLES                    \
    char* name;                                        \
    uint8_t num;                                       \
    uint8_t* buff;                                     \
    uint32_t size;                                     \
    uint32_t block_size;                               \
    bool valid;

typedef struct {
    SW_SD_CARD_CONNON_VARIABLES
}SwSdCardConfig_t;

typedef struct {
    SW_SD_CARD_CONNON_VARIABLES
    bool init;
    uint32_t spin;
}SwSdCardHandle_t;


#endif /* SW_SD_CARD_TYPES_H */
