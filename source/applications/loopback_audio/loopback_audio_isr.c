#include "loopback_audio_isr.h"

#include "wav_player_mcal.h"
#include "i2s_full_duplex.h"
#include "loopback_audio_mcal.h"
#include "dma_channel_const.h"
#include "sound_recorder_mcal.h"

bool I2xTxHalfCallbackCustom(I2sHandle_t* const I2s) {
    bool res = false;
    if (WAV_PLAYER_STATUS_PART2_LOADED != WavPlayerInstance[0].status) {
        WavPlayerInstance[0].slow_read_error++;
    }
    WavPlayerInstance[0].state = WAV_PLAYER_STATE_PLAY_PART2;
    WavPlayerInstance[0].action = WAV_PLAYER_ACTION_LOAD_PART1;

    LoopbackAudioHandle_t *Node = LoopbackAudioGetNode(1);
    if (Node) {
        if (false == Node->tx_rx_180) {
            if (Node->rec_need) {
                res = i2s_rx_dma_restart(DMA_CHANNEL_NUM_I2S2_RX, I2s->num, (uint32_t) Node->RxSampleArray,
                        Node->sample_array_size);
                if (res) {
                    res = sound_recorder_start_indication(Node->rec_num);
                }
            }
            Node->tx_rx_180 = true;

        }
    }

    return res;
}

bool I2xTxDoneCallbackCustom(I2sHandle_t* const I2s) {

    if (WAV_PLAYER_STATUS_PART1_LOADED != WavPlayerInstance[0].status) {
        WavPlayerInstance[0].slow_read_error++;
    }

    WavPlayerInstance[0].state = WAV_PLAYER_STATE_PLAY_PART1;
    WavPlayerInstance[0].action = WAV_PLAYER_ACTION_LOAD_PART2;
    return true;
}

