
#ifndef NVS_NRF_DIAG_H
#define NVS_NRF_DIAG_H

#include <stdbool.h>

#ifndef HAS_NVS
#error "+HAS_NVS"
#endif

bool nvs_custom_diag(void);

#endif /* NVS_NRF_DIAG_H  */
