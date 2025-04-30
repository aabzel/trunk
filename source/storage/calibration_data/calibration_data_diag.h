#ifndef CALIBRATION_DATA_DIAG_H
#define CALIBRATION_DATA_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "calibration_data_types.h"

const char* CalibrationData2Str(const CalibrationData_t * const Node);
bool calibration_data_diag(void);

#ifdef __cplusplus
}
#endif

#endif /* CALIBRATION_DATA_DIAG_H */
