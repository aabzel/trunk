#ifndef DMA_CHANNEL_CONFIG_H
#define DMA_CHANNEL_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"
//#include "dma_channel_config_adc.h"

typedef enum{
   DMA_CHANNEL_NUM_ADC1 = 1,
   DMA_CHANNEL_NUM_SDIO_RX ,
   DMA_CHANNEL_NUM_SDIO_TX ,
   DMA_CHANNEL_NUM_MEMCPY1 ,
   DMA_CHANNEL_NUM_MEMCPY2 ,
   DMA_CHANNEL_NUM_CNT
}DmaChannelLegalNums_t;

extern const DmaChannelConfig_t DmaChannelConfig[];
extern volatile DmaChannelHandle_t DmaChannelInstance[];

uint32_t dma_channel_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_CONFIG_H  */
