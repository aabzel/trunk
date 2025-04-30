#ifndef NOR_FLASH_API_H
#define NOR_FLASH_API_H

#include <stdbool.h>
#include <stdint.h>

#include "nor_flash_config.h"
#include "nor_flash_dep.h"
#include "nor_flash_types.h"

bool nor_flash_read(uint8_t flash_num, uint32_t phy_address, uint8_t* const data, uint32_t size);
bool nor_flash_erase_mem(uint8_t flash_num, uint32_t phy_address, uint32_t size);
bool nor_flash_erase_sector(uint8_t flash_num, uint32_t phy_address);
bool nor_flash_erase_chip(uint8_t flash_num);
bool nor_flash_erase_block(uint8_t flash_num, uint32_t phy_address, uint32_t block_size);
bool nor_flash_page_program(uint8_t flash_num, uint32_t phy_address, const uint8_t* const data, uint32_t size);
bool nor_flash_write(uint8_t flash_num, uint32_t phy_address, const uint8_t* const data, uint32_t size);
bool nor_flash_zero(uint8_t flash_num, uint32_t phy_address, uint32_t size);
bool nor_flash_reset(uint8_t flash_num);

#endif /* NOR_FLASH_API_H */
