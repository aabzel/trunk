#ifndef STORAGE_COMMANDS_H
#define STORAGE_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_STORAGE
#error "+HAS_STORAGE"
#endif

#ifdef HAS_CALIBRATION_DATA_COMMANDS
#include "calibration_data_commands.h"
#else
#define CALIBRATION_DATA_COMMANDS
#endif

#ifdef HAS_SW_NVRAM_COMMANDS
#include "sw_nvram_commands.h"
#else
#define SW_NVRAM_COMMANDS
#endif

#ifdef HAS_STORE_FS_COMMANDS
#include "store_fs_commands.h"
#else
#define STORE_FS_COMMANDS
#endif

#ifdef HAS_FLASH_COMMANDS
#include "flash_commands.h"
#else
#define FLASH_COMMANDS
#endif

#ifdef HAS_FLASH_FS_COMMANDS
#include "flash_fs_commands.h"
#else
#define FLASH_FS_COMMANDS
#endif

#ifdef HAS_EXT_RAM_EMUL_COMMANDS
#include "ext_ram_sim_commands.h"
#else
#define EXT_RAM_EMUL_COMMANDS
#endif

#ifdef HAS_FAT_FS_COMMANDS
#include "fat_fs_commands.h"
#else
#define FAT_FS_COMMANDS
#endif

#ifdef HAS_LITTLE_FS_COMMANDS
#include "little_fs_commands.h"
#else
#define LITTLE_FS_COMMANDS
#endif

#ifdef HAS_HEAP_COMMANDS
#include "allocator_commands.h"
#else
#define HEAP_COMMANDS
#endif

#ifdef HAS_KEEPASS_COMMANDS
#include "keepass_commands.h"
#else
#define KEEPASS_COMMANDS
#endif

#ifdef HAS_AT24CX_COMMANDS
#include "at24cxx_commands.h"
#else
#define AT24CX_COMMANDS
#endif

#ifdef HAS_MX25L6433_COMMANDS
#include "mx25l6433f_commands.h"
#else
#define MX25L6433_COMMANDS
#endif

#ifdef HAS_MX25R6435F_COMMANDS
#include "mx25r6435f_commands.h"
#else
#define MX25R6435F_COMMANDS
#endif

#ifdef HAS_NVS_COMMANDS
#include "nvs_commands.h"
#else
#define NVS_COMMANDS
#endif

#ifdef HAS_PARAM_COMMANDS
#include "param_commands.h"
#else
#define PARAM_COMMANDS
#endif

#ifdef HAS_SD_CARD_COMMANDS
#include "sd_card_commands.h"
#else
#define SD_CARD_COMMANDS
#endif

#ifdef HAS_HEX_BIN_COMMANDS
#include "hex_bin_commands.h"
#else
#define HEX_BIN_COMMANDS
#endif

#ifdef HAS_NOR_FLASH_COMMANDS
#include "nor_flash_commands.h"
#else
#define NOR_FLASH_COMMANDS
#endif

#ifdef HAS_FILE_PC_COMMANDS
#include "file_pc_commands.h"
#else
#define FILE_PC_COMMANDS
#endif

#ifdef HAS_WAV_COMMANDS
#include "wav_commands.h"
#else
#define WAV_COMMANDS
#endif

#ifdef HAS_SW_SD_CARD_COMMANDS
#include "sw_sd_card_commands.h"
#else
#define SW_SD_CARD_COMMANDS
#endif

#ifdef HAS_DISK_COMMANDS
#include "disk_commands.h"
#else
#define DISK_COMMANDS
#endif

#ifdef HAS_RUNNING_LINE_COMMANDS
#include "running_line_commands.h"
#else
#define RUNNING_LINE_COMMANDS
#endif

#ifndef HAS_STORAGE_COMMANDS
#error "+HAS_STORAGE_COMMANDS"
#endif

bool malloc_try_command(int32_t argc, char* argv[]);

#define STORAGE_ASICS_COMMANDS        \
    AT24CX_COMMANDS             \
    MX25L6433_COMMANDS          \
    MX25R6435F_COMMANDS         \
    SD_CARD_COMMANDS

#define STORAGE_COMMANDS        \
    STORAGE_ASICS_COMMANDS      \
    CALIBRATION_DATA_COMMANDS   \
    DISK_COMMANDS               \
    EXT_RAM_EMUL_COMMANDS       \
    FAT_FS_COMMANDS             \
    LITTLE_FS_COMMANDS          \
    STORE_FS_COMMANDS           \
    FILE_PC_COMMANDS            \
    FLASH_FS_COMMANDS           \
    HEAP_COMMANDS               \
    HEX_BIN_COMMANDS            \
    KEEPASS_COMMANDS            \
    NOR_FLASH_COMMANDS          \
    WAV_COMMANDS                \
    NVS_COMMANDS                \
    PARAM_COMMANDS              \
    RUNNING_LINE_COMMANDS       \
    SHELL_CMD("malloc", "mall", malloc_try_command, "MallocTry"),    \
    SW_NVRAM_COMMANDS


#ifdef __cplusplus
}
#endif

#endif /* STORAGE_COMMANDS_H */
