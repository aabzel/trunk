#ifndef QUADRATURE_MIXER_CONFIG_H
#define QUADRATURE_MIXER_CONFIG_H

#include "std_includes.h"
#include "quadrature_mixer_types.h"

extern const QuadratureMixerConfig_t QuadratureMixerConfig[];
extern QuadratureMixerHandle_t QuadratureMixerInstance[];

uint32_t quadrature_mixer_get_cnt(void);

#endif /* QUADRATURE_MIXER_CONFIG_H  */
