#ifndef STORAGE_TASKS_H
#define STORAGE_TASKS_H


#ifdef HAS_EXT_RAM_EMUL_PROC
#include "ext_ram_sim.h"
#define EXT_RAM_EMUL_TASKS
#else
#define EXT_RAM_EMUL_TASKS
#endif

#ifdef HAS_FLASH_PROC
#include "flash.h"
#define FLASH_TASKS
#else
#define FLASH_TASKS
#endif

#ifdef HAS_FLASH_FS_PROC
#include "flash_fs.h"
#define FLASH_FS_TASKS  {.name="FLASH_FS", .period_us=FLASH_FS_POLL_PERIOD_US, .limiter.function=flash_fs_proc,},
#else
#define FLASH_FS_TASKS
#endif

#ifdef HAS_BLACK_BOX_PROC
#include "black_box.h"
#define BLACK_BOX_TASKS {.name="BLACK_BOX", .period_us=BLACK_BOX_POLL_PERIOD_US, .limiter.function=black_box_proc,},
#else
#define BLACK_BOX_TASKS
#endif

#ifdef HAS_FAT_FS_PROC
#include "fat_fs.h"
#define FAT_FS_TASKS
#else
#define FAT_FS_TASKS
#endif

#ifdef HAS_HEAP_PROC
#include "allocator.h"
#define HEAP_TASKS
#else
#define HEAP_TASKS
#endif

#ifdef HAS_KEEPASS_PROC
#include "keepass.h"
#define KEEPASS_TASKS
#else
#define KEEPASS_TASKS
#endif

#ifdef HAS_MX25L6433_PROC
#include "mx25l6433f.h"
#define MX25L6433_TASKS
#else
#define MX25L6433_TASKS
#endif

#ifdef HAS_MX25R6435F_PROC
#include "mx25r6435f.h"
#define MX25R6435F_TASKS
#else
#define MX25R6435F_TASKS
#endif

#ifdef HAS_NOR_FLASH_PROC
#include "nor_flash.h"
#define NOR_FLASH_TASKS
#else
#define NOR_FLASH_TASKS
#endif

#ifdef HAS_NVS_PROC
#include "nvs.h"
#define NVS_TASKS
#else
#define NVS_TASKS
#endif

#ifdef HAS_PARAM_PROC
#include "param.h"
#define PARAM_TASKS
#else
#define PARAM_TASKS
#endif

#ifdef HAS_SD_CARD_PROC
#include "sd_card.h"
#define SD_CARD_TASKS
#else
#define SD_CARD_TASKS
#endif

#ifdef HAS_SW_NVRAM_PROC
#include "sw_nvram.h"
#define SW_NVRAM_TASKS   {.name="SW_NVRAM", .period_us=SW_NVRAM_POLL_PERIOD_US, .limiter.function=sw_nvram_proc,},
#else
#define SW_NVRAM_TASKS
#endif


#ifdef HAS_RUNNING_LINE_PROC
#include "running_line.h"
#define RUNNING_LINE_TASKS   {.name="RunLine", .period_us=RUNNING_LINE_POLL_PERIOD_US, .limiter.function=running_line_proc,},
#else
#define RUNNING_LINE_TASKS
#endif


#define STORAGE_TASKS     \
    BLACK_BOX_TASKS       \
    EXT_RAM_EMUL_TASKS    \
    FAT_FS_TASKS          \
    FLASH_TASKS           \
    FLASH_FS_TASKS        \
    HEAP_TASKS            \
    KEEPASS_TASKS         \
    MX25L6433_TASKS       \
    MX25R6435F_TASKS      \
    NVS_TASKS             \
    PARAM_TASKS           \
    RUNNING_LINE_TASKS    \
    SD_CARD_TASKS         \
    NOR_FLASH_TASKS       \
    SW_NVRAM_TASKS

#endif /* STORAGE_TASKS_H */
