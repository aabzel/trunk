#ifndef PDM_CONFIG_H
#define PDM_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "pdm_types.h"

#define PDM_SAMPLE_COUNT 1024

extern const PdmConfig_t PdmConfig[];
extern PdmHandle_t PdmInstance[];

uint32_t pdm_get_cnt(void);

#endif /* PDM_CONFIG_H  */
