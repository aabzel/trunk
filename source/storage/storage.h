#ifndef STARAGE_H
#define STARAGE_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "storage_types.h"
#include "storage_diag.h"

bool memory_read( const uint32_t phy_address, uint8_t* const data,  const uint32_t size);
bool memory_write(const uint32_t phy_address, const uint8_t* const data,  const uint32_t size);
uint8_t read_addr_8bit(const uint32_t address);
bool write_addr_8bit(const uint32_t address, const uint8_t value) ;
bool storage_proc_cmd(uint8_t tbfp_num, const uint8_t* const payload, const uint32_t size);
bool storage_tbfp_memory(uint8_t tbfp_num, const uint8_t* const payload, const uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* STARAGE_H */
