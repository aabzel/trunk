#ifndef FLASH_FS_PARAMS_H
#define FLASH_FS_PARAMS_H

#include "param_types.h"

#define PARAMS_FLASH_FS                   \
    {                                     \
        .facility = FLASH_FS,             \
        .id = PAR_ID_FLASH_FS_TOGGLE_CNT, \
        .len = 4,                         \
        .type = TYPE_UINT32,              \
        .default_value = "0",             \
        .name = "FFSpageToggleCnt",       \
        },


#endif /* FLASH_FS_PARAMS_H */
