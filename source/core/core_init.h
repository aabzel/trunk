#ifndef CORE_INIT_H
#define CORE_INIT_H

#include "core_driver.h"

#ifdef HAS_LOG
#define CORE_NAME .name="CORE",
#else
#define CORE_NAME
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#else
#define CORE_MCAL_INIT
#endif

#ifdef HAS_DWT
#include "dwt_mcal.h"
#else
#define DWT_INIT
#endif

#ifdef HAS_CLOCK
#include "clock_mcal.h"
#else
#define CLOCK_INIT
#endif

#define CORE_INIT         \
     CLOCK_INIT           \
     DWT_INIT             \
     CORE_MCAL_INIT


#endif /* CORE_INIT_H */
