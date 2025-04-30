#ifndef SOCKET_DRV_H
#define SOCKET_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "socket_config.h"
#include "socket_types.h"
#ifdef HAS_SOCKET_DIAG
#include "socket_diag.h"
#endif

#include "socket_client.h"
#include "socket_server.h"

SocketHandle_t* SocketGetNode(uint8_t num);
const SocketConfig_t* SocketGetConfig(uint8_t num);

bool socket_init_one(uint8_t num);
bool socket_proc_one(uint8_t num);
bool socket_init(void);
bool socket_proc(void);

#endif /* SOCKET_DRV_H  */
