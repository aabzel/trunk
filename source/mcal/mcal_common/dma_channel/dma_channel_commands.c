#include "dma_channel_commands.h"

#include "convert.h"
#include "dma_channel_mcal.h"
#include "log.h"

bool dma_channel_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool dma_channel_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = dma_channel_diag();
        log_info_res(DMA_CHANNEL, res, "Diag");
    } else {
        LOG_ERROR(DMA_CHANNEL, "Usage: dcd");
    }

    return res;
}

bool dma_channel_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = dma_channel_mcal_init();
        log_info_res(DMA_CHANNEL, res, "ChInit");
    } else {
        LOG_ERROR(DMA_CHANNEL, "Usage: dci");
    }
    return res;
}

bool dma_channel_mux_command(int32_t argc, char* argv[]) {
    bool res = true;
    uint8_t dma_num = 0;
    uint8_t channel = 0;
    uint8_t mux = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &dma_num);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr DmaNum %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &channel);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr Chan %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &mux);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr Mux %s", argv[2]);
        }
    }

    if(res) {
        DmaChannelPad_t DmaPad = {
            .dma_num = dma_num,
            .channel = channel,
        };

        switch(argc) {
        case 2: {
            mux = 0;
            res = dma_channel_mux_get(DmaPad, &mux);
            if(res) {
                LOG_INFO(SYS, "Get,DmaNum:%u,Channel:%u,Mux:%u", dma_num, channel, mux);
            }
        } break;
        case 3: {
            LOG_INFO(SYS, "Set,DmaNum:%u,Channel:%u,Mux:%u", dma_num, channel, mux);
            res = dma_channel_mux_set(DmaPad, mux);
            log_info_res(DMA_CHANNEL, res, "MuxSet");
        } break;
        default:
            break;
        }
    } else {
        LOG_ERROR(SYS, "Usage: dcm DmaNum Channel Mux");
    }
    return res;
}

bool dma_channel_priority_command(int32_t argc, char* argv[]) {
    bool res = true;
    uint8_t dma_num = 0;
    uint8_t channel = 0;
    uint8_t priority = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &dma_num);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr DmaNum %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &channel);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr Chan %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &priority);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr Mux %s", argv[2]);
        }
    }

    if(res) {
        DmaChannelPad_t DmaPad = {
            .dma_num = dma_num,
            .channel = channel,
        };

        switch(argc) {
        case 2: {
            priority = 0;
            res = dma_channel_priority_get(DmaPad, &priority);
            if(res) {
                LOG_INFO(SYS, "Get,DmaNum:%u,Channel:%u,Priority:%u", dma_num, channel, priority);
            }
        } break;
        case 3: {
            LOG_INFO(SYS, "Set,DmaNum:%u,Channel:%u,Priority:%u", dma_num, channel, priority);
            res = dma_channel_priority_set(DmaPad, priority);
            log_info_res(DMA_CHANNEL, res, "PrioritySet");
        } break;
        default:
            break;
        }
    } else {
        LOG_ERROR(SYS, "Usage: dcp DmaNum Channel Priority");
    }
    return res;
}
