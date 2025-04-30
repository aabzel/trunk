#ifndef NOR_FLASH_TYPES_H
#define NOR_FLASH_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "nor_flash_const.h"

typedef bool (*CustomInit_t)(uint8_t num);

#define COMMON_VARIABLES                                                                                               \
    uint32_t start;                                                                                                    \
    uint32_t size;                                                                                                     \
    NorFlashOption_t option;                                                                                           \
    bool valid;                                                                                                        \
    uint8_t num;                                                                                                       \
    uint8_t* memory;

typedef struct {
    COMMON_VARIABLES
    char* name;
    CustomInit_t CustomInit;
} NorFlashConfig_t;

typedef struct {
    COMMON_VARIABLES
    bool init;
} NorFlashItem_t;

#endif /* NOR_FLASH_TYPES_H */
