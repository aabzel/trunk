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

const char* DmaPadToStr(DmaPad_t DmaPad);
const char* DmaConfigToStr(const DmaConfig_t* const Config);
const char* DmaChannelConfigToStr(const DmaChannelConfig_t* const Config);
const char* DmaDirToStr(DmaDir_t dir);
const char* DmaIncr2Str(DmaInc_t code);
const char* DmaMode2Str(DmaMode_t code);
const char* DmaPriority2Str(DmaPriority_t code);

uint8_t DmaDataSizeBits2Str(DmaAligmant_t code);
#ifdef __cplusplus
}
#endif

#endif /* DMA_DIAG_H  */
