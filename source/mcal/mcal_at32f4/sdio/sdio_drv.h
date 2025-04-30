#ifndef SDIO_CUSTOM_DRIVER_H
#define SDIO_CUSTOM_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_SDIO
#error "+HAS_SDIO"
#endif

#ifndef HAS_DMA
#warning "+HAS_DMA"
#endif

#include "hal_diag.h"
#include "sdio_custom_const.h"
#include "sdio_types.h"
#include "stm32f4xx.h"

#ifdef HAS_SDIO_DIAG
#include "sdio_diag.h"
#endif /**/

bool sdio_proc(void);
bool sdio_card_info_get(uint32_t sdio_num);
// bool sdio_is_connected(uint32_t sdio_num);

uint8_t SdioInstance2num(SD_TypeDef* Instance);
bool sdio_read_sector_time_out(uint8_t sdio_num, uint32_t block_num, uint32_t number_of_blocks, uint8_t* const RxData);

bool sdio_write_sector_time_out(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData);

#ifdef HAS_INTERRUPT
bool sdio_read_sector_it(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData);

bool sdio_write_sector_it(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData);
#endif

#ifdef HAS_DMA
bool sdio_read_sector_dma(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData);

bool sdio_write_sector_dma(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const RxData);
#endif /*HAS_DMA*/

bool sdio_read_sector(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData);

bool sdio_write_sector(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const RxData);

bool sdio_scan(uint8_t sdio_num);

bool sdio_init_ll(uint32_t sdio_num);
bool sdio_init(void);
uint16_t sdio_get_block_size(uint32_t sdio_num);
uint32_t sdio_get_block_num(uint32_t sdio_num);

#ifdef __cplusplus
}
#endif

#endif /* SDIO_CUSTOM_DRIVER_H */
