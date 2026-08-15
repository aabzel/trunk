





/*ISO-26262 require verify configuration*/

bool RecPlayIsValidConfig(const RecPlayConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(REC_PLAY, "%u,Name,Err", Config->num);
            res = false;
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
    SoundRecorderHandle_t *Rec = SoundRecorderGetNode(Node->rec_num);
    if(Rec) {
        switch (Rec->state) {
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

static bool rec_play_proc_play(RecPlayHandle_t* Node) {
    bool res = false;
    WavPlayerHandle_t *Player = WavPlayerGetNode(Node->play_num);
    if(Player) {
        switch (Player->state) {
        case WAV_PLAYER_STATE_IDLE: {
            Node->state = REC_PLAY_STATE_IDLE;
        }
            break;

        case WAV_PLAYER_STATE_PLAY_PART1: {
            res = true;
        }
            break;

        case WAV_PLAYER_STATE_PLAY_PART2: {
            res = true;
        }
            break;

        default: {
            res = false;
        }
            break;
        }
    }
    return res;
}

bool rec_play_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(REC_PLAY, "Proc %u", i);
    RecPlayHandle_t *Node = RecPlayGetNode(i);
    if(Node) {
        switch (Node->state) {

        case REC_PLAY_STATE_IDLE: {
            res = rec_play_proc_idle(Node);
        }
            break;

        case REC_PLAY_STATE_REC: {
            res = rec_play_proc_rec(Node);
        }
            break;

        case REC_PLAY_STATE_PLAY: {
            res = rec_play_proc_play(Node);
        }
            break;

        default: {

        }
            break;
        }
        Node->spin++;
    }
    return res;
}

bool rec_play_raw_reg_diag(uint8_t i) {
    bool res = false;
#if 0
    RecPlayInfo_t* Info = RecPlayGetInfo(i);
    if(Info) {
        (void) Info;
    }
#endif
    return res;
}

bool rec_play_init_common(const RecPlayConfig_t* const Config, RecPlayHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->interrupt_on = Config->interrupt_on;
            res = true;
        }
    }
    return res;
}

bool rec_play_init_node(RecPlayHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->spin = 0;
        Node->init = false ;
        Node->state = REC_PLAY_STATE_IDLE;
        Node->valid = true;
        memset(Node->file_name,0,sizeof(Node->file_name));
        res = true;
    }
    return res;
}

bool rec_play_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(REC_PLAY, "REC_PLAY%u", num);
    const RecPlayConfig_t *Config = RecPlayGetConfig(num);
    if(Config) {
        res = RecPlayIsValidConfig(Config);
        if(res) {
#ifdef HAS_REC_PLAY_DIAG
            LOG_WARNING(REC_PLAY, "Config:%s", RecPlayConfigToStr(Config));
#endif
            RecPlayHandle_t *Node = RecPlayGetNode(num);
            if(Node) {
                res = rec_play_init_common(Config, Node);
                res = rec_play_init_node(Node);
                Node->valid = true;
                Node->init = true;
                LOG_INFO(REC_PLAY, "Init,Ok,%u", num);
                res = true;
            } else {
                LOG_ERROR(REC_PLAY, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(REC_PLAY, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(REC_PLAY, "ConfigErr %u", num);
    }
    return res;
}

