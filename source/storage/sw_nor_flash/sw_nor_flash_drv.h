#ifndef SW_NOR_FLASH_DRV_H
#define SW_NOR_FLASH_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "nor_flash_config.h"
#include "sw_nor_flash_config.h"
#include "sw_nor_flash_dep.h"
#include "sw_nor_flash_types.h"

bool sw_nor_flash_read(uint8_t num, uint32_t phy_address, uint8_t * const data, uint32_t array_len);
bool sw_nor_flash_page_program(uint8_t num, uint32_t phy_address, const uint8_t* constdata, uint32_t array_len);
bool sw_nor_flash_erase_sector(uint8_t num, uint32_t phy_address);
bool sw_nor_flash_erase_block(uint8_t num, uint32_t phy_address, uint32_t block_size);
bool sw_nor_flash_erase_chip(uint8_t num);
bool sw_nor_flash_zero(uint8_t num, uint32_t phy_address, uint32_t size);
bool sw_nor_flash_write(uint8_t num, uint32_t phy_address, const uint8_t* const data, uint32_t array_len);
bool sw_nor_flash_init(uint8_t num);
bool sw_nor_flash_erase_mem(uint8_t num, uint32_t phy_address, uint32_t size);

#endif /* SW_NOR_FLASH_DRV_H */
