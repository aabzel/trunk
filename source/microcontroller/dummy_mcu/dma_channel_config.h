#ifndef DMA_CHANNEL_CONFIG_H
#define DMA_CHANNEL_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"


extern const DmaChannelConfig_t DmaChannelConfig[];
extern volatile DmaChannelHandle_t DmaChannelInstance[];

uint32_t dma_channel_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_CONFIG_H  */
