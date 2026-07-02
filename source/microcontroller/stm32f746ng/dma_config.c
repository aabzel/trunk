#include "dma_config.h"

#include <stddef.h>
#include <string.h>

#include "std_includes.h"
#include "data_utils.h"
#include "stm32f7xx_hal.h"
#include "hal_diag.h"

#ifndef HAS_DMA
#error "+ HAS_DMA"
#endif

const DmaConfig_t DmaConfig[]={
#ifdef HAS_DMA1
    {
    		.num=1,    .dma_num=1,   .name="DMA1",     .valid=true,
    },
#endif /*HAS_DMA2*/

#ifdef HAS_DMA2
    {
    		.num=2,    .dma_num=2,   .name="DMA2",     .valid=true,
    },
#endif /*HAS_DMA2*/

};

DmaHandle_t DmaInstance[]={
#ifdef HAS_DMA1
    {.num=1, 
     .valid=true,},
#endif /**/

#ifdef HAS_DMA2
    {.num=2, 
     .valid=true,},
#endif /**/
};

COMPONENT_GET_CNT(Dma, dma)


