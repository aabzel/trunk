#include "i2s_mcal.h"

#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "clock_mcal.h"
#include "std_includes.h"
#include "clock_const.h"
#include "microcontroller.h"
#include "clock_custom_diag.h"
#include "clock_diag.h"
#include "clock_custom_const.h"
#include "clock_utils.h"
#include "i2s_config.h"
#include "connectivity.h"
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
#include "stm32f4xx_ll_rcc.h"
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

const I2sInfo_t I2sInfo[] = {
#ifdef HAS_I2S1
        {
            .clock_bus = CLOCK_BUS_APB2,
            .num = 1,
            .I2Sx = SPI1,
            .irq_n = SPI1_IRQn,
            .CallBackTxHalf = NULL,
            .CallBackTxDone = NULL,
            .CallBackRxHalf = NULL,
            .CallBackRxDone = NULL,
            .dma_tx_irq_n = DMA2_Stream3_IRQn,
            .DmaInfoChannelTx = { .dma_num = 2, .stream = 3, .channel = 3,  .name = "I2S1_TX/SPI1_TX", },
            .dma_rx_irq_n = DMA2_Stream3_IRQn,
            .DmaInfoChannelRx = { .dma_num = 2, .stream = 0, .channel = 3,  .name = "I2S1_RX/SPI1_RX", },
            .valid = true,
        },
#endif

#ifdef HAS_I2S2
    {
        .num = 2,
        .clock_bus = CLOCK_BUS_APB1,
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
#endif

#ifdef HAS_I2S3
        {
            .num = 3,
            .I2Sx = SPI3,
            .irq_n = SPI3_IRQn,
            .clock_bus = CLOCK_BUS_APB1,
            .CallBackTxHalf = NULL,
            .CallBackTxDone = NULL,
            .CallBackRxHalf = NULL,
            .CallBackRxDone = NULL,
            .dma_tx_irq_n = DMA1_Stream5_IRQn,
            .DmaInfoChannelTx = { .dma_num = 1, .stream = 5, .channel = 0,  .name = "I2S3_TX/SPI3_TX", },
            .dma_rx_irq_n = DMA1_Stream0_IRQn,
            .DmaInfoChannelRx = { .dma_num = 1, .stream = 0, .channel = 0,  .name = "I2S3_RX/SPI3_RX", },
            .valid = true,
        },
#endif

#ifdef HAS_I2S4
        {
            .num = 4,
            .I2Sx = I2S2ext,
            .clock_bus = CLOCK_BUS_APB1,
            .irq_n = SPI2_IRQn,
            .CallBackTxHalf = NULL,
            .CallBackTxDone = NULL,
            .CallBackRxHalf = NULL,
            .CallBackRxDone = NULL,
            .dma_tx_irq_n = DMA1_Stream4_IRQn,
            .DmaInfoChannelTx = { .dma_num = 1, .stream=4, .channel = 0,  .name = "I2S2_TX", },
            .dma_rx_irq_n = DMA1_Stream3_IRQn,
            .DmaInfoChannelRx = { .dma_num = 1, .stream=3, .channel = 3,  .name = "I2S2_EXT_RX", },
            .valid = true,
        },
#endif

#ifdef HAS_I2S5
    {
        .num = 5,
        .I2Sx = I2S3ext,
        .irq_n = SPI3_IRQn,
        .clock_bus = CLOCK_BUS_APB1,
        .CallBackTxHalf = NULL,
        .CallBackTxDone = NULL,
        .CallBackRxHalf = NULL,
        .CallBackRxDone = NULL,
        .dma_tx_irq_n = DMA1_Stream4_IRQn,
        .DmaInfoChannelTx = { .dma_num = 1, .stream=4, .channel = 0,  .name = "I2S3_TX", },
        .dma_rx_irq_n = DMA1_Stream3_IRQn,
        .DmaInfoChannelRx = { .dma_num = 1, .stream=0, .channel = 3,  .name = "I2S3_EXT_RX", },
        .valid = true,
    },
#endif
};

COMPONENT_GET_INFO(I2s)

uint32_t i2s_info_get_cnt(void) {
    uint32_t cnt = 0 ;
    cnt = ARRAY_SIZE(I2sInfo);
    return cnt;
}

static uint32_t i2s_data_len_to_frame_size(const Stm32I2sDatLen_t dat_len) {
    uint32_t frame_size=16;
    switch(dat_len) {
        case I2S_DAT_LEN16_BIT:{
            frame_size=16;
        } break;

        case I2S_DAT_LEN24_BIT:
        case I2S_DAT_LEN32_BIT:{
            frame_size=32;
        } break;

        default: frame_size=32; break;
    }
    return frame_size;
}


uint32_t i2s_base_clock_get(void) {
    uint32_t bus_freq_hz = 0;
    bus_freq_hz = HAL_RCCEx_GetPeriphCLKFreq(  RCC_PERIPHCLK_I2S);
    return bus_freq_hz;
}

uint8_t i2s_sample_size_get(uint8_t num) {
    uint8_t sample_size_bit = 0 ;
    const I2sInfo_t* Info = I2sGetInfo(num);
    if (Info) {
        I2sReg_SPI_I2SCFGR_t I2SCFGR;
        I2SCFGR.dword = Info->I2Sx->I2SCFGR;
        sample_size_bit = I2s_DATLEN_ToNum(I2SCFGR.DATLEN) ;
    }
    return sample_size_bit;
}

// see Figure 282. I2S clock generator architecture
uint32_t i2s_bitclock_get(uint8_t num) {
    uint32_t bitclock_hz = 0 ;
    const I2sInfo_t* Info = I2sGetInfo(num);
    if (Info) {
        uint32_t bus_freq_hz = 0;
        clock_frequency_get(Info->clock_bus, &bus_freq_hz);

        I2sReg_SPI_I2SCFGR_t I2SCFGR;
        I2SCFGR.dword = Info->I2Sx->I2SCFGR;

        I2sReg_SPI_I2SPR_t I2SPR;
        I2SPR.dword= Info->I2Sx->I2SPR;
        uint32_t freq_after_div_hz = bus_freq_hz/(I2SPR.I2SDIV+I2SPR.ODD);
        uint32_t freq_div4_hz =freq_after_div_hz/4;
        uint32_t freq_div2_hz =freq_div4_hz/2;

        uint32_t freq_channel_hz = 0 ;
        if(I2S_I2SCFGR_CHLEN_32_BIT == I2SCFGR.CHLEN){
            freq_channel_hz = freq_div4_hz ;
        }else{
            freq_channel_hz = freq_div2_hz ;
        }


        if(SPI_I2SPR_MCKOE_DISABLED==I2SPR.MCKOE){
            bitclock_hz=freq_after_div_hz;
        }else{
            bitclock_hz=freq_channel_hz;
        }

    }
    return bitclock_hz;
}

/*
When the master clock is generated (MCKOE in the SPI_I2SPR register is set):
FS = I2SxCLK / [(16*2)*((2*I2SDIV)+ODD)*8)] when the channel frame is 16-bit wide
FS = I2SxCLK / [(32*2)*((2*I2SDIV)+ODD)*4)] when the channel frame is 32-bit wide
*/
static uint32_t i2s_sample_freq_master_clock_on_get_ll(const I2sInfo_t* const Info,  const I2sReg_SPI_I2SPR_t* const pI2SPR){
    uint32_t sampling_frequency_hz = 0 ;

    uint32_t i2sx_clk_hz = 0 ;
    i2sx_clk_hz = i2s_base_clock_get();

    I2sReg_SPI_I2SCFGR_t I2SCFGR;
    I2SCFGR.dword = Info->I2Sx->I2SCFGR;

    uint32_t sample_bit_size=i2s_data_len_to_frame_size( I2SCFGR.DATLEN);

    switch(I2SCFGR.DATLEN) {
        case I2S_DAT_LEN16_BIT:{
            // FS = I2SxCLK / [   (16*2)*{(2*I2SDIV)+ODD)*8}   ]     when the channel frame is 16-bit wide
            sampling_frequency_hz = i2sx_clk_hz/   (     ((sample_bit_size*2)*(  (2*pI2SPR->I2SDIV) + pI2SPR->ODD    )*8    )    ) ;
        } break;

        case I2S_DAT_LEN24_BIT:
        case I2S_DAT_LEN32_BIT:{
            //  FS = I2SxCLK / [      (32*2)*((2*I2SDIV)+ODD)*4)     ] when the channel frame is 32-bit wide
            sampling_frequency_hz = i2sx_clk_hz/   (     ((sample_bit_size*2)*(  (2*pI2SPR->I2SDIV) + pI2SPR->ODD    )*4    )    ) ;
        } break;

        default:   break;
    }


    return sampling_frequency_hz;
}


static uint32_t i2s_sample_freq_master_clock_off_get_ll(I2sInfo_t* Info,  I2sReg_SPI_I2SPR_t* pI2SPR){
    uint32_t sampling_frequency_hz = 0 ;
    I2sReg_SPI_I2SCFGR_t I2SCFGR;
    I2SCFGR.dword = Info->I2Sx->I2SCFGR;
    uint32_t bus_freq_hz = 0 ;
    bus_freq_hz = i2s_base_clock_get();
    uint32_t sample_bit_size = i2s_data_len_to_frame_size(I2SCFGR.DATLEN);
    // FS = I2SxCLK / [(16*2)*((2*I2SDIV)+ODD))] when the channel frame is 16-bit wide
    // FS = I2SxCLK / [(32*2)*((2*I2SDIV)+ODD))] when the channel frame is 32-bit wide
    sampling_frequency_hz = bus_freq_hz / ( (sample_bit_size*2)*((2*pI2SPR->I2SDIV) + pI2SPR->ODD) ) ;

    return sampling_frequency_hz;
}

static bool i2s_sample_freq_master_clock_on_get(const I2sInfo_t *Info, uint32_t* const audio_frequency_hz){
    bool res = true;
    I2sReg_SPI_I2SPR_t I2SPR;
    I2SPR.dword = Info->I2Sx->I2SPR;
    *audio_frequency_hz = i2s_sample_freq_master_clock_on_get_ll(Info,  &I2SPR);
    return res;
}


static bool i2s_sample_freq_master_clock_off_get( const I2sInfo_t *Info, uint32_t* const audio_frequency_hz) {
    bool res = true;
    I2sReg_SPI_I2SPR_t I2SPR;
    I2SPR.dword = Info->I2Sx->I2SPR;
    *audio_frequency_hz= i2s_sample_freq_master_clock_off_get_ll( Info, &I2SPR);
    return res;
}

bool i2s_sample_freq_get(uint8_t num, uint32_t* const audio_frequency_hz) {
    bool res = false;

    if(audio_frequency_hz) {
        const I2sInfo_t *Info = I2sGetInfo(num);
        if(Info) {
            I2sReg_SPI_I2SPR_t I2SPR;
            I2SPR.dword = Info->I2Sx->I2SPR;
            switch (I2SPR.MCKOE) {
                case SPI_I2SPR_MCKOE_DISABLED: {
                    res = i2s_sample_freq_master_clock_on_get(Info, audio_frequency_hz);
                } break;

                case SPI_I2SPR_MCKOE_ENABLED: {
                    res = i2s_sample_freq_master_clock_off_get(Info, audio_frequency_hz);
                } break;

                default: res = false; break;
            }
        }

        //  uint32_t bitclock=i2s_bitclock_get(  num)
        //  * const audio_frequency_hz = (bitclock/2)/16 ;
        //  res = true;
    }
    return res;
}

int32_t i2s_get_sample_rate(uint8_t num) {
    int32_t audio_frequency_hz = -1;
    uint32_t fps_frequency_hz = 0;
    bool res = i2s_sample_freq_get(num, &fps_frequency_hz);
    if(res) {
        audio_frequency_hz = (int32_t) fps_frequency_hz;
        LOG_ERROR(I2S, "GetFps");
    }
    return audio_frequency_hz;
}

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

        //  HAL_NVIC_SetPriority(SPI1_IRQn, 14, 14);
        //  HAL_NVIC_EnableIRQ(SPI1_IRQn);
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
       // //  HAL_NVIC_SetPriority(SPI2_IRQn, 14, 14);
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
        //  HAL_NVIC_SetPriority(SPI3_IRQn, 14, 14);
        //  HAL_NVIC_EnableIRQ(SPI3_IRQn);
    }
#endif /*HAS_I2S3*/

#ifdef HAS_I2S4
    if(SPI2 == i2sHandle->Instance) {
        // I2sHandle_t* Node = I2sGetNode(4);
#if 0
        bool res = i2s_clock_init(4);
        if(false == res) {
            LOG_ERROR(I2S, "4 ClockInitErr");
        }

        __HAL_RCC_SPI4_CLK_ENABLE();
        DmaHandle_t* DmaNodeTx = DmaGetNode(DMA2_I2S4_TX);
        if(DmaNodeTx) {
            __HAL_LINKDMA(i2sHandle, hdmatx, DmaNodeTx->dma_h);
        }
#endif /*HAS_DMA*/
        //  HAL_NVIC_SetPriority(SPI2_IRQn, 14, 14);
        //  HAL_NVIC_EnableIRQ(SPI2_IRQn);
    }
#endif /*HAS_I2S4*/

#ifdef HAS_I2S5
    if(SPI2 == i2sHandle->Instance) {
        bool res = i2s_clock_init(5);
        if(false == res) {
            LOG_ERROR(I2S, "5 ClockInitErr");
        }
        __HAL_RCC_SPI2_CLK_ENABLE();

#if 0
        I2sHandle_t* Node = I2sGetNode(5);
        DmaHandle_t* DmaNodeTx = DmaGetNode(DMAx_I2S5_TX);
        if(DmaNodeTx) {
            __HAL_LINKDMA(i2sHandle, hdmatx, DmaNodeTx->dma_h);
        }
        DmaHandle_t* DmaNodeRx = DmaGetNode(DMAx_I2S5_RX);
        if(DmaNodeTx) {
            __HAL_LINKDMA(i2sHandle, hdmarx, DmaNodeRx->dma_h);
        }
#endif /*HAS_DMA*/

        //  HAL_NVIC_SetPriority(SPI2_IRQn, 14, 14);
        //  HAL_NVIC_EnableIRQ(SPI2_IRQn);
    }
#endif /*HAS_I2S5*/
}

I2S_HandleTypeDef* i2s_num_to_handle(uint8_t num) {
    I2S_HandleTypeDef* pHandle=NULL;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        if(Node->pHandle){
            pHandle = Node->pHandle;
        }
    }
    return pHandle;
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
    if(SPI2 == i2sHandle->Instance) {
        __HAL_RCC_SPI2_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(SPI2_IRQn);
    }
#endif /*HAS_I2S4*/

#ifdef HAS_I2S5
    if(SPI3 == i2sHandle->Instance) {
        __HAL_RCC_SPI3_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(SPI3_IRQn);
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
        HAL_StatusTypeDef ret ;
        //HAL_DMA_Abort(Node->pHandle->hdmatx);
        //ret = HAL_I2S_DMAStop(Node->pHandle);
        Node->pHandle->hdmatx->State = HAL_DMA_STATE_BUSY;
        ret = HAL_DMA_Abort_IT(Node->pHandle->hdmatx);

        Node->pHandle->State = HAL_I2S_STATE_READY;
        Node->pHandle->hdmatx->State = HAL_DMA_STATE_READY;
        ret = HAL_I2S_Transmit_DMA(Node->pHandle, (uint16_t*) array, words);
        if(HAL_OK == ret) {
            res = true;
        } else {
            LOG_DEBUG(I2S, "WrErr:%u %s", ret, HalStatusToStr(ret));
        }
    } else {
        LOG_DEBUG(I2S, "%u NodeErr", num);
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

bool i2s_read_write(uint8_t num,
                    uint16_t* tx_array,
                    uint16_t* rx_array,
                    uint32_t words) {
    bool res = false;
    LOG_DEBUG(I2S, "ReadWrite i2s:%u sample:0x%08x", num, words);
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret = HAL_ERROR;
        //ret = HAL_I2S_DMAStop(Node->pHandle);
        ret = HAL_I2SEx_TransmitReceive_DMA(Node->pHandle,
                                           (uint16_t*) tx_array,
                                           (uint16_t*) rx_array,
                                           words);
        if(HAL_OK != ret) {
            LOG_ERROR(I2S, "%u DmaTxRxErr %u %s", num, ret, HalStatusToStr(ret));
            Node->error_cnt++;
            res = false;
        } else {
            LOG_INFO(I2S, "%u DmaTxRxOk", num);
            res = true;
        }
    }
#ifdef SPI_I2S_FULLDUPLEX_SUPPORT
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
    I2sReg_SPI_I2SCFGR_t RegCfg;
    RegCfg.dword = I2sBaseAddr->I2SCFGR;
    sample_size = I2sSampleBitness2bytes(RegCfg.DATLEN);
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
                    ret = HAL_I2SEx_TransmitReceive_DMA(Node->pHandle, (uint16_t*)&Dds->tx_sample_array[0],
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
                HAL_I2S_StateTypeDef state = HAL_I2S_GetState(Node->pHandle);
                if(HAL_I2S_STATE_READY != state) {
                    LOG_WARNING(I2S, "DmaState:%s DmaStop", HalI2sStateToStr(state));
                    i2s_dma_stop(num);
                }

                HAL_StatusTypeDef ret = HAL_ERROR;
                LOG_INFO(I2S, "StartPlay1KHz");
                ret = HAL_I2S_Transmit_DMA(Node->pHandle, (uint16_t*)Dds->tx_sample_static_array, 48 * 2);

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
                    HAL_I2S_StateTypeDef state = HAL_I2S_GetState(Node->pHandle);
                    if(HAL_I2S_STATE_READY != state) {
                        LOG_WARNING(I2S, "DmaState:%s DmaStop", HalI2sStateToStr(state));
                        i2s_dma_stop(num);
                    }

                    LOG_INFO(I2S, "StartPlay");
                    ret = HAL_I2S_Transmit_DMA(Node->pHandle, (uint16_t*)Dds->sample_array,
                                               Dds->sample_cnt * 2);

                    // ret = HAL_I2S_Transmit_DMA(Node->pHandle, (uint16_t*)&Dds->real_sample_array[0],
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
        ret = HAL_I2S_Receive_DMA(Node->pHandle, (uint16_t*) &Node->rx_sample.u32[0], size);
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
        ret = HAL_I2SEx_TransmitReceive_DMA(Node->pHandle, (uint16_t*) &Node->tx_sample.u32[0],
                (uint16_t*) &Node->rx_sample.u32[0], 2);
        if(HAL_OK != ret) {
            Node->error_cnt++;
        }
#endif
    }
    return res;
}

int32_t i32_calc_error(const uint32_t val1u, const uint32_t val2u) {
    int32_t val1i = (int32_t) val1u;
    int32_t val2i = (int32_t) val2u;
    int32_t error = val1i - val2i;
    return error ;
}

#if 0
uint32_t i2s_get_sample_rate(uint8_t num) {
    uint32_t sample_rate = 0;
    const I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {
        sample_rate = Node->audio_frequency_hz;
    }
    return sample_rate;
}
#endif

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
            pInit->MCLKOutput = I2sParseMCLKOutput(Config->mclk_out);
            pInit->DataFormat = I2sParseDataFormat(Config->data_format);
            pInit->Standard = I2sParseStandard(Config->standard);
            pInit->Mode = I2sDirRoleToMode(Config->bus_role, Config->direction);
            pInit->ClockSource = I2sParseClockSource(Config->clock_source); // I2S_CLOCK_PLL;
            pInit->CPOL = I2sParseCPol(Config->cpol); // I2S_CPOL_LOW;
            pInit->FullDuplexMode = I2sParseFullDuplexMode(Config->full_duplex);
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

/*
1 SPI1
2 SPI2
3 SPI3
4 I2S2ext
5 I2S3ext
*/
bool i2s_is_rx(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        I2sReg_SPI_CR2_t SPI_CR2;
        SPI_CR2.dword = Node->I2Sx->CR2;
        if(SPI_CR2.RXDMAEN) {
            I2sReg_SPI_I2SCFGR_t SPI_I2SCFGR;
            SPI_I2SCFGR.dword = Node->I2Sx->I2SCFGR;
            if(SPI_I2SCFGR.I2SE) {
                res = true;
            }
        }
    }
    return res;
}

/*
1 SPI1
2 SPI2
3 SPI3
4 I2S2ext
5 I2S3ext
*/
bool i2s_is_tx(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        I2sReg_SPI_CR2_t SPI_CR2;
        SPI_CR2.dword = Node->I2Sx->CR2;
        if(SPI_CR2.TXDMAEN){
            I2sReg_SPI_I2SCFGR_t SPI_I2SCFGR;
            SPI_I2SCFGR.dword = Node->I2Sx->I2SCFGR;
            if(SPI_I2SCFGR.I2SE){
                res = true;
            }
        }
    }
    return res;
}




bool i2s_vefify_one(const uint8_t num) {
    bool res = true;
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_I2SEx_TransmitReceive_DMA(Node->pHandle,
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

bool i2s_prescaler_get(uint8_t num  , I2sReg_SPI_I2SPR_t * const pReg) {
    bool res = false;
    const I2sInfo_t* Info = I2sGetInfo(num);
    if(Info){
        pReg->dword = Info->I2Sx->I2SPR;
        res = true;
    }
    return res;
}

bool i2s_ctrl(uint8_t num, bool en ) {
    bool res = false;
    const I2sInfo_t* Info = I2sGetInfo(num);
    if(Info){
        I2sReg_SPI_I2SCFGR_t I2SCFGR;
        I2SCFGR.dword = Info->I2Sx->I2SCFGR;
        I2SCFGR.I2SE = (uint32_t) en;
        Info->I2Sx->I2SCFGR = I2SCFGR.dword;
        res = true;
    }
    return res;
}

bool i2s_prescaler_set(uint8_t num , uint8_t i2s_div, bool odd, bool master_clk_out) {
    bool res = false;
    enter_critical();
    i2s_ctrl(num, false );

    LOG_INFO(I2S,"I2S_%u,SetPrescaler,DIV:%u,ODD:%u,MCLK:%u",num,i2s_div,odd,master_clk_out);
    const I2sInfo_t* Info = I2sGetInfo(num);
    if(Info){
        I2sReg_SPI_I2SPR_t I2SPR;
        I2SPR.dword = Info->I2Sx->I2SPR;
        I2SPR.I2SDIV = i2s_div;
        I2SPR.ODD = odd;
        I2SPR.MCKOE = master_clk_out;
        Info->I2Sx->I2SPR = I2SPR.dword ;
        res = true;
    }

    i2s_ctrl(num, true);
    exit_critical();
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

uint32_t get_i2s_clock_freq_hal() {
    // Функция возвращает частоту в кГц
    return HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2S);
}

static bool i2s_init_one_ll(const I2sConfig_t* const Config, I2sHandle_t* const Node) {
    bool res = false;
    res = i2s_is_valid_config(Config);
    if (res) {
        if (Config->need_init) {
            LOG_INFO(I2S, "I2S_%u init", Config->num);
            if (Node) {
                const I2sInfo_t *Info = I2sGetInfo(Config->num);
                if (Info) {
                    res = i2s_init_common(Config, Node);
                    Node->I2Sx = Info->I2Sx;
                    Node->pHandle->Instance = Info->I2Sx;
                    res = i2s_init_node(Node);
                    res = i2s_init_hal(Config, &(Node->pHandle->Init));

#ifdef HAS_I2S_DMA
                    Node->CallBackTxHalf = Info->CallBackTxHalf;
                    Node->CallBackTxDone = Info->CallBackTxDone;
                    Node->CallBackRxHalf = Info->CallBackRxHalf;
                    Node->CallBackRxDone = Info->CallBackRxDone;
#endif

                    HAL_StatusTypeDef ret = HAL_ERROR;

                    res = IS_I2S_ALL_INSTANCE(Node->pHandle->Instance);
                    // res = true;
                    if(res){
                        ret = HAL_I2S_Init(Node->pHandle);
                        res = HAL_retToRes(ret);
                        if (res) {
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

                    }
                } else {
                    LOG_ERROR(I2S, "%u InfoErr", Config->num);
                    res = false;
                }
            } else {
                LOG_ERROR(I2S, "%u HandleErr", Config->num);
                res = false;
            }
        }
    } else {
        LOG_DEBUG(I2S, "%u ConfigErr", Config->num);
        res = false;
    }
    return res;
}


static uint32_t i2s_spi_i2spr_to_audio_frequency_hz(I2sInfo_t* Info, I2sReg_SPI_I2SPR_t* pI2SPR) {
    uint32_t audio_frequency_hz = 0;

    switch (pI2SPR->MCKOE) {
        case SPI_I2SPR_MCKOE_DISABLED: {
            audio_frequency_hz = i2s_sample_freq_master_clock_on_get_ll(Info, pI2SPR);
        } break;

        case SPI_I2SPR_MCKOE_ENABLED: {
            audio_frequency_hz = i2s_sample_freq_master_clock_off_get_ll(Info, pI2SPR);
        } break;

        default:

            break;
    }

    return audio_frequency_hz;

}

bool i2s_audio_frequency_set_fast(const uint8_t num, const uint32_t audio_frequency_hz) {
    bool spot_solution = false;
    bool res = false;
    const I2sInfo_t *Info = I2sGetInfo(num);
    if(Info) {
        LOG_INFO(I2S, "I2S_%u,Set,AudioFreq:%u Hz", num, audio_frequency_hz);


        I2sPrescalerInfo_t BestPrescaler;
        BestPrescaler.abs_error = INT_MAX;

        I2sReg_SPI_I2SPR_t I2SPR;
        I2SPR.dword = 0;
        int32_t div = 0;
        for(div=0;div<0xFF;div++) {
            int32_t odd = 0;
            for(odd=0;odd<=1;odd++){
                I2SPR.I2SDIV = div;
                I2SPR.ODD = odd;
                I2SPR.MCKOE = 0;
                uint32_t ws_freq_hz = i2s_spi_i2spr_to_audio_frequency_hz(Info, &I2SPR);
                int32_t error =  i32_calc_error(audio_frequency_hz, ws_freq_hz);
                int32_t abs_error = abs(error);
                if(abs_error < BestPrescaler.abs_error) {
                    BestPrescaler.I2SPR = I2SPR;
                    BestPrescaler.abs_error = abs_error;
                    spot_solution = true;
                }
            }
        }

        if(spot_solution) {
            I2sDiagReg_I2SPR(BestPrescaler.I2SPR.dword);
            res = i2s_prescaler_set(  num , BestPrescaler.I2SPR.I2SDIV, BestPrescaler.I2SPR.ODD, BestPrescaler.I2SPR.MCKOE);
        }


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

#if 0
bool i2s_audio_set_data_dirrection_slow(const uint8_t num,
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
#endif

static uint32_t  i2s_master_dir_to_i2scfg(     const IfOperation_t operation) {
    uint32_t  i2s_cfg = 0;
    switch(operation) {
        case INTERFACE_OPERATION_RECEPTION: {
            i2s_cfg =  I2S_ROLE_MASTER_RECEIVE ;
        }break;

        case INTERFACE_OPERATION_SEND: {
            i2s_cfg =  I2S_ROLE_MASTER_TRANSMIT ;
        }break;

        default : break;
    }
    return i2s_cfg;
}


static uint32_t  i2s_slave_dir_to_i2scfg(     const IfOperation_t operation) {
    uint32_t  i2s_cfg = 0;
    switch(operation) {
        case INTERFACE_OPERATION_RECEPTION: {
            i2s_cfg =  I2S_ROLE_SLAVE_RECEIVE ;
        }break;

        case INTERFACE_OPERATION_SEND: {
            i2s_cfg =  I2S_ROLE_SLAVE_TRANSMIT ;
        }break;

        default : break;
    }
    return i2s_cfg;
}

static uint32_t i2s_bus_role_and_dir_to_i2scfg(IfBusRole_t bus_role ,   const IfOperation_t operation) {
    uint32_t  i2s_cfg = 0;
    switch(bus_role) {
        case IF_BUS_ROLE_MASTER: {
            i2s_cfg =   i2s_master_dir_to_i2scfg(    operation) ;
        }break;

        case IF_BUS_ROLE_SLAVE: {
            i2s_cfg =   i2s_slave_dir_to_i2scfg(    operation) ;
        }break;

        default : break;
    }
    return i2s_cfg;
}


bool i2s_audio_set_data_dirrection(const uint8_t num,
                                    const IfOperation_t operation) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(  num);
    if (Node) {
        Node->direction = operation_to_connectivit_dir(operation);
        LOG_INFO(I2S, "I2S_%u,Set,Operation:%s", num, IfOperationToStr(operation));
        I2sReg_SPI_I2SCFGR_t I2SCFGR;
        I2SCFGR.dword = Node->I2Sx->I2SCFGR;
        I2SCFGR.I2SCFG = i2s_bus_role_and_dir_to_i2scfg(Node->bus_role , operation);
        Node->I2Sx->I2SCFGR = I2SCFGR.dword ;
        res = true;
    }
    return res;
}


bool i2s_proc_status(I2sHandle_t* Node ){
    bool res = true;
    I2sReg_SPI_SR_t SPI_SR;
    SPI_SR.dword = Node->I2Sx->SR;
    if(SPI_SR.FRE) {
        LOG_ERROR(I2S, "I2S_%u,Err,FrameFormat", Node->num);
        Node->error_cnt++;
        res = false ;
    }

    if(SPI_SR.UDR) {
        LOG_ERROR(I2S, "I2S_%u,Err,Underrun", Node->num);
        Node->error_cnt++;
        res = false ;
    }

    return res;
}

bool i2s_proc_one(uint8_t num) {
    bool res = true;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        res = i2s_proc_status(Node);
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

