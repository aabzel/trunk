#include "flash_fs_config.h"

//#include "flash_config.h"
//#include "nvs_const.h"

const FlashFsConfig_t FlashFsConfig = {
    .page = {
           { .num=1, .offset=FLASH_FS_PAGE1_OFFSET, .size=FLASH_FS_PAGE1_SIZE,},
           { .num=2, .offset=FLASH_FS_PAGE2_OFFSET, .size=FLASH_FS_PAGE2_SIZE,},
    }
};

FlashFs_t FlashFs={
      .page ={
    		{ .files_cnt=0, .usage_pre_cent=0,},
            { .files_cnt=0, .usage_pre_cent=0,},
       },
      .err_set_cnt=0,
      .err_get_cnt=0,
};
