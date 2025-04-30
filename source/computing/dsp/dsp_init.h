#ifndef DSP_INIT_H
#define DSP_INIT_H

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_DSP
#error  "+HAS_DSP"
#endif


#ifdef HAS_DECIMATOR
#include "decimator.h"
#define DECIMATOR_INIT {.init_function=decimator_mcal_init, .name="Decimator",},
#else
#define DECIMATOR_INIT
#endif /*HAS_DECIMATOR*/

#ifdef HAS_DELTA_SIGMA
#include "delta_sigma.h"
#define DELTA_SIGMA_INIT {.init_function=delta_sigma_mcal_init, .name="DeltaSigma",},
#else
#define DELTA_SIGMA_INIT
#endif /*HAS_DELTA_SIGMA*/

#ifdef HAS_ECHO_EFFECT
#include "echo_effect.h"
#define ECHO_EFFECT_INIT {.init_function=echo_effect_mcal_init, .name="EchoEeffect",},
#else
#define ECHO_EFFECT_INIT
#endif /*HAS_SCHMITT_TRIGGER*/

#ifdef HAS_FIR
#include "fir.h"
#define FIR_INIT {.init_function=fir_mcal_init, .name="Fir",},
#else
#define FIR_INIT
#endif /*HAS_FIR*/

#ifdef HAS_FIR_INT
#include "fir_int.h"
#define FIR_INT_INIT {.init_function=fir_int_mcal_init, .name="FirInt",},
#else
#define FIR_INT_INIT
#endif /*HAS_FIR_INT*/

#ifdef HAS_FOURIER_SERIES
#include "fourier_series.h"
#define FOURIER_SERIES_INIT   {.init_function=fourier_series_mcal_init, .name="FourierSeries",},
#else
#define FOURIER_SERIES_INIT
#endif /*HAS_FOURIER_SERIES*/

#ifdef HAS_IIR
#include "iir.h"
#define IIR_INIT {.init_function=iir_mcal_init, .name="Iir",},
#else
#define IIR_INIT
#endif /*HAS_IIR*/

#ifdef HAS_SCAN
#include "scan.h"
#define SCAN_INIT {.init_function=scan_mcal_init, .name="Scan",},
#else
#define SCAN_INIT
#endif /*HAS_IIR*/


#ifdef HAS_PHASE_DETECTOR
#include "phase_detector.h"
#define PHASE_DETECTOR_INIT {.init_function=phase_detector_mcal_init, .name="PhaseDetector",},
#else
#define PHASE_DETECTOR_INIT
#endif /*HAS_SCHMITT_TRIGGER*/

#ifdef HAS_SCHMITT_TRIGGER
#include "schmitt_trigger.h"
#define SCHMITT_TRIGGER_INIT {.init_function=schmitt_trigger_mcal_init, .name="SchmittTrigger",},
#else
#define SCHMITT_TRIGGER_INIT
#endif /*HAS_SCHMITT_TRIGGER*/

#ifdef HAS_QUADRATURE_MIXER
#include "quadrature_mixer.h"
#define QUADRATURE_MIXER_INIT {.init_function=quadrature_mixer_mcal_init, .name="QuadratureMixer",},
#else
#define QUADRATURE_MIXER_INIT
#endif /*HAS_QUADRATURE_MIXER*/

// order matter!
#define DSP_INIT           \
    DECIMATOR_INIT         \
    DELTA_SIGMA_INIT       \
    SCHMITT_TRIGGER_INIT   \
    FOURIER_SERIES_INIT    \
    FIR_INIT               \
    FIR_INT_INIT           \
    IIR_INIT               \
    QUADRATURE_MIXER_INIT  \
    PHASE_DETECTOR_INIT    \
    SCAN_INIT              \
    ECHO_EFFECT_INIT

#endif /* DSP_INIT_H */
