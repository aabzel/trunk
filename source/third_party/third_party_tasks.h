#ifndef THIRD_PARTY_TASKS_H
#define THIRD_PARTY_TASKS_H


#ifdef HAS_THIRD_PARTY_ASICS
#include "asics_routines.h"
#else
#define ASICS_ROUTINE
#endif

#ifdef HAS_THIRD_PARTY_COMPUTING
#include "computing_routines.h"
#else
#define COMPUTING_ROUTINE
#endif

#ifdef HAS_THIRD_PARTY_SENSITIVITY
#include "sensitivity_routines.h"
#else
#define SENSITIVITY_ROUTINE
#endif


#define THIRD_PARTY_TASKS     \
    ASICS_ROUTINE             \
    COMPUTING_ROUTINE         \
    SENSITIVITY_ROUTINE

#endif /* THIRD_PARTY_TASKS_H */
