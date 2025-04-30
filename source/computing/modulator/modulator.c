#include "modulator.h"

#include "base16.h"
#include "modulator_diag.h"
#include "dds_drv.h"
#include "log.h"
#include "time_mcal.h"
#include "utils_math.h"

bool modulator_calc_samples(Modulator_t* instance, uint32_t part) {
     bool res = false;
     LOG_WARNING(MODULATOR, "CalcSamples %u...%u", instance->sample_per_tone*part,
                                                   instance->sample_per_tone*part+instance->sample_per_tone-1);
     uint32_t sample_period_ns = 0;
     uint32_t  max_time_ns = 0;
     DdsHandle_t* DacNode = DdsGetNode(instance->dac_num);
     if(0<instance->sampling_frequency_hz) {
         DacNode->sample_per_second = instance->sampling_frequency_hz;
         LOG_WARNING(MODULATOR, "CalcArray:  Freq:%u Hz Part: %u", instance->sampling_frequency_hz,part);
         LOG_INFO(MODULATOR, "SampleSize %u Byte", sizeof(SampleType_t));
         LOG_INFO(MODULATOR, "sample_per_tone %u", instance->sample_per_tone);
         sample_period_ns = 1000000000/instance->sampling_frequency_hz;
         LOG_INFO(MODULATOR, "SampleTime [%u] ns",sample_period_ns);
         if(DacNode) {
             LOG_INFO(MODULATOR, "Amplutude: %u Freq: %f Hz", DacNode->amplitude, DacNode->frequency);
             if( DacNode->frequency<(instance->sampling_frequency_hz/2)){
                 res = true;
                 max_time_ns = MSEC_2_NSEC(instance->tone_duration_ms)  ;
                 LOG_INFO(MODULATOR, "MaxTime %u ns %u us %u ms", max_time_ns,max_time_ns/1000, max_time_ns/1000000);

                 DacNode->sample_cnt = max_time_ns/sample_period_ns;
                 LOG_INFO(MODULATOR, "SampleCnt %u", DacNode->sample_cnt);
             }else {
                 LOG_ERROR(MODULATOR, "Freq TooBig %f Hz While Sampling  %f Hz",DacNode->frequency,instance->sampling_frequency_hz);
                 res = false;
             }
         } else {
             LOG_ERROR(MODULATOR, "NodeErr");
         }
     }else{
         LOG_ERROR(MODULATOR,"FreqErr %u",instance->sampling_frequency_hz);
     }

     if(res) {
         //memset(instance->samples, 0, DacNode->sample_cnt*sizeof(SampleType_t));
         res = false;
         LOG_INFO(MODULATOR, " [%u] samples", DacNode->sample_cnt);
         LOG_INFO(MODULATOR, " %u byte per sample", sizeof(SampleType_t));
         LOG_INFO(MODULATOR, " %u byte total", DacNode->sample_cnt*2*sizeof(SampleType_t));
         LOG_INFO(MODULATOR, "SampleMode %s", DdsMode2Str(DacNode->dac_mode));
         uint32_t cur_time_ns = 0;
         uint32_t s=0;
         for(s=0; cur_time_ns<= max_time_ns ; s++){
             cur_time_ns += sample_period_ns;
            SampleType_t tx_sample = 0;
            switch((uint8_t) DacNode->dac_mode){
                case DAC_MODE_SIN:{
                    res = true;
                    tx_sample = (SampleType_t)calc_sin_sample(cur_time_ns/1000, DacNode->frequency, DacNode->phase_ms,
                                                            DacNode->amplitude, DacNode->offset);
                }break;
                case DAC_MODE_CHIRP:{
                   // tx_sample = (SampleType_t)calc_chirp_sample(cur_time_ns/1000, DacNode->frequency, DacNode->amplitude );
                }break;
                default:
                    res = false;
                break;
            }

            instance->samples[instance->sample_per_tone*part+s] = tx_sample;
            res = true;
        }

     }
     return res;
}

/*8 byte */
bool modulator_modulate(Modulator_t* instance,
        const uint8_t* const raw_data, uint32_t data_size ){
    bool res = false;
    LOG_INFO(TEST, "ModulateData ToneDuration %f ms" ,instance->tone_duration_ms);
    /*Calc number of needed samples*/
    if(data_size<=8) {
        instance->symbol_cnt = data_size*2;
        LOG_INFO(TEST, "symbol_cnt %u",instance->symbol_cnt );
        instance->signal_duration_s = MSEC_2_SEC(instance->tone_duration_ms)*instance->symbol_cnt ;
        instance->sample_cnt = instance->signal_duration_s*( (double) instance->sampling_frequency_hz);
        instance->sample_per_tone =  instance->sample_cnt/instance->symbol_cnt;
        LOG_WARNING(MODULATOR,"SignalDuration %f s Samples %u",instance->signal_duration_s,instance->sample_cnt);

        res = base16_encode(raw_data, data_size, instance->base16_chunk);
        if(res){
            double cur_freq = 0.0;
            uint8_t t = 0;
            uint8_t tone_code=0;
            for(t=0; t<instance->symbol_cnt ; t++) {
                tone_code = base16_char_to_val(instance->base16_chunk[t]);
                cur_freq = instance->freq_step_hz + instance->freq_step_hz*tone_code;
                LOG_WARNING(MODULATOR,"ToneNumber %u-> %f Hz",tone_code,cur_freq);
                dds_set_sin(instance->dac_num, cur_freq, instance->amplitude, 0.0, 0.0);
                res = modulator_calc_samples(instance, t);
            }


            modulator_print_samples(instance);
        }

    }
    return res;
}

bool modulator_demodulate(Modulator_t instance,
        const SampleType_t* const x_signal,
        uint8_t* const raw_data, uint32_t * const data_size ){
    bool res = false;
    return res;
}
