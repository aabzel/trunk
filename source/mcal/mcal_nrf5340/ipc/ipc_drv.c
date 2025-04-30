#include "nrfx_errors.h"

#include "nrfx_ipc.h"
#include "nrf_ipc.h"
#include "ipc_config.h"
#include "hal_nrfx_diag.h"
#include "log.h"

bool ipc_proc(void) {
	bool res = false;
    return res;
}

bool ipc_check(void) {
	bool res = false;
	return res;
}

static void nrfx_ipc_handler(uint32_t event_mask, void *p_context){
	Ipc.it_cnt++;
}

bool ipc_init(void) {
	bool res = false;
	LOG_INFO(IPC,"Init");
	nrfx_err_t ret= nrfx_ipc_init(0, nrfx_ipc_handler, NULL);
	if(NRFX_SUCCESS==ret) {
		res = true;
		nrf_ipc_send_config_set(NRF_IPC, CHAN_TX, 1 << CHAN_TX);
		nrf_ipc_receive_config_set(NRF_IPC, CHAN_RX, 1 << CHAN_RX);
		//nrfx_ipc_config_load(&IpcConfig.config);
		nrf_ipc_int_enable(NRF_IPC, 1 << CHAN_RX);
		LOG_INFO(IPC,"InitOk");
	}else{
		LOG_ERROR(IPC,"InitErr %s", HalStatus2Str(ret));
		res = false;
	}
    return res;
}
