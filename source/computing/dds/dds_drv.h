#ifndef DDS_SC_H
#define DDS_SC_H

#include "std_includes.h"
#include "dds_type.h"
#include "dds_config.h"

#ifdef HAS_DDS_DIAG
#include "dds_diag.h"
#endif


/*API*/
DdsHandle_t* DdsGetNode(uint8_t num);
const DdsConfig_t* DdsGetConfig(uint8_t num);
bool dds_mcal_init(void);
bool dds_proc(void);
bool dds_proc_one(uint8_t num);
bool dds_init_one(uint8_t num);
bool dds_is_init(uint8_t num);

/*getters*/
float dds_signal_duration_get(uint8_t num);
float dds_sample_frequency_get(const uint8_t num);
uint8_t i2s_num_to_dds_num(uint8_t i2s_num);
bool dds_calc_one_sample(DdsHandle_t* Node, uint64_t time_us, SampleType_t* tx_sample);

int16_t dds_calc_sample_s16(float t_s, DdsHandle_t* const Node);
int16_t dds_calc_sin_sample_s16(float t_s, DdsHandle_t* const Node);
float dds_signal_diration_get(uint8_t num );
bool dds_player_set(uint8_t num,InterfaceType_t player);
bool dds_match_sample_size(const DdsHandle_t* const Node, uint8_t sample_bitness);
bool dds_pattern_set(uint8_t num, FramePattern_t frame_pattern);
bool dds_rev_hwords(uint8_t num);
bool dds_rev_bytes(uint8_t num);
bool dds_rev_bytes(uint8_t num);

/*setter*/
bool dds_signal_duration_set(uint8_t num, float signal_duration_s);
bool dds_sample_frequency_set(uint8_t num, float sample_frequency_hz);
bool dds_play_con(uint8_t num) ;
bool dds_stop(uint8_t num);
bool dds_set_fps(uint8_t num, uint32_t fps);
bool dds_set_array_ext(uint8_t num, uint32_t fps, SampleType_t* array, uint32_t size);
bool dds_phase_set(uint8_t num, float phase_s);
bool dds_set_phase_ms(uint8_t num, float phase_ms);
bool dds_shift_signal(uint8_t num, float phase_s);
bool dds_play1khz(uint8_t num, SampleType_t amplitude, float offset, float phase);
bool dds_play(uint8_t num, uint64_t duration_ms);

bool dds_set_m_seq(uint8_t num, uint8_t m_seq_num, float amplitude,
                   float carrier_frequency_hz, uint32_t periods_per_chip) ;

bool dds_set_barker13(uint8_t num,
                      float amplitude,
                      float carrier_frequency_hz,
                      uint32_t periods_per_chip);

bool dds_duration_set(uint8_t num, float signal_duration_s);
bool dds_set_chirp(uint8_t num, float amplitude, float chirp_duration_s, float frequency1, float frequency2);
bool dds_frequency_set(uint8_t num, float frequency_hz);
bool dds_set_array(uint8_t num, uint32_t periods, uint32_t min_abs_period_ns);
bool dds_set_static_period_48k_1000hz_word(uint8_t num);
bool dds_reset_values(void);
bool dds_set_sample(uint8_t num, SampleType_t sample);
bool dds_proc_sample(uint8_t num, SampleType_t* out_sample);
#ifdef HAS_I2S
bool dds_i2s_play1khz(uint8_t num, uint8_t i2s_num, SampleType_t amplitude, uint64_t duration_ms);
#endif
bool dds_set_pwm(uint8_t num, float frequency, SampleType_t amplitude, float duty_cycle, float phase,
                    float offset);
bool dds_set_fence(uint8_t num, float des_frequency, SampleType_t des_amplitude, float des_phase,
                      float des_off_set);
bool dds_set_saw(uint8_t num, float des_frequency, SampleType_t des_amplitude, float des_phase,
                    float des_off_set);
bool dds_set_sin(uint8_t num, float des_frequency, SampleType_t amplitude, float des_phase, SampleType_t offset);

#if 0
int16_t DdsPlayerToI2sNum(DdsPlayer_t player) ;
#endif
uint32_t DdsFramePatToNumChann(FramePattern_t frame_pattern);
uint32_t dds_calc_max_time_ns(DdsHandle_t* Node, uint32_t periods);
float  DdsPhaseMsToRad(float Fs, float phase_ms) ;

#endif /*DDS_SC_H*/
