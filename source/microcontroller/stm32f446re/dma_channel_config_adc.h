#ifndef DMA_CHANNEL_CONFIG_ADC_H
#define DMA_CHANNEL_CONFIG_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"
#include "macro_utils.h"
#include "adc_config.h"

bool CallBackHalfAdc1(void);
bool CallBackDoneAdc1(void);

/*
  Table 43. DMA2 request mapping
 */
#define DMA_CHANNEL_ADC1                               \
    {                                                  \
        .num = DMA_CHANNEL_NUM_ADC1,                   \
        .DmaPad = {.dma_num = 2, .channel = 0},        \
        .name = "adc1",                                \
        .dir = DMA_MCAL_DIR_PERIPH_TO_MEMORY,          \
        .CallBackHalf = CallBackHalfAdc1,              \
        .CallBackDone = CallBackDoneAdc1,              \
        .mem_inc = DMA_INC_ON,                         \
        .per_inc = DMA_INC_OFF,                        \
        .valid = true,                                 \
        .aligment_mem = DMA_ALIGNMENT_WORD,            \
        .aligment_per = DMA_ALIGNMENT_WORD,            \
        .mode = DMA_MODE_CIRCULAR,                     \
        .interrupt_on = true,                          \
        .priority = DMA_PRIOR_MED,                     \
        .base_addr_source = (uint32_t) &(ADC1->DR),    \
        .base_addr_destination = (uint32_t) Adc1RxSamples, \
        .move_size = (uint32_t) ADC1_RX_SAMPLE_CNT,    \
        .block_size = (uint32_t) DMA_MEMCPY_SIZE,      \
        .block_count = 1,                              \
        .fifo = DMA_FIFO_OFF,                          \
        .memory_burst = DMA_BURST_SINGLE,              \
        .periph_burst = DMA_BURST_SINGLE,              \
    },

#define DMA_CHANNEL_ADC                              \
        DMA_CHANNEL_ADC1

#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_CONFIG_ADC_H  */
