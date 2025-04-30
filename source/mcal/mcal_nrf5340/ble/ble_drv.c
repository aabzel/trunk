#include "ble_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAS_CLI
#include "ble_string_reader.h"
#include "cli_config.h"
#endif

#include "bit_utils.h"
#include "ble_bsp.h"
#include "ble_types.h"
#include "hal_nrfx_diag.h"
#include "log.h"
#include "nrfx_blee.h"
#include "sys_config.h"

/* Callback from ble_core when the ble subsystem is ready */
void on_ble_core_ready(void) {
#if 0
	int ret;

	(void)atomic_set(&ble_core_is_ready, (atomic_t) true);

	if (IS_ENABLED(CONFIG_SETTINGS)) {
		settings_load();

		ret = bonding_clear_check();
		ERR_CHK(ret);
	}
#endif
}

bool ble_init(void) {
    bool res = true;
    int ret;
#ifdef HAS_LOG
    LOG_INFO(BLE, "Init..");
#endif /*HAS_LOG*/

    /* Initialize BLE, with callback for when BLE is ready */
    ret = ble_core_init(on_ble_core_ready);
    if(0 != res) {
        LOG_ERROR(BLE, "CoreInitErr");
    } else {
        LOG_INFO(BLE, "CoreInitOk");
    }

    return out_res;
}

bool ble_check(void) { return false; }

bool proc_ble(void) {
    bool res = false;
    return res;
}
