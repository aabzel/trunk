#include "flash_fs_config.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif

#ifndef HAS_FLASH_FS
#error "Add HAS_FLASH_FS"
#endif

#include "flash_config.h"
#include "nvs_const.h"

const FlashFsConfig_t SECTION_CFG_DATA FlashFsConfig = {
    .page =
        {
            {
                .offset = FLASH_FS1_OFFSET,
                .num = 1,
                .size = FLASH_FS1_LENGTH,
            },
            {
                .offset = FLASH_FS2_OFFSET,
                .num = 2,
                .size = FLASH_FS2_LENGTH,
            },
        },
};

FlashFsHandle_t FlashFsInstance = {
    .page =
        {
            {
                .files_cnt = 0,
                .usage_pre_cent = 0,
            },
            {
                .files_cnt = 0,
                .usage_pre_cent = 0,
            },
        },
    .err_set_cnt = 0,
    .err_get_cnt = 0,
};
