#include "dma_config.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef HAS_AT32F413_FIRMWARE_LIB
#include "at32f413.h"
#endif

#include "data_utils.h"
#include "hal_diag.h"

const DmaConfig_t DmaConfig[] = {
#ifdef HAS_DMA1
    {
        .valid = true,
        .num = 1,
        .dma_num = 1,
        .name = "DMA1",
    },
#endif /*HAS_DMA1*/

#ifdef HAS_DMA2
    {
        .valid = true,
        .num = 2,
        .dma_num = 2,
        .name = "DMA2",
    },
#endif /*HAS_DMA2*/
};

DmaHandle_t DmaInstance[] = {
#ifdef HAS_DMA1
    {
        .num = 1,
        .dma_num = 1,
        .valid = true,
    },
#endif /*HAS_DMA1*/

#ifdef HAS_DMA2
    {
        .num = 2,
        .dma_num = 2,
        .valid = true,
    },
#endif /*HAS_DMA2*/
};

uint32_t dma_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DmaInstance);
    cnt2 = ARRAY_SIZE(DmaConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}

const DmaChannelConfig_t DmaChannelConfig[] = {
    {
        .num = 1,
        .dma_num = 1,
        .channel = 1,
        .dir = DMA_MCAL_DIR_MEMORY_TO_MEMORY,
        .mode = DMA_MODE_NORMAL,
        .mem_inc = DMA_INC_ON,
        .per_inc = DMA_INC_ON,
        .aligment_per = DMA_ALIG_BYTE,
        .aligment_mem = DMA_ALIG_BYTE,
        .fifo = DMA_FIFO_OFF,
        .priority = DMA_PRIOR_LOW,
        .memory_burst = DMA_BURST_SINGLE,
        .peripheral_base_addr = 0x20000000,
        .memory_base_addr = 0x20000000,
        .periph_burst = DMA_BURST_SINGLE,
        .valid = true,
        .mux = 0,
    },
    {
        .num = 2,
        .dma_num = 1,
        .channel = 2,
        .valid = true,
        .mux = 0,
    },
    {
        .num = 3,
        .dma_num = 1,
        .channel = 3,
        .valid = true,
        .mux = 0,
    },
    {
        .num = 4,
        .dma_num = 1,
        .channel = 4,
        .valid = true,
        .mux = 0,
    },
    {
        .num = 5,
        .dma_num = 1,
        .channel = 5,
        .valid = true,
        .mux = 0,
    },
    {
        .num = 6,
        .dma_num = 1,
        .channel = 6,
        .valid = true,
        .mux = 0,
    },
    {
        .num = 7,
        .dma_num = 1,
        .channel = 7,
        .valid = true,
        .mux = 0,
    },
    {
        .num = 8,
        .dma_num = 2,
        .channel = 1,
        .valid = true,
        .mux = 115,
    },
    {
        .num = 9,
        .dma_num = 2,
        .channel = 2,
        .dir = DMA_MCAL_DIR_MEMORY_TO_PERIPH,
        .mode = DMA_MODE_NORMAL,
        .mem_inc = DMA_INC_ON,
#ifdef HAS_UART6
        .peripheral_base_addr = (uint32_t)&USART6->dt,
#endif
        .memory_base_addr = 0x20000000,
        .per_inc = DMA_INC_OFF,
        .aligment_per = DMA_ALIG_BYTE,
        .aligment_mem = DMA_ALIG_BYTE,
        .fifo = DMA_FIFO_OFF,
        .priority = DMA_PRIOR_MED,
        .memory_burst = DMA_BURST_SINGLE,
        .periph_burst = DMA_BURST_SINGLE,
        .valid = true,
        .mux = 0,
    },
    {
        .num = 10,
        .dma_num = 2,
        .channel = 3,
        .valid = true,
        .mux = 0,
    },
    {
        .num = 11,
        .dma_num = 2,
        .channel = 4,
        .valid = true,
        .mux = 0,
    },
    {
        .num = 12,
        .dma_num = 2,
        .channel = 5,
        .valid = true,
        .mux = 0,
    },
    {
        .num = 13,
        .dma_num = 2,
        .channel = 6,
        .valid = true,
        .mux = 0,
    },
    {
        .num = 14,
        .dma_num = 2,
        .channel = 7,
        .valid = true,
        .mux = 0,
    },
};

volatile DmaChannelHandle_t DmaChannelInstance[] = {
    {
        .num = 1,
        .dma_num = 1,
        .channel = 1,
        .valid = true,
    },
    {
        .num = 2,
        .dma_num = 1,
        .channel = 2,
        .valid = true,
    },
    {
        .num = 3,
        .dma_num = 1,
        .channel = 3,
        .valid = true,
    },
    {
        .num = 4,
        .dma_num = 1,
        .channel = 4,
        .valid = true,
    },
    {
        .num = 5,
        .dma_num = 1,
        .channel = 5,
        .valid = true,
    },
    {
        .num = 6,
        .dma_num = 1,
        .channel = 6,
        .valid = true,
    },
    {
        .num = 7,
        .dma_num = 1,
        .channel = 7,
        .valid = true,
    },
    {
        .num = 8,
        .dma_num = 2,
        .channel = 1,
        .valid = true,
    },
    {
        .num = 9,
        .dma_num = 2,
        .channel = 2,
        .valid = true,
    },
    {
        .num = 10,
        .dma_num = 2,
        .channel = 3,
        .valid = true,
    },
    {
        .num = 11,
        .dma_num = 2,
        .channel = 4,
        .valid = true,
    },
    {
        .num = 12,
        .dma_num = 2,
        .channel = 5,
        .valid = true,
    },
    {
        .num = 13,
        .dma_num = 2,
        .channel = 6,
        .valid = true,
    },
    {
        .num = 14,
        .dma_num = 2,
        .channel = 7,
        .valid = true,
    },

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
