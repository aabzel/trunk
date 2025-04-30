#ifndef NOR_FLASH_FS_TYPES_H
#define NOR_FLASH_FS_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "flash_fs_const.h"

typedef struct {
    uint32_t files_cnt;
    uint8_t usage_pre_cent;
} FlashPageFs_t;

typedef struct {
    uint32_t offset;
    uint32_t size;
    uint8_t num;
} FlashFsPageConfig_t;

typedef struct {
    FlashFsPageConfig_t page[2];
} FlashFsConfig_t;

typedef struct {
    FlashPageFs_t page[2];
    uint32_t err_set_cnt;
    uint32_t err_get_cnt;
    FlashFsPage_t cur_page;
    uint32_t toggle_cnt;
} FlashFs_t;

typedef struct {
    uint16_t id;
    uint16_t nid; /* bit inverted id*/
    uint16_t length;
    uint8_t crc8;                          /*only for payload*/
} __attribute__((packed)) FlashFsHeader_t; /*to save flash memory*/

// typedef struct xMMitem_t FlashFsHeader_t;

#endif /* NOR_FLASH_FS_TYPES_H */
