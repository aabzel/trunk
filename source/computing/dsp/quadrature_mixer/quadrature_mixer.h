#ifndef QUADRATURE_MIXER_H
#define QUADRATURE_MIXER_H


#include "std_includes.h"
#include "quadrature_mixer_config.h"
#include "quadrature_mixer_types.h"
#ifdef HAS_QUADRATURE_MIXER_DIAG
#include "quadrature_mixer_diag.h"
#endif

QuadratureMixerHandle_t* QuadratureMixerGetNode(uint8_t num);

bool quadrature_mixer_lpf_iir(uint8_t num, double k);

const QuadratureMixerConfig_t* QuadratureMixerGetConfig(uint8_t num);
bool quadrature_mixer_init_one(uint8_t num);
bool quadrature_mixer_mcal_init(void);
bool quadrature_mixer_proc_sample_ll(QuadratureMixerHandle_t* const Node,
                                     double time_s,
                                     double carrier_frequency_hz,
                                     double lo_phase_rad,
                                     double sample) ;
bool quadrature_mixer_proc_sample(uint8_t num,
		                          double time_s,
                                  double carrier_frequency_hz,
                                  double lo_phase_rad,
								  double sample);

#endif
