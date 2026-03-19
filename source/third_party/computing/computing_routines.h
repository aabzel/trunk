#ifndef COMPUTING_ROUTINES_H
#define COMPUTING_ROUTINES_H

#ifndef HAS_COMPUTING
#error "+HAS_COMPUTING"
#endif

#include "std_includes.h"

#ifdef DDS_PROC_IN_USE
#include "dds.h"

bool DDS_proc(void);

#define DDS_ROUTINE {.name="TpDDS", .period_us=DDS_POLL_PERIOD_US, .limiter.function=DDS_proc,},
#else
#define DDS_ROUTINE
#endif

#ifdef HAS_DSP_PROC
#include "dsp.h"

bool DSP_Proc(void);

#define DSP_ROUTINE {.name="TpDDS", .period_us=DSP_POLL_PERIOD_US, .limiter.function=DSP_Proc,},
#else
#define DSP_ROUTINE
#endif


#define COMPUTING_ROUTINE    \
    DDS_ROUTINE
    DSP_ROUTINE



#endif /* COMPUTING_ROUTINES_H */
