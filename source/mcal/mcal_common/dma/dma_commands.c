#include "dma_commands.h"

#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "dma_mcal.h"
#include "log.h"
#include "str_utils.h"
#include "sys_config.h"

bool dma_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = dma_diag();
    } else {
        LOG_ERROR(SYS, "Usage: dd");
    }
    return res;
}

bool dma_channel_diag_command(int32_t argc, char* argv[]) {
    bool res = true;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = dma_channel_diag();
    } else {
        LOG_ERROR(SYS, "Usage: dcd");
    }
    return res;
}

bool dma_channel_mux_command(int32_t argc, char* argv[]) {
    bool res = true;
    uint8_t dma_num = 0;
    uint8_t channel = 0;
    uint8_t dmamux = 0;

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
        res = try_str2uint8(argv[2], &dmamux);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr Mux %s", argv[2]);
        }
    }

    if(res) {
        switch(argc) {
        case 2: {
            dmamux = 0;
            res = dma_mux_get(dma_num, channel, &dmamux);
            if(res) {
                LOG_INFO(SYS, "Get,DmaNum:%u,Channel:%u,Mux:%u", dma_num, channel, dmamux);
            }
        } break;
        case 3: {
            LOG_INFO(SYS, "Set,DmaNum:%u,Channel:%u,Mux:%u", dma_num, channel, dmamux);
            res = dma_mux_set(dma_num, channel, dmamux);
            if(res) {
                LOG_INFO(SYS, "SetOk");
            } else {
                LOG_ERROR(SYS, "SetErr");
            }
        } break;
        }
    } else {
        LOG_ERROR(SYS, "Usage: dcm DmaNum Channel Mux");
    }
    return res;
}
