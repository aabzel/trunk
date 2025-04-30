#ifndef DMA_MCAL_H
#define DMA_MCAL_H

#include <stddef.h>

#include "std_includes.h"
#include "dma_types.h"
#include "dma_config.h"
#include "dma_diag.h"
#include "dma_isr.h"
#ifdef HAS_DMA_COSTOM
#include "dma_custom_drv.h"
#endif

extern const DmaMuxInfo_t DmaMuxlInfo[];

/*API DMA*/
bool dma_mcal_init(void) ;
bool dma_init_custom(void) ;
bool dma_init_one(uint8_t num) ;
bool dma_wait_done(uint8_t num, DmaChannel_t channel);

#ifdef HAS_DMA_COSTOM
const DmaInfo_t* DmaGetInfo(uint8_t num);
const DmaChannelInfo_t * DmaChannelGetInfo(uint8_t num, DmaChannel_t channel);
#endif
DmaHandle_t* DmaGetNode(uint8_t num);
const DmaConfig_t* DmaGetConfig(uint8_t num);

/*API Channels*/
bool dma_channel_mcal_init(void) ;
bool dma_channel_init_custom(void) ;
bool dma_channel_init_common_one(DmaChannelConfig_t* Config, DmaChannelHandle_t* Node);
bool dma_channel_init_one(uint8_t num) ;
bool dma_channel_stop(DmaPad_t DmaPad) ;
bool dma_channel_init_one_ll(const DmaChannelConfig_t* const Config);
DmaChannelHandle_t* DmaPadGetNodeItem(DmaPad_t DmaPad);
DmaChannelHandle_t* DmaChannelGetNode(uint8_t num);
const DmaChannelConfig_t* DmaChannelGetConfig(uint8_t num);
DmaChannelHandle_t * DmaChannelGetNodeItem(uint8_t dma_num, DmaChannel_t channel);

/*getters*/
bool dma_mux_get(uint8_t dma_num, DmaChannel_t channel, uint8_t* const dmamux);
bool dma_get_spare(DmaStream_t* const DmaStream);

/*setters*/
//bool dma_stop(uint8_t num);
bool dma_channel_restart(DmaPad_t DmaPad, uint16_t data_number) ;
bool dma_memcpy(void* const  destination, const  void* const  source, size_t n);
bool dma_mux_set(uint8_t dma_num, DmaChannel_t channel, uint8_t dmamux);

#endif /* DMA_MCAL_H */
