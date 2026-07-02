#include "dma_commands.h"

#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "dma_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "str_utils.h"

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

bool dma_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t dma_num = 1;
    if(0 <= argc) {
        res = true;
        dma_num = 1;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &dma_num);
    }

    if(res) {
        switch(argc) {
        case 0: {
            res = dma_mcal_init();
        } break;
        case 1: {
            res = dma_init_one(dma_num);
        } break;
        default:
            break;
        }
    } else {
        LOG_ERROR(LG_DMA, "Usage: di DmaNum");
    }
    return res;
}

bool dma_stop_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t dma_num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &dma_num);
    }
    if(res) {
        res = dma_stop(dma_num);
    } else {
        LOG_ERROR(LG_DMA, "Usage: ds DmaNum");
    }
    return res;
}

bool dma_start_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t dma_num = 1;
    uint32_t src_address = 0;
    uint32_t dst_address = 0;
    uint32_t bytes = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &dma_num);
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &src_address);
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &dst_address);
    }

    if(4 <= argc) {
        res = try_str2uint32(argv[3], &bytes);
    }

    if(res) {
        res = dma_start(dma_num, src_address, dst_address, bytes);
    } else {
        LOG_ERROR(LG_DMA, "Usage: dt DmaNum SrcAddr dstAddr Size");
    }
    return res;
}
