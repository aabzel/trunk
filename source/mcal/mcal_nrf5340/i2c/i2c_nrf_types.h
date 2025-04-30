#ifndef I2C_NRF_TYPES_H
#define I2C_NRF_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "nrfx_twim.h"


typedef struct  {
    nrfx_twim_t twim;
    nrfx_twim_evt_type_t result;
} twim_dev_t;

typedef struct  {
	nrf_twim_frequency_t nrf_rate;
	uint32_t rate_hz;
} I2cAvailRates_t;

#ifdef __cplusplus
}
#endif

#endif /* I2C_NRF_TYPES_H */
