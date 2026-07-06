#include "i2s_mcal.h"

#include <string.h>

#include "code_generator.h"
#include "compiler_const.h"
#include "connectivity_const.h"
#include "data_utils.h"
#include "dma_channel_mcal.h"
#include "dsp_types.h"
#include "float_diag.h"
#include "gpio_mcal.h"
#include "i2s_config.h"
#include "audio.h"
#include "i2s_diag.h"
#include "i2s_mcal.h"
#include "led_mono_drv.h"
#include "log.h"
#include "std_includes.h"
#include "time_mcal.h"
#include "word_utils.h"

#ifdef HAS_I2S_VOLUME
#include "i2s_volume.h"
#endif

#ifdef HAS_DDS
#include "dds_drv.h"
#endif

COMPONENT_GET_NODE(I2s, i2s)
COMPONENT_GET_CONFIG(I2s, i2s)


static const I2sBusDirInfo_t I2sBusDirInfo[] = {
    {
        .bus_role = IF_BUS_ROLE_SLAVE,
        .direction = CONNECT_DIR_TRANSMIT,
#if 0
        .i2s_bus_dir = I2S_DIR_BUS_MODE_SLAVE_TX,
#endif
        .num = 1,
        .valid = true,
    },
    {
        .bus_role = IF_BUS_ROLE_SLAVE,
        .direction = CONNECT_DIR_RECEIVER,
#if 0
        .i2s_bus_dir = I2S_DIR_BUS_MODE_SLAVE_RX,
#endif
        .num = 2,
        .valid = true,
    },
    {
        .bus_role = IF_BUS_ROLE_MASTER,
        .direction = CONNECT_DIR_TRANSMIT,
#if 0
        .i2s_bus_dir = I2S_DIR_BUS_MODE_MASTER_TX,
#endif
        .num = 3,
        .valid = true,
    },
    {
        .bus_role = IF_BUS_ROLE_MASTER,
        .direction = CONNECT_DIR_RECEIVER,
#if 0
        .i2s_bus_dir = I2S_DIR_BUS_MODE_MASTER_RX,
#endif
        .num = 4,
        .valid = true,
    },
};

const I2sBusDirInfo_t* I2sRoleAndDirToInfo(const IfBusRole_t bus_role, const ConnectivitDir_t direction) {
    I2sBusDirInfo_t* BusInfo = NULL;
    uint32_t cnt = ARRAY_SIZE(I2sBusDirInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(I2sBusDirInfo[i].valid) {
            if(direction == I2sBusDirInfo[i].direction) {
                if(bus_role == I2sBusDirInfo[i].bus_role) {
                    BusInfo = &I2sBusDirInfo[i];
                }
            }
        }
    }
    return BusInfo;
}

static bool i2s_dma_is_valid_config(const I2sConfig_t* const Config) {
    bool res = false;
    if(Config) {
        bool l_res = true;
        res = true;

        l_res = dma_channel_is_valid_num(Config->dma_channel_tx_num);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,dma_channel_tx_num", Config->num);
        }

        l_res = dma_channel_is_valid_num(Config->dma_channel_rx_num);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,dma_channel_rx_num", Config->num);
        }

        ifn(Config->CallBackTxHalf) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,CallBackTxHalf", Config->num);
        }

        ifn(Config->CallBackTxDone) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,CallBackTxDone", Config->num);
        }

        ifn(Config->CallBackRxHalf) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,CallBackRxHalf", Config->num);
        }

        ifn(Config->CallBackRxDone) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,CallBackRxDone", Config->num);
        }
    }
    return res;
}

static bool i2s_gpio_is_valid_config(const I2sConfig_t* const Config) {
    bool res = false;
    if(Config) {
        bool l_res = true;
        res = true;
#if 0
        l_res = GpioIsValidConfig(&Config->GpioMClk);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,GpioMClk", Config->num);
        }
#endif

#ifdef HAS_I2S_GPIO
        l_res = GpioIsValidConfig(&Config->GpioSdIn);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,GpioSdIn", Config->num);
        }
#endif

#ifdef HAS_I2S_GPIO
        l_res = GpioIsValidConfig(&Config->GpioSdIn);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,GpioSdIn", Config->num);
        }
#endif
        l_res = led_mono_is_valid_num(Config->led_rx_num);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,led_rx_num", Config->num);
        }

        l_res = led_mono_is_valid_num(Config->led_tx_num);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,led_tx_num", Config->num);
        }

#ifdef HAS_I2S_GPIO
        l_res = GpioIsValidConfig(&Config->GpioSdOut);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,GpioSdOut", Config->num);
        }
#endif

#ifdef HAS_I2S_GPIO
        l_res = GpioIsValidConfig(&Config->GpioLrCk);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,GpioLrCk", Config->num);
        }
#endif

#ifdef HAS_I2S_GPIO
        l_res = GpioIsValidConfig(&Config->GpioSck);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,GpioSck", Config->num);
        }
#endif

#if 0
        l_res = gpio_is_valid_pad(Config->PadDebug1);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,PadDebug1", Config->num);
        }

        l_res = gpio_is_valid_pad(Config->PadDebug2);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,PadDebug2", Config->num);
        }
#endif
    }
    return res;
}

bool i2s_is_valid_config(const I2sConfig_t* const Config) {
    bool res = false;
    if(Config) {
        bool l_res = true;
        res = true;

        l_res = audio_is_valid_frequency(Config->audio_frequency_hz);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,audioFrequencyHz", Config->num);
        }

        l_res = i2s_gpio_is_valid_config(Config);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,Gpio", Config->num);
        }

        l_res = i2s_dma_is_valid_config(Config);
        ifn(l_res) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,Dma", Config->num);
        }

        ifn(Config->mclk_out) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,mclk_out", Config->num);
        }

        ifn(Config->standard) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,standard", Config->num);
        }
#if 0
        ifn(Config->dir_role) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,dir_role", Config->num);
        }
#endif

        ifn(Config->clock_source) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,clock_source", Config->num);
        }

        ifn(Config->sample_mode) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,sample_mode", Config->num);
        }

        ifn(Config->full_duplex) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,full_duplex", Config->num);
        }

        ifn(Config->direction) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,direction", Config->num);
        }

        ifn(Config->data_format) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,data_format", Config->num);
        }

        ifn(Config->bus_role) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,bus_role", Config->num);
        }

        ifn(2 < Config->samples_cnt) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,samples_cnt", Config->num);
        }

        ifn(Config->move_mode) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,move_mode", Config->num);
        }

        ifn(Config->TxArray) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,TxArray", Config->num);
        }

        ifn(Config->RxArray) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,RxArray", Config->num);
        }
        ifn(Config->cpol) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,cpol", Config->num);
        }
        ifn(Config->name) {
            res = false;
            LOG_ERROR(I2S, "I2S_%u,Err,name", Config->num);
        }
    }
    return res;
}

#if 0
bool i2s_play_static_tx(uint8_t num, uint8_t dac_num, bool status) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        I2sDirAndBusRole_t bus_role = I2S_DIR_BUS_MODE_UNDEF;
        res = i2s_dir_bus_role_get(num, &bus_role);
        if(I2S_DIR_BUS_MODE_MASTER_TX != bus_role) {
            res = i2s_dir_bus_role_set(num, I2S_DIR_BUS_MODE_MASTER_TX);
        }
#ifdef HAS_DDS
        Node->dac_num = 0;
        DdsHandle_t* DdsNode = DdsGetNode(dac_num);
        if(DdsNode) {
            LOG_DEBUG(I2S, "SpotDac:%u,Play:48 Sam", dac_num);
            Node->dac_num = dac_num;
            Node->loopback = false;
            Node->play = status;
            if(Node->play) {
                res = i2s_mcal_write(num, (SampleType_t*)DdsNode->tx_sample_array, 48 * 2);
                LOG_INFO(I2S, "StartPlay1KHz");
                if(res) {
                    LOG_INFO(I2S, "DmaTxOk,%u Sam", DdsNode->sample_cnt);
                    res = true;
                } else {
                    LOG_ERROR(I2S, "DmaTxErr,%s");
                    Node->error_cnt++;
                }
            } else {
                res = true;
            }
        } else {
            LOG_ERROR(DDS, "HandleErr");
        }
#else
        LOG_ERROR(I2S, "AddDdsComponent");
#endif /*HAS_DDS*/
    } else {
        LOG_ERROR(I2S, "HandleErr");
    }
    return res;
}
#endif

#if 0
const I2sBusDirInfo_t* I2S_DirRoleToInfo(const I2sDirAndBusRole_t i2s_bus_dir) {
    I2sBusDirInfo_t* BusInfo = NULL;
    uint32_t cnt = ARRAY_SIZE(I2sBusDirInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(I2sBusDirInfo[i].valid) {
            if(i2s_bus_dir == I2sBusDirInfo[i].i2s_bus_dir) {
                BusInfo = &I2sBusDirInfo[i];
            }
        }
    }
    return BusInfo;
}
#endif

#if 0
I2sDirAndBusRole_t i2s_role_and_dir_to_dir_bus(const IfBusRole_t bus_role, const ConnectivitDir_t direction) {
    I2sDirAndBusRole_t bus_dir_role = I2S_DIR_BUS_MODE_UNDEF;
    const I2sBusDirInfo_t* BusInfo = I2sRoleAndDirToInfo(bus_role, direction);
    if(BusInfo) {
        bus_dir_role = BusInfo->i2s_bus_dir;
    }

    return bus_dir_role;
}
#endif

#ifdef HAS_I2S
bool i2s_common_init(uint8_t num) {
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        memset(Node, 0x00, sizeof(I2sHandle_t));
        Node->rx_rate.min = 0xFFFFFFFF;
    }
    return true;
}
#endif /*HAS_I2S*/

#ifdef HAS_MICROCONTROLLER
bool i2s_calc_byte_rate(void) {
    bool res = false;
    uint8_t num = 0;
    for(num = 0; num < i2s_get_cnt(); num++) {
        I2sHandle_t* Node = I2sGetNode(num);
        if(Node) {
            Node->rx_rate.cur = Node->cnt.byte_rx - Node->cnt_prev.byte_rx;
            Node->rx_rate.min = min32u(Node->rx_rate.min, Node->rx_rate.cur);
            Node->rx_rate.max = max32u(Node->rx_rate.max, Node->rx_rate.cur);
            Node->cnt_prev.byte_rx = Node->cnt.byte_rx;

            Node->tx_rate.cur = Node->cnt.byte_tx - Node->cnt_prev.byte_tx;
            Node->tx_rate.min = min32u(Node->tx_rate.min, Node->tx_rate.cur);
            Node->tx_rate.max = max32u(Node->tx_rate.max, Node->tx_rate.cur);
            Node->cnt_prev.byte_tx = Node->cnt.byte_tx;
        }
        res = true;
    }
    return res;
}
#endif

_WEAK_FUN_
uint8_t i2s_sample_size_get(uint8_t num) { return 0; }

_WEAK_FUN_
bool i2s_dir_bus_role_set(uint8_t num, IfBusRole_t bus_role) { return false; }

_WEAK_FUN_
bool i2s_init_custom(void) { return false; }

_WEAK_FUN_
bool i2s_dir_bus_role_get(uint8_t num, IfBusRole_t* bus_role) { return false; }

_WEAK_FUN_
bool i2s_sample_freq_get(uint8_t num, uint32_t* const audio_frequency_hz) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        *audio_frequency_hz = Node->audio_frequency_hz;
        res = true;
    }
    return res;
}

_WEAK_FUN_
bool i2s_data_format_get(uint8_t num, I2sDataFormat_t* data_format) { return false; }

_WEAK_FUN_
bool i2s_stop(uint8_t num) { return false; }

_WEAK_FUN_
bool i2s_is_init(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        res = Node->init_done;
    }
    return res;
}

bool i2s_init_common(const I2sConfig_t* const Config, I2sHandle_t* const Node) {
    bool res = false;
    if(Node) {
        if(Config) {

#ifdef HAS_I2S_DMA
            Node->dma_channel_tx_num = Config->dma_channel_tx_num;
            Node->dma_channel_rx_num = Config->dma_channel_rx_num;
            Node->CallBackTxHalf = Config->CallBackTxHalf;
            Node->CallBackTxDone = Config->CallBackTxDone;
            Node->CallBackRxHalf = Config->CallBackRxHalf;
            Node->CallBackRxDone = Config->CallBackRxDone;
#endif

#ifdef HAS_I2S_GPIO
            Node->GpioSck = Config->GpioSck;
            Node->GpioLrCk = Config->GpioLrCk;
            Node->GpioSdOut = Config->GpioSdOut;
            Node->GpioSdIn = Config->GpioSdIn;
            Node->GpioMClk = Config->GpioMClk;
#endif

            Node->bus_role = Config->bus_role;
            Node->direction = Config->direction;
            Node->led_rx_num = Config->led_rx_num;
            Node->led_tx_num = Config->led_tx_num;
            Node->PadDmaRx = Config->PadDmaRx;
            Node->PadDmaTx = Config->PadDmaTx;
#if 0
            Node->dir_role = Config->dir_role;
#endif
            Node->mclk_out = Config->mclk_out;
            Node->standard = Config->standard;
            Node->clock_source = Config->clock_source;
            Node->sample_mode = Config->sample_mode;
            Node->full_duplex = Config->full_duplex;
            Node->data_format = Config->data_format;
            Node->audio_frequency_hz = Config->audio_frequency_hz;
            Node->irq_priority = Config->irq_priority;
            Node->move_mode = Config->move_mode;
            Node->num = Config->num;
            Node->name = Config->name;
            Node->cpol = Config->cpol;
            Node->TxArray = Config->TxArray;
            Node->RxArray = Config->RxArray;
            Node->samples_cnt = Config->samples_cnt;
            res = true;
        }
    }
    return res;
}

_WEAK_FUN_
bool i2s_is_valid_num(uint8_t num) {
    bool res = false;
    const I2sConfig_t* Config = I2sGetConfig(num);
    if(Config) {
        I2sHandle_t* Node = I2sGetNode(num);
        if(Node) {
            res = true;
        }
    }

    return res;
}

uint32_t I2sByteToSample(uint32_t byte) {
    uint32_t sample = 0;
    sample = byte / sizeof(SampleType_t);
    return sample;
}

_WEAK_FUN_
uint32_t i2s_err_total(I2sErr_t* Err) {
    uint32_t cnt = 0;
    if(Err) {
        cnt = Err->next + Err->read + Err->start + Err->write;
    }
    return cnt;
}

#if 0
uint32_t I2sAudioFreq2Hz(AudioFreq_t audio_freq){
    uint32_t des_lr_freq_hz=0;
    switch((uint32_t)audio_freq){
    case I2S_AUDIO_FREQ_192K   :des_lr_freq_hz=192000; break;
    case I2S_AUDIO_FREQ_96K    :des_lr_freq_hz=96000; break;
    case I2S_AUDIO_FREQ_48K    :des_lr_freq_hz=48000; break;
    case I2S_AUDIO_FREQ_44K    :des_lr_freq_hz=44100; break;
    case I2S_AUDIO_FREQ_41K    :des_lr_freq_hz=41000; break;
    case I2S_AUDIO_FREQ_32K    :des_lr_freq_hz=32000; break;
    case I2S_AUDIO_FREQ_22K    :des_lr_freq_hz=22000; break;
    case I2S_AUDIO_FREQ_16K    :des_lr_freq_hz=16000; break;
    case I2S_AUDIO_FREQ_11K    :des_lr_freq_hz=11000; break;
    case I2S_AUDIO_FREQ_8K     :des_lr_freq_hz=8000 ; break;
    }
    return des_lr_freq_hz;
}
#endif

#ifdef HAS_DFT
bool i2s_calc_dft(uint8_t num) {
    bool res = false;
    LOG_INFO(I2S, "I2S%u CalcDft", num);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        float sample_period_s = 1.0 / ((float)Node->audio_freq);
        LOG_INFO(I2S, "SampleFreq %u Hz, SamplePeriod %u us", Node->audio_freq, SEC_2_USEC(sample_period_s));
        res = dft_calc((SampleType_t*)&Node->RxArray[0], Node->samples_cnt, Node->dft_mem, Node->samples_cnt,
                       sample_period_s);
#ifdef HAS_COMPLEX_DIAG
        complex_array_print(Node->dft_mem, Node->samples_cnt, sample_period_s, Node->samples_cnt);
#endif /*HAS_COMPLEX_DIAG*/
        // complex_array_print_csv(Node->dft_mem, Node->samples_cnt, sample_period_s, Node->samples_cnt);
        float max_freq = 0.0;
        ft_find_freq(Node->dft_mem, Node->samples_cnt, sample_period_s, &max_freq);
        LOG_INFO(I2S, "Max Freq %f Hz", max_freq);
    }
    return res;
}
#endif /*HAS_DFT*/

bool i2s_wait_idle(uint8_t num) {
    bool res = true;
    uint32_t up_time_ms = 0;
    uint32_t diff_ms = 0;
    uint32_t start_uptime_ms = time_get_ms32();
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        bool loop = true;
        while(loop) {
            res = wait_in_loop_ms(100);
            if(I2S_STATE_IDLE == Node->state) {
                loop = false;
                res = true;
            }

            up_time_ms = time_get_ms32();
            diff_ms = up_time_ms - start_uptime_ms;
            if(20000 < diff_ms) {
                loop = false;
                res = false;
            }
        }
    }
    return res;
}

bool i2s_wait_tx_done_ll(I2sHandle_t* Node, uint32_t timeout_ms) {
    bool res = false;
    LOG_DEBUG(I2S, "WaitTxDone i2s:%u Words:%u ms", Node->num, timeout_ms);
    if(Node) {
        res = true;
        uint32_t start_ms = time_get_ms32();
        while(false == Node->tx_done) {
            res = time_wait_timeout(start_ms, timeout_ms);
            if(!res) {
                LOG_ERROR(I2S, "I2S_%u,Tx,TimeOut", Node->num);
                res = false;
                break;
            }
        }
    } else {
        LOG_ERROR(I2S, "%u NodeErr", Node->num);
    }
    return res;
}

_WEAK_FUN_
bool i2s_play_1khz(uint8_t i2s_num, uint8_t dac_num, SampleType_t amplitude, uint32_t phase_ms) {
    bool res = false;
    LOG_INFO(I2S, "I2S%u, DAC%u, Amp:%d, Phase:%u", i2s_num, dac_num, amplitude, phase_ms);
#ifdef HAS_DDS
    res = dds_set_sin(dac_num, 1000.0, amplitude, (float)phase_ms, 0);
    if(res) {
        res = dds_set_array(  dac_num, 1, 0);
        DdsHandle_t* Dds = DdsGetNode(dac_num);
        if(Dds) {
            res = i2s_mcal_write(i2s_num, (uint16_t*) Dds->sample_array, Dds->sample_cnt);
        } else {
            LOG_ERROR(I2S, "DAC%u Err", dac_num);
        }
    } else {
        LOG_ERROR(I2S, "SetSin DAC%u, Amp:%d, Phase:%u Err", dac_num, amplitude, phase_ms);
    }
#endif /*HAS_DDS*/
    return res;
}

bool i2s_proc_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->proc_on = on_off;
        res = true;
    }
    return res;
}

bool i2s_rec_reverse_byte_order(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        LOG_INFO(I2S, "SampleSize:%u byte", sizeof(SampleType_t));
        uint32_t w = 0;
        for(w = 0; w < Node->samples_cnt; w++) {
            if(2 == sizeof(SampleType_t)) {
                Node->RxArray[w] = reverse_byte_order_uint16(Node->RxArray[w]);
            }
            res = true;
        }
    }
    return res;
}

// TODO replace i2s_listen -> i2s_rec
_WEAK_FUN_
bool i2s_listen(uint8_t num, uint32_t des_duration_ms) {
    bool res = false;
    LOG_WARNING(I2S, "Listen:%u,Dur:%u ms", num, des_duration_ms);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        res = i2s_sample_freq_get(num, &Node->audio_frequency_hz);
        if(res) {
            float sample_time_s = 1.0 / ((float)Node->audio_frequency_hz);
            Node->max_diration_s = (sample_time_s * ((float)Node->samples_cnt)) / 2.0;
            LOG_INFO(I2S, "SampleTime:%s", FloatToStr(sample_time_s, 2));
            LOG_INFO(I2S, "RecDuration:%s", FloatToStr(Node->max_diration_s, 2));
            float parts_d = MSEC_2_SEC(des_duration_ms) / Node->max_diration_s;
            uint32_t parts_i = (uint32_t)parts_d;
            LOG_INFO(I2S, "Parts:%f=%u", parts_d, parts_i);
            uint32_t duration_ms = parts_i * SEC_2_MSEC(Node->max_diration_s);
            LOG_WARNING(I2S, "SamSize:%u byte,Listen %u ms,%u Samples", sizeof(SampleType_t), duration_ms,
                        Node->samples_cnt);

            res = i2s_mcal_read(num, (uint16_t*)Node->RxArray, Node->samples_cnt);
            if(res) {
                Node->state = I2S_STATE_REC;
                uint32_t up_time = time_get_ms32();
                Node->rec_off_time_stamp_ms = up_time + duration_ms;
            } else {
                LOG_ERROR(I2S, "I2S%u,ReadErr", num);
            }
        }
    } else {
        LOG_ERROR(I2S, "I2S%u NodeErr", num);
    }

    return res;
}

_WEAK_FUN_
bool i2s_proc_one(uint8_t num) {
    bool res = true;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
#ifdef HAS_I2S_VOLUME
        res = i2s_volume_proc_ll(Node);
#endif
    }

#if 0
        if(Node->tx_int) {
            uint32_t i = 0;
            Node->tx_int = false;
            if(Node->switch_needed) {
                switch(Node->cur_tx_track) {
                case 0:{
                    for(i=0; i<Node->frames; i++){
                        Node->TxBuffer[1][i] = Node->RxArray[1][i];
                    }
                    //memcpy(&(Node->TxBuffer[0][0]),&(Node->RxArray[0][0]),Node->frames*4);
                    res = true;
                } break;
                case 1:{
                    for(i=0; i<Node->frames; i++){
                        Node->TxBuffer[0][i] = Node->RxArray[0][i];
                    }
                    //memcpy(&(Node->TxBuffer[1][0]),&(Node->RxArray[1][0]),Node->frames*4);
                    res = true;
                } break;
                }
            }
        }
#endif

    return res;
}

#if 0
bool i2s_play_tone(uint8_t num, uint8_t dac_num, float freq, SampleType_t amplitude, uint32_t duration_ms) {
    bool res = false;
    if(0.0 < freq) {
        if(0 < amplitude) {
            if(duration_ms) {
                LOG_INFO(I2S, "Play,Amplitude:%d,Freq:%f Hz,Durat:%ums", amplitude, freq, duration_ms);
                I2sHandle_t* Node = I2sGetNode(num);
                if(Node) {
                    uint32_t fps = 0;
                    fps = i2s_get_sample_rate(num);
                    LOG_INFO(I2S, "SampleRate: %u Hz", fps);
                    res = dds_set_sin(dac_num, freq, amplitude, 0, (SampleType_t)0);
                    if(res) {
                        LOG_INFO(I2S, "CfgDacOk");
                    } else {
                        LOG_ERROR(I2S, "CfgDacErr");
                    }

                    res = dds_set_array(dac_num, 2, 0);
                    if(res) {
                        LOG_INFO(I2S, "CalcDataOk");
                    } else {
                        LOG_ERROR(I2S, "CalcDataErr");
                    }

#ifdef HAS_DDS_DIAG
                    log_level_t ll = log_level_get(DDS);
                    if(LOG_LEVEL_DEBUG == ll) {
                        dds_diag();
                        dds_print_track(dac_num);
                    }
#endif

                    res = i2s_play_tx(num, dac_num, true);
                    if(res) {
                        LOG_INFO(I2S, "PlayOk");
                    } else {
                        LOG_ERROR(I2S, "PlayErr");
                    }

                    uint32_t up_time = time_get_ms32();
                    Node->play_off_time_stamp_ms = up_time + duration_ms;
                    res = true;
                } else {
                    LOG_ERROR(I2S, "NodeErr");
                }
            } else {
                LOG_ERROR(I2S, "DurationErr");
            }
        } else {
            LOG_ERROR(I2S, "AmpErr");
        }
    } else {
        LOG_ERROR(I2S, "FreqErr");
    }
    return res;
}
#endif

COMPONENT_INIT_ANY_PATTERT_CNT(I2S, I2S, i2s, I2S_COUNT)
COMPONENT_PROC_PATTERT(I2S, I2S, i2s)
