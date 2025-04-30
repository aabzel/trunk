#ifndef NVS_GENERAL_DRV_H
#define NVS_GENERAL_DRV_H

#include "std_includes.h"
#include "flash_mcal.h"
#include "nvs_config.h"
#include "nvs_types.h"

#ifdef HAS_NVS_CUSTOM
#include "nvs_custom_drv.h"
#endif

#ifdef HAS_NVS_DIAG
#include "nvs_diag.h"
#endif


//#define MIN_SIZE_OF_ITEM (sizeof(mmItem_t)+QWORD_LEN)
bool is_nvs_addr_range(uint32_t address, uint32_t size);
bool is_nvs_addr(uint32_t flash_addr);
bool nvs_get_first_spare_page(void);
bool nvs_mcal_read(uint32_t flash_addr, uint8_t* const out_array, uint32_t num_bytes);
bool nvs_init(void);
uint16_t nvs_calc_crc16(void);

#ifdef HAS_NVS_WRITE
bool nvs_erase_page(uint32_t addr);
bool nvs_erase(uint32_t addr, uint32_t len);
bool nvs_errase_all(void);
bool nvs_mcal_write(const uint32_t addr, const uint8_t* const array, const uint32_t size);
#endif

#endif /* NVS_GENERAL_DRV_H  */
