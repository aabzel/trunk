
#ifndef CALIBRATION_DATA_H
#define CALIBRATION_DATA_H

#include <stdbool.h>
#include <stdint.h>

#include "data_types.h"
#include "flash_drv.h"
#include "calibration_data_config.h"
#include "calibration_data_types.h"
#include "calibration_data_diag.h"

#ifdef HAS_CALIBRATION_DATA_WRITE
bool calibration_data_erase(void);
bool calibration_data_set(const void* const data);
#endif

bool calibration_data_init(void);
bool calibration_data_get(void* const data);


#endif /* CALIBRATION_DATA_H */
