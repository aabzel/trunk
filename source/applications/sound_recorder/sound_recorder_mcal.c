#include "sound_recorder_mcal.h"

#include "audio.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "dds_drv.h"
#include "dwt_mcal.h"
#include "fat_fs.h"
#include "float_diag.h"
#include "i2s_mcal.h"
#include "led_mono_drv.h"
#include "log.h"
#include "string_reader.h"
#include "wav.h"
#include "wav_diag.h"
#include "wm8731_drv.h"

COMPONENT_IS_VALID(SoundRecorder, sound_recorder)
COMPONENT_GET_NODE(SoundRecorder, sound_recorder)
COMPONENT_GET_CONFIG(SoundRecorder, sound_recorder)

/*ISO-26262 require verify configuration*/
bool SoundRecorderIsValidConfig(const SoundRecorderConfig_t* const Config) {
    bool res = false;
    if (Config) {
        bool l_res = true;
        res = true;
        ifn(Config->name) {
            LOG_ERROR(SOUND_RECORDER, "SOUND_RECORDER_%u,Name,Err", Config->num);
            res = false;
        }
#if 0
        ifn(Config->FixRxSampleArray) {
            LOG_ERROR(SOUND_RECORDER, "SOUND_RECORDER_%u,FixRxSampleArray,Err", Config->num);
            res = false;
        }
#endif

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

        l_res = audio_is_valid_frequency(Config->sample_freq_hz);
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

static inline bool sound_recorder_proc_idle(SoundRecorderHandle_t* Node) {
    bool res = false;
    return res;
}

static inline bool sound_recorder_stop_ll(SoundRecorderHandle_t* Node) {
    bool res = false;
    res = i2s_dma_stop(Node->i2s_num);
    Node->stop_rec_ms = time_get_ms32();
    Node->duration_ms = Node->stop_rec_ms - Node->start_rec_ms;
    log_info_res(SOUND_RECORDER, res, "I2sDmaStop");

    FRESULT ret = f_close(&Node->FileToRec);
    res = FatFsRetToRes(ret, "CloseFile");
    if (res) {
        LOG_DEBUG(SOUND_RECORDER, "CloseFile:[%s]Ok", Node->file_name);
    } else {
        LOG_ERROR(SOUND_RECORDER, "CloseFile:[%s]Err", Node->file_name);
    }
    Node->state = SOUND_RECORDER_STATE_IDLE;
    Node->action = SOUND_RECORDER_ACTION_NOPE;
    Node->rec = false;
    Node->is_rec = false;

    res = fat_fs_touch(Node->file_name);
    log_debug_res(SOUND_RECORDER, res, "Touch");
    led_mono_sw_pwm_duty(Node->led_num, 50);

    sound_recorder_stop_report(Node);
    i2s_init_one(Node->i2s_num);

    LOG_WARNING(SOUND_RECORDER, "RecStop:[%s]", Node->file_name);
    return res;
}

#if 0
bool sound_rec_fix_part(SoundRecorderHandle_t* Node, uint32_t sam_index) {
    bool res = true;
    uint32_t i = 0;
    for(i = sam_index; i < (sam_index + REC_MEM_HALF_SIZE); i++) {
        Node->FixRxSampleArray[i] = Node->RxSampleArray[i];
    }
    return res;
}
#endif

static inline bool sound_rec_save_part_offset(SoundRecorderHandle_t* Node,
                                              uint32_t sam_index,
                                              uint32_t need_size,
                                              SoundRecorderLoadStatus_t status) {
    bool res = false;
    Node->status = SOUND_RECORDER_STATUS_NOPE;
    // i2s_interrupt_ctrl(Node->i2s_num, false);
    if (Node->cur_save_size < Node->total_file_size) {
        UINT written = 0;
        // void *buff = (void*) (((uint32_t) Node->FixRxSampleArray) + offset);
        // uint32_t start_save_us = time_get_us32();
        FRESULT ret = f_write(&Node->FileToRec, &(Node->RxSampleArray[sam_index]), need_size, &written);
        // uint32_t end_save_us = time_get_us32();
        if (FR_OK == ret) {
            if (need_size == written) {
                Node->cur_save_size += written;
                Node->status = status;
                Node->wr_ok_cnt++;
                res = true;
            } else {
                Node->error_size_cnt++;
                // LOG_ERROR(SOUND_RECORDER,"WriteSmall:%u Byte", written);
                res = sound_recorder_stop_ll(Node);
            }
            Node->action = SOUND_RECORDER_ACTION_NOPE;
        } else {
            Node->fat_fs_err_code = ret;
            /*File system in SD card curruptes*/
            Node->error_cnt++;
            Node->action = SOUND_RECORDER_ACTION_NOPE;
            res = sound_recorder_stop_ll(Node);
        }
#if 0
        uint32_t diff_us = end_save_us - start_save_us;
        if(REC_PART_TIMEOUT_US < diff_us) {
            Node->long_write_error_cnt++;
            // res = sound_recorder_stop_ll(Node);
        }
#endif
    } else {
        res = sound_recorder_stop_ll(Node);
    }
    // i2s_interrupt_ctrl(Node->i2s_num, true);
    return res;
}

static inline bool sound_recorder_save_to_part1(SoundRecorderHandle_t* Node) {
    bool res = false;
    uint32_t need_size = sizeof(SampleType_t) * Node->rx_sample_array_size / 2;
    res = sound_rec_save_part_offset(Node, 0, need_size, SOUND_RECORDER_STATUS_PART_1_SAVED);
    return res;
}

static inline bool sound_recorder_save_to_part2(SoundRecorderHandle_t* Node) {
    bool res = false;
    uint32_t need_size = sizeof(SampleType_t) * Node->rx_sample_array_size / 2;
    res = sound_rec_save_part_offset(Node, Node->rx_sample_array_size / 2, need_size,
            SOUND_RECORDER_STATUS_PART_2_SAVED);
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

static inline bool sound_recorder_proc_rec_part_2( SoundRecorderHandle_t* Node) {
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

bool sound_recorder_fs_set(const uint8_t num, const uint32_t sample_freq_hz) {
    bool res = false;
    SoundRecorderHandle_t *Node = SoundRecorderGetNode(num);
    if (Node) {
        LOG_INFO(SOUND_RECORDER, "Set,SamFreqHz,%u->%u", Node->sample_freq_hz, sample_freq_hz);
        Node->sample_freq_hz = sample_freq_hz;
        res = true;
    }
    return res;
}

bool sound_recorder_init_common(const SoundRecorderConfig_t* const Config, SoundRecorderHandle_t* const Node) {
    bool res = false;
    if (Config) {
        if (Node) {
            Node->wm8731_num = Config->wm8731_num;
            Node->rx_sample_array_size = Config->rx_sample_array_size;
            Node->frame_pattern = Config->frame_pattern;
            Node->led_num = Config->led_num;
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
        if (Node->I2s) {
            res = true;
        }
    }
    return res;
}

bool sound_recorder_compose_wav_header(const SoundRecorderHandle_t* const Rec, WavHeader_t* const Header) {
    bool res = false;
    if (Rec) {
        LOG_INFO(WAV, "%s", SoundRecorderNodeToStr(Rec));
        if (Header) {
            uint32_t chan_cnt = DdsFramePatToNumChann(Rec->frame_pattern);
            uint32_t byte_per_sample = (Rec->sample_bitness / 8) * chan_cnt;
            uint32_t data_size = Rec->sample_cnt * (Rec->sample_bitness / 8) * chan_cnt;

            Header->chunkId = reverse_byte_order_uint32(WAV_RIFF); /*RIFF*/
            Header->chunkSize = data_size + sizeof(WavHeader_t) - 8; /**/
            Header->format = reverse_byte_order_uint32(WAV_WAVE); /*WAVE*/
            Header->subchunk1Id = reverse_byte_order_uint32(WAV_SECTION_ID_FMT); /*fmt */
            Header->subchunk1Size = WAV_SECTION_FMT_SIZE;
            Header->audioFormat = WAVE_COMPRESSION_CODE_PCM; /*PCM*/
            Header->numChannels = chan_cnt; /**/
            Header->sampleRate = Rec->sample_freq_hz; /**/
            Header->aver_bytes_per_sec = byte_per_sample * Rec->sample_freq_hz; /**/
            Header->blockAlign = byte_per_sample; /**/
            Header->bitsPerSample = Rec->sample_bitness; /**/
            Header->subchunk2Id = reverse_byte_order_uint32(WAV_SECTION_ID_DATA); /*data 0x64617461*/
            Header->subchunk2Size = data_size; /**/
            LOG_INFO(WAV, "%s", WavHeaderToStr(Header));
            res = true;
        }
    }
    return res;
}

static bool sound_recorder_init_start(SoundRecorderHandle_t* Node, const float duration_s) {
    bool res = true;
    Node->wr_ok_cnt = 0;
    Node->long_save_error = 0;
    Node->long_write_error_cnt = 0;
    Node->error_cnt = 0;
    Node->i2s_error_cnt = 0;
    Node->cur_save_size = 0;
    Node->rec_need_duration_ms = SEC_2_MSEC(duration_s);
    uint8_t channel_cnt = DdsFramePatToNumChann(Node->frame_pattern);
    float sample_duration_s = 1.0f / ((float) Node->sample_freq_hz);
    uint32_t sample_size = Node->sample_bitness / 8;
    uint32_t one_record_size = sample_size * channel_cnt;
    Node->sample_cnt = duration_s / sample_duration_s;
    Node->data_size = one_record_size * Node->sample_cnt;
    Node->total_file_size = Node->data_size + sizeof(WavHeader_t);
    return res;
}

bool sound_recorder_set_temp_mem(const uint8_t num,
                                 const SampleType_t* const SampleArray,
                                 uint32_t const sample_array_size) {
    bool res = false;
    SoundRecorderHandle_t *Node = SoundRecorderGetNode(num);
    if (Node) {
        Node->RxSampleArray = SampleArray;
        Node->rx_sample_array_size = sample_array_size;
        res = true;
    }
    return res;
}

bool sound_recorder_post_pone_rec(const uint8_t num, bool on_off) {
    bool res = false;
    SoundRecorderHandle_t *Node = SoundRecorderGetNode(num);
    if (Node) {
        Node->postponed_rec_start = on_off;
        res = true;
    }
    return res;
}

static bool sound_recorder_start_indication_ll(SoundRecorderHandle_t* Node) {
    bool res = false;
    Node->start_rec_ms = time_get_ms32();
    Node->state = SOUND_RECORDER_STATE_REC_PART_1;
    Node->is_rec = true;
    Node->rec = true;
    res = led_mono_sw_pwm_duty(Node->led_num, 5);
    return res;
}

bool sound_recorder_start_indication(const uint8_t num) {
    bool res = false;
    SoundRecorderHandle_t *Node = SoundRecorderGetNode(num);
    if (Node) {
        res = sound_recorder_start_indication_ll(Node);
    }
    return res;
}

#define FAT_FS_MODE_REC (FA_WRITE | FA_CREATE_ALWAYS)
bool sound_recorder_start(const uint8_t num, const char* const file_name, const float duration_s) {
    bool res = false;
    SoundRecorderHandle_t *Node = SoundRecorderGetNode(num);
    if (Node) {
        if (false == Node->is_rec) {
            sound_recorder_init_start(Node, duration_s);
            WavHeader_t Header = { 0 };
            res = sound_recorder_compose_wav_header(Node, &Header);
            if (res) {
                strcpy(Node->file_name, file_name);
                FRESULT ret = f_open(&Node->FileToRec, (const TCHAR*) file_name, FAT_FS_MODE_REC);
                if (FR_OK == ret) {
                    UINT written = 0;
                    ret = f_write(&Node->FileToRec, (void*) Header.buff, (UINT) sizeof(WavHeader_t), &written);
                    if (FR_OK == ret) {
                        if (sizeof(WavHeader_t) == written) {
                            Node->cur_save_size += written;
                            wm8731_sample_rate(Node->wm8731_num, Node->sample_freq_hz);

                            I2sHandle_t *I2s = I2sGetNode(Node->i2s_num);
                            if (FULL_DUPLEX_OFF == I2s->full_duplex) {
                                res = i2s_audio_set_data_dirrection(Node->i2s_num, INTERFACE_OPERATION_RECEPTION);
                                res = i2s_gpio_set_read(Node->i2s_num);
                            }
                            if (res) {
                                if (false == Node->postponed_rec_start) {
                                    LOG_INFO(SOUND_RECORDER, "RecStart...");
                                    res = i2s_mcal_read(Node->i2s_num, (uint16_t*) Node->RxSampleArray,
                                            Node->rx_sample_array_size);
                                    if (res) {
                                        // TODO print rec metadata
                                        res = sound_recorder_start_indication_ll(Node);
                                    }
                                }
                            }
                            Node->rec = true;
                        }
                    }
                }
            }
            Node->rec_cnt++;
        }
    }
    return res;
}

bool sound_recorder_test_start(const uint8_t num, float duration_s) {
    bool res = false;
    char nameRec[80] = { 0 };
    res = wav_file_name_generate(nameRec, sizeof(nameRec), REC_MEM_SAM_CNT, duration_s);
    res = sound_recorder_start(num, nameRec, duration_s);
    return res;
}

bool sound_recorder_proc_one_ll(SoundRecorderHandle_t* Node) {
    bool res = false;
    if (Node->rec) {

        switch (Node->action) {
            case SOUND_RECORDER_ACTION_SAVE_PART_1: {
                res = sound_recorder_save_to_part1(Node);
            }
                break;
            case SOUND_RECORDER_ACTION_SAVE_PART_2: {
                res = sound_recorder_save_to_part2(Node);
            }
                break;
            case SOUND_RECORDER_ACTION_NOPE:
                break;
            default:
                break;
        }

        if (SOUND_RECORDER_STATE_REC_PART_2 == Node->state || SOUND_RECORDER_STATE_REC_PART_1 == Node->state) {
            if (Node->total_file_size <= Node->cur_save_size) {
                res = sound_recorder_stop_ll(Node);
            }

            uint32_t cur_duration_ms = time_get_ms32() - Node->start_rec_ms;
            if (Node->rec_need_duration_ms < cur_duration_ms) {
                /*player can stop I2S DMA We need extra rec termination rule*/
                res = sound_recorder_stop_ll(Node);
            }
        }

    }else{
        Node->state = SOUND_RECORDER_STATE_IDLE;
    }
    Node->spin++;

    return res;
}

#if 0
bool super_cycle_proc_max_perf(void) {
    bool res = true;
    res = sound_recorder_proc_one_ll(&SoundRecorderInstance[0]);
    res = dwt_proc_one(1);
    res = led_mono_proc_one(1);
    if(false == SoundRecorderInstance[0].is_rec) {
        res = string_reader_proc_one(STRING_READER_NUM_UART2);
    }
    return res;
}
#endif

bool sound_recorder_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(SOUND_RECORDER, "SOUND_RECORDER_%u,Proc", num);
    SoundRecorderHandle_t *Node = SoundRecorderGetNode(num);
    if (Node) {
        res = sound_recorder_proc_one_ll(Node);
    }
    return res;
}

#if 0
bool sound_recorder_is_valid_num(uint8_t num) {
    bool res = false;
    SoundRecorderHandle_t *Node = SoundRecorderGetNode(num);
    if (Node) {
        res = true;
    }
    return res;
}
#endif

bool sound_recorder_is_idle(const uint8_t num) {
    bool res = false;
    SoundRecorderHandle_t *Node = SoundRecorderGetNode(num);
    if (Node) {
        res = SOUND_RECORDER_STATE_IDLE == Node->state;
    }
    return res;
}

bool sound_recorder_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SOUND_RECORDER, "SOUND_RECORDER_%u", num);
    const SoundRecorderConfig_t *Config = SoundRecorderGetConfig(num);
    res = SoundRecorderIsValidConfig(Config);
    if (res) {
#ifdef HAS_SOUND_RECORDER_DIAG
        LOG_WARNING(SOUND_RECORDER, "%s", SoundRecorderConfigToStr(Config));
#endif
        SoundRecorderHandle_t *Node = SoundRecorderGetNode(num);
        if (Node) {
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
