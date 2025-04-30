#include "dma_config.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "data_utils.h"
#include "stm32f4xx_hal.h"
#include "hal_diag.h"

#ifndef HAS_DMA
#error "+ HAS_DMA"
#endif /*HAS_DMA*/

const DmaConfig_t DmaConfig[]={
#ifdef HAS_DMA2
    {.num=DMA2_SDIO_RX, .dma_num=2,  .stream_num=3,      .name="SDIO_RX",
     .channel=DMA_CHAN_4,
     .dir=DMA_DIR_PERIPH_TO_MEMORY,
     .mode=DMA_MODE_PFCTRL,
     .mem_inc=DMA_INC_ON,
     .per_inc=DMA_INC_OFF,
     .aligment_per=DMA_ALIG_WORD,
     .aligment_mem=DMA_ALIG_WORD,
     .fifo=DMA_FIFO_ON,
     .priority=DMA_PRIOR_LOW,
	 .memory_burst=DMA_BURST_INC4,
	 .periph_burst=DMA_BURST_INC4,

	 .valid=true,
    },
#endif /*HAS_DMA2*/

#ifdef HAS_DMA2
    {.num=DMA2_SDIO_TX, .dma_num=2,  .stream_num=6,     .name="SDIO_TX",
      .channel=DMA_CHAN_4,
      .dir=DMA_DIR_MEMORY_TO_PERIPH,
      .mode=DMA_MODE_PFCTRL,
      .mem_inc=DMA_INC_ON,
      .per_inc=DMA_INC_OFF,
      .aligment_per=DMA_ALIG_WORD,
      .aligment_mem=DMA_ALIG_WORD,
      .fifo=DMA_FIFO_ON,
      .priority=DMA_PRIOR_LOW,
      .memory_burst=DMA_BURST_INC4,
	  .periph_burst=DMA_BURST_INC4,
	  .valid=true,
    },
#endif /*HAS_DMA2*/
};

DmaHandle_t DmaInstance[]={
#ifdef HAS_DMA2
    {.num=DMA2_SDIO_RX, .valid=true,},
    {.num=DMA2_SDIO_TX, .valid=true,},
#endif /*HAS_DMA2*/
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
    assert_param(2==cnt);
    return cnt;
}
