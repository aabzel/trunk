#ifndef MX25R6435F_DRV_H
#define MX25R6435F_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "mx25r6435f_config.h"
#include "mx25r6435f_dep.h"
#include "mx25r6435f_types.h"

#ifdef HAS_MX25R6435F_DIAG
#include "mx25r6435f_diag.h"
#endif

bool mx25r6435f_is_valid_addr(uint32_t address);
bool pack_24bit_big_endian(uint32_t address, uint8_t* const buff);
bool mx25r6435f_read_sfdp(uint32_t address, uint16_t* word);
bool mx25r6435f_read(uint32_t address, uint8_t* data, uint32_t size);
bool mx25r6435f_scan(uint32_t address, uint32_t size, double* usage_pec, uint32_t* spare, uint32_t* busy);
bool mx25r6435f_reg_set(uint8_t reg_addr, uint8_t reg_val);
bool mx25r6435f_reg_get(uint8_t reg_addr, uint8_t* reg_val);
bool mx25r6435f_reg_read_all(void);
bool mx25r6435f_page_program(uint32_t address, const uint8_t* const data, uint32_t size);
bool mx25r6435f_write(uint32_t address, const uint8_t* const data, uint32_t size);
bool mx25r6435f_verify(uint32_t address, const uint8_t* const data, uint32_t size);
bool mx25r6435f_erase_chip(void);
bool mx25r6435f_erase_mem(uint32_t address, uint32_t size);
bool mx25r6435f_erase_block(uint32_t address, Mx25BlockSize_t block_size);
bool mx25r6435f_erase_sector(uint32_t address);
bool mx25r6435f_check(void);
bool mx25r6435f_is_write_in_progress(void);
bool mx25r6435f_wait_write_done(uint32_t time_out);
bool mx25r6435f_deep_power_down(void);
bool mx25r6435f_is_connected(void);
bool mx25r6435f_init(void);
bool mx25r6435f_status_reg_read(void);
bool mx25r6435f_identification_read(void);
bool mx25r6435f_configuration_read(void);
bool mx25r6435f_electronic_signature_read(void);
bool mx25r6435f_proc(void);
bool mx25r6435f_write_reg_by_bitmask(uint8_t reg_addr, char* bit_mask);
bool mx25r6435f_write_enable(bool on_off);
bool mx25r6435f_reset(void);
bool mx25r6435f_reset_hw(void);
bool mx25r6435f_zero(uint32_t address, uint32_t size);
uint32_t mx25r6435f_reg_cnt(void);

#endif /* MX25R6435F_DRV_H */
