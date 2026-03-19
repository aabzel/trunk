#ifndef DMA_CHANNEL_MCAL_ISR_H
#define DMA_CHANNEL_MCAL_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"

bool DmaChannelHalfIsr(Dma_t dma_num, DmaChannel_t channel);
bool DmaChannelDoneIsr(Dma_t dma_num, DmaChannel_t channel);
bool DmaChannelErrorIsr(Dma_t dma_num, DmaChannel_t channel);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_MCAL_ISR_H */
