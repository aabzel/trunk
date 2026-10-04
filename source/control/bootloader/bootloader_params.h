#ifndef BOOTLOADER_PARAMS_H
#define BOOTLOADER_PARAMS_H

#include "storage_types.h"

// {.facility = BOOTLOADER, .id = PAR_ID_BOOT_CNT,   .len = 2, .type = TYPE_UINT16,     .default_value = "0", .name = "BootCnt"},

#define PARAMS_BOOTLOADER                                                         \
    {.facility = BOOTLOADER,                                                      \
     .id = PAR_ID_APP_CRC32,                                                      \
     .len = 4,                                                                    \
     .type = TYPE_UINT32_HEX,                                                     \
     .parser = U32ToStr,                                                          \
     .default_value = "0",                                                        \
     .name = "AppCrc32"},                                                         \
    {.facility = BOOTLOADER,                                                      \
     .id = PAR_ID_APP_LEN,                                                        \
     .len = 4,                                                                    \
     .type = TYPE_UINT32,                                                         \
     .parser = U32ToStr,                                                          \
     .default_value = "0",                                                        \
     .name = "AppLen"},                                                           \
    {.facility = BOOTLOADER,                                                      \
     .id = PAR_ID_APP_START,                                                      \
     .len = 4,                                                                    \
     .type = TYPE_UINT32_HEX,                                                     \
     .parser = U32ToStr,                                                          \
     .default_value = "0",                                                        \
     .name = "StartApp"},                                                         \
    {.facility = BOOTLOADER,                                                      \
     .id = PAR_ID_APP_STATUS,                                                     \
     .len = 1,                                                                    \
     .parser = U8DecToStr,                                                        \
     .type = TYPE_UINT8,                                                          \
     .default_value = "0",                                                        \
     .name = "AppStatus"                                                          \
},

#endif /* BOOTLOADER_PARAMS_H */
