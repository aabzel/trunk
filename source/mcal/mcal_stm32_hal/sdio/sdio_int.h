#ifndef SDIO_INT_H
#define SDIO_INT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sdio_types.h"
#include "std_includes.h"

#ifndef HAS_SDIO_INTERRUPT
#error "+HAS_SDIO_INTERRUPT"
#endif

bool sdio_read_sector_it(uint8_t num, uint32_t block_num, uint32_t block_cnt, uint8_t* const data);
bool sdio_write_sector_it(uint8_t num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const data) ;

#ifdef __cplusplus
}
#endif

#endif /* SDIO_INT_H */
