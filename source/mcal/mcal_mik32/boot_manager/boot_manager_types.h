#ifndef BOOT_MANAGER_TYPES_H
#define BOOT_MANAGER_TYPES_H

#include <stdint.h>

#include "boot_manager_const.h"
#include "compiler_const.h"

typedef union {
    uint32_t dword;
    struct{
        uint32_t boot_mode :2;
        uint32_t res :30;
    };
}__attribute__((__packed__)) BootManagerRegBoot_t;


#endif /* BOOT_MANAGER_TYPES_H  */
