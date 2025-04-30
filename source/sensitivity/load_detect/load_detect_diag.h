
#ifndef LOAD_DETECT_DIAG_H
#define LOAD_DETECT_DIAG_H

#include "load_detect_types.h"

const char* LoadDetectOut2Str(LoadDetectOut_t decision);
const char* LoadDetectGpioClass2Str(GpioClass_t gpio_class);

bool load_detect_diag(void);
bool load_detect_pin_diag(void);

#endif /* LOAD_DETECT_DIAG_H  */
