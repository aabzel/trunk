#include "loopback_audio_mcal.h"

#include "audio.h"
#include "led_mono_drv.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"
#include "wav_player_mcal.h"
#include "sound_recorder_mcal.h"
#include "wav.h"
#include "i2s_mcal.h"

COMPONENT_IS_VALID(LoopbackAudio, loopback_audio)
COMPONENT_GET_NODE(LoopbackAudio, loopback_audio)
COMPONENT_GET_CONFIG(LoopbackAudio, loopback_audio)

/*ISO-26262 require verify configuration*/
bool LoopbackAudioIsValidConfig(const LoopbackAudioConfig_t* const Config) {
    bool res = false;
    if(Config) {
        bool lres = true;
        res = true;
        ifn(Config->name) {
            LOG_ERROR(LOOPBACK_AUDIO, "LOOPBACK_AUDIO_%u,Name,Err", Config->num);
            res = false;
        }

        ifn(1024<=Config->sample_array_size) {
            LOG_ERROR(LOOPBACK_AUDIO, "LOOPBACK_AUDIO_%u,sample_array_size,Err", Config->num);
            res = false;
        }

        ifn(Config->RxSampleArray) {
            LOG_ERROR(LOOPBACK_AUDIO, "LOOPBACK_AUDIO_%u,RxSampleArray,Err", Config->num);
            res = false;
        }

        ifn(Config->TxSampleArray) {
            LOG_ERROR(LOOPBACK_AUDIO, "LOOPBACK_AUDIO_%u,TxSampleArray,Err", Config->num);
            res = false;
        }

        lres= wav_player_is_valid_num(Config->player_num);
        ifn(lres) {
            LOG_ERROR(LOOPBACK_AUDIO, "LOOPBACK_AUDIO_%u,player_num,Err", Config->num);
            res = false;
        }

        lres = sound_recorder_is_valid_num(Config->rec_num);
        ifn(lres) {
            LOG_ERROR(LOOPBACK_AUDIO, "LOOPBACK_AUDIO_%u,rec_num,Err", Config->num);
            res = false;
        }

        lres = led_mono_is_valid_num(Config->led_num);
        ifn(lres) {
            LOG_ERROR(LOOPBACK_AUDIO, "LOOPBACK_AUDIO_%u,led_num,Err", Config->num);
            res = false;
        }

    }
    return res;
}


bool loopback_audio_init_custom(void) {
    bool res = false;
    LOG_INFO(LOOPBACK_AUDIO, "Version:%u", LOOPBACK_AUDIO_VERSION);
    return res;
}


bool loopback_audio_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(LOOPBACK_AUDIO, "LOOPBACK_AUDIO_%u,Proc", num);
    LoopbackAudioHandle_t* Node = LoopbackAudioGetNode(num);
    if(Node) {
        Node->spin++;
    }
    return res;
}

bool loopback_audio_init_common(const LoopbackAudioConfig_t* const Config, LoopbackAudioHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->player_num = Config->player_num;
            Node->rec_num = Config->rec_num;
            Node->led_num = Config->led_num;
            Node->RxSampleArray = Config->RxSampleArray;
            Node->TxSampleArray = Config->TxSampleArray;
            Node->sample_array_size = Config->sample_array_size;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool loopback_audio_init_node(LoopbackAudioHandle_t* const Node) {
    bool res = false;
    if (Node) {
        Node->error_cnt = 0;
        Node->action = LOOPBACK_ACTION_UNDEF;
        Node->state = LOOPBACK_AUDIO_STATE_UNDEF;
        Node->spin = 0;
        Node->init = false;
        Node->tx_rx_180 = false;
        Node->valid = true;
        strcpy(Node->rec_file_name,"");
        strcpy(Node->play_file_name,"");
        res = true;
    }
    return res;
}

bool loopback_audio_play_rec_file(uint8_t num, char* PlayFileName, char* RecFileName) {
    bool res = false;
    LoopbackAudioHandle_t* Node=LoopbackAudioGetNode(  num);
    if(Node) {
        Node->tx_rx_180 = false ;
        Node->rec_need = true;

        strcpy(Node->play_file_name,PlayFileName);
        strcpy(Node->rec_file_name,RecFileName);
        memset(Node->TxSampleArray, 0, sizeof(SampleType_t)*Node->sample_array_size);
        memset(Node->RxSampleArray, 0, sizeof(SampleType_t)*Node->sample_array_size);

        res = wav_player_set_temp_mem(Node->player_num, Node->TxSampleArray, Node->sample_array_size);
        res = sound_recorder_set_temp_mem(Node->rec_num, Node->RxSampleArray, Node->sample_array_size);
        res = sound_recorder_post_pone_rec(Node->rec_num, true);
        float rec_duration_s = wav_read_file_duration(PlayFileName);

        res = sound_recorder_start(Node->rec_num, RecFileName,  rec_duration_s) ;
        res = wav_player_play_file(Node->player_num, PlayFileName);
    }
    return res;
}

bool loopback_audio_start_dummy_read(const uint8_t num) {
    bool res = false;
    LoopbackAudioHandle_t* Node = LoopbackAudioGetNode(  num);
    if(Node) {
        uint8_t i2s_num = loopback_audio_i2s_num_get(num);
        memset(Node->TxSampleArray, 0, sizeof( Node->sample_array_size)*sizeof(SampleType_t));
        res = i2s_mcal_write( i2s_num, (uint16_t*)Node->TxSampleArray, Node->sample_array_size);
    }
    return res;
}

bool loopback_audio_rec_file(const uint8_t num,
                             const char* const RecFileName,
                             const float rec_duration_s) {
    bool res = false;
    LoopbackAudioHandle_t* Node = LoopbackAudioGetNode(num);
    if(Node) {
        Node->tx_rx_180 = false;
        Node->rec_need = true;
        memset(Node->RxSampleArray, 0, sizeof( Node->sample_array_size)*sizeof(SampleType_t));
        res = sound_recorder_set_temp_mem(Node->player_num,
                                          Node->RxSampleArray,
                                          Node->sample_array_size);
        res = sound_recorder_start(Node->rec_num, RecFileName, rec_duration_s) ;
        uint8_t i2s_num = loopback_audio_i2s_num_get(num);
        memset(Node->TxSampleArray, 0, sizeof( Node->sample_array_size)*sizeof(SampleType_t));
        res = i2s_mcal_write(i2s_num, (uint16_t*)Node->TxSampleArray, Node->sample_array_size);
        if(!res) {
            LOG_ERROR(LOOPBACK_AUDIO,"i2sMcalWrite,Err");
        }
    }
    return res;
}

bool loopback_audio_rec_test(const uint8_t num,
                             const float rec_duration_s) {
    bool res;
    char PlayFileName[80] = {0};
    res = wav_file_name_generate(PlayFileName,
                                 sizeof(PlayFileName),
                                 LOOPBACK_MEM_SAM_CNT,
                                 rec_duration_s);
    res = loopback_audio_rec_file(num, PlayFileName,rec_duration_s);
    return res;
}

bool loopback_audio_play_file(const uint8_t num, const char* const PlayFileName) {
    bool res = false;
    LoopbackAudioHandle_t* Node = LoopbackAudioGetNode(num);
    if(Node) {
        Node->rec_need = false;
        Node->tx_rx_180 = true;
        strcpy(Node->play_file_name, PlayFileName);
        memset(Node->TxSampleArray, 0, sizeof(SampleType_t)*Node->sample_array_size);

        strcpy(Node->play_file_name, PlayFileName);
        res = wav_player_set_temp_mem(Node->player_num, Node->TxSampleArray, Node->sample_array_size);
        res = wav_player_play_file(Node->player_num, PlayFileName);
    }
    return res;
}

bool loopback_audio_is_valid_num(uint8_t num) {
    bool res = false;
    LoopbackAudioHandle_t *Node = LoopbackAudioGetNode(num);
    if(Node) {
        res = Node->init;
    }
    return res;
}

bool loopback_audio_i2s_num_set(uint8_t num, uint8_t i2s_num) {
    bool res = false;
    LoopbackAudioHandle_t *Node = LoopbackAudioGetNode(num);
    if(Node) {
        uint32_t cnt = 0 ;
        SoundRecorderHandle_t *Recorder = SoundRecorderGetNode(Node->rec_num);
        if(Recorder) {
            Recorder->i2s_num = i2s_num;
            cnt++;
        }

        WavPlayerHandle_t *Player = WavPlayerGetNode(Node->player_num);
        if(Player) {
            Player->i2s_num = i2s_num;
            cnt++;
        }

        if(2==cnt){
            res = true;
        }
    }
    return res;
}

uint8_t loopback_audio_i2s_num_get(const uint8_t num){
    uint8_t i2s_num = 0xFF;
    LoopbackAudioHandle_t *Node = LoopbackAudioGetNode(num);
    if(Node) {
        WavPlayerHandle_t* Player=WavPlayerGetNode(Node->player_num);
        if(Player){
            SoundRecorderHandle_t* Recorder=SoundRecorderGetNode(Node->rec_num);
            if(Recorder){
                  if(Recorder->i2s_num==Player->i2s_num){
                      i2s_num = Recorder->i2s_num;
                  }
            }
        }
    }
    return i2s_num;
}

bool loopback_audio_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(LOOPBACK_AUDIO, "LOOPBACK_AUDIO_%u", num);
    const LoopbackAudioConfig_t *Config = LoopbackAudioGetConfig(num);
    res = LoopbackAudioIsValidConfig(Config);
    if(res) {
#ifdef HAS_LOOPBACK_AUDIO_DIAG
        LOG_WARNING(LOOPBACK_AUDIO, "%s", LoopbackAudioConfigToStr(Config));
#endif
        LoopbackAudioHandle_t *Node = LoopbackAudioGetNode(num);
        if(Node) {
            res = loopback_audio_init_common(Config, Node);
            res = loopback_audio_init_node(Node);
            Node->init = true;
        } else {
            LOG_ERROR(LOOPBACK_AUDIO, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(LOOPBACK_AUDIO, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(LOOPBACK_AUDIO, LOOPBACK_AUDIO, loopback_audio)
COMPONENT_PROC_PATTERT(LOOPBACK_AUDIO, LOOPBACK_AUDIO, loopback_audio)
