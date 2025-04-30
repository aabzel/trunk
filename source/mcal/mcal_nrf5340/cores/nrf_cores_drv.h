#ifndef NRF_CORES_DRV_H
#define NRF_CORES_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_NRF_CORES
#error "+HAS_NRF_CORES"
#endif

bool nrf_core_network_set_state(bool status);
bool nrf_cores_init(void);

#ifdef __cplusplus
}
#endif

#endif /* NRF_CORES_DRV_H  */
