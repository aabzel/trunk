#ifndef THIRD_PARTY_INIT_H
#define THIRD_PARTY_INIT_H


#ifdef HAS_SERVICES
#include "services_init.h"
#else
#define SERVICES_INIT
#endif /*HAS_SERVICES*/

#ifdef HAS_THIRD_PARTY_ASICS
#include "asics_initialize.h"
#else
#define ASICS_INITIALIZE
#endif /*HAS_THIRD_PARTY_ASICS*/

#ifdef HAS_THIRD_PARTY_COMPUTING
#include "computing_initialize.h"
#else
#define COMPUTING_INITIALIZE
#endif /*HAS_THIRD_PARTY_COMPUTING*/

#ifdef HAS_THIRD_PARTY_SENSITIVITY
#include "sensitivity_initialize.h"
#else
#define SENSITIVITY_INITIALIZE
#endif /*HAS_THIRD_PARTY_COMPUTING*/


#ifdef HAS_THIRD_PARTY_STORAGE
#include "storage_initialize.h"
#else
#define STORAGE_INITIALIZE
#endif /*HAS_THIRD_PARTY_STORAGE*/


#define THIRD_PARTY_INIT     \
    COMPUTING_INITIALIZE     \
    ASICS_INITIALIZE         \
    STORAGE_INITIALIZE       \
    SENSITIVITY_INITIALIZE   \
    SERVICES_INIT

#endif /* THIRD_PARTY_INIT_H */
