#ifndef DSP_COMMANDS_H
#define DSP_COMMANDS_H

#ifdef HAS_LOG
#include "log.h"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_DSP
#error "+HAS_DSP"
#endif

#ifndef HAS_DSP_COMMANDS
#error "+HAS_DSP_COMMANDS"
#endif

#ifdef HAS_ECHO_EFFECT_COMMANDS
#include "echo_effect_commands.h"
#else
#define ECHO_EFFECT_COMMANDS
#endif

#ifdef HAS_DECIMATOR_COMMANDS
#include "decimator_commands.h"
#else
#define DECIMATOR_COMMANDS
#endif

#ifdef HAS_DELTA_SIGMA_COMMANDS
#include "delta_sigma_commands.h"
#else
#define DELTA_SIGMA_COMMANDS
#endif

#ifdef HAS_FIR_COMMANDS
#include "fir_commands.h"
#else
#define FIR_COMMANDS
#endif

#ifdef HAS_FIR_INT_COMMANDS
#include "fir_int_commands.h"
#else
#define FIR_INT_COMMANDS
#endif

#ifdef HAS_FOURIER_SERIES_COMMANDS
#include "fourier_series_commands.h"
#else
#define FOURIER_SERIES_COMMANDS
#endif

#ifdef HAS_IIR_COMMANDS
#include "iir_commands.h"
#else
#define IIR_COMMANDS
#endif

#ifdef HAS_QUADRATURE_MIXER_COMMANDS
#include "quadrature_mixer_commands.h"
#else
#define QUADRATURE_MIXER_COMMANDS
#endif

#ifdef HAS_SCHMITT_TRIGGER_COMMANDS
#include "schmitt_trigger_commands.h"
#else
#define SCHMITT_TRIGGER_COMMANDS
#endif

#ifdef HAS_PHASE_DETECTOR_COMMANDS
#include "phase_detector_commands.h"
#else
#define PHASE_DETECTOR_COMMANDS
#endif


#define DSP_COMMANDS            \
    DECIMATOR_COMMANDS          \
    DELTA_SIGMA_COMMANDS        \
    ECHO_EFFECT_COMMANDS        \
    FOURIER_SERIES_COMMANDS     \
    FIR_COMMANDS                \
    PHASE_DETECTOR_COMMANDS     \
    FIR_INT_COMMANDS            \
    IIR_COMMANDS                \
    QUADRATURE_MIXER_COMMANDS   \
    SCHMITT_TRIGGER_COMMANDS

#endif /* DSP_COMMANDS_H */
