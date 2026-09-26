#include "wav.h"

/* That code must work at PC and MCU */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "audio.h"
#include "byte_utils.h"
#include "code_generator.h"
#include "csv.h"
#include "dds_drv.h"
#include "file_mcal.h"
#include "float_diag.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_FILE_PC
#include "file_pc.h"
#endif

#ifdef HAS_FIR
#include "fir.h"
#endif

#ifdef HAS_IIR
#include "iir.h"
#endif

// https://audiocoding.cc/articles/2008-05-22-wav-file-structure/

COMPONENT_GET_NODE(Wav, wav)
COMPONENT_GET_CONFIG(Wav, wav)

static bool wav_init_common(const WavConfig_t* const Config, WavHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->file_num = Config->file_num;
            Node->channels = Config->channels;
            strcpy(Node->fileName, Config->file_name_dflt);
            Node->sample_cnt = Config->sample_cnt;
            Node->sampling_frequency_hz = Config->sampling_frequency_hz;
            res = true;
        }
    }
    return res;
}

bool WavHeaderToNode(const WavHeader_t* const Header, WavHandle_t* const Node) {
    bool res = false;
    if(Header) {
        if(Node) {
            Node->bits_per_sample = Header->bitsPerSample;
            Node->sampling_frequency_hz = (float)Header->sampleRate;
            Node->sample_time_s = 1.0 / ((double)Header->sampleRate);
            Node->data_size = (float)Header->subchunk2Size;
            Node->sample_cnt = Header->subchunk2Size / Header->blockAlign;
            Node->duration_s = Node->sample_time_s * ((double)Node->sample_cnt);
            res = true;
        }
    }
    return res;
}

uint32_t WavHeaderToPlayDurationMs(const WavHeader_t* const pHeader) {
    uint32_t duration_ms = 10000;
    bool res = wav_is_valid_header(pHeader);
    if(res) {
        WavInfo_t Info = {0};
        res = WavHeaderToInfo(pHeader, &Info);
        if(res) {
            duration_ms = SEC_2_MSEC(Info.duration_s);
        }
    }
    return duration_ms;
}

uint32_t WavHeaderToFrameSize(WavHeader_t* Header) {
    uint32_t bytes_per_frame = 0;
    if(Header) {
        bytes_per_frame = Header->numChannels * Header->bitsPerSample / 8;
        if(bytes_per_frame != Header->blockAlign) {
            LOG_ERROR(WAV, "blockAlign:%u NotEqualToBytesPerFrame:%u");
        }
    }
    return bytes_per_frame;
}

bool wav_is_valid_header(const WavHeader_t* const pHeader) {
    bool res = false;
    if(pHeader) {
        res = true;
        ifn(reverse_byte_order_uint32(WAV_RIFF) == pHeader->chunkId) {
            LOG_ERROR(WAV, "Err,chunkId:0x%x", pHeader->chunkId);
            res = false;
        }

        ifn(pHeader->audioFormat) {
            LOG_ERROR(WAV, "Err,audioFormat:0x%x", pHeader->audioFormat);
            res = false;
        }
        ifn(reverse_byte_order_uint32(WAV_WAVE) == pHeader->format) {
            LOG_ERROR(WAV, "Err,format:0x%08x", pHeader->format);
            res = false;
        }

        ifn(reverse_byte_order_uint32(WAV_SECTION_ID_FMT) == pHeader->subchunk1Id) {
            LOG_ERROR(WAV, "Err,subchunk1Id:0x%08x", pHeader->subchunk1Id);
            res = false;
        }
        ifn(0 < pHeader->chunkSize) {
            LOG_ERROR(WAV, "Err,chunkSize:%u Byte", pHeader->chunkSize);
            res = false;
        }

        ifn(0 < pHeader->subchunk1Size) {
            LOG_ERROR(WAV, "Err,subchunk1Size:%u Byte", pHeader->subchunk1Size);
            res = false;
        }

        ifn(0 < pHeader->numChannels) {
            LOG_ERROR(WAV, "Err,numChannels:%u", pHeader->numChannels);
            res = false;
        }

        ifn(0 < pHeader->sampleRate) {
            LOG_ERROR(WAV, "Err,sampleRate:%u Hz", pHeader->sampleRate);
            res = false;
        }

        ifn(0 < pHeader->aver_bytes_per_sec) {
            LOG_ERROR(WAV, "Err,aver_bytes_per_sec:%u Byte", pHeader->aver_bytes_per_sec);
            res = false;
        }

        ifn(0 < pHeader->blockAlign) {
            LOG_ERROR(WAV, "Err,blockAlign:%u Byte", pHeader->blockAlign);
            res = false;
        }

        ifn(0 < pHeader->bitsPerSample) {
            LOG_ERROR(WAV, "Err,bitsPerSample:%u Bits", pHeader->bitsPerSample);
            res = false;
        }

        ifn(reverse_byte_order_uint32(WAV_SECTION_ID_DATA) == pHeader->subchunk2Id) {
            LOG_ERROR(WAV, "Err,subchunk2Id:0x%08x", pHeader->subchunk2Id);
            res = false;
        }

        ifn(0 < pHeader->subchunk2Size) {
            LOG_ERROR(WAV, "Err,subchunk2Size:%u Byte", pHeader->subchunk2Size);
            res = false;
        }
    }
    return res;
}

bool wav_header_to_handle(const WavHeader_t* const pHeader, WavHandle_t* const pHandle) {
    bool res = false;
    if(pHeader) {
        if(pHandle) {
            pHandle->sample_time_s = 1.0 / ((float)pHeader->sampleRate);
            pHandle->sample_cnt = pHeader->subchunk2Size / pHeader->blockAlign;
            pHandle->duration_s = pHandle->sample_time_s * ((float)pHandle->sample_cnt);
            pHandle->data_size = pHeader->subchunk2Size;
            pHandle->bits_per_sample = pHeader->bitsPerSample;
            pHandle->block_align = pHeader->blockAlign;
            pHandle->sampling_frequency_hz = pHeader->sampleRate;
            pHandle->channels = pHeader->numChannels;
            LOG_NOTICE(WAV, "%s", WavNodeToStr(pHandle));
            res = true;
        }
    }
    return res;
}

bool WavHeaderToInfo(const WavHeader_t* const Header, WavInfo_t* const Info) {
    bool res = false;
    if(Header) {
        if(Info) {
            Info->sampling_frequency_hz = (float)Header->sampleRate;
            Info->sample_time_s = 1.0f / ((float)Header->sampleRate);
            Info->data_size = (float)Header->subchunk2Size;
            Info->sample_cnt = Header->subchunk2Size / Header->blockAlign;
            Info->duration_s = Info->sample_time_s * ((double)Info->sample_cnt);
            Info->channels = Header->numChannels;
            Info->sample_size = Header->bitsPerSample / 8;
            res = true;
        }
    }
    return res;
}

bool wav_compose_header_by_dds(DdsHandle_t* const DDs, WavHeader_t* const Header) {
    bool res = false;
    if(DDs) {
        LOG_DEBUG(WAV, "%s", DdsNodeToStr(DDs));
        if(Header) {
            uint32_t chan_cnt = DdsFramePatToNumChann(DDs->frame_pattern);
            uint32_t byte_per_sample = (DDs->sample_bitness / 8) * chan_cnt;
            uint32_t data_size = DDs->sample_cnt * (DDs->sample_bitness / 8);

            Header->chunkId = reverse_byte_order_uint32(WAV_RIFF);                 /*RIFF*/
            Header->chunkSize = data_size + sizeof(WavHeader_t) - 8;               /**/
            Header->format = reverse_byte_order_uint32(WAV_WAVE);                  /*WAVE*/
            Header->subchunk1Id = reverse_byte_order_uint32(WAV_SECTION_ID_FMT);   /*fmt */
            Header->subchunk1Size = WAV_SECTION_FMT_SIZE;                          /**/
            Header->audioFormat = WAVE_COMPRESSION_CODE_PCM;                       /*PCM*/
            Header->numChannels = chan_cnt;                                        /**/
            Header->sampleRate = DDs->sample_per_second;                           /**/
            Header->aver_bytes_per_sec = byte_per_sample * DDs->sample_per_second; /**/
            Header->blockAlign = byte_per_sample;                                  /**/
            Header->bitsPerSample = DDs->sample_bitness;                           /**/
            Header->subchunk2Id = reverse_byte_order_uint32(WAV_SECTION_ID_DATA);  /*data*/
            Header->subchunk2Size = DDs->sample_cnt * (DDs->sample_bitness / 8);   /**/
            LOG_NOTICE(WAV, "%s", WavHeaderToStr(Header));
            res = true;
        }
    }
    return res;
}

static bool wav_init_custom(void) {
    bool res = true;
    return res;
}

bool wav_info_ll(WavHeader_t* const Header, const char* const file_name) {
    bool res = false;
    if(file_name) {
        res = file_mcal_open_re(FILE_MCAL_READ, file_name);
        if(res) {
            LOG_DEBUG(WAV, "OpenFile:[%s]Ok", file_name);
            uint32_t real_read = 0;
            // real_read = fread((void*)Header, 1, sizeof(WavHeader_t), pFileRead);
            real_read = file_mcal_read(FILE_MCAL_READ, Header->buff, sizeof(WavHeader_t));
            if(sizeof(WavHeader_t) == real_read) {
                res = wav_is_valid_header(Header);
                if(res) {
                    LOG_DEBUG(WAV, "Read,Ok");
                    LOG_NOTICE(WAV, "%s", WavHeaderToStr(Header));
                    WavHandle_t WavHandle = {0};
                    WavHandle.sample_time_s = 1.0 / ((float)Header->sampleRate);
                    WavHandle.sample_cnt = Header->subchunk2Size / Header->blockAlign;
                    WavHandle.duration_s = WavHandle.sample_time_s * ((float)WavHandle.sample_cnt);
                    LOG_NOTICE(WAV, "%s", WavNodeToStr(&WavHandle));
                } else {
                    LOG_ERROR(WAV, "HeaderCurrupted %s", file_name);
                }
            }

            res = file_mcal_close(FILE_MCAL_READ);
            // fclose(pFileRead);
        } else {
            LOG_ERROR(WAV, "OpenFile:[%s] Err", file_name);
        }
    }
    return res;
}

uint32_t wav_sampling_frequency_hz(const char* const file_name) {
    bool res = false;
    uint32_t sampling_frequency_hz = 0;
    WavInfo_t Info = {0};
    res = wav_read_file_metadata(file_name, &Info);
    if(res) {
        sampling_frequency_hz = Info.sampling_frequency_hz;
        LOG_INFO(WAV, "File:[%s],Fs:%u Hz", file_name, sampling_frequency_hz);
    }

    return sampling_frequency_hz;
}

float wav_read_file_duration(const char* const file_name) {
    bool res = false;

    float duration_s = -1.0;
    WavInfo_t Info = {0};
    res = wav_read_file_metadata(file_name, &Info);
    if(res) {
        duration_s = Info.duration_s;
    }

#if 0
    if(file_name) {
        res = file_mcal_open_re(FILE_MCAL_READ, file_name);
        if(res) {
            LOG_DEBUG(WAV, "OpenFile:[%s]Ok", file_name);
            uint32_t real_read = 0;
            WavHeader_t WavHeader = { 0 };
            real_read = file_mcal_read(FILE_MCAL_READ , WavHeader.buff, sizeof(WavHeader_t));

                if(sizeof(WavHeader_t) == real_read) {
                    LOG_DEBUG(WAV, "ReadHeader,Ok");
                    WavHandle_t Obj = { 0 };
                    res = WavHeaderToNode(&WavHeader, &Obj);
                    LOG_NOTICE(WAV, "%s", WavNodeToStr(&Obj));
                    duration_s = Obj.duration_s;
                    res = true;
                }


            res = file_mcal_close(FILE_MCAL_READ);
        } else {
            LOG_ERROR(WAV, "OpenFile:[%s] Err", file_name);
        }
    }
#endif
    return duration_s;
}

bool wav_read_file_metadata(const char* const file_name, WavInfo_t* const Info) {
    bool res = false;
    if(file_name) {
        res = file_mcal_open_re(FILE_MCAL_READ, file_name);
        if(res) {
            LOG_DEBUG(WAV, "OpenFile:[%s]Ok", file_name);
            uint32_t real_read = 0;
            WavHeader_t WavHeader = {0};
            real_read = file_mcal_read(FILE_MCAL_READ, WavHeader.buff, sizeof(WavHeader_t));
            if(sizeof(WavHeader_t) == real_read) {
                LOG_DEBUG(WAV, "Read,[%s],Header,Ok", file_name);
                res = wav_is_valid_header(&WavHeader);
                if(res) {
                    LOG_DEBUG(WAV, "HeaderValid");
                    res = WavHeaderToInfo(&WavHeader, Info);
                    LOG_NOTICE(WAV, "%s", WavInfoToStr(Info));
                    res = true;
                } else {
                    LOG_ERROR(WAV, "HeaderErr");
                    res = false;
                }
            } else {
                LOG_ERROR(WAV, "Read,Header,Err %u", real_read);
                res = false;
            }

            res = file_mcal_close(FILE_MCAL_READ);
        } else {
            res = false;
            LOG_ERROR(WAV, "MetaDataOpenFile:[%s] Err", file_name);
        }
    }
    return res;
}

bool wav_info(const char* const file_name) {
    bool res = false;
    if(file_name) {
        WavHeader_t WavHeader = {0};
        res = wav_info_ll(&WavHeader, file_name);
    }
    return res;
}

bool wav_shift_right(const char* const file_name, float duratuin_s) {
    bool res = false;
    WavInfo_t Info = {0};
    LOG_WARNING(WAV, "ShiftRight,File:[%s],Duration:%f s", file_name, duratuin_s);
    res = wav_read_file_metadata(file_name, &Info);
    if(res) {
        uint32_t samples = audio_duration_to_samples(Info.sampling_frequency_hz, duratuin_s);
        res = wav_shift_right_sample(file_name, "new_.wav", samples);
    }

    return res;
}

bool wav_shift_right2(uint8_t num, const float duratuin_s) {
    bool res = false;
    WavHandle_t* Wav = WavGetNode(num);
    if(Wav) {
        WavInfo_t Info = {0};
        LOG_WARNING(WAV, "ShiftRight,File:[%s],TimeOut:%f s", Wav->fileName, duratuin_s);
        res = wav_read_file_metadata(Wav->fileName, &Info);
        if(res) {
            uint32_t samples = audio_duration_to_samples(Info.sampling_frequency_hz, duratuin_s);
            char file_temp[80] = "temp1.wav";
            res = wav_shift_right_sample(Wav->fileName, file_temp, samples);
            res = file_mcal_delete(FILE_MCAL_WRITE, Wav->fileName);
            res = file_mcal_rename(FILE_MCAL_WRITE, file_temp, Wav->fileName);
        }
    }

    return res;
}

bool wav_info_sample(const char* const file_name) {
    bool res = false;
    if(file_name) {
        res = file_mcal_open_re(FILE_MCAL_READ, file_name);
        if(res) {
            LOG_DEBUG(WAV, "OpenFile:[%s]Ok", file_name);
            WavHeader_t WavHeader = {0};
            uint32_t real_read = file_mcal_read(FILE_MCAL_READ, WavHeader.buff, sizeof(WavHeader_t));
            if(sizeof(WavHeader_t) == real_read) {
                LOG_DEBUG(WAV, "ReadOk");
                LOG_NOTICE(WAV, "%s", WavHeaderToStr(&WavHeader));
                cli_printf(CRLF);
                uint32_t s = 0;

                WavHandle_t WavHandle = {0};
                WavHandle.sample_time_s = 1.0 / ((double)WavHeader.sampleRate);
                WavHandle.sample_cnt = WavHeader.subchunk2Size / WavHeader.blockAlign;
                WavHandle.duration_s = WavHandle.sample_time_s * ((double)WavHandle.sample_cnt);
                LOG_NOTICE(WAV, "%s", WavNodeToStr(&WavHandle));

                static const table_col_t cols[] = {
                    {8, "sam"}, {8, "time"}, {8, "prog"}, {8, "left"}, {8, "right"},
                };
                table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

                for(s = 0; s < WavHandle.sample_cnt; s++) {
                    double up_time_s = ((double)s) * WavHandle.sample_time_s;
                    WavSample16_t WavSample16 = {0};
                    cli_printf(TSEP);
                    cli_printf(" %6u " TSEP, s);
                    cli_printf(" %6.2f " TSEP, up_time_s);
                    cli_printf(" %6.2f " TSEP, 100.0 * up_time_s / WavHandle.duration_s);

                    real_read = file_mcal_read(FILE_MCAL_READ, (uint8_t*)&WavSample16, WavHeader.blockAlign);
                    if(WavHeader.blockAlign == real_read) {
                        cli_printf(" %6d " TSEP, WavSample16.left);
                        cli_printf(" %6d " TSEP, WavSample16.right);
                    } else {
                        res = false;
                        LOG_ERROR(WAV, "readDataErr:%u", real_read);
                    }
                    cli_printf(CRLF);
                }
                table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
                res = true;
            } else {
                LOG_ERROR(WAV, "readErr");
            }

            res = file_mcal_close(FILE_MCAL_READ);
        } else {
            LOG_ERROR(WAV, "OpenFile:[%s] Err", file_name);
        }
    }
    return res;
}

bool wav_samples_save(const WavHeader_t* const Header, const SampleType_t* const SampleArray, const uint32_t sample_cnt,
                      uint32_t repetitions) {
    bool res = false;
    if(Header) {
        LOG_DEBUG(WAV, "Save,Samples:%s", WavHeaderToStr(Header));
        if(SampleArray) {
            if(sample_cnt) {
                char file_name[300] = {0};
                res = WavHeaderToFileName(Header, file_name, sizeof(file_name));
                res = file_mcal_open_wb(FILE_MCAL_WRITE, file_name);
                if(res) {
                    // TODO change to file_mcal_write()
                    res = file_mcal_write(FILE_MCAL_WRITE, Header->buff, sizeof(WavHeader_t));
                    if(res) {
                        LOG_DEBUG(WAV, "Write,Header,Ok");
                        uint32_t r = 0;
                        for(r = 0; r < repetitions; r++) {
                            // TODO change to file_mcal_write()
                            res = file_mcal_write(FILE_MCAL_WRITE, (uint8_t*)SampleArray, sizeof(SampleType_t));
                            if(res) {
                                LOG_DEBUG(WAV, "Write,Data%u,Ok", r);
                            } else {
                                LOG_ERROR(WAV, "Write,Data,Err");
                            }
                        }
                    } else {
                        LOG_ERROR(WAV, "Write,Header,Err");
                    }
                    res = file_mcal_close(FILE_MCAL_WRITE);
                } else {
                    LOG_ERROR(WAV, "Open,File:[%s],Err", file_name);
                }
            } else {
                LOG_ERROR(WAV, "Open,sample_cnt,Err");
            }
        } else {
            LOG_ERROR(WAV, "Open,SampleArray,Err");
        }
    } else {
        LOG_ERROR(WAV, "Open,Header,Err");
    }
    return res;
}

bool wav_proc_iir_sample(const char* const file_name, uint8_t iir_num) {
    bool res = false;
    LOG_DEBUG(WAV, "Proc,Sample,File:[%s],IIR:%u", file_name, iir_num);
    if(file_name) {
        res = file_mcal_open_re(FILE_MCAL_READ, file_name);
        if(res) {
            LOG_DEBUG(WAV, "OpenFile:[%s]Ok", file_name);
            WavHeader_t WavHeader = {0};
            uint32_t real_read = file_mcal_read(FILE_MCAL_READ, WavHeader.buff, sizeof(WavHeader_t));
            if(sizeof(WavHeader_t) == real_read) {
                char text_line[100] = "";
                char file_write_name[80] = {0};
                res = csv_parse_text(file_name, '.', 0, file_write_name, sizeof(file_write_name));
                snprintf(file_write_name, sizeof(file_write_name), "%s_Iir_%u.wav", file_write_name, iir_num);
                res = file_mcal_open_wb(FILE_MCAL_WRITE, file_write_name);
                if(res) {
                    res = file_mcal_write(FILE_MCAL_WRITE, WavHeader.buff, sizeof(WavHeader_t));
                    if(res) {
                        LOG_DEBUG(WAV, "WriteHeaderOk");
                    } else {
                        LOG_ERROR(WAV, "WriteHeaderErr");
                    }
                }
                cli_printf(CRLF);
                LOG_DEBUG(WAV, "ReadOk");
                LOG_DEBUG(WAV, "%s", WavHeaderToStr(&WavHeader));
                uint32_t s = 0;

                WavHandle_t WavHandle = {0};
                WavHandle.sample_time_s = 1.0 / ((double)WavHeader.sampleRate);
                WavHandle.sample_cnt = WavHeader.subchunk2Size / WavHeader.blockAlign;
                WavHandle.duration_s = WavHandle.sample_time_s * ((double)WavHandle.sample_cnt);
                LOG_NOTICE(WAV, "%s", WavNodeToStr(&WavHandle));

                for(s = 0; s < WavHandle.sample_cnt; s++) {
                    double up_time_s = ((double)s) * WavHandle.sample_time_s;
                    WavSample16_t WavSample16 = {0};
                    strcpy(text_line, TSEP);
                    snprintf(text_line, sizeof(text_line), "%s %6u " TSEP, text_line, s);
                    snprintf(text_line, sizeof(text_line), "%s %6.2f " TSEP, text_line, up_time_s);
                    snprintf(text_line, sizeof(text_line), "%s %6.2f " TSEP, text_line,
                             100.0 * up_time_s / WavHandle.duration_s);

                    real_read = file_mcal_read(FILE_MCAL_READ, (uint8_t*)&WavSample16, WavHeader.blockAlign);
                    if(WavHeader.blockAlign == real_read) {
                        snprintf(text_line, sizeof(text_line), "%s %6d " TSEP, text_line, WavSample16.left);
                        snprintf(text_line, sizeof(text_line), "%s %6d " TSEP, text_line, WavSample16.right);
#ifdef HAS_IIR
                        int16_t sample_common = (WavSample16.left / 2) + (WavSample16.right / 2);
                        IirSample_t iirOutSample = 0;
                        res = iir_proc_in_out(iir_num, (IirSample_t)sample_common, &iirOutSample);
                        if(res) {
                            snprintf(text_line, sizeof(text_line), "%s %6.0f " TSEP, text_line, iirOutSample);
                            WavSample16_t WavSample16Wr = {
                                .left = (int16_t)iirOutSample,
                                .right = (int16_t)iirOutSample,
                            };
                            res = file_mcal_write(FILE_MCAL_WRITE, (uint8_t*)&WavSample16Wr, sizeof(WavSample16_t));
                            if(res) {
                                LOG_DEBUG(WAV, "WriteOk:%u", s);
                            } else {
                                LOG_ERROR(WAV, "WriteErr:%u", s);
                            }
                        } else {
                            LOG_ERROR(WAV, "FirProcErr:%u", s);
                        }
#endif
                    } else {
                        res = false;
                        LOG_ERROR(WAV, "readDataErr:%u", real_read);
                    }
                    if(0 == (s % (WavHandle.sample_cnt / 100))) {
                        cli_printf("\r%s", text_line);
                    }
                }
                res = true;
            } else {
                LOG_ERROR(WAV, "readErr");
            }

            res = file_mcal_close(FILE_MCAL_WRITE);
            res = file_mcal_close(FILE_MCAL_READ);
        } else {
            LOG_ERROR(WAV, "OpenFile:[%s] Err", file_name);
        }
    }
    return res;
}

#ifdef HAS_FIR
static bool wav_proc_fir_sample_ll(WavSample16_t WavSample16, uint8_t fir_num, uint32_t file_id, uint32_t s) {
    bool res = false;
    int16_t sample_common = (WavSample16.left / 2) + (WavSample16.right / 2);
    FirSample_t firOutSample = 0;
    res = fir_proc_in_out(fir_num, (FirSample_t)sample_common, &firOutSample);
    if(res) {
        WavSample16_t WavSample16Wr = {
            .left = (int16_t)firOutSample,
            .right = (int16_t)firOutSample,
        };
        res = file_mcal_write(file_id, (uint8_t*)&WavSample16Wr, sizeof(WavSample16_t));
        if(res) {
            res = true;
            LOG_DEBUG(WAV, "WriteOk,Sam:%u", s);
        } else {
            LOG_ERROR(WAV, "WriteErr,Sam:%u", s);
        }
    } else {
        LOG_ERROR(WAV, "FirProcErr:%u", s);
    }
    return res;
}
#endif

#ifdef HAS_FILE_PC
bool wav_load(uint8_t wav_num, const char* const file_name) {
    bool res = false;
    LOG_WARNING(WAV, "WAV_%u,LoadFile:[%s]", wav_num, file_name);
    WavHandle_t* Node = WavGetNode(wav_num);
    if(Node) {
        Node->real_file_size = file_pc_get_size(file_name);
        if((sizeof(WavHeader_t) + 1) < Node->real_file_size) {
            FILE* pFileRead = NULL;
            pFileRead = fopen(file_name, "rb");
            if(pFileRead) {
                LOG_DEBUG(WAV, "OpenFile:[%s]Ok", file_name);
                WavHeader_t WavHeader = {0};
                size_t real_read = fread((void*)&WavHeader, sizeof(WavHeader_t), 1, pFileRead);
                if(1 == real_read) {
                    LOG_DEBUG(WAV, "ReadHeaderOk,%s", WavHeaderToStr(&WavHeader));
                    res = WavHeaderToNode(&WavHeader, Node);
                    Node->real_data_size = Node->real_file_size - sizeof(WavHeader_t);
                    Node->sample_cnt = Node->real_data_size / WavHeader.blockAlign;
                    LOG_NOTICE(WAV, "%s", WavNodeToStr(Node));
                    Node->data_diff_size = ((int32_t)Node->real_data_size) - ((int32_t)WavHeader.subchunk2Size);

                    if(0 != Node->data_diff_size) {
                        if (Node->data_diff_size<0) {
                            LOG_ERROR(WAV, "DataDiff:[%d]RealSizeLessThanInWavHeader", Node->data_diff_size);
                        } else {
                            LOG_ERROR(WAV, "DataDiff:[%d]RealSizeMoreThanInWavHeader", Node->data_diff_size);
                        }
                    }

                    Node->data = (uint8_t*)malloc(Node->real_data_size);
                    if(Node->data) {
                        LOG_DEBUG(WAV, "MallocOk,%u", Node->real_data_size);

                        memset(Node->data, 0, Node->real_data_size);
                        real_read = fread((void*)Node->data, Node->real_data_size, 1, pFileRead);
                        LOG_DEBUG(WAV, "realRead:%u", real_read);
                        if(1 == real_read) {
                            LOG_DEBUG(WAV, "Read:%u Byte,Ok", Node->real_data_size);
                            res = true;
                        } else {
                            res = false;
                            LOG_ERROR(WAV, "WAV_%u,%s,ReadErr:%u byte", wav_num, file_name, Node->real_data_size);
                        }
                    } else {
                        res = false;
                        LOG_ERROR(WAV, "MallocErr:%u byte", WavHeader.subchunk2Size);
                    }

#if 0
                Node->data = (int16_t*)malloc(sizeof(int16_t)*Node->sample_cnt);
                if(Node->data) {
                    for(s=0;s<Node->sample_cnt;s++) {
                        AudioStereoSample16bit_t StereoSample;
                        real_read = fread((void*)StereoSample.buff, WavHeader.blockAlign,1, pFileRead);
                        if(1==real_read ) {
                            Node->data[s] = StereoSample.right;
                            res = true;
                        }
                    }
                } else {
                    res = false;
                    LOG_ERROR(WAV, "MallocErr:%u byte", WavHeader.subchunk2Size);
                }
#endif
                } else {
                    res = false;
                    LOG_ERROR(WAV, "ReadErr:%s", file_name);
                }
                fclose(pFileRead);
            } else {
                res = false;
                LOG_ERROR(WAV, "OpenErr:%s", file_name);
            }
        } else {
            LOG_ERROR(WAV, "WAV_%u,WavFileSizeError:%u", wav_num);
        }
    } else {
        LOG_ERROR(WAV, "WAV_%u,NodeError:%u", wav_num);
    }
    return res;
}
#endif

bool wav_proc_fir_sample(const char* const file_name, uint8_t fir_num) {
    bool res = false;
    LOG_DEBUG(WAV, "Proc,Sample,File:[%s],FIR:%u", file_name, fir_num);
    if(file_name) {
        res = file_mcal_open_re(FILE_MCAL_READ, file_name);
        if(res) {
            LOG_DEBUG(WAV, "OpenFile:[%s]Ok", file_name);
            WavHeader_t WavHeader = {0};
            uint32_t real_read = file_mcal_read(FILE_MCAL_READ, WavHeader.buff, sizeof(WavHeader_t));
            if(sizeof(WavHeader_t) == real_read) {
                LOG_DEBUG(WAV, "ReadHeaderOk,%s", WavHeaderToStr(&WavHeader));
                char text_line[100] = "";
                char file_write_name[80] = {0};
                snprintf(file_write_name, sizeof(file_write_name), "Fir%u.wav", fir_num);
                res = file_mcal_open_wb(FILE_MCAL_WRITE, file_write_name);
                if(res) {
                    res = file_mcal_write(FILE_MCAL_WRITE, WavHeader.buff, sizeof(WavHeader_t));
                    if(res) {
                        LOG_DEBUG(WAV, "WriteHeaderOk");
                    } else {
                        LOG_ERROR(WAV, "WriteHeaderErr");
                    }
                }
                cli_printf(CRLF);
                uint32_t s = 0;

                WavHandle_t WavHandle = {0};
                WavHandle.sample_time_s = 1.0 / ((double)WavHeader.sampleRate);
                WavHandle.sample_cnt = WavHeader.subchunk2Size / WavHeader.blockAlign;
                WavHandle.duration_s = WavHandle.sample_time_s * ((double)WavHandle.sample_cnt);
                LOG_NOTICE(WAV, "%s", WavNodeToStr(&WavHandle));

                for(s = 0; s < WavHandle.sample_cnt; s++) {
                    double up_time_s = ((double)s) * WavHandle.sample_time_s;
                    WavSample16_t WavSample16 = {0};
                    strcpy(text_line, TSEP);
                    snprintf(text_line, sizeof(text_line), "%s %6u " TSEP, text_line, s);
                    snprintf(text_line, sizeof(text_line), "%s %6.2f " TSEP, text_line, up_time_s);
                    snprintf(text_line, sizeof(text_line), "%s %6.2f " TSEP, text_line,
                             100.0 * up_time_s / WavHandle.duration_s);
                    //       real_read = fread((void*) &WavSample16, WavHeader.blockAlign, 1, pFileRead);
                    real_read = file_mcal_read(FILE_MCAL_READ, (uint8_t*)&WavSample16, WavHeader.blockAlign);
                    if(1 == real_read) {
                        snprintf(text_line, sizeof(text_line), "%s %6d " TSEP, text_line, WavSample16.left);
                        snprintf(text_line, sizeof(text_line), "%s %6d " TSEP, text_line, WavSample16.right);
#ifdef HAS_FIR
                        res = wav_proc_fir_sample_ll(WavSample16, fir_num, FILE_MCAL_READ, s);
#endif
                    } else {
                        res = false;
                        LOG_ERROR(WAV, "readDataErr:%u", real_read);
                    }
                    if(0 == (s % (WavHandle.sample_cnt / 100))) {
                        cli_printf("\r%s", text_line);
                    }
                }
                res = true;
            } else {
                LOG_ERROR(WAV, "readErr");
            }
            res = file_mcal_close(FILE_MCAL_WRITE);
            res = file_mcal_close(FILE_MCAL_READ);
        } else {
            LOG_ERROR(WAV, "OpenFile:[%s] Err", file_name);
        }
    }
    return res;
}

float wav_duration_get(uint8_t num) {
    float duratuin_s = -1.0f;
    WavHandle_t* Node = WavGetNode(num);
    if(Node) {
        duratuin_s = Node->duration_s;
    }
    return duratuin_s;
}

bool wav_duration_set(uint8_t num, float duratuin_s) {
    bool res = false;
    WavHandle_t* Node = WavGetNode(num);
    if(Node) {
        LOG_NOTICE(WAV, "WAV_%u,Set,Duration:%f s", num, duratuin_s);
        Node->duration_s = duratuin_s;
        res = true;
    }
    return res;
}

bool wav_generate(uint8_t num, char* name, uint8_t dds_num) {
    bool res = false;
    WavHandle_t* Node = WavGetNode(num);
    if(Node) {
        LOG_NOTICE(WAV, "GenerateSound:N:%u,File:[%s],DDS%u", num, name, dds_num);
        strcpy(Node->fileName, name);

        switch(Node->channels) {
        case 1: {
            res = wav_generate_1_channel(num, dds_num);
            log_res(DDS, res, "wavGenerateMonoOneChannel");
        } break;

        case 2: {
            res = wav_generate_2_channel(num, dds_num, dds_num, Node->duration_s);
            log_res(DDS, res, "wavGenerateMonoTwoChannel");
        } break;

        default: {
            res = wav_generate_2_channel(num, dds_num, dds_num, Node->duration_s);
            log_res(DDS, res, "wavGenerateMonoTwoChannel");
            res = false;
        } break;
        }
#if 0
        WavHeader_t WavHeader = {0};
        DdsHandle_t* DDs = DdsGetNode(  dds_num);
        if(DDs) {
            res = wav_compose_header_by_dds(DDs, &WavHeader);
            if(res) {
                res = wav_calc_samples(Node);
                res = wav_samples_save(&WavHeader,
                                       DDs->sample_array,
                                       DDs->sample_cnt,
                                       1);
                log_res(DDS,res,"WavSamplsSave");
            }else {
                LOG_ERROR(WAV, "GenHeaderErr");
            }
        }else {
            LOG_ERROR(WAV, "DdsNodeErr");
        }
#endif
    } else {
        LOG_ERROR(WAV, "NodeErr");
    }
    return res;
}

bool wav_dds_to_name(char* const name, const uint32_t size, const uint8_t dds_num, const char* const prefix) {
    bool res = false;
    if(name) {
        if(size) {
            DdsHandle_t* Dds = DdsGetNode(dds_num);
            if(Dds) {
                memset(name, 0, size);
                float signal_diration_ms = ceilf(SEC_2_MSEC(Dds->signal_diration_s));
                snprintf(name, size, "%s%s_", name, prefix);
                snprintf(name, size, "%s%s_", name, DdsModeToStr(Dds->dds_mode));
                snprintf(name, size, "%sA%u_", name, (uint32_t)Dds->amplitude);
                snprintf(name, size, "%sFstart%uHz_", name, (uint32_t)(Dds->frequency));

                switch(Dds->dds_mode) {
                case DDS_MODE_SIN: {
                } break;

                case DDS_MODE_M_SEQ: {
                    snprintf(name, size, "%sMs_%u_", name, (uint32_t)(Dds->m_seq_num));
                    //snprintf(name, size, "%sCAR_%u_", name, (uint32_t)(Dds->frequency));
                    snprintf(name, size, "%sPerPchip%u_", name, (uint32_t)(Dds->periods_per_chip));
                } break;

                case DDS_MODE_BARKER_13: {
                    //snprintf(name, size, "%sCAR_%u_", name, (uint32_t)(Dds->frequency));
                    snprintf(name, size, "%sPerPchip%u_", name, (uint32_t)(Dds->periods_per_chip));
                } break;

                case DDS_MODE_CHIRP_SYMMETRIC:
                case DDS_MODE_CHIRP: {
                    snprintf(name, size, "%sFend%uHz_", name, (uint32_t)(Dds->frequency2));
                } break;
                default:
                    break;
                }
                snprintf(name, size, "%sdt%u", name, (uint32_t)signal_diration_ms);
                snprintf(name, size, "%s.wav", name);
                res = true;
            }
        }
    }
    return res;
}

bool wav_generate_signal(const uint8_t num, const uint8_t dds_num, char* prefix) {
    bool res = false;
    char name[80] = {0};
    wav_dds_to_name(name, sizeof(name), dds_num, prefix);
    res = wav_generate(num, name, dds_num);
    return res;
}

static bool wav_compose_header(WavHeader_t* const Header, uint32_t chan_cnt, uint32_t sample_bitness,
                               uint32_t sample_per_second, uint32_t sample_cnt) {
    bool res = false;
    if(Header) {
        uint32_t byte_per_sample = (sample_bitness / 8) * chan_cnt;
        uint32_t data_size = chan_cnt * sample_cnt * (sample_bitness / 8);
        Header->chunkId = reverse_byte_order_uint32(WAV_RIFF);                /*RIFF*/
        Header->chunkSize = data_size + sizeof(WavHeader_t) - 8;              /**/
        Header->format = reverse_byte_order_uint32(WAV_WAVE);                 /*WAVE*/
        Header->subchunk1Id = reverse_byte_order_uint32(WAV_SECTION_ID_FMT);  /*fmt */
        Header->subchunk1Size = WAV_SECTION_FMT_SIZE;                         /**/
        Header->audioFormat = WAVE_COMPRESSION_CODE_PCM;                      /*PCM*/
        Header->numChannels = chan_cnt;                                       /**/
        Header->sampleRate = sample_per_second;                               /**/
        Header->aver_bytes_per_sec = byte_per_sample * sample_per_second;     /**/
        Header->blockAlign = byte_per_sample;                                 /**/
        Header->bitsPerSample = sample_bitness;                               /**/
        Header->subchunk2Id = reverse_byte_order_uint32(WAV_SECTION_ID_DATA); /*data*/
        Header->subchunk2Size = data_size;                                    /**/
        LOG_NOTICE(WAV, "%s", WavHeaderToStr(Header));
        res = true;
    }
    return res;
}

bool wav_generate_2_channel(uint8_t wav_num, uint8_t dds1_num, uint8_t dds2_num, float duration_s) {
    bool res = false;
    LOG_INFO(WAV, "Generate2CHfile,WAV%u,DDS%u,DDS%u,Duration:%f s", wav_num, dds1_num, dds2_num, duration_s);
    WavHandle_t* Wav = WavGetNode(wav_num);
    if(Wav) {
        LOG_NOTICE(WAV, "%s", WavNodeToStr(Wav));
        DdsHandle_t* Dds1 = DdsGetNode(dds1_num);
        if(Dds1) {
            LOG_NOTICE(WAV, "DDS1,%s", DdsNodeToStr(Dds1));
            DdsHandle_t* Dds2 = DdsGetNode(dds2_num);
            if(Dds2) {
                LOG_NOTICE(WAV, "DDS2,%s", DdsNodeToStr(Dds2));
                WavHeader_t WavHeader = {0};
                float sample_duration_s = 1.0f / ((float)Wav->sampling_frequency_hz);
                uint32_t sample_cnt = duration_s / sample_duration_s;
                LOG_NOTICE(WAV, "SampleCnt:%u Sam Duration:%f s Sam:%f s", sample_cnt, duration_s, sample_duration_s);

                if(sample_cnt) {
                    res = wav_compose_header(&WavHeader, 2, 16, Wav->sampling_frequency_hz, sample_cnt);

                    res = file_mcal_open_wb(Wav->file_num, Wav->fileName);
                    if(res) {
                        uint32_t ok_cnt = 0;
                        LOG_DEBUG(WAV, "Write,Header,Ok,Sample:%u", sample_cnt);
                        // TODO change to file_mcal_write()
                        // size_t write_cnt = fwrite((void*) &WavHeader, sizeof(WavHeader_t), 1, pFileWrite);
                        res = file_mcal_write(Wav->file_num, WavHeader.buff, sizeof(WavHeader_t));
                        if(res) {
                            uint32_t s = 0;
                            for(s = 0; s < sample_cnt; s++) {
                                float up_time_s = ((float)s) * sample_duration_s;
                                AudioStereoSample16bit_t Sample16bit = {0};
                                Sample16bit.left  = dds_calc_sample_s16(up_time_s, Dds1);
                                Sample16bit.right = dds_calc_sample_s16(up_time_s, Dds2);

                                res = file_mcal_write(Wav->file_num, (uint8_t*)&Sample16bit,
                                                      sizeof(AudioStereoSample16bit_t));

                                // write_cnt = fwrite((void*) &Sample16bit, sizeof(AudioStereoSample16bit_t), 1,
                                // pFileWrite);
                                if(res) {
                                    res = true;
                                    ok_cnt++;
                                    LOG_DEBUG(WAV, "UpTime:%f s,Write,Sample:%u/%u,Sam:%s,Ok", up_time_s, s, sample_cnt,
                                              AudioStereoSample16bitToStr(&Sample16bit));
                                } else {
                                    LOG_ERROR(WAV, "Write,Sample:%u,Err", s);
                                }
                            }
                        } else {
                            LOG_ERROR(WAV, "Err,WavHeaderWrite");
                            res = false;
                        }

                        res = file_mcal_close(Wav->file_num);

                        if(ok_cnt == sample_cnt) {
                            res = true;
                        } else {
                            LOG_ERROR(WAV, "WriteData,Err OkCnt:%u!=SamCnt:%u", ok_cnt, sample_cnt);
                            res = false;
                        }
                    } else {
                        LOG_ERROR(WAV, "OpenFile:[%s],Err", Wav->fileName);
                        res = false;
                    }

                } else {
                    LOG_ERROR(WAV, "ZeroSamCnt,Err");
                    res = false;
                }

            } else {
                LOG_ERROR(WAV, "DDS1,Err");
                res = false;
            }
        } else {
            LOG_ERROR(WAV, "Node,Err");
            res = false;
        }
    }
    return res;
}

bool wav_sampling_frequency_set(uint8_t num, uint32_t sampling_frequency_hz) {
    bool res = false;
    WavHandle_t* Node = WavGetNode(num);
    if(Node) {
        LOG_NOTICE(WAV, "WAV_%u,Set,SampleFreq:%u Hz", num, sampling_frequency_hz);
        Node->sampling_frequency_hz = sampling_frequency_hz;
        res = true;
    }
    return res;
}

uint32_t wav_sampling_frequency_get(uint8_t num) {
    uint32_t sampling_frequency_hz = 0xFFFFFFFF;
    WavHandle_t* Node = WavGetNode(num);
    if(Node) {
        sampling_frequency_hz = Node->sampling_frequency_hz;
    }
    return sampling_frequency_hz;
}

bool wav_generate_1_channel(uint8_t num, uint8_t dds1_num) {
    bool res = false;
    WavHandle_t* Node = WavGetNode(num);
    if(Node) {
        res = wav_generate_2_channel(num, dds1_num, dds1_num, Node->duration_s);
    }
    return res;
}

bool wav_init_one(uint8_t num) {
    bool res = false;
    LOG_DEBUG(WAV, "Init:%u", num);
    const WavConfig_t* Config = WavGetConfig(num);
    if(Config) {
        WavHandle_t* Node = WavGetNode(num);
        if(Node) {
            res = wav_init_common(Config, Node);
            res = true;
        }
    }
    return res;
}

#ifdef HAS_PC
bool wav_shift_right_sample_pc(const char* const file_name, uint32_t samples) {
    bool res = false;
    LOG_WARNING(WAV, "ShiftRight,File:[%s],Offset:%u Sam", file_name, samples);
    FILE* pFileOld;
    char new_file_name[80] = {0};
    snprintf(new_file_name, sizeof(new_file_name), "out_shift.wav");
    pFileOld = fopen(file_name, "rb");
    if(pFileOld) {
        LOG_DEBUG(WAV, "OpenFile:[%s] Ok", file_name);
        uint32_t real_read = 0;
        WavHeader_t OldHeader = {0};
        real_read = fread((void*)OldHeader.buff, sizeof(WavHeader_t), 1, pFileOld);
        if(real_read) {
            res = wav_is_valid_header(&OldHeader);
            if(res) {
                LOG_DEBUG(WAV, "ReadHeader:%s,Ok", file_name);
                uint32_t bytes_per_frame = WavHeaderToFrameSize(&OldHeader);
                uint32_t zero_mem_size = samples * bytes_per_frame;
                LOG_DEBUG(WAV, "zero_mem_size:%u Byte", zero_mem_size);

                FILE* pFileNew;
                pFileNew = fopen(new_file_name, "wb");
                if(pFileNew) {
                    LOG_DEBUG(WAV, "OpenNew [%s] Ok", new_file_name);
                    WavHeader_t NewHeader = {0};
                    memcpy(NewHeader.buff, OldHeader.buff, sizeof(WavHeader_t));
                    size_t write_cnt = fwrite((void*)NewHeader.buff, sizeof(WavHeader_t), 1, pFileNew);
                    if(write_cnt) {
                        log_info_res(WAV, res, "WriteNewHeader");

                        uint32_t i = 0;
                        for(i = 0; i < zero_mem_size;) {
                            uint8_t data[32] = {0};
                            memset(data, 0, sizeof(data));
                            write_cnt = fwrite((void*)data, sizeof(data), 1, pFileNew);
                            if(write_cnt) {
                                i += sizeof(data);
                            }
                        }

                        uint32_t rest = OldHeader.subchunk2Size - zero_mem_size;
                        LOG_DEBUG(WAV, "rest:%u Byte", rest);
                        for(i = 0; i < rest;) {
                            uint8_t data[32] = {0};
                            memset(data, 0, sizeof(data));
                            uint32_t read_size = 0;
                            real_read = fread((void*)data, sizeof(data), 1, pFileOld);
                            if(real_read) {
                                LOG_DEBUG(WAV, "Written:%u Byte", read_size);
                                write_cnt = fwrite((void*)data, sizeof(data), 1, pFileNew);
                                if(write_cnt) {
                                    i += sizeof(data);
                                } else {
                                    break;
                                }
                            } else {
                                break;
                            }
                        }
                    }

                    fclose(pFileNew);
                    pFileNew = NULL;
                }
            }
        }
        fclose(pFileOld);
        pFileOld = NULL;
    }
    return res;
}
#endif

bool wav_file_name_set(uint32_t num,
                       const char* const new_file_name) {
    bool res = false;
    WavHandle_t *Node = WavGetNode(num);
    if (Node) {
        strcpy(Node->fileName, new_file_name);
        LOG_INFO(WAV, "newFileName:[%s]", new_file_name);
        res = true;
    }
    return res;
}

bool wav_shift_right_sample(const char* const file_name, const char* const new_file_name, uint32_t samples) {
    bool res = false;

    if(samples) {
        WavHandle_t* WavOld = WavGetNode(WAV_NUM_READ);
        WavHandle_t* WavNew = WavGetNode(WAV_NUM_WRITE);

        wav_file_name_set(WAV_NUM_WRITE, new_file_name);

        LOG_WARNING(WAV, "ShiftRight,File:[%s],Offset:%u Sam", file_name, samples);
        res = file_mcal_open_re(WavOld->file_num, file_name);
        if(res) {
            LOG_DEBUG(WAV, "OpenFile:[%s] Ok", file_name);
            WavHeader_t OldHeader = {0};
            uint32_t real_read = 0;
            real_read = file_mcal_read(WavOld->file_num, OldHeader.buff, sizeof(WavHeader_t));
            if(real_read) {
                res = wav_is_valid_header(&OldHeader);
                if(res) {
                    LOG_DEBUG(WAV, "ReadHeader:%s,Ok", file_name);
                    uint32_t bytes_per_frame = WavHeaderToFrameSize(&OldHeader);
                    uint32_t zero_mem_size = samples * bytes_per_frame;
                    LOG_DEBUG(WAV, "zero_mem_size:%u Byte", zero_mem_size);

                    res = file_mcal_open_wb(WavNew->file_num, WavNew->fileName);
                    if(res) {
                        LOG_DEBUG(WAV, "OpenNew [%s] Ok", WavNew->fileName);
                        WavHeader_t NewHeader = {0};
                        memcpy(NewHeader.buff, OldHeader.buff, sizeof(WavHeader_t));
                        res = file_mcal_write(WavNew->file_num, NewHeader.buff, sizeof(WavHeader_t));
                        if(res) {
                            log_info_res(WAV, res, "WriteNewHeader");
                            LOG_NOTICE(WAV, "WriteZeros:%u", zero_mem_size);
                            // log_level_set(FILE_MCAL, LOG_LEVEL_DEBUG);
                            uint32_t i = 0;
                            for(i = 0; i < zero_mem_size;) {
                                uint8_t zeros[128] = {0};
                                memset(zeros, 0, sizeof(zeros));
                                res = file_mcal_write(WavNew->file_num, zeros, sizeof(zeros));
                                if(res) {
                                    i += sizeof(zeros);
                                } else {
                                    LOG_ERROR(WAV, "WriteZero:%u Byte", sizeof(zeros));
                                }
                            }

                            // log_level_set(FILE_MCAL, LOG_LEVEL_INFO);
                            uint32_t rest = OldHeader.subchunk2Size - zero_mem_size;
                            LOG_NOTICE(WAV, "rest:%u Byte", rest);
                            for(i = 0; i < rest;) {
                                uint8_t data[128] = {0};
                                memset(data, 0, sizeof(data));
                                real_read = file_mcal_read(WavOld->file_num, data, sizeof(data));
                                if(real_read) {
                                    res = file_mcal_write(WavNew->file_num, data, sizeof(data));
                                    if(res) {
                                        LOG_DEBUG(WAV, "Written:%u Byte", sizeof(data));
                                        i += sizeof(data);
                                    } else {
                                        break;
                                    }
                                } else {
                                    break;
                                }
                            }
                            res = file_mcal_close(WavNew->file_num);
                            log_info_res(WAV, res, "CloseNew");
                        }
                    }
                }
                res = file_mcal_close(WavOld->file_num);
                log_info_res(WAV, res, "CloseOld");
            }
        }
    } else {
        LOG_ERROR(WAV, "ZeroShift");
    }
    return res;
}

COMPONENT_INIT_PATTERT(WAV, WAV, wav)
