#include "i2s_drv.h"

#include <stdbool.h>
#include <string.h>

#include "clock_const.h"
#include "clock_custom_diag.h"
#include "clock_diag.h"
#include "clock_stm_const.h"
#include "clock_utils.h"
#include "i2s_config.h"
#include "i2s_custom_diag.h"
#include "i2s_custom_drv.h"
#include "i2s_custom_types.h"
#include "i2s_diag.h"
#include "log.h"
#include "at32f435_437_i2s_ex.h"

#ifdef HAS_DMA
#include "dma_mcal.h"
#endif /*HAS_DMA*/

#include "param_drv.h"

#ifdef HAS_SW_DAC
#include "sw_dac_config.h"
#include "sw_dac_drv.h"
#endif /*HAS_SW_DAC*/

#include "hal_diag.h"
#include "i2s_types.h"
#include "at32f435_437.h"
#include "at32f435_437_rcc_ex.h"

#ifdef HAS_IIR
#include "iir_filter.h"
#include "iir_filter_config.h"
#endif /*HAS_IIR*/

#ifdef HAS_SW_DAC
#include "sw_dac_drv.h"
#endif /*HAS_SW_DAC*/

#ifndef HAL_I2S_MODULE_ENABLED
#error "Add HAL_I2S_MODULE_ENABLED"
#endif /*HAL_I2S_MODULE_ENABLED*/

#ifndef HAS_I2S
#error "Add HAS_I2S"
#endif /*HAS_I2S*/

static int8_t get_i2s_index(SPI_TypeDef* I2Sx) {
    int8_t num = -1;
#ifdef SPI1
    if(SPI1 == I2Sx) {
        num = 1;
    }
#endif /*SPI1*/

#ifdef SPI2
    if(SPI2 == I2Sx) {
        num = 2;
    }
#endif /*SPI2*/

#ifdef SPI3
    if(SPI3 == I2Sx) {
        num = 3;
    }
#endif /*SPI2*/

#ifdef SPI4
    if(SPI4 == I2Sx) {
        num = 4;
    }
#endif /*SPI4*/

#ifdef SPI5
    if(SPI5 == I2Sx) {
        num = 5;
    }
#endif /*SPI5*/

#ifdef SPI6
    if(SPI6 == I2Sx) {
        num = 6;
    }
#endif /*SPI6*/

    return num;
}

SPI_TypeDef* I2sGetBaseAddr(uint8_t num) {
    SPI_TypeDef* I2Sx = NULL;
    switch(num) {
#ifdef SPI1
    case 1:
        I2Sx = SPI1;
        break;
#endif /*I2S1*/

#ifdef SPI2
    case 2:
        I2Sx = SPI2;
        break;
#endif /*I2S2*/

#ifdef SPI3
    case 3:
        I2Sx = SPI3;
        break;
#endif /*I2S3*/

#ifdef SPI4
    case 4:
        I2Sx = SPI4;
        break;
#endif /*I2S4*/

#ifdef SPI5
    case 5:
        I2Sx = SPI5;
        break;
#endif /*I2S5*/

#ifdef SPI6
    case 6:
        I2Sx = SPI6;
        break;
#endif /*I2S6*/
    default:
        I2Sx = NULL;
        break;
    }
    return I2Sx;
}

static uint32_t ParseAudioFreq(AudioFreq_t audio_freq) {
    uint32_t code = 0xFFFFFFFF;
    switch(audio_freq) {
    case I2S_AUDIO_FREQ_192K:
        code = I2S_AUDIOFREQ_192K;
        break;
    case I2S_AUDIO_FREQ_96K:
        code = I2S_AUDIOFREQ_96K;
        break;
    case I2S_AUDIO_FREQ_48K:
        code = I2S_AUDIOFREQ_48K;
        break;
    case I2S_AUDIO_FREQ_44K:
        code = I2S_AUDIOFREQ_44K;
        break;
    case I2S_AUDIO_FREQ_32K:
        code = I2S_AUDIOFREQ_32K;
        break;
    case I2S_AUDIO_FREQ_22K:
        code = I2S_AUDIOFREQ_22K;
        break;
    case I2S_AUDIO_FREQ_16K:
        code = I2S_AUDIOFREQ_16K;
        break;
    case I2S_AUDIO_FREQ_11K:
        code = I2S_AUDIOFREQ_11K;
        break;
    case I2S_AUDIO_FREQ_8K:
        code = I2S_AUDIOFREQ_8K;
        break;
    case I2S_AUDIO_FREQ_DEFAULT:
        code = I2S_AUDIOFREQ_DEFAULT;
        break;
    default:
        code = 0xFFFFFFFF;
        break;
    }
    return code;
}

static uint32_t ParseClockSource(ClockSource_t clock_source) {
    uint32_t code = 0xFFFFFFFF;
    switch(clock_source) {
    case I2S_CLK_PLL:
        code = I2S_CLOCK_PLL;
        break;
    case I2S_CLK_EXT:
        code = I2S_CLOCK_EXTERNAL;
        break;
    default:
        code = 0xFFFFFFFF;
        break;
    }
    return code;
}

static uint32_t ParseCPol(Cpol_t cpol) {
    uint32_t code = 0xFFFFFFFF;
    switch(cpol) {
    case I2S_CLOCK_POL_LOW:
        code = I2S_CPOL_LOW;
        break;
    case I2S_CLOCK_POL_HIGH:
        code = I2S_CPOL_HIGH;
        break;
    default:
        code = 0xFFFFFFFF;
        break;
    }
    return code;
}

static uint32_t ParseDataFormat(I2sDataFormat_t data_format) {
    uint32_t code = 0xFFFFFFFF;
    switch(data_format) {
    case I2S_DATA_FORMAT_16B:
        code = I2S_DATAFORMAT_16B;
        break;
    case I2S_DATA_FORMAT_16B_EXTENDED:
        code = I2S_DATAFORMAT_16B_EXTENDED;
        break;
    case I2S_DATA_FORMAT_24B:
        code = I2S_DATAFORMAT_24B;
        break;
    case I2S_DATA_FORMAT_32B:
        code = I2S_DATAFORMAT_32B;
        break;
    default:
        break;
    }
    return code;
}

static uint32_t ParseFullDuplexMode(FullDuplex_t full_duplex) {
    uint32_t code = 0xFFFFFFFF;
    switch(full_duplex) {
    case FULL_DUPLEX_OFF:
        code = I2S_FULLDUPLEXMODE_DISABLE;
        break;
    case FULL_DUPLEX_ON:
        code = I2S_FULLDUPLEXMODE_ENABLE;
        break;
    default:
        break;
    }
    return code;
}

static uint32_t ParseBusMode(I2sRole_t mode) {
    uint32_t code = 0xFFFFFFFF;
    switch((uint8_t)mode) {
    case I2SMODE_SLAVE_TX:
        code = I2S_MODE_SLAVE_TX;
        break;
    case I2SMODE_SLAVE_RX:
        code = I2S_MODE_SLAVE_RX;
        break;
    case I2SMODE_MASTER_TX:
        code = I2S_MODE_MASTER_TX;
        break;
    case I2SMODE_MASTER_RX:
        code = I2S_MODE_MASTER_RX;
        break;
    default:
        break;
    }
    return code;
}

static uint32_t ParseMCLKOutput(MclkOut_t mclk_out) {
    uint32_t code = 0xFFFFFFFF;
    switch(mclk_out) {
    case I2S_MCLKOUT_ON:
        code = I2S_MCLKOUTPUT_ENABLE;
        break;
    case I2S_MCLKOUT_OFF:
        code = I2S_MCLKOUTPUT_DISABLE;
        break;
    default:
        break;
    }
    return code;
}

static uint32_t ParseStandard(Standard_t standard) {
    uint32_t code = 0xFFFFFFFF;
    switch(standard) {
    case I2S_STD_PHILIPS:
        code = I2S_STANDARD_PHILIPS;
        break;
    case I2S_STD_MSB:
        code = I2S_STANDARD_MSB;
        break;
    case I2S_STD_LSB:
        code = I2S_STANDARD_LSB;
        break;
    case I2S_STD_PCM_SHORT:
        code = I2S_STANDARD_PCM_SHORT;
        break;
    case I2S_STD_PCM_LONG:
        code = I2S_STANDARD_PCM_LONG;
        break;
    default:
        break;
    }
    return code;
}

static bool i2s_load_params(I2sConfig_t* Config) {
    bool out_res = true;
    if(Config) {
        LOAD_PARAM_V2(I2S, Config->ParamId.bus_role, Config->mode);
    }
    return out_res;
}

static uint32_t I2sBus2Code(ClockBus_t CurBus) {
    uint32_t periph_clk_code = 0;
    switch(CurBus) {
    case BUS_APB1:
        periph_clk_code = RCC_PERIPHCLK_I2S_APB1;
        break;
    case BUS_APB2:
        periph_clk_code = RCC_PERIPHCLK_I2S_APB2;
        break;
    default:
        break;
    }
    return periph_clk_code;
}

static bool i2s_clock_init(uint8_t num) {
    bool res = false;
    uint32_t periph_clk_code = 0;
    ClockBus_t CurBus = BUS_UNDEF;
    switch(num) {
    case 2:
    case 3:
        CurBus = BUS_APB1;
        break;
    case 1:
    case 4:
    case 5:
        CurBus = BUS_APB2;
        break;
    default:
        break;
    }

    if(BUS_UNDEF != CurBus) {
        LOG_INFO(I2S, "%u Init Bus:%s Clock", num, Bus2Str(CurBus));

        periph_clk_code = I2sBus2Code(CurBus);

        uint32_t freq_hz = HAL_RCCEx_GetPeriphCLKFreq(periph_clk_code);
        LOG_WARNING(I2S, "%u InitClock %s ClockBefore %fMHz", num, Bus2Str(CurBus), HZ_2_MHZ(freq_hz));
        RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
        PeriphClkInitStruct.PLLI2S.PLLI2SQ = 2;
        PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
        PeriphClkInitStruct.PLLI2S.PLLI2SM = 4;
#if defined(AT32F412Zx) || defined(AT32F412Vx) || defined(AT32F412Rx) || defined(AT32F412Cx) ||                    \
    defined(AT32F413xx) || defined(AT32F423xx)
        PeriphClkInitStruct.PLLI2SSelection = RCC_PLLI2SCLKSOURCE_PLLSRC;
#endif

        if(BUS_APB1 == CurBus) {
            PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_PLLI2S | RCC_PERIPHCLK_I2S_APB1;
            PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
            PeriphClkInitStruct.I2sApb1ClockSelection = RCC_I2SAPB1CLKSOURCE_PLLI2S;
        } else if(BUS_APB2 == CurBus) {
            PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_PLLI2S | RCC_PERIPHCLK_I2S_APB2;
            PeriphClkInitStruct.PLLI2S.PLLI2SN = 200;
            PeriphClkInitStruct.I2sApb2ClockSelection = RCC_I2SAPB2CLKSOURCE_PLLI2S;
        } else {
            res = false;
        }
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
        if(HAL_OK != ret) {
            res = false;
            I2sHandle_t* Node = I2sGetNode(num);
            if(Node) {
                Node->error_cnt++;
            }
            LOG_ERROR(I2S, "%u %s", ret, HalStatus2Str(ret));
        } else {
            LOG_INFO(I2S, "%u InitClockOk", num);
            res = true;
        }

        freq_hz = HAL_RCCEx_GetPeriphCLKFreq(periph_clk_code);
        LOG_NOTICE(I2S, "%s ClockAfter %fMHz", Bus2Str(CurBus), HZ_2_MHZ(freq_hz));
    }

    return res;
}

bool i2s_init_ll(uint8_t num) {
    bool res = true;
    LOG_INFO(I2S, "%u init", num);
    SPI_TypeDef* I2Sx = NULL;
    I2sHandle_t* Node = I2sGetNode(num);
    const I2sConfig_t* Config = NULL;
    HAL_StatusTypeDef ret = HAL_ERROR;
    if(Node) {
        I2Sx = I2sGetBaseAddr(num);
        if(I2Sx) {
            Config = I2sGetConfNode(num);
            if(Config) {
                res = true;
            } else {
                LOG_ERROR(I2S, "%u ConfigErr", num);
                res = false;
            }
        } else {
            LOG_ERROR(I2S, "%u InstanceErr", num);
            res = false;
        }
    } else {
        LOG_ERROR(I2S, "%u HandleErr", num);
        res = false;
    }

    if(res) {
        // res = i2s_load_params(Config);
        memset((void*)Node->tx_sample.u8, 0, sizeof(Node->tx_sample));
        memset((void*)Node->rx_sample.u8, 0, sizeof(Node->rx_sample));
        Node->tx_cnt = 0;
        Node->rx_cnt = 0;
        Node->rx_buff = NULL;
        Node->rx_buff_size = 0;
        Node->echo = false;
        Node->tx_half_cnt = 0;
        Node->rx_half_cnt = 0;
        Node->i2s_h.Instance = I2Sx;
        Node->i2s_h.Init.AudioFreq = ParseAudioFreq(Config->audio_freq);
        Node->i2s_h.Init.ClockSource = ParseClockSource(Config->clock_source); // I2S_CLOCK_PLL;
        Node->i2s_h.Init.CPOL = ParseCPol(Config->cpol);                       // I2S_CPOL_LOW;
        Node->i2s_h.Init.DataFormat = ParseDataFormat(Config->data_format);
        Node->i2s_h.Init.FullDuplexMode = ParseFullDuplexMode(Config->full_duplex);
        Node->i2s_h.Init.Mode = ParseBusMode(Config->mode);
        Node->i2s_h.Init.MCLKOutput = ParseMCLKOutput(Config->mclk_out);
        Node->i2s_h.Init.Standard = ParseStandard(Config->standard);

        ret = HAL_I2S_Init((I2S_HandleTypeDef*)&Node->i2s_h);
        if(HAL_OK == ret) {
            res = true;
            Node->init_done = true;
#if 0
            ret =  HAL_I2SEx_TransmitReceive_DMA(&Node->i2s_h,
                                                (uint16_t *)&Node->tx_sample,
                                                (uint16_t *)&Node->rx_sample,2);
            if(HAL_OK!=ret) {
                Node->error_cnt++;
                res = false;
            }
#endif
            LOG_INFO(I2S, "I2S%u initOk", num);
        } else {
            Node->error_cnt++;
            LOG_ERROR(I2S, "%u initErr", num);
            res = false;
        }
    }
    return res;
}

bool i2s_init(void) {
    bool res = true;
    LOG_DEBUG(I2S, "init");
    set_log_level(I2S, LOG_LEVEL_NOTICE);

    uint32_t cnt = i2s_get_cnt();
    memcpy(&I2sConfig[0], &I2sConfigLuT[0], cnt * sizeof(I2sConfig_t));

#ifdef HAS_I2S1
    res = i2s_init_ll(1) && res;
#endif /*HAS_I2S1*/

#ifdef HAS_I2S2
    res = i2s_init_ll(2) && res;
#endif /*HAS_I2S2*/

#ifdef HAS_I2S3
    res = i2s_init_ll(3) && res;
#endif /*HAS_I2S3*/

#ifdef HAS_I2S4
    res = i2s_init_ll(4) && res;
#endif /*HAS_I2S4*/

#ifdef HAS_I2S5
    res = i2s_init_ll(5) && res;
#endif /*HAS_I2S5*/
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

#ifdef HAS_DMA1
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
        HAL_NVIC_SetPriority(SPI2_IRQn, 14, 14);
        HAL_NVIC_EnableIRQ(SPI2_IRQn);
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

static bool i2s_write_wait(uint8_t num, uint16_t* array, uint16_t words) {
    bool res = false;
    LOG_DEBUG(I2S, "WriteWait i2s:%u Words:%u", num, words);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        uint32_t init_tx_cnt = Node->tx_cnt;
        HAL_StatusTypeDef ret = HAL_I2S_Transmit_DMA(&Node->i2s_h, (uint16_t*)array, words);
        if(HAL_OK == ret) {
            res = true;
            uint32_t cnt = 0;
            while(init_tx_cnt == Node->tx_cnt) {
                cnt++;
                if(0x006FFFFF < cnt) {
                    LOG_ERROR(I2S, "%u WrTimeOut", num);
                    res = false;
                    break;
                }
            }
        } else {
            LOG_ERROR(I2S, "WrErr:%u %s", ret, HalStatus2Str(ret));
        }
    } else {
        LOG_ERROR(I2S, "%u NodeErr", num);
    }
    return res;
}

bool i2s_api_write(uint8_t num, uint16_t* array, size_t words) {
    bool res = false;
    LOG_DEBUG(I2S, "Write i2s:%u Words:%u", num, words);
    res = i2s_write_wait(num, (uint16_t*)array, words);
    return res;
}

bool i2s_read_write(uint8_t num, uint32_t tx_sample) {
    bool res = false;
#ifdef SPI_I2S_FULLDUPLEX_SUPPORT
    Type32Union_t un32;
    un32.u32 = tx_sample;
    LOG_DEBUG(I2S, "ReadWrite i2s:%u sample:0x%08x", num, tx_sample);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->tx_sample.u32[0] = un32.u16[0];
        Node->tx_sample.u32[1] = un32.u16[1];

        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_I2SEx_TransmitReceive_DMA(&Node->i2s_h, (uint16_t*)&Node->tx_sample, (uint16_t*)&Node->rx_sample, 2);
        if(HAL_OK != ret) {
            LOG_ERROR(I2S, "%u DmaTxRxErr %u %s", num, ret, HalStatus2Str(ret));
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

bool i2s_api_read(uint8_t num, uint32_t* array, size_t words) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        uint32_t init_rx_cnt = Node->rx_cnt;
        HAL_StatusTypeDef ret = HAL_I2S_Receive_DMA(&Node->i2s_h, (uint16_t*)array, words);
        if(HAL_OK == ret) {
            res = true;
            uint32_t cnt = 0;
            while(init_rx_cnt == Node->rx_cnt) {
                cnt++;
                if(0x008FFFFF < cnt) {
                    LOG_ERROR(I2S, "RdTimeOut");
                    res = false;
                    break;
                }
            }
        } else {
            LOG_ERROR(I2S, "ReadErr:%u %s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef* hi2s) {
    int8_t num = 0;
    num = get_i2s_index(hi2s->Instance);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->tx_half_cnt++;
        Node->tx_half_int = true;
    }
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef* hi2s) {
    int8_t num = 0;
    num = get_i2s_index(hi2s->Instance);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->tx_cnt++;
        Node->tx_int = true;
    }
}

void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef* hi2s) {
    int8_t num = 0;
    num = get_i2s_index(hi2s->Instance);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->rx_half_cnt++;
        Node->rx_half_int = true;
    }
}

void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef* hi2s) {
    int8_t num = 0;
    num = get_i2s_index(hi2s->Instance);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->rx_cnt++;
#if 0
        uint8_t sample_size = i2s_get_sample_size(num);
        uint16_t sample = Node->rx_sample[0];
        Node->rx_sample_fixed[0]=sample;
        Node->rx_sample_fixed[1]=sample;
#endif
        memcpy((void*)&Node->rx_sample_fixed.u8[0], (void*)&Node->rx_sample.u8[0], 8);
#ifdef HAS_I2S_ECHO
        if(Node->echo) {
            HAL_StatusTypeDef ret = HAL_ERROR;
            (void)ret;
            memcpy((void*)Node->tx_sample, (void*)Node->rx_sample, sizeof(Node->tx_sample));
#ifdef SPI_I2S_FULLDUPLEX_SUPPORT
            ret =
                HAL_I2SEx_TransmitReceive_DMA(&Node->i2s_h, (uint16_t*)Node->tx_sample, (uint16_t*)Node->rx_sample, 2);
            if(HAL_OK != ret) {
                Node->error_cnt++;
            }
#endif /*SPI_I2S_FULLDUPLEX_SUPPORT*/
        }
#endif /*HAS_I2S_ECHO*/
    }
}

void HAL_I2S_ErrorCallback(I2S_HandleTypeDef* hi2s) {
    int8_t num = 0;
    num = get_i2s_index(hi2s->Instance);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->error_cnt++;
        memcpy((void*)&Node->tx_sample.u8[0], (void*)&Node->rx_sample.u8[0], sizeof(Node->tx_sample));
        Node->tx_sample.u64 = 0x5555;
        Node->rx_sample.u64 = 0x0000;
#ifdef SPI_I2S_FULLDUPLEX_SUPPORT
        __HAL_I2SEXT_CLEAR_OVRFLAG(&Node->i2s_h);
#endif
    }
}

void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef* hi2s) {
    int8_t num = 0;
    num = get_i2s_index(hi2s->Instance);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->tx_half_cnt++;
        Node->tx_half_int = true;
        Node->rx_half_cnt++;
        Node->rx_half_int = true;
    }
}

void HAL_I2SEx_TxRxCpltCallback(I2S_HandleTypeDef* hi2s) {
    int8_t num = 0;
    num = get_i2s_index(hi2s->Instance);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->tx_cnt++;
        Node->rx_cnt++;
        Node->tx_int = true;
        Node->rx_int = true;
        // uint8_t sample_size=i2s_get_sample_size(num);
        memcpy((void*)&Node->rx_sample_fixed.u8[0], (void*)&Node->rx_sample.u8[0], 8);
#ifdef HAS_I2S_ECHO
        if(Node->echo) {
            memcpy((void*)Node->tx_sample, (void*)Node->rx_sample, sizeof(Node->tx_sample));
        }
#endif /*HAS_I2S_ECHO*/
#ifdef HAS_SW_DAC
        if(Node->dac) {
            SampleType_t dac_val = 0;
            bool res = sw_dac_proc(DAC_I2S_NUM, &dac_val);
            if(res) {
                Node->tx_sample.u32[0] = dac_val;
                Node->tx_sample.u32[1] = dac_val;
            }
        }
#endif /*HAS_SW_DAC*/

#ifdef HAS_IIR
        if(Node->iir) {
            int16_t iir_val = 0;
            bool res = iir_filt_proc(IIF_FILT_ECHO_NUM, (int16_t)Node->rx_sample[0], &iir_val);
            if(res) {
                Node->tx_sample.u32[0] = (uint16_t)iir_val;
                Node->tx_sample.u32[1] = (uint16_t)iir_val;
            }
        }
#endif /*HAS_IIR*/
        HAL_StatusTypeDef ret = HAL_ERROR;
        (void)ret;
        if(Node->loopback) {
#ifdef SPI_I2S_FULLDUPLEX_SUPPORT
            ret = HAL_I2SEx_TransmitReceive_DMA(&Node->i2s_h, (uint16_t*)&Node->tx_sample.u32[0],
                                                (uint16_t*)&Node->rx_sample.u32[0], 2);
            if(HAL_OK != ret) {
                Node->error_cnt++;
            }
#endif
        }
    }
}

static uint8_t I2sSampleBitness2bytes(Stm32I2sDatLen_t code) {
    uint8_t num_bytes = 0;
    switch((uint8_t)code) {
    case I2S_DAT_LEN16_BIT:
        num_bytes = 2;
        break;
    case I2S_DAT_LEN24_BIT:
        num_bytes = 4;
        break;
    case I2S_DAT_LEN32_BIT:
        num_bytes = 4;
        break;
    case I2S_DAT_NOT_ALLOWED:
        num_bytes = 0;
        break;

    default:
        num_bytes = 0;
        break;
    }
    return num_bytes;
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
    SPI_TypeDef* I2sBaseAddr = I2sGetBaseAddr(num);
    if(I2sBaseAddr) {
        sample_size = i2s_get_sample_size_ll(I2sBaseAddr);
    }
    return sample_size;
}

bool i2s_play_rx_tx(uint8_t num, uint8_t dac_num, bool status) {
    bool res = false;
#if defined(SPI_I2S_FULLDUPLEX_SUPPORT)
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
#ifdef HAS_SW_DAC
        Node->dac_num = 0;
        SwDac_t* DacNode = sw_dac_get_node(dac_num);
        if(DacNode) {
            LOG_DEBUG(I2S, "SpotDac %u", dac_num);
            Node->dac_num = dac_num;
            if(DacNode->tx_sample_array && DacNode->rx_sample_array && (0 < DacNode->sample_cnt)) {
                LOG_DEBUG(I2S, "SpotRecord %u", dac_num);
                LOG_INFO(I2S, "Play %u samples", DacNode->sample_cnt);
                HAL_StatusTypeDef ret = HAL_ERROR;
                Node->loopback = false;
                Node->play = status;
                if(Node->play) {
                    LOG_DEBUG(I2S, "StartPlay");
                    ret = HAL_I2SEx_TransmitReceive_DMA(&Node->i2s_h, (uint16_t*)&DacNode->tx_sample_array[0],
                                                        (uint16_t*)&DacNode->rx_sample_array[0], DacNode->sample_cnt);
                    if(HAL_OK != ret) {
                        Node->error_cnt++;
                        LOG_ERROR(I2S, "DmaTxRxErr %s", HalStatus2Str(ret));
                    } else {
                        LOG_INFO(I2S, "DmaTxRx" LOG_OK);
                        res = true;
                    }
                } else {
                    res = true;
                }
            } else {
                LOG_ERROR(LG_DAC, "RecordErr");
            }
        } else {
            LOG_ERROR(LG_DAC, "HandleErr");
        }
#else
        LOG_ERROR(I2S, "Add SW_DAC component");
#endif /*HAS_SW_DAC*/
    } else {
        LOG_ERROR(I2S, "HandleErr");
    }
#endif
    return res;
}

bool i2s_play_static_tx(uint8_t num, uint8_t dac_num, bool status) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
#ifdef HAS_SW_DAC
        Node->dac_num = 0;
        SwDac_t* DacNode = sw_dac_get_node(dac_num);
        if(DacNode) {
            LOG_DEBUG(I2S, "SpotDac %u", dac_num);
            Node->dac_num = dac_num;
            LOG_INFO(I2S, "Play 48 samples");
            Node->loopback = false;
            Node->play = status;
            if(Node->play) {
                HAL_I2S_StateTypeDef state = HAL_I2S_GetState(&Node->i2s_h);
                if(HAL_I2S_STATE_READY != state) {
                    LOG_WARNING(I2S, "DmaState:%s DmaStop", HalI2sState2Str(state));
                    i2s_dma_stop(num);
                }

                HAL_StatusTypeDef ret = HAL_ERROR;
                LOG_INFO(I2S, "StartPlay1KHz");
                ret = HAL_I2S_Transmit_DMA(&Node->i2s_h, (uint16_t*)DacNode->tx_sample_static_array, 48 * 2);

                if(HAL_OK != ret) {
                    Node->error_cnt++;
                    LOG_ERROR(I2S, "DmaTxErr %s", HalStatus2Str(ret));
                } else {
                    LOG_INFO(I2S, "DmaTxOk %u Samples", DacNode->sample_cnt);
                    res = true;
                }
            } else {
                res = true;
            }

        } else {
            LOG_ERROR(SW_DAC, "HandleErr");
        }
#else
        LOG_ERROR(I2S, "Add SW_DAC component");
#endif /*HAS_SW_DAC*/
    } else {
        LOG_ERROR(I2S, "HandleErr");
    }
    return res;
}

bool i2s_play_tx(uint8_t num, uint8_t dac_num, bool status) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
#ifdef HAS_SW_DAC
        Node->dac_num = 0;
        SwDac_t* DacNode = sw_dac_get_node(dac_num);
        if(DacNode) {
            LOG_DEBUG(I2S, "SpotDac %u", dac_num);
            Node->dac_num = dac_num;
            if(DacNode->tx_sample_array && DacNode->rx_sample_array && (0 < DacNode->sample_cnt)) {
                LOG_DEBUG(I2S, "SpotRecord %u", dac_num);
                LOG_INFO(I2S, "Play %u samples", DacNode->sample_cnt);
                HAL_StatusTypeDef ret = HAL_ERROR;
                Node->loopback = false;
                Node->play = status;
                if(Node->play) {
                    HAL_I2S_StateTypeDef state = HAL_I2S_GetState(&Node->i2s_h);
                    if(HAL_I2S_STATE_READY != state) {
                        LOG_WARNING(I2S, "DmaState:%s DmaStop", HalI2sState2Str(state));
                        i2s_dma_stop(num);
                    }

                    LOG_INFO(I2S, "StartPlay");
                    ret = HAL_I2S_Transmit_DMA(&Node->i2s_h, (uint16_t*)DacNode->tx_sample_array,
                                               DacNode->sample_cnt * 2);

                    // ret = HAL_I2S_Transmit_DMA(&Node->i2s_h, (uint16_t*)&DacNode->real_sample_array[0],
                    //                           DacNode->sample_cnt );

                    if(HAL_OK != ret) {
                        Node->error_cnt++;
                        LOG_ERROR(I2S, "DmaTxErr %s", HalStatus2Str(ret));
                    } else {
                        LOG_INFO(I2S, "DmaTxOk %u Samples", DacNode->sample_cnt);
                        res = true;
                    }
                } else {
                    res = true;
                }
            } else {
                LOG_ERROR(LG_DAC, "TrackErr");
            }
        } else {
            LOG_ERROR(LG_DAC, "HandleErr");
        }
#else
        LOG_ERROR(I2S, "Add SW_DAC component");
#endif /*HAS_SW_DAC*/
    } else {
        LOG_ERROR(I2S, "HandleErr");
    }
    return res;
}

bool i2s_read_sample(uint8_t num, size_t size) {
    bool res = false;
    LOG_DEBUG(I2S, "I2S%u Read %u Samples", num, size);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_I2S_Receive_DMA(&Node->i2s_h, (uint16_t*)&Node->rx_sample.u32[0], size);
        if(HAL_OK != ret) {
            Node->error_cnt++;
            LOG_ERROR(I2S, "RxDmaErr: %u %s", ret, HalStatus2Str(ret));
        } else {
            LOG_INFO(I2S, "RxDma" LOG_OK);
            res = true;
        }
    } else {
        LOG_ERROR(I2S, "NodeErr");
    }
    return res;
}

static uint32_t I2sSampleRate2Hz(AudioFreq_t code) {
    uint32_t sample_rate = 0;
    switch((uint32_t)code) {
    case I2S_AUDIO_FREQ_192K:
        sample_rate = 192000;
        break; // DVD-Audio (MLP 2.0);
    case I2S_AUDIO_FREQ_96K:
        sample_rate = 96000;
        break; // DVD-Audio (MLP 5.1);
    case I2S_AUDIO_FREQ_48K:
        sample_rate = 48000;
        break; // DVD, DAT;
    case I2S_AUDIO_FREQ_44K:
        sample_rate = 44100;
        break; //
    case I2S_AUDIO_FREQ_32K:
        sample_rate = 32000;
        break;
    case I2S_AUDIO_FREQ_22K:
        sample_rate = 22050;
        break;
    case I2S_AUDIO_FREQ_16K:
        sample_rate = 16000;
        break;
    case I2S_AUDIO_FREQ_11K:
        sample_rate = 11025;
        break;
    case I2S_AUDIO_FREQ_8K:
        sample_rate = 8000;
        break;
    default:
        break;
    }
    return sample_rate;
}

uint32_t i2s_get_sample_rate(uint8_t num) {
    uint32_t sample_rate = 0;
    const I2sConfig_t* Config = I2sGetConfNode(num);
    if(Config) {
        sample_rate = I2sSampleRate2Hz(Config->audio_freq);
    }
    return sample_rate;
}

bool i2s_dma_pause(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret;
        ret = HAL_I2S_DMAPause(&Node->i2s_h);
        if(HAL_OK == ret) {
            res = true;
            LOG_INFO(I2S, "DmaPause" LOG_OK);
        } else {
            LOG_ERROR(I2S, "DmaPause %s", HalStatus2Str(ret));
        }
    } else {
        LOG_ERROR(I2S, "NodeGetErr");
    }
    return res;
}

bool i2s_dma_stop(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret;
        ret = HAL_I2S_DMAStop(&Node->i2s_h);
        if(HAL_OK == ret) {
            res = true;
            LOG_INFO(I2S, "DmaStop" LOG_OK);
        } else {
            LOG_ERROR(I2S, "DmaStop %s", HalStatus2Str(ret));
        }
    } else {
        LOG_ERROR(I2S, "NodeGetErr");
    }
    return res;
}

bool i2s_send(uint8_t num, bool status) {
    bool res = true;
    LOG_ERROR(I2S, "ImplementLater");
    return res;
}

bool i2s_config_tx(uint8_t i2s_num, uint8_t word_size, uint8_t channels, uint32_t audio_freq) { return false; }

bool i2s_loopback_shared_memory(uint8_t i2s_num, size_t words_num) { return false; }

bool i2s_loopback(uint8_t i2s_num, size_t words_num) { return false; }
