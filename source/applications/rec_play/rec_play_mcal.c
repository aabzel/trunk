#include "rec_play_mcal.h"

#include "audio.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"
#include "sound_recorder_mcal.h"
#include "wav_player_mcal.h"

COMPONENT_GET_NODE(RecPlay, rec_play)
COMPONENT_GET_CONFIG(RecPlay, rec_play)

/* ISO-26262 require verify configuration */
bool RecPlayIsValidConfig(const RecPlayConfig_t* const Config) {
    bool res = false;
    if(Config) {
        bool l_res = true;
        res = true;
        ifn(Config->name) {
            LOG_ERROR(REC_PLAY, "REC_PLAY_%u,Name,Err", Config->num);
            res = false;
        }

        l_res = sound_recorder_is_valid_num(Config->rec_num);
        ifn(l_res) {
            LOG_ERROR(REC_PLAY, "REC_PLAY_%u,Name,rec_num", Config->num);
            res = false;
        }

        l_res = wav_player_is_valid_num(Config->play_num);
        ifn(l_res) {
            LOG_ERROR(REC_PLAY, "REC_PLAY_%u,Name,play_num", Config->num);
            res = false;
        }
    }
    return res;
}

static bool rec_play_proc_play(RecPlayHandle_t* Node) {
    bool res = false;
    WavPlayerHandle_t* Player = WavPlayerGetNode(Node->play_num);
    if(Player) {
        switch(Player->state) {
        case WAV_PLAYER_STATE_IDLE: {
            Node->state = REC_PLAY_STATE_IDLE;
        } break;

        case WAV_PLAYER_STATE_PLAY_PART1: {
            res = true;
        } break;

        case WAV_PLAYER_STATE_PLAY_PART2: {
            res = true;
        } break;

        default: {
            res = false;
        } break;
        }
    }
    return res;
}

static bool rec_play_proc_idle(RecPlayHandle_t* Node) {
    bool res = true;
    return res;
}

bool rec_play_proc_rec(RecPlayHandle_t* Node) {
    bool res = false;
    SoundRecorderHandle_t* Rec = SoundRecorderGetNode(Node->rec_num);
    if(Rec) {
        switch(Rec->state) {
        case SOUND_RECORDER_STATE_IDLE: {
            res = wav_player_play_file(Node->play_num, Node->file_name);
            if(res) {
                Node->state = REC_PLAY_STATE_PLAY;
            }
        } break;

        case SOUND_RECORDER_STATE_REC_PART_1: {
            res = true;
        } break;

        case SOUND_RECORDER_STATE_REC_PART_2: {
            res = true;
        } break;

        default: {
            res = false;
        } break;
        }
    }
    return res;
}

bool rec_play_init_custom(void) {
    bool res = false;
    LOG_INFO(REC_PLAY, "Version:%u", REC_PLAY_VERSION);
    return res;
}

bool rec_play_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(REC_PLAY, "Proc %u", num);
    RecPlayHandle_t* Node = RecPlayGetNode(num);
    if(Node) {
        switch(Node->state) {

        case REC_PLAY_STATE_IDLE: {
            res = rec_play_proc_idle(Node);
        } break;

        case REC_PLAY_STATE_REC: {
            res = rec_play_proc_rec(Node);
        } break;

        case REC_PLAY_STATE_PLAY: {
            res = rec_play_proc_play(Node);
        } break;

        default: {
        } break;
        }
        Node->spin++;
    }
    return res;
}

bool rec_play_init_common(const RecPlayConfig_t* const Config, RecPlayHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->rec_num = Config->rec_num;
            Node->play_num = Config->play_num;
            res = true;
        }
    }
    return res;
}

bool rec_play_start(uint8_t num, char* file_name, float duration_s) {
    bool res = false;
    RecPlayHandle_t* Node = RecPlayGetNode(num);
    if(Node) {
        strcpy(Node->file_name, file_name);
        LOG_INFO(REC_PLAY, "REC->PLAY_%u,File:[%s]", num, file_name);
        res = sound_recorder_start(Node->rec_num, file_name, duration_s);
        if(res) {
            Node->state = REC_PLAY_STATE_REC;
        }
    }
    return res;
}

bool rec_play_start_test(uint8_t num, float duration_s) {
    bool res = false;
    char file_name[80] = {0};
    res = wav_file_name_generate(file_name, sizeof(file_name), REC_MEM_SAM_CNT, duration_s);
    res = rec_play_start(num, file_name, duration_s);
    return res;
}

bool rec_play_init_node(RecPlayHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->spin = 0;
        Node->init = false;
        Node->state = REC_PLAY_STATE_IDLE;
        Node->valid = true;
        memset(Node->file_name, 0, sizeof(Node->file_name));
        res = true;
    }
    return res;
}

bool rec_play_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(REC_PLAY, "REC_PLAY_%u", num);
    const RecPlayConfig_t* Config = RecPlayGetConfig(num);
    res = RecPlayIsValidConfig(Config);
    if(res) {
#ifdef HAS_REC_PLAY_DIAG
        LOG_WARNING(REC_PLAY, "%s", RecPlayConfigToStr(Config));
#endif
        RecPlayHandle_t* Node = RecPlayGetNode(num);
        if(Node) {
            res = rec_play_init_common(Config, Node);
            res = rec_play_init_node(Node);
            LOG_INFO(REC_PLAY, "Init,Ok,%u", num);
            Node->valid = true;
            Node->init = true;
        } else {
            LOG_ERROR(REC_PLAY, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(REC_PLAY, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(REC_PLAY, REC_PLAY, rec_play)
COMPONENT_PROC_PATTERT(REC_PLAY, REC_PLAY, rec_play)
