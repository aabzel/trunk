#include "dma_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "artery_at32f4xx.h"
#include "code_generator.h"
#include "data_utils.h"
#include "dma_custom_drv.h"
#include "dma_custom_types.h"
#include "hal_diag.h"
#include "log.h"
#include "time_mcal.h"

#define DMA_MUX_COMPOSER(MMM, TEXT)                                                                                    \
    {                                                                                                                  \
        .valid = true,                                                                                                 \
        .mux = MMM,                                                                                                    \
        .name = #TEXT,                                                                                                 \
    },

// TODO mode to MCU spesific
#ifdef HAS_AT32F43X
/*Table 9-3 Flexible DMA1/DMA2 request mapping DMAMUX*/
#define DMA_MIX_DIAG                                                                                                   \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_REQ_G1, DMA_MUXREQG1)                                                            \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_REQ_G2, DMA_MUXREQG2)                                                            \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_REQ_G3, DMA_MUXREQG3)                                                            \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_REQ_G4, DMA_MUXREQG4)                                                            \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_ADC1, ADC1)                                                                      \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_DAC1, DAC1)                                                                      \
    DMA_MUX_COMPOSER(7, reserved)                                                                                      \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_TMR6_OVERFLOW, TMR6_OVERFLOW)                                                    \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_TMR7_OVERFLOW, TMR7_OVERFLOW)                                                    \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_SPI1_RX, SPI1_RX)                                                                \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_SPI1_TX, SPI1_TX)                                                                \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_SPI2_RX, SPI2_RX)                                                                \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_SPI2_TX, SPI2_TX)                                                                \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_SPI3_RX, SPI3_RX)                                                                \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_SPI3_TX, SPI3_TX)                                                                \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_I2C1_RX, I2C1_RX)                                                                \
    DMA_MUX_COMPOSER(17, I2C1_TX)                                                                                      \
    DMA_MUX_COMPOSER(18, I2C2_RX)                                                                                      \
    DMA_MUX_COMPOSER(19, I2C2_TX)                                                                                      \
    DMA_MUX_COMPOSER(20, I2C3_RX)                                                                                      \
    DMA_MUX_COMPOSER(21, I2C3_TX)                                                                                      \
    DMA_MUX_COMPOSER(22, reserved)                                                                                     \
    DMA_MUX_COMPOSER(23, reserved)                                                                                     \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_USART1_RX, USART1_RX)                                                            \
    DMA_MUX_COMPOSER(25, USART1_TX)                                                                                    \
    DMA_MUX_COMPOSER(26, USART2_RX)                                                                                    \
    DMA_MUX_COMPOSER(27, USART2_TX)                                                                                    \
    DMA_MUX_COMPOSER(28, USART3_RX)                                                                                    \
    DMA_MUX_COMPOSER(29, USART3_TX)                                                                                    \
    DMA_MUX_COMPOSER(30, UART4_RX)                                                                                     \
    DMA_MUX_COMPOSER(31, UART4_TX)                                                                                     \
    DMA_MUX_COMPOSER(32, UART5_RX)                                                                                     \
    DMA_MUX_COMPOSER(33, UART5_TX)                                                                                     \
    DMA_MUX_COMPOSER(34, reserved)                                                                                     \
    DMA_MUX_COMPOSER(35, reserved)                                                                                     \
    DMA_MUX_COMPOSER(36, ADC2)                                                                                         \
    DMA_MUX_COMPOSER(37, ADC3)                                                                                         \
    DMA_MUX_COMPOSER(38, reserved)                                                                                     \
    DMA_MUX_COMPOSER(39, SDIO1)                                                                                        \
    DMA_MUX_COMPOSER(40, QSPI1)                                                                                        \
    DMA_MUX_COMPOSER(41, DAC2)                                                                                         \
    DMA_MUX_COMPOSER(42, TMR1_CH1)                                                                                     \
    DMA_MUX_COMPOSER(43, TMR1_CH2)                                                                                     \
    DMA_MUX_COMPOSER(44, TMR1_CH3)                                                                                     \
    DMA_MUX_COMPOSER(45, TMR1_CH4)                                                                                     \
    DMA_MUX_COMPOSER(46, TMR1_OVERFLOW)                                                                                \
    DMA_MUX_COMPOSER(47, TMR1_TRIG)                                                                                    \
    DMA_MUX_COMPOSER(48, TMR1_HALL)                                                                                    \
    DMA_MUX_COMPOSER(49, TMR8_CH1)                                                                                     \
    DMA_MUX_COMPOSER(50, TMR8_CH2)                                                                                     \
    DMA_MUX_COMPOSER(51, TMR8_CH3)                                                                                     \
    DMA_MUX_COMPOSER(52, TMR8_CH4)                                                                                     \
    DMA_MUX_COMPOSER(53, TMR8_OVERFLOW)                                                                                \
    DMA_MUX_COMPOSER(54, TMR8_TRIG)                                                                                    \
    DMA_MUX_COMPOSER(55, TMR8_HALL)                                                                                    \
    DMA_MUX_COMPOSER(56, TMR2_CH1)                                                                                     \
    DMA_MUX_COMPOSER(57, TMR2_CH2)                                                                                     \
    DMA_MUX_COMPOSER(58, TMR2_CH3)                                                                                     \
    DMA_MUX_COMPOSER(59, TMR2_CH4)                                                                                     \
    DMA_MUX_COMPOSER(60, TMR2_OVERFLOW)                                                                                \
    DMA_MUX_COMPOSER(61, TMR3_CH1)                                                                                     \
    DMA_MUX_COMPOSER(62, TMR3_CH2)                                                                                     \
    DMA_MUX_COMPOSER(63, TMR3_CH3)                                                                                     \
    DMA_MUX_COMPOSER(64, TMR3_CH4)                                                                                     \
    DMA_MUX_COMPOSER(65, TMR3_OVERFLOW)                                                                                \
    DMA_MUX_COMPOSER(66, TMR3_TRIG)                                                                                    \
    DMA_MUX_COMPOSER(67, TMR4_CH1)                                                                                     \
    DMA_MUX_COMPOSER(68, TMR4_CH2)                                                                                     \
    DMA_MUX_COMPOSER(69, TMR4_CH3)                                                                                     \
    DMA_MUX_COMPOSER(70, TMR4_CH4)                                                                                     \
    DMA_MUX_COMPOSER(71, TMR4_OVERFLOW)                                                                                \
    DMA_MUX_COMPOSER(72, TMR5_CH1)                                                                                     \
    DMA_MUX_COMPOSER(73, TMR5_CH2)                                                                                     \
    DMA_MUX_COMPOSER(74, TMR5_CH3)                                                                                     \
    DMA_MUX_COMPOSER(75, TMR5_CH4)                                                                                     \
    DMA_MUX_COMPOSER(76, TMR5_OVERFLOW)                                                                                \
    DMA_MUX_COMPOSER(77, TMR5_TRIG)                                                                                    \
    DMA_MUX_COMPOSER(78, reserved)                                                                                     \
    DMA_MUX_COMPOSER(79, reserved)                                                                                     \
    DMA_MUX_COMPOSER(80, reserved)                                                                                     \
    DMA_MUX_COMPOSER(81, reserved)                                                                                     \
    DMA_MUX_COMPOSER(82, reserved)                                                                                     \
    DMA_MUX_COMPOSER(83, reserved)                                                                                     \
    DMA_MUX_COMPOSER(84, reserved)                                                                                     \
    DMA_MUX_COMPOSER(85, reserved)                                                                                     \
    DMA_MUX_COMPOSER(86, TMR20_CH1)                                                                                    \
    DMA_MUX_COMPOSER(87, TMR20_CH2)                                                                                    \
    DMA_MUX_COMPOSER(88, TMR20_CH3)                                                                                    \
    DMA_MUX_COMPOSER(89, TMR20_CH4)                                                                                    \
    DMA_MUX_COMPOSER(90, TMR20_OVERFLOW)                                                                               \
    DMA_MUX_COMPOSER(91, reserved)                                                                                     \
    DMA_MUX_COMPOSER(92, reserved)                                                                                     \
    DMA_MUX_COMPOSER(93, TMR20_TRIG)                                                                                   \
    DMA_MUX_COMPOSER(94, TMR20_HALL)                                                                                   \
    DMA_MUX_COMPOSER(95, reserved)                                                                                     \
    DMA_MUX_COMPOSER(96, reserved)                                                                                     \
    DMA_MUX_COMPOSER(97, reserved)                                                                                     \
    DMA_MUX_COMPOSER(98, reserved)                                                                                     \
    DMA_MUX_COMPOSER(99, reserved)                                                                                     \
    DMA_MUX_COMPOSER(115, USART6_TX)                                                                                   \
    DMA_MUX_COMPOSER(116, UART7_RX)                                                                                    \
    DMA_MUX_COMPOSER(100, reserved)                                                                                    \
    DMA_MUX_COMPOSER(101, reserved)                                                                                    \
    DMA_MUX_COMPOSER(102, reserved)                                                                                    \
    DMA_MUX_COMPOSER(104, QSPI2)                                                                                       \
    DMA_MUX_COMPOSER(103, SDIO2)                                                                                       \
    DMA_MUX_COMPOSER(105, DVP)                                                                                         \
    DMA_MUX_COMPOSER(106, SPI4_RX)                                                                                     \
    DMA_MUX_COMPOSER(107, SPI4_TX)                                                                                     \
    DMA_MUX_COMPOSER(108, reserved)                                                                                    \
    DMA_MUX_COMPOSER(109, reserved)                                                                                    \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_I2S2_EXT_RX, I2S2_EXT_RX)                                                        \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_I2S2_EXT_TX, I2S2_EXT_TX)                                                        \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_I2S3_EXT_RX, I2S3_EXT_RX)                                                        \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_I2S3_EXT_TX, I2S3_EXT_TX)                                                        \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_USART6_RX, USART6_RX)                                                            \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_UART8_RX, UART8_RX)                                                              \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_UART8_TX, UART8_TX)                                                              \
    DMA_MUX_COMPOSER(120, reserved)                                                                                    \
    DMA_MUX_COMPOSER(121, reserved)                                                                                    \
    DMA_MUX_COMPOSER(122, reserved)                                                                                    \
    DMA_MUX_COMPOSER(123, reserved)                                                                                    \
    DMA_MUX_COMPOSER(124, reserved)                                                                                    \
    DMA_MUX_COMPOSER(125, reserved)                                                                                    \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_TMR2_TRIG, TMR2_TRIG)                                                            \
    DMA_MUX_COMPOSER(127, reserved)                                                                                    \
    DMA_MUX_COMPOSER(DMAMUX_DMAREQ_ID_UART7_TX, UART7_TX)

#else
#define DMA_MIX_DIAG
#endif // HAS_AT32F43X

const DmaMuxInfo_t DmaMuxlInfo[] = {DMA_MIX_DIAG};

const DmaMuxInfo_t* DmaMuxToInfo(uint8_t mux) {
    DmaMuxInfo_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(DmaMuxlInfo);
    for(i = 0; i < cnt; i++) {
        if(mux == DmaMuxlInfo[i].mux) {
            if(DmaMuxlInfo[i].valid) {
                Node = &DmaMuxlInfo[i];
            }
        }
    }
    return Node;
}

static dma_peripheral_data_size_type DmaAligmentToPeripheralArtery(DmaAligmant_t aligment) {
    dma_peripheral_data_size_type data_size = DMA_MEMORY_DATA_WIDTH_BYTE;
    switch((uint8_t)aligment) {
    case DMA_ALIG_BYTE:
        data_size = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
        break;
    case DMA_ALIG_HALF_WORD:
        data_size = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
        break;
    case DMA_ALIG_WORD:
        data_size = DMA_PERIPHERAL_DATA_WIDTH_WORD;
        break;
    case DMA_ALIG_UNDEF:
        LOG_ERROR(DMA, "ErrDatSize:%u", aligment);
        break;
    }
    return data_size;
}

static dma_memory_data_size_type DmaAligmentToMemoryArtery(DmaAligmant_t aligment) {
    dma_memory_data_size_type data_size = DMA_MEMORY_DATA_WIDTH_BYTE;
    switch((uint8_t)aligment) {
    case DMA_ALIG_BYTE:
        data_size = DMA_MEMORY_DATA_WIDTH_BYTE;
        break;
    case DMA_ALIG_HALF_WORD:
        data_size = DMA_MEMORY_DATA_WIDTH_HALFWORD;
        break;
    case DMA_ALIG_WORD:
        data_size = DMA_MEMORY_DATA_WIDTH_WORD;
        break;
    case DMA_ALIG_UNDEF:
        LOG_ERROR(DMA, "ErrMemSize:%u", aligment);
        break;
    }
    return data_size;
}

static confirm_state DmaIncToArtey(DmaInc_t inc) {
    confirm_state state = FALSE;
    switch((uint8_t)inc) {
    case DMA_INC_OFF:
        state = FALSE;
        break;
    case DMA_INC_ON:
        state = TRUE;
        break;
    }
    return state;
}
static confirm_state DmaModeToArtery(DmaMode_t mode) {
    confirm_state loop_mode = FALSE;
    switch((uint8_t)mode) {
    case DMA_MODE_CIRCULAR:
        loop_mode = TRUE;
        break;
    case DMA_MODE_NORMAL:
        loop_mode = FALSE;
        break;
    case DMA_MODE_PFCTRL:
        loop_mode = FALSE;
        break;
    }
    return loop_mode;
}

static dma_priority_level_type DmaPriorityToArtery(DmaPriority_t priority) {
    dma_priority_level_type priority_level = 0;
    switch((uint8_t)priority) {
    case DMA_PRIOR_LOW:
        priority_level = DMA_PRIORITY_LOW;
        break;
    case DMA_PRIOR_MED:
        priority_level = DMA_PRIORITY_MEDIUM;
        break;
    case DMA_PRIOR_HIGH:
        priority_level = DMA_PRIORITY_HIGH;
        break;
    case DMA_PRIOR_VERY_HIGH:
        priority_level = DMA_PRIORITY_VERY_HIGH;
        break;
    }
    return priority_level;
}

static dma_dir_type DmaDirToArtery(DmaDir_t dir) {
    dma_dir_type dir_at32 = DMA_DIR_MEMORY_TO_MEMORY;
    switch((uint8_t)dir) {
    case DMA_MCAL_DIR_PERIPH_TO_MEMORY:
        dir_at32 = DMA_DIR_PERIPHERAL_TO_MEMORY;
        break;
    case DMA_MCAL_DIR_MEMORY_TO_PERIPH:
        dir_at32 = DMA_DIR_MEMORY_TO_PERIPHERAL;
        break;
    case DMA_MCAL_DIR_MEMORY_TO_MEMORY:
        dir_at32 = DMA_DIR_MEMORY_TO_MEMORY;
        break;
    }
    return dir_at32;
}

bool dma_init_custom(void) {
    bool res = true;
    log_level_get_set(DMA, LOG_LEVEL_INFO);

    uint32_t cnt = dma_get_cnt();
    if(0 == cnt) {
        LOG_WARNING(DMA, "NoConfig");
    }

    return res;
}

static const DmaInfo_t DmaInfo[] = {
    {
        .num = 1,
        .clock_type = CRM_DMA1_PERIPH_CLOCK,
        .DMAx = DMA1,
        .valid = true,
    },
    {
        .num = 2,
        .clock_type = CRM_DMA2_PERIPH_CLOCK,
        .DMAx = DMA2,
        .valid = true,
    },
};

COMPONENT_GET_INFO(Dma)

#ifdef HAS_AT32F43X
#define DMA_CHAN_MUX_IRQ_INFO_COMPOSER(DDD, CCC)                                                                       \
    .dmamux_channelx = DMA##DDD##MUX_CHANNEL##CCC, .irq_n = DMA##DDD##_Channel##CCC##_IRQn,
#else
#define DMA_CHAN_MUX_IRQ_INFO_COMPOSER(DDD, CCC)
#endif // HAS_AT32F43X

#define DMA_CHAN_INFO_COMPOSER(DDD, CCC)                                                                               \
    {                                                                                                                  \
        .dma_num = DDD,                                                                                                \
        .channel = DMA_CHAN_##CCC,                                                                                     \
        .dmax_channely = DMA##DDD##_CHANNEL##CCC,                                                                      \
        DMA_CHAN_MUX_IRQ_INFO_COMPOSER(DDD, CCC).Flag.error = DMA##DDD##_DTERR##CCC##_FLAG,                            \
        .Flag.done = DMA##DDD##_FDT##CCC##_FLAG,                                                                       \
        .Flag.half = DMA##DDD##_HDT##CCC##_FLAG,                                                                       \
        .Flag.global = DMA##DDD##_GL##CCC##_FLAG,                                                                      \
        .valid = true,                                                                                                 \
    },

#define DMA_CHANNEL_INFO                                                                                               \
    DMA_CHAN_INFO_COMPOSER(1, 1)                                                                                       \
    DMA_CHAN_INFO_COMPOSER(1, 2)                                                                                       \
    DMA_CHAN_INFO_COMPOSER(1, 3)                                                                                       \
    DMA_CHAN_INFO_COMPOSER(1, 4)                                                                                       \
    DMA_CHAN_INFO_COMPOSER(1, 5)                                                                                       \
    DMA_CHAN_INFO_COMPOSER(1, 6)                                                                                       \
    DMA_CHAN_INFO_COMPOSER(1, 7)                                                                                       \
    DMA_CHAN_INFO_COMPOSER(2, 1)                                                                                       \
    DMA_CHAN_INFO_COMPOSER(2, 2)                                                                                       \
    DMA_CHAN_INFO_COMPOSER(2, 3)                                                                                       \
    DMA_CHAN_INFO_COMPOSER(2, 4)                                                                                       \
    DMA_CHAN_INFO_COMPOSER(2, 5)                                                                                       \
    DMA_CHAN_INFO_COMPOSER(2, 6)                                                                                       \
    DMA_CHAN_INFO_COMPOSER(2, 7)

static const DmaChannelInfo_t DmaChannelInfo[] = {DMA_CHANNEL_INFO
#if 0
        // just as an example:
       {
   .valid = true,
   .dma_num = 2,
   .dmax_channely = DMA2_CHANNEL2,
   .channel = DMA_CHAN_2,
   .Flag.error =DMA2_DTERR2_FLAG,
   .Flag.done =DMA2_FDT2_FLAG,
   .Flag.half = DMA2_HDT2_FLAG;
   .Flag.global = DMA2_GL2_FLAG;
   .dmamux_channelx = DMA2MUX_CHANNEL2,
   .irq_n=DMA2_Channel2_IRQn,

       },
#endif
};

const DmaChannelInfo_t* DmaChannelGetInfo(uint8_t num, DmaChannel_t channel) {
    DmaChannelInfo_t* Info = NULL;
    uint32_t cnt = ARRAY_SIZE(DmaChannelInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(num == DmaChannelInfo[i].dma_num) {
            if(channel == DmaChannelInfo[i].channel) {
                Info = &DmaChannelInfo[i];
            }
        }
    }
    return Info;
}

bool dma_init_one(uint8_t num) {
    bool res = false;
    const DmaConfig_t* Config = DmaGetConfig(num);
    if(Config) {
#ifdef HAS_DMA_DIAG
        LOG_WARNING(DMA, "%s", DmaConfigToStr(Config));
#endif
        DmaHandle_t* Node = DmaGetNode(num);
        if(Node) {
            const DmaInfo_t* Info = DmaGetInfo(num);
            if(Info) {
                Node->DMAx = Info->DMAx;
                LOG_WARNING(DMA, "Init,DMA%u:0x%08x", num, Info->DMAx);
                crm_periph_clock_enable(Info->clock_type, TRUE);
#ifdef HAS_AT32F43X
                dmamux_enable(Info->DMAx, TRUE);
#endif // HAS_AT32F43X
                res = true;
            }
        }
    }

    uint32_t cnt = dma_get_cnt();
    if(0 == cnt) {
        res = true;
    }

    return res;
}

bool dma_channel_init_custom(void) {
    bool res = true;

    uint32_t cnt = dma_channel_get_cnt();
    if(0 == cnt) {
        LOG_WARNING(DMA, "NoChanConfigs");
    }

    return res;
}

static bool dma_mux_set_ll(DmaChannelInfo_t* ChannelInfo, uint8_t dma_mux) {
    bool res = false;
    if(ChannelInfo) {
#ifdef HAS_AT32F43X
        dmamux_requst_id_sel_type dmamux_code = dma_mux;
        // LOG_DEBUG(DMA, "DMA%u,CH%u,MUX:%u=%s", ChannelInfo->dma_num, ChannelInfo->channel, dma_mux,
        //            DmaReqSelToStr(dma_mux));
        dmamux_init(ChannelInfo->dmamux_channelx, dmamux_code);
        res = true;
#endif // HAS_AT32F43X
    }

    return res;
}

bool dma_mux_get(uint8_t dma_num, DmaChannel_t channel, uint8_t* const dma_mux) {
    bool res = false;
    DmaChannelInfo_t* ChannelInfo = DmaChannelGetInfo(dma_num, channel);
    if(ChannelInfo) {
        if(dma_mux) {
#ifdef HAS_AT32F43X
            *dma_mux = ChannelInfo->dmamux_channelx->muxctrl_bit.reqsel;
            LOG_PARN(DMA, "DMA%u,CH%u,MUX:%u=%s", dma_num, channel, *dma_mux, DmaReqSelToStr(*dma_mux));
            res = true;
#endif // HAS_AT32F43X
        }
    }
    return res;
}

bool dma_mux_set(uint8_t dma_num, DmaChannel_t channel, uint8_t dma_mux) {
    bool res = false;
    const DmaChannelInfo_t* ChannelInfo = DmaChannelGetInfo(dma_num, channel);
    if(ChannelInfo) {
        res = dma_mux_set_ll(ChannelInfo, dma_mux);
        res = false;
    }

    return res;
}

bool dma_get_spare(DmaStream_t* const DmaStream) {
    bool res = false;
    uint8_t dma_num = 0;
    for(dma_num = 0; dma_num <= DMA_COUNT; dma_num++) {
        uint8_t channel = 0;
        for(channel = DMA_CHAN_0; channel < DMA_CHAN_15; channel++) {
            DmaChannelHandle_t* ChannelNode = DmaChannelGetNodeItem(dma_num, channel);
            if(ChannelNode) {
                if(false == ChannelNode->busy) {
                    DmaStream->dma_num = dma_num;
                    DmaStream->channel = channel;
                    res = true;
                }
            }
        }
    }
    return res;
}

bool dma_channel_stop(DmaPad_t DmaPad) {
    bool res = false;
    const DmaChannelInfo_t* ChannelInfo = DmaChannelGetInfo(DmaPad.dma_num, DmaPad.channel);
    if(ChannelInfo) {
        dma_reset(ChannelInfo->dmax_channely);
        dma_channel_enable(ChannelInfo->dmax_channely, FALSE);
        res = true;
    }
    return res;
}

bool dma_channel_restart(DmaPad_t DmaPad, uint16_t data_number) {
    bool res = false;
    const DmaChannelInfo_t* ChannelInfo = DmaChannelGetInfo(DmaPad.dma_num, DmaPad.channel);
    if(ChannelInfo) {
        /*The number of data to transfer is from 0x0 to 0xFFFF. DMA_CxDTCNT
          register can only written when the CHEN bit in the
          corresponding channel is set 0. The value is decremented
          after each DMA transfer.*/
        dma_channel_enable(ChannelInfo->dmax_channely, FALSE);
        dma_data_number_set(ChannelInfo->dmax_channely, data_number);
        dma_channel_enable(ChannelInfo->dmax_channely, TRUE);
        res = true;
    }
    return res;
}

bool dma_channel_init_one_ll(const DmaChannelConfig_t* const Config) {
    bool res = false;
    if(Config) {
        // LOG_WARNING(DMA, "%s", DmaChannelConfigToStr(Config));
        DmaChannelHandle_t* Node = DmaChannelGetNode(Config->num);
        if(Node) {
            res = dma_channel_init_common_one(Config, Node);
            // LOG_INFO(DMA, "DMA%u,Ch%u,Reset", Config->dma_num, Config->channel);
            const DmaChannelInfo_t* ChannelInfo = DmaChannelGetInfo(Config->dma_num, Config->channel);
            if(ChannelInfo) {
                const DmaInfo_t* Info = DmaGetInfo(Config->dma_num);
                if(Info) {
                    crm_periph_clock_enable(Info->clock_type, TRUE);
                    dma_reset(ChannelInfo->dmax_channely); //!!!
#ifdef HAS_AT32F43X
                    dmamux_enable(Info->DMAx, TRUE);
#endif // HAS_AT32F43X
                }
                // dmamux_init(ChannelInfo->dmamux_channelx, Config->mux);

                res = dma_mux_set_ll(ChannelInfo, Config->mux);

                dma_init_type InitStruct = {0};
                dma_default_para_init(&InitStruct);
                /* dma transmit direction, peripheral as source or as destnation  */
                /* counter to transfer (0~0xFFFF) */
                InitStruct.buffer_size = Config->buffer_size;
                InitStruct.direction = DmaDirToArtery(Config->dir);
                /* when loop mode enable, buffer size will reload if count to 0*/
                InitStruct.loop_mode_enable = DmaModeToArtery(Config->mode);
                InitStruct.memory_base_addr = Config->memory_base_addr;
                /* memory address increment after one transmit */
                InitStruct.memory_inc_enable = DmaIncToArtey(Config->mem_inc);
                /* memory data width for transmit */
                InitStruct.memory_data_width = DmaAligmentToMemoryArtery(Config->aligment_mem);
                /* periphera address increment after one transmit */
                InitStruct.peripheral_inc_enable = DmaIncToArtey(Config->per_inc);
                /* peripheral data width for transmit */
                InitStruct.peripheral_data_width = DmaAligmentToPeripheralArtery(Config->aligment_per);
                InitStruct.peripheral_base_addr = Config->peripheral_base_addr;
                /* dma priority can choose from very high,high,dedium or low */
                InitStruct.priority = DmaPriorityToArtery(Config->priority);
                dma_init(ChannelInfo->dmax_channely, &InitStruct);

                /* dma half data transfer interrupt */
                dma_interrupt_enable(ChannelInfo->dmax_channely, DMA_HDT_INT, TRUE);
                /* dma full data transfer interrupt */
                dma_interrupt_enable(ChannelInfo->dmax_channely, DMA_FDT_INT, TRUE);
                /* dma errorr interrupt */
                dma_interrupt_enable(ChannelInfo->dmax_channely, DMA_DTERR_INT, TRUE);

                nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
                nvic_irq_enable(ChannelInfo->irq_n, 2, 2);

                NVIC_SetPriority(ChannelInfo->irq_n, 4);
                NVIC_EnableIRQ(ChannelInfo->irq_n);

                dma_channel_enable(ChannelInfo->dmax_channely, TRUE);
                res = true;

                // LOG_INFO(DMA, "DMA%u,Ch%u,initDone", Config->dma_num, Config->channel);
                Node->init = true;

            } else {
                // LOG_ERROR(DMA, "%u,InfoErr", Config->num);
                res = false;
            }
        } else {
            // LOG_ERROR(DMA, "%u,NodeErr", Config->num);
            res = false;
        }
    } else {
        // LOG_ERROR(DMA, "%u,ConfigErr", Config->num);
        res = false;
    }

    uint32_t cnt = dma_channel_get_cnt();
    if(0 == cnt) {
        res = true;
    }
    return res;
}

bool dma_channel_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(DMA, "ChanInit:%u", num);
    const DmaChannelConfig_t* Config = DmaChannelGetConfig(num);
    if(Config) {
        res = dma_channel_init_one_ll(Config);
    } else {
        LOG_ERROR(DMA, "%u,ConfigErr", num);
    }

    uint32_t cnt = dma_channel_get_cnt();
    if(0 == cnt) {
        res = true;
    }
    return res;
}

bool dma_memcpy(void* const destination, const void* const source, size_t size) {
    bool res = false;
    if(destination) {
        if(source) {
            if(size) {
                res = true;
            }
        }
    }

    if(res) {
        DmaChannelHandle_t* Node = DmaChannelGetNodeItem(1, 1);
        if(Node) {
            Node->done = false;
        }

        res = false;
        /*TODO get spare DMA and channel*/
        /* enable dma1 clock */
        crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);

        /* dma1 channel1 configuration */
        dma_reset(DMA1_CHANNEL7);
        dma_init_type InitStruct = {0};

        dma_default_para_init(&InitStruct);

        InitStruct.buffer_size = size;
        InitStruct.direction = DMA_DIR_MEMORY_TO_MEMORY;
        InitStruct.memory_base_addr = (uint32_t)destination;
        InitStruct.peripheral_base_addr = (uint32_t)source;
        InitStruct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
        InitStruct.memory_inc_enable = TRUE;
        InitStruct.peripheral_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
        InitStruct.peripheral_inc_enable = TRUE;
        InitStruct.priority = DMA_PRIORITY_MEDIUM;
        InitStruct.loop_mode_enable = FALSE;

        dma_init(DMA1_CHANNEL7, &InitStruct);

        /* enable transfer full data interrupt */
        /* dma full data transfer interrupt */
        dma_interrupt_enable(DMA1_CHANNEL7, DMA_FDT_INT, TRUE);
        /* dma half data transfer interrupt */
        dma_interrupt_enable(DMA1_CHANNEL7, DMA_HDT_INT, TRUE);
        /* dma errorr interrupt */
        dma_interrupt_enable(DMA1_CHANNEL7, DMA_DTERR_INT, TRUE);

        /* dma1 channel1 interrupt nvic init */
        nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
        nvic_irq_enable(DMA1_Channel1_IRQn, 1, 0);

        dma_channel_enable(DMA1_CHANNEL7, TRUE);

        res = dma_wait_done(1, 1);
    }
    return res;
}
