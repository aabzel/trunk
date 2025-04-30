#include "sdio_drv.h"

#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "debug_info.h"
#include "hal_diag.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "sdio_bsp.h"
#include "sdio_config.h"
#include "time_utils.h"

#ifdef HAS_SDIO_DMA
#include "dma_bsp.h"
#endif

#ifdef HAS_SDIO_INTERRUPT
#ifdef HAS_SDIO_DMA
#error Chose one MODE
#endif /*HAS_SDIO_DMA*/
#endif /*HAS_SDIO_INTERRUPT*/

uint8_t SdioInstance2num(SD_TypeDef* Instance) {
    uint8_t num = 1;
    if(SDIO == Instance) {
        num = 1;
    }
    return num;
}

static bool SdioWaitTxDoneLl(SdioHandle_t* Node, uint32_t time_out, uint8_t num, uint32_t block_num) {
    bool res = true;
    uint32_t cur_ms = 0;
    uint32_t diff_ms = 0;
    uint32_t start_ms = time_get_ms32();
    while(false == Node->tx_int) {
        cur_ms = time_get_ms32();
        diff_ms = cur_ms - start_ms;
        if(time_out < diff_ms) {
            LOG_ERROR(LG_SDIO, "%u WriteBlock %u TimeOut", num, block_num);
            break;
            res = false;
        }

        if(HAL_SD_STATE_READY == Node->sdio_h.State) {
            res = true;
            break;
        }
    }
    return res;
}

static bool SdioWaitRxDoneLl(SdioHandle_t* Node, uint32_t time_out_ms, uint8_t num, uint32_t block_num) {
    bool res = true;
    uint32_t cur_ms = 0;
    uint32_t diff_ms = 0;
    uint32_t start_ms = time_get_ms32();
    while(false == Node->rx_int) {
        cur_ms = time_get_ms32();
        diff_ms = cur_ms - start_ms;
        if(time_out_ms < diff_ms) {
            LOG_ERROR(LG_SDIO, "%u ReadBlock %u TimeOut", num, block_num);
            res = false;
            break;
        }

        if(HAL_SD_STATE_READY == Node->sdio_h.State) {
            res = true;
            break;
        }
    }
    return res;
}

#ifdef HAS_SDIO_DMA
bool sdio_read_sector_dma(uint8_t num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "ReadBlockDma SdioNum:%u BlkNum:%u BlkCnt:%u", num, block_num, block_cnt);
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        memset(RxData, 0, SDIO_BLOCK_SIZE * block_cnt);
        HAL_StatusTypeDef ret;
        Node->rx_int = false;
        wait_ms(SDIO_TIME_OUT_MS);
        ret = HAL_SD_ReadBlocks_DMA(&Node->sdio_h, RxData, block_num, block_cnt);
        if(HAL_OK == ret) {
            res = SdioWaitRxDoneLl(Node, SDIO_RX_TIME_OUT_MS, num, block_num);
            if(res) {
                LOG_DEBUG(LG_SDIO, "%u ReadBlock %u Ok", num, block_num);
                log_level_t log_level = log_level_get(LG_SDIO);
                if(LOG_LEVEL_PARANOID == log_level) {
                    res = print_mem(RxData, SDIO_BLOCK_SIZE * block_cnt, true, true, true, true);
                }
            }
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u DmaReadBlockErr %u %u=%s", num, block_num, ret, HalStatus2Str(ret));
#ifdef HAS_SDIO_DIAG
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->sdio_h.ErrorCode, HalSdioErrCode2Str(Node->sdio_h.ErrorCode));
#endif
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", num);
    }
    return res;
}
#endif

#ifdef HAS_SDIO_INTERRUPT
bool sdio_read_sector_it(uint8_t num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "ReadBlockIT SdioNum:%u BlkNum:%u BlkCnt:%u", num, block_num, block_cnt);
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        memset(RxData, 0, SDIO_BLOCK_SIZE * block_cnt);
        HAL_StatusTypeDef ret;
        Node->rx_int = false;
        wait_ms(SDIO_TIME_OUT_MS); /*TODO discard pause*/
        ret = HAL_SD_ReadBlocks_IT(&Node->sdio_h, RxData, block_num, block_cnt);
        if(HAL_OK == ret) {
            res = SdioWaitRxDoneLl(Node, SDIO_RX_TIME_OUT_MS, num, block_num);
            if(res) {
                LOG_DEBUG(LG_SDIO, "%u ReadBlockIT %u Ok", num, block_num);
                log_level_t log_level = log_level_get(LG_SDIO);
                if(LOG_LEVEL_PARANOID == log_level) {
                    res = print_mem(RxData, SDIO_BLOCK_SIZE * block_cnt, true, true, true, true);
                }
            }
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u ItReadBlockIT %u Err %s", num, block_num, HalStatus2Str(ret));
#ifdef HAS_SDIO_DIAG
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->sdio_h.ErrorCode, HalSdioErrCode2Str(Node->sdio_h.ErrorCode));
#endif
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", num);
    }
    return res;
}

bool sdio_write_sector_it(uint8_t num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData) {
    LOG_DEBUG(LG_SDIO, "WriteBlockIT SdioNum:%u BlkNum:%u BlkCnt:%u", num, block_num, block_cnt);
    bool res = false;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        res = false;
        HAL_StatusTypeDef ret;
        Node->tx_int = false;
        wait_ms(SDIO_TIME_OUT_MS);
        ret = HAL_SD_WriteBlocks_IT(&Node->sdio_h, (uint8_t*)TxData, block_num, block_cnt);
        if(HAL_OK == ret) {
            res = SdioWaitTxDoneLl(Node, SDIO_TX_TIME_OUT_MS, num, block_num);
            if(res) {
                LOG_DEBUG(LG_SDIO, "%u WriteBlockIt %u Ok", num, block_num);
            }
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u WriteBlockIt Num:%u Err %s", num, block_num, HalStatus2Str(ret));
#ifdef HAS_SDIO_DIAG
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->sdio_h.ErrorCode, HalSdioErrCode2Str(Node->sdio_h.ErrorCode));
#endif
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", num);
    }
    LOG_DEBUG(LG_SDIO, "%u WriteBlockIt Num:%u done", num, block_num);
    return res;
}
#endif

bool sdio_read_sector_time_out(uint8_t num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "ReadBlockTimeOut SdioNum:%u BlkNum:%u BlkCnt:%u", num, block_num, block_cnt);
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        memset(RxData, 0, SDIO_BLOCK_SIZE * block_cnt);
        HAL_StatusTypeDef ret;
        ret = HAL_SD_ReadBlocks(&Node->sdio_h, RxData, block_num, block_cnt, SDIO_RX_TIME_OUT_MS);
        if(HAL_OK == ret) {
            LOG_DEBUG(LG_SDIO, "%u ReadBlockTo %u Ok", num, block_num);
            log_level_t log_level = log_level_get(LG_SDIO);
            if(LOG_LEVEL_PARANOID == log_level) {
                res = print_mem(RxData, SDIO_BLOCK_SIZE * block_cnt, true, true, true, true);
            }
            res = true;
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u ToReadBlockTo %u Err %s", num, block_num, HalStatus2Str(ret));
#ifdef HAS_SDIO_DIAG
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->sdio_h.ErrorCode, HalSdioErrCode2Str(Node->sdio_h.ErrorCode));
#endif
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", num);
    }
    return res;
}

bool sdio_write_sector_time_out(uint8_t num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData) {
    LOG_DEBUG(LG_SDIO, "WriteBlockTimeOut SdioNum:%u BlkNum:%u BlkCnt:%u", num, block_num, block_cnt);
    bool res = false;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        res = false;
        HAL_StatusTypeDef ret;
        ret = HAL_SD_WriteBlocks(&Node->sdio_h, (uint8_t*)TxData, block_num, block_cnt, SDIO_TX_TIME_OUT_MS);
        if(HAL_OK == ret) {
            LOG_DEBUG(LG_SDIO, "%u WriteBlockTo %u Ok", num, block_num);
            res = true;
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u WriteBlockTo Num:%u Err %s", num, block_num, HalStatus2Str(ret));
#ifdef HAS_SDIO_DIAG
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->sdio_h.ErrorCode, HalSdioErrCode2Str(Node->sdio_h.ErrorCode));
#endif
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", num);
    }
    LOG_DEBUG(LG_SDIO, "%u WriteBlockTo Num:%u done", num, block_num);
    return res;
}

#ifdef HAS_SDIO_DMA
bool sdio_write_sector_dma(uint8_t num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData) {
    LOG_DEBUG(LG_SDIO, "WriteBlockDma SdioNum:%u BlkNum:%u BlkCnt:%u", num, block_num, block_cnt);
    bool res = false;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        res = false;
        HAL_StatusTypeDef ret;
        wait_ms(SDIO_TIME_OUT_MS); /*TODO Minimize time here*/
        Node->tx_int = false;
        ret = HAL_SD_WriteBlocks_DMA(&Node->sdio_h, (uint8_t*)TxData, block_num, block_cnt);
        if(HAL_OK == ret) {
            res = SdioWaitTxDoneLl(Node, SDIO_TX_TIME_OUT_MS, num, block_num);
            if(res) {
                LOG_DEBUG(LG_SDIO, "%u WriteBlockDma %u Ok", num, block_num);
            }
        } else {
            res = false;
            LOG_ERROR(LG_SDIO, "%u WriteBlockDma Num:%u Err %s", num, block_num, HalStatus2Str(ret));
#ifdef HAS_SDIO_DIAG
            LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->sdio_h.ErrorCode, HalSdioErrCode2Str(Node->sdio_h.ErrorCode));
#endif
        }
    } else {
        LOG_ERROR(LG_SDIO, "%u NodeErr %s", num);
    }
    LOG_DEBUG(LG_SDIO, "%u WriteBlockDma Num:%u done", num, block_num);
    return res;
}
#endif

void HAL_SD_MspInit(SD_HandleTypeDef* sdHandle) {
    if(SDIO == sdHandle->Instance) {
        __HAL_RCC_SDIO_CLK_ENABLE();
#ifdef HAS_SDIO_DMA
        DmaHandle_t* DmaNodeRx = DmaGetNode(DMA2_SDIO_RX);
        if(DmaNodeRx) {
            __HAL_LINKDMA(sdHandle, hdmarx, DmaNodeRx->dma_h);
        }
        DmaHandle_t* DmaNodeTx = DmaGetNode(DMA2_SDIO_TX);
        if(DmaNodeTx) {
            __HAL_LINKDMA(sdHandle, hdmatx, DmaNodeTx->dma_h);
        }
#endif                                         /*HAS_SDIO_DMA*/
        HAL_NVIC_SetPriority(SDIO_IRQn, 2, 2); /*Crusial*/
        HAL_NVIC_EnableIRQ(SDIO_IRQn);
    }
}

void HAL_SD_MspDeInit(SD_HandleTypeDef* sdHandle) {
    if(SDIO == sdHandle->Instance) {
        __HAL_RCC_SDIO_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(SDIO_IRQn);
    }
}

bool sdio_read_sector(uint8_t num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "ReadBlock SdioNum:%u BlkNum:%u BlkCnt:%u", num, block_num, block_cnt);
    uint32_t try
        = 0;
    bool read_ok = false;
    for(try = 0; try <= SDIO_READ_TRY_CNT; try ++) {
        res = false;
#ifdef HAS_SDIO_INTERRUPT
        res = sdio_read_sector_it(num, block_num, block_cnt, RxData);
#endif /*HAS_SDIO_INTERRUPT*/

#ifdef HAS_SDIO_DMA
        res = sdio_read_sector_dma(num, block_num, block_cnt, RxData);
#endif /*HAS_SDIO_DMA*/
        // res = sdio_read_sector_time_out(num, block_num, block_cnt, RxData);
        SdioHandle_t* Node = SdioGetNode(num);
        if(Node) {
            Node->read_cnt++;
            if(res) {
                read_ok = true;
                Node->read_ok_cnt++;
                LOG_DEBUG(LG_SDIO, "ReadBlockOk SdioNum:%u BlkNum:%u try:%u", num, block_num, try);
                Node->try_read_cnt++;
                break;
            } else {
                Node->read_err_cnt++;
            }
        }
    }
    if(false == read_ok) {
        LOG_ERROR(LG_SDIO, "ReadBlock SdioNum:%u BlkNum:%u BlkCnt:%u err", num, block_num, block_cnt);
    }

    return res;
}

bool sdio_write_sector(uint8_t num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "WriteBlock SdioNum:%u BlkNum:%u BlkCnt:%u", num, block_num, block_cnt);
    uint32_t try
        = 0;
    for(try = 0; try < SDIO_WRITE_TRY_CNT; try ++) {
        res = false;
#ifdef HAS_SDIO_INTERRUPT
        res = sdio_write_sector_it(num, block_num, block_cnt, TxData);
#endif

#ifdef HAS_SDIO_DMA
        res = sdio_write_sector_dma(num, block_num, block_cnt, TxData);
#endif
        // res= sdio_write_sector_time_out(num, block_num, block_cnt, TxData);
        wait_ms(SDIO_TIME_OUT_MS); /*TODO: minimize that time*/
        if(res) {
            LOG_DEBUG(LG_SDIO, "WriteBlockOk SdioNum:%u BlkNum:%u try:%u", num, block_num, try);
            SdioHandle_t* Node = SdioGetNode(num);
            if(Node) {
                Node->try_write_cnt++;
            }
            break;
        }
    }
    return res;
}

bool sdio_scan(uint8_t num) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "Scan Num:%u ", num);
    set_log_level(LG_SDIO, LOG_LEVEL_NOTICE);
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret;
        ret = HAL_SD_GetCardInfo(&Node->sdio_h, &Node->CardInfo);
        if(HAL_OK == ret) {
            LOG_INFO(LG_SDIO, "%u GetCardInfo Ok", num);
            res = true;
        } else {
            LOG_ERROR(LG_SDIO, "GetCardInfoErr %s", HalStatus2Str(ret));
        }
    }

    if(res) {
        uint32_t sum = 0;
        Node->busy_block_cnt = 0;
        Node->spare_block_cnt = 0;
        // uint8_t RxData[SDIO_BLOCK_SIZE + 1];
        LOG_INFO(LG_SDIO, "BlockNbr %u", Node->CardInfo.BlockNbr);
        uint32_t i = 0;
        for(i = 0; i < Node->CardInfo.BlockNbr; i++) {
            if(0 == (i % 400)) {
                cli_printf("\r%9u Progress %f %% Busy:%6u Spare:%6u Spare: %f %%", i,
                           100.0 * ((double)i) / ((double)Node->CardInfo.BlockNbr), Node->busy_block_cnt,
                           Node->spare_block_cnt, 100.0 * ((double)Node->spare_block_cnt) / ((double)i));
            }
            res = sdio_read_sector(num, i, 1, Node->RxData);
            if(res) {
                sum = arr_sum(Node->RxData, SDIO_BLOCK_SIZE);
                if(0 < sum) {
                    Node->busy_block_cnt++;
                } else {
                    Node->spare_block_cnt++;
                }
            } else {
                LOG_ERROR(LG_SDIO, "Read err BlockNbr %u", i);
            }
        }
        LOG_INFO(LG_SDIO, "BlockNbr %u", Node->CardInfo.BlockNbr);
        LOG_INFO(LG_SDIO, "busy %u Blk", Node->busy_block_cnt);
        LOG_INFO(LG_SDIO, "spare %u Blk", Node->spare_block_cnt);
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

bool sdio_init_ll(uint32_t num) {
    bool res = false;
    LOG_WARNING(LG_SDIO, "Init: %u", num);
    SdioHandle_t* Node = SdioGetNode(num);
    const SdioConfig_t* Config = SdioGetConfNode(num);
    if(Config) {
        if(Node) {
            Node->sdio_h.Instance = SDIO;
            Node->sdio_h.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
            Node->sdio_h.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
            Node->sdio_h.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
            Node->sdio_h.Init.BusWide = SDIO_BUS_WIDE_1B;
            Node->sdio_h.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
            uint32_t pclk2 = HAL_RCC_GetPCLK2Freq();
            LOG_INFO(LG_SDIO, "PCLK2 %u Hz", pclk2);
            uint32_t clock_div = SdioCalcClockDiv(pclk2, Config->bit_rate_hz);
            if(clock_div < 255) {
                LOG_INFO(LG_SDIO, "FinalClockDiv %u", clock_div);
                Node->sdio_h.Init.ClockDiv = clock_div;
            } else {
                LOG_ERROR(LG_SDIO, "FinalClockDivErr %u set 254", clock_div);
                Node->sdio_h.Init.ClockDiv = 254;
            }

            HAL_StatusTypeDef ret;
            ret = HAL_SD_Init(&Node->sdio_h);
            if(HAL_OK == ret) {
                res = true;
#ifdef HAS_SDIO_4BIT
                ret = HAL_SD_ConfigWideBusOperation(&Node->sdio_h, SDIO_BUS_WIDE_4B);
                if(HAL_OK == ret) {
                    LOG_INFO(LG_SDIO, "4BitInitOk", num);
                    res = true;
                } else {
                    res = false;
                    LOG_ERROR(LG_SDIO, "4BitInitErr", num);
#ifdef HAS_SDIO_DIAG
                    LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->sdio_h.ErrorCode,
                              HalSdioErrCode2Str(Node->sdio_h.ErrorCode));
#endif
                }
#endif
                res = sdio_read_sector(num, 2, 1, Node->RxData);
                if(res) {
                    LOG_INFO(LG_SDIO, "TestReadOk", num);
                } else {
                    LOG_ERROR(LG_SDIO, "TestReadErr", num);
                }
            } else {
                LOG_ERROR(LG_SDIO, "InitErr %s", HalStatus2Str(ret));
#ifdef HAS_SDIO_DIAG
                LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->sdio_h.ErrorCode,
                          HalSdioErrCode2Str(Node->sdio_h.ErrorCode));
#endif
                res = false;
            }
#ifdef HAS_SD_CARD_INIT
            if(res) {
                ret = HAL_SD_InitCard(&Node->sdio_h);
                if(HAL_OK == ret) {
                    LOG_INFO(LG_SDIO, "CardInitOk", num);
                    res = true;
                } else {
                    LOG_ERROR(LG_SDIO, "CardInitErr %s", HalStatus2Str(ret));
#ifdef HAS_SDIO_DIAG
                    LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->sdio_h.ErrorCode,
                              HalSdioErrCode2Str(Node->sdio_h.ErrorCode));
#endif
                    res = false;
                }
            }
#endif
        }
    }
    set_log_level(LG_SDIO, LOG_LEVEL_INFO);
    return res;
}

bool sdio_init(void) {
    bool res = false;
    uint32_t num = 0;
    uint32_t ok_cnt = 0;
    uint32_t sdio_cnt = 0;

    set_log_level(LG_SDIO, LOG_LEVEL_INFO);

    sdio_cnt = sdio_get_cnt();
    LOG_INFO(LG_SDIO, "Total:%u", sdio_cnt);
    for(num = 0; num <= sdio_cnt; num++) {
        res = sdio_init_ll(num);
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

uint32_t sdio_get_block_num(uint32_t num) {
    uint32_t block_num = 0;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret;
        ret = HAL_SD_GetCardInfo(&Node->sdio_h, &Node->CardInfo);
        if(HAL_OK == ret) {
            block_num = Node->CardInfo.LogBlockNbr;
        }
    }
    return block_num;
}

uint16_t sdio_get_block_size(uint32_t num) {
    uint16_t block_size = 0;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret;
        ret = HAL_SD_GetCardInfo(&Node->sdio_h, &Node->CardInfo);
        if(HAL_OK == ret) {
            block_size = Node->CardInfo.LogBlockSize;
        }
    }
    return block_size;
}

bool sdio_card_info_get(uint32_t num) {
    bool res = true;
    uint32_t ok_cnt = 0;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_SD_GetCardStatus(&Node->sdio_h, &Node->status);
        if(HAL_OK != ret) {
            LOG_DEBUG(LG_SDIO, "GetStatusErr %u=%s", ret, HalStatus2Str(ret));
            memset(&Node->status, 0, sizeof(HAL_SD_CardStatusTypeDef));
            res = false;
        } else {
            ok_cnt++;
        }
        ret = HAL_SD_GetCardCID(&Node->sdio_h, &Node->CID);
        if(HAL_OK != ret) {
            LOG_ERROR(LG_SDIO, "GetCIDErr %s", HalStatus2Str(ret));
            res = false;
        } else {
            ok_cnt++;
        }
        ret = HAL_SD_GetCardCSD(&Node->sdio_h, &Node->CSD);
        if(HAL_OK != ret) {
            LOG_ERROR(LG_SDIO, "GetCSDErr %s", HalStatus2Str(ret));
            res = false;
        } else {
            ok_cnt++;
        }
        ret = HAL_SD_GetCardInfo(&Node->sdio_h, &Node->CardInfo);
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

#if 0
bool sdio_is_connected(uint32_t num) {
    bool res = true;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret = HAL_SD_GetCardStatus(&Node->sdio_h, &Node->status);
        if(HAL_OK != ret) {
            LOG_DEBUG(LG_SDIO, "GetCardStatusErr");
            if(Node->sdio_h.ErrorCode) {
#ifdef HAS_SDIO_DIAG
                LOG_DEBUG(LG_SDIO, "ErrorCode 0x%x=%s", Node->sdio_h.ErrorCode,
                          HalSdioErrCode2Str(Node->sdio_h.ErrorCode));
#endif
                // res=sdio_init();
            }
        }

        Node->SD_CardState = HAL_SD_GetCardState(&Node->sdio_h);
        switch(Node->SD_CardState) {
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
            LOG_ERROR(LG_SDIO, "Card %u-%s", Node->SD_CardState, CardState2Str(Node->SD_CardState));
        } break;
        }
        res = sdio_read_sector(num, 2, 1, Node->RxData);
        if(res) {
            LOG_DEBUG(LG_SDIO, "CardConnected");
        } else {
            LOG_ERROR(LG_SDIO, "CardDisconnected");
        }
    }

    return res;
}
#endif

bool sdio_proc(void) {
    bool res = false;
#if 0
    res = sdio_is_connected(1);
    if(false == res) {
        LOG_ERROR(LG_SDIO, "CardDisconnected");
    } else {
        res = sdio_card_info_get(1);
    }
#endif
    SdioHandle_t* Node = SdioGetNode(1);
    if(Node) {
        if(Node->rx_cnt_prev < Node->rx_cnt) {
            int32_t rx_diff = Node->rx_cnt - Node->rx_cnt_prev;
            LOG_WARNING(LG_SDIO, "RxInterrupt %u +%u %u ms", Node->rx_cnt, rx_diff, Node->rx_time_stamp);
        }

        if(Node->tx_cnt_prev < Node->tx_cnt) {
            int32_t tx_diff = Node->tx_cnt - Node->tx_cnt_prev;
            LOG_WARNING(LG_SDIO, "TxInterrupt %u +%u %u ms", Node->tx_cnt, tx_diff, Node->tx_time_stamp);
        }
        Node->tx_cnt_prev = Node->tx_cnt;
        Node->rx_cnt_prev = Node->rx_cnt;
    }
    return res;
}
