#include "dma_channel_config.h"

#include "data_utils.h"
#include "microcontroller_const.h"
#include "dma_channel_config_memcpy.h"

#ifdef HAS_ADC
#include "dma_channel_config_adc.h"
#else
#define DMA_CHANNEL_ADC
#endif

#ifdef HAS_SPI
#include "dma_channel_config_spi1.h"
#else
#define DMA_CHANNEL_SPI1
#endif

//    DMA_CHANNEL_SPI1

#define DMA_CHANNEL_ALL  \
    DMA_CHANNEL_MEMCPY   \
    DMA_CHANNEL_ADC

const DmaChannelConfig_t SECTION_CFG_DATA DmaChannelConfig[] = {
    DMA_CHANNEL_ALL
};

volatile DmaChannelHandle_t DmaChannelInstance[] = {
    { .num = 1,  .valid = true,    },
    { .num = 2,  .valid = true,    },
    { .num = 3,  .valid = true,    },
    { .num = 4,  .valid = true,    },
};

COMPONENT_GET_CNT(DmaChannel, dma_channel)

