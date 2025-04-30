#ifndef EEPROM_MCAL_WRITE_H
#define EEPROM_MCAL_WRITE_H


#include "std_includes.h"

bool eeprom_byte_erase(const uint32_t phy_addr);
bool eeprom_byte_write(const uint32_t phy_addr, const uint8_t byte);

bool eeprom_bytes_erase(const uint32_t phy_addr, const uint32_t size);
bool eeprom_bytes_write(const uint32_t phy_addr, const uint8_t*const  byte, uint32_t size);

bool eeprom_mcal_erase_all(void);
bool eeprom_mcal_erase(uint32_t phy_addr, uint32_t size);
bool eeprom_mcal_write(uint32_t phy_addr, uint8_t* data, uint32_t size);
bool eeprom_dwords_write(uint32_t phy_addr, uint32_t* wr_array, uint32_t size);
bool eeprom_dwords_zero(uint32_t phy_addr, uint32_t size);
bool eeprom_dword_erase(const uint32_t phy_addr);
bool eeprom_dword_write(const uint32_t phy_addr, const uint32_t wr_array);

bool eeprom_write_relative(const uint32_t offset, const uint8_t* const data, uint32_t size, uint32_t read_crc32 );

#endif /* EEPROM_MCAL_WRITE_H */
