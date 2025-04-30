#ifndef EEPROM_MCAL_H
#define EEPROM_MCAL_H

#include <stddef.h>

#include "std_includes.h"
#include "eeprom_config.h"
#include "eeprom_types.h"

#ifdef HAS_FREE_RTOS
#include "FreeRTOS.h"
#include "semphr.h"
#endif

#ifdef HAS_EEPROM_DIAG
#include "eeprom_diag.h"
#endif

#ifdef HAS_EEPROM_WRITE
#include "eeprom_write.h"
#endif


#ifdef HAS_FREE_RTOS
extern SemaphoreHandle_t xEepromWrireSem;
#endif

/*API*/
bool eeprom_mcal_init(void);
const EepromConfig_t* EepromGetConfig(uint8_t num) ;
EepromHandle_t* EepromGetNode(uint8_t num);
bool eeprom_init_common(const EepromConfig_t* const Config, EepromHandle_t* const Node);
bool eeprom_is_valid_config(const EepromConfig_t* const Config);

bool eeprom_mcal_unlock(void);
bool eeprom_mcal_lock(void);

int32_t eeprom_get_fragment_number(uint32_t in_addr,uint32_t fragment_size) ;
bool eeprom_interrupt_ctrl(bool on_off);
bool Addr2SectorSize(uint32_t addr, uint32_t* sector, uint32_t* sec_size) ;


/*getters*/
bool eeprom_read_relative(const uint32_t offset, const uint32_t size);
void eeprom_read_word(uint32_t read_addr, uint16_t* p_buffer, uint16_t num_read);
bool eeprom_dword_read(const uint32_t phy_addr, uint32_t* const dword);
bool eeprom_bytes_read(const uint32_t phy_addr, uint8_t * const byte, uint32_t size);
bool eeprom_byte_read(const uint32_t phy_addr, uint8_t * const byte);
bool eeprom_mcal_read(uint32_t in_eeprom_addr, uint8_t* const rx_array, uint32_t size);
bool eeprom_get_first_addr_spare_piece(const uint32_t size, uint32_t* const start_addr );
bool eeprom_is_the_same(uint32_t addr_val, uint8_t* const array, uint32_t size);
bool eeprom_is_address_range(uint32_t address, uint32_t size);
bool eeprom_is_address(uint32_t eeprom_addr);
bool eeprom_is_erased(uint32_t addr, uint32_t size) ;
bool eeprom_find_spare_region(uint32_t* out_addr, uint32_t size);
/*Busy names for Zephyr RTOS:eeprom_api_read eeprom_read*/
bool eeprom_scan(uint8_t* base, uint32_t size, float* usage_pec, uint32_t* spare, uint32_t* busy);
bool is_eeprom_spare(uint32_t eeprom_addr, uint32_t size);

#endif /* EEPROM_MCAL_H */
