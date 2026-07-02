#include "dma_config.h"


#include "std_includes.h"
#include "data_utils.h"

#ifndef HAS_DMA
#error "+ HAS_DMA"
#endif

const DmaConfig_t SECTION_CFG_DATA DmaConfig[]={
#ifdef HAS_DMA1
    {
            .num=1,    .dma_num=1,   .name="DMA1",     .valid=true,
    },
#endif /**/

#ifdef HAS_DMA2
    {
            .num=2,    .dma_num=2,   .name="DMA2",     .valid=true,
    },
#endif /**/

};

DmaHandle_t DmaInstance[]={
#ifdef HAS_DMA1
    {.num = 1, .valid = true,},
#endif

#ifdef HAS_DMA2
    {.num = 2, .valid = true,},
#endif
};

COMPONENT_GET_CNT(Dma, dma)

