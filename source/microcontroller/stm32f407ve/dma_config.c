#include "dma_config.h"

#include "data_utils.h"

const DmaConfig_t SECTION_CFG_DATA DmaConfig[] = {
    {.num=1, .dma_num=1,     .name="DMA1",    .valid=true,    },
    {.num=2, .dma_num=2,     .name="DMA2",    .valid=true,    },
};

DmaHandle_t DmaInstance[]={
    {.num=1, .valid=true,},
    {.num=2, .valid=true,},
};

COMPONENT_GET_CNT(Dma, dma)

