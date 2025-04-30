#ifndef FLASH_MCAL_H
#define FLASH_MCAL_H

#include <stddef.h>

#include "std_includes.h"
#include "flash_config.h"
#include "flash_types.h"

#ifdef HAS_FREE_RTOS
#include "FreeRTOS.h"
#include "semphr.h"
#endif

#ifdef HAS_FLASH_DIAG
#include "flash_diag.h"
#endif


#ifdef HAS_FREE_RTOS
extern SemaphoreHandle_t xFlashWrireSem;
#endif

/*API*/
bool flash_init(void);
const FlashConfig_t* FlashGetConfig(uint8_t num) ;
FlashHandle_t* FlashGetNode(uint8_t num);
bool flash_init_common(const FlashConfig_t* const Config, FlashHandle_t* const Node);
bool flash_is_valid_config(const FlashConfig_t* const Config);

bool flash_mcal_unlock(void);
bool flash_mcal_lock(void);
bool flash_lock_ctrl(bool on_off);
bool flash_is_sector_start(uint32_t rand_addr, uint32_t chunk);
bool flash_get_sector_start(uint32_t rand_addr, uint32_t chunk, uint32_t* sector_start_out);

int32_t flash_get_fragment_number(uint32_t in_addr,uint32_t fragment_size) ;
bool flash_interrupt_ctrl(bool on_off);
//bool flash_addr_to_sector_size(uint32_t addr, uint32_t* sector, uint32_t* sec_size);
// sector=page
#ifdef HAS_FLASH_WRITE

bool flash_erase_sector(uint32_t addr) ;
bool flash_is_legal_change_array(uint32_t flash_addr, const uint8_t* const wr_array, uint32_t size);
bool flash_is_legal_change(uint8_t prev_byte, uint8_t new_byte);
bool flash_mcal_erase(uint32_t addr, uint32_t size); // Busy names for Zephyr RTOS: flash_erase;flash_api_erase
bool flash_mcal_eraseall(void);
bool flash_mcal_erasesector(uint32_t addr);
bool flash_mcal_erasepage(uint32_t addr);
bool flash_mcal_erasepages(uint8_t page_start, uint8_t page_end);
bool flash_mcal_write(uint32_t flash_addr, uint8_t* data, uint32_t size);
bool flash_mcal_writeite_dword(uint32_t flash_addr, uint32_t* wr_array, size_t size);
bool flash_mcal_eraseblock(uint32_t phy_address, uint32_t block_size);
bool flash_zero(uint32_t flash_addr, uint32_t size);
#endif /*HAS_FLASH_WRITE*/

/*getters*/
bool is_spi_flash_address(uint32_t address) ;
bool is_address_range(uint32_t address, uint32_t size);
bool flash_find_spare_region(uint32_t* out_addr, uint32_t size);
/*Busy names for Zephyr RTOS:flash_api_read flash_read*/
bool flash_mcal_read(uint32_t in_flash_addr, uint8_t* const rx_array, uint32_t size);
void flash_read_u16(uint32_t read_addr, uint16_t* p_buffer, uint16_t num_read);
bool flash_scan(uint8_t* base, uint32_t size, float* usage_pec, uint32_t* spare, uint32_t* busy);
uint32_t flash_get_first_spare_page(void);
bool is_flash_addr(uint32_t flash_addr);
bool is_flash_addr_range(uint32_t flash_addr, uint32_t size);
bool is_flash_spare(uint32_t flash_addr, uint32_t size);
bool is_erased(uint32_t addr, uint32_t size);
bool is_text_addr(uint32_t addr);
bool flash_is_the_same(  uint32_t addr, uint8_t* const array, size_t size);
bool flash_is_bootloader(uint32_t* address);
bool flash_is_generic(uint32_t* address);
bool flash_is_mbr(uint32_t address);
int32_t flash_addr_to_sector_num(uint32_t flash_addr);

#endif /* FLASH_MCAL_H */
