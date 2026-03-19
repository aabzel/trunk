#ifndef SDIO_POLL_H
#define SDIO_POLL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sdio_types.h"
#include "std_includes.h"

#ifndef HAS_SDIO_POLL
#error "+HAS_SDIO_POLL"
#endif

bool sdio_write_sector_time_out(uint8_t num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData);

bool sdio_read_sector_time_out(uint8_t num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData) ;

#ifdef __cplusplus
}
#endif

#endif /* SDIO_POLL_H */
