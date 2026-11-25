#ifndef DMA_CUSTOM_DRIVER_H
#define DMA_CUSTOM_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dma_types.h"
#include "dma_custom_types.h"
#include "dma_custom_isr.h"

const DmaMuxInfo_t* DmaMuxToInfo(uint8_t mux);
DmaChannelInfo_t * DmaChannelGenInfo(uint8_t num, DmaChannel_t channel);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CUSTOM_DRIVER_H  */
