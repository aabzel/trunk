#ifndef DISK_CONFIG_H
#define DISK_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "disk_types.h"
#include "disk_dep.h"

#define _USE_WRITE 1 /* 1: Enable disk_write function */
#define _USE_IOCTL 1 /* 1: Enable diskctl function */

extern const DiskConfig_t DiskConfig[];
extern DiskHandle_t DiskInstance[];

uint32_t disk_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* DISK_CONFIG_H */
