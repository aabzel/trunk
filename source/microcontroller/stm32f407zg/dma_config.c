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
    {.num=1, .valid=true,},
#endif /*HAS_DMA1*/

#ifdef HAS_DMA2
    {.num=2, .valid=true,},
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

static uint16_t DmaSdioMem[16]={0};

const DmaChannelConfig_t DmaChannelConfig[] ={
        {
                .num=DMA2_SDIO_RX,
                .CallBackHalf=NULL,
                .CallBackDone=NULL,
                .memory_burst=DMA_BURST_INC4,
                .periph_burst=DMA_BURST_INC4,
                .name="SDIO_RX",
                .channel=DMA_CHAN_4,
                .dir=DMA_MCAL_DIR_PERIPH_TO_MEMORY,
                .mem_inc=DMA_INC_ON,
                .per_inc=DMA_INC_OFF,
                .aligment_per=DMA_ALIG_WORD,
                .aligment_mem=DMA_ALIG_WORD,
                .dma_num=2,
                .fifo=DMA_FIFO_ON,
                .valid=true,
                .priority=DMA_PRIOR_LOW,
                .mode=DMA_MODE_NORMAL,
                .memory_base_addr=(uint32_t)DmaSdioMem,        /* base addrress for memory */
                .buffer_size=ARRAY_SIZE(DmaSdioMem),  /*counter to transfer (0~0xFFFF)    */

                //.peripheral_base_addr=SDIO->,    /* base addrress for peripheral */
                .mux=0,
        },
        {
                .valid=true,
                .CallBackHalf=NULL,
                .CallBackDone=NULL,
                .num=DMA2_SDIO_TX,
                .name="SDIO_TX",
                .channel=DMA_CHAN_4,
                .dir=DMA_MCAL_DIR_MEMORY_TO_PERIPH,
                .mem_inc=DMA_INC_ON,
                .per_inc=DMA_INC_OFF,
                .aligment_mem=DMA_ALIG_WORD,
                .aligment_per=DMA_ALIG_WORD,
                .dma_num=2,
                .fifo=DMA_FIFO_ON,
                .memory_burst=DMA_BURST_INC4,
                .periph_burst=DMA_BURST_INC4,
                .priority=DMA_PRIOR_LOW,
                .mode=DMA_MODE_NORMAL,
                .buffer_size=ARRAY_SIZE(DmaSdioMem),  /*counter to transfer (0~0xFFFF)    */
                .memory_base_addr= (uint32_t)DmaSdioMem,        /* base addrress for memory */

                //.peripheral_base_addr=SDIO,    /* base addrress for peripheral */
                .mux=0,
        },
};



volatile DmaChannelHandle_t DmaChannelInstance[]={
        {.valid=true, .num=DMA2_SDIO_TX,},
        {.valid=true, .num=DMA2_SDIO_RX,}
};

uint32_t dma_channel_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DmaChannelInstance);
    cnt2 = ARRAY_SIZE(DmaChannelConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
