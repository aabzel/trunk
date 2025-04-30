#ifndef ECHO_EFFECT_CONFIG_H
#define ECHO_EFFECT_CONFIG_H

#include <stdbool.h>

#include "echo_effect_types.h"

extern const EchoEffectConfig_t EchoEffectConfig[];
extern EchoEffectHandle_t EchoEffectInstance[];

uint32_t echo_effect_get_cnt(void);

#endif /* ECHO_EFFECT_CONFIG_H  */
