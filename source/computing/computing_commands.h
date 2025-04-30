#ifndef COMPUTING_COMMANDS_H
#define COMPUTING_COMMANDS_H

#ifdef HAS_LOG
#include "log.h"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_COMPUTING
#error "+HAS_COMPUTING"
#endif

#ifndef HAS_COMPUTING_COMMANDS
#error "+HAS_COMPUTING_COMMANDS"
#endif

#ifdef HAS_ANALOG_FILTER_COMMANDS
#include "analog_filter_commands.h"
#else
#define ANALOG_FILTER_COMMANDS
#endif

#ifdef HAS_FOURIER_SERIES_COMMANDS
#include "fourier_series_commands.h"
#else
#define FOURIER_SERIES_COMMANDS
#endif

#ifdef HAS_SCHMITT_TRIGGER_COMMANDS
#include "schmitt_trigger_commands.h"
#else
#define SCHMITT_TRIGGER_COMMANDS
#endif

#ifdef HAS_CALCULATOR_COMMANDS
#include "calculator_commands.h"
#else
#define CALCULATOR_COMMANDS
#endif

#ifdef HAS_CONVERTOR_COMMANDS
#include "convertor_commands.h"
#else
#define CONVERTOR_COMMANDS
#endif

#ifdef HAS_BASE64_COMMANDS
#include "base64_commands.h"
#else
#define BASE64_COMMANDS
#endif

#ifdef HAS_RLE_COMMANDS
#include "rle_commands.h"
#else
#define RLE_COMMANDS
#endif

#ifdef HAS_SW_DAC_COMMANDS
#include "sw_dac_commands.h"
#else
#define SW_DAC_COMMANDS
#endif

#ifdef HAS_SOLUTIONS_COMMANDS
#include "solutions_commands.h"
#else
#define SOLUTIONS_COMMANDS
#endif

#ifdef HAS_FIR_COMMANDS
#include "fir_commands.h"
#else
#define FIR_COMMANDS
#endif

#ifdef HAS_IEC16022_COMMANDS
#include "iec16022_commands.h"
#else
#define IEC16022_COMMANDS
#endif

#ifdef HAS_IIR_COMMANDS
#include "iir_commands.h"
#else
#define IIR_COMMANDS
#endif

#ifdef HAS_SOLVER_COMMANDS
#include "solver_commands.h"
#else
#define SOLVER_COMMANDS
#endif

#ifdef HAS_STATISTICS_COMMANDS
#include "statistics_commands.h"
#else
#define STATISTICS_COMMANDS
#endif

#ifdef HAS_VOLTAGE_DIVIDER_COMMANDS
#include "voltage_divider_commands.h"
#else
#define VOLTAGE_DIVIDER_COMMANDS
#endif
#ifdef HAS_PLL_CALC_COMMANDS
#include "pll_calc_commands.h"
#else
#define PLL_CALC_COMMANDS
#endif

#ifdef HAS_TIMER_CALC_COMMANDS
#include "timer_calc_commands.h"
#else
#define TIMER_CALC_COMMANDS
#endif

#ifdef HAS_MATH_COMMANDS
#include "math_commands.h"
#else
#define MATH_COMMANDS
#endif


#ifdef HAS_PLL_SIM_COMMANDS
#include "pll_sim_commands.h"
#else
#define PLL_SIM_COMMANDS
#endif

#ifdef HAS_DELTA_SIGMA_COMMANDS
#include "delta_sigma_commands.h"
#else
#define DELTA_SIGMA_COMMANDS
#endif

#ifdef HAS_DDS_COMMANDS
#include "dds_commands.h"
#else
#define DDS_COMMANDS
#endif

#ifdef HAS_DSP_COMMANDS
#include "dsp_commands.h"
#else
#define DSP_COMMANDS
#endif

#ifdef HAS_MODULATOR_COMMANDS
#include "modulator_commands.h"
#else
#define MODULATOR_COMMANDS
#endif

#ifdef HAS_TOPO_SORT_COMMANDS
#include "topo_sort_commands.h"
#else
#define TOPO_SORT_COMMANDS
#endif

#define COMPUTING_COMMANDS      \
    ANALOG_FILTER_COMMANDS      \
    BASE64_COMMANDS             \
    CALCULATOR_COMMANDS         \
    CONVERTOR_COMMANDS          \
    DDS_COMMANDS                \
    DSP_COMMANDS                \
    MATH_COMMANDS               \
    MODULATOR_COMMANDS          \
    IEC16022_COMMANDS           \
    RLE_COMMANDS                \
    PLL_CALC_COMMANDS           \
    PLL_SIM_COMMANDS            \
    SOLVER_COMMANDS             \
    SOLUTIONS_COMMANDS          \
    STATISTICS_COMMANDS         \
    SW_DAC_COMMANDS             \
    TIMER_CALC_COMMANDS         \
    VOLTAGE_DIVIDER_COMMANDS

#endif /* COMPUTING_COMMANDS_H */
