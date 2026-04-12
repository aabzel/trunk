#ifndef DMA_CHANNEL_CONFIG_H
#define DMA_CHANNEL_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"
#include "dma_types.h"


typedef enum{
   DMA2_SDIO_RX = 1,
   DMA2_SDIO_TX = 2,

   DMA2_UNDEF= 0,
}DmaLegalNums_t;

extern const DmaConfig_t DmaConfig[];
extern DmaHandle_t DmaInstance[];

extern const DmaChannelConfig_t DmaChannelConfig[];
extern volatile DmaChannelHandle_t DmaChannelInstance[];

uint32_t dma_get_cnt(void);
uint32_t dma_channel_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_CONFIG_H  */
