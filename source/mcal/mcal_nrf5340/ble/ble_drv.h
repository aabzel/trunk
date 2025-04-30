#ifndef NRF_BLE_DRV_H
#define NRF_BLE_DRV_H

#include "sys_config.h"
#include "ble_bsp.h"
#include "ble_config.h"
#include "ble_nrf_types.h"

#define BLE_PERIOD_US 1

bool proc_ble(void);
bool ble_check(void);
bool ble_init(void);

#endif /* NRF_BLE_DRV_H  */
