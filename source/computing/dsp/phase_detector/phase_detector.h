#ifndef PHASE_DETECTOR_H
#define PHASE_DETECTOR_H


#include <std_includes.h>

#include "phase_detector_config.h"
#include "phase_detector_types.h"
#include "phase_detector_diag.h"

// API
bool phase_detector_half_cos(double freq_signal, const char* const file_name);
PhaseDetectorHandle_t* PhaseDetectorGetNode(uint8_t num);
const PhaseDetectorConfig_t* PhaseDetectorGetConfig(uint8_t num);
bool phase_detector_init_one(uint8_t num);
bool phase_detector_mcal_init(void);

bool phase_detector_proc_file(double f_signal, const char* const file_name);

#endif
