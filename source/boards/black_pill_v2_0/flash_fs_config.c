#include "flash_fs_config.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif /*HAS_FLASH*/

#ifndef HAS_FLASH_FS
#error "Add HAS_FLASH_FS"
#endif /*HAS_FLASH_FS*/

#include "flash_config.h"
#include "nvs_const.h"


const FlashFsConfig_t FlashFsConfig = {
    .page={
            {.offset=MEMORY_MANAGER1_OFFSET, .num=1, .size=MEMORY_MANAGER1_LENGTH,},
            {.offset=MEMORY_MANAGER2_OFFSET, .num=2, .size=MEMORY_MANAGER2_LENGTH,},
    },
};

FlashFs_t FlashFs={
         .page={
                { .files_cnt=0, .usage_pre_cent=0,},
                { .files_cnt=0, .usage_pre_cent=0,},
         },
        .err_set_cnt=0,
        .err_get_cnt=0,
};
