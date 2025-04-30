#include "sdio_drv.h"

#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "debug_info.h"
#include "hal_diag.h"
#include "log.h"
#include "log_utils.h"
#include "none_blocking_pause.h"
#include "sdio_bsp.h"
#include "sdio_config.h"
#include "sdio_diag.h"
#include "time_utils.h"

#ifdef HAS_DMA
#include "dma_bsp.h"
#endif

uint8_t SdioInstance2num(SD_TypeDef* Instance) {
    uint8_t sdio_num = 1;
    if(SDIO == Instance) {
        sdio_num = 1;
    }
    return sdio_num;
}

static bool SdioWaitTxDoneLl(SdioHandle_t* SdioNode, uint32_t time_out, uint8_t sdio_num, uint32_t block_num) {
    bool res = true;
    uint32_t cur_ms = 0;
    uint32_t diff_ms = 0;
    uint32_t start_ms = time_get_ms32();
    while(false == SdioNode->tx_int) {
        cur_ms = time_get_ms32();
        diff_ms = cur_ms - start_ms;
        if(time_out < diff_ms) {
            LOG_ERROR(LG_SDIO, "%u WriteBlock %u TimeOut", sdio_num, block_num);
            break;
            res = false;
        }
    }
    return res;
}

static bool SdioWaitRxDoneLl(SdioHandle_t* SdioNode, uint32_t time_out_ms, uint8_t sdio_num, uint32_t block_num) {
    bool res = true;
    uint32_t cur_ms = 0;
    uint32_t diff_ms = 0;
    uint32_t start_ms = time_get_ms32();
    while(false == SdioNode->rx_int) {
        cur_ms = time_get_ms32();
        diff_ms = cur_ms - start_ms;
        if(time_out_ms < diff_ms) {
            LOG_ERROR(LG_SDIO, "%u ReadBlock %u TimeOut", sdio_num, block_num);
            res = false;
            break;
        }
    }
    return res;
}

#ifdef HAS_DMA
bool sdio_read_sector_dma(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "ReadBlockDma SdioNum:%u BlkNum:%u BlkCnt:%u", sdio_num, block_num, block_cnt);
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        memset(RxData, 0, SDIO_BLOCK_SIZE * block_cnt);
        HAL_StatusTypeDef ret;
        SdioNode->rx_int = false;
        wait_ms(SDIO_TIME_OUT_MS);
        ret = HAL_SD_ReadBlocks_DMA(&SdioNode->sdio_h, RxData, block_num, block_cnt);
        if(HAL_OK == ret) {
            res = SdioWaitRxDoneLl(SdioNode, SDIO_RX_TIME_OUT_MS, sdio_num, block_num);
            if(res) {
                LOG_DEBUG(LG_SDIO, "%u ReadBlock %u Ok", sdio_num, block_num);
                log_level_t log_level = log_level_get(LG_SDIO);
                if(LOG_LEVEL_PARANOID == log_level) {
                    res = print_mem(RxData, SDIO_BLOCK_SIZE * block_cnt, true, true, true, true);
                }
            }
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u DmaReadBlockErr %u %u=%s", sdio_num, block_num, ret, HalStatus2Str(ret));
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", SdioNode->sdio_h.ErrorCode,
                      HalSdioErrCode2Str(SdioNode->sdio_h.ErrorCode));
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", sdio_num);
    }
    return res;
}
#endif

#ifdef HAS_INTERRUPT
bool sdio_read_sector_it(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "ReadBlockIT SdioNum:%u BlkNum:%u BlkCnt:%u", sdio_num, block_num, block_cnt);
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        memset(RxData, 0, SDIO_BLOCK_SIZE * block_cnt);
        HAL_StatusTypeDef ret;
        SdioNode->rx_int = false;
        wait_ms(SDIO_TIME_OUT_MS);
        ret = HAL_SD_ReadBlocks_IT(&SdioNode->sdio_h, RxData, block_num, block_cnt);
        if(HAL_OK == ret) {
            res = SdioWaitRxDoneLl(SdioNode, SDIO_RX_TIME_OUT_MS, sdio_num, block_num);
            if(res) {
                LOG_DEBUG(LG_SDIO, "%u ReadBlockIT %u Ok", sdio_num, block_num);
                log_level_t log_level = log_level_get(LG_SDIO);
                if(LOG_LEVEL_PARANOID == log_level) {
                    res = print_mem(RxData, SDIO_BLOCK_SIZE * block_cnt, true, true, true, true);
                }
            }
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u ItReadBlockIT %u Err %s", sdio_num, block_num, HalStatus2Str(ret));
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", SdioNode->sdio_h.ErrorCode,
                      HalSdioErrCode2Str(SdioNode->sdio_h.ErrorCode));
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", sdio_num);
    }
    return res;
}

bool sdio_write_sector_it(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData) {
    LOG_DEBUG(LG_SDIO, "WriteBlockIT SdioNum:%u BlkNum:%u BlkCnt:%u", sdio_num, block_num, block_cnt);
    bool res = false;
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        res = false;
        HAL_StatusTypeDef ret;
        SdioNode->tx_int = false;
        wait_ms(SDIO_TIME_OUT_MS);
        ret = HAL_SD_WriteBlocks_IT(&SdioNode->sdio_h, (uint8_t*)TxData, block_num, block_cnt);
        if(HAL_OK == ret) {
            res = SdioWaitTxDoneLl(SdioNode, SDIO_TX_TIME_OUT_MS, sdio_num, block_num);
            if(res) {
                LOG_DEBUG(LG_SDIO, "%u WriteBlockIt %u Ok", sdio_num, block_num);
            }
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u WriteBlockIt Num:%u Err %s", sdio_num, block_num, HalStatus2Str(ret));
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", SdioNode->sdio_h.ErrorCode,
                      HalSdioErrCode2Str(SdioNode->sdio_h.ErrorCode));
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", sdio_num);
    }
    LOG_DEBUG(LG_SDIO, "%u WriteBlockIt Num:%u done", sdio_num, block_num);
    return res;
}
#endif

bool sdio_read_sector_time_out(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "ReadBlockTimeOut SdioNum:%u BlkNum:%u BlkCnt:%u", sdio_num, block_num, block_cnt);
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        memset(RxData, 0, SDIO_BLOCK_SIZE * block_cnt);
        HAL_StatusTypeDef ret;
        ret = HAL_SD_ReadBlocks(&SdioNode->sdio_h, RxData, block_num, block_cnt, SDIO_RX_TIME_OUT_MS);
        if(HAL_OK == ret) {
            LOG_DEBUG(LG_SDIO, "%u ReadBlockTo %u Ok", sdio_num, block_num);
            log_level_t log_level = log_level_get(LG_SDIO);
            if(LOG_LEVEL_PARANOID == log_level) {
                res = print_mem(RxData, SDIO_BLOCK_SIZE * block_cnt, true, true, true, true);
            }
            res = true;
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u ToReadBlockTo %u Err %s", sdio_num, block_num, HalStatus2Str(ret));
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", SdioNode->sdio_h.ErrorCode,
                      HalSdioErrCode2Str(SdioNode->sdio_h.ErrorCode));
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", sdio_num);
    }
    return res;
}

bool sdio_write_sector_time_out(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData) {
    LOG_DEBUG(LG_SDIO, "WriteBlockTimeOut SdioNum:%u BlkNum:%u BlkCnt:%u", sdio_num, block_num, block_cnt);
    bool res = false;
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        res = false;
        HAL_StatusTypeDef ret;
        ret = HAL_SD_WriteBlocks(&SdioNode->sdio_h, (uint8_t*)TxData, block_num, block_cnt, SDIO_TX_TIME_OUT_MS);
        if(HAL_OK == ret) {
            LOG_DEBUG(LG_SDIO, "%u WriteBlockTo %u Ok", sdio_num, block_num);
            res = true;
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u WriteBlockTo Num:%u Err %s", sdio_num, block_num, HalStatus2Str(ret));
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", SdioNode->sdio_h.ErrorCode,
                      HalSdioErrCode2Str(SdioNode->sdio_h.ErrorCode));
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", sdio_num);
    }
    LOG_DEBUG(LG_SDIO, "%u WriteBlockTo Num:%u done", sdio_num, block_num);
    return res;
}

#ifdef HAS_DMA
bool sdio_write_sector_dma(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData) {
    LOG_DEBUG(LG_SDIO, "WriteBlockDma SdioNum:%u BlkNum:%u BlkCnt:%u", sdio_num, block_num, block_cnt);
    bool res = false;
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        res = false;
        HAL_StatusTypeDef ret;
        wait_ms(SDIO_TIME_OUT_MS); /*TODO Minimize time here*/
        SdioNode->tx_int = false;
        ret = HAL_SD_WriteBlocks_DMA(&SdioNode->sdio_h, (uint8_t*)TxData, block_num, block_cnt);
        if(HAL_OK == ret) {
            res = SdioWaitTxDoneLl(SdioNode, SDIO_TX_TIME_OUT_MS, sdio_num, block_num);
            if(res) {
                LOG_DEBUG(LG_SDIO, "%u WriteBlockDma %u Ok", sdio_num, block_num);
            }
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u WriteBlockDma Num:%u Err %s", sdio_num, block_num, HalStatus2Str(ret));
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", SdioNode->sdio_h.ErrorCode,
                      HalSdioErrCode2Str(SdioNode->sdio_h.ErrorCode));
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", sdio_num);
    }
    LOG_DEBUG(LG_SDIO, "%u WriteBlockDma Num:%u done", sdio_num, block_num);
    return res;
}
#endif

void HAL_SD_MspInit(SD_HandleTypeDef* sdHandle) {
    if(SDIO == sdHandle->Instance) {
        __HAL_RCC_SDIO_CLK_ENABLE();
#ifdef HAS_DMA
        DmaHandle_t* DmaNodeRx = DmaGetNode(DMA2_SDIO_RX);
        if(DmaNodeRx) {
            __HAL_LINKDMA(sdHandle, hdmarx, DmaNodeRx->dma_h);
        }
        DmaHandle_t* DmaNodeTx = DmaGetNode(DMA2_SDIO_TX);
        if(DmaNodeTx) {
            __HAL_LINKDMA(sdHandle, hdmatx, DmaNodeTx->dma_h);
        }
#endif                                         /*HAS_DMA*/
        HAL_NVIC_SetPriority(SDIO_IRQn, 2, 2); /*Crutial*/
        HAL_NVIC_EnableIRQ(SDIO_IRQn);
    }
}

void HAL_SD_MspDeInit(SD_HandleTypeDef* sdHandle) {
    if(SDIO == sdHandle->Instance) {
        __HAL_RCC_SDIO_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(SDIO_IRQn);
    }
}

bool sdio_read_sector(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "ReadBlock SdioNum:%u BlkNum:%u BlkCnt:%u", sdio_num, block_num, block_cnt);
    uint32_t try
        = 0;
    bool read_ok = false;
    for(try = 0; try <= SDIO_READ_TRY_CNT; try ++) {
        res = false;
#ifdef HAS_INTERRUPT
        // res = sdio_read_sector_it(sdio_num, block_num, block_cnt, RxData);
#endif

#ifdef HAS_DMA
        res = sdio_read_sector_dma(sdio_num, block_num, block_cnt, RxData);
#else  /*HAS_DMA*/
#endif /*HAS_DMA*/
        // res = sdio_read_sector_time_out(sdio_num, block_num, block_cnt, RxData);
        SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
        if(SdioNode) {
            SdioNode->read_cnt++;
            if(res) {
                read_ok = true;
                SdioNode->read_ok_cnt++;
                LOG_DEBUG(LG_SDIO, "ReadBlockOk SdioNum:%u BlkNum:%u try:%u", sdio_num, block_num, try);
                SdioNode->try_read_cnt++;
                break;
            } else {
                SdioNode->read_err_cnt++;
            }
        }
    }
    if(false == read_ok) {
        LOG_ERROR(LG_SDIO, "ReadBlock SdioNum:%u BlkNum:%u BlkCnt:%u err", sdio_num, block_num, block_cnt);
    }

    return res;
}

bool sdio_write_sector(uint8_t sdio_num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "WriteBlock SdioNum:%u BlkNum:%u BlkCnt:%u", sdio_num, block_num, block_cnt);
    uint32_t try
        = 0;
    for(try = 0; try < SDIO_WRITE_TRY_CNT; try ++) {
        res = false;
#ifdef HAS_INTERRUPT
        // res = sdio_write_sector_it(sdio_num, block_num, block_cnt, TxData);
#endif
#ifdef HAS_DMA
        res = sdio_write_sector_dma(sdio_num, block_num, block_cnt, TxData);
#else
#endif
        // res= sdio_write_sector_time_out(sdio_num, block_num, block_cnt, TxData);
        wait_ms(SDIO_TIME_OUT_MS); /*TODO: minimize that time*/
        if(res) {
            LOG_DEBUG(LG_SDIO, "WriteBlockOk SdioNum:%u BlkNum:%u try:%u", sdio_num, block_num, try);
            SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
            if(SdioNode) {
                SdioNode->try_write_cnt++;
            }
            break;
        }
    }
    return res;
}

bool sdio_scan(uint8_t sdio_num) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "Scan SdioNum:%u ", sdio_num);
    set_log_level(LG_SDIO, LOG_LEVEL_NOTICE);
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        HAL_StatusTypeDef ret;
        ret = HAL_SD_GetCardInfo(&SdioNode->sdio_h, &SdioNode->CardInfo);
        if(HAL_OK == ret) {
            LOG_INFO(LG_SDIO, "%u GetCardInfo Ok", sdio_num);
            res = true;
        } else {
            LOG_ERROR(LG_SDIO, "GetCardInfoErr %s", HalStatus2Str(ret));
        }
    }

    if(res) {
        uint32_t sum = 0;
        SdioNode->busy_block_cnt = 0;
        SdioNode->spare_block_cnt = 0;
        // uint8_t RxData[SDIO_BLOCK_SIZE + 1];
        LOG_INFO(LG_SDIO, "BlockNbr %u", SdioNode->CardInfo.BlockNbr);
        uint32_t i = 0;
        for(i = 0; i < SdioNode->CardInfo.BlockNbr; i++) {
            if(0 == (i % 400)) {
                cli_printf("\r%9u Progress %f %% Busy:%6u Spare:%6u Spare: %f %%", i,
                           100.0 * ((double)i) / ((double)SdioNode->CardInfo.BlockNbr), SdioNode->busy_block_cnt,
                           SdioNode->spare_block_cnt, 100.0 * ((double)SdioNode->spare_block_cnt) / ((double)i));
            }
            res = sdio_read_sector(sdio_num, i, 1, SdioNode->RxData);
            if(res) {
                sum = arr_sum(SdioNode->RxData, SDIO_BLOCK_SIZE);
                if(0 < sum) {
                    SdioNode->busy_block_cnt++;
                } else {
                    SdioNode->spare_block_cnt++;
                }
            } else {
                LOG_ERROR(LG_SDIO, "Read err BlockNbr %u", i);
            }
        }
        LOG_INFO(LG_SDIO, "BlockNbr %u", SdioNode->CardInfo.BlockNbr);
        LOG_INFO(LG_SDIO, "busy %u Blk", SdioNode->busy_block_cnt);
        LOG_INFO(LG_SDIO, "spare %u Blk", SdioNode->spare_block_cnt);
    }
    set_log_level(LG_SDIO, LOG_LEVEL_DEBUG);
    return res;
}

/* 0-84MHz */
/* 1-48MHz */
/* 2-28MHz */
/* 3-21MHz */
/* 4-16MHz */
/* 5-14MHz */
static uint32_t SdioCalcClockDiv(uint32_t apb2_clk2, uint32_t bit_rate_hz) {
    uint32_t clock_div = 0;
    LOG_INFO(LG_SDIO, "APB2 Clock %u Hz(Max: 84 MHz) DesClk %u Hz", apb2_clk2, bit_rate_hz);
    double tapb2 = 1.0 / ((double)apb2_clk2);
    double tclk = 1.0 / ((double)bit_rate_hz);
    LOG_INFO(LG_SDIO, "tapb2 %f", tapb2);
    LOG_INFO(LG_SDIO, "tclk %f", tclk);
    double needed_div = tclk / tapb2;
    LOG_INFO(LG_SDIO, "CalcDiv %f", needed_div);
    clock_div = (uint32_t)needed_div;
    LOG_INFO(LG_SDIO, "CalcDiv %f =%u", needed_div, clock_div);
    double read_clock = 1.0 / ((tapb2) * ((double)clock_div));

    LOG_INFO(LG_SDIO, "RealSDIOclock %f Hz", read_clock);
    return clock_div - 1;
}

bool sdio_init_ll(uint32_t sdio_num) {
    bool res = false;
    LOG_INFO(LG_SDIO, "Init: %u", sdio_num);
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    const SdioConfig_t* SdioConfigNode = SdioGetConfNode(sdio_num);
    if(SdioConfigNode) {
        if(SdioNode) {
            SdioNode->sdio_h.Instance = SDIO;
            SdioNode->sdio_h.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
            SdioNode->sdio_h.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
            SdioNode->sdio_h.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
            SdioNode->sdio_h.Init.BusWide = SDIO_BUS_WIDE_1B;
            SdioNode->sdio_h.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
            uint32_t pclk2 = HAL_RCC_GetPCLK2Freq();
            uint32_t clock_div = SdioCalcClockDiv(pclk2, SdioConfigNode->bit_rate_hz);
            if(clock_div < 255) {
                LOG_INFO(LG_SDIO, "FinalClockDiv %u", clock_div);
                SdioNode->sdio_h.Init.ClockDiv = clock_div;
            } else {
                LOG_ERROR(LG_SDIO, "FinalClockDivErr %u", clock_div);
                SdioNode->sdio_h.Init.ClockDiv = clock_div;
            }

            HAL_StatusTypeDef ret;
            ret = HAL_SD_Init(&SdioNode->sdio_h);
            if(HAL_OK == ret) {
                res = true;
#ifdef HAS_SDIO_4BIT
                ret = HAL_SD_ConfigWideBusOperation(&SdioNode->sdio_h, SDIO_BUS_WIDE_4B);
                if(HAL_OK == ret) {
                    LOG_INFO(LG_SDIO, "4BitInitOk", sdio_num);
                    res = true;
                } else {
                    res = false;
                    LOG_ERROR(LG_SDIO, "4BitInitErr", sdio_num);
                    LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", SdioNode->sdio_h.ErrorCode,
                              HalSdioErrCode2Str(SdioNode->sdio_h.ErrorCode));
                }
#endif
                res = sdio_read_sector(sdio_num, 2, 1, SdioNode->RxData);
                if(res) {
                    LOG_INFO(LG_SDIO, "TestReadOk", sdio_num);
                } else {
                    LOG_ERROR(LG_SDIO, "TestReadErr", sdio_num);
                }
            } else {
                LOG_ERROR(LG_SDIO, "InitErr %s", HalStatus2Str(ret));
                LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", SdioNode->sdio_h.ErrorCode,
                          HalSdioErrCode2Str(SdioNode->sdio_h.ErrorCode));
                res = false;
            }
#ifdef HAS_SD_CARD_INIT
            if(res) {
                ret = HAL_SD_InitCard(&SdioNode->sdio_h);
                if(HAL_OK == ret) {
                    LOG_INFO(LG_SDIO, "CardInitOk", sdio_num);
                    res = true;
                } else {
                    LOG_ERROR(LG_SDIO, "CardInitErr %s", HalStatus2Str(ret));
                    LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", SdioNode->sdio_h.ErrorCode,
                              HalSdioErrCode2Str(SdioNode->sdio_h.ErrorCode));
                    res = false;
                }
            }
#endif
        }
    }
    return res;
}

bool sdio_init(void) {
    bool res = false;
    uint32_t sdio_num = 0;
    uint32_t ok_cnt = 0;
    uint32_t sdio_cnt = 0;

    set_log_level(LG_SDIO, LOG_LEVEL_INFO);

    sdio_cnt = sdio_get_cnt();
    LOG_INFO(LG_SDIO, "Total:%u", sdio_cnt);
    for(sdio_num = 0; sdio_num <= sdio_cnt; sdio_num++) {
        res = sdio_init_ll(sdio_num);
        if(res) {
            ok_cnt++;
        }
    }

    if(ok_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

uint32_t sdio_get_block_num(uint32_t sdio_num) {
    uint32_t block_num = 0;
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        HAL_StatusTypeDef ret;
        ret = HAL_SD_GetCardInfo(&SdioNode->sdio_h, &SdioNode->CardInfo);
        if(HAL_OK == ret) {
            block_num = SdioNode->CardInfo.LogBlockNbr;
        }
    }
    return block_num;
}

uint16_t sdio_get_block_size(uint32_t sdio_num) {
    uint16_t block_size = 0;
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        HAL_StatusTypeDef ret;
        ret = HAL_SD_GetCardInfo(&SdioNode->sdio_h, &SdioNode->CardInfo);
        if(HAL_OK == ret) {
            block_size = SdioNode->CardInfo.LogBlockSize;
        }
    }
    return block_size;
}

bool sdio_card_info_get(uint32_t sdio_num) {
    bool res = true;
    uint32_t ok_cnt = 0;
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_SD_GetCardStatus(&SdioNode->sdio_h, &SdioNode->status);
        if(HAL_OK != ret) {
            LOG_DEBUG(LG_SDIO, "GetStatusErr %u=%s", ret, HalStatus2Str(ret));
            memset(&SdioNode->status, 0, sizeof(HAL_SD_CardStatusTypeDef));
            res = false;
        } else {
            ok_cnt++;
        }
        ret = HAL_SD_GetCardCID(&SdioNode->sdio_h, &SdioNode->CID);
        if(HAL_OK != ret) {
            LOG_ERROR(LG_SDIO, "GetCIDErr %s", HalStatus2Str(ret));
            res = false;
        } else {
            ok_cnt++;
        }
        ret = HAL_SD_GetCardCSD(&SdioNode->sdio_h, &SdioNode->CSD);
        if(HAL_OK != ret) {
            LOG_ERROR(LG_SDIO, "GetCSDErr %s", HalStatus2Str(ret));
            res = false;
        } else {
            ok_cnt++;
        }
        ret = HAL_SD_GetCardInfo(&SdioNode->sdio_h, &SdioNode->CardInfo);
        if(HAL_OK != ret) {
            LOG_ERROR(LG_SDIO, "GetCardInfoErr %s", HalStatus2Str(ret));
            res = false;
        } else {
            ok_cnt++;
        }
    } else {
        res = false;
    }

    if(ok_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool sdio_is_connected(uint32_t sdio_num) {
    bool res = true;
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        HAL_StatusTypeDef ret = HAL_SD_GetCardStatus(&SdioNode->sdio_h, &SdioNode->status);
        if(HAL_OK != ret) {
            LOG_DEBUG(LG_SDIO, "GetCardStatusErr");
            if(SdioNode->sdio_h.ErrorCode) {
                LOG_DEBUG(LG_SDIO, "ErrorCode 0x%x=%s", SdioNode->sdio_h.ErrorCode,
                          HalSdioErrCode2Str(SdioNode->sdio_h.ErrorCode));
                // res=sdio_init();
            }
        }

        SdioNode->SD_CardState = HAL_SD_GetCardState(&SdioNode->sdio_h);
        switch(SdioNode->SD_CardState) {
        case 0: {
            res = true;
        } break;
        case HAL_SD_CARD_READY: {
            res = true;
        } break;
        case HAL_SD_CARD_IDENTIFICATION: {
            res = true;
        } break;
        case HAL_SD_CARD_STANDBY: {
            res = true;
        } break;
        case HAL_SD_CARD_TRANSFER: {
            res = true;
        } break;
        case HAL_SD_CARD_SENDING: {
            res = true;
        } break;
        case HAL_SD_CARD_RECEIVING: {
            res = true;
        } break;
        case HAL_SD_CARD_PROGRAMMING: {
            res = true;
        } break;
        case HAL_SD_CARD_ERROR: {
            LOG_DEBUG(LG_SDIO, "CardErr");
            res = false;
        } break;
        case HAL_SD_CARD_DISCONNECTED: {
            LOG_ERROR(LG_SDIO, "CardDisconnected");
            res = false;
        } break;
        default: {
            LOG_ERROR(LG_SDIO, "Card %u-%s", SdioNode->SD_CardState, CardState2Str(SdioNode->SD_CardState));
        } break;
        }
        res = sdio_read_sector(sdio_num, 2, 1, SdioNode->RxData);
        if(res) {
            LOG_DEBUG(LG_SDIO, "CardConnected");
        } else {
            LOG_ERROR(LG_SDIO, "CardDisconnected");
        }
    }

    return res;
}

bool sdio_proc(void) {
    bool res = false;
    res = sdio_is_connected(1);
    if(false == res) {
        LOG_ERROR(LG_SDIO, "CardDisconnected");
    } else {
        res = sdio_card_info_get(1);
    }
    SdioHandle_t* SdioNode = SdioGetNode(1);
    if(SdioNode) {
        if(SdioNode->rx_cnt_prev < SdioNode->rx_cnt) {
            int32_t rx_diff = SdioNode->rx_cnt - SdioNode->rx_cnt_prev;
            LOG_WARNING(LG_SDIO, "RxInterrupt %u +%u %u ms", SdioNode->rx_cnt, rx_diff, SdioNode->rx_time_stamp);
        }

        if(SdioNode->tx_cnt_prev < SdioNode->tx_cnt) {
            int32_t tx_diff = SdioNode->tx_cnt - SdioNode->tx_cnt_prev;
            LOG_WARNING(LG_SDIO, "TxInterrupt %u +%u %u ms", SdioNode->tx_cnt, tx_diff, SdioNode->tx_time_stamp);
        }
        SdioNode->tx_cnt_prev = SdioNode->tx_cnt;
        SdioNode->rx_cnt_prev = SdioNode->rx_cnt;
    }
    return res;
}
