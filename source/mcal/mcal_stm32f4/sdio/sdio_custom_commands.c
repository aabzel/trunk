#include <inttypes.h>
#include <math.h>
#include <mcal/mcal_stm32f4/sdio/sdio_custom_commands.h>
#include <mcal/mcal_stm32f4/sdio/sdio_custom_diag.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "hal_diag.h"
#include "log.h"
#include "sdio_custom.h"
#include "sdio_mcal.h"
#include "table_utils.h"
#include "writer_config.h"

bool sdio_custom_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 <= argc) {
        res = true;
        num = 1;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LG_SDIO, res, "Num");
    }
    if(res) {
        res = sdio_card_info_get(num);
        SdioHandle_t* Node = SdioGetNode(num);
        if(Node) {
            LOG_INFO(LG_SDIO, "Read %u Ok %u Err %u", Node->read_cnt, Node->read_ok_cnt, Node->read_err_cnt);
            LOG_INFO(LG_SDIO, "IntCnt %u", Node->it_cnt);
            LOG_INFO(LG_SDIO, "AbortCnt %u", Node->abort_cnt);
            LOG_INFO(LG_SDIO, "TryWrCnt/WrCnt %u/%u", Node->try_write_cnt, Node->tx_cnt);
            LOG_INFO(LG_SDIO, "TryRdCnt/RdCnt %u/%u", Node->try_read_cnt, Node->rx_cnt);
            LOG_INFO(LG_SDIO, "ErrCnt %u", Node->err_cnt);
            LOG_INFO(LG_SDIO, "State %u %s", Node->Handle.State, SdState2Str(Node->Handle.State));
            LOG_INFO(LG_SDIO, "SdMmcDataTimeOut %u ms %f s", SDMMC_DATATIMEOUT, MSEC_2_SEC(SDMMC_DATATIMEOUT));
            LOG_INFO(LG_SDIO, "Size %u Byte", (Node->CardInfo.BlockNbr) * (Node->CardInfo.BlockSize));
            LOG_INFO(LG_SDIO, "MemoryCapacity %u Byte", (Node->CSD.DeviceSize + 1) * 512);
            LOG_INFO(LG_SDIO, "cSizeMul %f Byte", pow(2.0, (double)(Node->CSD.DeviceSizeMul + 2)));
        }
    }
    return res;
}

bool sd_card_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 <= argc) {
        res = true;
        num = 1;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LG_SDIO, res, "Num");
    }
    if(res) {
        SdioHandle_t* Node = SdioGetNode(num);
        if(Node) {
            HAL_StatusTypeDef ret;
            ret = HAL_SD_GetCardStatus(&Node->Handle, &Node->status);
            if(HAL_OK == ret) {
                LOG_INFO(LG_SDIO, "%u SD_GetCardStatusOk", num);
                res = ParseSdCardStatus(&Node->status);
            } else {
                LOG_ERROR(LG_SDIO, "Err %s", HalStatusToStr(ret));
            }
        }

    } else {
        LOG_ERROR(LG_SDIO, "Usage cad");
    }
    return res;
}

bool sdio_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 <= argc) {
        res = true;
        num = 1;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LG_SDIO, res, "Num");
    }
    if(res) {
        res = sdio_card_info_get(num);
        if(res) {
            SdioHandle_t* Node = SdioGetNode(num);
            if(Node) {
                res = ParseSdCardCSD(&Node->CSD);
                res = ParseSdCardCID(&Node->CID);
                res = ParseSdCardInfo(&Node->CardInfo);
                LOG_INFO(LG_SDIO, "%u CardState %s", num, CardState2Str(Node->SD_CardState));
            }
        }
    } else {
        LOG_ERROR(LG_SDIO, "Usage sdd num");
    }
    return res;
}

bool sdio_custom_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 <= argc) {
        num = 1;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LG_SDIO, res, "Num");
    }
    if(res) {
        res = sdio_init_one(num);
        log_info_res(LG_SDIO, res, "InitOne");
    }
    return res;
}

bool sdio_diag_int_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool sdio_init_card_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(0 <= argc) {
        res = true;
        num = 1;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LG_SDIO, res, "Num");
    }
    if(res) {
        SdioHandle_t* Node = SdioGetNode(num);
        if(Node) {
            HAL_StatusTypeDef ret;
            ret = HAL_SD_InitCard(&Node->Handle);
            if(HAL_OK == ret) {
                LOG_INFO(LG_SDIO, "InitCardOk", num);
            } else {
                LOG_ERROR(LG_SDIO, "InitCardErr %s", HalStatusToStr(ret));
            }
        } else {
            LOG_ERROR(LG_SDIO, "NodeErr %u", num);
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
    uint8_t num = 1;
    uint32_t number_of_blocks = 1;
    uint32_t block_num = 0;
    uint32_t size = 0;
    if(0 <= argc) {
        res = true;
        num = 1;
        number_of_blocks = 1;
        block_num = 1;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LG_SDIO, res, "Num");
    }
    if(2 <= argc) {
        res = try_str2uint32(argv[1], &block_num);
        log_info_res(LG_SDIO, res, "BlkNum");
    }
    if(3 <= argc) {
        res = try_str2uint32(argv[2], &number_of_blocks);
        log_info_res(LG_SDIO, res, "BlkCnt");
    }

    if(res) {
        uint8_t* RxData = NULL;
        size = SDIO_BLOCK_SIZE * number_of_blocks + 1;
        RxData = (uint8_t*)malloc(size);
        if(RxData) {
            res = sdio_read_sector(num, block_num, number_of_blocks, RxData);
            if(res) {
                LOG_INFO(LG_SDIO, "%u ReadBlock %u Ok", num, block_num);
                res = print_mem(RxData, size, true, true, true, true);
            } else {
                LOG_ERROR(LG_SDIO, "%u ReadBlock %u Err", num, block_num);
            }

            free(RxData);
        } else {
            LOG_ERROR(LG_SDIO, "MallocErr");
        }
    } else {
        LOG_ERROR(LG_SDIO, "Usage sdr num block_add number_of_blocks");
    }

    return res;
}

bool sdio_errase_command(int32_t argc, char* argv[]) {
    bool res = false;
    // HAL_StatusTypeDef HAL_SD_Erase(&Node->Handle, uint32_t BlockStartAdd, uint32_t BlockEndAdd);
    return res;
}

bool sdio_scan_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LG_SDIO, res, "Num");
    }
    if(res) {
        res = sdio_scan(num);
        log_info_res(LG_SDIO, res, "Scan");
    }
    return res;
}
