#ifndef DMA_CHANNEL_MCAL_ISR_H
#define DMA_CHANNEL_MCAL_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"

bool DmaChannelHalfIsrLL(DmaChannelHandle_t* const Node);
bool DmaChannelDoneIsrLL(DmaChannelHandle_t* const Node);
bool DmaChannelM1HalfTxIsrLL(DmaChannelHandle_t* const Node);
bool DmaChannelM1FullTxIsrLL(DmaChannelHandle_t* const Node);
bool DmaChannelErrorIsrLL(DmaChannelHandle_t* const Node);
bool DmaChannelAbortIsrLL(DmaChannelHandle_t* const Node);
bool DmaChannelAllIsrLL(DmaChannelHandle_t* const Node);

bool DmaChannelHalfIsr(Dma_t dma_num, DmaChannel_t channel);
bool DmaChannelDoneIsr(Dma_t dma_num, DmaChannel_t channel);
bool DmaChannelErrorIsr(Dma_t dma_num, DmaChannel_t channel);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_MCAL_ISR_H */
