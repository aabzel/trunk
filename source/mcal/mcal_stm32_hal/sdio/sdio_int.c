#include "sdio_int.h"

#include <string.h>

#include "array_diag.h"
#include "log.h"
#include "sdio_mcal.h"

bool sdio_write_sector_it(uint8_t num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData) {
    LOG_DEBUG(LG_SDIO, "WriteBlockIT,Num:%u,BlkNum:%u,BlkCnt:%u", num, block_num, block_cnt);
    bool res = false;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        res = false;
        HAL_StatusTypeDef ret;
        Node->tx_done = false;
        wait_ms(SDIO_TIME_OUT_MS);
        ret = HAL_SD_WriteBlocks_IT(&Node->Handle, (uint8_t*)TxData, block_num, block_cnt);
        if(HAL_OK == ret) {
            res = SdioWaitTxDoneLl(Node, SDIO_TX_TIME_OUT_MS, num, block_num);
            if(res) {
                LOG_DEBUG(LG_SDIO, "%u WriteBlockIt %u Ok", num, block_num);
            }
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u WriteBlockIt Num:%u Err %s", num, block_num, HalStatusToStr(ret));
#ifdef HAS_SDIO_DIAG
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->Handle.ErrorCode, HalSdioErrCode2Str(Node->Handle.ErrorCode));
#endif
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", num);
    }
    LOG_DEBUG(LG_SDIO, "%u WriteBlockIt Num:%u done", num, block_num);
    return res;
}

bool sdio_read_sector_it(uint8_t num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "ReadBlockIT,Num:%u,BlkNum:%u,BlkCnt:%u", num, block_num, block_cnt);
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        memset(RxData, 0, SDIO_BLOCK_SIZE * block_cnt);
        Node->rx_done = false;
        wait_ms(SDIO_TIME_OUT_MS); /*TODO discard pause*/
        HAL_StatusTypeDef ret;
        ret = HAL_SD_ReadBlocks_IT(&Node->Handle, RxData, block_num, block_cnt);
        if(HAL_OK == ret) {
            res = SdioWaitRxDoneLl(Node, SDIO_RX_TIME_OUT_MS, num, block_num);
            if(res) {
#ifdef HAS_ARRAY_DIAG
                // LOG_DEBUG(LG_SDIO, "%u ReadBlockIT %u Ok", num, block_num);
                log_level_t log_level = log_level_get(LG_SDIO);
                if(LOG_LEVEL_PARANOID == log_level) {
                    res = print_mem(RxData, SDIO_BLOCK_SIZE * block_cnt, true, true, true, true);
                }
#endif
            }
        } else {
            res = false;
            // LOG_ERROR(LG_SDIO, "%u ItReadBlockIT %u Err %s", num, block_num, HalStatusToStr(ret));
#ifdef HAS_SDIO_DIAG
            // LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->Handle.ErrorCode,
            // HalSdioErrCode2Str(Node->Handle.ErrorCode));
#endif
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", num);
    }
    return res;
}
