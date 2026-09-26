#ifndef ANALOG_MISC_H
#define ANALOG_MISC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "analog_misc_types.h"

float AnalogSample12ToVoltageVef3_3(const uint32_t sample);

#ifdef __cplusplus
}
#endif

#endif /* ANALOG_MISC_H */
