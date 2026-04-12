#ifndef BOOT_TYPES_H
#define BOOT_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "boot_const.h"
#include "std_includes.h"

typedef void (*pFunction)(void);


typedef struct  {
    uint32_t app_crc32_calc;
    uint32_t app_crc32_read;
    uint32_t app_start_address;
    uint32_t app_len;
} BootData_t;

#define BOOT_COMMON_VARIABLES      \
    uint32_t fw_start_address;     \
    uint32_t stack_lim_address;    \
    uint32_t stack_top_address;    \
    char*  name;                   \
    uint8_t num;                   \
    bool valid;

typedef struct  {
    BOOT_COMMON_VARIABLES
} BootConfig_t;

typedef struct  {
    BOOT_COMMON_VARIABLES
    bool init;
    uint32_t spin;
} BootHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* BOOT_TYPES_H */
