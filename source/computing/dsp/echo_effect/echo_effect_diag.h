#ifndef ECHO_EFFECT_DIAG_H
#define ECHO_EFFECT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include  "echo_effect_types.h"

bool echo_effect_diag(uint8_t num);
const char* EchoEffectConfigToStr(const EchoEffectConfig_t* const Config);
const char* EchoEffectNodeToStr(const EchoEffectHandle_t* const Node);


#ifdef __cplusplus
}
#endif

#endif /* ECHO_EFFECT_DIAG_H */
