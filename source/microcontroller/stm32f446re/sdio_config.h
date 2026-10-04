#ifndef SDIO_CONFIG_H
#define SDIO_CONFIG_H

#include "sdio_types.h"
#include "sys_config.h"

#define SDIO_NUM 1

#ifndef HAS_SDIO
#error "+HAS_SDIO"
#endif

extern const SdioConfig_t SdioConfig[];
extern SdioHandle_t SdioInstance[];

uint32_t sdio_get_cnt(void);

#endif /* SDIO_CONFIG_H  */
