#ifndef BOOTLOADER_TYPES_H
#define BOOTLOADER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "bootloader_const.h"
#include "crc_types.h"

#define BOOTLOADER_COMMON_VARIABLES  \
    uint32_t app_start_address;

typedef struct {
    BOOTLOADER_COMMON_VARIABLES
} BootLoaderConfig_t;

typedef struct  {
    BOOTLOADER_COMMON_VARIABLES
    Crc32_t app_crc32;
    uint32_t app_len;
} BootLoaderHandler_t;

#ifdef __cplusplus
}
#endif

#endif /* BOOTLOADER_TYPES_H */
