#ifndef W25Q16BV_DRV_H
#define W25Q16BV_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "w25q16bv_config.h"
#include "w25q16bv_dep.h"
#include "w25q16bv_types.h"

#ifdef HAS_W25Q16BV_DIAG
#include "w25q16bv_diag.h"
#endif



/*API*/
W25q16bvHandle_t* W25q16bvGetNode(uint8_t num);
const W25q16bvConfig_t* W25q16bvGetConfig(uint8_t num);
bool w25q16bv_proc_one(uint8_t num);
bool w25q16bv_proc(void) ;
bool w25q16bv_init_custom(void) ;
bool w25q16bv_init_one(uint8_t num);
bool w25q16bv_mcal_init(void);
bool w25q16bv_wait_busy(const uint8_t num, const  uint32_t timeout);

/*Setter*/
bool w25q16bv_prog_page(const uint8_t num, const uint32_t address, const uint8_t* const data, const uint16_t size);
bool w25q16bv_write_enable(const uint8_t num);
bool w25q16bv_chip_erase(const uint8_t num);

/*Getter*/
bool w25q16bv_read_data(const uint8_t num, const uint32_t address, uint8_t* const data, const uint16_t size);



#endif /* W25Q16BV_DRV_H */
