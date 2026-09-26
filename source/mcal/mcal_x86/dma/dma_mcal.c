#include "dma_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "code_generator.h"
#include "data_utils.h"
#include "dma_custom_drv.h"
#include "dma_custom_types.h"
#include "hal_diag.h"
#include "log.h"
#include "time_mcal.h"
#include "x86x.h"

const DmaMuxInfo_t DmaMuxlInfo[] = {0};

const DmaMuxInfo_t* DmaMuxToInfo(uint8_t mux) {
    DmaMuxInfo_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(DmaMuxlInfo);
    for(i = 0; i < cnt; i++) {
        if(mux == DmaMuxlInfo[i].mux) {
            if(DmaMuxlInfo[i].valid) {
                Node = &DmaMuxlInfo[i];
            }
        }
    }
    return Node;
}

bool dma_init_custom(void) {
    bool res = true;
    log_level_get_set(DMA, LOG_LEVEL_INFO);

    uint32_t cnt = dma_get_cnt();
    if(0 == cnt) {
        LOG_WARNING(DMA, "NoConfig");
    }

    return res;
}

const DmaChannelInfo_t* DmaChannelGetInfo(uint8_t num, DmaChannel_t channel) {
    DmaChannelInfo_t* Info = NULL;
    return Info;
}

bool dma_init_one(uint8_t num) {
    bool res = false;
    const DmaConfig_t* Config = DmaGetConfig(num);
    if(Config) {
#ifdef HAS_DMA_DIAG
        LOG_WARNING(DMA, "%s", DmaConfigToStr(Config));
#endif
        DmaHandle_t* Node = DmaGetNode(num);
        if(Node) {
            res = true;
        }
    }

    uint32_t cnt = dma_get_cnt();
    if(0 == cnt) {
        res = true;
    }

    return res;
}

bool dma_channel_init_custom(void) {
    bool res = true;

    uint32_t cnt = dma_channel_get_cnt();
    if(0 == cnt) {
        LOG_WARNING(DMA, "NoChanConfigs");
    }

    return res;
}

static bool dma_mux_set_ll(DmaChannelInfo_t* ChannelInfo, uint8_t dma_mux) {
    bool res = false;
    if(ChannelInfo) {
#ifdef HAS_X86
        dmamux_requst_id_sel_type dmamux_code = dma_mux;
        // LOG_DEBUG(DMA, "DMA%u,CH%u,MUX:%u=%s", ChannelInfo->dma_num, ChannelInfo->channel, dma_mux,
        //            DmaReqSelToStr(dma_mux));
        dmamux_init(ChannelInfo->dmamux_channelx, dmamux_code);
        res = true;
#endif // HAS_X86
    }

    return res;
}

bool dma_mux_get(uint8_t dma_num, DmaChannel_t channel, uint8_t* const dma_mux) {
    bool res = false;
    DmaChannelInfo_t* ChannelInfo = DmaChannelGetInfo(dma_num, channel);
    if(ChannelInfo) {
        if(dma_mux) {
#ifdef HAS_X86
            *dma_mux = ChannelInfo->dmamux_channelx->muxctrl_bit.reqsel;
            LOG_PARN(DMA, "DMA%u,CH%u,MUX:%u=%s", dma_num, channel, *dma_mux, DmaReqSelToStr(*dma_mux));
            res = true;
#endif // HAS_X86
        }
    }
    return res;
}

bool dma_mux_set(uint8_t dma_num, DmaChannel_t channel, uint8_t dma_mux) {
    bool res = false;
    const DmaChannelInfo_t* ChannelInfo = DmaChannelGetInfo(dma_num, channel);
    if(ChannelInfo) {
        res = dma_mux_set_ll(ChannelInfo, dma_mux);
        res = false;
    }

    return res;
}

bool dma_get_spare(DmaStream_t* const DmaStream) {
    bool res = false;
    uint8_t dma_num = 0;
    for(dma_num = 0; dma_num <= DMA_COUNT; dma_num++) {
        uint8_t channel = 0;
        for(channel = DMA_CHAN_0; channel < DMA_CHAN_15; channel++) {
            DmaChannelHandle_t* ChannelNode = DmaChannelGetNodeItem(dma_num, channel);
            if(ChannelNode) {
                if(false == ChannelNode->busy) {
                    DmaStream->dma_num = dma_num;
                    DmaStream->channel = channel;
                    res = true;
                }
            }
        }
    }
    return res;
}

bool dma_channel_stop(DmaPad_t DmaPad) {
    bool res = false;
    const DmaChannelInfo_t* ChannelInfo = DmaChannelGetInfo(DmaPad.dma_num, DmaPad.channel);
    if(ChannelInfo) {
        res = true;
    }
    return res;
}

bool dma_channel_restart(DmaPad_t DmaPad, uint16_t data_number) {
    bool res = false;
    const DmaChannelInfo_t* ChannelInfo = DmaChannelGetInfo(DmaPad.dma_num, DmaPad.channel);
    if(ChannelInfo) {
    }
    return res;
}

bool dma_channel_init_one_ll(const DmaChannelConfig_t* const Config) {
    bool res = false;
    if(Config) {
        DmaChannelHandle_t* Node = DmaChannelGetNode(Config->num);
        if(Node) {
            res = dma_channel_init_common_one(Config, Node);
#if 0
            const DmaChannelInfo_t* ChannelInfo = DmaChannelGetInfo(Config->dma_num, Config->channel);
            if(ChannelInfo) {
            	res = true;
            } else {
                res = false;
            }
            res = true;
#endif
        } else {
            res = false;
        }
    } else {
        res = false;
    }

    uint32_t cnt = dma_channel_get_cnt();
    if(0 == cnt) {
        res = true;
    }
    return res;
}

bool dma_channel_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(DMA, "ChanInit:%u", num);
    const DmaChannelConfig_t* Config = DmaChannelGetConfig(num);
    if(Config) {
        res = dma_channel_init_one_ll(Config);
    } else {
        LOG_ERROR(DMA, "%u,ConfigErr", num);
    }

    uint32_t cnt = dma_channel_get_cnt();
    if(0 == cnt) {
        res = true;
    }
    return res;
}

bool dma_memcpy(void* const destination, const void* const source, size_t size) {
    bool res = false;
    if(destination) {
        if(source) {
            if(size) {
                res = true;
            }
        }
    }

    if(res) {
        DmaChannelHandle_t* Node = DmaChannelGetNodeItem(1, 1);
        if(Node) {
            Node->done = false;
        }
    }
    return res;
}
