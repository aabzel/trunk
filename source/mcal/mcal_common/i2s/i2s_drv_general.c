#include "i2s_drv.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "data_utils.h"
#include "time_mcal.h"

#ifdef HAS_I2S_VOLUME
#include "i2s_volume.h"
#endif

#ifdef HAS_SW_DAC
#include "sw_dac_drv.h"
#endif

#ifdef HAS_COMPLEX_DIAG
#include "complex_diag.h"
#endif

#include "log.h"
#ifdef HAS_DFT
#include "dft.h"
#endif

#include "i2s_config.h"
#include "i2s_diag.h"
#include "i2s_drv.h"

#ifndef HAS_I2S
#error "+HAS_I2S"
#endif /*HAS_I2S*/

I2sHandle_t* I2sGetNode(uint8_t num) {
    I2sHandle_t* InstNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = i2s_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == I2sInstance[i].num) {
            if(I2sInstance[i].valid) {
                InstNode = &I2sInstance[i];
                break;
            }
        }
    }
    return InstNode;
}

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

bool i2s_is_init(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        res = Node->init_done;
    }
    return res;
}

const I2sConfig_t* I2sGetConfig(uint8_t num) {
    const I2sConfig_t* ConfNode = NULL;
    uint32_t i = 0;
    for(i = 0; i < i2s_get_cnt(); i++) {
        if(num == I2sConfigLuT[i].num) {
            if(I2sConfigLuT[i].valid) {
                ConfNode = &I2sConfigLuT[i];
                break;
            }
        }
    }
    return ConfNode;
}

bool i2s_is_allowed(uint8_t num) {
    bool res = false;
    bool res1 = false;
    bool res2 = false;
    uint32_t i = 0;
    for(i = 0; i < i2s_get_cnt(); i++) {
        if(num == I2sInstance[i].num) {
            res1 = true;
        }
    }
    for(i = 0; i < i2s_get_cnt(); i++) {
        if(num == I2sConfigLuT[i].num) {
            res2 = true;
        }
    }
    if(res1 && res2) {
        res = true;
    }
    return res;
}

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
        double sample_period_s = 1.0 / ((double)Node->audio_freq);
        LOG_INFO(I2S, "SampleFreq %u Hz, SamplePeriod %u us", Node->audio_freq, SEC_2_USEC(sample_period_s));
        res = dft_calc((SampleType_t*)&Node->RxBuffer[0], Node->samples_cnt, Node->dft_mem, Node->samples_cnt,
                       sample_period_s);
#ifdef HAS_COMPLEX_DIAG
        complex_array_print(Node->dft_mem, Node->samples_cnt, sample_period_s, Node->samples_cnt);
#endif /*HAS_COMPLEX_DIAG*/
        // complex_array_print_csv(Node->dft_mem, Node->samples_cnt, sample_period_s, Node->samples_cnt);
        double max_freq = 0.0;
        ft_find_freq(Node->dft_mem, Node->samples_cnt, sample_period_s, &max_freq);
        LOG_INFO(I2S, "Max Freq %f Hz", max_freq);
    }
    return res;
}
#endif /*HAS_DFT*/

bool i2s_play_1khz(uint8_t i2s_num, uint8_t dac_num, SampleType_t amplitude, uint32_t phase_ms) {
    bool res = false;
    LOG_INFO(I2S, "I2S%u, DAC%u, Amp:%d, Phase:%u", i2s_num, dac_num, amplitude, phase_ms);
#ifdef HAS_SW_DAC
    res = sw_dac_set_sin(dac_num, 1000.0, amplitude, (double)phase_ms, 0);
    if(res) {
        res = sw_dac_set_static_period_48k_1000hz_word(dac_num);
        SwDac_t* DacNode = SwDacGetNode(dac_num);
        if(DacNode) {
            res = false;
#ifdef HAS_SW_DAC_STATIC_SAMPLES
            res = i2s_api_write(i2s_num, DacNode->tx_sample_static_array, DacNode->sample_cnt);
#else  /*HAS_SW_DAC_STATIC_SAMPLES*/
            LOG_ERROR(I2S, "DAC%u NoStaticMemory", dac_num);
#endif /*HAS_SW_DAC_STATIC_SAMPLES*/
        } else {
            LOG_ERROR(I2S, "DAC%u Err", dac_num);
        }
    } else {
        LOG_ERROR(I2S, "SetSin DAC%u, Amp:%d, Phase:%u Err", dac_num, amplitude, phase_ms);
    }
#endif /*HAS_SW_DAC*/
    return res;
}

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
                        Node->TxBuffer[1][i] = Node->RxBuffer[1][i];
                    }
                    //memcpy(&(Node->TxBuffer[0][0]),&(Node->RxBuffer[0][0]),Node->frames*4);
                    res = true;
                } break;
                case 1:{
                    for(i=0; i<Node->frames; i++){
                        Node->TxBuffer[0][i] = Node->RxBuffer[0][i];
                    }
                    //memcpy(&(Node->TxBuffer[1][0]),&(Node->RxBuffer[1][0]),Node->frames*4);
                    res = true;
                } break;
                }
            }
        }
#endif

    return res;
}
