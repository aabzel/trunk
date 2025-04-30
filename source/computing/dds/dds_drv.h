#ifndef DDS_SC_H
#define DDS_SC_H

#include "std_includes.h"
#include "dds_config.h"
#include "dds_type.h"

#ifdef HAS_DDS_DIAG
#include "dds_diag.h"
#endif


/*API*/
bool dds_mcal_init(void);
bool dds_proc(void);
bool dds_proc_one(uint8_t num);
bool dds_init_one(uint8_t num);
const DdsConfig_t* DdsGetConfig(uint8_t num);
DdsHandle_t* DdsGetNode(uint8_t num);


int16_t dds_calc_sample_s16(double t_s, DdsHandle_t* const Node);
int16_t dds_calc_sin_sample_s16(double t_s, DdsHandle_t* const Node);
bool dds_player_set(uint8_t num,DdsPlayer_t player);
bool dds_match_sample_size(const DdsHandle_t* const Node, uint8_t sample_bitness);
bool dds_pattern_set(uint8_t num, FramePattern_t frame_pattern);
bool dds_rev_hwords(uint8_t num);
bool dds_rev_bytes(uint8_t num);
bool dds_rev_bytes(uint8_t num);

bool dds_phase_set(uint8_t num, double phase_s);
bool dds_set_phase_ms(uint8_t num, double phase_ms);
bool dds_shift_signal(uint8_t num, double phase_s);
bool dds_set_fps(uint8_t num, uint32_t fps);
bool dds_stop(uint8_t num);
bool dds_i2s_play1khz(uint8_t num, uint8_t i2s_num, SampleType_t amplitude, uint64_t duration_ms);
bool dds_set_array_ext(uint8_t num, uint32_t fps, SampleType_t* array, uint32_t size);
bool dds_play1khz(uint8_t num, SampleType_t amplitude, double offset, double phase);
bool dds_play(uint8_t num, uint64_t duration_ms);
bool dds_set_chirp(uint8_t num, double chirp_duration_s, double frequency1, double frequency2);
bool dds_set_array(uint8_t num, uint32_t periods, uint32_t min_abs_period_ns);
bool dds_set_static_period_48k_1000hz_word(uint8_t num);
bool dds_proc_sample(uint8_t num, SampleType_t* out_sample);
bool dds_reset_values(void);
bool dds_set_sample(uint8_t num, SampleType_t sample);
bool dds_set_pwm(uint8_t num, double frequency, SampleType_t amplitude, double duty_cycle, double phase,
                    double offset);

bool dds_set_fence(uint8_t num, double des_frequency, SampleType_t des_amplitude, double des_phase,
                      double des_off_set);
bool dds_set_saw(uint8_t num, double des_frequency, SampleType_t des_amplitude, double des_phase,
                    double des_off_set);
bool dds_set_sin(uint8_t num, double des_frequency, SampleType_t amplitude, double des_phase, SampleType_t offset);

int16_t DdsPlayerToI2sNum(DdsPlayer_t player) ;
uint32_t DdsFramePatToNumChann(FramePattern_t frame_pattern);

#endif /*DDS_SC_H*/
