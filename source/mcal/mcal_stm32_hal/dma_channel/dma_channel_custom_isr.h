#ifndef DMA_CHANNEL_CUSTOM_ISR_H
#define DMA_CHANNEL_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_inc.h"
#include "dma_mcal.h"
#include "dma_custom_types.h"
#include "stm32fx_hal.h"

#ifndef HAS_DMA
#error "+HAS_DMA"
#endif

void DmaChannelAll(DMA_HandleTypeDef *h_dma);
void DmaChannelError(DMA_HandleTypeDef *h_dma);
void DmaChannelAbort(DMA_HandleTypeDef *h_dma);
void DmaChannelTxDone(DMA_HandleTypeDef *h_dma);
void DmaChannelTxHalf(DMA_HandleTypeDef *h_dma);
void DmaChannelM1HalfTx(DMA_HandleTypeDef *h_dma);
void DmaChannelM1FullTx(DMA_HandleTypeDef *h_dma);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_CUSTOM_ISR_H  */
