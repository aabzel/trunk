#ifndef ZEPHYR_NVS_DRV_H
#define ZEPHYR_NVS_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "flash_drv.h"

#define MIN_SIZE_OF_ITEM (sizeof(mmItem_t)+QWORD_LEN)

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifndef HAS_FLASH
#error "+HAS_FLASH"
#endif

#ifndef HAS_NVS
#error "+HAS_NVS"
#endif

bool nvs_init(void);

#ifdef HAS_NVS_WRITE
bool nvs_erase(uint32_t addr, uint32_t array_len);
bool nvs_write(uint32_t addr, uint8_t* array, uint32_t array_len);
#endif

#endif /* ZEPHYR_NVS_DRV_H  */
