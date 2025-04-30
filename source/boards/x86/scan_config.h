#ifndef SCAN_CONFIG_H
#define SCAN_CONFIG_H

#include "std_includes.h"
#include "scan_types.h"

extern const ScanConfig_t ScanConfig[];
extern ScanHandle_t ScanInstance[];

uint32_t scan_get_cnt(void);

#endif /* SCAN_CONFIG_H */
