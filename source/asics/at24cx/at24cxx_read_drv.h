#ifndef AT24CXX_READ_DRV_H
#define AT24CXX_READ_DRV_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "at24cxx_config.h"
#include "at24cxx_types.h"

bool at24cxx_read_address_ll(At24cxxHandle_t* const Node, uint16_t* const address);
uint8_t at24cxx_read_byte_short(uint8_t num, uint16_t address);
bool at24cxx_read_byte(uint8_t num, uint16_t address, uint8_t* const data);
bool at24cxx_read(uint8_t num, uint16_t address, void* const data, size_t size);
bool at24cxx_read_address(uint8_t num, uint16_t* const address);

#endif /* AT24CXX_READ_DRV_H */
