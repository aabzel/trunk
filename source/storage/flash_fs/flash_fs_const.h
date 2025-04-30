#ifndef NOR_FLASH_FS_CONST_H
#define NOR_FLASH_FS_CONST_H

#ifdef HAS_TIME
#include "timer_utils.h"
#endif
#include "flash_fs_file_ids.h"
#include "flash_fs_dep.h"

typedef enum{
    FLASH_FS_PAGE_1=1,
    FLASH_FS_PAGE_2=2,

    FLASH_FS_PAGE_UNDEF=0x55,
}FlashFsPage_t;

#define QWORD_LEN 4
#define MM_INVALID_ID 0xFFFF


#define FLASH_FS_ACTIV_PAGE_DWORD 0xAA55A55A

#define FLASH_FS_POLL_PERIOD_US MIN_2_US(1)
//#define FLASH_FS_MAX_FILE_SIZE 512

#define ITEM_HEADER_SZ (sizeof(FlashFsHeader_t))
#define MIN_FILE_LEN (ITEM_HEADER_SZ + 1)

#endif /* NOR_FLASH_FS_CONST_H */
