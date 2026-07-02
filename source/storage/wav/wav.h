#ifndef WAV_H
#define WAV_H

#include "std_includes.h"

#include "wav_types.h"
#include "dds_type.h"
#include "dsp_types.h"
#include "wav_config.h"

#ifdef HAS_WAV_DIAG
#include "wav_diag.h"
#endif

// API
const WavConfig_t* WavGetConfig(uint8_t num);
WavHandle_t* WavGetNode(uint8_t num);
bool wav_mcal_init(void);
bool wav_init_one(uint8_t num);

//getters
bool WavHeaderToNode(const  WavHeader_t* const Header, WavHandle_t* const Node);
bool wav_info_ll(WavHeader_t* const Header, const char* const file_name);
bool wav_info_sample(const char* const file_name);
bool wav_info(const char* const file_name);

// setters
bool wav_load(uint8_t wav_num, const char* const file_name);
bool wav_generate_1_channel(uint8_t wav_num, uint8_t dds1_num);
bool wav_generate_2_channel(uint8_t wav_num, uint8_t dds1_num, uint8_t dds2_num);
bool wav_samples_save(const WavHeader_t* const Header,
                       const SampleType_t* const  sample,
                       const uint32_t sample_cnt, uint32_t repetitions);

bool wav_proc_fir_sample(const char* const file_name, uint8_t fir_num);
bool wav_proc_iir_sample(const char* const file_name, uint8_t iir_num);
bool wav_generate(uint8_t num, uint8_t dds);

bool wav_compose_header_by_dds(DdsHandle_t* const DDs,
                               WavHeader_t* const Header);

#endif /* WAV_H */
