#include "i2s_mcal.h"

#include <stdbool.h>
#include <string.h>

#include "at32_misc.h"
#include "clock_custom_const.h"
#include "clock_custom_diag.h"
#include "clock_diag.h"
#include "clock_utils.h"
#include "code_generator.h"
#include "gpio_mcal.h"
#include "i2s_config.h"
#include "i2s_custom_diag.h"
#include "i2s_custom_drv.h"
#include "i2s_custom_types.h"
#include "i2s_diag.h"
#include "log.h"
#include "microcontroller_const.h"

#ifdef HAS_DMA
#include "dma_mcal.h"
#include "i2s_dma_mcal.h"
#endif /*HAS_DMA*/

#include "param_drv.h"

#ifdef HAS_DDS
#include "dds_drv.h"
#endif /*HAS_DDS*/

#include "artery_at32f4xx.h"
#include "hal_diag.h"
#include "i2s_types.h"

#ifdef HAS_DDS
#include "dds_drv.h"
#endif /*HAS_DDS*/

#ifndef HAS_I2S
#error "Add HAS_I2S"
#endif /*HAS_I2S*/

const Reg32_t I2sReg[] = {
    {
        .valid = true,
        .name = "SPI_CTRL1",
        .offset = 0x00,
    },
    {
        .valid = true,
        .name = "SPI_CTRL2",
        .offset = 0x04,
    },
    {
        .valid = true,
        .name = "SPI_STS",
        .offset = 0x08,
    },
    {
        .valid = true,
        .name = "SPI_DT",
        .offset = 0x0C,
    },
    {
        .valid = true,
        .name = "SPI_CPOLY",
        .offset = 0x10,
    },
    {
        .valid = true,
        .name = "SPI_RCRC",
        .offset = 0x14,
    },
    {
        .valid = true,
        .name = "SPI_TCRC",
        .offset = 0x18,
    },
    {
        .valid = true,
        .name = "SPI_I2SCTRL",
        .offset = 0x1C,
    },
    {
        .valid = true,
        .name = "SPI_I2SCLKP",
        .offset = 0x20,
    },

};

static const I2sInfo_t I2sInfo[] = {
    {
        .num = 1,
        .valid = true,
        .I2Sx = SPI1,
        .clock_bus = CLOCK_BUS_AHB2,
        .irq_n = SPI1_IRQn,
        .clock_type = CRM_SPI1_PERIPH_CLOCK,
#ifdef HAS_I2S1
        .CallBackTxHalf = I2s1DmaCallBackTxHalf,
        .CallBackTxDone = I2s1DmaCallBackTxDone,
        .CallBackRxHalf = I2s1DmaCallBackRxHalf,
        .CallBackRxDone = I2s1DmaCallBackRxDone,
#endif
    },

    {
        .num = 2,
        .valid = true,
        .I2Sx = SPI2, /*I2S2EXT*/
        .clock_bus = CLOCK_BUS_AHB1,
        .irq_n = SPI2_I2S2EXT_IRQn,
        .clock_type = CRM_SPI2_PERIPH_CLOCK,

#ifdef HAS_I2S2
        .CallBackTxHalf = I2s2DmaCallBackTxHalf,
        .CallBackTxDone = I2s2DmaCallBackTxDone,
        .CallBackRxHalf = I2s2DmaCallBackRxHalf,
        .CallBackRxDone = I2s2DmaCallBackRxDone,
#endif

    },

#ifdef HAS_I2S3
    {
        .num = 3,
        .valid = true,
        .I2Sx = I2S3EXT,
        .clock_bus = CLOCK_BUS_AHB1,
        .irq_n = SPI3_I2S3EXT_IRQn,
        .clock_type = CRM_SPI3_PERIPH_CLOCK,
        .CallBackTxHalf = I2s3DmaCallBackTxHalf,
        .CallBackTxDone = I2s3DmaCallBackTxDone,
        .CallBackRxHalf = I2s3DmaCallBackRxHalf,
        .CallBackRxDone = I2s3DmaCallBackRxDone,
    },
#endif

    {
        .num = 4,
        .valid = true,
        .I2Sx = SPI4,
        .clock_bus = CLOCK_BUS_AHB2,
        .irq_n = SPI4_IRQn,
        .clock_type = CRM_SPI4_PERIPH_CLOCK,
#ifdef HAS_I2S4
        .CallBackTxHalf = I2s4DmaCallBackTxHalf,
        .CallBackTxDone = I2s4DmaCallBackTxDone,
        .CallBackRxHalf = I2s4DmaCallBackRxHalf,
        .CallBackRxDone = I2s4DmaCallBackRxDone,
#endif
    },

    {
        .num = 5,
        .valid = true,
        .I2Sx = I2S2EXT,
        .clock_bus = CLOCK_BUS_AHB2,
        .irq_n = SPI2_I2S2EXT_IRQn,
        .clock_type = CRM_SPI2_PERIPH_CLOCK,
#ifdef HAS_I2S5
        .CallBackTxHalf = I2s5DmaCallBackTxHalf,
        .CallBackTxDone = I2s5DmaCallBackTxDone,
        .CallBackRxHalf = I2s5DmaCallBackRxHalf,
        .CallBackRxDone = I2s5DmaCallBackRxDone,
#endif

    },

};

COMPONENT_GET_INFO(I2s)

static i2s_operation_mode_type I2sBusRoleToArteryRole(I2sDirRole_t bus_dir_role) {
    i2s_operation_mode_type op_mode = I2S_MODE_MASTER_TX;
    switch((uint32_t)bus_dir_role) {
    case I2S_DIR_BUS_MODE_SLAVE_TX:
        op_mode = I2S_MODE_SLAVE_TX;
        break;
    case I2S_DIR_BUS_MODE_SLAVE_RX:
        op_mode = I2S_MODE_SLAVE_RX;
        break;
    case I2S_DIR_BUS_MODE_MASTER_TX:
        op_mode = I2S_MODE_MASTER_TX;
        break;
    case I2S_DIR_BUS_MODE_MASTER_RX:
        op_mode = I2S_MODE_MASTER_RX;
        break;

    case I2S_DIR_BUS_MODE_SLAVE:
        op_mode = I2S_MODE_MASTER_TX;
        break;
    case I2S_DIR_BUS_MODE_MASTER:
        op_mode = I2S_MODE_MASTER_TX;
        break;
    }
    return op_mode;
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

static i2s_data_channel_format_type I2sDataFormatToArteryDf(I2sDataFormat_t data_format) {
    i2s_data_channel_format_type data_channel_format = I2S_DATA_24BIT_CHANNEL_32BIT;
    switch((uint32_t)data_format) {
    case I2S_DATA_FORMAT_8B:
        data_channel_format = I2S_DATA_16BIT_CHANNEL_16BIT;
        break;
    case I2S_DATA_FORMAT_16B:
        data_channel_format = I2S_DATA_16BIT_CHANNEL_16BIT;
        break;
    case I2S_DATA_FORMAT_16B_EXTENDED:
        data_channel_format = I2S_DATA_16BIT_CHANNEL_32BIT;
        break;
    case I2S_DATA_FORMAT_24B:
        data_channel_format = I2S_DATA_24BIT_CHANNEL_32BIT;
        break;
    case I2S_DATA_FORMAT_32B:
        data_channel_format = I2S_DATA_32BIT_CHANNEL_32BIT;
        break;
    default:
        break;
    }
    return data_channel_format;
}

static confirm_state MclkToBool(MclkOut_t mclk_out) {
    confirm_state mclk_output = FALSE;
    switch((uint32_t)mclk_out) {
    case I2S_MCLKOUT_ON:
        mclk_output = TRUE;
        break;
    case I2S_MCLKOUT_OFF:
        mclk_output = FALSE;
        break;
    default:
        mclk_output = FALSE;
        break;
    }
    return mclk_output;
}

static i2s_audio_sampling_freq_type I2sSamplingFreqToArterySf(AudioFreq_t audio_freq_hz) {
    i2s_audio_sampling_freq_type sampling_freq = I2S_AUDIO_FREQUENCY_48K;
    switch((uint32_t)audio_freq_hz) {
    case I2S_AUDIO_FREQ_8K:
        sampling_freq = I2S_AUDIO_FREQUENCY_8K;
        break;
    case I2S_AUDIO_FREQ_11K:
        sampling_freq = I2S_AUDIO_FREQUENCY_11_025K;
        break;
    case I2S_AUDIO_FREQ_16K:
        sampling_freq = I2S_AUDIO_FREQUENCY_16K;
        break;
    case I2S_AUDIO_FREQ_22K:
        sampling_freq = I2S_AUDIO_FREQUENCY_22_05K;
        break;
    case I2S_AUDIO_FREQ_32K:
        sampling_freq = I2S_AUDIO_FREQUENCY_32K;
        break;
    case I2S_AUDIO_FREQ_41K:
        sampling_freq = I2S_AUDIO_FREQUENCY_44_1K;
        break;
    case I2S_AUDIO_FREQ_48K:
        sampling_freq = I2S_AUDIO_FREQUENCY_48K;
        break;
    case I2S_AUDIO_FREQ_88K:
        sampling_freq = I2S_AUDIO_FREQUENCY_48K;
        break;
    case I2S_AUDIO_FREQ_96K:
        sampling_freq = I2S_AUDIO_FREQUENCY_96K;
        break;
    case I2S_AUDIO_FREQ_176K:
        sampling_freq = I2S_AUDIO_FREQUENCY_48K;
        break;
    case I2S_AUDIO_FREQ_192K:
        sampling_freq = I2S_AUDIO_FREQUENCY_192K;
        break;
    case I2S_AUDIO_FREQ_384K:
        sampling_freq = I2S_AUDIO_FREQUENCY_192K;
        break;
    case I2S_AUDIO_FREQ_768K:
        sampling_freq = I2S_AUDIO_FREQUENCY_192K;
        break;

    case I2S_AUDIO_FREQ_DEFAULT:
        sampling_freq = I2S_AUDIO_FREQUENCY_48K;
        break;
    }
    return sampling_freq;
}

static i2s_clock_polarity_type ClockPolarityToArteryCp(Cpol_t cpol) {
    i2s_clock_polarity_type clock_polarity = I2S_CLOCK_POLARITY_HIGH;
    switch((uint32_t)cpol) {
    case I2S_CLOCK_POL_LOW:
        clock_polarity = I2S_CLOCK_POLARITY_LOW;
        break;
    case I2S_CLOCK_POL_HIGH:
        clock_polarity = I2S_CLOCK_POLARITY_HIGH;
        break;
    }
    return clock_polarity;
}

static bool i2s_init_gpio(const I2sConfig_t* Config, ConnectivitDir_t direction) {
    bool res = true;
    if(I2S_MODE_INTERRUPT == Config->mode) {
        res = false;
        switch(direction) {
        case CONNECT_DIR_TRANSMITTER: {
            res = gpio_init_one(&Config->GpioSdOut);
            res = gpio_deinit_one(Config->GpioSdIn.pad);
        } break;
        case CONNECT_DIR_RECEIVER: {
            res = gpio_deinit_one(Config->GpioSdOut.pad);
            res = gpio_init_one(&Config->GpioSdIn);
        } break;
        default: {
            // res = gpio_init_one(&Config->GpioSdOut);
            // res = gpio_deinit_one(Config->GpioSdIn.pad);
        } break;
        }
    }
    return res;
}

static bool i2s_init_interrupts(const I2sConfig_t* Config, I2sHandle_t* Node, I2sInfo_t* Info) {
    bool res = false;
    LOG_WARNING(I2S, "Init,Interrupts");
    nvic_irq_enable(Info->irq_n, 10, 10);
    spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_RDBF_INT, TRUE);
    spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_TDBE_INT, TRUE);
    spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_ERROR_INT, TRUE);
    spi_i2s_flag_clear(Node->I2Sx, SPI_I2S_TDBE_FLAG);
    spi_i2s_flag_clear(Node->I2Sx, I2S_ACS_FLAG);
    spi_i2s_flag_clear(Node->I2Sx, SPI_I2S_BF_FLAG);
    res = true;
    return res;
}

static bool i2s_init_ll(const I2sConfig_t* Config, I2sHandle_t* Node, I2sInfo_t* Info, I2sDirRole_t bus_dir_role) {
    bool res = false;
    Node->I2Sx = Info->I2Sx;
    crm_periph_clock_enable(Info->clock_type, TRUE);
    spi_i2s_reset(Node->I2Sx);

    i2s_init_type I2sInitStruct = {0};
    i2s_default_para_init(&I2sInitStruct);

    I2sInitStruct.audio_protocol = I2S_AUDIO_PROTOCOL_PHILLIPS;
    I2sInitStruct.audio_sampling_freq = I2sSamplingFreqToArterySf(Config->audio_freq_hz);
    I2sInitStruct.data_channel_format = I2sDataFormatToArteryDf(Config->data_format);
    I2sInitStruct.clock_polarity = ClockPolarityToArteryCp(Config->cpol);
    I2sInitStruct.mclk_output_enable = MclkToBool(Config->mclk_out);
    I2sInitStruct.operation_mode = I2sBusRoleToArteryRole(bus_dir_role);

    i2s_init(Node->I2Sx, &I2sInitStruct);

    res = true;
    return res;
}

bool i2s_init_role_one_ll(const I2sConfig_t* Config, I2sHandle_t* Node, I2sDirRole_t bus_dir_role) {
    bool res = false;
    if(Config) {
        LOG_WARNING(I2S, "I2S%u,Set,Role:%s", Config->num, I2sBusRole2Str(bus_dir_role));
        LOG_WARNING(I2S, "%s", I2sConfigToStr(Config));
        res = i2s_init_gpio(Config, Config->direction);
        if(Node) {
            i2s_init_common(Config, Node);
            const I2sBusDirInfo_t* BusInfo = I2S_DirRoleToInfo(bus_dir_role);
            if(BusInfo) {
                Node->bus_role = BusInfo->bus_role;
                Node->direction = BusInfo->direction;
            }
            I2sInfo_t* Info = I2sGetInfo(Config->num);
            if(Info) {
                res = i2s_init_ll(Config, Node, Info, bus_dir_role);
                switch(Config->mode) {
                case I2S_MODE_INTERRUPT: {
                    res = i2s_init_interrupts(Config, Node, Info);
                } break;
                case I2S_MODE_DMA: {
#ifdef HAS_I2S_DMA
                    res = i2s_init_dma(Config, Node);
#endif
                } break;
                default: {
                    LOG_ERROR(I2S, "UndefMode");
                    res = false;
                } break;
                }
                i2s_enable(Node->I2Sx, FALSE);
            }
        }
    }

    return res;
}

static I2sOperation_t I2sBusRoleToArteryOperation(I2sDirRole_t bus_dir_role) {
    I2sOperation_t operation = OPERSEL_SLAVE_RX;
    switch((uint32_t)bus_dir_role) {
    case I2S_DIR_BUS_MODE_SLAVE:
        operation = OPERSEL_SLAVE_RX;
        break;
    case I2S_DIR_BUS_MODE_MASTER:
        operation = OPERSEL_MASTER_TX;
        break;
    case I2S_DIR_BUS_MODE_SLAVE_TX:
        operation = OPERSEL_SLAVE_TX;
        break;
    case I2S_DIR_BUS_MODE_SLAVE_RX:
        operation = OPERSEL_SLAVE_RX;
        break;
    case I2S_DIR_BUS_MODE_MASTER_TX:
        operation = OPERSEL_MASTER_TX;
        break;
    case I2S_DIR_BUS_MODE_MASTER_RX:
        operation = OPERSEL_MASTER_RX;
        break;
    }
    return operation;
}

static bool i2s_interrup_stop_ll(I2sHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->play = false;
        Node->rec = false;
        res = true;
    }
    return res;
}

static bool i2s_dir_bus_dir_role_set(uint8_t num, I2sDirRole_t bus_dir_role) {
    bool res = false;
    LOG_DEBUG(I2S, "I2S%u,Set,Role:%s", num, I2sBusRole2Str(bus_dir_role));
    const I2sInfo_t* Info = I2sGetInfo(num);
    if(Info) {
        Info->I2Sx->i2sctrl_bit.opersel = I2sBusRoleToArteryOperation(bus_dir_role);
        res = true;
    }

    return res;
}

bool i2s_init_one(uint8_t num) {
    bool res = false;
    const I2sConfig_t* Config = I2sGetConfig(num);
    if(Config) {
        I2sHandle_t* Node = I2sGetNode(num);
        if(Node) {
            I2sDirRole_t bus_dir_role = i2s_role_and_dir_to_dir_bus(Node->bus_role, Node->direction);
            res = i2s_init_role_one_ll(Config, Node, bus_dir_role);
        }
    }

    return res;
}

bool i2s_write_wait(uint8_t num, uint16_t* array, uint16_t tx_data) {
    bool res = false;
    LOG_DEBUG(I2S, "WriteWait i2s:%u Words:%u", num, tx_data);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        spi_i2s_data_transmit(Node->I2Sx, tx_data);
        res = true;
    } else {
        LOG_ERROR(I2S, "%u NodeErr", num);
    }
    return res;
}

static bool i2s_api_write_interrupts(uint8_t num, SampleType_t* const array, size_t size) {
    bool res = false;
    LOG_INFO(I2S, "Write,I2S%u,Words:%u", num, size);

    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->state = I2S_STATE_RUN;
        Node->Tx.array = array;
        Node->Tx.size = size * 2; /*1 sample 2 channel*/
        Node->Tx.index = 0;
        Node->play = true;
        spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_TDBE_INT, TRUE);
        spi_i2s_data_transmit(Node->I2Sx, array[0]);
        i2s_enable(Node->I2Sx, TRUE);
        res = true;
    }
    return res;
}

bool i2s_api_write(uint8_t num, SampleType_t* const array, size_t size) {
    bool res = false;
    LOG_INFO(I2S, "Write I2S_%u,Words:%u", num, size);

    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        const I2sConfig_t* Config = I2sGetConfig(num);
        if(Config) {
            I2sDirRole_t bus_dir_role = i2s_role_and_dir_to_dir_bus(Node->bus_role, CONNECT_DIR_TRANSMITTER);
            res = i2s_dir_bus_dir_role_set(num, bus_dir_role);
            res = i2s_init_gpio(Config, CONNECT_DIR_TRANSMITTER);

            switch(Node->mode) {
            case I2S_MODE_INTERRUPT: {
                res = i2s_api_write_interrupts(num, array, size);
            } break;
            case I2S_MODE_DMA: {
                res = false;
#ifdef HAS_I2S_DMA
                res = i2s_api_write_dma(num, array, size, DMA_MODE_CIRCULAR);
#endif
            } break;
            default:
                res = false;
                break;
            }
        }
    }
    return res;
}

/*
 * samples must be even
 */
static bool i2s_api_read_int(uint8_t num, SampleType_t* const array, size_t samples) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        memset(array, 0, sizeof(SampleType_t) * samples);
        const I2sConfig_t* Config = I2sGetConfig(num);
        if(Config) {
            res = i2s_init_gpio(Config, CONNECT_DIR_RECEIVER);
        }

        LOG_INFO(I2S, "I2S%u_Read:%u sam", num, samples);
        Node->state = I2S_STATE_REC;
        Node->rec = true;
        Node->Rx.index = 0;
        Node->Rx.size = samples;
        Node->Rx.array = array;
        spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_RDBF_INT, TRUE);
        spi_i2s_data_receive(Node->I2Sx);
        i2s_enable(Node->I2Sx, TRUE);
        res = true;
    }
    return res;
}

/*
 * samples must be even
 */
bool i2s_api_read(uint8_t num, SampleType_t* const array, size_t samples) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        const I2sConfig_t* Config = I2sGetConfig(num);
        if(Config) {
            I2sDirRole_t bus_dir_role = i2s_role_and_dir_to_dir_bus(Node->bus_role, CONNECT_DIR_RECEIVER);
            res = i2s_dir_bus_dir_role_set(num, bus_dir_role);
            res = i2s_init_gpio(Config, CONNECT_DIR_RECEIVER);
            switch((uint32_t)Node->mode) {
            case I2S_MODE_INTERRUPT: {
                res = i2s_api_read_int(num, array, samples);
            } break;
            case I2S_MODE_DMA: {
                res = false;
#ifdef HAS_I2S_DMA
                res = i2s_api_read_dma(num, array, samples, DMA_MODE_CIRCULAR);
#endif
            } break;
            default:
                res = false;
                break;
            }
        }
    }
    return res;
}

bool i2s_read_write(uint8_t num, uint32_t tx_data) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        spi_i2s_data_transmit(Node->I2Sx, tx_data);
        uint16_t data_value = spi_i2s_data_receive(Node->I2Sx);
        LOG_DEBUG(I2S, "RxWord:0x%x", data_value);
    }
    return res;
}

uint32_t i2s_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(I2sReg);
    return cnt;
}

uint32_t i2s_get_sample_rate(uint8_t num) {
    uint32_t sample_rate = 0;
    const I2sConfig_t* Config = I2sGetConfig(num);
    if(Config) {
        sample_rate = I2sSampleRate2Hz(Config->audio_freq_hz);
    }
    return sample_rate;
}

bool i2s_stop(uint8_t num) {
    bool res = false;
    LOG_INFO(I2S, "%u,Stop", num);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        switch((uint32_t)Node->mode) {
        case I2S_MODE_INTERRUPT: {
            res = i2s_interrup_stop_ll(Node);
        } break;
        case I2S_MODE_DMA: {
#ifdef HAS_I2S_DMA
            res = i2s_dma_ctrl_ll(Node, false);
#endif
        } break;
        }
    } else {
        LOG_ERROR(I2S, "NodeErr");
    }

    if(res) {
        Node->state = I2S_STATE_IDLE;
    }

    return res;
}

static bool i2s_start(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        i2s_enable(Node->I2Sx, TRUE);
    }
    return res;
}

bool i2s_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    switch((uint32_t)on_off) {
    case true: {
        res = i2s_start(num);
    } break;
    case false: {
        res = i2s_stop(num);

    } break;
    default: {
    } break;
    }
    return res;
}

bool i2s_dir_bus_role_get(uint8_t num, I2sDirRole_t* const bus_dir_role) {
    bool res = false;
    if(bus_dir_role) {
        I2sHandle_t* Node = I2sGetNode(num);
        if(res) {
            *bus_dir_role = i2s_role_and_dir_to_dir_bus(Node->bus_role, Node->direction);
            ;
        } else {
            *bus_dir_role = I2S_DIR_BUS_MODE_UNDEF;
        }
    }
    return res;
}

bool i2s_config_tx(uint8_t num, I2sDataFormat_t word_size, uint8_t channels, AudioFreq_t audio_freq_hz) {
    return false;
}

bool i2s_init_custom(void) {
    bool res = false;
    log_level_get_set(I2S, LOG_LEVEL_INFO);
    return res;
}
