#ifndef BOOT_CONFIG_H
#define BOOT_CONFIG_H

#include "boot_types.h"

extern const BootConfig_t BootConfig[];
extern BootHandle_t BootInstance[] ;

uint32_t boot_get_cnt(void);

#endif /* BOOT_CONFIG_H */
