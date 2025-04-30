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
		.page_1={  .num=1, .size=NVS_SECTOR_SIZE, .page_offset=NVS_START,},
		.page_2={  .num=2, .size=NVS_SECTOR_SIZE, .page_offset=(NVS_START+NVS_SECTOR_SIZE),},
};

FlashFs_t FlashFs={
	     .page1={ .files_cnt=0, .usage_pre_cent=0,},
	     .page2={ .files_cnt=0, .usage_pre_cent=0,},
	    .err_set_cnt=0,
	    .err_get_cnt=0,
};
