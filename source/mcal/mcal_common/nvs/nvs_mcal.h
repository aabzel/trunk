#ifndef NVS_GENERAL_DRV_H
#define NVS_GENERAL_DRV_H

#include "std_includes.h"
#include "flash_mcal.h"
#include "nvs_config.h"
#include "nvs_types.h"
#include "nvs_write.h"

#ifdef HAS_NVS_CUSTOM
#include "nvs_custom_drv.h"
#endif

#ifdef HAS_NVS_DIAG
#include "nvs_diag.h"
#endif


/* API */
const NvsConfig_t* NvsGetConfig(uint8_t num);
NvsHandle_t* NvsGetNode(uint8_t num);
bool nvs_mcal_init(void);
bool nvs_init_custom(void);
bool nvs_init_common(const NvsConfig_t* const Config, NvsHandle_t* const Node);
bool nvs_init_one(uint8_t num);

bool nvs_proc_one(uint8_t num);
bool nvs_proc(void);

/*getters*/
bool is_nvs_addr_range(uint8_t num, uint32_t address, uint32_t size);
bool is_nvs_addr(uint8_t num, uint32_t address);
bool nvs_get_first_spare_page(uint8_t num);
bool nvs_mcal_read(uint8_t num, uint32_t flash_addr, uint8_t* const out_array, uint32_t num_bytes);
uint16_t nvs_calc_crc16(uint8_t num);

/*setters*/

#endif /* NVS_GENERAL_DRV_H */
