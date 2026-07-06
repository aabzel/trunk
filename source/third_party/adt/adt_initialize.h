#ifndef THIRD_PARTY_ADT_INITIALIZE_H
#define THIRD_PARTY_ADT_INITIALIZE_H


#ifdef HAS_IQUEUE
#include "iqueue.h"
#define IQUEUE_INITIALIZE {.init_function=iqueue_mcal_init, .name="iQueue",},
#else
#define IQUEUE_INITIALIZE
#endif

#define ADT_INITIALIZE            \
    IQUEUE_INITIALIZE

#endif /*THIRD_PARTY_ADT_INITIALIZE_H */
