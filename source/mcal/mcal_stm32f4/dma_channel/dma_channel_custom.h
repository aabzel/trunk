#ifndef DMA_CHANNEL_CUSTOM_DRV_H
#define DMA_CHANNEL_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dma_mcal.h"
#include "dma_custom_types.h"
#include "stm32f4xx_hal.h"

#ifndef HAS_DMA
#error "+HAS_DMA"
#endif

DMA_Stream_TypeDef* DmaChannelToDMAx(uint8_t dma_num, DmaChannel_t channel);
DMA_Stream_TypeDef* gma_stream_num_2_prt(uint8_t dma_num, uint8_t stream_num);
DmaStreamIntStatusReg_t DmaGetStream(uint8_t dma_num, uint8_t stream_num);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_CUSTOM_DRV_H  */
