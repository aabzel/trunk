#include "sdio_poll.h"

#include <string.h>

#include "array_diag.h"
#include "log.h"
#include "sdio_mcal.h"
#include "time_mcal.h"

bool sdio_write_sector_time_out(uint8_t num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData) {
    LOG_DEBUG(LG_SDIO, "WriteBlockTimeOut,Num:%u,BlkNum:%u,BlkCnt:%u", num, block_num, block_cnt);
    bool res = false;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        res = false;
        HAL_StatusTypeDef ret;
        ret = HAL_SD_WriteBlocks(&Node->Handle, (uint8_t*)TxData, block_num, block_cnt, SDIO_TX_TIME_OUT_MS);
        if(HAL_OK == ret) {
            LOG_DEBUG(LG_SDIO, "SDIO%u,WriteBlockTo %u Ok", num, block_num);
            res = true;
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "SDIO%u,PollWriteBlock,Num:%u,Err:%s", num, block_num, HalStatusToStr(ret));
#ifdef HAS_SDIO_DIAG
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->Handle.ErrorCode, HalSdioErrCode2Str(Node->Handle.ErrorCode));
#endif
        }
    } else {
        LOG_ERROR(LG_SDIO, "SDIO%u,NodeErr %s", num);
    }
    LOG_DEBUG(LG_SDIO, "SDIO%u,WriteBlockTo Num:%u done", num, block_num);
    return res;
}

bool sdio_read_sector_time_out(uint8_t num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "ReadBlockTimeOut,Num:%u,BlkNum:%u,BlkCnt:%u", num, block_num, block_cnt);
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        memset(RxData, 0, SDIO_BLOCK_SIZE * block_cnt);
        HAL_StatusTypeDef ret;
        ret = HAL_SD_ReadBlocks(&Node->Handle, RxData, block_num, block_cnt, SDIO_RX_TIME_OUT_MS);
        if(HAL_OK == ret) {
#ifdef HAS_ARRAY_DIAG
            LOG_DEBUG(LG_SDIO, "SDIO%u,ReadBlockTo %u Ok", num, block_num);
            log_level_t log_level = log_level_get(LG_SDIO);
            if(LOG_LEVEL_PARANOID == log_level) {
                res = print_mem(RxData, SDIO_BLOCK_SIZE * block_cnt, true, true, true, true);
            }
            res = true;
#endif
        } else {
            res = false;
#ifdef HAS_SDIO_DIAG
            LOG_ERROR(LG_SDIO, "SDIO%u,PollReadBlock:%u,Err:%s", num, block_num, HalStatusToStr(ret));
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->Handle.ErrorCode, HalSdioErrCode2Str(Node->Handle.ErrorCode));
#endif
        }
    } else {
        LOG_ERROR(LG_SDIO, "SDIO%u,NodeErr %s", num);
    }
    return res;
}
