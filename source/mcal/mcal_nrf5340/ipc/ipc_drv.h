#ifndef NRF_IPC_DRV_H
#define NRF_IPC_DRV_H

#include "ipc_types.h"
#include "ipc_config.h"

#ifndef HAS_IPC
#error "+HAS_IPC"
#endif

bool ipc_proc(void);
bool ipc_check(void);
bool ipc_init(void);

#endif /* NRF_IPC_DRV_H  */
