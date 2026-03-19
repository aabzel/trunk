#ifndef NVS_WRITE_MCAL_H
#define NVS_WRITE_MCAL_H

#include "std_includes.h"
#include "nvs_types.h"

/*setters*/
bool nvs_mcal_write(uint8_t num,
                    const uint32_t addr,
                    const uint8_t* const data,
                    const uint32_t size);
bool nvs_mcal_erase(uint8_t num, uint32_t addr, uint32_t size);
bool nvs_errase_all(uint8_t num);

#endif /* NVS_WRITE_MCAL_H */
