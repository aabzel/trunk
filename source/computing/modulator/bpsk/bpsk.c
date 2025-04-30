#include "bpsk.h"

#include <string.h>

#include "bit_utils.h"
#include "dsp.h"
#include "byte_utils.h"
#include "code_generator.h"
#include "csv.h"
#include "dds_drv.h"
#include "debug_info.h"
#include "quadrature_mixer.h"
#include "decimator.h"
#include "file_pc.h"
#include "fir.h"
#include "log.h"
#ifdef HAS_PID
#include "pid.h"
#endif
#include "time_mcal.h"
#include "utils_math.h"
#include "vector_math.h"
#include "wav.h"

COMPONENT_GET_NODE(Bpsk, bpsk)
COMPONENT_GET_CONFIG(Bpsk, bpsk)

bool bpsk_init_custom(void) {
    bool res = true;
    return res;
}


static double BpskBitValToPhase(bool bit_val){
    double phase = 0.0;
    switch((uint32_t)bit_val) {
        case false: phase = -1.0; break;
        case true: phase = 1.0; break;
        default: phase = 0.0; break;
    }
    return phase;
}

/*
 * Deencode from BPSK sample array
 *
 * x_signal - ADC data with information
 * data - data to encode
 * data_size - data size
 * sample - ADC sample with modulation
 * sample_cnt - sample count
 */


bool bpsk_encode_ll(BpskHandle_t* Node,
                   const uint8_t* const data, uint32_t data_size,
                   SampleType_t* const sample, uint32_t sample_cnt){
    bool res = false;
    if(Node){
        if(data){
            if(data_size){
                if(sample){
                    if(sample_cnt){
                        res = true;
                    }
                }
            }

        }
    }

    if(res) {
        LOG_INFO(BPSK,"Encode,%s", BpskNodeToStr(Node));
        res = false;
        uint32_t bit_cnt = 8*data_size;
        Node->sample_cnt = Node->sample_per_chip*bit_cnt;
        if(Node->sample_cnt < sample_cnt) {
            LOG_INFO(BPSK,"Encode,%u,Sam",Node->sample_cnt );
            Node->samples = sample;
            uint32_t bit = 0;
            uint32_t s = 0;
            for(bit=0; bit < bit_cnt; bit++) {
                // MSB first
                uint32_t byte_num = bit/8;
                uint8_t bit_num = 7-(bit%8);
                bool bit_val = bit_get_u8(data[byte_num], bit_num);
                LOG_DEBUG(BPSK,"Byte:%u,Bit:%u,Val:%u",byte_num,bit_num,bit_val);
                double BinaryPhase = BpskBitValToPhase(bit_val);
                uint32_t chirp = 0;
                for(chirp=0;chirp<Node->sample_per_chip;chirp++) {
                    double time_s = s * Node->sample_time_s;
                    sample[s] = (SampleType_t) (BinaryPhase * math_calc_sin_sample(time_s,(double) Node->carrier_frequency_hz, 0.0, Node->amplitude, 0));
                    s++;
                    res = true;
                }
            }
        } else {
            LOG_ERROR(BPSK,"NotEnoughSamples,Need:%u,Available:%u",Node->sample_cnt,sample_cnt);
        }
    }

    return res;
}

bool bpsk_encode(uint8_t num,
                   const uint8_t* const raw_data, uint32_t data_size,
                   SampleType_t* const sample, uint32_t sample_cnt){
    bool res = false;
    BpskHandle_t* Node=BpskGetNode(  num);
    if(Node) {
        res= bpsk_encode_ll(Node, raw_data, data_size,sample, sample_cnt);
    }
    return res;
}

static bool bpsk_compose_wav_header_ll(const BpskHandle_t* const Node, WavHeader_t* const Header, uint32_t repetitions){
    bool res = false;
    if(Node){
        if(Header){
            // see https://audiocoding.cc/articles/2008-05-22-wav-file-structure/
            Header->chunkId = reverse_byte_order_uint32(0x52494646);  /* "RIFF" */
            Header->chunkSize = Node->data_size_bytes*repetitions+sizeof(WavHeader_t)-8;  /**/
            Header->format = reverse_byte_order_uint32(0x57415645); /* "WAVE" */
            Header->subchunk1Id = reverse_byte_order_uint32(0x666d7420); /* "fmt" */
            Header->subchunk1Size = 16; /**/
            Header->audioFormat = WAVE_FORMAT_PCM; /**/
            Header->numChannels = 1; /**/
            Header->sampleRate = Node->sampling_frequency_hz;/**/
            Header->blockAlign = 1*(Node->sample_size_bit/8);/**/
            Header->byteRate = Node->sampling_frequency_hz*(Node->sample_size_bit/8);/**/
            Header->bitsPerSample = Node->sample_size_bit;/**/
            Header->subchunk2Id = reverse_byte_order_uint32(0x64617461);/*"data"*/
            Header->subchunk2Size = Node->data_size_bytes*repetitions;/**/
            res = true;
        }
    }
    return res;
}

bool bpsk_encode_to_wav(uint8_t num,
                const uint8_t* const data_to_encode,
                const uint32_t data_size, const uint32_t repetition) {
    bool res = false;
    // TODO: add flow computing
    SampleType_t sample[50000] = {0};
    BpskHandle_t* Node = BpskGetNode(num);
    if(Node) {
        LOG_INFO(BPSK, "Encode,repetition:%u",repetition);
        res = bpsk_encode_ll(Node, data_to_encode, data_size, sample, ARRAY_SIZE(sample));
        if(res) {
            Node->data_size_bytes = sizeof(SampleType_t)*Node->sample_cnt;
            WavHeader_t WavHeader = {0};
            res = bpsk_compose_wav_header_ll(Node, &WavHeader, repetition);
            if(res) {
                res = wav_samples_save(&WavHeader, sample, Node->sample_cnt, repetition);
            }
        } else {
            LOG_ERROR(BPSK,"Encode,Err");
        }
    }
    return res;
}

#ifdef HAS_BPSK_PHASE_ERROR_ASIN
double bpsk_calc_phase_error_asin(BpskHandle_t* const Node){
    double phase_error_rad = 0.0;
    Node->s_feed_back = Node->SdrQ.AfterFilt*Node->SdrI.AfterFilt;
    Node->s_feed_back_sin = 8.0 * Node->s_feed_back;
    if(-1.0<Node->s_feed_back_sin) {
        if(Node->s_feed_back_sin<1.0) {
        } else {
            Node->s_feed_back_sin = 1.0;
            LOG_DEBUG(BPSK, "Asin,Big,Err");
        }
    } else {
        Node->s_feed_back_sin = -1.0;
        LOG_DEBUG(BPSK, "Asin,Small,Err");
    }
    Node->s_feed_back_sin_arg = asin(Node->s_feed_back_sin);
    phase_error_rad = Node->s_feed_back_sin_arg*0.5;
    return phase_error_rad;
}
#endif


/*
 *           Q
 *           ^
 *           |
 *   --------|++++++++
 *   --------|++++++++
 * __--------|++++++++_______\I
 *   ++++++++|--------       /
 *   ++++++++|--------
 *   ++++++++|--------
 */

double bpsk_calc_carrier_phase_err_rad(double i_val, double q_val) {
    double carr_phase_err_rad = 0.0;
    /* PLL discriminator */
    if(0.0 < i_val) {
        //atan2 monotone increasing function
        carr_phase_err_rad = atan2((double)q_val, (double)i_val); // -pi/2......  pi/2
    } else {
        carr_phase_err_rad = atan2((double)-q_val, (double)-i_val);// -pi/2......  pi/2
    }
    LOG_PARN(BPSK, "Carr,Phase,Err:%7.6f Rad", carr_phase_err_rad);
    return carr_phase_err_rad;
}

#ifdef HAS_BPSK_PHASE_ERROR_ATAN
double bpsk_calc_phase_error_atan(BpskHandle_t* const Node) {
    double phase_error_rad = 0.0;
    if(Node) {
        phase_error_rad = bpsk_calc_carrier_phase_err_rad(Node->SdrI.AfterFilt, Node->SdrQ.AfterFilt);
    }
    return (phase_error_rad);
}
#endif

#if 0
//#ifdef HAS_BPSK_PHASE_ERROR_VECTOR
double bpsk_calc_phase_error_vector(BpskHandle_t* const Node) {
    double phase_error_rad = 0.0;
    if(Node) {
        Vector_t x_axis={    0};
        Vector_t phaseVector={ 0};
        phaseVector.dx = (double) Node->SdrI.AfterFilt;
        phaseVector.dy = (double) Node->SdrQ.AfterFilt;
        phaseVector.dz = 0.0;
        x_axis.dx = 100.0;
        x_axis.dy = 0;
        x_axis.dz = 0;
        phase_error_rad = calc_angle_between_vectors_rad(&x_axis,&phaseVector);
    }
    return (phase_error_rad);
}
#endif

static bool bpsk_decode_sample_ll(BpskHandle_t* const Node, SampleType_t sample, uint32_t s) {
    bool res = false;
    Node->time_s = ((double)s) * Node->sample_time_s;
    Node->sample = sample;
#ifdef HAS_BPSK_PHASE_ERROR_ASIN
    Node->real_sample = math_sign((double)sample);
#endif
    //Node->real_sample = ((double)sample)/((double)Node->amplitude);
#ifdef HAS_BPSK_PHASE_ERROR_ATAN
    Node->real_sample = ((double)sample);
#endif
#ifdef HAS_BPSK_PHASE_ERROR_VECTOR
    Node->real_sample = ((double)sample);
#endif

    QuadratureMixerHandle_t* QM = QuadratureMixerGetNode(Node->quadrature_mixer_num);
    if(QM) {
        res = quadrature_mixer_proc_sample_ll(QM,
                                              Node->time_s,
                                              (double) Node->carrier_frequency_hz,
                                              Node->lo_phase_rad,
                                              Node->real_sample) ;

            res = true;

#ifdef HAS_BPSK_PHASE_ERROR_ASIN
            Node->lo_phase_err_rad = -bpsk_calc_phase_error_asin(Node)+  (M_PI/2.0);
            lo_phase_rad = Node->lo_phase_err_rad ; //
#endif

#ifdef HAS_BPSK_PHASE_ERROR_ATAN
            Node->lo_phase_err_rad = bpsk_calc_phase_error_atan(Node);
            Node->lo_phase_rad += BPSK_PHASE_ATAN_PROP* (Node->lo_phase_err_rad); // integrator
#endif

            Node->lo_phase_err_rad = QM->phase_error_rad;
#ifdef HAS_BPSK_PHASE_ERROR_VECTOR
            //Node->lo_phase_err_rad = bpsk_calc_phase_error_vector(Node);
            Node->lo_phase_rad += BPSK_PHASE_VEC_PROP*(Node->lo_phase_err_rad); // integrator
#endif
            //res = pid_proc_value(Node->pid_phase_err_num, Node->lo_phase_err_rad, &Node->lo_phase_rad);

            //LOG_DEBUG(BPSK, "S=%d", s);
            FirSample_t lo_phase_filt_rad = 0.0;
            res = filter_proc_in_out(Node->filter_loop_num,Node->filter_loop_type, (FirSample_t) Node->lo_phase_rad, (FirSample_t*) &lo_phase_filt_rad);
            if(res) {
                //LOG_DEBUG(BPSK, "S=%d, lo_phase_filt_rad:%f", s, lo_phase_filt_rad);
                Node->lo_phase_rad = (double) lo_phase_filt_rad;
            }else {
                LOG_ERROR(BPSK, "Fir,Lo,Phase,Err");
            }

            char logLine[300] = {0};
            BpskComposeLogLine(Node, logLine, sizeof(logLine));
            file_pc_print_array(Node->LogFileName, logLine, strlen(logLine));

            Node->data = (math_sign(QM->SdrI.AfterFilt)+1.0)/2;
            int8_t bit_data = 0xee;
            bool decimator_res = decimator_proc_val(Node->decimator_num, Node->data, &bit_data);
            if(decimator_res) {
                LOG_DEBUG(BPSK, "Bit[%u]=%d",Node->bit_rx_cnt,bit_data);
                if(Node->BinDataArray) {
                    uint32_t byteNum = Node->bit_rx_cnt/8;
                    uint8_t bitNum = Node->bit_rx_cnt%8;
                    switch(bit_data) {
                        case 0:{
                            RESET_BIT_NUM(Node->BinDataArray[byteNum], (7-bitNum));
                        } break;
                        case 1:{
                            SET_BIT_NUM(Node->BinDataArray[byteNum], (7-bitNum));
                        } break;
                        default: res = false; break;
                    }
                }
                Node->bit_rx_cnt++;
            }
    //    }else {
    //        LOG_ERROR(BPSK, "Fir,Q,Err");
    //    }
    //}else {
    //    LOG_ERROR(BPSK, "Fir,I,Err");
    }//if(QM)

    return res;
}

/*
 * Deencode from BPSK sample array
 *
 * x_signal - ADC data with information
 * sample_cnt - ADC sample cnt
 * raw_data - deencoded data
 * data_size - deencoded data size
 */
bool bpsk_decode_ll(BpskHandle_t* const Node,
        const SampleType_t* const SignalArray, uint32_t sample_cnt,
        uint8_t* const raw_data, uint32_t * const data_size ){
    bool res = false;
    if(Node) {
        if(SignalArray) {
            if(sample_cnt) {
                if(raw_data) {
                    res = true;
                }
            }
        }
    }

    if(res) {
        res = false;
        LOG_INFO(BPSK, "Decode,%u,Samples",sample_cnt);
        file_pc_delete(Node->LogFileName);
        Node->bit_rx_cnt = 0;
        Node->data_size_bytes = 0;
        Node->BinDataArray = raw_data;
        uint32_t s = 0;
        uint32_t ok_cnt = 0;
        for(s=0; s<sample_cnt; s++) {
            res = bpsk_decode_sample_ll(Node, SignalArray[s], s);
            if(res){
                ok_cnt++;
            }
        }
        if(ok_cnt==sample_cnt){
            res = true;
        }else {
            res = false;
        }
        Node->data_size_bytes = Node->bit_rx_cnt/8;
        if(data_size) {
            *data_size = Node->data_size_bytes ;
        }
    }
    return res;
}

/*
 */
bool bpsk_decode(uint8_t num,
                 const SampleType_t* const SampleArray, uint32_t sample_cnt,
                 uint8_t* const raw_data, uint32_t* data_size){
    bool res = false;
    BpskHandle_t* Node = BpskGetNode(num);
    if (Node) {
        res = bpsk_decode_ll(Node, SampleArray, sample_cnt, raw_data, data_size );
    }
    return res;
}


static bool BpskIsValidConfig( const BpskConfig_t*const  Config ){
    bool res = false;
    if(Config) {
        if(0<Config->bit_rate){
            if(0<Config->sampling_frequency_hz){
                if(0<Config->dds_num){
                    if(0<Config->amplitude){
                        res = true;
                    }else{
                        LOG_ERROR(BPSK, "Absurd,Amp");
                    }
                }else{
                    LOG_ERROR(BPSK, "Absurd,DDS");
                }
            }else{
                LOG_ERROR(BPSK, "Absurd,Fs");
            }
        }else{
            LOG_ERROR(BPSK, "Absurd,BitRate");
        }

        if(res) {
            if(0 < Config->carrier_frequency_hz) {
                res = true;
            } else {
                LOG_ERROR(BPSK, "carrier,frequency,Err");
                res = false;
            }
        }

        if(res) {
            if(Config->carrier_frequency_hz< (Config->sampling_frequency_hz/2)){
                res = true;
            }else{
                LOG_ERROR(BPSK, "Fcar,TooBig");
                res = false;
            }
        }

        if(res) {
            if(0 < Config->sample_size_bit) {
                res = true;
            } else {
                LOG_ERROR(BPSK, "Sample,Bit,Err");
                res = false;
            }
        }

        if(res) {
            if((sizeof(SampleType_t)*8) == Config->sample_size_bit) {
                res = true;
            } else {
                LOG_ERROR(BPSK, "Sample,Size,Err");
                res = false;
            }
        }

        if(res) {
            if(0 < Config->filter_order) {
                res = true;
            } else {
                LOG_ERROR(BPSK, "Fir,Order,Err");
                res = false;
            }
        }

        if(res) {
            if(0 < Config->quadrature_mixer_num) {
                res = true;
            } else {
                LOG_ERROR(BPSK, "Qmix,Num,Err");
                res = false;
            }
        }

    }
    return res;
}

static bool bpsk_wav_proc_samples(BpskHandle_t* const Node, const char* const file_name) {
    bool res = false;
    LOG_INFO(BPSK, "Proc,Sample,File:[%s]", file_name);
    if(file_name) {
        FILE* pFileRead = NULL;
        pFileRead = fopen(file_name, "rb");
        if(pFileRead) {
            LOG_INFO(BPSK, "Open,File:[%s]Ok", file_name);
            WavHeader_t WavHeader={0};
            size_t real_read = fread((void*)&WavHeader, sizeof(WavHeader_t),1, pFileRead);
            if(1==real_read) {
                LOG_INFO(BPSK, "Read,Header,Ok,%s",WavHeaderToStr(&WavHeader));

                WavHandle_t WavHandle = {0};
                WavHandle.sample_time_s = 1.0 / ((double)WavHeader.sampleRate);
                WavHandle.sample_cnt = WavHeader.subchunk2Size/WavHeader.blockAlign;
                WavHandle.duration_s = WavHandle.sample_time_s*((double)WavHandle.sample_cnt);
                LOG_INFO(BPSK, "%s",WavHandleToStr(&WavHandle));
              //  LOG_INFO(BPSK, "%s",WavHandleToStr(&WavHandle));

                file_pc_delete(Node->LogFileName);
                Node->bit_rx_cnt = 0;
                Node->data_size_bytes = 0;
                Node->BinDataArray = NULL;

                uint32_t s = 0;
                for(s=0; s<WavHandle.sample_cnt; s++) {
                    LOG_DEBUG(BPSK,"Proc,Sample:%u", s);
                    BpskSample_t Sample = {0};
                    real_read = fread((void*)&Sample, WavHeader.blockAlign,1, pFileRead);
                    if( 1 == real_read) {
                        res = bpsk_decode_sample_ll(Node, Sample, s);
                    }else{
                        res = false;
                        LOG_ERROR(BPSK,"Read,Data,Err:%u",real_read);
                    }
                    if(0==(s%(WavHandle.sample_cnt/100))){
                        cli_printf("\r%s",ProgressToStr(  s,   WavHandle.sample_cnt));
                    }
                }
                res = true;
            } else {
                LOG_ERROR(BPSK,"readErr");
            }


            fclose(pFileRead);
        } else {
            LOG_ERROR(BPSK, "OpenFile:[%s] Err", file_name);
        }

    }
    return res;
}


bool bpsk_decode_wav(uint8_t  num, const char* const file_name){
    bool res = false;
    BpskHandle_t* Node=BpskGetNode(num);
    if(Node) {
        if(file_name) {
            LOG_INFO(BPSK, "N:%u,Decode,File:%s", num, file_name);
            WavHeader_t WavHeader = {0};
            res = wav_info_ll(&WavHeader, file_name);
            if (res) {
                res = false;
                Node->sampling_frequency_hz =WavHeader.sampleRate ;
                Node->sample_size_bit = WavHeader.bitsPerSample;
                Node->sample_cnt = WavHeader.subchunk2Size/WavHeader.blockAlign;
                Node->sample_time_s = 1.0/((double)Node->sampling_frequency_hz);

                LOG_INFO(BPSK, "%s", BpskNodeToStr(Node));

                res = bpsk_wav_proc_samples(Node, file_name);
            }
        }
    }
    return res;
}


bool bpsk_reinit_node(uint8_t num){
    bool res = false;
    BpskHandle_t* Node = BpskGetNode(num);
    if(Node) {
        Node->chip_dutation_s = 1.0/((double)Node->bit_rate);
        Node->carrier_period_s = 1.0/((double)Node->carrier_frequency_hz);
        Node->sample_time_s = 1.0/((double)Node->sampling_frequency_hz);
        Node->sample_per_chip = (uint32_t) ( Node->chip_dutation_s/ Node->sample_time_s);
        Node->carrier_periods_per_chip = (uint32_t) ( Node->chip_dutation_s/ Node->carrier_period_s);
        Node->lo_phase_rad = 0.0;

        res = quadrature_mixer_init_one(Node->quadrature_mixer_num);
        if(res) {
            res = filter_synthesize(Node->filter_loop_num ,Node->filter_loop_type,
                        Node->filter_order,
						Node->filter_loop_cuf_off_freq_hz,
                        (FirSample_t) Node->sampling_frequency_hz );
            if(res) {
                res = decimator_adjust(Node->decimator_num, (Node->sample_per_chip*9)/10);
                if(res) {
                    LOG_WARNING(BPSK, "%s",BpskNodeToStr(Node));
                    LOG_INFO(BPSK, "Init,Ok");
                    Node->init = true;
                }
            }
        }
    }
    return res;
}

bool bpsk_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(BPSK, "Init:%u");
    const BpskConfig_t* Config = BpskGetConfig(num);
    if(Config) {
        LOG_WARNING(BPSK, "SpotConfig:%s",BpskConfigToStr(Config));
        res = BpskIsValidConfig(Config);
        if(res) {
            res = false;
            BpskHandle_t* Node = BpskGetNode(num);
            if(Node) {
                Node->LogFileName = Config->LogFileName;
                Node->quadrature_mixer_num = Config->quadrature_mixer_num;
                Node->amplitude = Config->amplitude;
                Node->bit_order = Config->bit_order;
                Node->bit_rate = Config->bit_rate;
                Node->carrier_frequency_hz = Config->carrier_frequency_hz;
                Node->dds_num = Config->dds_num;
                Node->decimator_num = Config->decimator_num;
                Node->filter_loop_cuf_off_freq_hz = Config->filter_loop_cuf_off_freq_hz;
                Node->filter_loop_type = Config->filter_loop_type;
                Node->filter_loop_num = Config->filter_loop_num;
                Node->filter_order = Config->filter_order;
                Node->name = Config->name;
                Node->num = Config->num;
                Node->pid_phase_err_num = Config->pid_phase_err_num;
                Node->sample_size_bit = Config->sample_size_bit;
                Node->sampling_frequency_hz = Config->sampling_frequency_hz;

                res = bpsk_reinit_node(num);
            }
        } else {
            LOG_INFO(BPSK, "Absurd,Config");
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(BPSK, BPSK, bpsk)
