#include "bpsk_4fs_mcal.h"

#include <string.h>

#include "bit_utils.h"
#include "dsp.h"
#include "byte_utils.h"
#include "code_generator.h"
#include "csv.h"
#include "debug_info.h"
#include "quad_mix_4fs.h"
#include "decimator.h"
#include "num_to_str.h"
#include "log.h"
#include "time_mcal.h"
#include "utils_math.h"
#include "vector_math.h"
#include "local_oscillator_mcal.h"
#include "dc_cut_filter_mcal.h"

#ifdef HAS_GPIO
#include "gpio_mcal.h"
#endif

#ifdef HAS_ADC
#include "adc_mcal.h"
#endif

#ifdef HAS_DDS
#include "dds_drv.h"
#endif

#ifdef HAS_FIR
#include "fir.h"
#endif

#ifdef HAS_WAV
#include "wav.h"
#endif

#ifdef HAS_IQUEUE
#include "iqueue.h"
#endif

#ifdef HAS_FILE_PC
#include "file_pc.h"
#endif

#ifdef HAS_PID
#include "pid.h"
#endif

COMPONENT_GET_NODE(Bpsk4fs, bpsk_4fs)
COMPONENT_GET_CONFIG(Bpsk4fs, bpsk_4fs)

static bool bpsk_4fs_init_custom(void) {
    bool res = true;
    return res;
}

static int32_t Bpsk4fsBitValToPhaseS32(uint8_t bit_val) {
    int32_t phase = 0;
    switch(bit_val) {
        case 0: phase = -1; break;
        case 1: phase = 1; break;
        default:
        {
            phase = 0;
            LOG_ERROR(BPSK_4FS,"bit_val:%u",bit_val);
        }
        break;
    }
    return phase;
}

static uint32_t bpsk_4fs_encode_chirp(Bpsk4fsHandle_t* Node,
                                  uint32_t s ,
                                  const uint8_t* const data,
                                  uint32_t bit,
                                  int32_t* const sample) {
    // MSB first
    // One bit - one chirp
    uint32_t byte_num = bit / 8;
    uint8_t bit_num = 7 - (bit % 8);
    bool bit_val = bit_get_u8(data[byte_num], bit_num);
    LOG_DEBUG(BPSK_4FS, "Data:0%x,ByteN:%u,BitN:%u,BitVal:%u,samPerChip:%u Sam"CRLF, data[byte_num], byte_num, bit_num, bit_val,Node->sample_per_chip);
    int32_t pbsk_phase = Bpsk4fsBitValToPhaseS32(bit_val);
    uint32_t chirp_sample = 0;
    for (chirp_sample = 0; chirp_sample < Node->sample_per_chip; chirp_sample++) {
        sample[s] = (int32_t) (pbsk_phase * sin4_int(s, 0));
        cli_printf("%d;", sample[s]);
        s++;

    }
    return s;
}

/*
 * encode from BPSK_4FS sample array
 *
 * x_signal - ADC data with information
 * data - data to encode
 * data_size - data size
 * sample - ADC sample with modulation
 * sample_cnt - sample count
 * sample_len - the number of samples that were actually required
 */

static bool bpsk_4fs_encode_ll(Bpsk4fsHandle_t* Node,
                   const uint8_t* const data, uint32_t data_size,
                   int32_t* const sample, uint32_t sample_cnt,uint32_t *sample_len){
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
        LOG_INFO(BPSK_4FS,"Encode,%s", Bpsk4fsNodeToStr(Node));
        uint32_t bit_cnt = 8*data_size;
        Node->sample_cnt = Node->sample_per_chip*bit_cnt;
        *sample_len = Node->sample_cnt;
        if(Node->sample_cnt < sample_cnt) {
            LOG_INFO(BPSK_4FS,"Encode,%u,Sam",Node->sample_cnt );
            Node->samples = sample;
            uint32_t bit = 0;
            uint32_t s = 0;
            for(bit=0; bit < bit_cnt; bit++) {
                s = bpsk_4fs_encode_chirp(Node, s ,data,bit,sample);
                res = true;
            }
        } else {
            LOG_ERROR(BPSK_4FS,"NotEnoughSamples,Need:%u,Available:%u",Node->sample_cnt,sample_cnt);
        }
    }

    return res;
}

bool bpsk_4fs_encode(uint8_t num,
                     const uint8_t* const message,
                     const uint32_t message_size,
                     int32_t* const sample,
                     uint32_t sample_cnt,
                     uint32_t *const sample_len ) {
    bool res = false;
    Bpsk4fsHandle_t *Node = Bpsk4fsGetNode(num);
    if(Node) {
        res = bpsk_4fs_encode_ll(Node, message, message_size, sample, sample_cnt, sample_len);
    }
    return res;
}

#ifdef HAS_WAV
static bool bpsk_4fs_compose_wav_header_ll(const Bpsk4fsHandle_t* const Node, WavHeader_t* const Header, uint32_t repetitions){
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
#endif

#ifdef HAS_WAV
bool bpsk_4fs_encode_to_wav(uint8_t num,
                const uint8_t* const data_to_encode,
                const uint32_t data_size, const uint32_t repetition) {
    bool res = false;
    // TODO: add flow computing
    int32_t sample[50000] = {0};
    Bpsk4fsHandle_t* Node = Bpsk4fsGetNode(num);
    if(Node) {
        LOG_INFO(BPSK_4FS, "Encode,repetition:%u",repetition);
        res = bpsk_4fs_encode_ll(Node, data_to_encode, data_size, sample, ARRAY_SIZE(sample));
        if(res) {
            Node->data_size_bytes = sizeof(int32_t)*Node->sample_cnt;
            WavHeader_t WavHeader = {0};
            res = bpsk_4fs_compose_wav_header_ll(Node, &WavHeader, repetition);
            if(res) {
                res = wav_samples_save(&WavHeader, sample, Node->sample_cnt, repetition);
            }
        } else {
            LOG_ERROR(BPSK_4FS,"Encode,Err");
        }
    }
    return res;
}
#endif

#ifdef HAS_BPSK_4FS_PHASE_ERROR_ASIN
float bpsk_4fs_calc_phase_error_asin(Bpsk4fsHandle_t* const Node){
    float phase_error_rad = 0.0;
    Node->s_feed_back = Node->SdrQ.AfterFilt*Node->SdrI.AfterFilt;
    Node->s_feed_back_sin = 8.0 * Node->s_feed_back;
    if(-1.0<Node->s_feed_back_sin) {
        if(Node->s_feed_back_sin<1.0) {
        } else {
            Node->s_feed_back_sin = 1.0;
            LOG_DEBUG(BPSK_4FS, "Asin,Big,Err");
        }
    } else {
        Node->s_feed_back_sin = -1.0;
        LOG_DEBUG(BPSK_4FS, "Asin,Small,Err");
    }
    Node->s_feed_back_sin_arg = asin(Node->s_feed_back_sin);
    phase_error_rad = Node->s_feed_back_sin_arg*0.5;
    return phase_error_rad;
}
#endif

bool bpsk_4fs_rx_bit_phase(const uint8_t num,const  int32_t rx_bit_phase) {
    bool res = false;
    LOG_INFO(BPSK_4FS, "N:%u,BitPhase:%d", num, rx_bit_phase);
    Bpsk4fsHandle_t *Node = Bpsk4fsGetNode(num);
    if (Node) {
        Node->bit_rx_phase = rx_bit_phase;
        res = true;
    }
    return res;
}

#ifdef HAS_BPSK_4FS_PHASE_ERROR_ATAN
float bpsk_4fs_calc_phase_error_atan(Bpsk4fsHandle_t* const Node) {
    float phase_error_rad = 0.0;
    if(Node) {
        phase_error_rad = bpsk_4fs_calc_carrier_phase_err_rad(Node->SdrI.AfterFilt, Node->SdrQ.AfterFilt);
    }
    return (phase_error_rad);
}
#endif

#if 0
//#ifdef HAS_BPSK_4FS_PHASE_ERROR_VECTOR
float bpsk_4fs_calc_phase_error_vector(Bpsk4fsHandle_t* const Node) {
    float phase_error_rad = 0.0;
    if(Node) {
        Vector_t x_axis={    0};
        Vector_t phaseVector={ 0};
        phaseVector.dx = (float) Node->SdrI.AfterFilt;
        phaseVector.dy = (float) Node->SdrQ.AfterFilt;
        phaseVector.dz = 0.0;
        x_axis.dx = 100.0;
        x_axis.dy = 0;
        x_axis.dz = 0;
        phase_error_rad = calc_angle_between_vectors_rad(&x_axis,&phaseVector);
    }
    return (phase_error_rad);
}
#endif

bool bpsk_4fs_phase_error_calc_ll(Bpsk4fsHandle_t* const Node) {
    bool res = true;
#ifdef HAS_BPSK_4FS_PHASE_ERROR_ASIN
    Node->lo_phase_err_rad = -bpsk_4fs_calc_phase_error_asin(Node)+  (M_PI/2.0);
    lo_phase_sample = Node->lo_phase_err_rad ; //
#endif

#ifdef HAS_BPSK_4FS_PHASE_ERROR_ATAN
    Node->lo_phase_err_rad = bpsk_4fs_calc_phase_error_atan(Node);
    Node->lo_phase_sample += BPSK_4FS_PHASE_ATAN_PROP* (Node->lo_phase_err_rad); // integrator
#endif
    return res;
}

static bool bpsk_4fs_decode_decimator(Bpsk4fsHandle_t* const Node) {
    bool res = true;
    int8_t bit_data = 0xee;
    bool spot_bit = decimator_proc_val(Node->decimator_num, Node->data, &bit_data);
#ifdef HAS_BPSK_DEBUG
    //log_parn_res(BPSK_4FS,res,"decimatorProc");
#endif
    if (spot_bit) {
#ifdef HAS_BPSK_DEBUG
       LOG_DEBUG(BPSK_4FS, "Bit[%u]=%d", Node->bit_rx_cnt, bit_data);
#endif

#ifdef HAS_GPIO
        gpio_logic_level_set(Node->PadData, (GpioLogicLevel_t) bit_data);
        gpio_toggle(Node->PadClk);
#endif

        uint32_t cur_bit_rx_cnt = (uint32_t)(((int32_t) Node->bit_rx_cnt) + ((int32_t) Node->bit_rx_phase));
        uint8_t bitNum = cur_bit_rx_cnt % 8;/* 0 1 2 3 4 5 6 7  0 1 2 3*/
        switch (bit_data) {
            case 0: {
                RESET_BIT_NUM(Node->rx_byte, (7 - bitNum));
            }
                break;
            case 1: {
                SET_BIT_NUM(Node->rx_byte, (7 - bitNum));
            }
                break;
            default:
                res = false;
                break;
        }

        if(7==bitNum) {
#ifdef HAS_BPSK_DEBUG
            LOG_NOTICE(BPSK_4FS, "h%02x-%s", Node->rx_byte, utoa_bin8(Node->rx_byte));
            if (Node->BinDataArray) {
                uint32_t byteNum = cur_bit_rx_cnt / 8; /**/
                if (byteNum < Node->data_size_bytes) {
                    Node->BinDataArray[byteNum]=Node->rx_byte;
                }
            }
#endif

        }
        Node->bit_rx_cnt++;
    }
    return res;
}

int32_t Bpsk4fskRadToSample(float phase_error_rad) {
    int32_t phase_n = 0;
    float phase_error_deg = RAD_2_DEG(phase_error_rad);

    phase_n = -(  (int32_t) ( phase_error_deg/90.0f)    );

#if 0
    if(0 == phase_n) {
        if(10.0 < fabsf(phase_error_deg)) {

            if(0 < phase_error_deg) {
                phase_n = -((int32_t) ceilf(phase_error_deg / 90.0f));
            } else {
                phase_n = -((int32_t) floorf(phase_error_deg / 90.0f));
            }
        }
    }
#endif
    //LOG_PARN(BPSK_4FS, "PhaseErr:%f deg -> %d Sam",phase_error_rad,phase_n);
    return phase_n;
}

// Hi load function
static bool bpsk_4fs_decode_sample_ll(Bpsk4fsHandle_t* const Node,  int32_t sample) {
    bool res = false;
    Node->sample = sample;
#ifdef HAS_BPSK_DEBUG
    LOG_PARN(BPSK_SAMPLE, "[%d]=%d",Node->sam_n,sample);
#endif
    QuadMix4fsHandle_t *QM = QuadMix4fsGetNode(Node->quad_mix_4fs_num);
    res = quad_mix_4fs_proc_sample_ll(QM, Node->sam_n, sample);
    //log_parn_res(BPSK_4FS,res,"QmuxProcSam");
    //QM->lo_phase_n = -1;
    // 0 sam-   phase_error_rad:90 deg
    // -1 sam-   phase_error_rad:0 deg
    float  lo_phase_rad = 0.0;
    res = pid_proc_value(Node->pid_num, QM->phase_error_rad, &lo_phase_rad);
    QM->lo_phase_n = Bpsk4fskRadToSample(lo_phase_rad);

#if 0
        FirSample_t out = 0;
        FirSample_t in = QM->phase_error_rad;
        res = fir_proc_in_out(FIR_MUN_LO_PHASE, in, (FirSample_t*) &out);
        if(res) {
            //LOG_DEBUG(BPSK_4FS, "S=%d, lo_phase_filt_rad:%f", s, lo_phase_filt_rad);
            QM->phase_error_rad = out;
            QM->lo_phase_n = Bpsk4fskRadToSample(QM->phase_error_rad);
        }else {
            LOG_ERROR(BPSK_4FS, "Fir,Lo,Phase,Err");
        }
#endif

        Node->data = (math_sign_s32(QM->SdrI.AfterFilt) + 1) / 2;
        res = bpsk_4fs_decode_decimator(Node);
        //log_parn_res(BPSK_4FS,res,"Decode");


    return res;
}

/*
 * Deencode from BPSK_4FS sample array
 *
 * x_signal - ADC data with information
 * sample_cnt - ADC sample cnt
 * raw_data - deencoded data
 * data_size - deencoded data size
 */
static bool bpsk_4fs_decode_ll(Bpsk4fsHandle_t* const Node,
                               const int32_t* const SignalArray,
                               uint32_t sample_cnt,
                               uint8_t* const raw_data,
                               uint32_t const raw_data_size,
                               uint32_t * const data_size ){
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
        LOG_INFO(BPSK_4FS, "Decode,%u,Samples",sample_cnt);
#ifdef HAS_FILE_PC
        file_pc_delete(Node->LogFileName);
#endif
        Node->bit_rx_cnt = 0;
        Node->data_size_bytes = raw_data_size;
        Node->BinDataArray = raw_data;
        uint32_t s = 0;
        uint32_t ok_cnt = 0;
        for(s = 0; s <  sample_cnt; s++) {
            Node->sam_n =s;
            res = bpsk_4fs_decode_sample_ll(Node,  SignalArray[s]);
            if(res) {
                ok_cnt++;
            }
        }
        if(ok_cnt==sample_cnt){
            res = true;
        }else {
            res = false;
            LOG_ERROR(BPSK_4FS,"Ok:%u/%u",ok_cnt,sample_cnt);
        }
        //Node->data_size_bytes = Node->bit_rx_cnt/8;
        if(data_size) {
            *data_size = Node->bit_rx_cnt/8 ;
        }
    }
    return res;
}

/*
 */
bool bpsk_4fs_decode(uint8_t num,
                 const int32_t* const SampleArray,
                 uint32_t sample_cnt,
                 uint8_t* const raw_data,
                 const uint32_t raw_data_size,
                 uint32_t* message_size){
    bool res = false;
    Bpsk4fsHandle_t* Node = Bpsk4fsGetNode(num);
    if (Node) {
        res = bpsk_4fs_decode_ll(Node, SampleArray, sample_cnt, raw_data, raw_data_size, message_size );
    }
    return res;
}


static bool Bpsk4fsIsValidConfig( const Bpsk4fsConfig_t*const  Config ){
    bool res = false;
    if(Config) {
        if(0<Config->bit_rate){
            if(0<Config->sampling_frequency_hz){
                if(0<Config->dds_num){
                    if(0<Config->amplitude){
                        res = true;
                    }else{
                        LOG_ERROR(BPSK_4FS, "Absurd,Amp");
                    }
                }else{
                    LOG_ERROR(BPSK_4FS, "Absurd,DDS");
                }
            }else{
                LOG_ERROR(BPSK_4FS, "Absurd,Fs");
            }
        }else{
            LOG_ERROR(BPSK_4FS, "Absurd,BitRate");
        }

        if(res) {
            if(0 < Config->carrier_frequency_hz) {
                res = true;
            } else {
                LOG_ERROR(BPSK_4FS, "carrier,frequency,Err");
                res = false;
            }
        }

        if(res) {
            if(Config->carrier_frequency_hz< (Config->sampling_frequency_hz/2)){
                res = true;
            }else{
                LOG_ERROR(BPSK_4FS, "Fcar,TooBig");
                res = false;
            }
        }

            ifn(0 < Config->sample_size_bit) {
                LOG_ERROR(BPSK_4FS, "Sample,Bit,Err");
                res = false;
            }

        if(res) {
            if((sizeof(int32_t)*8) == Config->sample_size_bit) {
                res = true;
            } else {
                LOG_ERROR(BPSK_4FS, "Sample,Size,Err");
                res = false;
            }
        }

            ifn(0 < Config->filter_order) {
                LOG_ERROR(BPSK_4FS, "Fir,Order,Err");
                res = false;
            }

            ifn(0 < Config->quad_mix_4fs_num) {
                LOG_ERROR(BPSK_4FS, "Qmix,Num,Err");
                res = false;
            }

    }
    return res;
}

#ifdef HAS_WAV
static bool bpsk_4fs_wav_proc_samples(Bpsk4fsHandle_t* const Node, const char* const file_name) {
    bool res = false;
    LOG_INFO(BPSK_4FS, "Proc,Sample,File:[%s]", file_name);
    if(file_name) {
        FILE* pFileRead = NULL;
        pFileRead = fopen(file_name, "rb");
        if(pFileRead) {
            LOG_INFO(BPSK_4FS, "Open,File:[%s]Ok", file_name);
            WavHeader_t WavHeader={0};
            size_t real_read = fread((void*)&WavHeader, sizeof(WavHeader_t),1, pFileRead);
            if(1==real_read) {
                LOG_INFO(BPSK_4FS, "Read,Header,Ok,%s",WavHeaderToStr(&WavHeader));

                WavHandle_t WavHandle = {0};
                WavHandle.sample_time_s = 1.0 / ((float)WavHeader.sampleRate);
                WavHandle.sample_cnt = WavHeader.subchunk2Size/WavHeader.blockAlign;
                WavHandle.duration_s = WavHandle.sample_time_s*((float)WavHandle.sample_cnt);
                LOG_INFO(BPSK_4FS, "%s",WavHandleToStr(&WavHandle));
              //  LOG_INFO(BPSK_4FS, "%s",WavHandleToStr(&WavHandle));

                file_pc_delete(Node->LogFileName);
                Node->bit_rx_cnt = 0;
                Node->data_size_bytes = 0;
                Node->BinDataArray = NULL;

                uint32_t s = 0;
                for(s=0; s<WavHandle.sample_cnt; s++) {
                    LOG_DEBUG(BPSK_4FS,"Proc,Sample:%u", s);
                    Bpsk4fsSample_t Sample = {0};
                    real_read = fread((void*)&Sample, WavHeader.blockAlign,1, pFileRead);
                    if( 1 == real_read) {
                        res = bpsk_4fs_decode_sample_ll(Node, Sample, s);
                    }else{
                        res = false;
                        LOG_ERROR(BPSK_4FS,"Read,Data,Err:%u",real_read);
                    }
                    if(0==(s%(WavHandle.sample_cnt/100))){
                        cli_printf("\r%s",ProgressToStr(  s,   WavHandle.sample_cnt));
                    }
                }
                res = true;
            } else {
                LOG_ERROR(BPSK_4FS,"readErr");
            }


            fclose(pFileRead);
        } else {
            LOG_ERROR(BPSK_4FS, "OpenFile:[%s] Err", file_name);
        }

    }
    return res;
}
#endif

#ifdef HAS_WAV
bool bpsk_4fs_decode_wav(uint8_t  num, const char* const file_name){
    bool res = false;
    Bpsk4fsHandle_t* Node=Bpsk4fsGetNode(num);
    if(Node) {
        if(file_name) {
            LOG_INFO(BPSK_4FS, "N:%u,Decode,File:%s", num, file_name);
            WavHeader_t WavHeader = {0};
            res = wav_info_ll(&WavHeader, file_name);
            if (res) {
                res = false;
                Node->sampling_frequency_hz =WavHeader.sampleRate ;
                Node->sample_size_bit = WavHeader.bitsPerSample;
                Node->sample_cnt = WavHeader.subchunk2Size/WavHeader.blockAlign;
                Node->sample_time_s = 1.0/((float)Node->sampling_frequency_hz);

                LOG_INFO(BPSK_4FS, "%s", Bpsk4fsNodeToStr(Node));

                res = bpsk_4fs_wav_proc_samples(Node, file_name);
            }
        }
    }
    return res;
}
#endif


bool bpsk_4fs_reinit_node(uint8_t num) {
    bool res = false;
    Bpsk4fsHandle_t *Node = Bpsk4fsGetNode(num);
    if (Node) {
        Node->chip_dutation_s = 1.0f / ((float) Node->bit_rate);
        Node->carrier_period_s = 1.0f / ((float) Node->carrier_frequency_hz);
        Node->sample_time_s = 1.0f / ((float) Node->sampling_frequency_hz);
        Node->sample_per_chip = (uint32_t) ceilf(Node->chip_dutation_s / Node->sample_time_s);
        Node->carrier_periods_per_chip = (uint32_t) ceilf(Node->chip_dutation_s / Node->carrier_period_s);
        LOG_INFO(BPSK_4FS, "SamPerChip:%u",Node->sample_per_chip);
        res = quad_mix_4fs_init_one(Node->quad_mix_4fs_num);
        if (res) {
            res = decimator_adjust(Node->decimator_num, (Node->sample_per_chip * 9) / 10);
            if (res) {
                LOG_WARNING(BPSK_4FS, "%s", Bpsk4fsNodeToStr(Node));
                LOG_INFO(BPSK_4FS, "Init,Ok");
                Node->init = true;
            }

        }
    }
    return res;
}

static bool bpsk_4fs_init_filter_common(const Bpsk4fsConfig_t* const Config, Bpsk4fsHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->filter_loop_cuf_off_freq_hz = Config->filter_loop_cuf_off_freq_hz;
            Node->filter_loop_type = Config->filter_loop_type;
            Node->filter_loop_num = Config->filter_loop_num;
            Node->filter_order = Config->filter_order;
            res = true;
        }
    }
    return res;
}

static bool bpsk_4fs_init_decoder_common(const Bpsk4fsConfig_t* const Config,
                                         Bpsk4fsHandle_t* const Node) {
    bool res = true;
    Node->quad_mix_4fs_num = Config->quad_mix_4fs_num;
    Node->bit_rx_phase = Config->bit_rx_phase;
    Node->bit_order = Config->bit_order;
    Node->pid_num = Config->pid_num;
    Node->adc_num = Config->adc_num;
    Node->decimator_num = Config->decimator_num;
    Node->dc_cut_filter_num = Config->dc_cut_filter_num;
    Node->pid_phase_err_num = Config->pid_phase_err_num;
    Node->filter_loop_num = Config->filter_loop_num;
    Node->filter_loop_type = Config->filter_loop_type;
    Node->filter_order = Config->filter_order;
    Node->BinDataArray = Config->BinDataArray;
    Node->data_size_bytes = Config->data_size_bytes;
    Node->filter_loop_cuf_off_freq_hz = Config->filter_loop_cuf_off_freq_hz;
    return res;
}


static bool bpsk_4fs_init_phy_common(const Bpsk4fsConfig_t* const Config, Bpsk4fsHandle_t* const Node){
    bool res = true;
    Node->bit_rate = Config->bit_rate; /* 100 bit/s  */
    Node->carrier_frequency_hz = Config->carrier_frequency_hz; /*2kHz*/
    Node->sampling_frequency_hz = Config->sampling_frequency_hz; /*8kHz*/
    Node->sample_size_bit = Config->sample_size_bit;
    return res;
}

static bool bpsk_4fs_init_common(const Bpsk4fsConfig_t* const Config, Bpsk4fsHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            res = bpsk_4fs_init_filter_common(Config, Node) ;
            res = bpsk_4fs_init_decoder_common(Config, Node) ;
            res = bpsk_4fs_init_phy_common(Config, Node) ;
            Node->LogFileName = Config->LogFileName;
            Node->amplitude = Config->amplitude;
            Node->dds_num = Config->dds_num;
            Node->name = Config->name;
            Node->num = Config->num;
#ifdef HAS_GPIO
            Node->PadData = Config->PadData;
            Node->PadClk = Config->PadClk;
#endif
            res = true;
        }
    }
    return res;
}

bool bpsk_4fs_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(BPSK_4FS, "Init:%u", num);
    const Bpsk4fsConfig_t *Config = Bpsk4fsGetConfig(num);
    res = Bpsk4fsIsValidConfig(Config);
    if(res) {
        LOG_WARNING(BPSK_4FS, "SpotConfig:%s", Bpsk4fsConfigToStr(Config));
        res = false;
        Bpsk4fsHandle_t *Node = Bpsk4fsGetNode(num);
        if(Node) {
            res = bpsk_4fs_init_common(Config, Node);
            res = bpsk_4fs_reinit_node(num);
        }

    } else {
        LOG_INFO(BPSK_4FS, "Absurd,Config");
    }
    return res;
}

bool proc_samples_to_mem(Bpsk4fsHandle_t* Bpsk, uint16_t *SampleMem, uint32_t start, uint32_t end) {
    bool res = false;
    uint32_t i = 0;
    for(i=start; i<end; i++) {
        //LOG_DEBUG(BPSK_4FS, "Sam:[%u]=%u",i,SampleMem[i]);
        int32_t x = (int32_t) SampleMem[i];
        int32_t y = 0;
        res = dc_cut_filter_proc_sample(Bpsk->dc_cut_filter_num, x, &y);
        res = bpsk_4fs_decode_sample_ll(Bpsk, y);
        Bpsk->sam_n++;
    }
    return res;
}

#ifdef HAS_ADC
static bool bpsk_4fs_proc_from_adc_mem(Bpsk4fsHandle_t* Bpsk) {
    bool res = false;
    AdcHandle_t *Adc = AdcGetNode(Bpsk->adc_num);
    if(Adc) {
        Bpsk->lost_block = 0;
        if(Adc->half_cplt_done) {
            Adc->half_cplt_done = false;
            res = proc_samples_to_mem(Bpsk, Adc->RxSamples,
                                      0,
                                      Adc->RxSamplesCnt/2);
            if( (Bpsk->half_cplt_done_cnt_prev+1)==Adc->half_cplt_done_cnt){

            }else{
                Bpsk->lost_block = Adc->half_cplt_done_cnt- Bpsk->half_cplt_done_cnt_prev-1;
                Bpsk->error_cnt++;
            }
            Bpsk->half_cplt_done_cnt_prev = Adc->half_cplt_done_cnt;
        }

        if(Adc->chan_conv_end) {
            Adc->chan_conv_end = false;
            res = proc_samples_to_mem(Bpsk, Adc->RxSamples,
                                      Adc->RxSamplesCnt/2,
                                      Adc->RxSamplesCnt);

            if( (Bpsk->chan_conv_end_cnt_prev+1)==Adc->chan_conv_end_cnt){

            }else{
                Bpsk->lost_block = Adc->chan_conv_end_cnt- Bpsk->chan_conv_end_cnt_prev-1;
                Bpsk->error_cnt++;
            }

            Bpsk->chan_conv_end_cnt_prev = Adc->chan_conv_end_cnt;
        }
    }
    return res;
}

bool bpsk_4fs_proc_from_adc_fifo(Bpsk4fsHandle_t* Node) {
    bool res = false;
    //log_level_t ll = log_level_get(LG_ADC);
    AdcHandle_t *Adc = AdcGetNode(Node->adc_num);
    if(Adc) {
        i_status ret;
        size_t size = 0;
        ret = iqueue_size(&Adc->iQueue, &size);
        if(I_OK == ret) {
            uint32_t i = 0;
            for (i = 0; i < size; i++) {
                uint16_t sample = 0;
                ret = iqueue_dequeue(&Adc->iQueue, (void*) &sample);
                if(I_OK == ret) {
                    //if(LOG_LEVEL_DEBUG == ll) {
                    //    cli_printf("\rAdc,Code:%4u,%5.3f V", sample, AdcSample12ToVoltageVef3_3(sample));
                    //}
                    int32_t x =(int32_t) sample;
                    int32_t y = 0;
                    res = dc_cut_filter_proc_sample(Node->dc_cut_filter_num, x,&y);
                    res = bpsk_4fs_decode_sample_ll(Node,  y);
                    Node->sam_n++;
                } else {
                    LOG_ERROR(LG_ADC, "FiFoPull,Err:%u=%s", ret, iQueueStatusToStr(ret));
                }
            }
        }
    }

    return res;
}
#endif

#ifdef HAS_ADC
bool super_cycle_proc_max_perf(void) {
    bool res = true;
    bpsk_4fs_proc_one(1);
    return res;
}
#endif

bool bpsk_4fs_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(BPSK_4FS, "%u,Proc", num);
    Bpsk4fsHandle_t* Node = Bpsk4fsGetNode(num);
    if(Node) {
#ifdef HAS_ADC
        res = bpsk_4fs_proc_from_adc_mem(Node);
        //res = bpsk_4fs_proc_from_adc(Node);
#endif
        Node->spin++;
    }
    return res;
}

COMPONENT_INIT_PATTERT(BPSK_4FS, BPSK_4FS, bpsk_4fs)
COMPONENT_PROC_PATTERT(BPSK_4FS, BPSK_4FS, bpsk_4fs)
