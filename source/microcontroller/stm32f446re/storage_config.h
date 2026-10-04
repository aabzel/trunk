#ifndef STORAGE_CONFIG_H
#define STORAGE_CONFIG_H

#include <stdint.h>

#include "storage_types.h"

extern const StorageItem_t StorageArray[];

uint32_t storage_get_cnt(void);

#endif /* STORAGE_CONFIG_H  */
