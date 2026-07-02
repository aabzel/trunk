#ifndef DMA_CHANNEL_CONFIG_MEMCPY_H
#define DMA_CHANNEL_CONFIG_MEMCPY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"

#define DMA_MEMCPY_SIZE 50
extern uint8_t toArray[DMA_MEMCPY_SIZE];
extern uint8_t fromArray[DMA_MEMCPY_SIZE];

bool CallBackHalfMemCpy(void);
bool CallBackDoneMemCpy(void);

//Table 42. DMA1 request mapping
#define DMA_CHANNEL_MEMCPY_COMMON             \
 .per_inc = DMA_INC_ON,                       \
 .mem_inc = DMA_INC_ON,                       \
 .mux = 0,                                    \
 .block_count =1,                             \
 .memory_burst = DMA_BURST_SINGLE,            \
 .dir = DMA_MCAL_DIR_MEMORY_TO_MEMORY,        \
 .fifo = DMA_FIFO_OFF,                        \
 .periph_burst = DMA_BURST_SINGLE,            \
 .aligment_mem = DMA_ALIGNMENT_BYTE,          \
 .aligment_per = DMA_ALIGNMENT_BYTE,          \
 .priority = 10,                              \
 .interrupt_on = true,                        \
 .CallBackHalf= CallBackHalfMemCpy,           \
 .CallBackDone= CallBackDoneMemCpy,           \
 .base_addr_source = (uint32_t)fromArray,     \
 .base_addr_destination = (uint32_t)toArray,  \
 .mode = DMA_MODE_NORMAL,                     \
 .valid = true,

#define DMA_CHANNEL_MEMCPY1                                     \
    {                                                           \
       .num = DMA_CHANNEL_NUM_MEMCPY1,                          \
       .name = "MemCpy",                                        \
       .DmaChPad={.dma_num = 1, .stream = 6, .channel=0, },     \
        DMA_CHANNEL_MEMCPY_COMMON                               \
    },


#define DMA_CHANNEL_MEMCPY2                              \
    {                                                    \
        .num = DMA_CHANNEL_NUM_MEMCPY2,                         \
        .DmaChPad={.dma_num = 1, .stream = 1, .channel=0,},     \
        .name = "MemCpy",                                       \
         DMA_CHANNEL_MEMCPY_COMMON                               \
    },


#define DMA_CHANNEL_MEMCPY  \
    DMA_CHANNEL_MEMCPY1     \
    DMA_CHANNEL_MEMCPY2



#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_CONFIG_MEMCPY_H  */
