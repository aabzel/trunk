#include "i2s_mcal.h"

#include <string.h>

#include "std_includes.h"
#include "clock_const.h"
#include "microcontroller.h"
#include "clock_custom_diag.h"
#include "clock_diag.h"
#include "clock_custom_const.h"
#include "clock_utils.h"
#include "i2s_config.h"
#include "hal_mcal.h"
#include "gpio_mcal.h"
#include "i2s_custom_diag.h"
#include "i2s_custom_misc.h"
#include "i2s_custom_drv.h"
#include "i2s_custom_types.h"
#include "interrupt_mcal.h"
#include "interfaces_diag.h"
#include "i2s_diag.h"
#include "log.h"
#include "hal_diag.h"
#include "i2s_types.h"
#include "i2s_dma_custom.h"
#include "stm32fx_hal.h"
//#include "stm32fx_hal_i2s_ex.h"

#ifdef HAS_DMA
#include "i2s_dma_custom.h"
#include "dma_mcal.h"
#endif

//#include "param_drv.h"

#ifdef HAS_DDS
#include "dds_config.h"
#include "dds_drv.h"
#endif

//#include "stm32fx_hal_rcc_ex.h"

#ifdef HAS_IIR
#include "iir_filter.h"
#include "iir_filter_config.h"
#endif

#ifdef HAS_DDS
#include "dds_drv.h"
#endif

#ifndef HAL_I2S_MODULE_ENABLED
#error "Add HAL_I2S_MODULE_ENABLED"
#endif

#ifndef HAS_I2S
#error "Add HAS_I2S"
#endif

static const I2sInfo_t I2sInfo[] = {
    {
        .num = 2,
        .I2Sx = SPI2,
        .irq_n = SPI2_IRQn,
        .CallBackTxHalf = NULL,
        .CallBackTxDone = NULL,
        .CallBackRxHalf = NULL,
        .CallBackRxDone = NULL,
        .dma_tx_irq_n = DMA1_Stream4_IRQn,
        .DmaInfoChannelTx = { .dma_num = 1, .stream=4, .channel = 0,  .name = "I2S2_TX", },
        .dma_rx_irq_n = DMA1_Stream3_IRQn,
        .DmaInfoChannelRx = { .dma_num = 1, .stream=3, .channel = 0,  .name = "I2S2_RX", },
        .valid = true,
    },
};

COMPONENT_GET_INFO( I2s)

bool i2s_load_params(I2sConfig_t* Config) {
    bool out_res = true;
    if(Config) {
        //LOAD_PARAM_V2(I2S, Config->ParamId.bus_role, Config->mode);
    }
    return out_res;
}

#if 0
    uint32_t periph_clk_code = 0;
    ClockBus_t cur_clock_bus = BUS_UNDEF;
    switch(num) {
    case 2:
    case 3:
        cur_clock_bus = CLOCK_BUS_APB1;
        break;
    case 1:
    case 4:
    case 5:
        cur_clock_bus = CLOCK_BUS_APB2;
        break;
    default:
        break;
    }
        periph_clk_code = I2sBus2Code(cur_clock_bus);
        LOG_INFO(I2S, "%u Init Bus:%s Clock", num, ClockBusToStr(cur_clock_bus));
        uint32_t freq_hz = HAL_RCCEx_GetPeriphCLKFreq(periph_clk_code);
        LOG_WARNING(I2S, "%u InitClock %s ClockBefore %fMHz", num, BusToStr(cur_clock_bus), HZ_2_MHZ(freq_hz));
#endif

bool i2s_clock_init(const uint8_t num) {
    bool res = false;
    HAL_StatusTypeDef ret = HAL_ERROR;
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    PeriphClkInitStruct.PLLI2S.PLLI2SN = 50;
    PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
    ret = HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
    res = HAL_retToRes(ret);

#if 0
        RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
        PeriphClkInitStruct.PLLI2S.PLLI2SQ = 2;
        PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
        PeriphClkInitStruct.PLLI2S.PLLI2SM = 4;
        PeriphClkInitStruct.PLLI2SSelection = RCC_PLLI2SCLKSOURCE_PLLSRC;
        ret = HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

        if(BUS_APB1 == cur_clock_bus) {
            PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_PLLI2S | RCC_PERIPHCLK_I2S_APB1;
            PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
            PeriphClkInitStruct.I2sApb1ClockSelection = RCC_I2SAPB1CLKSOURCE_PLLI2S;
        } else if(BUS_APB2 == cur_clock_bus) {
            PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_PLLI2S | RCC_PERIPHCLK_I2S_APB2;
            PeriphClkInitStruct.PLLI2S.PLLI2SN = 200;
            PeriphClkInitStruct.I2sApb2ClockSelection = RCC_I2SAPB2CLKSOURCE_PLLI2S;
        } else {
            res = false;
        }
        HAL_StatusTypeDef ret = HAL_ERROR;
        if(HAL_OK != ret) {
            res = false;
            I2sHandle_t* Node = I2sGetNode(num);
            if(Node) {
                Node->error_cnt++;
            }
            LOG_ERROR(I2S, "%u %s", ret, HalStatusToStr(ret));
        } else {
            LOG_INFO(I2S, "%u InitClockOk", num);
            res = true;
        }

        freq_hz = HAL_RCCEx_GetPeriphCLKFreq(periph_clk_code);
        LOG_NOTICE(I2S, "%s ClockAfter %fMHz", BusToStr(cur_clock_bus), HZ_2_MHZ(freq_hz));
#endif


    return res;
}

void HAL_I2S_MspInit(I2S_HandleTypeDef* i2sHandle) {
    // RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
#ifdef HAS_I2S1
    if(SPI1 == i2sHandle->Instance) {
        // I2sHandle_t* Node = I2sGetNode(1);
        bool res = i2s_clock_init(1);
        if(false == res) {
            LOG_ERROR(I2S, "1 ClockInitErr");
        }

        __HAL_RCC_SPI1_CLK_ENABLE();

#ifdef HAS_DMA
        DmaHandle_t* DmaNodeRx = DmaGetNode(DMA2_I2S1_RX);
        if(DmaNodeRx) {
            __HAL_LINKDMA(i2sHandle, hdmarx, DmaNodeRx->dma_h);
        }
#endif /*HAS_DMA*/

        HAL_NVIC_SetPriority(SPI1_IRQn, 14, 14);
        HAL_NVIC_EnableIRQ(SPI1_IRQn);
    }
#endif /*HAS_I2S1*/

#ifdef HAS_I2S2
    if(SPI2 == i2sHandle->Instance) {
        // I2sHandle_t* Node = I2sGetNode(2);
        bool res = i2s_clock_init(2);
        if(false == res) {
            LOG_ERROR(I2S, "2 ClockInitErr");
        } else {
            LOG_INFO(I2S, "I2S2 ClockInitOk");
        }

        __HAL_RCC_SPI2_CLK_ENABLE();

#if 0
        DmaHandle_t* DmaNodeTx = DmaGetNode(DMA1_I2S2_TX);
        if(DmaNodeTx) {
            __HAL_LINKDMA(i2sHandle, hdmatx, DmaNodeTx->dma_h);
        }
#ifdef HAS_I2S_RX
        DmaHandle_t* DmaNodeRx = DmaGetNode(DMA1_I2S2_RX);
        if(DmaNodeRx) {
            __HAL_LINKDMA(i2sHandle, hdmarx, DmaNodeRx->dma_h);
        }
#endif /*HAS_I2S_RX*/
#endif /*HAS_DMA1*/
       // HAL_NVIC_SetPriority(SPI2_IRQn, 14, 14);
       // HAL_NVIC_EnableIRQ(SPI2_IRQn);
    }
#endif /*HAS_I2S2*/

#ifdef HAS_I2S3
    if(SPI3 == i2sHandle->Instance) {
        I2sHandle_t* Node = I2sGetNode(3);
        bool res = i2s_clock_init(3);
        if(false == res) {
            LOG_ERROR(I2S, "3 ClockInitErr");
        }

        __HAL_RCC_SPI3_CLK_ENABLE();
#ifdef HAS_DMA
        DmaHandle_t* DmaNodeTx = DmaGetNode(DMAx_I2S3_TX);
        if(DmaNodeTx) {
            __HAL_LINKDMA(i2sHandle, hdmatx, DmaNodeTx->dma_h);
        }
        DmaHandle_t* DmaNodeRx = DmaGetNode(DMAx_I2S3_RX);
        if(DmaNodeTx) {
            __HAL_LINKDMA(i2sHandle, hdmarx, DmaNodeRx->dma_h);
        }
#endif /*HAS_DMA*/
        HAL_NVIC_SetPriority(SPI3_IRQn, 14, 14);
        HAL_NVIC_EnableIRQ(SPI3_IRQn);
    }
#endif /*HAS_I2S3*/

#ifdef HAS_I2S4
    if(SPI4 == i2sHandle->Instance) {
        // I2sHandle_t* Node = I2sGetNode(4);
        bool res = i2s_clock_init(4);
        if(false == res) {
            LOG_ERROR(I2S, "4 ClockInitErr");
        }

        __HAL_RCC_SPI4_CLK_ENABLE();
#ifdef HAS_DMA
        DmaHandle_t* DmaNodeTx = DmaGetNode(DMA2_I2S4_TX);
        if(DmaNodeTx) {
            __HAL_LINKDMA(i2sHandle, hdmatx, DmaNodeTx->dma_h);
        }
#endif /*HAS_DMA*/
        HAL_NVIC_SetPriority(SPI4_IRQn, 14, 14);
        HAL_NVIC_EnableIRQ(SPI4_IRQn);
    }
#endif /*HAS_I2S4*/

#ifdef HAS_I2S5
    if(SPI5 == i2sHandle->Instance) {
        I2sHandle_t* Node = I2sGetNode(5);
        bool res = i2s_clock_init(5);
        if(false == res) {
            LOG_ERROR(I2S, "5 ClockInitErr");
        }
        __HAL_RCC_SPI5_CLK_ENABLE();

#ifdef HAS_DMA
        DmaHandle_t* DmaNodeTx = DmaGetNode(DMAx_I2S5_TX);
        if(DmaNodeTx) {
            __HAL_LINKDMA(i2sHandle, hdmatx, DmaNodeTx->dma_h);
        }
        DmaHandle_t* DmaNodeRx = DmaGetNode(DMAx_I2S5_RX);
        if(DmaNodeTx) {
            __HAL_LINKDMA(i2sHandle, hdmarx, DmaNodeRx->dma_h);
        }
#endif /*HAS_DMA*/

        HAL_NVIC_SetPriority(SPI5_IRQn, 14, 14);
        HAL_NVIC_EnableIRQ(SPI5_IRQn);
    }
#endif /*HAS_I2S5*/
}

void HAL_I2S_MspDeInit(I2S_HandleTypeDef* i2sHandle) {
    LOG_DEBUG(I2S, "%s()", __FUNCTION__);
#ifdef HAS_I2S1
    if(SPI1 == i2sHandle->Instance) {
        __HAL_RCC_SPI1_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(SPI1_IRQn);
    }
#endif /*HAS_I2S1*/

#ifdef HAS_I2S2
    if(SPI2 == i2sHandle->Instance) {
        __HAL_RCC_SPI2_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(SPI2_IRQn);
    }
#endif /*HAS_I2S2*/

#ifdef HAS_I2S3
    if(SPI3 == i2sHandle->Instance) {
        __HAL_RCC_SPI3_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(SPI3_IRQn);
    }
#endif /*HAS_I2S3*/

#ifdef HAS_I2S4
    if(SPI4 == i2sHandle->Instance) {
        __HAL_RCC_SPI4_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(SPI4_IRQn);
    }
#endif /*HAS_I2S4*/

#ifdef HAS_I2S5
    if(SPI5 == i2sHandle->Instance) {
        __HAL_RCC_SPI5_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(SPI5_IRQn);
    }
#endif /*HAS_I2S5*/
}

/*words- 2xsample_cnt
 @param  Size number of data sample to be sent:
 @note   When a 16-bit data frame or a 16-bit data frame extended is selected during the I2S
         configuration phase, the Size parameter means the number of 16-bit data length
         in the transaction and when a 24-bit data frame or a 32-bit data frame is selected
         the Size parameter means the number of 24-bit or 32-bit data length*/
bool i2s_dma_write(uint8_t num, const uint16_t* const array, const  uint16_t words) {
    bool res = false;
    LOG_DEBUG(I2S, "I2S_%u,WriteDma,Words:%u", num, words);
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret = HAL_I2S_Transmit_DMA(&Node->handle, (uint16_t*) array, words);
        if(HAL_OK == ret) {
            res = true;
        } else {
            LOG_ERROR(I2S, "WrErr:%u %s", ret, HalStatusToStr(ret));
        }
    } else {
        LOG_ERROR(I2S, "%u NodeErr", num);
    }
    return res;
}

/*words- 2xsample_cnt*/
bool i2s_mcal_write(uint8_t num, const uint16_t* const array, const uint32_t words) {
    bool res = false;
    if(array) {
        if(words) {
          LOG_DEBUG(I2S, "I2S_%u,Write,Mem:%p,Words:%u", num, array, words);
          res = i2s_dma_write(num, (uint16_t*) array, words);
        }
    }
    return res;
}

bool i2s_read_write(uint8_t num, uint32_t tx_sample) {
    bool res = false;
#ifdef SPI_I2S_FULLDUPLEX_SUPPORT
    Type32Union_t un32;
    un32.u32 = tx_sample;
    LOG_DEBUG(I2S, "ReadWrite i2s:%u sample:0x%08x", num, tx_sample);
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {
        Node->tx_sample.u32[0] = un32.u16[0];
        Node->tx_sample.u32[1] = un32.u16[1];

        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_I2SEx_TransmitReceive_DMA(&Node->handle, (uint16_t*) &Node->tx_sample, (uint16_t*) &Node->rx_sample,
                2);
        if(HAL_OK != ret) {
            LOG_ERROR(I2S, "%u DmaTxRxErr %u %s", num, ret, HalStatusToStr(ret));
            Node->error_cnt++;
            res = false;
        } else {
            LOG_INFO(I2S, "%u DmaTxRxOk", num);
            res = true;
        }
    }
#endif /*SPI_I2S_FULLDUPLEX_SUPPORT*/
    return res;
}

bool i2s_mcal_read(uint8_t num, uint16_t* array, uint32_t words) {
    bool res = false;
    res = i2s_dma_read(num, array, words);
    return res;
}

static uint8_t i2s_get_sample_size_ll(SPI_TypeDef* I2sBaseAddr) {
    uint8_t sample_size = 0;
    RegI2sConfig_t RegCfg;
    RegCfg.reg_val = I2sBaseAddr->I2SCFGR;
    sample_size = I2sSampleBitness2bytes(RegCfg.datlen);
    return sample_size;
}

uint8_t i2s_get_sample_size(uint8_t num) {
    uint8_t sample_size = 0;
    SPI_TypeDef *I2sBaseAddr = I2sGetBaseAddr(num);
    if(I2sBaseAddr) {
        sample_size = i2s_get_sample_size_ll(I2sBaseAddr);
    }
    return sample_size;
}

bool i2s_send(uint8_t num, bool status) {
    bool res = true;
    LOG_ERROR(I2S, "ImplementLater");
    return res;
}

bool i2s_play_rx_tx(uint8_t num, uint8_t dac_num, bool status) {
    bool res = false;
#if defined(SPI_I2S_FULLDUPLEX_SUPPORT)
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {
#if 0
        Node->dac_num = 0;
        DdsHandle_t* Dds = DdsGetNode(dac_num);
        if(Dds) {
            LOG_DEBUG(I2S, "SpotDac %u", dac_num);
            Node->dac_num = dac_num;
            if(Dds->tx_sample_array && Dds->rx_sample_array && (0 < Dds->sample_cnt)) {
                LOG_DEBUG(I2S, "SpotRecord %u", dac_num);
                LOG_INFO(I2S, "Play %u samples", Dds->sample_cnt);
                HAL_StatusTypeDef ret = HAL_ERROR;
                Node->loopback = false;
                Node->play = status;
                if(Node->play) {
                    LOG_DEBUG(I2S, "StartPlay");
                    ret = HAL_I2SEx_TransmitReceive_DMA(&Node->handle, (uint16_t*)&Dds->tx_sample_array[0],
                                                        (uint16_t*)&Dds->rx_sample_array[0], Dds->sample_cnt);
                    if(HAL_OK != ret) {
                        Node->error_cnt++;
                        LOG_ERROR(I2S, "DmaTxRxErr %s", HalStatusToStr(ret));
                    } else {
                        LOG_INFO(I2S, "DmaTxRx" LOG_OK);
                        res = true;
                    }
                } else {
                    res = true;
                }
            } else {
                LOG_ERROR(I2S, "RecordErr");
            }
        } else {
            LOG_ERROR(I2S, "HandleErr");
        }
#else
        LOG_ERROR(I2S, "Add DDS component");
#endif /*HAS_DDS*/
    } else {
        LOG_ERROR(I2S, "HandleErr");
    }
#endif
    return res;
}

bool i2s_play_static_tx(uint8_t num, uint8_t dac_num, bool status) {
    bool res = false;
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {
#if 0
        Node->dac_num = 0;
        DdsHandle_t* Dds = dds_get_node(dac_num);
        if(Dds) {
            LOG_DEBUG(I2S, "SpotDac %u", dac_num);
            Node->dac_num = dac_num;
            LOG_INFO(I2S, "Play 48 samples");
            Node->loopback = false;
            Node->play = status;
            if(Node->play) {
                HAL_I2S_StateTypeDef state = HAL_I2S_GetState(&Node->handle);
                if(HAL_I2S_STATE_READY != state) {
                    LOG_WARNING(I2S, "DmaState:%s DmaStop", HalI2sStateToStr(state));
                    i2s_dma_stop(num);
                }

                HAL_StatusTypeDef ret = HAL_ERROR;
                LOG_INFO(I2S, "StartPlay1KHz");
                ret = HAL_I2S_Transmit_DMA(&Node->handle, (uint16_t*)Dds->tx_sample_static_array, 48 * 2);

                if(HAL_OK != ret) {
                    Node->error_cnt++;
                    LOG_ERROR(I2S, "DmaTxErr %s", HalStatusToStr(ret));
                } else {
                    LOG_INFO(I2S, "DmaTxOk %u Samples", Dds->sample_cnt);
                    res = true;
                }
            } else {
                res = true;
            }

        } else {
            LOG_ERROR(DDS, "HandleErr");
        }
#else
        LOG_ERROR(I2S, "Add DDS component");
#endif /*HAS_DDS*/
    } else {
        LOG_ERROR(I2S, "HandleErr");
    }
    return res;
}

#if 0
bool i2s_play_tx(uint8_t num, uint8_t dac_num, bool status) {
    bool res = false;
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {

#ifdef HAS_DDS
        Node->dac_num = 0;
        DdsHandle_t* Dds = dds_get_node(dac_num);
        if(Dds) {
            LOG_DEBUG(I2S, "SpotDac %u", dac_num);
            Node->dac_num = dac_num;
            if(Dds->sample_array && Dds->rx_sample_array && (0 < Dds->sample_cnt)) {
                LOG_DEBUG(I2S, "SpotRecord %u", dac_num);
                LOG_INFO(I2S, "Play %u samples", Dds->sample_cnt);
                HAL_StatusTypeDef ret = HAL_ERROR;
                Node->loopback = false;
                Node->play = status;
                if(Node->play) {
                    HAL_I2S_StateTypeDef state = HAL_I2S_GetState(&Node->handle);
                    if(HAL_I2S_STATE_READY != state) {
                        LOG_WARNING(I2S, "DmaState:%s DmaStop", HalI2sStateToStr(state));
                        i2s_dma_stop(num);
                    }

                    LOG_INFO(I2S, "StartPlay");
                    ret = HAL_I2S_Transmit_DMA(&Node->handle, (uint16_t*)Dds->sample_array,
                                               Dds->sample_cnt * 2);

                    // ret = HAL_I2S_Transmit_DMA(&Node->handle, (uint16_t*)&Dds->real_sample_array[0],
                    //                           Dds->sample_cnt );

                    if(HAL_OK != ret) {
                        Node->error_cnt++;
                        LOG_ERROR(I2S, "DmaTxErr %s", HalStatusToStr(ret));
                    } else {
                        LOG_INFO(I2S, "DmaTxOk %u Samples", Dds->sample_cnt);
                        res = true;
                    }
                } else {
                    res = true;
                }
            } else {
                LOG_ERROR(I2S, "TrackErr");
            }
        } else {
            LOG_ERROR(I2S, "HandleErr");
        }
#else
        LOG_ERROR(I2S, "Add DDS component");
#endif
    } else {
        LOG_ERROR(I2S, "HandleErr");
    }
    return res;
}
#endif

bool i2s_read_sample(uint8_t num, uint32_t size) {
    bool res = false;
    LOG_DEBUG(I2S, "I2S%u Read %u Samples", num, size);
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_I2S_Receive_DMA(&Node->handle, (uint16_t*) &Node->rx_sample.u32[0], size);
        if(HAL_OK != ret) {
            Node->error_cnt++;
            LOG_ERROR(I2S, "RxDmaErr: %u %s", ret, HalStatusToStr(ret));
        } else {
            LOG_INFO(I2S, "RxDma" LOG_OK);
            res = true;
        }
    } else {
        LOG_ERROR(I2S, "NodeErr");
    }
    return res;
}

bool i2s_stop(uint8_t num) {
    bool res = i2s_dma_stop(num);
    return res;
}

bool i2s_isr_loopback(I2sHandle_t* Node) {
    bool res = false;
    if(Node->loopback) {
#ifdef SPI_I2S_FULLDUPLEX_SUPPORT
        HAL_StatusTypeDef ret = HAL_ERROR;
        (void) ret;
        ret = HAL_I2SEx_TransmitReceive_DMA(&Node->handle, (uint16_t*) &Node->tx_sample.u32[0],
                (uint16_t*) &Node->rx_sample.u32[0], 2);
        if(HAL_OK != ret) {
            Node->error_cnt++;
        }
#endif
    }
    return res;
}

uint32_t i2s_get_sample_rate(uint8_t num) {
    uint32_t sample_rate = 0;
    const I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {
        sample_rate = Node->audio_frequency_hz;
    }
    return sample_rate;
}

bool i2s_config_tx(uint8_t i2s_num, uint8_t word_size, uint8_t channels, uint32_t audio_freq) {
    return false;
}

bool i2s_loopback_shared_memory(uint8_t i2s_num, uint32_t words_num) {
    return false;
}

bool i2s_loopback(uint8_t i2s_num, uint32_t words_num) {
    return false;
}

static bool i2s_init_hal(const I2sConfig_t* const Config, I2S_InitTypeDef* const pInit) {
    bool res = false;
    if(Config) {
        if(pInit) {
            pInit->AudioFreq = I2sParseAudioFreq(Config->audio_frequency_hz);
            pInit->ClockSource = I2sParseClockSource(Config->clock_source); // I2S_CLOCK_PLL;
            pInit->CPOL = I2sParseCPol(Config->cpol); // I2S_CPOL_LOW;
            pInit->DataFormat = I2sParseDataFormat(Config->data_format);
            pInit->FullDuplexMode = I2sParseFullDuplexMode(Config->full_duplex);
            pInit->Mode = I2sDirRoleToMode(Config->bus_role, Config->direction);
            pInit->MCLKOutput = I2sParseMCLKOutput(Config->mclk_out);
            pInit->Standard = I2sParseStandard(Config->standard);
            res = true;
        }
    }
    return res;
}

bool i2s_init_node(I2sHandle_t* const Node) {
    bool res = false;
    if(Node) {
        memset((void*) Node->tx_sample.u8, 0, sizeof(Node->tx_sample));
        memset((void*) Node->rx_sample.u8, 0, sizeof(Node->rx_sample));
        Node->tx_cnt = 0;
        Node->rx_cnt = 0;
        Node->echo = false;
        Node->tx_half_cnt = 0;
        Node->rx_half_cnt = 0;
        res = true;
    }
    return res;
}



bool i2s_vefify_one(const uint8_t num) {
    bool res = true;
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_I2SEx_TransmitReceive_DMA(&Node->handle,
                                            (uint16_t*) &Node->tx_sample,
                                            (uint16_t*) &Node->rx_sample,
                                             2);
        res = HAL_retToRes(ret);
        if(!res) {
            Node->error_cnt++;
            res = false;
        }
    }
    return res;
}

bool i2s_gpio_set_read(const uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node){
        res = gpio_init_one(&Node->GpioLrCk);
        res = gpio_init_one(&Node->GpioSck);
        res = gpio_init_one(&Node->GpioSdIn);
#ifdef HAS_I2S_MCL
        res = gpio_init_input(Node->GpioMClk.Pad);
        res = gpio_pad_mux_set(Node->GpioMClk.Pad,0);
#endif

        res = gpio_init_input(Node->GpioSdOut.Pad);

        res = gpio_pad_mux_set(Node->GpioSdOut.Pad,0);

    }
    return res;
}


bool i2s_gpio_set_write(const uint8_t num){
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node){

        res = gpio_init_one(&Node->GpioLrCk);
        res = gpio_init_one(&Node->GpioSck);
        res = gpio_init_one(&Node->GpioSdOut);
#ifdef HAS_I2S_MCL
        res = gpio_init_input(Node->GpioMClk.Pad);
#endif
        res = gpio_init_input(Node->GpioSdIn.Pad);
        res = gpio_pad_mux_set(Node->GpioSdIn.Pad,0);
    }
    return res;
}

bool i2s_interrupt_ctrl(const uint8_t num, bool on_off){
    bool res = false;
    const I2sInfo_t *Info = I2sGetInfo(num);
    if(Info) {
        res = true;
        res = interrupt_control(Info->irq_n,   on_off)&&res;
        res = interrupt_control(Info->dma_tx_irq_n,   on_off) &&res;
        res = interrupt_control(Info->dma_rx_irq_n,   on_off) &&res;
    }
    return res;
}

static bool i2s_init_one_ll(const I2sConfig_t* const Config, I2sHandle_t* const Node) {
    bool res = false;
    res = i2s_is_valid_config(Config);
    if(res) {
        LOG_INFO(I2S, "%u init", Config->num);
        if(Node) {
            const I2sInfo_t *Info = I2sGetInfo(Config->num);
            if(Info) {
                Node->handle.Instance = Info->I2Sx;
                res = i2s_init_common(Config, Node);
                res = i2s_init_node(Node);
                res = i2s_init_hal(Config, &Node->handle.Init);
                // res = i2s_dma_init(Config, Node, Info);

#ifdef HAS_I2S_DMA
                Node->CallBackTxHalf = Info->CallBackTxHalf;
                Node->CallBackTxDone = Info->CallBackTxDone;
                Node->CallBackRxHalf = Info->CallBackRxHalf;
                Node->CallBackRxDone = Info->CallBackRxDone;
#endif

                HAL_StatusTypeDef ret = HAL_ERROR;
                ret = HAL_I2S_Init(&Node->handle);
                res = HAL_retToRes(ret);
                if(res) {
                    Node->init_done = true;
#ifdef HAS_I2S_DMA
                    res = i2s_dma_init(Config->num);
#endif
                    //res = i2s_vefify_one(Config->num);
                    LOG_INFO(I2S, "I2S%u initOk", Config->num);
                } else {
                    Node->error_cnt++;
                    LOG_ERROR(I2S, "%u initErr", Config->num);
                    res = false;
                }
            } else {
                LOG_ERROR(I2S, "%u InfoErr", Config->num);
                res = false;
            }
        } else {
            LOG_ERROR(I2S, "%u HandleErr", Config->num);
            res = false;
        }
    } else {
        LOG_DEBUG(I2S, "%u ConfigErr", Config->num);
        res = false;
    }
    return res;
}

bool i2s_audio_frequency_set(const uint8_t num, const uint32_t audio_frequency_hz) {
    bool res = false;
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {
        LOG_INFO(I2S, "I2S_%u,Set,AudioFreq:%u Hz", num, audio_frequency_hz);
        Node->NewConfig.audio_frequency_hz = audio_frequency_hz;
        Node->audio_frequency_hz = audio_frequency_hz;
        res = i2s_init_one_ll(&Node->NewConfig, Node);
    }
    return res;
}

bool i2s_audio_set_data_dirrection(const uint8_t num,
                                   const IfOperation_t operation) {
    bool res = false;
    I2sHandle_t *Node = I2sGetNode(num);
    if (Node) {
        LOG_INFO(I2S, "I2S_%u,Set,Operation:%s", num, IfOperationToStr(operation));
        const I2sConfig_t *Config = I2sGetConfig(num);
        if (Config) {
            memcpy(&Node->NewConfig, Config, sizeof(I2sConfig_t));
            Node->NewConfig.direction = I2SOperationToDirection(operation);
            Node->direction = I2SOperationToDirection(operation);
            res = i2s_init_one_ll(&Node->NewConfig, Node);
        }
    }
    return res;
}

bool i2s_init_one(const uint8_t num) {
    bool res = false;
    LOG_INFO(I2S, "I2S_%u,Init", num);
    const I2sConfig_t *Config = I2sGetConfig(num);
    if(Config) {
        I2sHandle_t* Node = I2sGetNode(num);
        if(Node) {
            memcpy(&Node->NewConfig, Config, sizeof(I2sConfig_t));
            res = i2s_init_one_ll(Config, Node) ;
        }
    }
    return res;
}

