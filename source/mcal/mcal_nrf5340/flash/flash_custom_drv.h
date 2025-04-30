#ifndef FLASH_NRF_DRV_H
#define FLASH_NRF_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "macro_utils.h"
#include "sys_config.h"
#include "flash_config.h"
#include "flash_types.h"

#if defined(HAS_CORE_APP) &&defined(HAS_CORE_NET)
#error "Core Select Error"
#endif

#if !defined(HAS_CORE_APP) && !defined(HAS_CORE_NET)
#error "No Core Select Error"
#endif


uint8_t Address2PageNum(uint32_t address);
bool Addr2SectorSize(uint32_t addr, uint32_t *sector, uint32_t *sec_size);
bool flash_is_page_start(uint32_t addr);
bool flash_find_spare_region(uint32_t* out_addr, uint32_t size);


#endif /* FLASH_NRF_DRV_H  */
