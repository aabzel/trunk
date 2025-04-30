#ifndef QUADRATURE_MIXER_ISR_H
#define QUADRATURE_MIXER_ISR_H

#include <stdbool.h>
#include <stdint.h>

#include "quadrature_mixer_types.h"

bool quadrature_mixer_pop_ll(QuadratureMixerHandle_t *Node, QuadratureMixerSample_t x0, QuadratureMixerSample_t *const out) ;

bool quadrature_mixer_proc_in_out_ll(QuadratureMixerHandle_t *Node, QuadratureMixerSample_t x, QuadratureMixerSample_t *const y);
bool quadrature_mixer_proc_in_out(uint8_t num, QuadratureMixerSample_t x0, QuadratureMixerSample_t* const y);

bool quadrature_mixer_proc_in_out_array(uint8_t num,
                           uint32_t size,
                           const QuadratureMixerSample_t* const x,
                           QuadratureMixerSample_t* const y);

#endif
