#ifndef DMA_MCAL_H
#define DMA_MCAL_H

#include <stddef.h>

#include "std_includes.h"
#include "dma_types.h"
#include "dma_config.h"
#include "dma_diag.h"
#include "dma_isr.h"

#ifdef HAS_DMA_CHANNEL
#include "dma_channel_mcal.h"
#endif

#ifdef HAS_DMA_CUSTOM
#include "dma_custom.h"
#endif

//extern const DmaMuxInfo_t DmaMuxlInfo[];


uint32_t MemoryBurst2StmMemoryBurst(uint8_t mem_burst) ;
uint32_t PeriphBurst2StmPeriphBurst(DmaBurst_t periph_burst) ;
uint32_t DmaGetPriority(DmaPriority_t priority) ;
uint32_t DmaGetFiFoNode(const DmaFifo_t fifo);
uint32_t DmaGetMode(DmaMode_t mode) ;
uint32_t DmaGetMemDataAlignment(DmaAligmant_t aligment_mem);
uint32_t DmaGetPeriphInc(uint8_t per_inc) ;
uint32_t DmaGetMemInc(uint8_t mem_inc) ;
uint32_t DmaGetPeriphDataAlignment(DmaAligmant_t aligment_per);
uint32_t DmaGetMemDataAlignment(DmaAligmant_t aligment_mem) ;

/*API DMA*/
DmaHandle_t* DmaGetNode(uint8_t num);
const DmaConfig_t* DmaGetConfig(uint8_t num);
bool DmaIsValidConfig(const DmaConfig_t* const Config);
bool dma_mcal_init(void) ;
bool dma_init_custom(void) ;
bool dma_init_one(uint8_t num) ;

bool dma_proc_one(uint8_t i);


#ifdef HAS_DMA_CUSTOM
const DmaInfo_t* DmaGetInfo(uint8_t num);
#endif


uint32_t DmaGetPeriphDataAlignment(uint8_t aligment_per);
/*API Channels*/

/*getters*/

/*setters*/
bool dma_start(uint8_t num, uint32_t src_address, uint32_t dst_address, uint32_t bytes) ;
bool dma_init_clock(uint8_t num) ;
bool dma_stop(uint8_t num);
bool dma_memcpy(void* const  destination, const  void* const  source, uint32_t n);
//bool dma_mux_set(uint8_t dma_num, DmaChannel_t channel, uint8_t dmamux);


#endif /* DMA_MCAL_H */
