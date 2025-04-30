#ifndef BOOT_TYPES_H
#define BOOT_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "boot_const.h"

typedef void (*pFunction)(void);


typedef struct  {
    uint32_t app_crc32_calc;
    uint32_t app_crc32_read;
    uint32_t app_start_address;
    uint32_t app_len;
} BootData_t;


typedef struct  {
    uint32_t fw_start_address;
} BootConfig_t;

typedef struct  {
   uint32_t fw_start_address;
} BootHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* BOOT_TYPES_H */
