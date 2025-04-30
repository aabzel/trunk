#ifndef BOOTLOADER_PARAMS_H
#define BOOTLOADER_PARAMS_H

#include "param_types.h"

#define PARAMS_BOOTLOADER                                                                                                 \
    {.facility=BOOTLOADER, .id=PAR_ID_BOOT_CNT,   .len=2, .type=TYPE_UINT16,     .default_value="0", .name="BootCnt"},    \
    {.facility=BOOTLOADER, .id=PAR_ID_APP_CRC32,  .len=4, .type=TYPE_UINT32_HEX, .default_value="0", .name="AppCrc32"},   \
    {.facility=BOOTLOADER, .id=PAR_ID_APP_LEN,    .len=4, .type=TYPE_UINT32,     .default_value="0", .name="AppLen"},     \
    {.facility=BOOTLOADER, .id=PAR_ID_APP_START,  .len=4, .type=TYPE_UINT32_HEX, .default_value="0", .name="StartApp"},   \
    {.facility=BOOTLOADER, .id=PAR_ID_APP_STATUS, .len=1, .type=TYPE_UINT8,      .default_value="0", .name="AppStatus"},


#endif /* BOOTLOADER_PARAMS_H */
