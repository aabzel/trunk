#ifndef FLASH_CUSTOM_DRV_H
#define FLASH_CUSTOM_DRV_H

#include <stdbool.h>
#include <stdint.h>


bool Addr2SectorSize(uint32_t addr, uint32_t *sector, uint32_t *sec_size);
//bool flash_find_spare_region(uint32_t* out_addr, uint32_t size);


#endif /* FLASH_CUSTOM_DRV_H  */
