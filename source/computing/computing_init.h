#ifndef PROC_COMPUTING_H
#define PROC_COMPUTING_H

#include "std_includes.h"

#ifndef HAS_COMPUTING
#error "+HAS_COMPUTING"
#endif

#ifdef HAS_CLOCK_DIVIDER
#include "clock_divider.h"
#define CLOCK_DIVIDER_INIT {.init_function=clock_divider_mcal_init, .name="ClockDivider",},
#else
#define CLOCK_DIVIDER_INIT
#endif /*HAS_TOPO_SORT*/

#ifdef HAS_DDS
#include "dds_drv.h"
#define DDS_INIT {.init_function=dds_mcal_init, .name="Dds",},
#else
#define DDS_INIT
#endif /*HAS_DDS*/

#ifdef HAS_DSP
#include "dsp_init.h"
#else
#define DSP_INIT
#endif /*HAS_DSP*/

#ifdef HAS_GPS
#include "gps.h"
#define GPS_INIT {.init_function=gps_mcal_init, .name="GPS",},
#else
#define GPS_INIT
#endif /*HAS_IIR*/

#ifdef HAS_MODULATOR
#include "modulator_init.h"
#else
#define MODULATOR_INIT
#endif /*HAS_MODULATOR*/

#ifdef HAS_PLL_SIM
#include "pll_sim.h"
#define PLL_SIM_INIT {.init_function=pll_sim_mcal_init, .name="PllSim",},
#else
#define PLL_SIM_INIT
#endif /*HAS_PLL_SIM*/

#ifdef HAS_SDR
#include "sdr_drv.h"
#define SDR_INIT {.init_function=local_oscillator_mcal_init, .name="LocalOscillator",},
#else
#define SDR_INIT
#endif /*HAS_SDR*/


#ifdef HAS_GNSS
#include "gnss_drv.h"
#define GNSS_INIT {.init_function=gnss_mcal_init, .name="Gnss",},
#else
#define GNSS_INIT
#endif /*HAS_IIR*/


/*order matter*/
#define COMPUTING_INIT                   \
    DDS_INIT                             \
    CLOCK_DIVIDER_INIT                   \
    DSP_INIT                             \
    GPS_INIT                             \
    GNSS_INIT                            \
    PLL_SIM_INIT                         \
    SDR_INIT                             \
    MODULATOR_INIT

#endif /* PROC_COMPUTING_H */
