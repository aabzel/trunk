#ifndef ASICS_ROUTINES_H
#define ASICS_ROUTINES_H

#include "std_includes.h"

#ifdef HAS_LIS3DH_EHAL_PROC
#include "lis3dh_driver.h"

bool LIS3DH_EHAL_Process(void);
bool LIS3DH_EHAL_ProcessLink(void);

#define LIS3DH_ROUTINE                                    \
    {                                                     \
        .name = "TpLis3gh",                               \
        .period_us = LIS3DH_POLLING_PERIOD_US,            \
        .limiter.function = LIS3DH_EHAL_Process,          \
    },                                                    \
    {                                                     \
        .name = "TpLis3ghLink",                           \
        .period_us = LIS3DH_LINK_POLLING_PERIOD_US,       \
        .limiter.function = LIS3DH_EHAL_ProcessLink,      \
    },

#else
#define LIS3DH_ROUTINE
#endif

#ifdef HAS_NAU8814_EHAL_PROC
#include "nau8814_driver.h"

bool NAU8814_EHAL_Process(void);

#define NAU8814_ROUTINE                                \
    {                                                  \
        .name = "TpNau8814",                           \
        .period_us = NAU8814_POLL_PERIOD_US,           \
        .limiter.function = NAU8814_EHAL_Process,      \
    },

#else
#define NAU8814_ROUTINE
#endif

#define ASICS_ROUTINE    \
    LIS3DH_ROUTINE       \
    NAU8814_ROUTINE

#endif /* ASICS_ROUTINES_H */
