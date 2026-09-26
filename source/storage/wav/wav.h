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
WavHandle_t* WavGetNode(uint8_t num);
const WavConfig_t* WavGetConfig(uint8_t num);
bool wav_mcal_init(void);
bool wav_init_one(uint8_t num);
bool WavHeaderToInfo(const WavHeader_t* const Header, WavInfo_t* const Info);

//getters
bool wav_is_valid_header(const WavHeader_t* const pHeader) ;
bool wav_read_file_metadata(const char* const file_name, WavInfo_t* const Info);
bool WavHeaderToNode(const  WavHeader_t* const Header, WavHandle_t* const Node);
bool wav_info_ll(WavHeader_t* const Header, const char* const file_name);
bool wav_info_sample(const char* const file_name);
bool wav_info(const char* const file_name);
uint32_t WavHeaderToFrameSize( WavHeader_t* Header) ;
uint32_t WavHeaderToPlayDurationMs(const WavHeader_t* const pHeader);
uint32_t wav_sampling_frequency_get(uint8_t num);
uint32_t wav_sampling_frequency_hz(const char* const file_name);
float wav_read_file_duration(const char* const file_name);
float wav_duration_get(uint8_t num) ;

// setters
bool wav_file_name_set(const uint32_t num, const char* const new_file_name);
bool wav_header_to_handle(const WavHeader_t* const pHeader,
                          WavHandle_t* const pHandle);
#ifdef HAS_PC
bool wav_shift_right_sample_pc(const char* const file_name, uint32_t samples);
#endif
bool wav_dds_to_name(char* const name, const uint32_t size, const uint8_t dds_num,const char* const prefix) ;

bool wav_shift_right_sample(const char* const file_name,
                            const char* const new_file_name,
                            uint32_t samples);

bool wav_shift_right(const char* const file_name, float duratuin_s);
bool wav_shift_right2(uint8_t num, const float duratuin_s);
bool wav_duration_set(uint8_t num, float duratuin_s) ;
bool wav_sampling_frequency_set(uint8_t num, uint32_t sampling_frequency_hz);
bool wav_load(uint8_t wav_num, const char* const file_name);
bool wav_generate(uint8_t num, char* name, uint8_t dds);
bool wav_generate_signal(const uint8_t num, const uint8_t dds_num, char* prefix);
bool wav_generate_1_channel(uint8_t wav_num, uint8_t dds1_num);
bool wav_generate_2_channel(uint8_t wav_num, uint8_t dds1_num, uint8_t dds2_num, float duratuin_s) ;
bool wav_samples_save(const WavHeader_t* const Header,
                       const SampleType_t* const  sample,
                       const uint32_t sample_cnt, uint32_t repetitions);

bool wav_proc_fir_sample(const char* const file_name, uint8_t fir_num);
bool wav_proc_iir_sample(const char* const file_name, uint8_t iir_num);


bool wav_compose_header_by_dds(DdsHandle_t* const DDs,
                               WavHeader_t* const Header);

#endif /* WAV_H */
