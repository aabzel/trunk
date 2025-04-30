#ifndef SPI_NRF_TYPES_H
#define SPI_NRF_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "nrf_spim.h"
#include "spi_nrf_const.h"

#ifdef NRFX_SPIM_ENABLED
#include "nrfx_spim.h"
#endif

typedef struct {
    nrf_spim_frequency_t nrf_bit_rate;
    uint32_t bit_rate_hz;
} SpiFreqInto_t;

typedef struct {
    uint8_t num;
    uint8_t spi_inst_id;
    nrfx_spim_evt_handler_t event_handler;
    NRF_SPIM_Type* spi_ptr;
    bool valid;
} NrfSpiInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* SPI_NRF_TYPES_H */
