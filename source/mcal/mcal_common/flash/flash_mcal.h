#ifndef FLASH_MCAL_H
#define FLASH_MCAL_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "std_includes.h"
#include "flash_config.h"
#include "flash_types.h"
#include "flash_isr.h"

#ifdef HAS_FLASH_WRITE
#include "flash_write.h"
#endif

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
const FlashConfig_t* FlashGetConfig(uint8_t num);
FlashHandle_t* FlashGetNode(uint8_t num);

bool flash_init_custom(void);
bool flash_mcal_init(void);
bool flash_init_common(const FlashConfig_t* const Config, FlashHandle_t* const Node);
bool FlashIsValidConfig(const FlashConfig_t* const Config);

bool flash_mcal_unlock(void);
bool flash_mcal_lock(void);
bool flash_lock_ctrl(bool on_off);
bool flash_is_sector_start(uint32_t rand_addr, uint32_t chunk);
bool flash_get_sector_start(uint32_t rand_addr, uint32_t chunk, uint32_t* sector_start_out);

int32_t flash_get_fragment_number(uint32_t in_addr,uint32_t fragment_size) ;
bool flash_interrupt_ctrl(bool on_off);
//bool flash_addr_to_sector_size(uint32_t addr, uint32_t* sector, uint32_t* sec_size);

/*getters*/
uint32_t flash_get_first_spare_size_aligned(uint32_t starting_point,
                                            uint32_t search_size,
                                            const uint32_t alignment,
                                            const uint32_t size);

bool Addr2SectorSize(uint32_t addr, uint32_t* sector, uint32_t* sec_size);
bool is_spi_flash_address(uint32_t address) ;
bool flash_find_spare_region(uint32_t* out_addr, uint32_t size);
/*Busy names for Zephyr RTOS:flash_api_read flash_read*/
bool flash_mcal_read(uint32_t in_flash_addr, uint8_t* const rx_array, uint32_t size);
void flash_read_word(uint32_t address, uint16_t* const  word, uint16_t size);
bool flash_scan(uint8_t* base, uint32_t size, float* usage_pec, uint32_t* spare, uint32_t* busy, uint8_t pattern );
bool is_flash_addr(const uint32_t flash_addr);
bool is_flash_address_range(uint32_t flash_addr, uint32_t size);
bool is_flash_spare(uint32_t flash_addr, uint32_t size);
bool is_flash_pattern(uint32_t address, uint32_t size, uint8_t pattern);
bool is_erased(uint32_t addr, uint32_t size);
bool is_text_addr(uint32_t addr);
bool flash_is_the_same(  uint32_t addr, uint8_t* const array, size_t size);
bool flash_is_bootloader(uint32_t* address);
bool flash_is_generic(uint32_t* address);
bool flash_is_mbr(uint32_t address);
uint32_t flash_get_first_spare_size(const uint32_t size);
int32_t flash_addr_to_sector_num(uint32_t flash_addr);
uint32_t flash_get_first_spare_page(void);


#ifdef __cplusplus
}
#endif

#endif /* FLASH_MCAL_H */
