#include "sound_recorder_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"
#include "dds_drv.h"
#include "audio.h"
#include "float_diag.h"
#include "i2s_mcal.h"
#include "wav.h"
#include "fat_fs.h"

COMPONENT_IS_VALID(SoundRecorder, sound_recorder)
COMPONENT_GET_NODE(SoundRecorder, sound_recorder)
COMPONENT_GET_CONFIG(SoundRecorder, sound_recorder)


/*ISO-26262 require verify configuration*/
bool SoundRecorderIsValidConfig(const SoundRecorderConfig_t* const Config) {
    bool res = false;
    if(Config) {
        bool l_res = true;
        res = true;
        ifn(Config->name) {
            LOG_ERROR(SOUND_RECORDER, "SOUND_RECORDER_%u,Name,Err", Config->num);
            res = false;
        }

        ifn(Config->RxSampleArray) {
            LOG_ERROR(SOUND_RECORDER, "SOUND_RECORDER_%u,RxSampleArray,Err", Config->num);
            res = false;
        }

        l_res = i2s_is_valid_num(Config->i2s_num);
        ifn(l_res) {
            LOG_ERROR(SOUND_RECORDER, "SOUND_RECORDER_%u,i2s_num,Err", Config->num);
            res = false;
        }

        ifn(Config->frame_pattern) {
            LOG_ERROR(SOUND_RECORDER, "SOUND_RECORDER_%u,frame_pattern,Err", Config->num);
            res = false;
        }

        ifn(0 < Config->rx_sample_array_size) {
            LOG_ERROR(SOUND_RECORDER, "SOUND_RECORDER_%u,rx_sample_array_size,Err", Config->num);
            res = false;
        }

        ifn(8 <= Config->sample_bitness) {
            LOG_ERROR(SOUND_RECORDER, "SOUND_RECORDER_%u,sample_bitness,Err", Config->num);
            res = false;
        }

        l_res = audio_is_valid_frequency(Config->sample_freq_hz) ;
        ifn(l_res) {
            LOG_ERROR(SOUND_RECORDER, "SOUND_RECORDER_%u,sample_freq_hz,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool sound_recorder_init_custom(void) {
    bool res = false;
    LOG_INFO(SOUND_RECORDER, "Version:%u", SOUND_RECORDER_VERSION);
    LOG_INFO(SOUND_RECORDER, "REC_MEM_SAM_CNT:%u Sam", REC_MEM_SAM_CNT);
    LOG_INFO(SOUND_RECORDER, "REC_SIZE_OF:%u Byte", REC_SIZE_OF);
    LOG_INFO(SOUND_RECORDER, "Frames:%u", REC_FRAMES);
    LOG_INFO(SOUND_RECORDER, "PartDuration:%f s", REC_PART_DURATION_S);
    return res;
}

static inline bool sound_recorder_proc_idle(  SoundRecorderHandle_t* Node) {
    bool res = false;
    return res;
}

static inline bool sound_recorder_stop_ll(SoundRecorderHandle_t* Node) {
    bool res = false;
    res = i2s_dma_stop(Node->i2s_num);
    log_info_res(SOUND_RECORDER, res, "I2sDmaStop");

    FRESULT ret = f_close(&Node->FileToRec);
    res = FatFsRetToRes(ret, "CloseFile");
    if(res) {
        LOG_INFO(SOUND_RECORDER, "CloseFile:[%s]Ok", Node->file_name);
    } else {
        LOG_ERROR(SOUND_RECORDER, "CloseFile:[%s]Err", Node->file_name);
    }
    Node->stop_rec_ms = time_get_ms32();
    Node->state = SOUND_RECORDER_STATE_IDLE;

    uint32_t duration_ms =  Node->stop_rec_ms -  Node->start_rec_ms ;
    LOG_INFO(SOUND_RECORDER, "RecDuration:%u ms", duration_ms);
    LOG_INFO(SOUND_RECORDER, "WrOkCnt:%u", Node->wr_ok_cnt);
    LOG_INFO(SOUND_RECORDER, "errorCnt:%u", Node->error_cnt);
    LOG_INFO(SOUND_RECORDER, "WrSzErrorCnt:%u", Node->error_size_cnt);
    LOG_INFO(SOUND_RECORDER, "longWriteErrorCnt:%u", Node->long_write_error_cnt);
    Node->state = SOUND_RECORDER_STATE_IDLE;
    Node->action = SOUND_RECORDER_ACTION_NOPE;
    return res;
}


static inline bool sound_rec_save_part_offset(SoundRecorderHandle_t* Node, uint32_t offset, uint32_t need_size) {
    bool res = false;
    if(Node->cur_save_size < Node->total_file_size) {
        UINT written = 0;
        uint32_t start_save_us = time_get_us32();
        void* buff = (void* )    ( (   (uint32_t ) Node->RxSampleArray) +  offset     );
        FRESULT ret = f_write(&Node->FileToRec, buff, need_size, &written);
        uint32_t end_save_us = time_get_us32();
        if(FR_OK == ret) {
            if(need_size == written) {
                Node->cur_save_size += written;
                Node->wr_ok_cnt++;
                res = true;
            } else {
                Node->error_size_cnt++;
                //LOG_ERROR(SOUND_RECORDER,"WriteSmall:%u Byte", written);
                res = sound_recorder_stop_ll(Node);
            }
            Node->action = SOUND_RECORDER_ACTION_NOPE;
        } else {
            Node->error_cnt++;
            Node->action = SOUND_RECORDER_ACTION_NOPE;
            res = sound_recorder_stop_ll(Node);
        }
        uint32_t diff_us = end_save_us-start_save_us;
        if (REC_PART_TIMEOUT_US < diff_us) {
            Node->long_write_error_cnt++;
            res = sound_recorder_stop_ll(Node);
        }
    } else {
        res = sound_recorder_stop_ll(Node);
    }
    return res;
}


static inline bool sound_recorder_save_to_part1(SoundRecorderHandle_t* Node) {
    bool res = false;
    res = sound_rec_save_part_offset(Node, 0, REC_HALF_SIZE_OF);
    return res;
}

static inline bool sound_recorder_save_to_part2(SoundRecorderHandle_t* Node) {
    bool res = false;
    res = sound_rec_save_part_offset(Node, REC_HALF_SIZE_OF, REC_HALF_SIZE_OF);
    return res;
}

#if 0
static inline bool sound_recorder_proc_rec_part_1(SoundRecorderHandle_t* Node) {
    bool res = false;
    if(Node->I2s) {
        if(Node->I2s->rx_half) {
            Node->I2s->rx_half = false;
           // Node->state = SOUND_RECORDER_STATE_REC_PART_2;
            res = sound_recorder_save_to_part1(Node);
        }

        if(Node->I2s->rx_done) {
            Node->I2s->rx_done = false;
           // Node->state = SOUND_RECORDER_STATE_REC_PART_1;
            res = sound_recorder_save_to_part2(Node);
            Node->i2s_error_cnt++;
        }
    }

    if(Node->total_file_size <= Node->cur_save_size) {
        res = sound_recorder_stop_ll(Node);
        if(res) {
            Node->state = SOUND_RECORDER_STATE_IDLE;
        }
    }

    return res;
}

static inline bool sound_recorder_proc_rec_part_2(  SoundRecorderHandle_t* Node) {
    bool res = false;
    if(Node->I2s) {
        if(Node->I2s->rx_half) {
            Node->I2s->rx_half = false;
           // Node->state = SOUND_RECORDER_STATE_REC_PART_2;
            res = sound_recorder_save_to_part1(Node);
            Node->i2s_error_cnt++;
        }

        if(Node->I2s->rx_done) {
            Node->I2s->rx_done = false;
           // Node->state = SOUND_RECORDER_STATE_REC_PART_1;
            res = sound_recorder_save_to_part2(Node);
        }
    }

    if(Node->total_file_size <= Node->cur_save_size) {
        res = sound_recorder_stop_ll(Node);
        if(res) {
            Node->state = SOUND_RECORDER_STATE_IDLE;
        }
    }

    return res;
}
#endif



bool sound_recorder_init_common(const SoundRecorderConfig_t* const Config, SoundRecorderHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->rx_sample_array_size = Config->rx_sample_array_size;
            Node->frame_pattern = Config->frame_pattern;
            Node->sample_bitness = Config->sample_bitness;
            Node->sample_freq_hz = Config->sample_freq_hz;
            Node->i2s_num = Config->i2s_num;
            Node->RxSampleArray = Config->RxSampleArray;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool sound_recorder_init_node(SoundRecorderHandle_t* const Node) {
    bool res = false;
    if (Node) {
        Node->action = SOUND_RECORDER_ACTION_NOPE;
        Node->state = SOUND_RECORDER_STATE_IDLE;
        Node->spin = 0;
        Node->valid = true;
        Node->I2s = I2sGetNode(Node->i2s_num);
        if(Node->I2s){
            res = true;
        }
    }
    return res;
}

bool sound_recorder_compose_wav_header(const SoundRecorderHandle_t* const Rec,
                                       WavHeader_t* const Header) {
    bool res = false;
    if(Rec) {
        LOG_INFO(WAV, "%s", SoundRecorderNodeToStr(Rec));
        if(Header) {
            uint32_t chan_cnt =  DdsFramePatToNumChann(Rec->frame_pattern);
            uint32_t byte_per_sample = (Rec->sample_bitness/8)*chan_cnt;
            uint32_t data_size =  Rec->sample_cnt*(Rec->sample_bitness/8);

            Header->chunkId = reverse_byte_order_uint32(0x52494646); /*RIFF*/
            Header->chunkSize = data_size+sizeof(WavHeader_t)-8; /**/
            Header->format = reverse_byte_order_uint32(0x57415645); /*WAVE*/
            Header->subchunk1Id = reverse_byte_order_uint32(WAV_SECTION_ID_FMT); /*fmt */
            Header->subchunk1Size = WAV_SECTION_FMT_SIZE ;
            Header->audioFormat = WAVE_COMPRESSION_CODE_PCM ; /*PCM*/
            Header->numChannels = chan_cnt; /**/
            Header->sampleRate = Rec->sample_freq_hz; /**/
            Header->aver_bytes_per_sec = byte_per_sample* Rec->sample_freq_hz; /**/
            Header->blockAlign = byte_per_sample; /**/
            Header->bitsPerSample = Rec->sample_bitness; /**/
            Header->subchunk2Id = reverse_byte_order_uint32(WAV_SECTION_ID_DATA ); /*data 0x64617461*/
            Header->subchunk2Size =  Rec->sample_cnt*(Rec->sample_bitness/8); /**/
            LOG_INFO(WAV, "%s",WavHeaderToStr(Header));
            res = true;
        }
    }
    return res;
}

#define FAT_FS_MODE_REC (FA_WRITE | FA_CREATE_ALWAYS)

bool sound_recorder_start(const uint8_t num, const char* const file_name,  const float duration_s) {
    bool res = false;
    SoundRecorderHandle_t* Node = SoundRecorderGetNode(num);
    if(Node) {
        Node->wr_ok_cnt = 0 ;
        Node->long_write_error_cnt = 0 ;
        Node->error_cnt = 0 ;
        Node->i2s_error_cnt = 0 ;
        Node->cur_save_size = 0 ;
        uint8_t channel_cnt = DdsFramePatToNumChann(Node->frame_pattern);
        float sample_duration_s = 1.0f / ( (float ) Node->sample_freq_hz);
        uint32_t sample_size = Node->sample_bitness / 8;
        uint32_t one_record_size = sample_size * channel_cnt;
        Node->sample_cnt = duration_s/sample_duration_s;
        Node->data_size =  one_record_size * Node->sample_cnt;
        snprintf(Node->name, sizeof(Node->name),"R%u_%s.wav", Node->rec_cnt, FloatToStr(duration_s,2));
        Node->total_file_size = Node->data_size+sizeof(WavHeader_t);
        WavHeader_t Header = {0};
        res = sound_recorder_compose_wav_header(Node, &Header);
        if(res) {
            strcpy(Node->file_name,file_name);
            FRESULT ret = f_open(&Node->FileToRec, (const TCHAR*)file_name, FAT_FS_MODE_REC);
            if(FR_OK==ret) {
                UINT written = 0 ;
                ret = f_write(&Node->FileToRec, (void*) Header.buff, (UINT) sizeof(WavHeader_t), &written);
                if(FR_OK==ret) {
                     if(sizeof(WavHeader_t)==written) {
                         Node->cur_save_size += written;
                         res = i2s_audio_set_data_dirrection(Node->i2s_num, INTERFACE_OPERATION_RECEPTION);
                         res = i2s_gpio_set_read(Node->i2s_num);
                         if(res) {
                             // TODO print rec metadata
                             LOG_INFO(SOUND_RECORDER, "RecStart...");
                             Node->start_rec_ms = time_get_ms32();
                             res = i2s_mcal_read(Node->i2s_num, (uint16_t* ) Node->RxSampleArray, Node->rx_sample_array_size);
                             if(res) {
                                 Node->state = SOUND_RECORDER_STATE_REC_PART_1;
                             }
                         }
                     }
                }
            }

        }
        Node->rec_cnt++;
    }
    return res;
}

bool  sound_recorder_test_start(const uint8_t num, float duration_s) {
    bool res = false;
    uint32_t up_time_ms= time_get_ms32();
    char nameRec[80] = {0};
    uint32_t duration_ms = 1000.0*duration_s;
    snprintf(nameRec,sizeof(nameRec),"R_%u_UT%u_%uMs.wav",REC_MEM_SAM_CNT,up_time_ms, duration_ms);
    res = sound_recorder_start(num, nameRec,  duration_s);
    return res;
}

bool sound_recorder_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(SOUND_RECORDER, "SOUND_RECORDER_%u,Proc", num);
    SoundRecorderHandle_t* Node = SoundRecorderGetNode(num);
    if(Node) {
        switch(Node->action){
            case SOUND_RECORDER_ACTION_SAVE_PART_1: {
                res = sound_recorder_save_to_part1(Node);
            }break;
            case SOUND_RECORDER_ACTION_SAVE_PART_2: {
                res = sound_recorder_save_to_part2(Node);
            }break;
            case SOUND_RECORDER_ACTION_NOPE: break;
            default: break;
        }

        if(SOUND_RECORDER_STATE_REC_PART_2==Node->state ||
                SOUND_RECORDER_STATE_REC_PART_1==Node->state ){

            if(Node->total_file_size <= Node->cur_save_size) {
                res = sound_recorder_stop_ll(Node);
                if(res) {
                    Node->state = SOUND_RECORDER_STATE_IDLE;
                }
            }
        }


        Node->spin++;
    }
    return res;
}

bool sound_recorder_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SOUND_RECORDER, "SOUND_RECORDER_%u", num);
    const SoundRecorderConfig_t *Config = SoundRecorderGetConfig(num);
    res = SoundRecorderIsValidConfig(Config);
    if(res) {
#ifdef HAS_SOUND_RECORDER_DIAG
        LOG_WARNING(SOUND_RECORDER, "%s", SoundRecorderConfigToStr(Config));
#endif
        SoundRecorderHandle_t *Node = SoundRecorderGetNode(num);
        if(Node) {
            res = sound_recorder_init_common(Config, Node);
            res = sound_recorder_init_node(Node);
            Node->init = true;
        } else {
            LOG_ERROR(SOUND_RECORDER, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(SOUND_RECORDER, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(SOUND_RECORDER, SOUND_RECORDER, sound_recorder)
COMPONENT_PROC_PATTERT(SOUND_RECORDER, SOUND_RECORDER, sound_recorder)
