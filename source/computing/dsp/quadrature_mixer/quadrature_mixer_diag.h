#ifndef QUADRATURE_MIXER_DIAG_H
#define QUADRATURE_MIXER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include <std_includes.h>
#include "quadrature_mixer_types.h"


const char* QuadratureMixerNodeToStr(const  QuadratureMixerHandle_t* const Node);
const char* QuadratureMixerConfigToStr(const  QuadratureMixerConfig_t* const Config);

bool QuadratureMixerDiagConfig(const QuadratureMixerConfig_t* const Config);
bool quadrature_mixer_diag(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* QUADRATURE_MIXER_DIAG_H */
