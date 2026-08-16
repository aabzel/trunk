#ifndef DSP_INIT_H
#define DSP_INIT_H

#include "std_includes.h"

#ifndef HAS_DSP
#error  "+HAS_DSP"
#endif

#ifdef HAS_SLIDING_INTEGRAL
#include "sliding_integral.h"
#define SLIDING_INTEGRAL_INIT {.init_function=sliding_integral_mcal_init, .name="SlidingIntegral",},
#else
#define SLIDING_INTEGRAL_INIT
#endif

#ifdef HAS_CORRELATOR_NAIV_S16
#include "correlator_naiv_s16.h"
#define CORRELATOR_NAIV_S16_INIT {.init_function = correlator_naiv_s16_mcal_init, .name="CorrelatorNaivS16",},
#else
#define CORRELATOR_NAIV_S16_INIT
#endif

#ifdef HAS_DECIMATOR
#include "decimator.h"
#define DECIMATOR_INIT {.init_function=decimator_mcal_init, .name="Decimator",},
#else
#define DECIMATOR_INIT
#endif

#ifdef HAS_CORRELATOR_S16
#include "correlator_s16.h"
#define CORRELATOR_S16_INIT {.init_function=correlator_s16_mcal_init, .name="CorrelatorS16",},
#else
#define CORRELATOR_S16_INIT
#endif

#ifdef HAS_DELTA_SIGMA
#include "delta_sigma.h"
#define DELTA_SIGMA_INIT {.init_function=delta_sigma_mcal_init, .name="DeltaSigma",},
#else
#define DELTA_SIGMA_INIT
#endif

#ifdef HAS_ECHO_EFFECT
#include "echo_effect.h"
#define ECHO_EFFECT_INIT {.init_function=echo_effect_mcal_init, .name="EchoEeffect",},
#else
#define ECHO_EFFECT_INIT
#endif

#ifdef HAS_MEDIAN_FILTER
#include "median_filter.h"
#define MEDIAN_FILTER_INIT {.init_function=median_filter_mcal_init, .name="MedianFilter",},
#else
#define MEDIAN_FILTER_INIT
#endif


#ifdef HAS_MEDIAN_FILTER_FAST
#include "median_filter_fast.h"
#define MEDIAN_FILTER_FAST_INIT {.init_function=median_filter_fast_mcal_init, .name="MedianFilterFast",},
#else
#define MEDIAN_FILTER_FAST_INIT
#endif


#ifdef HAS_FIR
#include "fir.h"
#define FIR_INIT {.init_function=fir_mcal_init, .name="Fir",},
#else
#define FIR_INIT
#endif

#ifdef HAS_FIR_INT
#include "fir_int.h"
#define FIR_INT_INIT {.init_function=fir_int_mcal_init, .name="FirInt",},
#else
#define FIR_INT_INIT
#endif

#ifdef HAS_FOURIER_SERIES
#include "fourier_series.h"
#define FOURIER_SERIES_INIT   {.init_function=fourier_series_mcal_init, .name="FourierSeries",},
#else
#define FOURIER_SERIES_INIT
#endif

#ifdef HAS_IIR
#include "iir.h"
#define IIR_INIT {.init_function=iir_mcal_init, .name="Iir",},
#else
#define IIR_INIT
#endif

#ifdef HAS_SCAN
#include "scan.h"
#define SCAN_INIT {.init_function=scan_mcal_init, .name="Scan",},
#else
#define SCAN_INIT
#endif


#ifdef HAS_PHASE_DETECTOR
#include "phase_detector.h"
#define PHASE_DETECTOR_INIT {.init_function=phase_detector_mcal_init, .name="PhaseDetector",},
#else
#define PHASE_DETECTOR_INIT
#endif

#ifdef HAS_MANCHESTER_DECODE
#include "manchester_decode_mcal.h"
#define MANCHESTER_DECODE_INIT {.init_function=manchester_decode_mcal_init, .name="ManchesterDecode",},
#else
#define MANCHESTER_DECODE_INIT
#endif

#ifdef HAS_DC_CUT_FILTER
#include "dc_cut_filter_mcal.h"
#define DC_CUT_FILTER_INIT {.init_function=dc_cut_filter_mcal_init, .name="DcCutFilter",},
#else
#define DC_CUT_FILTER_INIT
#endif

#ifdef HAS_SCHMITT_TRIGGER
#include "schmitt_trigger.h"
#define SCHMITT_TRIGGER_INIT {.init_function=schmitt_trigger_mcal_init, .name="SchmittTrigger",},
#else
#define SCHMITT_TRIGGER_INIT
#endif

#ifdef HAS_QUADRATURE_MIXER
#include "quadrature_mixer.h"
#define QUADRATURE_MIXER_INIT {.init_function=quadrature_mixer_mcal_init, .name="QuadratureMixer",},
#else
#define QUADRATURE_MIXER_INIT
#endif

#ifdef HAS_HIST_FILTER
#include "hist_filter_mcal.h"
#define HIST_FILTER_INIT {.init_function=hist_filter_mcal_init, .name="HistFilter",},
#else
#define HIST_FILTER_INIT
#endif

// order matter!
#define DSP_INIT               \
    DECIMATOR_INIT             \
    DELTA_SIGMA_INIT           \
    CORRELATOR_NAIV_S16_INIT   \
    SCHMITT_TRIGGER_INIT       \
    FOURIER_SERIES_INIT        \
    CORRELATOR_S16_INIT        \
    FIR_INIT                   \
    HIST_FILTER_INIT           \
    DC_CUT_FILTER_INIT         \
    FIR_INT_INIT               \
    SLIDING_INTEGRAL_INIT      \
    IIR_INIT                   \
    MEDIAN_FILTER_INIT         \
    MEDIAN_FILTER_FAST_INIT    \
    QUADRATURE_MIXER_INIT      \
    MANCHESTER_DECODE_INIT     \
    PHASE_DETECTOR_INIT        \
    SCAN_INIT                  \
    ECHO_EFFECT_INIT

#endif /* DSP_INIT_H */
