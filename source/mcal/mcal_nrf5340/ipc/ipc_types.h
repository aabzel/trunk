#ifndef NRF_IPC_TYPES_H
#define NRF_IPC_TYPES_H

#include <stdint.h>

#include "ipc_const.h"
#include "nrfx_ipc.h"

typedef struct{
     bool valid;
	 nrfx_ipc_config_t config;
}IpcConfig_t;

typedef struct{
    bool valid;
    uint32_t it_cnt;
}Ipc_t;

#endif /* NRF_IPC_TYPES_H  */
