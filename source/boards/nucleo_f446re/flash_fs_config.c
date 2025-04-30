#include "flash_fs_config.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif /*HAS_FLASH*/

#ifndef HAS_FLASH_FS
#error "Add HAS_FLASH_FS"
#endif /*HAS_FLASH_FS*/

#include "flash_config.h"
#include "nvs_const.h"
#include "nvs_config.h"

const FlashFsConfig_t FlashFsConfig = {
		.page =
        {
        { .num = 1,
          .size = NVS_SECTOR_SIZE,
		  .offset = NVS_START,
        },
        {
		  .num = 2,
		  .size =                NVS_SECTOR_SIZE,
		  .offset = (NVS_START + NVS_SECTOR_SIZE) },
        },
};

FlashFs_t FlashFs = {
		.page = {
		{ .files_cnt = 0,
				.usage_pre_cent = 0,
},
		{ .files_cnt = 0,
        .usage_pre_cent = 0, }
},
		.err_set_cnt = 0, .err_get_cnt = 0,
};
