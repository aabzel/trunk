#ifndef DMA_GENERAL_ISR_H
#define DMA_GENERAL_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dma_types.h"

bool DmaChannelHalfIsrLL(DmaChannelHandle_t* const Node) ;
bool DmaChannelDoneIsrLL(DmaChannelHandle_t* const Node);
bool DmaChannelErrorIsr_ll(DmaChannelHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* DMA_GENERAL_ISR_H  */
