#ifndef FLASH_MCAL_GENERAL_TYPES_H
#define FLASH_MCAL_GENERAL_TYPES_H


#include "std_includes.h"
#include "flash_const.h"

#ifdef HAS_FLASH_CUSTOM
#include "flash_custom_types.h"
#else
#define FLASH_CUSTOM_TYPES
#endif

// logical sector
typedef struct  {
    uint32_t start;
    uint32_t size;
    uint8_t sector;
    MemContent_t content;
} FlashSectorConfig_t;


#define FLASH_COMMON_VARIABLES          \
    uint32_t start;                     \
    uint32_t size;                      \
    uint32_t app_start;                 \
    uint32_t boot_start;                \
    FlashSectorConfig_t* PageArray;     \
    uint32_t page_cnt;                  \
    uint32_t page_size; /*sector_size*/ \
    bool is_equal_sectors;              \
    bool interrupt_on;

typedef struct {
    FLASH_COMMON_VARIABLES
} FlashConfig_t;


#define FLASH_FSM_VARIABLES       \
    FlashOperation_t operation;   \
    FlashInput_t input;           \
    FlashState_t state;           \
    uint32_t wr_flash_addr;       \
    uint32_t start_ms;            \
    uint32_t diff_ms;             \
    uint32_t spin_cnt;            \
    uint8_t wr_byte;              \
    uint16_t wr_word;             \
    uint32_t wr_qword;            \
    bool loop;

typedef struct {
    FLASH_FSM_VARIABLES
    FLASH_COMMON_VARIABLES
    FLASH_CUSTOM_TYPES
    uint16_t crc16;
    bool init;
} FlashHandle_t;


#endif /* FLASH_MCAL_GENERAL_TYPES_H */
