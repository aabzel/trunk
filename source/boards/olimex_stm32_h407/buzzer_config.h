#ifndef BUZZER_CONFIG_H
#define BUZZER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "buzzer_types.h"
#include "buzzer_dep.h"

extern const BuzzerConfig_t BuzzerConfig[];
extern BuzzerHandle_t BuzzerInstance[];

uint32_t buzzer_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* BUZZER_CONFIG_H */
