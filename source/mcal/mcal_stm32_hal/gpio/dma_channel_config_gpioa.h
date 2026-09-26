#ifndef DMA_CHANNEL_PORT_A_CONFIG_H
#define DMA_CHANNEL_PORT_A_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"

#define GPIO_SAMPLE_SIZE 100

extern uint16_t PortAtoArray[GPIO_SAMPLE_SIZE];

bool CallBackDonePortARx(void);
bool CallBackHalfPortARx(void);

bool CallBackDonePortATx(void);
bool CallBackHalfPortATx(void);


#define DMA_CHANNEL_PORT_COMMON                     \
        .memory_burst = DMA_BURST_SINGLE,           \
        .periph_burst = DMA_BURST_SINGLE,           \
        .interrupt_on = true,                       \
        .block_count = 1,                           \
        .valid = true,                              \
        .fifo = DMA_FIFO_OFF,                       \
        .priority = DMA_PRIOR_VERY_HIGH,


#define DMA_CHANNEL_PORT_A_RX                                 \
    {                                                         \
        .num = DMA_CHANNEL_NUM_GPIOA_RX,                      \
        .mode = DMA_MODE_CIRCULAR,                            \
        .DmaChPad = { .dma_num = 2, .stream = 1, .channel = 7,  .name = "PortArx", },      \
        DMA_CHANNEL_PORT_COMMON                               \
        .aligment_per = DMA_ALIGNMENT_WORD,                   \
        .aligment_mem = DMA_ALIGNMENT_WORD,                   \
        .per_inc = DMA_INC_OFF,                               \
        .mem_inc = DMA_INC_ON,                                \
        .dir = DMA_MCAL_DIR_PERIPH_TO_MEMORY,                 \
        .name = "PORTA_RX",                                   \
        .base_addr_source = (uint32_t)  &(GPIOA->IDR),        \
        .base_addr_destination = (uint32_t) PortAtoArray,     \
        .block_size = (uint32_t) GPIO_SAMPLE_SIZE,            \
        .CallBackHalf = CallBackHalfPortARx,                  \
        .CallBackDone = CallBackDonePortARx,                  \
    },

#define DMA_CHANNEL_PORT_A_TX                                 \
    {                                                         \
        DMA_CHANNEL_PORT_COMMON                               \
        .mode = DMA_MODE_NORMAL,                    \
        .base_addr_source = (uint32_t) PortAtoArray,          \
        .base_addr_destination = (uint32_t)  &(GPIOA->BSRR),  \
        .aligment_mem = DMA_ALIGNMENT_DWORD,                  \
        .aligment_per = DMA_ALIGNMENT_DWORD,                  \
        .mem_inc = DMA_INC_ON,                                \
        .per_inc = DMA_INC_OFF,                               \
        .DmaChPad = { .dma_num = 2, .stream = 5, .channel = 6,  .name = "PortAtx", },      \
        .num = DMA_CHANNEL_NUM_GPIOA_TX,                      \
        .dir = DMA_MCAL_DIR_MEMORY_TO_PERIPH,                 \
        .name = "PORTA_TX",                                   \
        .block_size = (uint32_t) GPIO_SAMPLE_SIZE,            \
        .CallBackHalf = CallBackHalfPortATx,                  \
        .CallBackDone = CallBackDonePortATx,                  \
    },


#define DMA_CHANNEL_PORT_A         \
        DMA_CHANNEL_PORT_A_RX      \
        DMA_CHANNEL_PORT_A_TX



#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_PORT_A_CONFIG_H  */
