#ifndef SW_DAC_DRIVER_H
#define SW_DAC_DRIVER_H

#include <stdbool.h>
#include <stdint.h>

#include "sw_dac_config.h"
#include "sw_dac_types.h"

#ifdef HAS_SW_DAC_DIAG
#include "sw_dac_diag.h"
#endif

#ifndef HAS_ALLOCATOR
#warning "+HAS_ALLOCATOR"
#endif /*HAS_ALLOCATOR*/

#ifndef HAS_SW_DAC
#error "+HAS_SW_DAC"
#endif /*HAS_SW_DAC*/

#ifndef HAS_MATH
#error "+HAS_MATH"
#endif /*HAS_MATH*/

#if 1
#define FREE_FUN h_free
#define MALLOC_FUN h_malloc
#else
#define FREE_FUN free
#define MALLOC_FUN malloc
#endif

bool sw_dac_match_sample_size(const SwDac_t* const Node, uint8_t sample_bitness);
bool sw_dac_pattern_set(uint8_t num, FramePattern_t frame_pattern);
bool sw_dac_rev_bytes(uint8_t num);
bool sw_dac_rev_hwords(uint8_t num);
bool sw_dac_set_fps(uint8_t num, uint32_t fps);

bool sw_dac_set_array(uint8_t num, uint32_t periods, uint32_t min_abs_period_ns);
bool sw_dac_set_static_period_48k_1000hz_word(uint8_t num);
bool sw_dac_proc(uint8_t num, SampleType_t* out_sample);
bool sw_dac_reset_values(void);
bool sw_dac_set_sample(uint8_t num, SampleType_t sample);
bool sw_dac_set_pwm(uint8_t num, double frequency, SampleType_t amplitude, double duty_cycle, double phase,
                    double offset);

bool sw_dac_set_fence(uint8_t num, double des_frequency, SampleType_t des_amplitude, double des_phase,
                      double des_off_set);
bool sw_dac_set_saw(uint8_t num, double des_frequency, SampleType_t des_amplitude, double des_phase,
                    double des_off_set);
bool sw_dac_set_sin(uint8_t num, double des_frequency, SampleType_t amplitude, double des_phase, SampleType_t offset);

bool sw_dac_init(void);
const SwDacConfig_t* SwDacGetConfig(uint8_t num);
SwDac_t* SwDacGetNode(uint8_t num);

#endif /*SW_DAC_DRIVER_H*/
