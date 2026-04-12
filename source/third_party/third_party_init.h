#ifndef THIRD_PARTY_INIT_H
#define THIRD_PARTY_INIT_H


#ifdef HAS_THIRD_PARTY_ADT
#include "adt_initialize.h"
#else
#define ADT_INITIALIZE
#endif

#ifdef HAS_SERVICES
#include "services_initialize.h"
#else
#define SERVICES_INIT
#endif

#ifdef HAS_THIRD_PARTY_ASICS
#include "asics_initialize.h"
#else
#define ASICS_INITIALIZE
#endif

#ifdef HAS_THIRD_PARTY_COMPUTING
#include "computing_initialize.h"
#else
#define COMPUTING_INITIALIZE
#endif

#ifdef HAS_THIRD_PARTY_SENSITIVITY
#include "sensitivity_initialize.h"
#else
#define SENSITIVITY_INITIALIZE
#endif

#ifdef HAS_THIRD_PARTY_STORAGE
#include "storage_initialize.h"
#else
#define STORAGE_INITIALIZE
#endif

#define THIRD_PARTY_INIT     \
    ADT_INITIALIZE           \
    COMPUTING_INITIALIZE     \
    ASICS_INITIALIZE         \
    STORAGE_INITIALIZE       \
    SENSITIVITY_INITIALIZE   \
    SERVICES_INIT

#endif /* THIRD_PARTY_INIT_H */
