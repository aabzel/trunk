#ifndef SW_NOR_FLASH_TYPES_H
#define SW_NOR_FLASH_TYPES_H

#include "std_includes.h"
#include "sw_nor_flash_const.h"

#define SW_NOR_FLASH_CONNON_VARIABLES                  \
    bool re_record;                                    \
    char* name;                                        \
    uint8_t num;                                       \
    uint32_t sector_size;                              \
    uint32_t page_size;                                \
    uint32_t block_size;                               \
    uint8_t* memory;                                   \
    uint32_t size;                                     \
    bool valid;


typedef struct {
    SW_NOR_FLASH_CONNON_VARIABLES
}SwNorFlashConfig_t;

typedef struct {
    SW_NOR_FLASH_CONNON_VARIABLES
    bool init;
    uint32_t spin;
}SwNorFlashHandle_t;


#endif /* SW_NOR_FLASH_TYPES_H */
