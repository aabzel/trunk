#ifndef PDM_CUSTOM_TYPES_H
#define PDM_CUSTOM_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "pdm_custom_const.h"

#ifdef NRFX_PDM_ENABLED
#include "nrfx_pdm.h"
#endif

typedef struct {
    nrf_pdm_freq_t nrf_frequency_code;
    uint32_t frequency_hz;
} PdmFreqInfo_t;

typedef struct{
    uint8_t num;
    bool valid;
    nrfx_pdm_event_handler_t event_handler;
    NRF_PDM_Type* const registers;
}PdmStaticInfo_t;

#endif /* PDM_CUSTOM_TYPES_H  */
