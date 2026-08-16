#include "wav_player_mcal.h"

#include "audio.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "fat_fs.h"
#include "ff.h" /* Declarations of FatFs API */
#include "i2s_mcal.h"
#include "led_mono_drv.h"
#include "log.h"
#include "wav.h"
#include "wm8731_drv.h"

COMPONENT_IS_VALID(WavPlayer, wav_player)
COMPONENT_GET_NODE(WavPlayer, wav_player)
COMPONENT_GET_CONFIG(WavPlayer, wav_player)

bool wav_player_stop_ll(WavPlayerHandle_t* Node) {
    bool res = false;
    res = i2s_dma_stop(Node->i2s_num);
    log_debug_res(WAV_PLAYER, res, "I2s");

    FRESULT ret = f_close(&Node->FileToPlay);
    res = FatFsRetToRes(ret, "CloseFile");
    if(res) {
        LOG_INFO(WAV_PLAYER, "CloseFile:[%s]Ok", Node->file_name);
    } else {
        LOG_ERROR(WAV_PLAYER, "CloseFile:[%s]Err", Node->file_name);
    }
    Node->state = WAV_PLAYER_STATE_IDLE;
    Node->action = WAV_PLAYER_ACTION_NONE;
    Node->play = false;
    led_mono_sw_pwm_duty(Node->led_num, 50);
    WavPlayerPrintReport(Node);
    i2s_init_one(Node->i2s_num);

    return res;
}

/*ISO-26262 require verify configuration*/
bool WavPlayerIsValidConfig(const WavPlayerConfig_t* const Config) {
    bool res = false;
    if(Config) {
        bool l_res = true;
        res = true;

        l_res = i2s_is_valid_num(Config->i2s_num);
        ifn(l_res) {
            LOG_ERROR(WAV_PLAYER, "WAV_PLAYER_%u,I3sNum,Err", Config->num);
            res = false;
        }

        ifn(16 < Config->sample_array_size) {
            LOG_ERROR(WAV_PLAYER, "WAV_PLAYER_%u,sampleArraySize,Err", Config->num);
            res = false;
        }

        ifn(Config->SampleArray) {
            LOG_ERROR(WAV_PLAYER, "WAV_PLAYER_%u,SampleArray,Err", Config->num);
            res = false;
        }

        ifn(Config->name) {
            LOG_ERROR(WAV_PLAYER, "WAV_PLAYER_%u,Name,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool wav_player_init_custom(void) {
    bool res = false;
    LOG_INFO(WAV_PLAYER, "Version:%u", WAV_PLAYER_VERSION);
    return res;
}

static inline bool wav_player_load_to_part_offset(WavPlayerHandle_t* Node, uint32_t offset, uint32_t sample_cnt,
                                                  WavPlayerStatus_t status) {
    bool res = false;
    Node->status = WAV_PLAYER_STATUS_IDLE;
    if(Node->cur_read_size < Node->file_size) {
        UINT need_size = sample_cnt * sizeof(SampleType_t);
        UINT real_read = 0;
        FRESULT ret = f_read(&Node->FileToPlay, &Node->SampleArray[offset], need_size, &real_read);
        if(FR_OK == ret) {
            if(need_size == real_read) {
                Node->cur_read_size += real_read;
                Node->status = status;
                res = true;
            } else if(0 == real_read) {
                res = wav_player_stop_ll(Node);
            } else {
                Node->read_len_error_cnt++;
                LOG_ERROR(WAV_PLAYER, "ReadUndefSize:%u Byte, Need:%u Byte", real_read,need_size);
            }
            Node->action = WAV_PLAYER_ACTION_NONE;
        } else {
            Node->read_error_cnt++;
        }
    } else {
        res = wav_player_stop_ll(Node);
    }
    return res;
}

static inline bool wav_player_load_to_part1(WavPlayerHandle_t* Node) {
    bool res = false;
    res = wav_player_load_to_part_offset(Node, 0, Node->sample_array_size / 2, WAV_PLAYER_STATUS_PART1_LOADED);
    return res;
}

static inline bool wav_player_load_to_part2(WavPlayerHandle_t* Node) {
    bool res = false;
    res = wav_player_load_to_part_offset(Node, Node->sample_array_size / 2, Node->sample_array_size / 2,
                                         WAV_PLAYER_STATUS_PART2_LOADED);
    return res;
}

bool wav_player_load_to_part(WavPlayerHandle_t* Node) {
    bool res = false;
    res = wav_player_load_to_part_offset(Node, 0, Node->sample_array_size, WAV_PLAYER_STATUS_PART_LOADED);
    return res;
}

#if 0
static bool wav_player_proc_play1(WavPlayerHandle_t* Node) {
    bool res = false;
    if(Node->I2s) {
        if(Node->I2s->tx_half) {
            Node->I2s->tx_half = false;
            Node->state = WAV_PLAYER_STATE_PLAY_PART2;
            res = wav_player_load_to_part1(Node);
        }

        if(Node->I2s->tx_done) {
            Node->I2s->tx_done = false;
            Node->state = WAV_PLAYER_STATE_PLAY_PART1;
            res = wav_player_load_to_part2(Node);
            Node->error_cnt++;
        }
    }

    if(Node->file_size <= Node->cur_read_size) {
        res = wav_player_stop_ll(Node);
        if(res) {
            Node->state = WAV_PLAYER_STATE_IDLE;
        }
    }

    return res;
}
#endif

#if 0


static bool wav_player_proc_play2(WavPlayerHandle_t* Node) {
    bool res = false;
    if(Node->I2s) {
        if(Node->I2s->tx_half) {
            Node->I2s->tx_half = false;
            Node->state = WAV_PLAYER_STATE_PLAY_PART2;
            res = wav_player_load_to_part1(Node);
            Node->error_cnt++;
        }

        if(Node->I2s->tx_done) {
            Node->I2s->tx_done = false;
            Node->state = WAV_PLAYER_STATE_PLAY_PART1;
            res = wav_player_load_to_part2(Node);
        }
    }

    if(Node->file_size <= Node->cur_read_size) {
        res = wav_player_stop_ll(Node);
        if(res) {
            Node->state = WAV_PLAYER_STATE_IDLE;
        }
    }

    return res;
}

bool wav_player_proc_idle(WavPlayerHandle_t* Node) {
    bool res = false;
    return res;
}
#endif

bool wav_player_init_common(const WavPlayerConfig_t* const Config, WavPlayerHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->wm8731_num = Config->wm8731_num;
            Node->led_num = Config->led_num;
            Node->i2s_num = Config->i2s_num;
            Node->SampleArray = Config->SampleArray;
            Node->fat_fs_num = Config->fat_fs_num;
            Node->audio_codec_num = Config->audio_codec_num;
            Node->sample_array_size = Config->sample_array_size;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool wav_player_set_temp_mem(const uint8_t num, const SampleType_t* const SampleArray,
                             uint32_t const sample_array_size) {
    bool res = false;
    WavPlayerHandle_t* Node = WavPlayerGetNode(num);
    if(Node) {
        Node->SampleArray = SampleArray;
        Node->sample_array_size = sample_array_size;
        res = true;
    }
    return res;
}

bool wav_player_init_node(WavPlayerHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->state = WAV_PLAYER_STATE_IDLE;
        Node->action = WAV_PLAYER_ACTION_NONE;
        Node->spin = 0;
        Node->valid = true;
        Node->I2s = I2sGetNode(Node->i2s_num);
        if(Node->I2s) {
            res = true;
        }
    }
    return res;
}

bool wav_player_stop(const uint8_t num) {
    bool res = false;
    WavPlayerHandle_t* Node = WavPlayerGetNode(num);
    if(Node) {
        res = wav_player_stop_ll(Node);
    }
    return res;
}

bool wav_player_is_idle(const uint8_t num){
    bool res = false;
    WavPlayerHandle_t* Node = WavPlayerGetNode(num);
    if(Node) {
        res = WAV_PLAYER_STATE_IDLE==Node->state;
    }
    return res;
}

bool wav_player_sample_freq_set(const uint8_t num, const AudioFreq_t audio_freq_hz) {
    bool res = false;
    WavPlayerHandle_t* Node = WavPlayerGetNode(num);
    if(Node) {
        LOG_INFO(WAV_PLAYER, "%u,SetAudioFreq:%u Hz", num, audio_freq_hz);
        res = i2s_audio_frequency_set(Node->i2s_num, audio_freq_hz);
        if(res){
            res = wm8731_sample_rate(Node->wm8731_num, audio_freq_hz);
        }
    }
    return res;
}

bool wav_player_play_file(const uint8_t num, const char* const file_name) {
    bool res = false;
    WavPlayerHandle_t* Node = WavPlayerGetNode(num);
    if(Node) {
        Node->slow_read_error = 0;
        Node->read_len_error_cnt = 0;
        Node->error_cnt = 0;
        Node->read_error_cnt = 0;
        Node->cur_read_size = 0;
        BYTE mode = FA_READ | FA_OPEN_EXISTING;
        FRESULT ret = f_open((FIL*)&Node->FileToPlay, (const TCHAR*)file_name, mode);
        res = FatFsRetToRes(ret, "Open");
        if(res) {
            strcpy(Node->file_name, file_name);
            res = false;
            Node->file_size = f_size(&Node->FileToPlay);
            UINT realRead = 0; /* [OUT] Number of bytes read */
            ret = f_read(&Node->FileToPlay, Node->WavHeader.buff, (UINT)sizeof(WavHeader_t), &realRead);
            res = FatFsRetToRes(ret, "ReadHeader");
            if(res) {
                Node->cur_read_size += sizeof(WavHeader_t);
                res = false;
                if(sizeof(WavHeader_t) == realRead) {
                    LOG_INFO(WAV_PLAYER, "ReadHeaderOk,%s", WavHeaderToStr(&Node->WavHeader));
                    Node->play_need_duration_ms = WavHeaderToPlayDurationMs(&Node->WavHeader);
                    res = i2s_audio_set_data_dirrection(Node->i2s_num, INTERFACE_OPERATION_SEND);
                    res = wav_player_sample_freq_set(num, (AudioFreq_t)Node->WavHeader.sampleRate);
                    res = i2s_gpio_set_write(Node->i2s_num);
                    if(res) {
                        res = wav_player_load_to_part(Node);
                        res = FatFsRetToRes(ret, "ReadPart");
                        if(res) {
                            res = i2s_mcal_write(Node->i2s_num, (uint16_t*)Node->SampleArray, Node->sample_array_size);
                            if(res) {
                                Node->start_play_ms = time_get_ms32();
                                Node->play = true;
                                Node->state = WAV_PLAYER_STATE_PLAY_PART1;
                                led_mono_sw_pwm_duty(Node->led_num, 90);
                            }
                        }
                    }
                }
            }
        }
        res = true;
    }
    return res;
}

bool wav_player_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(WAV_PLAYER, "WAV_PLAYER_%u,Proc", num);
    WavPlayerHandle_t* Node = WavPlayerGetNode(num);
    if(Node) {
        if(Node->play) {

            switch(Node->action) {
            case WAV_PLAYER_ACTION_NONE: {
                // res = wav_player_proc_idle(Node);
            } break;
            case WAV_PLAYER_ACTION_LOAD_PART1: {
                res = wav_player_load_to_part1(Node);
                Node->action = WAV_PLAYER_ACTION_NONE;
                // res = wav_player_proc_play1(Node);

            } break;

            case WAV_PLAYER_ACTION_LOAD_PART2: {
                res = wav_player_load_to_part2(Node);
                Node->action = WAV_PLAYER_ACTION_NONE;
                // res = wav_player_proc_play2(Node);
            } break;

            case WAV_PLAYER_ACTION_STOP: {
                res = wav_player_stop_ll(Node);
            } break;

            default: {
                res = false;
            } break;
            }

            uint32_t cur_duration_ms = time_get_ms32() - Node->start_play_ms;
            if (Node->play_need_duration_ms < cur_duration_ms) {
                /*player can stop I2S DMA We need extra rec termination rule*/
                res = wav_player_stop_ll(Node);
            }

        }else{
            Node->state = WAV_PLAYER_STATE_IDLE;
        }

#if 0
        switch(Node->state) {
        case WAV_PLAYER_STATE_IDLE: {
            res = wav_player_proc_idle(Node);
        } break;
        case WAV_PLAYER_STATE_PLAY_PART1: {
            res = wav_player_proc_play1(Node);
        } break;
        case WAV_PLAYER_STATE_PLAY_PART2: {
            res = wav_player_proc_play2(Node);
        } break;
        default: {
            res = false;
        } break;
        }
#endif
        Node->spin++;
    }
    return res;
}

#if 0
bool wav_player_is_valid_num(uint8_t num) {
    bool res = false;
    WavPlayerHandle_t* Node = WavPlayerGetNode(num);
    if(Node) {
        res = true;
    }
    return res;
}
#endif

bool wav_player_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(WAV_PLAYER, "WAV_PLAYER_%u", num);
    const WavPlayerConfig_t* Config = WavPlayerGetConfig(num);
    res = WavPlayerIsValidConfig(Config);
    if(res) {
#ifdef HAS_WAV_PLAYER_DIAG
        LOG_WARNING(WAV_PLAYER, "%s", WavPlayerConfigToStr(Config));
#endif
        WavPlayerHandle_t* Node = WavPlayerGetNode(num);
        if(Node) {
            res = wav_player_init_common(Config, Node);
            res = wav_player_init_node(Node);
            Node->init = true;
        } else {
            LOG_ERROR(WAV_PLAYER, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(WAV_PLAYER, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(WAV_PLAYER, WAV_PLAYER, wav_player)
COMPONENT_PROC_PATTERT(WAV_PLAYER, WAV_PLAYER, wav_player)
