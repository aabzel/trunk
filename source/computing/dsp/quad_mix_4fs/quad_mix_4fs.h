#ifndef QUAD_MIX_4FS_H
#define QUAD_MIX_4FS_H

#include "std_includes.h"
#include "quad_mix_4fs_config.h"
#include "quad_mix_4fs_types.h"

#ifdef HAS_QUAD_MIX_4FS_DIAG
#include "quad_mix_4fs_diag.h"
#endif

QuadMix4fsHandle_t* QuadMix4fsGetNode(uint8_t num);
const QuadMix4fsConfig_t* QuadMix4fsGetConfig(uint8_t num);

bool quad_mix_4fs_lpf_iir(uint8_t num, int32_t k);

bool quad_mix_4fs_init_one(uint8_t num);
bool quad_mix_4fs_mcal_init(void);
bool quad_mix_4fs_proc_sample_ll(QuadMix4fsHandle_t* const Node,
                                 int32_t time_s,
                                 int32_t sample);

bool quad_mix_4fs_proc_sample(uint8_t num,
                              int32_t time_s,
                              int32_t sample);

/*getter*/
float calc_carrier_phase_err_lut_rad(const int32_t i_val, const int32_t q_val);
bool quad_mix_4fs_is_valid_iq(const QuadMix4fsHandle_t* const Node);
bool is_valid_phase_err_rad(const float phase_error_rad);

bool quad_mix_4fs_calc_phase_error_vector_angle(QuadMix4fsHandle_t* const Node);
float calc_carrier_phase_err_rad(const float i_val, const float q_val);
float quad_mix_4fs_calc_phase_error_atan(QuadMix4fsHandle_t* const Node);

#endif
