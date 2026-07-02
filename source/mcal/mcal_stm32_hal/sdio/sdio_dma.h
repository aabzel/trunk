#ifndef SDIO_DMA_H
#define SDIO_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sdio_types.h"
#include "std_includes.h"

#ifndef HAS_SDIO_DMA
#error "+HAS_SDIO_DMA"
#endif

bool sdio_dma_init(SD_HandleTypeDef* sdHandle);

bool sdio_write_sector_dma(uint8_t num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData) ;
bool sdio_read_sector_dma(uint8_t num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData) ;


#ifdef __cplusplus
}
#endif

#endif /* SDIO_DMA_H */
