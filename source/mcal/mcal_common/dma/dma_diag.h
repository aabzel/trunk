#ifndef DMA_DIAG_H
#define DMA_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_types.h"

#ifdef HAS_DMA_COSTOM
#include "dma_custom_diag.h"
#include "dma_custom_types.h"
#endif

bool dma_diag(void);
bool dma_channel_diag(void);


const char* DmaConfigToStr(const DmaConfig_t* const Config);
const char* DmaDirToStr(DmaDir_t dir);
const char* DmaPriorityToStr(const DmaPriority_t priority);
const char* DmaIncrToStr(DmaInc_t code);
const char* DmaModeToStr(DmaMode_t code);
const char* DmaPriorityToStr(DmaPriority_t code);
uint8_t DmaDataSizeToBits(const DmaAligmant_t code);
uint8_t DmaDataSizeBitsToStr(DmaAligmant_t code);

#ifdef __cplusplus
}
#endif

#endif /* DMA_DIAG_H  */
