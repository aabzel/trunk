#ifndef DMA_MCAL_H
#define DMA_MCAL_H

#include <stddef.h>

#include "std_includes.h"
#include "dma_types.h"
#include "dma_config.h"
#include "dma_diag.h"
#include "dma_isr.h"

#ifdef HAS_DMA_CUSTOM
#include "dma_custom.h"
#endif

//extern const DmaMuxInfo_t DmaMuxlInfo[];

/*API DMA*/
DmaHandle_t* DmaGetNode(uint8_t num);
DmaHandle_t* DmaGetNodeByStream(uint8_t dma_num, uint8_t channel);
const DmaConfig_t* DmaGetConfig(uint8_t num);
bool DmaIsValidConfig(const DmaConfig_t* const Config);
bool dma_mcal_init(void) ;
bool dma_init_custom(void) ;
bool dma_init_one(uint8_t num) ;

bool dma_proc_one(uint8_t i);


#ifdef HAS_DMA_CUSTOM
const DmaInfo_t* DmaGetInfo(uint8_t num);
#endif

/*getters*/

/*setters*/
bool dma_init_clock(uint8_t num) ;
bool dma_stop(uint8_t num);
bool dma_memcpy(void* const  destination, const  void* const  source, uint32_t n);


#endif /* DMA_MCAL_H */
