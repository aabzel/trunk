#ifndef COMPUTING_INITIALIZE_H
#define COMPUTING_INITIALIZE_H

#include "std_includes.h"

#ifndef HAS_COMPUTING
#error  "+HAS_COMPUTING"
#endif

#ifdef HAS_DDS
#include "dds.h"
bool DDS_init(void);

#define DDS_INITIALIZE {.init_function=DDS_init, .name="EhalDDS",},

#else
#define DDS_INITIALIZE
#endif /*HAS_DDS*/

#ifdef HAS_DSP
#include "dsp.h"
#else
#define DSP_INITIALIZE
#endif /*HAS_DSP*/

#ifdef HAS_PYRAMID_ACCEL_CALIBRATION
#include "pyramid_accel_calibration.h"

bool PYRAMID_ACCEL_CALIBRATION_init(void);

#define PYRAMID_ACCEL_CALIBRATION_INITIALIZE                         \
    {                                                                \
        .init_function = PYRAMID_ACCEL_CALIBRATION_init,             \
        .name="EhalPyrAccCalib",                                     \
    },

#else
#define PYRAMID_ACCEL_CALIBRATION_INITIALIZE
#endif /*HAS_PYRAMID_ACCEL_CALIBRATION*/


#define COMPUTING_INITIALIZE   \
    DDS_INITIALIZE             \
    DSP_INITIALIZE             \
    PYRAMID_ACCEL_CALIBRATION_INITIALIZE




#endif /* COMPUTING_INITIALIZE_H */
