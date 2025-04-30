#ifndef AT24CXX_WRITE_DRV_H
#define AT24CXX_WRITE_DRV_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "at24cxx_config.h"
#include "at24cxx_drv.h"
#include "at24cxx_types.h"

bool at24cxx_write_ctrl(uint8_t num, bool on_off);
bool at24cxx_write(uint8_t num, uint16_t address, const uint8_t* const data, size_t size);
bool at24cxx_write_byte(uint8_t num, uint16_t address, uint8_t data);
bool at24cxx_write_page(uint8_t num, uint16_t address, const uint8_t* const page);
bool at24cxx_write_pattern(uint8_t num, uint8_t pattern);
bool at24cxx_erase(uint8_t num, uint16_t address, size_t size);
bool at24cxx_erase_chip(uint8_t num);

#endif /* AT24CXX_WRITE_DRV_H */
