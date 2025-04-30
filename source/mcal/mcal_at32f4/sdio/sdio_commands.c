#include "sdio_commands.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "hal_diag.h"
#include "log.h"
#include "sdio_bsp.h"
#include "sdio_diag.h"
#include "sdio_drv.h"
#include "table_utils.h"
#include "writer_config.h"

bool sdio_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t sdio_num = 1;
    if(0 <= argc) {
        res = true;
        sdio_num = 1;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &sdio_num);
        if(false == res) {
            LOG_ERROR(LG_SDIO, "ParseErr SdioNum %s", argv[0]);
        }
    }
    if(res) {
        res = sdio_card_info_get(sdio_num);
        SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
        if(SdioNode) {
            LOG_INFO(LG_SDIO, "Read %u Ok %u Err %u", SdioNode->read_cnt, SdioNode->read_ok_cnt,
                     SdioNode->read_err_cnt);
            LOG_INFO(LG_SDIO, "IntCnt %u", SdioNode->it_cnt);
            LOG_INFO(LG_SDIO, "AbortCnt %u", SdioNode->abort_cnt);
            LOG_INFO(LG_SDIO, "TryWrCnt/WrCnt %u/%u", SdioNode->try_write_cnt, SdioNode->tx_cnt);
            LOG_INFO(LG_SDIO, "TryRdCnt/RdCnt %u/%u", SdioNode->try_read_cnt, SdioNode->rx_cnt);
            LOG_INFO(LG_SDIO, "ErrCnt %u", SdioNode->err_cnt);
            LOG_INFO(LG_SDIO, "State %u %s", SdioNode->sdio_h.State, SdState2Str(SdioNode->sdio_h.State));
            LOG_INFO(LG_SDIO, "SdMmcDataTimeOut %u ms %f s", SDMMC_DATATIMEOUT, MSEC_2_SEC(SDMMC_DATATIMEOUT));
            LOG_INFO(LG_SDIO, "Size %u Byte", (SdioNode->CardInfo.BlockNbr) * (SdioNode->CardInfo.BlockSize));
            LOG_INFO(LG_SDIO, "MemoryCapacity %u Byte", (SdioNode->CSD.DeviceSize + 1) * 512);
            LOG_INFO(LG_SDIO, "cSizeMul %f Byte", pow(2.0, (double)(SdioNode->CSD.DeviceSizeMul + 2)));
        }
    }
    return res;
}

bool sd_card_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t sdio_num = 1;
    if(0 <= argc) {
        res = true;
        sdio_num = 1;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &sdio_num);
        if(false == res) {
            LOG_ERROR(LG_SDIO, "ParseErr SdioNum %s", argv[0]);
        }
    }
    if(res) {
        SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
        if(SdioNode) {
            HAL_StatusTypeDef ret;
            ret = HAL_SD_GetCardStatus(&SdioNode->sdio_h, &SdioNode->status);
            if(HAL_OK == ret) {
                LOG_INFO(LG_SDIO, "%u SD_GetCardStatusOk", sdio_num);
                res = ParseSdCardStatus(&SdioNode->status);
            } else {
                LOG_ERROR(LG_SDIO, "Err %s", HalStatus2Str(ret));
            }
        }

    } else {
        LOG_ERROR(LG_SDIO, "Usage cad");
    }
    return res;
}

bool sdio_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t sdio_num = 1;
    if(0 <= argc) {
        res = true;
        sdio_num = 1;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &sdio_num);
        if(false == res) {
            LOG_ERROR(LG_SDIO, "ParseErr SdioNum %s", argv[0]);
        }
    }
    if(res) {
        res = sdio_card_info_get(sdio_num);
        if(res) {
            SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
            if(SdioNode) {
                res = ParseSdCardCSD(&SdioNode->CSD);
                res = ParseSdCardCID(&SdioNode->CID);
                res = ParseSdCardInfo(&SdioNode->CardInfo);
                LOG_INFO(LG_SDIO, "%u CardState %s", sdio_num, CardState2Str(SdioNode->SD_CardState));
            }
        }
    } else {
        LOG_ERROR(LG_SDIO, "Usage sdd num");
    }
    return res;
}

bool sdio_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t sdio_num = 1;
    if(0 <= argc) {
        sdio_num = 1;
        res = true;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &sdio_num);
        if(false == res) {
            LOG_ERROR(LG_SDIO, "ParseErrindex %s", argv[0]);
        }
    }
    if(res) {
        res = sdio_init_ll(sdio_num);
        if(res) {
            LOG_INFO(LG_SDIO, "%u InitOk", sdio_num);
        } else {
            LOG_ERROR(LG_SDIO, "%u InitErr", sdio_num);
        }
    }
    return res;
}

bool sdio_diag_int_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool sdio_init_card_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t sdio_num = 0;
    if(0 <= argc) {
        res = true;
        sdio_num = 1;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &sdio_num);
        if(false == res) {
            LOG_ERROR(LG_SDIO, "ParseErrindex %s", argv[0]);
        }
    }
    if(res) {
        SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
        if(SdioNode) {
            HAL_StatusTypeDef ret;
            ret = HAL_SD_InitCard(&SdioNode->sdio_h);
            if(HAL_OK == ret) {
                LOG_INFO(LG_SDIO, "InitCardOk", sdio_num);
            } else {
                LOG_ERROR(LG_SDIO, "InitCardErr %s", HalStatus2Str(ret));
            }
        } else {
            LOG_ERROR(LG_SDIO, "NodeErr %u", sdio_num);
        }
    }
    return res;
}

bool sdio_write_command(int32_t argc, char* argv[]) {
    bool res = false;

    return res;
}

bool sdio_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t sdio_num = 1;
    uint32_t number_of_blocks = 1;
    uint32_t block_num = 0;
    uint32_t size = 0;
    if(0 <= argc) {
        res = true;
        sdio_num = 1;
        number_of_blocks = 1;
        block_num = 1;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &sdio_num);
        if(false == res) {
            LOG_ERROR(LG_SDIO, "ParseErrindex %s", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2uint32(argv[1], &block_num);
        if(false == res) {
            LOG_ERROR(LG_SDIO, "ParseErr BlockNum %s", argv[1]);
        }
    }
    if(3 <= argc) {
        res = try_str2uint32(argv[2], &number_of_blocks);
        if(false == res) {
            LOG_ERROR(LG_SDIO, "ParseErr BlockCnt %s", argv[2]);
        }
    }

    if(res) {
        uint8_t* RxData = NULL;
        size = SDIO_BLOCK_SIZE * number_of_blocks + 1;
        RxData = (uint8_t*)malloc(size);
        if(RxData) {
            res = sdio_read_sector(sdio_num, block_num, number_of_blocks, RxData);
            if(res) {
                LOG_INFO(LG_SDIO, "%u ReadBlock %u Ok", sdio_num, block_num);
                res = print_mem(RxData, size, true, true, true, true);
            } else {
                LOG_ERROR(LG_SDIO, "%u ReadBlock %u Err", sdio_num, block_num);
            }

            free(RxData);
        } else {
            LOG_ERROR(LG_SDIO, "MallocErr");
        }
    } else {
        LOG_ERROR(LG_SDIO, "Usage sdr sdio_num block_add number_of_blocks");
    }

    return res;
}

bool sdio_errase_command(int32_t argc, char* argv[]) {
    bool res = false;
    // HAL_StatusTypeDef HAL_SD_Erase(&SdioNode->sdio_h, uint32_t BlockStartAdd, uint32_t BlockEndAdd);
    return res;
}

bool sdio_scan_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t sdio_num = 1;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &sdio_num);
        if(false == res) {
            LOG_ERROR(LG_SDIO, "ParseErrindex %s", argv[0]);
        }
    }
    if(res) {
        res = sdio_scan(sdio_num);
    }
    return res;
}
