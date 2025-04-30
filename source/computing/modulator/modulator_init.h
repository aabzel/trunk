#ifndef MODULATOR_INIT_H
#define MODULATOR_INIT_H

#include "std_includes.h"

#ifndef HAS_MODULATOR
#error "+HAS_MODULATOR"
#endif

#ifdef HAS_BPSK
#include "bpsk.h"
#define BPSK_INIT {.init_function=bpsk_mcal_init, .name="Bpsk",},
#else
#define BPSK_INIT
#endif /*HAS_BPSK*/

/*order matter*/
#define MODULATOR_INIT                   \
    BPSK_INIT

#endif /* MODULATOR_INIT_H */
