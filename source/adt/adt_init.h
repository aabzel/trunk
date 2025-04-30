#ifndef ADT_INIT_H
#define ADT_INIT_H

#include <stdbool.h>

#ifdef HAS_HISTOGRAM
#include "histogram.h"
#define HISTOGRAM_INIT {.init_function=histogram_mcal_init, .name="histogram",},
#else
#define HISTOGRAM_INIT
#endif

#define ADT_INIT HISTOGRAM_INIT

#endif /*ADT_INIT_H*/
