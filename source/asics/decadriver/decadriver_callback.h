#ifndef DECADRIVER_CALLBACK_H
#define DECADRIVER_CALLBACK_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_DECADRIVER
#error "+ HAS_DECADRIVER"
#endif

#include "deca_device_api.h"

void rx_ok_callback(const dwt_cb_data_t* cb_data);
void rx_to_callback(const dwt_cb_data_t* cb_data);
void rx_err_callback(const dwt_cb_data_t* cb_data);
void tx_conf_callback(const dwt_cb_data_t* cb_data);

#ifdef __cplusplus
}
#endif

#endif /* DECADRIVER_CALLBACK_H */
