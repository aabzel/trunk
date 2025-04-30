#ifndef CLOCK_CUSTOM_TYPES_H
#define CLOCK_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "clock_const.h"
#include "clock_custom_const.h"
#include "nrfx_clock.h"

typedef union {
    nrf_clock_lfclk_t lfclk;
    nrf_clock_hfclk_t hfclk;
    uint8_t byte;
} NrfxClkSrc_t;

#define CLOCK_CUSTOM_TYPES                                                                                             \
    nrfx_clock_event_handler_t event_handler;                                                                          \
    NRF_CLOCK_Type* const registers;

typedef struct {
    char* name;
    nrf_clock_domain_t domain_nrf;
    ClockDomain_t domain_num;
    bool valid;
} ClockInfo_t;

#ifdef __cplusplus
}
#endif

#endif // CLOCK_CUSTOM_TYPES_H
