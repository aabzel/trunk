
#ifndef PHASE_DETECTOR_CONFIG_H
#define PHASE_DETECTOR_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "phase_detector_types.h"

extern const PhaseDetectorConfig_t PhaseDetectorConfig[];
extern PhaseDetectorHandle_t PhaseDetectorInstance[];

uint32_t phase_detector_get_cnt(void);

#endif /* PHASE_DETECTOR_CONFIG_H */
