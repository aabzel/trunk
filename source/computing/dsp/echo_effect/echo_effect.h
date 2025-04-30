#ifndef ECHO_EFFECT_DRV_H
#define ECHO_EFFECT_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#include "echo_effect_diag.h"
#include "echo_effect_types.h"
#include "echo_effect_config.h"

EchoEffectHandle_t* EchoEffectGetNode(uint8_t num);
const EchoEffectConfig_t* EchoEffectGetConfig(uint8_t num);

bool echo_effect_factor_set(uint8_t num, double scale);
bool echo_effect_factor_get(uint8_t num, double* const scale);
bool echo_effect_init_one(uint8_t num);
bool echo_effect_reset(uint8_t num);
bool echo_effect_mcal_init(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*ECHO_EFFECT_DRV_H*/
