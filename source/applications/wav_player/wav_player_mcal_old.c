#include "wav_player_mcal.h"

#include "fat_fs.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "wav_diag.h"
#include "i2s_mcal.h"
#include "log.h"
#include "ff.h"         /* Declarations of FatFs API */

COMPONENT_IS_VALID(WavPlayer, wav_player)
COMPONENT_GET_NODE(WavPlayer, wav_player)
COMPONENT_GET_CONFIG(WavPlayer, wav_player)

bool wav_player_stop_ll(WavPlayerHandle_t* Node) {
    bool res = false;
    res = i2s_dma_stop(Node->i2s_num);
    log_info_res(WAV_PLAYER, res, "I2s");

    FRESULT ret = f_close(&Node->FileToPlay);
    res = FatFsRetToRes(ret, "CloseFile");
    if(res) {
        LOG_INFO(WAV_PLAYER, "CloseFile:[%s]Ok", Node->file_name);
    } else {
        LOG_ERROR(WAV_PLAYER, "CloseFile:[%s]Err", Node->file_name);
    }
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

        ifn(512<Config->sample_array_size) {
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

static bool wav_player_load_to_part_offset(WavPlayerHandle_t* Node, uint32_t offset, uint32_t sample_cnt) {
    bool res = false;
    if(Node->cur_read_size < Node->file_size) {
        UINT need_size = sample_cnt * sizeof(SampleType_t);
        UINT real_read = 0;
        FRESULT ret = f_read(&Node->FileToPlay, &Node->I2s->TxArray[offset], need_size, &real_read);
        if(FR_OK == ret) {
            if(need_size == real_read) {
                Node->cur_read_size += real_read;
                res = true;
            }
        }
    }else {
        res = wav_player_stop_ll(Node);
    }
    return res;
}

static bool wav_player_load_to_part1(WavPlayerHandle_t* Node) {
    bool res = false;
    res = wav_player_load_to_part_offset(Node, 0,I2S_MEM_HALF_SIZE);
    return res;
}

static bool wav_player_load_to_part2( WavPlayerHandle_t* Node){
    bool res = false;
    res = wav_player_load_to_part_offset(Node, I2S_MEM_HALF_SIZE,I2S_MEM_HALF_SIZE);
    return res;
}

bool wav_player_load_to_part(WavPlayerHandle_t* Node) {
    bool res = false;
    res = wav_player_load_to_part_offset(Node, 0, I2S_MEM_SIZE);
    return res;
}

bool wav_player_proc_play(WavPlayerHandle_t* Node) {
    bool res = false;
    if(Node->I2s) {
        if(Node->I2s->tx_half) {
            Node->I2s->tx_half = false;
            res = wav_player_load_to_part1(Node);
        }

        if(Node->I2s->tx_done) {
            Node->I2s->tx_done = false;
            res = wav_player_load_to_part2(Node);
        }
    }

    if(Node->file_size <= Node->cur_read_size ) {
        res = wav_player_stop_ll(Node);
        if(res){
            Node->state = WAV_PLAYER_STATE_IDLE;
        }
    }

    return res;

}

bool wav_player_proc_idle(WavPlayerHandle_t* Node) {
    bool res = false;
    return res;
}

bool wav_player_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(WAV_PLAYER, "WAV_PLAYER_%u,Proc", num);
    WavPlayerHandle_t *Node = WavPlayerGetNode(num);
    if(Node) {
        switch (Node->state) {
            case WAV_PLAYER_STATE_IDLE: {
                res = wav_player_proc_idle(Node);
            } break;
            case WAV_PLAYER_STATE_PLAY: {
                res = wav_player_proc_play(Node);
            } break;
            default: {
                res = false;
            } break;
        }
        Node->spin++;
    }
    return res;
}


bool wav_player_init_common(const WavPlayerConfig_t* const Config, WavPlayerHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->SampleArray = Config->SampleArray;
            Node->fat_fs_num = Config->fat_fs_num;
            Node->audio_codec_num = Config->audio_codec_num;
            Node->i2s_num = Config->i2s_num;
            Node->sample_array_size = Config->sample_array_size;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool wav_player_init_node(WavPlayerHandle_t* const Node) {
    bool res = false;
    if (Node) {
        Node->spin = 0;
        Node->valid = true;
        Node->I2s = I2sGetNode(Node->i2s_num);
        res = true;
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

bool wav_player_play_file(const uint8_t num, const char * const file_name) {
    bool res = false;
    WavPlayerHandle_t* Node = WavPlayerGetNode(num);
    if(Node) {
        BYTE mode = FA_READ | FA_OPEN_EXISTING;
        FRESULT ret = f_open( (FIL*) &Node->FileToPlay, (const TCHAR*) file_name, mode);
        res = FatFsRetToRes(ret, "Open");
        if(res) {
            strcpy(Node->file_name,file_name);
            res = false;
            Node->file_size = f_size(&Node->FileToPlay);
            UINT realRead = 0; /* [OUT] Number of bytes read */
            ret = f_read( &Node->FileToPlay, Node->WavHeader.buff, ( UINT ) sizeof(WavHeader_t) , &realRead      );
            res = FatFsRetToRes(ret, "ReadHeader");
            if(res) {
                Node->cur_read_size +=sizeof(WavHeader_t) ;
                res = false;
                if( sizeof(WavHeader_t)==realRead) {
                    LOG_INFO(WAV, "ReadHeaderOk,%s", WavHeaderToStr(&Node->WavHeader));
                    res = i2s_audio_frequency_set(Node->i2s_num, Node->WavHeader.sampleRate);
                    res = wav_player_load_to_part(Node);
                    res = FatFsRetToRes(ret, "ReadPart");
                    if(res) {
                        res = i2s_mcal_write(Node->i2s_num, Node->SampleArray, Node->sample_array_size);
                        if(res) {
                            Node->state = WAV_PLAYER_STATE_PLAY  ;
                        }
                    }
                }
            }
        }
        res = true;
    }
    return res;
}

bool wav_player_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(WAV_PLAYER, "WAV_PLAYER_%u", num);
    const WavPlayerConfig_t *Config = WavPlayerGetConfig(num);
    res = WavPlayerIsValidConfig(Config);
    if(res) {
#ifdef HAS_WAV_PLAYER_DIAG
        LOG_WARNING(WAV_PLAYER, "%s", WavPlayerConfigToStr(Config));
#endif
        WavPlayerHandle_t *Node = WavPlayerGetNode(num);
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
