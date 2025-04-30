#ifndef SOCKET_CONFIG_H
#define SOCKET_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "socket_types.h"

#ifndef HAS_SOCKET
#error " +HAS_SOCKET"
#endif

extern const SocketConfig_t SocketConfig[];
extern SocketHandle_t SocketInstance[];

uint32_t socket_get_cnt(void);

#endif /* SOCKET_CONFIG_H */
