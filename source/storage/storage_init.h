#ifndef PROC_STORAGE_H
#define PROC_STORAGE_H

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_STORAGE
#error  "+HAS_STORAGE"
#endif

#ifdef HAS_AT24CXX
#include "at24cxx_drv.h"
#define AT24CXX_INIT   {.init_function=at24cxx_init, .name="AT24Cxx",},
#else
#define AT24CXX_INIT
#endif /*HAS_AT24CXX*/

#ifdef HAS_FAT_FS
#include "fat_fs_drv.h"
#define FAT_FS_INIT   {.init_function=fat_fs_init, .name="FatFs",},
#else
#define FAT_FS_INIT
#endif /*HAS_FAT_FS*/

#ifdef HAS_MX25R6435F
#include "mx25r6435f_drv.h"
#define MX25R6435F_INIT   {.init_function=mx25r6435f_init, .name="MX25R6435F",},
#else
#define MX25R6435F_INIT
#endif /*HAS_MX25R6435F*/

#ifdef HAS_NVS
#include "nvs_drv.h"
#define NVS_INIT   {.init_function=nvs_init, .name="NVS",},
#else
#define NVS_INIT
#endif /*HAS_NVS*/

#ifdef HAS_NOR_FLASH_INIT
#include "nor_flash_drv.h"
#define NOR_FLASH_INIT   {.init_function=nor_flash_init, .name="NorFlash",},
#else
#define NOR_FLASH_INIT
#endif /*HAS_NOR_FLASH*/

#ifdef HAS_FLASH_FS
#include "flash_fs.h"
#define FLASH_FS_INIT   {.init_function=flash_fs_init, .name="FlashFs",},
#else
#define FLASH_FS_INIT
#endif /*HAS_FLASH_FS*/

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
#endif /*HAS_PARAM*/

#ifdef HAS_SD_CARD
#include "sd_card_drv.h"
#define SD_CARD_INIT   {.init_function=sd_card_init, .name="SdCard",},
#else
#define SD_CARD_INIT
#endif /*HAS_SD_CARD*/

#ifdef HAS_SW_NVRAM
#include "sw_nvram.h"
#define SW_NVRAM_INIT   {.init_function=sw_nvram_init, .name="NVRAM",},
#else
#define SW_NVRAM_INIT
#endif /*HAS_SW_NVRAM*/

#ifdef HAS_BLACK_BOX
#include "black_box.h"
#define BLACK_BOX_INIT   {.init_function=black_box_init, .name="BlackBox",},
#else
#define BLACK_BOX_INIT
#endif /*HAS_BLACK_BOX*/

#ifdef HAS_CALIBRATION_DATA
#include "calibration_data.h"
#define CALIBRATION_DATA_INIT {.init_function=calibration_data_init, .name="CalibrationData",},
#else
#define CALIBRATION_DATA_INIT
#endif /*HAS_CALIBRATION_DATA*/

#ifdef HAS_HEX_BIN
#include "hex_bin.h"
#define HEX_BIN_INIT {.init_function=hex_bin_init, .name="HexBin",},
#else
#define HEX_BIN_INIT
#endif /*HAS_HEX_BIN*/

#ifdef HAS_RUNNING_LINE
#include "running_line.h"
#define RUNNING_LINE_INIT {.init_function=running_line_mcal_init, .name="RunningLine",},
#else
#define RUNNING_LINE_INIT
#endif /*HAS_RUNNING_LINE*/

#ifdef HAS_WAV
#include "wav.h"
#define WAV_INIT   {.init_function=wav_mcal_init, .name="WavFile",},
#else
#define WAV_INIT
#endif /*HAS_WAV*/

/*Order Matters!*/
#define STORAGE_HW_INIT \
     AT24CXX_INIT       \
     MX25R6435F_INIT    \
     SD_CARD_INIT

/*Order Matters!*/
#define STORAGE_SW_INIT  \
    NVS_INIT            \
    NOR_FLASH_INIT      \
    FLASH_FS_INIT       \
    PARAM_INIT          \
    FAT_FS_INIT         \
    SW_NVRAM_INIT       \
    KEEPASS_INIT        \
    CALIBRATION_DATA_INIT \
    HEX_BIN_INIT        \
    WAV_INIT            \
    BLACK_BOX_INIT      \
    RUNNING_LINE_INIT

/*Order Matters!*/
#define STORAGE_INIT   \
    STORAGE_HW_INIT    \
    STORAGE_SW_INIT


#ifdef HAS_SUPER_CYCLE
void super_storage_loop(uint64_t loop_start_time_us) ;
#endif /*SUPER_LOOP*/

#endif /* PROC_STORAGE_H */
