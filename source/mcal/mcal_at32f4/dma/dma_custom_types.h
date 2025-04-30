#ifndef DMA_CUSTOM_TYPES_H
#define DMA_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_const.h"
#include "dma_custom_const.h"
#include "microcontroller_types.h"

#define DMA_CUSTOM_TYPES dma_type* DMAx;

typedef struct {
    uint32_t half;
    uint32_t done;
    uint32_t global;
    uint32_t error;
} DmaChannelFlags_t;

typedef struct {
    DmaChannel_t channel;
    uint8_t dma_num;
    bool valid;
    volatile dma_channel_type* dmax_channely;
#ifdef HAS_AT32F43X
    volatile dmamux_channel_type* dmamux_channelx;
#else
    volatile uint32_t* dmamux_channelx;
#endif
    DmaChannelFlags_t Flag;
    IRQn_Type irq_n;
} DmaChannelInfo_t;

typedef struct {
    crm_periph_clock_type clock_type;
    uint8_t num; /*DMA num*/
    volatile dma_type* DMAx;
    bool valid;
} DmaInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* DMA_CUSTOM_TYPES_H  */
