#include "dma_config.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "data_utils.h"
#include "stm32f4xx_hal.h"

#ifndef HAS_DMA
#error "+ HAS_DMA"
#endif /**/

#ifndef HAS_DMA1
#error "+ HAS_DMA1"
#endif /**/



const DmaConfig_t DmaConfig[]={

#ifdef HAS_DMA1
    {.num=DMA1_I2S2_TX, .dma_num=1,  .stream_num=4,      .name="I2S2_TX",
     .channel=DMA_CHAN_0,
     .dir=DMA_DIR_MEMORY_TO_PERIPH,
     .mode=DMA_MODE_CIRCULAR,
     .mem_inc=DMA_INC_ON,
     .per_inc=DMA_INC_OFF,
     .aligment_per=DMA_ALIG_HALF_WORD,
     .aligment_mem=DMA_ALIG_HALF_WORD,
     .fifo=DMA_FIFO_ON,
     .priority=DMA_PRIOR_LOW,
	 .valid = true,
	 .memory_burst=DMA_BURST_SINGLE,
	 .periph_burst=DMA_BURST_SINGLE,
    },
#endif /**/


#ifdef HAS_DMA2

#endif /**/
};

DmaHandle_t DmaInstance[]={
#ifdef HAS_DMA1
    {.num=DMA1_I2S2_TX,	 .valid = true, },
#endif /**/
#ifdef HAS_DMA2
#endif /**/
};

uint32_t dma_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DmaInstance); 
    cnt2 = ARRAY_SIZE(DmaConfig); 
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    assert_param(1==cnt);
    return cnt;
}
