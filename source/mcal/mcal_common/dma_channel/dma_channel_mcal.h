#ifndef DMA_CHANNEL_MCAL_H
#define DMA_CHANNEL_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_config.h"
#include "dma_channel_isr.h"
#include "dma_channel_types.h"

#ifdef HAS_DMA_CHANNEL_DIAG
#include "dma_channel_diag.h"
#endif

#ifdef HAS_DMA_CHANNEL_CUSTOM
#include "dma_channel_custom.h"
#endif

extern const DmaInfoChannel_t DmaSpareChannels[];

/* API */
bool dma_wait_done(uint8_t num, DmaChannel_t channel);
const DmaChannelInfo_t * DmaChannelGetInfo(uint8_t num, DmaChannel_t channel);
const DmaChannelConfig_t* DmaChannelGetConfig(uint8_t num);
DmaChannelHandle_t* DmaPadGetNodeItem(DmaInfoChannel_t DmaPad);
DmaChannelHandle_t* DmaChannelGetNode(uint8_t num);
DmaChannelHandle_t* DmaChannelToNode(DmaInfoChannel_t DmaPad);
DmaChannelHandle_t* DmaChannelPadGetNode(DmaInfoChannel_t DmaPad);
bool DmaChannelIsValidConfig(const DmaChannelConfig_t* const Config);
#ifdef HAS_DMA_CHANNEL_CUSTOM
const DmaChannelInfo_t* DmaChannelToInfo(DmaInfoChannel_t DmaPad);
#endif

bool dma_channel_mcal_init(void);
bool dma_channel_init_one(uint8_t num);
bool dma_channel_init_custom(void) ;
bool dma_channel_init_one_ll(const DmaChannelConfig_t* const Config);
bool dma_channel_init_common(const DmaChannelConfig_t* const Config,
                             DmaChannelHandle_t* const Node);

DmaChannelHandle_t * DmaChannelGetNodeItem(uint8_t dma_num, DmaChannel_t channel);

bool dma_channel_proc_one(uint8_t num);
bool dma_channel_proc(void);


/*setters*/
bool dma_channel_restart(DmaInfoChannel_t DmaPad, uint16_t data_number) ;

bool dma_memcpy_ll(void* const destination,
                   const void* const source,
                   uint32_t size,
                   uint8_t dma_num,
                   uint8_t stream,
                   uint8_t channel);

bool dma_memcpy_custom_ll(void* const destination, const void* const source,
                          uint32_t size, uint8_t dma_num,
                          uint8_t stream, uint8_t channel);

bool dma_channel_init_interrupts(void) ;
bool dma_channel_control(DmaChannelHandle_t* const Channel, const void* const complete_data) ;
bool dma_channel_mux_set(DmaInfoChannel_t DmaPad, uint8_t dma_mux);
bool dma_channel_priority_set(DmaInfoChannel_t DmaPad, uint8_t priority);
bool dma_channel_start(DmaInfoChannel_t DmaPad);
bool dma_channel_start_ll(DmaChannelHandle_t* Node) ;
bool dma_channel_stop(DmaInfoChannel_t DmaPad);
//bool dma_channel_restart(DmaInfoChannel_t DmaPad);

/*getters*/
uint32_t dma_channel_spare_get_cnt(void);
bool dma_channel_is_valid_num(uint8_t num);
bool dma_mux_set(uint8_t dma_num, DmaChannel_t channel, uint8_t dmamux);
bool dma_channel_priority_get(DmaInfoChannel_t DmaPad, uint8_t* priority);

bool dma_channel_wait_done(DmaInfoChannel_t DmaPad);
bool dma_channel_mux_get(DmaInfoChannel_t DmaPad, uint8_t* const mux);
bool dma_mux_get(uint8_t dma_num, DmaChannel_t channel, uint8_t* const dmamux);
//bool dma_get_spare(DmaStream_t* const DmaStream);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_MCAL_H */
