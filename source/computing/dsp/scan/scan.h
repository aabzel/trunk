#ifndef SCAN_DRIVER_H
#define SCAN_DRIVER_H

#include "std_includes.h"
#include "scan_config.h"
#include "scan_types.h"
#include "scan_diag.h"

bool scan_proc_val(uint8_t num, float value_in, ScanAction_t* const action);
bool scan_mcal_init(void);

const ScanConfig_t* ScanGetConfig(uint8_t num);
ScanHandle_t* ScanGetNode(uint8_t num);

#endif /* SCAN_DRIVER_H  */
