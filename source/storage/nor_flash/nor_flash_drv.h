#ifndef NOR_FLASH_DRV_H
#define NOR_FLASH_DRV_H

#include "std_includes.h"
#include "nor_flash_api.h"
#include "nor_flash_config.h"
#include "nor_flash_dep.h"
#include "nor_flash_types.h"

const NorFlashConfig_t* NorFlashGetConfig(uint8_t num);
NorFlashItem_t* NorFlashGetNode(uint8_t num);

uint8_t nor_flash_read_byte(uint8_t flash_num, uint32_t phy_address) ;
bool nor_flash_verify_zero(uint8_t num, uint32_t phy_address, uint32_t size);
bool nor_flash_verify(uint8_t num, uint32_t phy_address, const uint8_t* const data, uint32_t array_len);
bool nor_flash_erase_verify(uint8_t num, uint32_t phy_address, uint32_t size);
bool nor_flash_is_valid_addr(uint8_t num, uint32_t phy_address);
bool nor_flash_is_spare_chunk(uint8_t num, uint32_t phy_address, uint32_t size);
bool nor_flash_scan(uint8_t num, uint32_t phy_address, uint32_t size, double* usage_pec, uint32_t* spare,
                    uint32_t* busy);
bool nor_flash_check(uint8_t num);
bool nor_flash_init(void);
bool nor_flash_init_one(uint8_t num);
#if 0
bool nor_flash_read(uint8_t num, uint32_t phy_address, uint8_t* const data, uint32_t array_len);
bool nor_flash_zero(uint8_t num, uint32_t phy_address, uint32_t size);
#endif
bool nor_flash_write_lazy(uint8_t num, uint32_t phy_address, const uint8_t* const data, uint32_t array_len);
bool nor_flash_memmove(uint8_t num, uint32_t from_phy_address, uint32_t to_phy_address, uint32_t size);
uint16_t nor_flash_calc_crc16(uint8_t num, uint32_t phy_address, uint32_t size);

#endif /* NOR_FLASH_DRV_H */
