#ifndef FLASH_MCAL_WRITE_H
#define FLASH_MCAL_WRITE_H

#include <stddef.h>

#include "std_includes.h"
#include "flash_config.h"
#include "flash_types.h"
#ifdef  HAS_FLASH_CUSTOM
#include "flash_custom.h"
#endif

bool flash_mcal_erase_ll(uint32_t address, uint32_t size);
bool flash_mcal_write_ll(uint32_t address, const uint8_t* const data, uint32_t size);
bool flash_erase_sector(uint32_t addr) ;
bool flash_is_legal_change_array(uint32_t flash_addr, const uint8_t* const wr_array, uint32_t size);
bool flash_is_legal_change(uint8_t prev_byte, uint8_t new_byte);
// Busy names for Zephyr RTOS: flash_erase;flash_api_erase
bool flash_mcal_erase(uint32_t addr, uint32_t size);
bool flash_mcal_eraseall(void);
bool flash_mcal_erasesector(uint32_t addr);
bool flash_mcal_erasepage(uint32_t addr);
bool flash_mcal_erasepages(uint8_t page_start, uint8_t page_end);
bool flash_mcal_write(uint32_t flash_addr, const uint8_t* const data, uint32_t size);
bool flash_mcal_writeite_dword(uint32_t flash_addr, uint32_t* wr_array, size_t size);
bool flash_mcal_eraseblock(uint32_t phy_address, uint32_t block_size);
bool flash_zero(uint32_t flash_addr, uint32_t size);


#endif /* FLASH_MCAL_WRITE_H */
