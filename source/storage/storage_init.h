#ifndef PROC_STORAGE_H
#define PROC_STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_STORAGE
#error  "+HAS_STORAGE"
#endif

#ifdef HAS_AT24CX
#include "at24cx_drv.h"
#define AT24CX_INIT   {.init_function=at24cx_init, .name="AT24Cx",},
#else
#define AT24CX_INIT
#endif

#ifdef HAS_DISK
#include "disk.h"
#define DISK_INIT   {.init_function=disk_mcal_init, .name="Disk",},
#else
#define DISK_INIT
#endif

#ifdef HAS_FAT_FS
#include "fat_fs.h"
#define FAT_FS_INIT   {.init_function=fat_fs_mcal_init, .name="FatFs",},
#else
#define FAT_FS_INIT
#endif

#ifdef HAS_STORE_FS
#include "store_fs.h"
#define STORE_FS_INIT {.init_function = store_fs_mcal_init, .name = "StoreFs", },
#else
#define STORE_FS_INIT
#endif

#ifdef HAS_LITTLE_FS
#include "little_fs.h"
#define LITTLE_FS_INIT {.init_function=little_fs_mcal_init, .name="LittleFs",},
#else
#define LITTLE_FS_INIT
#endif

#ifdef HAS_MX25R6435F
#include "mx25r6435f_drv.h"
#define MX25R6435F_INIT   {.init_function=mx25r6435f_init, .name="MX25R6435F",},
#else
#define MX25R6435F_INIT
#endif

#ifdef HAS_NVS
#include "nvs_mcal.h"
#define NVS_INIT   {.init_function = nvs_mcal_init, .name="NVS",},
#else
#define NVS_INIT
#endif

#ifdef HAS_NOR_FLASH_INIT
#include "nor_flash_drv.h"
#define NOR_FLASH_INIT   {.init_function=nor_flash_init, .name="NorFlash",},
#else
#define NOR_FLASH_INIT
#endif

#ifdef HAS_FLASH_FS
#include "flash_fs.h"
#define FLASH_FS_INIT   {.init_function=flash_fs_init, .name="FlashFs",},
#else
#define FLASH_FS_INIT
#endif

#ifdef HAS_KEEPASS
#include "keepass.h"
#define KEEPASS_INIT   {.init_function=keepass_init, .name="KeePass",},
#else
#define KEEPASS_INIT
#endif

#ifdef HAS_PARAM
#include "param_drv.h"
#define PARAM_INIT   {.init_function = param_init, .name = "Param",},
#else
#define PARAM_INIT
#endif

#ifdef HAS_SW_NOR_FLASH
#include "sw_nor_flash.h"
#define SW_NOR_FLASH_INIT   {.init_function = sw_nor_flash_mcal_init, .name = "sw_nor_flash",},
#else
#define SW_NOR_FLASH_INIT
#endif

#ifdef HAS_SD_CARD
#include "sd_card_drv.h"
#define SD_CARD_INIT   {.init_function=sd_card_init, .name="SdCard",},
#else
#define SD_CARD_INIT
#endif

#ifdef HAS_SW_NVRAM
#include "sw_nvram.h"
#define SW_NVRAM_INIT   {.init_function=sw_nvram_init, .name="NVRAM",},
#else
#define SW_NVRAM_INIT
#endif

#ifdef HAS_BLACK_BOX
#include "black_box.h"
#define BLACK_BOX_INIT   {.init_function=black_box_init, .name="BlackBox",},
#else
#define BLACK_BOX_INIT
#endif

#ifdef HAS_CALIBRATION_DATA
#include "calibration_data.h"
#define CALIBRATION_DATA_INIT {.init_function=calibration_data_init, .name="CalibrationData",},
#else
#define CALIBRATION_DATA_INIT
#endif

#ifdef HAS_HEX_BIN
#include "hex_bin.h"
#define HEX_BIN_INIT {.init_function=hex_bin_init, .name="HexBin",},
#else
#define HEX_BIN_INIT
#endif


#ifdef HAS_SW_SD_CARD
#include "sw_sd_card.h"
#define SW_SD_CARD_INIT {.init_function=sw_sd_card_mcal_init, .name="SwSdCard",},
#else
#define SW_SD_CARD_INIT
#endif


#ifdef HAS_RUNNING_LINE
#include "running_line.h"
#define RUNNING_LINE_INIT {.init_function=running_line_mcal_init, .name="RunningLine",},
#else
#define RUNNING_LINE_INIT
#endif

#ifdef HAS_WAV
#include "wav.h"
#define WAV_INIT   {.init_function=wav_mcal_init, .name="WavFile",},
#else
#define WAV_INIT
#endif

/*Order Matters!*/
#define STORAGE_HW_INIT   \
     AT24CX_INIT          \
     MX25R6435F_INIT      \
     SD_CARD_INIT         \
     DISK_INIT

/* LITTLE_FS_INIT and STORE_FS_INIT must be inited before clock   */

/*Order Matters!*/
#define STORAGE_SW_INIT   \
    NVS_INIT              \
    NOR_FLASH_INIT        \
    FLASH_FS_INIT         \
    PARAM_INIT            \
    SW_NOR_FLASH_INIT     \
    SW_SD_CARD_INIT       \
    LITTLE_FS_INIT        \
    FAT_FS_INIT           \
    SW_NVRAM_INIT         \
    KEEPASS_INIT          \
    CALIBRATION_DATA_INIT \
    HEX_BIN_INIT          \
    WAV_INIT              \
    BLACK_BOX_INIT        \
    STORE_FS_INIT         \
    RUNNING_LINE_INIT

/*Order Matters!*/
#define STORAGE_INIT   \
    STORAGE_HW_INIT    \
    STORAGE_SW_INIT



#ifdef __cplusplus
}
#endif

#endif /* PROC_STORAGE_H */
