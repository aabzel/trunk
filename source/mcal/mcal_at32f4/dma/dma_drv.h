#ifndef DMA_CUSTOM_DRV_H
#define DMA_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dma_mcal.h"
#include "dma_custom_types.h"
#include "at32f435_437.h"

#ifndef HAS_DMA
#error "+HAS_DMA"
#endif

DMA_Stream_TypeDef* gma_stream_num_2_prt(uint8_t dma_num, uint8_t stream_num);
DMA_TypeDef* DmaNum2Instance(uint8_t num);
bool dma_init_ll(uint8_t num);
bool dma_init(void);
bool dma_stop(uint8_t num);
bool dma_start(uint8_t num, uint32_t src_address, uint32_t dst_address, uint32_t bytes);
DmaStreamIntStatusReg_t DmaGetStream(uint8_t dma_num, uint8_t stream_num);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CUSTOM_DRV_H  */
