#include "wav.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "audio_types.h"
#include "code_generator.h"
#include "csv.h"
#include "log.h"
#include "table_utils.h"
#include "byte_utils.h"
#include "dds_drv.h"
#include "writer_config.h"
#include "file_mcal.h"

#ifdef HAS_FIR
#include "fir.h"
#endif

#ifdef HAS_IIR
#include "iir.h"
#endif

// https://audiocoding.cc/articles/2008-05-22-wav-file-structure/

COMPONENT_GET_NODE(Wav, wav)
COMPONENT_GET_CONFIG(Wav, wav)

bool wav_compose_header_by_dds(DdsHandle_t* const DDs,
                               WavHeader_t* const Header) {
    bool res = false;
    if(DDs) {
        LOG_INFO(WAV, "%s", DdsNodeToStr(DDs));
        if(Header) {
            uint32_t chan_cnt =  DdsFramePatToNumChann(DDs->frame_pattern);
            uint32_t byte_per_sample = (DDs->sample_bitness/8)*chan_cnt;
            uint32_t data_size =  DDs->sample_cnt*(DDs->sample_bitness/8);

            Header->chunkId= reverse_byte_order_uint32(0x52494646); /*RIFF*/
            Header->chunkSize =data_size+sizeof(WavHeader_t)-8; /**/
            Header->format = reverse_byte_order_uint32(0x57415645); /*WAVE*/
            Header->subchunk1Id = reverse_byte_order_uint32(0x666d7420); /*fmt */
            Header->subchunk1Size = 16 ; /**/
            Header->audioFormat = WAVE_FORMAT_PCM ; /*PCM*/
            Header->numChannels = chan_cnt; /**/
            Header->sampleRate = DDs->sample_per_second; /**/
            Header->byteRate = byte_per_sample* DDs->sample_per_second; /**/
            Header->blockAlign = byte_per_sample; /**/
            Header->bitsPerSample = DDs->sample_bitness; /**/
            Header->subchunk2Id = reverse_byte_order_uint32(0x64617461); /*data*/
            Header->subchunk2Size =  DDs->sample_cnt*(DDs->sample_bitness/8); /**/
            LOG_INFO(WAV, "%s",WavHeaderToStr(Header));
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
    if (file_name) {
        //FILE* pFileRead = NULL;
        //pFileRead = fopen(file_name, "rb");
        res = file_mcal_open_re(1, file_name);
        if (res) {
            LOG_INFO(WAV, "OpenFile:[%s]Ok", file_name);
            uint32_t real_read = 0;
            //real_read = fread((void*)Header, 1, sizeof(WavHeader_t), pFileRead);
            res = file_mcal_read(1, file_name, (uint8_t*) Header, sizeof(WavHeader_t), &real_read);
            if (res) {
                if (sizeof(WavHeader_t) == real_read) {
                    LOG_INFO(WAV, "Read,Ok");
                    LOG_INFO(WAV, "%s", WavHeaderToStr(Header));
                    WavHandle_t WavHandle = { 0 };
                    WavHandle.sample_time_s = 1.0 / ((float) Header->sampleRate);
                    WavHandle.sample_cnt = Header->subchunk2Size / Header->blockAlign;
                    WavHandle.duration_s = WavHandle.sample_time_s * ((float) WavHandle.sample_cnt);
                    LOG_INFO(WAV, "%s", WavHandleToStr(&WavHandle));
                    res = true;
                }
            }

            res = file_mcal_close(1);
            //fclose(pFileRead);
        } else {
            LOG_ERROR(WAV, "OpenFile:[%s] Err", file_name);
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

bool wav_info_sample(const char* const file_name) {
    bool res = false;
    if(file_name) {
        FILE* pFileRead = NULL;
        pFileRead = fopen(file_name, "rb");
        if(pFileRead) {
            LOG_INFO(WAV, "OpenFile:[%s]Ok", file_name);
            WavHeader_t WavHeader = {0};
            size_t real_read = fread((void*)&WavHeader, sizeof(WavHeader_t), 1, pFileRead);
            if(1 == real_read) {
                LOG_INFO(WAV, "ReadOk");
                LOG_INFO(WAV, "%s", WavHeaderToStr(&WavHeader));
                cli_printf(CRLF);
                uint32_t s = 0;

                WavHandle_t WavHandle = {0};
                WavHandle.sample_time_s = 1.0 / ((double)WavHeader.sampleRate);
                WavHandle.sample_cnt = WavHeader.subchunk2Size / WavHeader.blockAlign;
                WavHandle.duration_s = WavHandle.sample_time_s * ((double)WavHandle.sample_cnt);
                LOG_INFO(WAV, "%s", WavHandleToStr(&WavHandle));

                static const table_col_t cols[] = {
                    {8, "sam"}, {8, "time"}, {8, "prog"}, {8, "left"}, {8, "right"},
                };
                table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

                for(s = 0; s < WavHandle.sample_cnt; s++) {
                    double t_s = ((double)s) * WavHandle.sample_time_s;
                    WavSample16_t WavSample16 = {0};
                    cli_printf(TSEP);
                    cli_printf(" %6u " TSEP, s);
                    cli_printf(" %6.2f " TSEP, t_s);
                    cli_printf(" %6.2f " TSEP, 100.0 * t_s / WavHandle.duration_s);
                    real_read = fread((void*)&WavSample16, WavHeader.blockAlign, 1, pFileRead);
                    if(1 == real_read) {
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

            fclose(pFileRead);
        } else {
            LOG_ERROR(WAV, "OpenFile:[%s] Err", file_name);
        }
    }
    return res;
}

bool wav_samples_save(const WavHeader_t* const Header,
                      const SampleType_t* const SampleArray,
                      const uint32_t sample_cnt,
                      uint32_t repetitions) {
    bool res = false;
    if(Header) {
        LOG_INFO(WAV, "Save,Samples:%s", WavHeaderToStr(Header));
        if(SampleArray) {
            if(sample_cnt) {
                char file_name[300] = {0};
                res = WavHeaderToFileName(Header, file_name, sizeof(file_name));
                FILE* pFileWrite = fopen(file_name, "wb");
                if(pFileWrite) {
                    size_t write_cnt = fwrite((void*)Header, sizeof(WavHeader_t), 1, pFileWrite);
                    if(write_cnt) {
                        LOG_DEBUG(WAV, "Write,Header,Ok");
                        uint32_t r = 0;
                        for(r = 0; r < repetitions; r++) {
                            write_cnt = fwrite((void*)SampleArray, sizeof(SampleType_t), sample_cnt, pFileWrite);
                            if(write_cnt == sample_cnt) {
                                res = true;
                                LOG_DEBUG(WAV, "Write,Data%u,Ok", r);
                            } else {
                                LOG_ERROR(WAV, "Write,Data,Err");
                            }
                        }
                    } else {
                        LOG_ERROR(WAV, "Write,Header,Err");
                    }
                    fclose(pFileWrite);
                } else {
                    LOG_ERROR(WAV, "Open,File:[%s],Err",file_name);
                }
            }else {
                LOG_ERROR(WAV, "Open,sample_cnt,Err");
            }
        }else {
            LOG_ERROR(WAV, "Open,SampleArray,Err");
        }
    }else {
        LOG_ERROR(WAV, "Open,Header,Err");
    }
    return res;
}

bool wav_proc_iir_sample(const char* const file_name, uint8_t iir_num) {
    bool res = false;
    LOG_INFO(WAV, "Proc,Sample,File:[%s],IIR:%u", file_name, iir_num);
    if(file_name) {
        FILE* pFileRead = NULL;
        pFileRead = fopen(file_name, "rb");
        if(pFileRead) {
            FILE* pFileWrite = NULL;
            LOG_INFO(WAV, "OpenFile:[%s]Ok", file_name);
            WavHeader_t WavHeader = {0};
            size_t real_read = fread((void*)&WavHeader, sizeof(WavHeader_t), 1, pFileRead);
            if(1 == real_read) {
                char text_line[100] = "";
                char file_write_name[80] = {0};
                res = csv_parse_text(file_name, '.', 0, file_write_name, sizeof(file_write_name));
                snprintf(file_write_name, sizeof(file_write_name), "%s_Iir_%u.wav", file_write_name, iir_num);
                pFileWrite = fopen(file_write_name, "wb");
                if(pFileWrite) {
                    size_t write_cnt = fwrite((void*)&WavHeader, sizeof(WavHeader_t), 1, pFileWrite);
                    if(write_cnt) {
                        LOG_INFO(WAV, "WriteHeaderOk");
                    } else {
                        LOG_ERROR(WAV, "WriteHeaderErr");
                    }
                }
                cli_printf(CRLF);
                LOG_INFO(WAV, "ReadOk");
                LOG_INFO(WAV, "%s", WavHeaderToStr(&WavHeader));
                uint32_t s = 0;

                WavHandle_t WavHandle = {0};
                WavHandle.sample_time_s = 1.0 / ((double)WavHeader.sampleRate);
                WavHandle.sample_cnt = WavHeader.subchunk2Size / WavHeader.blockAlign;
                WavHandle.duration_s = WavHandle.sample_time_s * ((double)WavHandle.sample_cnt);
                LOG_INFO(WAV, "%s", WavHandleToStr(&WavHandle));
                LOG_INFO(WAV, "%s", WavHandleToStr(&WavHandle));

                for(s = 0; s < WavHandle.sample_cnt; s++) {
                    double t_s = ((double)s) * WavHandle.sample_time_s;
                    WavSample16_t WavSample16 = {0};
                    strcpy(text_line, TSEP);
                    snprintf(text_line, sizeof(text_line), "%s %6u " TSEP, text_line, s);
                    snprintf(text_line, sizeof(text_line), "%s %6.2f " TSEP, text_line, t_s);
                    snprintf(text_line, sizeof(text_line), "%s %6.2f " TSEP, text_line,
                             100.0 * t_s / WavHandle.duration_s);
                    real_read = fread((void*)&WavSample16, WavHeader.blockAlign, 1, pFileRead);
                    if(1 == real_read) {
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
                            size_t write_cnt = fwrite((void*)&WavSample16Wr, sizeof(WavSample16_t), 1, pFileWrite);
                            if(1 == write_cnt) {
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

            fclose(pFileWrite);
            fclose(pFileRead);
        } else {
            LOG_ERROR(WAV, "OpenFile:[%s] Err", file_name);
        }
    }
    return res;
}

#ifdef HAS_FIR
static bool wav_proc_fir_sample_ll(WavSample16_t WavSample16, uint8_t fir_num, FILE* const pFileWrite, uint32_t s) {
    bool res = false;
    int16_t sample_common = (WavSample16.left / 2) + (WavSample16.right / 2);
    FirSample_t firOutSample = 0;
    res = fir_proc_in_out(fir_num, (FirSample_t)sample_common, &firOutSample);
    if(res) {
        WavSample16_t WavSample16Wr = {
            .left = (int16_t)firOutSample,
            .right = (int16_t)firOutSample,
        };
        size_t write_cnt = fwrite((void*)&WavSample16Wr, sizeof(WavSample16_t), 1, pFileWrite);
        if(1 == write_cnt) {
            res = true;
            LOG_DEBUG(WAV, "WriteOk:%u", s);
        } else {
            LOG_ERROR(WAV, "WriteErr:%u", s);
        }
    } else {
        LOG_ERROR(WAV, "FirProcErr:%u", s);
    }
    return res;
}
#endif

bool WavHeaderToNode(const  WavHeader_t* const Header, WavHandle_t* const Node){
    bool res = false;
    if(Header) {
        if(Node) {
            Node->sample_time_s = 1.0 / ((double)Header->sampleRate);
            Node->data_size = (float) Header->subchunk2Size;
            Node->sample_cnt = Header->subchunk2Size / Header->blockAlign;
            Node->duration_s = Node->sample_time_s * ((double)Node->sample_cnt);
            Node->sampling_frequency_hz = (float) Header->sampleRate;
            res = true;
        }
    }
    return res;
}

bool wav_load(uint8_t wav_num, const char* const file_name) {
    bool res = false;
    LOG_WARNING(WAV, "Load");
    WavHandle_t* Node = WavGetNode(wav_num);
    if(Node) {
        FILE* pFileRead = NULL;
        pFileRead = fopen(file_name, "rb");
        if(pFileRead ) {
            LOG_INFO(WAV, "OpenFile:[%s]Ok", file_name);
            WavHeader_t WavHeader = {0};
            size_t real_read = fread((void*)&WavHeader, sizeof(WavHeader_t), 1, pFileRead);
            if(real_read) {
                LOG_INFO(WAV, "ReadHeaderOk,%s", WavHeaderToStr(&WavHeader));
                res = WavHeaderToNode(&WavHeader, Node);
                LOG_INFO(WAV, "%s", WavHandleToStr(Node));
                Node->data = (uint8_t*) malloc(WavHeader.subchunk2Size);
                if(Node->data) {
                    real_read = fread( (void*) Node->data, WavHeader.subchunk2Size, 1, pFileRead);
                    if (real_read == WavHeader.subchunk2Size) {
                        res = true;
                    }
                } else {
                	res = false;
                    LOG_ERROR(WAV, "MallocErr:%u byte", WavHeader.subchunk2Size);
                }
            }else {
            	res = false;
                LOG_ERROR(WAV, "ReadErr:%s", file_name);
            }
        }else{
        	res = false;
            LOG_ERROR(WAV, "OpenErr:%s", file_name);
        }
    }
    return res;
}



bool wav_generate_1_channel(uint8_t wav_num, uint8_t dds1_num) {
    bool res = false;
    return res;
}

bool wav_proc_fir_sample(const char* const file_name, uint8_t fir_num) {
    bool res = false;
    LOG_INFO(WAV, "Proc,Sample,File:[%s],FIR:%u", file_name, fir_num);
    if(file_name) {
        FILE* pFileRead = NULL;
        pFileRead = fopen(file_name, "rb");
        if(pFileRead) {
            FILE* pFileWrite = NULL;
            LOG_INFO(WAV, "OpenFile:[%s]Ok", file_name);
            WavHeader_t WavHeader = {0};
            size_t real_read = fread((void*)&WavHeader, sizeof(WavHeader_t), 1, pFileRead);
            if(1 == real_read) {
                LOG_INFO(WAV, "ReadHeaderOk,%s", WavHeaderToStr(&WavHeader));
                char text_line[100] = "";
                char file_write_name[80] = {0};
                snprintf(file_write_name, sizeof(file_write_name), "Fir%u.wav", fir_num);
                pFileWrite = fopen(file_write_name, "wb");
                if(pFileWrite) {
                    size_t write_cnt = fwrite((void*)&WavHeader, sizeof(WavHeader_t), 1, pFileWrite);
                    if(write_cnt) {
                        LOG_INFO(WAV, "WriteHeaderOk");
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
                LOG_INFO(WAV, "%s", WavHandleToStr(&WavHandle));
                LOG_INFO(WAV, "%s", WavHandleToStr(&WavHandle));

                for(s = 0; s < WavHandle.sample_cnt; s++) {
                    double t_s = ((double)s) * WavHandle.sample_time_s;
                    WavSample16_t WavSample16 = {0};
                    strcpy(text_line, TSEP);
                    snprintf(text_line, sizeof(text_line), "%s %6u " TSEP, text_line, s);
                    snprintf(text_line, sizeof(text_line), "%s %6.2f " TSEP, text_line, t_s);
                    snprintf(text_line, sizeof(text_line), "%s %6.2f " TSEP, text_line,
                             100.0 * t_s / WavHandle.duration_s);
                    real_read = fread((void*)&WavSample16, WavHeader.blockAlign, 1, pFileRead);
                    if(1 == real_read) {
                        snprintf(text_line, sizeof(text_line), "%s %6d " TSEP, text_line, WavSample16.left);
                        snprintf(text_line, sizeof(text_line), "%s %6d " TSEP, text_line, WavSample16.right);
#ifdef HAS_FIR
                        res = wav_proc_fir_sample_ll(WavSample16, fir_num, pFileWrite, s);
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

            fclose(pFileWrite);
            fclose(pFileRead);
        } else {
            LOG_ERROR(WAV, "OpenFile:[%s] Err", file_name);
        }
    }
    return res;
}



bool wav_generate(uint8_t num, uint8_t dds_num) {
    bool res = false;
    WavHandle_t* Node = WavGetNode(num);
    if(Node) {
        switch(Node->channels){
            case 1:{
                res = wav_generate_1_channel(  num,   dds_num);
                log_res(DDS,res,"wavGenerateMono");
            }break;
            case 2:{
                res = wav_generate_2_channel(  num,   dds_num,   dds_num);
                log_res(DDS,res,"wavGenerate2channel");
            }break;
            default:{
                res = wav_generate_2_channel(  num,   dds_num,   dds_num);
                log_res(DDS,res,"wavGenerate2channel");
                res = false;
            }break;
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
    }else {
        LOG_ERROR(WAV, "NodeErr");
    }
    return res;
}

static bool wav_compose_header( WavHeader_t* const Header,
                                uint32_t chan_cnt,
                                uint32_t sample_bitness,
                                uint32_t sample_per_second,
                                uint32_t sample_cnt){
    bool res = false;
    if(Header) {
        uint32_t byte_per_sample =(sample_bitness/8)*chan_cnt;
        uint32_t data_size =  sample_cnt*(sample_bitness/8);
        Header->chunkId= reverse_byte_order_uint32(0x52494646); /*RIFF*/
        Header->chunkSize =data_size+sizeof(WavHeader_t)-8; /**/
        Header->format = reverse_byte_order_uint32(0x57415645); /*WAVE*/
        Header->subchunk1Id = reverse_byte_order_uint32(0x666d7420); /*fmt */
        Header->subchunk1Size = sample_bitness ; /**/
        Header->audioFormat = WAVE_FORMAT_PCM ; /*PCM*/
        Header->numChannels = chan_cnt; /**/
        Header->sampleRate = sample_per_second; /**/
        Header->byteRate = byte_per_sample* sample_per_second; /**/
        Header->blockAlign = byte_per_sample; /**/
        Header->bitsPerSample = sample_bitness; /**/
        Header->subchunk2Id = reverse_byte_order_uint32(0x64617461); /*data*/
        Header->subchunk2Size =  sample_cnt*(sample_bitness/8); /**/
        LOG_INFO(WAV, "%s",WavHeaderToStr(Header));
        res = true;
    }

    return res;
}



bool wav_generate_2_channel(uint8_t wav_num, uint8_t dds1_num, uint8_t dds2_num){
    bool res = false;
    LOG_INFO(WAV, "Generate2CHfile");
    WavHandle_t* Wav = WavGetNode(wav_num);
    if(Wav) {
        DdsHandle_t* Dds1 = DdsGetNode(dds1_num);
        if(Dds1) {
            LOG_INFO(WAV, "DDS1,%s",DdsNodeToStr(Dds1));
            DdsHandle_t* Dds2 = DdsGetNode(dds2_num);
            if(Dds2) {
                LOG_INFO(WAV, "DDS2,%s",DdsNodeToStr(Dds2));
                WavHeader_t WavHeader = {0};
                res = wav_compose_header( &WavHeader, 2, 16, Wav->sampling_frequency_hz, Wav->sample_cnt);
                FILE* pFileWrite = fopen(Wav->file_name, "wb");
                if(pFileWrite) {
                    uint32_t ok_cnt = 0;
                    LOG_INFO(WAV, "Write,Header,Ok");
                    size_t write_cnt = fwrite((void*)&WavHeader, sizeof(WavHeader_t), 1, pFileWrite);
                    if(write_cnt ) {
                        uint32_t s = 0;
                        Wav->sample_cnt = MIN(Dds1->sample_cnt,Dds2->sample_cnt);
                        LOG_INFO(WAV, "SampleCnt:%u Sam", Wav->sample_cnt);
                        for(s=0; s<Wav->sample_cnt; s++) {
                            double t_s = s*(1.0/Wav->sampling_frequency_hz);
                            AudioStereoSample16bit_t Sample16bit = {0};
                            Sample16bit.left = dds_calc_sample_s16(t_s, Dds1);
                            Sample16bit.right= dds_calc_sample_s16(t_s, Dds2);
                            write_cnt = fwrite((void*)&Sample16bit, sizeof(AudioStereoSample16bit_t), 1, pFileWrite);
                            if(write_cnt) {
                                res = true;
                                ok_cnt++;
                                LOG_DEBUG(WAV, "Write,Sample:%u,Ok", s);
                            } else {
                                LOG_ERROR(WAV, "Write,Sample:%u,Err",s);
                            }
                        }
                    }
                    fclose(pFileWrite);

                    if(ok_cnt==Wav->sample_cnt) {
                        if(Wav->sample_cnt) {
                            res = true;
                        }
                    } else {
                        LOG_ERROR(WAV, "WriteData,Err");
                        res = false ;
                    }
                }
            }
        }
    }
    return res;
}

bool wav_init_one(uint8_t num) {
    bool res = false;
    LOG_DEBUG(WAV, "Init:%u", num);
    const WavConfig_t* Config = WavGetConfig(num);
    if(Config) {
        WavHandle_t* Node=WavGetNode(num);
        if(Node) {
            Node->channels = Config->channels;
            Node->file_name = Config->file_name;
            Node->sample_cnt = Config->sample_cnt;
            Node->sampling_frequency_hz = Config->sampling_frequency_hz;
            res = true;
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(WAV, WAV, wav)
