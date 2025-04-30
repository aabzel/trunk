#ifndef SRC_DEVICE_ID_H
#define SRC_DEVICE_ID_H

#include <stdint.h>

#include "sys.h"

void dump_device_id(void);
uint64_t get_device_serial(void);
bool device_has_chip_id(void);
const char* get_mcu_name(void);
const char* get_mcu_mask_id(void);

#endif /* SRC_DEVICE_ID_H */
