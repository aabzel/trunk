#ifndef COMPUTING_TASKS_H
#define COMPUTING_TASKS_H

#ifndef HAS_COMPUTING
#error "+HAS_COMPUTING"
#endif

#ifdef HAS_GNSS_PROC
#include "gnss_drv.h"
#define GNSS_TASK {.name="Gnss", .period_us=GNSS_PERIOD_US, .limiter.function=gnss_proc,},
#else
#define GNSS_TASK
#endif


#ifdef HAS_DDS_PROC
#include "dds_drv.h"
#define DDS_TASK {.name="DDS", .period_us=DDS_PERIOD_US, .limiter.function=dds_proc,},
#else
#define DDS_TASK
#endif

#ifdef HAS_PLL_SIM_PROC
#include "pll_sim.h"
#define PLL_SIM_TASK {.name="PllSim", .period_us=PLL_SIM_PERIOD_US, .limiter.function=pll_sim_proc,},
#else
#define PLL_SIM_TASK
#endif

#ifdef HAS_DELTA_SIGMA_PROC
#include "delta_sigma.h"
#define DELTA_SIGMA_TASK {.name="DeltaSigma", .period_us=DELTA_SIGMA_PERIOD_US, .limiter.function=delta_sigma_proc,},
#else
#define DELTA_SIGMA_TASK
#endif

#define COMPUTING_TASKS \
    PLL_SIM_TASK        \
    DDS_TASK            \
    GNSS_TASK            \
    DELTA_SIGMA_TASK


#endif /* COMPUTING_TASKS_H */
