#include "dma_channel_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "dma_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "std_includes.h"
#include "time_mcal.h"
#include "dma_const.h"

COMPONENT_GET_NODE(DmaChannel, dma_channel)
COMPONENT_GET_CONFIG(DmaChannel, dma_channel)

#ifdef HAS_DMA_CHANNEL_CUSTOM

#endif

_WEAK_FUN_
bool dma_channel_start_ll(DmaChannelHandle_t* Node) { return false; }

_WEAK_FUN_
bool dma_channel_control(DmaChannelHandle_t* const Channel, const void* const complete_data) { return false; }

/*
 ISO-26262 require verify configuration
 */
_WEAK_FUN_
bool DmaChannelIsValidConfig(const DmaChannelConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;

        if(Config->mux) {
        } else {
#ifdef HAS_DMA_CHANNEL_DIAG
            // res = false;
            LOG_WARNING(DMA_CHANNEL, "%s,Mux,Err", DmaPadToStr(Config->DmaPad), Config->mux);
#endif
        }

        if(Config->name) {
        } else {
            res = false;
            LOG_ERROR(DMA_CHANNEL, "%u,NameErr", Config->num);
        }

        if(Config->CallBackHalf) {
        } else {
            res = false;
            LOG_ERROR(DMA_CHANNEL, "%u,CallBackHalf,Err", Config->CallBackHalf);
        }

        if(Config->CallBackDone) {
        } else {
            res = false;
            LOG_ERROR(DMA_CHANNEL, "%u,CallBackDone,Err", Config->CallBackDone);
        }
#if 0
        if(Config->CallBackError) {
        } else {
            res = false;
            LOG_ERROR(DMA_CHANNEL, "%u,CallBackError,Err", Config->CallBackError);
        }
#endif

        if(Config->aligment_source) {
        } else {
            res = false;
            LOG_ERROR(DMA_CHANNEL, "%u,Aligment_source,Err", Config->aligment_source);
        }

        if(Config->aligment_destination) {
        } else {
            res = false;
            LOG_ERROR(DMA_CHANNEL, "%u,Aligment_destination,Err", Config->aligment_destination);
        }

        if(Config->dir) {
        } else {
            res = false;
            LOG_ERROR(DMA_CHANNEL, "%u,dir,Err", Config->dir);
        }

        if(Config->inc_destination) {
        } else {
            res = false;
            LOG_ERROR(DMA_CHANNEL, "%u,IncDest,Err", Config->inc_destination);
        }

        if(Config->inc_source) {
        } else {
            res = false;
            LOG_ERROR(DMA_CHANNEL, "%u,IncSrc,Err", Config->inc_source);
        }

        if(Config->priority) {
        } else {
            res = false;
            LOG_ERROR(DMA_CHANNEL, "%u,priority,Err", Config->priority);
        }

        if(Config->fifo) {
        } else {
            res = false;
            LOG_ERROR(DMA_CHANNEL, "%u,fifo,Err", Config->fifo);
        }

        if(Config->mode) {
        } else {
            res = false;
            LOG_ERROR(DMA_CHANNEL, "%u,mode,Err", Config->mode);
        }
    }
    return res;
}

static bool MemCpyDone(void) {
    bool res = true;
    return res;
}

static bool MemCpyHalf(void) {
    bool res = true;
    return res;
}

#ifdef HAS_DMA_CUSTOM
static void MemCpyTransferCompleteNotify(void* arg) {}
#endif

bool dma_memcpy_ll(void* const destination, const void* const source, size_t size, uint8_t dma_num, uint8_t channel

) {
    bool res = false;
    if(destination) {
        if(source) {
            if(size) {
                LOG_DEBUG(DMA_CHANNEL, "%08p->%08p,%u byte", destination, source, size);
                res = true;
            }
        }
    }

    if(res) {
        res = false;
        static DmaChannelHandle_t Channel = {0};
        Channel.DmaPad.dma_num = dma_num;
        Channel.DmaPad.channel = channel;
        Channel.priority = channel;
        Channel.base_addr_destination = (uint32_t)destination;
        Channel.base_addr_source = (uint32_t)source;
        Channel.block_size = size;
        Channel.block_count = 1;
        Channel.aligment_source = DMA_ALIGNMENT_BYTE;
        Channel.interrupt_on = true;
        Channel.aligment_destination = DMA_ALIGNMENT_BYTE;
        Channel.dir = DMA_MCAL_DIR_MEMORY_TO_MEMORY;
        Channel.inc_destination = DMA_INC_ON;
        Channel.inc_source = DMA_INC_ON;
        Channel.mode = DMA_MODE_NORMAL;
        Channel.mux = 0;
        Channel.fifo = DMA_FIFO_OFF;
        Channel.interrupt_on = false;
        Channel.CallBackHalf = MemCpyHalf;
        Channel.CallBackDone = MemCpyDone;
#ifdef HAS_DMA_CUSTOM
        Channel.pTransferCompleteNotify = MemCpyTransferCompleteNotify;
        Channel.pTransferErrorNotify = NULL;
#endif

        res = dma_channel_control(&Channel, (void*)source);
        if(res) {
            res = dma_channel_start_ll(&Channel);
        }
    }
    return res;
}

_WEAK_FUN_
bool dma_channel_init_custom(void) {
    bool res = false;
    LOG_INFO(DMA_CHANNEL, "Version:%s", DMA_CHANNEL_VERSION);
    return res;
}

_WEAK_FUN_
bool dma_channel_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(DMA_CHANNEL, "Proc:%u", i);
    DmaChannelHandle_t* Node = DmaChannelGetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

_WEAK_FUN_
bool dma_channel_init_common(const DmaChannelConfig_t* const Config, DmaChannelHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            // Node->CallBackError = Config->CallBackError;
            Node->aligment_destination = Config->aligment_destination;
            Node->aligment_source = Config->aligment_source;
            Node->base_addr_source = Config->base_addr_source;
            Node->base_addr_destination = Config->base_addr_destination;
            Node->block_count = Config->block_count;
            Node->block_size = Config->block_size;
            Node->CallBackHalf = Config->CallBackHalf;
            Node->CallBackDone = Config->CallBackDone;
            Node->dir = Config->dir;
            Node->DmaPad.byte = Config->DmaPad.byte;
            Node->fifo = Config->fifo;
            Node->inc_destination = Config->inc_destination;
            Node->inc_source = Config->inc_source;
            Node->interrupt_on = Config->interrupt_on;
            Node->num = Config->num;
            Node->name = Config->name;
            Node->mux = Config->mux;
            Node->mode = Config->mode;
            Node->memory_burst = Config->memory_burst;
            Node->priority = Config->priority;
            Node->periph_burst = Config->periph_burst;

            Node->busy = false;
            Node->global_done = false;
            Node->half = false;
            Node->done = false;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

DmaChannelHandle_t* DmaChannelToNode(DmaChannelPad_t DmaPad) {
    DmaChannelHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = dma_channel_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(DmaChannelInstance[i].valid) {
            if(DmaPad.byte == DmaChannelInstance[i].DmaPad.byte) {
                Node = &DmaChannelInstance[i];
                break;
            }
        }
    }

    return Node;
}

DmaChannelHandle_t* DmaChannelPadGetNode(DmaChannelPad_t DmaPad) {
    DmaChannelHandle_t* Node = NULL;
    Node = DmaChannelToNode(DmaPad);
    return Node;
}
bool dma_channel_wait_done(DmaChannelPad_t DmaPad) {
    bool res = false;
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        bool loop = true;
#ifdef HAS_DMA_CHANNEL_TIME_OUT
        uint32_t cur_ms = 0;
        uint32_t diff_ms = 0;
        uint32_t start_ms = time_get_ms32();
#endif
        while(loop) {
            if(Node->done) {
                res = true;
                loop = false;
            }
#ifdef HAS_DMA_CHANNEL_TIME_OUT
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
            if(DMA_CHANNEL_TRANSFER_TIMEOUT_MS < diff_ms) {
                loop = false;
                res = false;
                LOG_ERROR(DMA_CHANNEL, "DmaTxTimeOut");
            }
            wait_us(100);
#endif
        }
    }
    return res;
}

_WEAK_FUN_ bool dma_channel_mux_get(DmaChannelPad_t DmaPad, uint8_t* const mux) {
    LOG_ERROR(DMA_CHANNEL, "%s NotInplemented", __FUNCTION__);
    return false;
}

_WEAK_FUN_ bool dma_channel_mux_set(DmaChannelPad_t DmaPad, uint8_t mux) {
    LOG_ERROR(DMA_CHANNEL, "%s NotInplemented", __FUNCTION__);
    return false;
}

_WEAK_FUN_
bool dma_channel_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(DMA_CHANNEL, "DMA_CHANNEL%u", num);
    const DmaChannelConfig_t* Config = DmaChannelGetConfig(num);
    if(Config) {
        res = DmaChannelIsValidConfig(Config);
        if(res) {
#ifdef HAS_DMA_CHANNEL_DIAG
            LOG_WARNING(DMA_CHANNEL, "%s", DmaChannelConfigToStr(Config));
#endif
            DmaChannelHandle_t* Node = DmaChannelGetNode(num);
            if(Node) {
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(DMA_CHANNEL, "NodeErr:%u", num);
            }
        } else {
            LOG_ERROR(DMA_CHANNEL, "ConfigErr:%u", num);
        }
    } else {
        LOG_PARN(DMA_CHANNEL, "ConfigErr:%u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT_CNT(DMA_CHANNEL, DMA_CHANNEL, dma_channel, DMA_CHANNEL_COUNT)
COMPONENT_PROC_PATTERT_CNT(DMA_CHANNEL, DMA_CHANNEL, dma_channel, DMA_CHANNEL_COUNT)
