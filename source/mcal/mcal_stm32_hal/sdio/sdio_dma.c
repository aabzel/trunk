#include "sdio_dma.h"

#include <string.h>

#include "array_diag.h"
#include "dma_mcal.h"
#include "log.h"
#include "sdio_mcal.h"
#include "dma_channel_config.h"



bool sdio_dma_init(SD_HandleTypeDef* sdHandle) {
    bool res2 = false;
    bool res1 = false;
    bool res = false;
    DmaChannelHandle_t* DmaNodeRx = DmaChannelGetNode(DMA_CHANNEL_NUM_SDIO_RX);
    if(DmaNodeRx) {
        res1 = dma_channel_init_one(  DMA_CHANNEL_NUM_SDIO_RX);
        __HAL_LINKDMA(sdHandle, hdmarx, DmaNodeRx->dma_h);
    }
    DmaChannelHandle_t* DmaNodeTx = DmaChannelGetNode(DMA_CHANNEL_NUM_SDIO_TX);
    if(DmaNodeTx) {
        res2 = dma_channel_init_one(  DMA_CHANNEL_NUM_SDIO_TX);
        __HAL_LINKDMA(sdHandle, hdmatx, DmaNodeTx->dma_h);
    }
    if(res1 && res2){
        res = true;
    }
    return res;
}

bool sdio_write_sector_dma(uint8_t num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData) {
#ifdef HAS_SDIO_DEBUG
    LOG_DEBUG(LG_SDIO, "WriteBlockDma Num:%u BlkNum:%u BlkCnt:%u", num, block_num, block_cnt);
#endif
    bool res = false;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret;
        Node->tx_done = false;
        //ret = HAL_SD_Abort(&Node->Handle);
        sdio_wait_card_operation(&Node->Handle);
        ret = HAL_SD_WriteBlocks_DMA(&Node->Handle, (uint8_t*)TxData, block_num, block_cnt);
        if(HAL_OK == ret) {
            //sdio_wait_card_operation(&Node->Handle);
            //res = true;
            res = SdioWaitTxDoneLl(Node, SDIO_TX_TIME_OUT_MS, num, block_num);
#ifdef HAS_SDIO_DEBUG
            if(res) {
                LOG_DEBUG(LG_SDIO, "%u WriteBlockDma %u Ok", num, block_num);
            }
#endif
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u WriteBlockDma Num:%u Err %s", num, block_num, HalStatusToStr(ret));
#ifdef HAS_SDIO_DIAG
            LOG_ERROR(LG_SDIO, "WrErrorCode 0x%x=%s", Node->Handle.ErrorCode, HalSdioErrCode2Str(Node->Handle.ErrorCode));
#endif
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", num);
    }
#ifdef HAS_SDIO_DEBUG
    LOG_DEBUG(LG_SDIO, "%u WriteBlockDma Num:%u done", num, block_num);
#endif
    return res;
}

bool sdio_read_sector_dma(uint8_t num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData) {
    bool res = false;
#ifdef HAS_SDIO_DEBUG
    LOG_DEBUG(LG_SDIO, "ReadBlockDma Num:%u BlkNum:%u BlkCnt:%u", num, block_num, block_cnt);
#endif
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        memset(RxData, 0, SDIO_BLOCK_SIZE * block_cnt);
        HAL_StatusTypeDef ret;
        Node->rx_done = false;
        //ret = HAL_SD_Abort(&Node->Handle);
        sdio_wait_card_operation(&Node->Handle);
        ret = HAL_SD_ReadBlocks_DMA(&Node->Handle, RxData, block_num, block_cnt);
        if(HAL_OK == ret) {
            //sdio_wait_card_operation(&Node->Handle);
            //res = true;
            res = SdioWaitRxDoneLl(Node, SDIO_RX_TIME_OUT_MS, num, block_num);
#ifdef HAS_SDIO_DEBUG
            if(res) {
                LOG_DEBUG(LG_SDIO, "%u ReadBlock %u Ok", num, block_num);
#ifdef HAS_ARRAY_DIAG
                log_level_t log_level = log_level_get(LG_SDIO);
                if(LOG_LEVEL_PARANOID == log_level) {
                    res = print_mem(RxData, SDIO_BLOCK_SIZE * block_cnt, true, true, true, true);
                }
#endif
            }
#endif
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u DmaReadBlockErr %u %u=%s", num, block_num, ret, HalStatusToStr(ret));
#ifdef HAS_SDIO_DIAG
            LOG_ERROR(LG_SDIO, "RdErrorCode 0x%x=%s", Node->Handle.ErrorCode, HalSdioErrCode2Str(Node->Handle.ErrorCode));
#endif
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", num);
    }
    return res;
}
