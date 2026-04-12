#ifndef FLASH_FS_PARAMS_H
#define FLASH_FS_PARAMS_H

#include "storage_file_ids.h"

#define PARAMS_FLASH_FS                   \
    {                                     \
        .facility = FLASH_FS,             \
        .id = PAR_ID_FLASH_FS_TOGGLE_CNT, \
        .len = 4,                         \
        .type = TYPE_UINT32,              \
        .default_value = "0",             \
        .name = "FFSpageToggleCnt",       \
        .parser = U32DecToStr,            \
    },




#endif /* FLASH_FS_PARAMS_H */
