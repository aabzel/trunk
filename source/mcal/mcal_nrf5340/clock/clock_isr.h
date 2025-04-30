#ifndef CLOCKS_CUSTOM_ISR_H
#define CLOCKS_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrfx_clock.h"

void NrfxClockEventHandler(nrfx_clock_evt_type_t event);

#ifdef __cplusplus
}
#endif

#endif // CLOCKS_CUSTOM_ISR_H
