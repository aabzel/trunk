#include "analog_misc.h"

#include "std_includes.h"

#ifdef HAS_LOG
#include "log.h"
#endif

/* 0 - 0.0 V
   4095 -3.3 V */
float AnalogSample12ToVoltageVef3_3(const uint32_t sample) {
    float voltage_v = 0.0f;
    voltage_v = (3.3f *( (float) sample))/((float)ANALOG_MAX_VAL_12BIT);
    return voltage_v;
}
