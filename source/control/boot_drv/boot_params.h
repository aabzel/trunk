#ifndef BOOT_PARAMS_H
#define BOOT_PARAMS_H

#include "param_types.h"
#include "flash_fs_file_ids.h"

#ifdef HAS_MBR
#define MBR_PARAMS                               \
    {                                            \
        .facility = MBR,                          \
        .id = PAR_ID_BOOTLOADER_START,            \
        .len = 4,                                 \
        .type = TYPE_UINT32_HEX,                  \
        .default_value = "0",                     \
        .name = "StartBoot"                       \
    },

#else
#define MBR_PARAMS
#endif

#define PARAMS_BOOT                           \
    MBR_PARAMS                                \
   {                                          \
     .facility = BOOT,                        \
     .id = PAR_ID_REBOOT_CNT,                 \
     .len = 2,                                \
     .type = TYPE_UINT16,                     \
     .default_value = "1",                    \
     .name = "ReBootCnt",                     \
    },                                        \
    {                                         \
    .facility = BOOT,                         \
    .id = PAR_ID_BOOT_CMD,                    \
    .len = 1,                                 \
    .type = TYPE_UINT8,                       \
    .default_value = "0",                     \
    .name = "BootCmd",}, /*num*/


#endif /* BOOT_PARAMS_H */
