#ifndef COMPUTING_CLI_H
#define COMPUTING_CLI_H

#ifdef HAS_LOG
#include "log.h"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef COMPUTING_IN_USE
#error "+HAS_COMPUTING"
#endif

#ifndef COMPUTING_CLI_IN_USE
#error "+HAS_COMPUTING_COMMANDS"
#endif

#ifdef DDS_CLI_IN_USE
#include "dds_cli.h"
#else
#define DDS_CLI
#endif

#ifdef DSP_CLI_IN_USE
#include "dsp_cli.h"
#else
#define DSP_CLI
#endif

#ifdef PYRAMID_ACCEL_CALIBRATION_CLI_IN_USE
#include "pyramid_accel_calibration_cli.h"
#else
#define PYRAMID_ACCEL_CALIBRATION_CLI
#endif


#define COMPUTING_CLI  \
    DDS_CLI            \
    DSP_CLI            \
    PYRAMID_ACCEL_CALIBRATION_CLI

#endif /* COMPUTING_CLI_H */
