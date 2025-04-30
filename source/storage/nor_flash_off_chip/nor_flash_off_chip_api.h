#ifndef OFF_CHIP_NOR_FLASH_API_H
#define OFF_CHIP_NOR_FLASH_API_H

#include <stdbool.h>
#include <stdint.h>

#include "nor_flash_const.h"
#include "nor_flash_off_chip_dep.h"

bool nor_flash_off_chip_read(uint32_t address, uint8_t* data, uint32_t array_len);
bool nor_flash_off_chip_write(uint32_t address, const uint8_t* const data, uint32_t size);
bool nor_flash_off_chip_erase_sector(uint32_t address);
bool nor_flash_off_chip_erase_block(uint32_t address, NorFlashBlockSize_t block_size);
bool nor_flash_off_chip_erase_mem(uint32_t address, uint32_t size);
bool nor_flash_off_chip_erase_chip(void);
bool nor_flash_off_chip_zero(uint32_t address, uint32_t size);

#endif /* OFF_CHIP_NOR_FLASH_API_H */
