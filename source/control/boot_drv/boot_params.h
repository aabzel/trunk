#ifndef BOOT_PARAMS_H
#define BOOT_PARAMS_H

#include "storage_types.h"
#include "storage_file_ids.h"
#include "common_diag.h"

#ifdef HAS_BOOT_DIAG
#include "boot_diag.h"
#endif

#ifdef HAS_BOOT_DIAG
#define PARAM_MBR_BOOT_ADDRESS_PARSER      .parser = U23ToStr,
#define PARAM_MBR_BOOT_CMD_PARSER          .parser = StorageBootCmdToStr,
#define PARAM_MBR_BOOT_REBOOT_CNT_PARSER   .parser = U16DecToStr,
#define PARAM_MBR_BOOT_BOOT_CNT_PARSER     .parser = U8DecToStr,
#define PARAM_MBR_BOOT_ADDRESS_PARSER      .parser = U23ToStr,
#else
#define PARAM_MBR_BOOT_ADDRESS_PARSER
#define PARAM_MBR_BOOT_CMD_PARSER
#define PARAM_MBR_BOOT_REBOOT_CNT_PARSER
#define PARAM_MBR_BOOT_BOOT_CNT_PARSER
#define PARAM_MBR_BOOT_ADDRESS_PARSER
#endif

#ifdef HAS_MBR
#define MBR_PARAMS                                \
    {                                             \
        .facility = MBR,                          \
        .id = PAR_ID_BOOTLOADER_START,            \
        .len = 4,                                 \
        .type = TYPE_UINT32_HEX,                  \
        .default_value = "0",                     \
        .name = "StartBoot",                      \
        PARAM_MBR_BOOT_ADDRESS_PARSER             \
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
     PARAM_MBR_BOOT_REBOOT_CNT_PARSER         \
    },                                        \
        {                                     \
      .facility = BOOT,                       \
      .id = PAR_ID_BOOT_CNT,                  \
      .len = 1,                               \
      .type = TYPE_UINT8,                     \
      .default_value = "0",                   \
      .name = "BootCnt",                      \
      PARAM_MBR_BOOT_BOOT_CNT_PARSER          \
    },                                        \
    {                                         \
    .facility = BOOT,                         \
    .id = PAR_ID_BOOT_CMD,                    \
    .len = 1,                                 \
    .type = TYPE_UINT8,                       \
    .default_value = "2",                     \
    .name = "BootCmd",                        \
     PARAM_MBR_BOOT_CMD_PARSER                \
},


#endif /* BOOT_PARAMS_H */
