#ifndef DMA_CUSTOM_ISR_H
#define DMA_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dma_custom_types.h"

bool DMAxChannelyIRQHandler(uint8_t dma_num, DmaChannel_t channel);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CUSTOM_ISR_H  */
